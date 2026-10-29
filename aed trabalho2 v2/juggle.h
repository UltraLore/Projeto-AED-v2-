/*Esse modulo guarda funcoes que mechem com cartas em massa (por isso juggle ja que juggle=mecher top 10 piadas)*/
#ifndef JUGGLE_H
#define JUGGLE_H
#include <stdio.h>
#include "pilha.h"
#include "fila.h"
#include "structs.h"
#include "listase.h"

/*Como o nome sugere, distribui as cartas entre os jogadores na mesa*/
void distribuirCartas(tp_pilha *baralho, mesa *mes){
    for(int x=0; x<4; x++){
        mes->jogadores[x].mao=NULL;
        for(int i=0; i<3; i++){
            cartas temp;
            pop(baralho, &temp);
            insere_listase_no_fim(&mes->jogadores[x].mao, temp);
        }
    }
}

/*Efetiva a jogada da carta escolhida pelo jogador, bem similar com a funcao removelistase*/
int jogar_carta(tp_listase_carta **mao, tp_listase_carta **mesa, char naipe, char card){
    tp_listase_carta *atu=*mao, *ant=NULL;
    while(atu!=NULL&&((atu->info.naipe!=naipe)||(atu->info.carta!=card))){
        ant=atu;
        atu=atu->prox;
    }
    if(atu==NULL){
        return 0;
    }
    insere_listase_no_fim(mesa, atu->info);
    if(ant==NULL){
        *mao=atu->prox;
    }
    else{
        ant->prox=atu->prox;
    }
    free(atu);
    atu=NULL;
    return 1;
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
void manilhadora(tp_pilha *baralho, cartas *manilha, cartas *virada){
    int referencia=0;
    pop(baralho, virada);
    referencia=virada->rank; //usando o ranking da pre-manilha da para achar pelo menos uma carta dentro do grupo onde a manilha esta
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
    manilha->naipe='P'; //Paus e o naipe mais forte entao a manilha mais forte vai ter ele como default
}

/*Verifica se o jogador botou algo que deveria ser visivel para ele ou se ele esecreveu qualquer outra coisa que nao seja uma carta sua*/
int validar_jogada(char *jogada, tp_listase_carta *mao){
    char numero, naipe;
    if(strlen(jogada)>2){
        printf("Entrada invalida\n");
        return 0;
    }
    for(int i=0; i<2; i++){
        jogada[i]=toupper(jogada[i]); //garante que seja la se esqueceram ou nao do capslock nao seja um problema
    }
    numero=jogada[0]; naipe=jogada[1];
    tp_listase_carta *atu;
    atu=mao;
    while((atu!=NULL)&&(atu->info.carta!=numero||atu->info.naipe!=naipe)){ //verifica se a entrada pertence ou nao ao jogador
        atu=atu->prox;
    }
    if(atu==NULL) {
        printf("Esta carta nao te pertence, insira uma carta da sua mao\n");
        return 0;
    }
    //"So digo que foi um inferno descobrir que deveria ter formatado a busca do char desse jeito e que não devia utilizar free(atu)" - Felipe, 2026
    int num_val=(numero == 'A' || numero == '2' || numero == '3' || numero == '4' || numero == '5' || numero == '6' || numero == '7' || numero == 'Q' || numero == 'J' || numero == 'K');
    int nai_val=(naipe == 'P' || naipe == 'C' || naipe == 'E' || naipe == 'O');
    if(num_val&&nai_val){
        printf("Jogando %c de %c\n", numero, naipe);
        return 1;
    }
    else{
        printf("Entrada invalida\n");
        return 0;
    }
}

int pesamento(tp_listase_carta *competidas, mesa mes){
    int carta_maior=0, veredito=0, pos=0;
    tp_listase_carta *atu;
    atu=competidas;
    while((atu!=NULL)){
        if(atu->info.rank>carta_maior){
            carta_maior=atu->info.rank;
            veredito=pos; // corrigido de veredito++ para indicar a posição do jogador que venceu
        }
        atu=atu->prox;
        pos++;
    }
    printf("Jogador %s venceu\n", mes.jogadores[veredito].nome);
    return veredito;
}

#endif