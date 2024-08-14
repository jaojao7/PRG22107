#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

class Carta {
public:
    string tipo;
    string nome;

    Carta(string tipo, string nome) : tipo(tipo), nome(nome) {}

    string getTipo() const {
        return tipo;
    }

    string getNome() const {
        return nome;
    }
};

class Palpite {
public:
    string suspeito;
    string arma;
    string local;

    Palpite(string suspeito, string arma, string local) : suspeito(suspeito), arma(arma), local(local) {}

    string getSuspeito() const {
        return suspeito;
    }

    string getArma() const {
        return arma;
    }

    string getLocal() const {
        return local;
    }
};

class Jogador {
public:
    string nome;
    vector<Carta> cartas;
    bool anfitriao;
    bool mostrarCartas; // Controlar a exibição das cartas

    Jogador(string nome, bool anfitriao = false) : nome(nome), anfitriao(anfitriao), mostrarCartas(false) {}

    void receberCarta(Carta carta) {
        cartas.push_back(carta);
    }

    void mostrarCartasJogador() const { // Mostrar cartas se permitido
        if (mostrarCartas) {
            cout << "Cartas de " << nome << ":" << endl;
            for (const auto& carta : cartas) {
                cout << carta.getNome() << " (" << carta.getTipo() << ")" << endl;
            }
            cout << endl;
        } else {
            cout << nome << " não quer mostrar suas cartas." << endl;
        }
    }
};

class Crime {
public:
    string suspeito;
    string arma;
    string local;

    Crime() : suspeito(""), arma(""), local("") {}

    Crime(string suspeito, string arma, string local) : suspeito(suspeito), arma(arma), local(local) {}

    void revelarCrime() const {
        cout << "Crime: " << suspeito << " com " << arma << " no " << local << endl;
    }
};

class Jogo {
private:
    vector<Carta> cartas;
    vector<Jogador> jogadores;
    Crime crime;
    mt19937 rng;
    string localAtual; // Local onde o jogador está
    int movimento; // Número de movimentos com base no dado rolado

    int rolarDado() {
        uniform_int_distribution<int> dist(1, 6);
        return dist(rng);
    }

    void moverJogador(Jogador& jogador) {
        movimento = rolarDado();
        cout << jogador.nome << " rolou um " << movimento << "." << endl;

        // Definir o novo local baseado na rolagem do dado
        cout << "Escolha um local para mover (1: Salão, 2: Salão de jogos, 3: Biblioteca, 4: Escritório, 5: Jardim de inverno, 6: Cozinha): ";
        int escolha;
        cin >> escolha;

        if (escolha >= 1 && escolha <= 6) {
            localAtual = (escolha == 1) ? "Salão" :
                         (escolha == 2) ? "Salão de jogos" :
                         (escolha == 3) ? "Biblioteca" :
                         (escolha == 4) ? "Escritório" :
                         (escolha == 5) ? "Jardim de inverno" : "Cozinha";
            cout << jogador.nome << " se moveu para " << localAtual << "." << endl;
        } else {
            cout << "Local inválido. O jogador permanece no mesmo lugar." << endl;
        }
    }

    bool verificarPalpite(const Palpite& palpite) const {
        if (palpite.getSuspeito() == crime.suspeito && palpite.getArma() == crime.arma && palpite.getLocal() == crime.local) {
            cout << "Você acertou! O crime foi cometido por " << crime.suspeito << " com " << crime.arma << " no " << crime.local << "." << endl;
            return false;
        } else {
            cout << "Palpite errado. Continue tentando." << endl;
            return true;
        }
    }

    string cartaBotInvolvida(const string& suspeito, const string& arma, const string& local) const {
        for (const auto& jogador : jogadores) {
            if (!jogador.anfitriao) { // Verificar apenas bots
                for (const auto& carta : jogador.cartas) {
                    if (carta.getNome() == suspeito || carta.getNome() == arma || carta.getNome() == local) {
                        return carta.getNome(); // Retornar a carta envolvida
                    }
                }
            }
        }
        return ""; // Retornar vazio se nenhuma carta do bot estiver envolvida
    }

public:
    Jogo(int numBots) : rng(random_device{}()), localAtual(""), movimento(0) {
        // Inicializar cartas
        vector<string> suspeitos = {"Coronel Mostarda", "Professor Black", "Senhor Marinho", "Senhora Violeta", "Dona Branca", "Senhora Vermelha"};
        vector<string> armas = {"Faca", "Castiçal", "Revólver", "Corda", "Cano", "Chave inglesa"};
        vector<string> locais = {"Salão", "Salão de jogos", "Biblioteca", "Escritório", "Jardim de inverno", "Cozinha"};

        for (const auto& s : suspeitos) cartas.emplace_back("Suspeito", s);
        for (const auto& a : armas) cartas.emplace_back("Arma", a);
        for (const auto& l : locais) cartas.emplace_back("Local", l);

        // Sortear crime
        uniform_int_distribution<int> dist(0, suspeitos.size() - 1);
        string suspeito = suspeitos[dist(rng)];
        string arma = armas[dist(rng)];
        string local = locais[dist(rng)];
        crime = Crime(suspeito, arma, local);

        // Remover cartas do crime
        cartas.erase(remove_if(cartas.begin(), cartas.end(), [&](const Carta& c) {
            return c.getNome() == suspeito || c.getNome() == arma || c.getNome() == local;
        }), cartas.end());

        // Adicionar jogadores
        jogadores.emplace_back("Jogador", true);
        for (int i = 0; i < numBots; ++i) {
            jogadores.emplace_back("Bot " + to_string(i + 1));
        }

        // Embaralhar e distribuir cartas
        shuffle(cartas.begin(), cartas.end(), rng);
        distribuirCartas();
    }

    void distribuirCartas() {
        size_t jogadorAtual = 0;
        for (const auto& carta : cartas) {
            jogadores[jogadorAtual].receberCarta(carta);
            jogadorAtual = (jogadorAtual + 1) % jogadores.size();
        }
    }

    void iniciarJogo() {
        cout << "Bem-vindo ao jogo de Detetive!" << endl;
        bool jogoAtivo = true;
        while (jogoAtivo) {
            for (auto& jogador : jogadores) {
                if (jogador.anfitriao) {
                    moverJogador(jogador);
                    jogoAtivo = darPalpite(jogador);
                    if (!jogoAtivo) break;
                } else {
                    // Mostrar cartas dos bots somente se um palpite é feito com uma carta do bot
                    jogador.mostrarCartas = false;
                }
            }
        }
    }

    bool darPalpite(Jogador& jogador) {
        string suspeito, arma, local;
        cout << jogador.nome << ", faça seu palpite." << endl;

        // Escolher opções de palpite
        cout << "Escolha um suspeito:" << endl;
        for (const auto& s : {"Coronel Mostarda", "Professor Black", "Senhor Marinho", "Senhora Violeta", "Dona Branca", "Senhora Vermelha"}) {
            cout << s << endl;
        }
        cout << "Digite o nome do suspeito: ";
        cin.ignore();
        getline(cin, suspeito);

        cout << "Escolha uma arma:" << endl;
        for (const auto& a : {"Faca", "Castiçal", "Revólver", "Corda", "Cano", "Chave inglesa"}) {
            cout << a << endl;
        }
        cout << "Digite o nome da arma: ";
        getline(cin, arma);

        cout << "Escolha um local:" << endl;
        for (const auto& l : {"Salão", "Salão de jogos", "Biblioteca", "Escritório", "Jardim de inverno", "Cozinha"}) {
            cout << l << endl;
        }
        cout << "Digite o nome do local: ";
        getline(cin, local);

        // Verificar se o jogador está no local correto
        if (local != localAtual) {
            cout << "Você só pode dar palpite no local onde você está. Mova-se para o local correto primeiro." << endl;
            return true; // Continua o jogo
        }

        // Verificar se o palpite inclui uma carta dos bots
        string cartaBot = cartaBotInvolvida(suspeito, arma, local);

        if (!cartaBot.empty()) {
            cout << "Atenção: O seu palpite inclui uma carta que um bot possui. A carta é: " << cartaBot << "." << endl;
            for (auto& jogadorBot : jogadores) {
                if (!jogadorBot.anfitriao) {
                    jogadorBot.mostrarCartas = true;
                    jogadorBot.mostrarCartasJogador();
                }
            }
        }

        bool resultado = verificarPalpite(Palpite(suspeito, arma, local));

        // Após o palpite, ocultar cartas dos bots novamente
        if (!cartaBot.empty()) {
            for (auto& jogadorBot : jogadores) {
                if (!jogadorBot.anfitriao) {
                    jogadorBot.mostrarCartas = false;
                }
            }
        }

        return resultado;
    }
};

int main() {
    int numBots;
    cout << "Digite o número de bots (1-5): ";
    cin >> numBots;

    if (numBots < 1 || numBots > 5) {
        cout << "Número inválido de bots." << endl;
        return 1;
    }

    Jogo jogo(numBots);
    jogo.iniciarJogo();

    return 0;
}
