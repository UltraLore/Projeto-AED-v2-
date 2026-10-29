/*Piiii! Epa!! eu vi essa carta indo parar debaixo do tapete ai hein! - diria eu, caso fosse um juiz de truco, mas o C Afiados™ trouxe o VAR pra salvar a partida!
Uma lista duplamente encadeada vai guardando toda movimentação do jogo pra ser auditado mediante quaisquer suspeita de fraudes! */
#ifndef VAR_H
#define VAR_H
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "listade.h"

/*Lista duplamente encadeada + indicador de revisao + contador de rodadas registradas*/
typedef struct {
    tp_listad *lista;
    tp_no *atual;            // aponta para o no da rodada em revisao
    int total;
} tp_var;

void var_inicializa(tp_var *v){
    v->lista = inicializa_listad();
    v->atual = NULL;
    v->total = 0;
}

int var_vazio(tp_var *v){
    return listad_vazia(v->lista);
}

/*Grava uma copia do registro no fim da lista*/
int var_insere(tp_var *v, var_registro r){
    if(!insere_listad_no_fim(v->lista, r)) return 0;
    v->total++;
    return 1;
}

/*Função para registrar uma nova rodada no VAR, todas as informações de ação são registradas ao final de cada rodada*/
int var_registrar(tp_var *v, int mao, int rodada, mesa *mes, cartas *manilha, cartas *virada, int vencedor){
    var_registro r;
    int i = 0;
    tp_listase_carta *atu = mes->cartas_mesa;
    r.mao = mao;
    r.rodada = rodada;
    r.vira = *virada;
    r.manilha = *manilha;
    r.vencedor = vencedor;
    while(atu != NULL && i < 4){
        r.jogadas[i] = atu->info;
        atu = atu->prox;
        i++;
    }
    r.n_jogadas = i;
    for(i = 0; i < 4; i++){
        strncpy(r.nomes[i], mes->jogadores[i].nome, 49);
        r.nomes[i][49] = '\0';
        r.duplas[i] = mes->jogadores[i].dupla;
        r.pontos[i] = mes->jogadores[i].pontos;
    }
    return var_insere(v, r);
}

/*Navegacao do VAR: retorna 1 se andou, 0 se chegou na ultima rodada*/
void var_ir_inicio(tp_var *v){ v->atual = v->lista->ini; }
void var_ir_fim(tp_var *v){ v->atual = v->lista->fim; }

int var_proxima(tp_var *v){
    if(v->atual == NULL || v->atual->prox == NULL) return 0;
    v->atual = v->atual->prox;
    return 1;
}

int var_anterior(tp_var *v){
    if(v->atual == NULL || v->atual->ant == NULL) return 0;
    v->atual = v->atual->ant;
    return 1;
}

/*Mostra a rodada onde o cursor esta*/
void var_mostrar(tp_var *v){
    if(v->atual == NULL){
        printf("VAR: nenhuma rodada registrada ainda.\n");
        return;
    }
    var_registro *r = &v->atual->info;
    printf("\n===== VAR | Mao %d - Rodada %d =====\n", r->mao, r->rodada);
    printf("Vira: %c%c | Manilha: %c\n", r->vira.naipe, r->vira.carta, r->manilha.carta);
    for(int i = 0; i < r->n_jogadas; i++){
        printf("  %s (dupla %d): %c de %c%s\n", r->nomes[i], r->duplas[i],
               r->jogadas[i].carta, r->jogadas[i].naipe,
               (i == r->vencedor) ? "  <-- venceu" : "");
    }
    printf("Pontos: ");
    for(int i = 0; i < 4; i++) printf("%s=%d ", r->nomes[i], r->pontos[i]);
    printf("\n====================================\n");
}

/*Menuzinho interativo para controlar o VAR, */
void var_revisar(tp_var *v){
    char op;
    int mao_antes;
    if(var_vazio(v)){
        printf("VAR: ainda nao ha rodadas para revisar.\n");
        return;
    }
    var_ir_fim(v);
    var_mostrar(v);
    do{
        printf("\n[A] anterior  [P] proxima  [I] inicio  [F] fim  [S] sair do VAR: ");
        scanf(" %c", &op);
        mao_antes = v->atual->info.mao;
        switch(op){
            case 'a': case 'A':
                if(!var_anterior(v)) printf("Voce ja esta na primeira rodada.\n");
                else{
                    if(v->atual->info.mao != mao_antes) printf("\n>>> Voltou para a mao %d <<<\n", v->atual->info.mao);
                    var_mostrar(v);
                }
                break;
            case 'p': case 'P':
                if(!var_proxima(v)) printf("Voce ja esta na ultima rodada.\n");
                else{
                    if(v->atual->info.mao != mao_antes) printf("\n>>> Avancou para a mao %d <<<\n", v->atual->info.mao);
                    var_mostrar(v);
                }
                break;
            case 'i': case 'I': var_ir_inicio(v); var_mostrar(v); break; // [VAR] vai pro inicio da lista, cortesia de usar uma lista duplamente encadeada!
            case 'f': case 'F': var_ir_fim(v); var_mostrar(v); break; // [VAR] vai pro fim da lista, cortesia de usar uma lista duplamente encadeada!²
            case 's': case 'S': printf("Saindo do VAR.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while(op != 's' && op != 'S');
}
/*Isso mesmo, nada de vazamento de memória por aqui!!*/
void var_destroi(tp_var *v){ 
    v->lista = destroi_listad(v->lista);
    v->atual = NULL;
    v->total = 0;
}

#endif