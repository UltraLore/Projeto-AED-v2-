#ifndef LISTASE_H
#define LISTASE_H
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

tp_listase_carta * inicializa_listase(){ //Na main fica lista=inicializa_listase()"
    return NULL;
}

int listase_vazia(tp_listase_carta *lista){ //Na main vc cria "tp_listase_carta *lista" entao ele verifica se o ponteiro do tipo é NULL (o ponteiro nao e um struct por si so, ele so aponta para esse tipo de variavel)
    if(lista==NULL) return 1;
    return 0;
}

tp_listase_carta*aloca_listase(){
    tp_listase_carta *novo_no;
    novo_no=(tp_listase_carta*) malloc(sizeof(tp_listase_carta));
    return novo_no;
}

int insere_listase_no_fim(tp_listase_carta **lista, cartas e){
    tp_listase_carta *novo_no, *atu;
    novo_no=aloca_listase();
    if(novo_no==NULL) return 0;
    novo_no->info=e;
    novo_no->prox=NULL;
    if(listase_vazia(*lista)){
        *lista=novo_no;
    }
    else{
        atu=*lista;
        while(atu->prox!=NULL){
            atu=atu->prox;
        }
        atu->prox=novo_no;
    }
    return 1;
}

int remove_listase(tp_listase_carta **lista, char nai, char car){
    tp_listase_carta *ant, *atu;
    atu=*lista;
    ant=NULL;
    while((atu!=NULL)&&(atu->info.naipe!=nai||atu->info.carta!=car)){
        ant=atu;
        atu=atu->prox;
    }
    if(atu==NULL) {return 0;}
    if(ant==NULL){
        *lista=atu->prox;
    }
    else{
        ant->prox=atu->prox;
    }
    free(atu);
    atu=NULL;
    return 1;
}

void destroi_listase(tp_listase_carta **lista){
    tp_listase_carta *atu;
    atu=*lista;
    while(atu!=NULL){
        *lista=atu->prox;
        free(atu);
        atu=*lista;
    }
    *lista=NULL;
}

#endif