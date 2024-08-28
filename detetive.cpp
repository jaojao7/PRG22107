#include <iostream> //Biblioteca de entrada e saída 
#include <vector> //utilizada para criar e manipular vetores (dinâmico)
#include <string>  // Biblioteca Padrão
#include <algorithm>
#include <random>
#include <map>
#include <set>
#include <locale>  
#include <windows.h>
#include <cstdlib>
#include <thread>

using namespace std;

class Carta { //Classe Carta
private:
    string tipo; //Atributo do tipo
    string nome; //Atributo nome
public:
    Carta(string tipo, string nome) : tipo(tipo), nome(nome) {} // Construtor da classe

    string getTipo() const { // Metodo getTipo
        return tipo;
    }

    string getNome() const { // Metodo getNome
        return nome;
    }
};

class Palpite { // Classe Palpite
private:
    string suspeito; // Atributo suspeito
    string arma;    // Atributo arma
    string local;   // Atributo local

public:
    Palpite(string suspeito, string arma, string local) : suspeito(suspeito), arma(arma), local(local) {} // Construtor da classe Palpite

    string getSuspeito() const { // Método que retorna o suspeito do palpite
        return suspeito;
    }

    string getArma() const { // Método que retorna a arma do palpite
        return arma;
    }

    string getLocal() const { // Método que retorna o local do palpite
        return local;
    }
};

class Jogador { // Classe jogador
public:
    string nome; // Atributo Nome 
    vector<Carta> cartas; // Atributo cartas do jogar
    bool anfitriao; //
    bool mostrarCartas; // Controla a exibição das cartas
    string localAtual;  // Local onde o jogador está

    Jogador(string nome, bool anfitriao = false) 
        : nome(nome), anfitriao(anfitriao), mostrarCartas(false), localAtual("Banheiro") {} // Construtor

    void receberCarta(Carta carta) { // Método para receber as cartas
        cartas.push_back(carta);
    }

    void mostrarCartasJogador() const { // Mostrar as cartas do jogador se permitido
        if (mostrarCartas) {
            cout << "Cartas de " << nome << ":" << endl; 
            for (const auto& carta : cartas) { // for que passa por todas as cartas do jogador e imprime o tipo e nome da mesma
                cout << carta.getNome() << " (" << carta.getTipo() << ")" << endl;
            }
            cout << endl; // Pula linha
        } 
    }

    bool possuiCarta(const string& nomeCarta) const { // Método para pegar o nome da carta e verificar se a mesma se encontra nas cartas do jogador
        return any_of(cartas.begin(), cartas.end(), [&](const Carta& carta) {
            return carta.getNome() == nomeCarta;
        });
    }

    void moverPara(string novoLocal) { // Método da classe para movimentar para um novo local
        localAtual = novoLocal;
    }
};


class Crime { // Classe crime
private:
    string assasino; // Atributo privado do real assasino
    string arma;    // Atributo privado da real arma usada
    string local;   // Atributo privado do local real dp crime

public:
    Crime() : assasino(""), arma(""), local("") {} // Construtor padrão com inicizaliação vazia

    Crime(string suspeito, string arma, string local) : assasino(suspeito), arma(arma), local(local) {} // Construtor 

    void revelarCrime() const { // Método para revelar o crime
        cout << "Crime: " << assasino << " com " << arma << " no " << local << endl;
    }
    
    string getAssasino() const { // Métodos get para retornar as informações do crime
        return assasino;
    }

    string getArma() const {
        return arma;
    }

    string getLocal() const {
        return local;
    }
};

class Jogo { // Classe Jogo 
private:
    vector<Carta> cartas; // Obejto cartas
    vector<Jogador> jogadores; // Objeto Jogadores
    Crime crime; // Objeto crime
    mt19937 rng; // Usado para gerar valores aleatórios
    string localAtual; // Local onde o jogador está
    int movimento; // Número de movimentos com base no dado rolado
    map<string, vector<string>> adjacencias; // Mapa de locais adjacentes

    void inicializarAdjacencias() { // Método para definir as adjacenciais (proximidades) dos locais no tabuleiro virtual
        adjacencias["Banheiro"] = {"Laboratório", "Biblioteca",};
        adjacencias["Laboratório"] = {"Banheiro", "Biblioteca", "Almox"};
        adjacencias["Biblioteca"] = {"Banheiro", "Laboratório","Entrada"};
        adjacencias["Entrada"] = {"Biblioteca", "Almox"};
        adjacencias["Almox"] = {"Laboratório", "Entrada", "Cantina"};
        adjacencias["Cantina"] = {"Almox"};
    }

    class Dado {
        mt19937 rng;
        uniform_int_distribution<mt19937::result_type> dist6;
    public:
        Dado(mt19937::result_type seed) : rng(seed), dist6(1, 6) {}

        int rolarDado() {
            return dist6(rng);
        }
    };

    void moverJogador(Jogador& jogador) { // Método de movimentação do jogador
        static Dado dado(rng()); // Cria o obejto dado uma vez e é reutilizado
        char mover;

        movimento = dado.rolarDado(); // Movimento do dado

        cout << jogador.nome << " rolou o dado e saiu " << movimento << "." << endl;
        
        cout << jogador.nome << " deseja se movimentar? (s/n) " << endl;

        cin >> mover;

        while (mover!='n'){
            if (mover == 's'){
                // Mostra os locais possíveis com base nos movimentos e locais adjacentes
                cout << "Escolha um local para mover: ";
                vector<string> opcoesMoveis = adjacencias[jogador.localAtual]; // Verifica as opções adjacentes ao local atual em que é possível se movimentar
               // Limita o número de opções disponíveis com base no valor do dado
                size_t numOpcoes = min(static_cast<size_t>(movimento), opcoesMoveis.size());

                if (numOpcoes > 0) {
                    cout << "Escolha um local para mover (baseado no valor do dado): " << endl;
                    for (size_t i = 0; i < numOpcoes; ++i) {
                        cout << i + 1 << ": " << opcoesMoveis[i] << " ";
                    }
                    cout << endl;

                    int escolha;
                    cin >> escolha;

                if (escolha >= 1 && escolha <= static_cast<int>(numOpcoes)) {
                    jogador.moverPara(opcoesMoveis[escolha - 1]);
                    cout << jogador.nome << " se moveu para " << jogador.localAtual << "." << endl;
                } else {
                    cout << "Local inválido. O jogador permanece no mesmo lugar." << endl;
                }
                } else {
                    cout << "Não há locais disponíveis para mover baseado no valor do dado." << endl;
                }
                    } break;
            cout << "Opção inválida." << endl;
        }
       



       
    }

    bool verificarPalpite(const Palpite& palpite) const { // Método para verificar o paplpite
        if (palpite.getSuspeito() == crime.getAssasino() && palpite.getArma() == crime.getArma() && palpite.getLocal() == crime.getLocal()) {
            cout << "Voce acertou! O crime foi cometido por " << crime.getAssasino() << " com " << crime.getArma() << " no " << crime.getLocal() << "." << endl;
            return false;
        } else {
            cout << "Palpite errado. Continue tentando." << endl;
            return true;
        }
    }

    string cartaBotEnvolvida(const string& suspeito, const string& arma, const string& local) const {
    for (const auto& jogador : jogadores) {
        if (!jogador.anfitriao) { // Verifica apenas bots
            for (const auto& carta : jogador.cartas) {
                if (carta.getNome() == suspeito || carta.getNome() == arma || carta.getNome() == local) {
                    return carta.getNome(); // Retorna a carta envolvida
                }
            }
        }
    }
    return ""; // Retorna vazio se nenhuma carta do bot estiver envolvida
    }


public:
    void distribuirCartas() {
        shuffle(cartas.begin(), cartas.end(), rng);  // Embaralha as cartas antes de distribuir

        size_t jogadorAtual = 0;
        for (const auto& carta : cartas) {
            jogadores[jogadorAtual].receberCarta(carta);
            jogadorAtual = (jogadorAtual + 1) % jogadores.size();  // Distribui as cartas alternadamente entre os jogadores
        }

        // Mostra as cartas do jogador no início do jogo
        jogadores[0].mostrarCartas = true;
        jogadores[0].mostrarCartasJogador();
    }

    Jogo(int numBots) : rng(random_device{}()), localAtual("Entrada"), movimento(0) { // Contrutor da classe jogo
        inicializarAdjacencias(); // inicializa as localizações do tabuleiro
        
        // Inicializa as cartas
        vector<string> suspeitos = {"Thaine", "Diana", "João Pedro", "Eduardo", "Giovanna", "Hugo"};
        vector<string> armas = {"Faca", "Chave de Fenda", "Ferro de Solda", "Livro de Eletrônica", "Transformador", "Soprador Térmico"};
        vector<string> locais = {"Banheiro", "Laboratório", "Biblioteca", "Entrada", "Almox", "Cantina"};

        for (const auto& s : suspeitos) cartas.emplace_back("Suspeito", s);
        for (const auto& a : armas) cartas.emplace_back("Arma", a);
        for (const auto& l : locais) cartas.emplace_back("Local", l);

        // Sorteia o crime criando distribuições uniformes de cada tipo de carta e sorteando uma de cada
        uniform_int_distribution<int> dist_suspeito(0, suspeitos.size() - 1);
        uniform_int_distribution<int> dist_arma(0, armas.size() - 1);
        uniform_int_distribution<int> dist_local(0, locais.size() - 1);

        rng.seed(static_cast<unsigned>(time(0)));

        string suspeito = suspeitos[dist_suspeito(rng)];
        string arma = armas[dist_arma(rng)];
        string local = locais[dist_local(rng)];

        crime = Crime(suspeito, arma, local); 


        // Remove as cartas do crime do baralho geral 
        cartas.erase(remove_if(cartas.begin(), cartas.end(), [&](const Carta& c) {
            return c.getNome() == suspeito || c.getNome() == arma || c.getNome() == local;
        }), cartas.end());

        // Adiciona os jogadores bot e jogador
        jogadores.emplace_back("Jogador", true);
        for (int i = 0; i < numBots; ++i) {
            jogadores.emplace_back("Bot " + to_string(i + 1));
        }

        // Embaralha e distribui as cartas
        shuffle(cartas.begin(), cartas.end(), rng);
        distribuirCartas();
    }

  

    void iniciarJogo() { // Método de início do jogo
        bool jogoAtivo = true;
        char escolha;
        while (jogoAtivo) {
            for (auto& jogador : jogadores) {
                if (jogador.anfitriao) {
                    moverJogador(jogador);

                    cout << "Deseja dar palpite? (aperte 's')" << endl;
                    cin >> escolha;

                    if (escolha == 's'){
                        jogoAtivo = darPalpite(jogador);
                        if (!jogoAtivo) {
                            std::system("cls");
                            cout << "PARABÉNS VOCÊ RESOLVEU!" << endl;
                            system("start image.exe");  
                            break;
                        }}
                    
                } else {
                    // Mostra a carta do bot somente se um palpite é feito com uma carta do bot
                    jogador.mostrarCartas = false;
                    botFazPalpite(jogador);
                }
            }
        }
    }

void botFazPalpite(Jogador& bot) {
    string suspeito, arma, local;

    // Vetores para armazenar as opções disponíveis que o bot NÃO possui
    vector<string> suspeitosDisponiveis, armasDisponiveis, locaisDisponiveis;

    // Adicionar às listas apenas as cartas que o bot não possui
    for (const auto& carta : cartas) {
        if (bot.possuiCarta(carta.getNome())) continue;

        if (carta.getTipo() == "Suspeito") {
            suspeitosDisponiveis.push_back(carta.getNome());
        } else if (carta.getTipo() == "Arma") {
            armasDisponiveis.push_back(carta.getNome());
        } else if (carta.getTipo() == "Local") {
            locaisDisponiveis.push_back(carta.getNome());
        }
    }

    if (!suspeitosDisponiveis.empty()) {
        suspeito = suspeitosDisponiveis[rng() % suspeitosDisponiveis.size()];
    } else {
   
        vector<string> todosSuspeitos = {"Thaine", "Diana", "João Pedro", "Eduardo", "Giovanna", "Hugo"};
        suspeito = todosSuspeitos[rng() % todosSuspeitos.size()];
       
    }

    if (!armasDisponiveis.empty()) {
        arma = armasDisponiveis[rng() % armasDisponiveis.size()];
    } else {
        
        vector<string> todasArmas = {"Faca", "Chave de Fenda", "Ferro de Solda", "Livro de Eletrônica", "Transformador", "Soprador Térmico"};
        arma = todasArmas[rng() % todasArmas.size()];
    }

    if (!locaisDisponiveis.empty()) {
        local = locaisDisponiveis[rng() % locaisDisponiveis.size()];
    } else {
        
        vector<string> todosLocais = {"Banheiro", "Laboratório", "Biblioteca", "Entrada", "Almox", "Cantina"};
        local = todosLocais[rng() % todosLocais.size()];
    }

    // O bot faz o palpite com as cartas escolhidas
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
    local = jogador.localAtual;

    // Verificar se o jogador já possui uma das cartas
    if (jogador.possuiCarta(suspeito) || jogador.possuiCarta(arma) || jogador.possuiCarta(local)) {
        cout << "Você já possui uma dessas cartas. Tente novamente." << endl;
        return true;
    }

    // Verificar se o palpite inclui uma carta dos bots
    string cartaBot = cartaBotEnvolvida(suspeito, arma, local);

    if (!cartaBot.empty()) {
        cout << "Atencao: O seu palpite inclui uma carta que um bot possui. A carta é: " << cartaBot << "." << endl;
    }

    bool resultado = verificarPalpite(Palpite(suspeito, arma, local));

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
