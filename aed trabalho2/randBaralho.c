#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"
#include "fila.h"

typedef struct{
    char nome[50];
    int dupla;
    cartas mao[3];
}jogador;

/*Estrutura "mesa" para centralizar informações e facilitar exportação de estatitiscas de rodadas */
typedef struct{
    cartas vira[1];
    jogador jogadores[4];
    int rodada;
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

void inicializarJogadores(tp_fila *f) {
    int totalJogadores = 4;
    for (int i = 1; i <= totalJogadores; i++) {
        inserefila(f, i);
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
printf("A vira da rodada eh a carta: %c%c ", mesa->vira[0].naipe, mesa->vira[0].carta);
}

void distribuirCartas(tp_pilha *baralho, mesa *mesa){
    for (int i = 0; i<4; i++){ 
        for (int c =0; c<3; c++) {
            pop(baralho , &mesa->jogadores[i].mao[c]);
         }
    }
    pop(baralho, &mesa->vira[0]);
}

int main(){
    mesa mesa;  
    entradaDados(&mesa.jogadores);
    tp_fila filaTurnos;
    int jogadorAtual, rodada = 1, jogoRodando = 1, escolha;
    int embaralho=1;
    inicializafila(&filaTurnos);
    inicializarJogadores(&filaTurnos);
    printf("=== INICIO DO JOGO ===\n");
    
    while (jogoRodando==1) { 
        /*Embaralhamento comeca aqui*/
        if(embaralho==1){
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
            cartas manilha;
            top(&baralho, &manilha);
            numero_manilha=manilha.carta;
            for(int i=0;i<40;i++){
                if(&baralho.item[i]==numero_manilha){
                    baralho.item[i].rank+=41;
                }
            }
            /*Manilha termina aqui*/
            distribuirCartas(&baralho, &mesa);
            embaralho=0;
        }
        printf("\n--- RODADA %d ---", rodada);
        printf("\nVez do Jogador %d\n", jogadorAtual);

    }


return 0;
}