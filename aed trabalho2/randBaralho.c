#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"
#include "fila.h"

typedef struct{
    char nome[50];
    int dupla;
    cartas mao[3];
    int vitorias;
    int pontos;
}jogador;

/*Estrutura "mesa" para centralizar informações e facilitar exportação de estatitiscas de rodadas */
typedef struct{
    jogador jogadores[4];
    int rodada;
    int competidas[4];
}mesa;

/*Função para cadastrar as informações dos jogadores e definição de suas respectivas duplas*/
void entradaDados(jogador *jogador){
    int ordemJogadores[4] ={0, 2, 1, 3};
    printf("CADASTRO DA DUPLA 1\n");
    for (int i=0; i<4; i++){
        if (i == 2) printf("\nCADASTRO DA DUPLA 2\n");
        int p = ordemJogadores[i];
        printf("\n Digite o nome do jogador %d : ", i+1);
        scanf(" %[^\n]s", jogador[p].nome);
        if (i < 2) jogador[p].dupla = 1;
        else jogador[p].dupla=2;
    }
}

void imprimeDados (mesa *mesa){
    for (int i =0; i<4; i++){
        printf("\n %d - %s (dupla %d) ", i+1 , mesa->jogadores[i].nome, mesa->jogadores[i].dupla);
        printf("tem as cartas:\n");
        for(int c=0; c<3; c++){
            printf("%c%c \n", mesa->jogadores[i].mao[c].naipe, mesa->jogadores[i].mao[c].carta);
        }
    }
}

void imprimeMao(cartas *mao, char jogador){
    int tamanho=sizeof(mao);
    for(int i=0; i<tamanho-1; i++){
        printf("{Naipe: %c,Numero: %c, Ranking: %d}\n", mao[i].naipe, mao[i].carta, mao[i].rank);
    }
}

void imprimeManilha(cartas *manilha){
    printf("Valor da manilha:\n");
    printf("{Naipe: %c,Numero: %c, Ranking: %d}\n", manilha->naipe, manilha->carta, manilha->rank);
}

void distribuirCartas(tp_pilha *baralho, mesa *mesa){
    for (int i = 0; i<4; i++){ 
        for (int c =0; c<3; c++) {
            pop(baralho , &mesa->jogadores[i].mao[c]);
         }
    }
}

int main(){
    printf("=== INICIO DO JOGO ===\n");
    mesa mesa;
    cartas manilha;
    entradaDados(&mesa.jogadores);
    int contador=0, rodada = 1, jogoRodando = 1;
    int embaralho=1;
    for(int i=0; i<4; i++){
        mesa.jogadores[i].vitorias=0;
    }
    printf("Embaralhando...");
    while (jogoRodando==1) { 
        /*Embaralhamento comeca aqui*/
        if(embaralho==1){
            contador=0; 
            cartas carta[40] = {{'P','3',40},{'C','3',39},{'E','3',38},{'O','3',37},
                                {'P','2',36},{'C','2',35},{'E','2',34},{'O','2',33},
                                {'P','A',32},{'C','A',31},{'E','A',30},{'O','A',29},
                                {'P','K',28},{'C','K',27},{'E','K',26},{'O','K',25},
                                {'P','J',24},{'C','J',23},{'E','J',22},{'O','J',21},
                                {'P','Q',20},{'C','Q',19},{'E','Q',18},{'O','Q',17},
                                {'P','7',16},{'C','7',15},{'E','7',14},{'O','7',13},
                                {'P','6',12},{'C','6',11},{'E','6',10},{'O','6',9},
                                {'P','5',8},{'C','5',7},{'E','5',6},{'O','5',5},
                                {'P','4',4},{'C','4',3},{'E','4',2},{'O','4',1}};
            /* Inicializa uma cópia do vetor cartas (baralho ordenado em força de cada carta)*/  
            cartas cCarta[40];
            for(int i=0;i<40;i++){
                cCarta[i]=carta[i];
            }
            /* Imprime a copia do baralho Original */
            for(int i=0;i<40;i++){
                printf("%c%c ",cCarta[i].naipe,cCarta[i].carta);
            }
            printf("\n");
            /* Essa aqui é a baderna que randomiza o baralho */
            srand(time(NULL));
            int shuffleCount = rand();
            for(int i = 0; i < shuffleCount; i++){
                cartas temp;
                int randPos1 = i % 40;
                int randPos2 = (i * rand()) % 40;
                
                temp = cCarta[randPos1];
                cCarta[randPos1] = cCarta[randPos2];
                cCarta[randPos2] = temp;
            }
            /* Empilha o baralho randomizado (e inverte ele devido às propriedades de pilha) */
            tp_pilha baralho;
            iniPilha(&baralho);
            for(int i=0;i<40;i++){
                cartas what = cCarta[i];
                push(&baralho,what);
            }
            /* Eu não vou explicar isso. (Minha negação a explicar gastou mais caracteres do que explicar.) */
            pilhaPrint(baralho);
            /*Embaralhamento termina aqui*/

            /*Manilha comeca aqui*/
            char numero_manilha;
            pop(&baralho, &manilha);
            numero_manilha=manilha.carta;
            for(int i=0;i<40;i++){
                if(&baralho.item[i]==numero_manilha){
                    baralho.item[i].rank+=41;
                }
            }
            cartas dump;
            /*Manilha termina aqui*/
            distribuirCartas(&baralho, &mesa);
            imprimeDados(&mesa);
            embaralho=0;
        }

        int soma1, soma2, status;
        soma1=mesa.jogadores[0].pontos+mesa.jogadores[1].pontos;
        soma2=mesa.jogadores[2].pontos+mesa.jogadores[3].pontos;
        if(soma1==12){
            printf("Primeira dupla vence o jogo!\n");
            printf("Jogar novamente? (1=sim, 0=nao)\n");
            scanf("%d", &status);
            if(status==0){jogoRodando=0;}
            else{embaralho=1;}
        }
        if(soma2==12){
            printf("Segunda dupla vence o jogo!\n");
            printf("Jogar novamente? (1=sim, 0=nao)\n");
            scanf("%d", &status);
            if(status==0){jogoRodando=0;}
            else{embaralho=1;}
        }

        /*Vez dos jogadores jogarem suas cartas ou declarar truco*/
        rodada=0;
        printf("\n--- RODADA %d ---\n", rodada);
        imprimeManilha(&manilha);
        printf("\nVez de %s\n", mesa.jogadores[rodada].nome);
        while(rodada==0){
            int carta_escolhida;
            imprimeMao(&mesa.jogadores[rodada].mao, &mesa.jogadores[rodada].nome);
            printf("Escolha uma carta de 1 a 3 (cima para baixo) para jogar\n");
            scanf("%d", &carta_escolhida);
            if(carta_escolhida==1){
                mesa.competidas[0]=mesa.jogadores[rodada].mao[0].rank;
                mesa.jogadores[rodada].mao[0].carta="0"; mesa.jogadores[rodada].mao[0].naipe="0"; mesa.jogadores[rodada].mao[0].rank=0;
                rodada=1;
            }
            if(carta_escolhida==2){
                mesa.competidas[0]=mesa.jogadores[rodada].mao[1].rank;
                mesa.jogadores[rodada].mao[1].carta="0"; mesa.jogadores[rodada].mao[1].naipe="0"; mesa.jogadores[rodada].mao[1].rank=0;
                rodada=1;
            }
            if(carta_escolhida==3){
                mesa.competidas[0]=mesa.jogadores[rodada].mao[2].rank;
                mesa.jogadores[rodada].mao[2].carta="0"; mesa.jogadores[rodada].mao[2].naipe="0"; mesa.jogadores[rodada].mao[2].rank=0;
                rodada=1;
            }
        }
        printf("\nVez de %s\n", mesa.jogadores[rodada].nome);
        while(rodada==1){
            int carta_escolhida;
            imprimeManilha(&manilha);
            imprimeMao(&mesa.jogadores[rodada].mao, &mesa.jogadores[rodada].nome);
            printf("Escolha uma carta de 1 a 3 (cima para baixo) para jogar\n");
            scanf("%d", &carta_escolhida);
            if(carta_escolhida==1){
                mesa.competidas[1]=mesa.jogadores[rodada].mao[0].rank;
                mesa.jogadores[rodada].mao[0].carta="0"; mesa.jogadores[rodada].mao[0].naipe="0"; mesa.jogadores[rodada].mao[0].rank=0;
                rodada=2;
            }
            if(carta_escolhida==2){
                mesa.competidas[1]=mesa.jogadores[rodada].mao[1].rank;
                mesa.jogadores[rodada].mao[1].carta="0"; mesa.jogadores[rodada].mao[1].naipe="0"; mesa.jogadores[rodada].mao[1].rank=0;
                rodada=2;
            }
            if(carta_escolhida==3){
                mesa.competidas[1]=mesa.jogadores[rodada].mao[2].rank;
                mesa.jogadores[rodada].mao[2].carta="0"; mesa.jogadores[rodada].mao[2].naipe="0"; mesa.jogadores[rodada].mao[2].rank=0;
                rodada=2;
            }
        }
        printf("\nVez de %s\n", mesa.jogadores[rodada].nome);
        while(rodada==2){
            int carta_escolhida;
            imprimeManilha(&manilha);
            imprimeMao(&mesa.jogadores[rodada].mao, &mesa.jogadores[rodada].nome);
            printf("Escolha uma carta de 1 a 3 (cima para baixo) para jogar\n");
            scanf("%d", &carta_escolhida);
            if(carta_escolhida==1){
                mesa.competidas[2]=mesa.jogadores[rodada].mao[0].rank;
                mesa.jogadores[rodada].mao[0].carta="0"; mesa.jogadores[rodada].mao[0].naipe="0"; mesa.jogadores[rodada].mao[0].rank=0;
                rodada=3;
            }
            if(carta_escolhida==2){
                mesa.competidas[2]=mesa.jogadores[rodada].mao[1].rank;
                mesa.jogadores[rodada].mao[1].carta="0"; mesa.jogadores[rodada].mao[1].naipe="0"; mesa.jogadores[rodada].mao[1].rank=0;
                rodada=3;
            }
            if(carta_escolhida==3){
                mesa.competidas[2]=mesa.jogadores[rodada].mao[2].rank;
                mesa.jogadores[rodada].mao[2].carta="0"; mesa.jogadores[rodada].mao[2].naipe="0"; mesa.jogadores[rodada].mao[2].rank=0;
                rodada=3;
            }
        }
        printf("\nVez de %s\n", mesa.jogadores[rodada].nome);
        while(rodada==3){
            int carta_escolhida;
            imprimeManilha(&manilha);
            imprimeMao(&mesa.jogadores[rodada].mao, &mesa.jogadores[rodada].nome);
            printf("Escolha uma carta de 1 a 3 (cima para baixo) para jogar\n");
            scanf("%d", &carta_escolhida);
            if(carta_escolhida==1){
                mesa.competidas[3]=mesa.jogadores[rodada].mao[0].rank;
                mesa.jogadores[rodada].mao[0].carta="0"; mesa.jogadores[rodada].mao[0].naipe="0"; mesa.jogadores[rodada].mao[0].rank=0;
                rodada=4;
            }
            if(carta_escolhida==2){
                mesa.competidas[3]=mesa.jogadores[rodada].mao[1].rank;
                mesa.jogadores[rodada].mao[1].carta="0"; mesa.jogadores[rodada].mao[1].naipe="0"; mesa.jogadores[rodada].mao[1].rank=0;
                rodada=4;
            }
            if(carta_escolhida==3){
                mesa.competidas[3]=mesa.jogadores[rodada].mao[2].rank;
                mesa.jogadores[rodada].mao[2].carta="0"; mesa.jogadores[rodada].mao[2].naipe="0"; mesa.jogadores[rodada].mao[2].rank=0;
                rodada=4;
            }
        }

        /*Pesamento das cartas jogadas*/
        int carta_maior=0;
        for(int i=0; i<4; i++){
            if(mesa.competidas[i]>mesa.competidas[carta_maior]){carta_maior=i;}
        }
        printf("Jogador %c venceu a rodada!", mesa.jogadores[carta_maior].nome);
        mesa.jogadores[carta_maior].pontos++;
        contador++;
        if(contador==3){
            embaralho=1;
        }
    }
    return 0;
}