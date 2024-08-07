

![PRG22107/Imagens/logo.png](https://github.com/jaojao7/PRG22107/blob/main/Imagens/logo.png)


**Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina Departamento Acadêmico de Eletrônica**

**Graduação em Engenharia Eletrônica**

Diana Macedo Rodrigues, Giovanna Liz Souza, João Pedro de Araújo Duarte

**Análise e Projeto Orientado à Objetos**

**Caso de Uso: Jogar Detetive**

# **Objetivo**

Este caso de uso descreve um jogo de cartas onde tem um caso de assassinato e o objetivo é descobrir o ator do crime, a arma utilizada, e em qual localização ocorreu. 

 # **Requisitos**

 Jogar o jogo detetive.

 # **Atores**

De dois até quatro jogadores.

 # **Prioridade**

ALTA

 # **Pré-condições**

O jogo ao ser inicializado terá um conjunto de cartas que serão separadas em 3 grupos (suspeitos, armas e locais) uma carta de cada grupo será ocultada dos jogadores representando o crime da rodada, o restante será dividido igualmente entre a quantidade de participantes de forma aleatória. Uma carta é revelada a todos como dica comum no início do jogo. 


 # **Frequência de uso**

Não se aplica

 # **Criticalidade**

ALTA

 # **Condição de Entrada**

O jogador anfitrião solicita o início de uma nova  rodada do jogo.

 # **Fluxo Principal**

1. Cria uma conexão na rede para acesso dos jogadores;
2. Conexão estabelecida e jogadores conectados;
1. Sorteia o crime;
1. O sistema “mistura” e distribui as cartas igualmente;
1. Cada jogador verifica suas cartas;
1. O primeiro jogador é escolhido de forma aleatória pelo sistema;
1. Sorteia a localização do jogador;
   1) Localização válida é permitido o palpite;
   1) Localização inválida não é permitido palpite;
1. O jogador informa um palpite para o crime;
1. O sistema verifica se a algum dos outros jogadores possui uma carta do palpite;
   1) Caso alguém possua a carta, o sistema a revela para quem palpitou;
   1) Caso nenhuma carta do palpite esteja presente durante a partida e não estejam com o jogador que deu o palpite, é mostrado a quem palpitou “não há palpites presentes”;
1. O jogador assinala a carta que foi mostrada;
1. Cada jogador poderá dar somente um palpite acusação, considerado o palpite final daquele jogador;
    1. Se acertar o palpite acusação o usuário vence e a partida é finalizada;
    1. Se errar o palpite acusação o usuário é eliminado e suas cartas são reveladas para todos os jogadores que continuam na partida.
    1. O fluxo retorna ao jogo e passa o palpite para o próximo jogador;
    1. O sistema mostra quando o jogador acerta as três cartas no palpite;
    1. A rodada é encerrada informando o resultado aos jogadores;

 # **Fluxo Alternativo**

Não há

 # **Pós-condições**

Não há. O jogo é encerrado e as vitórias não são computadas.

 # **Regras de negócio**

1. Cada jogador possui a chance de um palpite por rodada;
1. É possível dar um palpite quando o jogador tem uma ou duas das cartas do palpite na mão.
1. Cada jogador poderá dar somente UM palpite acusação no jogo todo.

# **Diagrama**


![PRG22107/Imagens/Detetive.png](https://github.com/jaojao7/PRG22107/blob/main/Imagens/Detetive.png)
