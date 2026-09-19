#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include "structs.h"

/*Loga os dados dos jogadores que vao participar da jogada*/
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

/*Sincroniza as filas dentro da mesa e dentro do jogo em si*/
void sync(tp_fila *jog, mesa *mes){
    tp_fila temp; inicializafila(&temp);
    int cont=0;
    while(filavazia(jog)!=1){
        jogador temp_jog;
        removefila(jog, &temp_jog);
        mes->jogadores[cont]=temp_jog;
        cont++;
        inserefila(&temp, temp_jog);
    }
    while(filavazia(&temp)!=1){
        jogador transf;
        removefila(&temp, &transf);
        inserefila(jog, transf);
    }
}

#endif