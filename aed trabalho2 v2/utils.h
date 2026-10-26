/*Modulo com funcoes uteis que a gente nao sabe onde mais botar*/
#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "listade.h"

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

/*Tira lixo de memoria de cada jogdor novo*/
void limpezaDados(mesa *mes, tp_fila *jogs){
    for (int i = 0; i < 4; i++) {
        mes->jogadores[i].vitorias = 0;
        mes->jogadores[i].pontos = 0;
        mes->jogadores[i].mao = NULL;
        inserefila(jogs, mes->jogadores[i]);
    }
}

/*Sincroniza as filas dentro da mesa e dentro do jogo em si*/
void sync(tp_fila *jog, mesa *mes){
    while(!filavazia(jog)){
        jogador dump;
        removefila(jog, &dump);
    }
    for(int i = 0; i < 4; i++){
        inserefila(jog, mes->jogadores[i]);
    }
}

/*Reorganiza as filas quando ainda nao e hora de embaralhar*/
void reorg(tp_fila *jog1, tp_fila *jog2){
    while(filavazia(&jog2)!=1){
        jogador temp;
        removefila(&jog2, &temp);
        inserefila(&jog1, temp);
    }
}

/*Mostra a manilha atual*/
void imprimeManilha(cartas *manilha, cartas *virada){
    printf("Valor da vira:\n");
    printf("{Naipe: %c,Numero: %c}\n\n", virada->naipe, virada->carta); //O que vai aparecer no jogo de verdade para o jogador
    printf("Valor da manilha:\n");
    printf("{Naipe: %c,Numero: %c}\n\n", manilha->naipe, manilha->carta); //Para acompanhar se o algoritimo fez certo (na entrega final vai ficar omissa que nem no truco real)
}

/*Mostra a mao do jogador*/
void imprime_mao(tp_listase_carta *lista) {
    tp_listase_carta *atu;
    atu = lista;
    while (atu != NULL) {
        printf("%c de %c\n", atu->info.carta, atu->info.naipe);
        atu = atu->prox;
    }
}

/*Mostra os bagulho da rodada*/
void imprimeRodada(char *nome, cartas *man, cartas *vir, tp_listase_carta *mao){
    printf("\nVez de %s\n", nome);
    imprimeManilha(man, vir);
    printf("Sua mao:\n");
    imprime_mao(mao);
    printf("Escolha uma carta seguindo o formato: [Numero][Naipe] (tudo junto)\n");
}

/*Forma simples de encerrar o teste do codigo, cortesia de C Afiados™*/
int teste(){
    int x=0, check=1;
    printf("Terminar teste? (1=sim, 0=nao)\n");
    while (check==1){
        scanf("%d", &x);
        if (x==1){
            printf("Encerrando\n");
            return 0;
        }
        if(x==0){
            return 1;
        }
        else{
            printf("Entrada invalida\n");
        }
    }
}

#endif