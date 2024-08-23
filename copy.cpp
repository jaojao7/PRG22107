#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <map>
#include <set>
#include <locale>  
#include <windows.h>
#include <cstdlib>
#include <thread>

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
    string localAtual;  // Local onde o jogador está

    Jogador(string nome, bool anfitriao = false) 
        : nome(nome), anfitriao(anfitriao), mostrarCartas(false), localAtual("Banheiro") {}

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
            cout << nome << " nao quer mostrar suas cartas." << endl;
        }
    }

    bool possuiCarta(const string& nomeCarta) const {
        return any_of(cartas.begin(), cartas.end(), [&](const Carta& carta) {
            return carta.getNome() == nomeCarta;
        });
    }

    void moverPara(string novoLocal) {
        localAtual = novoLocal;
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
    map<string, vector<string>> adjacencias; // Mapa de locais adjacentes

    void inicializarAdjacencias() {
        adjacencias["Banheiro"] = {"Laboratório", "Biblioteca"};
        adjacencias["Laboratório"] = {"Banheiro", "Biblioteca", "Almox"};
        adjacencias["Biblioteca"] = {"Banheiro", "Laboratório", "Entrada"};
        adjacencias["Entrada"] = {"Biblioteca", "Almox"};
        adjacencias["Almox"] = {"Laboratório", "Entrada", "Cantina"};
        adjacencias["Cantina"] = {"Almox"};
    }

    int rolarDado() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); 
        return dist6(rng);
    }
    void moverJogador(Jogador& jogador) {
        movimento = rolarDado();
        cout << jogador.nome << " rolou um " << movimento << "." << endl;

        // Mostrar locais possíveis com base nos movimentos e locais adjacentes
        cout << "Escolha um local para mover: ";
        vector<string> opcoesMoveis = adjacencias[jogador.localAtual];
        for (size_t i = 0; i < opcoesMoveis.size(); ++i) {
            cout << i + 1 << ": " << opcoesMoveis[i] << " ";
        }
        cout << endl;

        int escolha;
        cin >> escolha;

        if (escolha >= 1 && escolha <= static_cast<int>(opcoesMoveis.size())) {
            jogador.moverPara(opcoesMoveis[escolha - 1]);
            cout << jogador.nome << " se moveu para " << jogador.localAtual << "." << endl;
        } else {
            cout << "Local invalido. O jogador permanece no mesmo lugar." << endl;
        }
    }

    bool verificarPalpite(const Palpite& palpite) const {
        if (palpite.getSuspeito() == crime.suspeito && palpite.getArma() == crime.arma && palpite.getLocal() == crime.local) {
            cout << "Voce acertou! O crime foi cometido por " << crime.suspeito << " com " << crime.arma << " no " << crime.local << "." << endl;
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
    Jogo(int numBots) : rng(random_device{}()), localAtual("Banheiro"), movimento(0) {
        inicializarAdjacencias();
        
        // Inicializar cartas
        vector<string> suspeitos = {"Thaine", "Diana", "João Pedro", "Eduardo", "Giovanna", "Hugo"};
        vector<string> armas = {"Faca", "Chave de Fenda", "Ferro de Solda", "Livro de Eletrônica", "Transformador", "Soprador Térmico"};
        vector<string> locais = {"Banheiro", "Laboratório", "Biblioteca", "Entrada", "Almox", "Cantina"};

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

        // Mostrar cartas do jogador no início
        jogadores[0].mostrarCartas = true;
        jogadores[0].mostrarCartasJogador();
    }

    void iniciarJogo() {
        cout << "Bem-vindo ao jogo de Detetive!" << endl;
        bool jogoAtivo = true;
        while (jogoAtivo) {
            for (auto& jogador : jogadores) {
                if (jogador.anfitriao) {
                    moverJogador(jogador);
                    jogoAtivo = darPalpite(jogador);
                    if (!jogoAtivo) {
                        std::system("cls");
                        cout << "PARABENS VOCE RESOLVEU!" << endl;
                        break;
                    }
                } else {
                    // Mostrar cartas dos bots somente se um palpite é feito com uma carta do bot
                    jogador.mostrarCartas = false;
                    botFazPalpite(jogador);
                }
            }
        }
    }

 void botFazPalpite(Jogador& bot) {
    string suspeito, arma, local;

    // Escolher palpite inteligente
    for (const auto& carta : cartas) {
        if (bot.possuiCarta(carta.getNome())) continue;

        if (carta.getTipo() == "Suspeito") {
            suspeito = carta.getNome();
        } else if (carta.getTipo() == "Arma") {
            arma = carta.getNome();
        } else if (carta.getTipo() == "Local") {
            local = carta.getNome();
        }
    }

    if (local != bot.localAtual) {
        // Bot precisa se mover para o local correto antes de fazer o palpite
        cout << bot.nome << " precisa se mover para " << local << " antes de fazer um palpite." << endl;
        bot.moverPara(local); // Mova o bot para o local correto
        cout << bot.nome << " se moveu para " << bot.localAtual << "." << endl;
    }

    // Fazer o palpite agora que o bot está no local correto
    cout << bot.nome << " faz um palpite: " << suspeito << " com " << arma << " no " << local << "." << endl;
    verificarPalpite(Palpite(suspeito, arma, local));
}

    bool darPalpite(Jogador& jogador) {
        string suspeito, arma, local;
        cout << jogador.nome << ", faca seu palpite." << endl;

        // Escolher opções de palpite
        cout << "Escolha um suspeito:" << endl;
        for (const auto& s : {"Thaine", "Diana", "João Pedro", "Eduardo", "Giovanna", "Hugo"}) {
            cout << s << endl;
        }
        cout << "Digite o nome do suspeito: ";
        cin.ignore();
        getline(cin, suspeito);

        cout << "Escolha uma arma:" << endl;
        for (const auto& a : {"Faca", "Chave de Fenda", "Ferro de Solda", "Livro de Eletrônica", "Transformador", "Soprador Térmico"}) {
            cout << a << endl;
        }
        cout << "Digite o nome da arma: ";
        getline(cin, arma);

        cout << "Escolha um local:" << endl;
        for (const auto& l : {"Banheiro", "Laboratório", "Biblioteca", "Entrada", "Almox", "Cantina"}) {
            cout << l << endl;
        }
        cout << "Digite o nome do local: ";
        getline(cin, local);

        // Verificar se o jogador está no local correto
        if (local != localAtual) {
            cout << "Voce so pode dar palpite no local onde voce esta. Mova-se para o local correto primeiro." << endl;
            return true; // Continua o jogo
        }

        // Verificar se o palpite inclui uma carta dos bots
        string cartaBot = cartaBotInvolvida(suspeito, arma, local);

        if (!cartaBot.empty()) {
            cout << "Atencao: O seu palpite inclui uma carta que um bot possui. A carta é: " << cartaBot << "." << endl;
            // for (auto& jogadorBot : jogadores) {
            //     if (!jogadorBot.anfitriao) {
            //         jogadorBot.mostrarCartas = true;
            //         jogadorBot.mostrarCartasJogador();
            //     }
            // }
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
    std::setlocale(LC_ALL, "pt_BR");
    SetConsoleOutputCP(CP_UTF8);

    int numBots;
    cout<<endl;
    cout << "==================================" << endl;
    cout << "|                                |" << endl;
    cout << "|      BEM-VINDO AO DETETIVE     |" << endl;
    cout << "|                                |" << endl;
    cout << "==================================" << endl;
    cout<<endl;
    cout << "Um aluno 'exemplar' foi assassinado na instituição,\nmuitos tinham motivos para matar ...... até você mesmo pode ter motivos.\n";
    cout << "Diana é uma aluna dissimulada e carismática, sempre sociável e acima de suspeitas.\n";
    cout << "Eduardo é um aluno ambicioso e mais reservado, o que deixa um ar de mistério nas investigações.\n";
    cout << "Giovanna é uma aluna amável e simpática, utiliza disso para conseguir o que deseja.\n";
    cout << "Hugo é um professor dedicado e enigmático, está à espreita daqueles que são suspeitos.\n";
    cout << "João é um aluno astuto e perspicaz, mas associado a eventos suspeitos dentro da instituição.\n";
    cout << "Thaine é uma aluna discreta e atraente, sempre fornecendo informações úteis sobre as pessoas.\n" << endl;

    cout << "PRESSIONE ENTER PARA CONTNUAR..."   << endl;


    if (cin.get() == '\n') {   

        system("start window.exe"); 

        cout << "Digite o numero de bots (1-3): ";
        cin >> numBots;

        if (numBots < 1 || numBots > 3) {
            cout << "Numero invalido de bots." << endl;
            return 1;
        }

        Jogo jogo(numBots);
        jogo.iniciarJogo();}
    else {}
    
    system("pause");
    return 0;
}
