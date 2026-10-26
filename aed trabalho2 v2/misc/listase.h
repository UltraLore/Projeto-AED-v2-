#ifndef LISTASE_H
#define LISTASE_H
#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

typedef struct tp_listase{ //tanto tp_no quanto tp_listase e usado
    tp_item info;
    struct tp_listase *prox;    
} tp_listase;

tp_listase * inicializa_listase(){ //Na main fica lista=inicializa_listase()"
    return NULL;
}

int listase_vazia(tp_listase *lista){ //Na main vc cria "tp_listase *lista" entao ele verifica se o ponteiro do tipo é NULL (o ponteiro nao e um struct por si so, ele so aponta para esse tipo de variavel)
    if(lista==NULL) return 1;
    return 0;
}

tp_listase*aloca_listase(){
    tp_listase *novo_no;
    novo_no=(tp_listase*) malloc(sizeof(tp_listase));
    return novo_no;
}

int insere_listase_no_fim(tp_listase **lista, tp_item e){
    tp_listase *novo_no, *atu;
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

int insere_listase_no_inicio(tp_listase **lista, tp_item e){
    tp_listase *novo_no, *ant;
    novo_no=aloca_listase();
    if(novo_no==NULL) return 0;
    novo_no->info=e;
    if(listase_vazia(*lista)){
        *lista=novo_no;
        novo_no->prox=NULL;
    }
    else{
        ant=*lista;
        *lista=novo_no;
        novo_no->prox=ant;
    }
    return 1;
}

int insere_listase_ordenado(tp_listase **lista, tp_item e){
    tp_listase *novo_no, *ant, *atu;
    novo_no=aloca_listase();
    novo_no->info=e;
    atu=*lista;
    ant=NULL;
    while((atu!=NULL)&&(atu->info < novo_no->info)){
        ant=atu;
        atu=atu->prox;
    }
    if(ant==NULL){
        *lista=novo_no;
    }
    else{
        ant->prox=novo_no;
    }
    novo_no->prox=atu;
    return 1;
}

void imprime_listase(tp_listase *lista){
    tp_listase *atu;
    atu=lista;
    while(atu!=NULL){
        printf("%d\n", atu->info);
        atu=atu->prox;
    }
}

int remove_listase(tp_listase **lista, tp_item e){
    tp_listase *ant, *atu;
    atu=*lista;
    ant=NULL;
    while((atu!=NULL)&&(atu->info!=e)){
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

tp_listase *busca_listase(tp_listase *lista, tp_item e){
    tp_listase *atu;
    atu=lista;
    while((atu!=NULL)&&(atu->info!=e)){
        atu=atu->prox;
    }
    return atu;
}

int tamanho_listase(tp_listase *lista){
    int cont=0;
    tp_listase *atu;
    atu=lista;
    while(atu!=NULL){
        cont++;
        atu=atu->prox;
    }
    return cont;
}

void destroi_listase(tp_listase **lista){
    tp_listase *atu;
    atu=*lista;
    while(atu!=NULL){
        *lista=atu->prox;
        free(atu);
        atu=*lista;
    }
    *lista=NULL;
}

int listase_igual(tp_listase *lista1, tp_listase *lista2){
    tp_listase *atu1, *atu2;
    atu1=lista1;
    atu2=lista2;
    if(tamanho_listase(atu1)!=tamanho_listase(atu2)) return 0;
    while(atu1!=NULL){
        if(atu1->info!=atu2->info){
            return 0;
        }
        atu1=atu1->prox;
        atu2=atu2->prox;
    }
    return 1;
}

void concatena_listas(tp_listase *L1, tp_listase **L2){
    tp_listase *atu1, *atu2;
    atu1=L1;
    atu2=*L2;
    while(atu1->prox!=NULL){
        atu1=atu1->prox;
    }
    while(atu2->prox!=NULL){
        atu2=atu2->prox;
    }
    atu1->prox=*L2;
    atu2->prox=L1;
    *L2=L1;
}

int desloc(tp_listase **lista, tp_item e, int delta){
    tp_listase *atu, *atu2, *ant;
    atu=*lista;
    ant=NULL;
    atu2=NULL;
    while(atu->info!=e && atu->prox!=NULL){
        ant=atu;
        atu=atu->prox;
    }
    if(atu->prox==NULL){return 0;}
    ant->prox=atu->prox;
    atu2=atu;
    while(delta!=0 && atu2->prox!=NULL){
        ant=atu2;
        atu2=atu2->prox;
        delta--;
    }
    atu->prox=atu2->prox;
    atu2->prox=atu;
    ant->prox=atu2;
    return 1;
}

#endif