#ifndef fila_h
#define fila_h
#include <stdio.h>
#include "structs.h"
#define MAX 100

typedef struct {
    jogador item[MAX];
    int ini, fim;
    //int tam;
}tp_fila;

void inicializafila(tp_fila *f){
    f->ini=f->fim=MAX-1; //ambos apontam para a ultima posicao da fila
    //f->tam=0
}

int filavazia(tp_fila *f){
    if(f->ini==f->fim) return 1;
    return 0;
}
int proximo(int pos){
    if(pos==MAX-1) return 0;
    return ++pos;
}
int filacheia(tp_fila *f){
    if(proximo(f->fim)==f->ini) return 1;
    return 0;
}

int inserefila(tp_fila *f, jogador e){
    if(filacheia(f)) return 0; //fila cheia
    f->fim=proximo(f->fim);
    f->item[f->fim]=e;
    //f->tam++;
    return 1;
}

int removefila(tp_fila *f, jogador *e){
    if(filavazia(f)) return 0; //fila vazia
    f->ini=proximo(f->ini);
    *e=f->item[f->ini];
    //f->tam--;
    return 1;
}

void imprimefila(tp_fila f){
    jogador e;
    while(!filavazia(&f)){
        removefila(&f, &e);
        printf("%d\n", e);
    }
}

int tamanhofila(tp_fila *f){
    if(filavazia(f)) return 0;
    if(f->ini < f->fim) return f->fim-f->ini;
    return MAX-1-f->ini+f->fim+1;
}
#endif