/*Esse modulo guarda funcoes que mechem com cartas em massa (por isso juggle ja que juggle=mecher top 10 piadas)*/
#ifndef JUGGLE_H
#define JUGGLE_H
#include <stdio.h>
#include "pilha.h"
#include "fila.h"
#include "structs.h"

/*Como o nome sugere, distribui as cartas entre os jogadores na mesa*/
void distribuirCartas(tp_pilha *baralho, tp_fila *jogs){
    tp_fila tempfila; inicializafila(&tempfila);
    while(filavazia(jogs)!=1){
        jogador tempjog;
        cartas tempcarta;
        removefila(jogs, &tempjog);
        for(int i=0; i<3; i++){
            pop(baralho, &tempcarta);
            tempjog.mao[i]=tempcarta;
        }
        inserefila(&tempfila, tempjog);
    }
    while(filavazia(&tempfila)!=1){
        jogador tempjog2;
        removefila(&tempfila, &tempjog2);
        inserefila(jogs, tempjog2);
    }
}

/*Basicamente eh a funcao que meche na mao do jogador quando ele decide jogar uma carta*/
/*No momento ele so "zera" a carta jogada, mas como isso e coisa da segunda entrega vou deixar assim para a primeira como placeholder*/
void jogada(mesa *mes, jogador *jog, int carta_escolhida, int rodada){
    if(carta_escolhida==1){
        mes->competidas[rodada]=jog->mao[0].rank;
        jog->mao[0].carta='0'; jog->mao[0].naipe='0'; jog->mao[0].rank=0;
    }
    if(carta_escolhida==2){
        mes->competidas[rodada]=jog->mao[1].rank;
        jog->mao[1].carta='0'; jog->mao[1].naipe='0'; jog->mao[1].rank=0;
    }
    if(carta_escolhida==3){
        mes->competidas[rodada]=jog->mao[2].rank;
        jog->mao[2].carta='0'; jog->mao[2].naipe='0'; jog->mao[2].rank=0;
    }
}

/*Mostra a mao do jogador atual*/
void imprimeMao(cartas *mao){
    for(int i=0; i<3; i++){
        printf("{Naipe: %c,Numero: %c, Ranking: %d}\n", mao[i].naipe, mao[i].carta, mao[i].rank);
    }
}

/*Embaralha as cartas*/
void embaralhador(tp_pilha *baralho){
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
    for(int i=0;i<40;i++){
        cartas what = cCarta[i];
        push(baralho,what);
    }
    /*Printa a bagaca do baralho*/
    pilhaPrint(*baralho);
}

/*funcao para definir a manilha do jogo*/
void manilhadora(tp_pilha *baralho, cartas *manilha){
    cartas pre_manilha; //essa sessao ate a linha 102 e basicamente o processo de triangular o numero da manilha
    int referencia=0;
    pop(baralho, &pre_manilha);
    referencia=pre_manilha.rank; //usando o ranking da pre-manilha da para achar pelo menos uma carta dentro do grupo onde a manilha esta
    referencia=referencia+4;
    for(int i=0; i<39; i++){
        if(referencia==baralho->item[i].rank){
            *manilha=baralho->item[i]; //nossa carta de referencia (manilha) e igualada a uma parte do grupo
            break;
        }
    }
    for(int i=0; i<39; i++){
        if(manilha->carta==baralho->item[i].carta){ //pega todas as cartas com o mesmo numero e soma o ranking delas em 41 (garantidamente vai estar acima do resto)
            baralho->item[i].rank=baralho->item[i].rank+41; 
        }
    }
}

/*Mostra a manilha atual (nem sei onde raios botaria nos modulos entao vai ficar aqui mesmo)*/
void imprimeManilha(cartas *manilha){
    printf("Valor da manilha:\n");
    printf("{Naipe: %c,Numero: %c}\n\n", manilha->naipe, manilha->carta);
}

#endif