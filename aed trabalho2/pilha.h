#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>
#define MAX 100

typedef struct{
    char naipe;
    char carta;
    int rank;
}cartas;


typedef struct{
    int topo;
    cartas item[MAX];
}tp_pilha;



void iniPilha(tp_pilha *p){
    p->topo=-1;
}

int pilhaVazia(tp_pilha *p){
    if(p->topo==-1) return 1;
    return 0;
}

int pilhaCheia(tp_pilha *p){
    if(p->topo==MAX-1) return 1;
    return 0;
}

int push(tp_pilha *p, cartas e){
    if(pilhaCheia(p)==1) return 0;
    p->topo++;
    p->item[p->topo] = e;
    return 1;
}

int pop(tp_pilha *p, cartas *e){
    if(pilhaVazia(p)==1) return 0;
    *e = p->item[p->topo];
    p->topo--;
    return 1;
}

int pilhaAltura(tp_pilha *p){
    return p->topo+1;
}

int top(tp_pilha *p, cartas *e){
    if(pilhaVazia(p)==1) return 0;
    *e = p->item[p->topo];
    return 1;
}

void pilhaPrint(tp_pilha p){
    cartas e;
    printf("\n");
    while(!pilhaVazia(&p)){
        pop(&p,&e);
        printf("%c%c ",e.naipe,e.carta);
    }
}


/*
int pilhaIdentica(tp_pilha p, tp_pilha p2){
    if(p.topo!=p2.topo) return 0;
    int e,e2;
    for(int i=0;i<p.topo+1;i++){
        pop(&p,&e);
        pop(&p2,&e2);
        if(e!=e2) return 0;
    }
    return 1;
}


void retiraImpares(tp_pilha *p){
    tp_pilha paux;
    iniPilha(&paux);
    cartas e;
    while(!pilhaVazia(p)){
        pop(p,&e);
        if(e%2==0) push(&paux,e);
    }
    while(!pilhaVazia(&paux)){
        pop(&paux,&e);
        push(p,e);
    }
}
    */

int empilhaPilha(tp_pilha *p, tp_pilha *p2){
    cartas e;
    tp_pilha temp;
    iniPilha(&temp);
    if(pilhaAltura(p)+pilhaAltura(p2)>MAX) return 0;
    while(!pilhaVazia(p2)){
        pop(p2,&e);
        push(&temp,e);
    }
    while(!pilhaVazia(&temp)){
        pop(&temp,&e);
        push(p,e);
    }
}

#endif