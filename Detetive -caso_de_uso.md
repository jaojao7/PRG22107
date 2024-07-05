

![PRG22107/Imagens/logo.png](https://github.com/jaojao7/PRG22107/blob/main/Imagens/logo.png)


**Instituto Federal de Educação, Ciência e Tecnologia de Santa Catarina Departamento Acadêmico de Eletrônica**

**Graduação em Engenharia Eletrônica**

Diana Macedo Rodrigues, Giovanna Liz Souza, João Pedro de Araújo Duarte

**Análise e Projeto Orientado à Objetos**

1. **Caso de Uso: Jogar Detetive**
    # **Objetivo**

**Info:** Contém uma breve descrição do objetivo do caso de uso.

Este caso de uso descreve um jogo de cartas onde tem um caso de assassinato e o objetivo é descobrir o ator do crime, a arma utilizada, e em qual localização ocorreu. 

 # **Requisitos**

**Info:** Neste campo indicamos a qual requisito funcional o caso de uso em questão está associado.

 Jogar o jogo detetive.

 # **Atores**

**Info:** Neste campo definimos a lista de atores associados ao caso de uso. Ator é qualquer entidade externa que interage com o sistema (neste caso, com o caso de uso em questão).

De dois até quatro jogadores.

 # **Prioridade**

**Info:** Informação identificada junto ao usuário que auxilia na definição dos casos de uso que serão contemplados em cada iteração do desenvolvimento do software.

ALTA

 # **Pré-condições**

**Info:** Neste campo devemos informar as condições que devem ser atendidas para que o caso de uso possa ser executado.

O jogo ao ser inicializado terá um conjunto de cartas que serão separadas em 3 grupos (suspeitos, armas e locais) uma carta de cada grupo será ocultada dos jogadores representando o crime da rodada, o restante será dividido igualmente entre a quantidade de participantes de forma aleatória. Uma carta é revelada a todos como dica comum no início do jogo. 


 # **Frequência de uso**

**Info:** Informação identificada junto ao usuário que auxilia na definição dos casos de uso que serão contemplados em cada iteração do desenvolvimento do software.

Não se aplica

 # **Criticalidade**

**Info:** Informação identificada junto ao usuário que auxilia na definição dos casos de uso que serão contemplados em cada iteração do desenvolvimento do software.

ALTA

 # **Condição de Entrada**

**Info:** Neste campo definimos qual ação do ator dará início à interação com o caso de uso em questão. O jogador anfitrião solicita o início de uma nova  rodada do jogo.
 # **Fluxo Principal!**

**Info:** Esta é uma das seções principais do caso de uso. É onde descrevemos os passos entre o ator e o sistema. O fluxo principal é o cenário que mais acontece no caso de uso e/ou o mais importante.

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
1) Se acertar o palpite acusação o usuário vence e a partida é finalizada;
1) Se errar o palpite acusação o usuário é eliminado e suas cartas são reveladas para todos os jogadores que continuam na partida.
   1. O fluxo retorna ao jogo e passa o palpite para o próximo jogador;
   1. O sistema mostra quando o jogador acerta as três cartas no palpite;
   1. A rodada é encerrada informando o resultado aos jogadores;

 # **Fluxo Alternativo**

**Info:** Fluxo alternativo é o caminho alternativo tomado pelo caso de uso a partir do fluxo principal, ou seja, dada uma condição de negócio o caso de uso seguirá por outro cenário que não o principal caso essa condição seja verdadeira.

Não há

 # **Pós-condições**

**Info:** Neste campo devemos informar o estado em que o sistema (ou entidade manipulada no caso de uso) estará depois que o caso de uso for executado.

Não há. O jogo é encerrado e as vitórias não são computadas.

 # **Regras de negócio**

**Info:** Nesta seção descrevemos todas as regras funcionais que o caso de uso deve cumprir durante sua execução.

1. Cada jogador possui a chance de um palpite por rodada;
1. É possível dar um palpite quando o jogador tem uma ou duas das cartas do palpite na mão.
1. Cada jogador poderá dar somente UM palpite acusação no jogo todo.
