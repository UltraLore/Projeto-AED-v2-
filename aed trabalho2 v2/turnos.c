#include <stdio.h>
#include "fila.h"

void inicializarJogadores(tp_fila *f) {
    int totalJogadores = 4;
    for (int i = 1; i <= totalJogadores; i++) {
        inserefila(f, i);
    }
}
int main() {
    tp_fila filaTurnos;
    int jogadorAtual;
    int rodada = 1;
    int jogoRodando = 1;
    int escolha;
    incializarfila(&filaTurnos);
    inicializarJogadores(&filaTurnos);
    
    printf("=== INICIO DO JOGO ===\n");
    
    while (jogoRodando==1) { 
        removefila(&filaTurnos, &jogadorAtual);

        printf("\n--- RODADA %d ---", rodada);
        printf("\nVez do Jogador %d\n", jogadorAtual);
        printf("1 - Fazer jogada\n");
        printf("0 - Terminar jogo \n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 0) {
            printf("\nO Jogador %d ganhou!\n", jogadorAtual);
            jogoRodando = 0;
        } else {
            inserefila(&filaTurnos, jogadorAtual);
            rodada++;
        }
    }

    printf("\n=== FIM DE JOGO ===\n");
    return 0;
}

if(carta_escolhida==1){
                mesa.competidas[0]=mesa.jogadores[rodada].mao[0].rank;
                mesa.jogadores[rodada].mao[0].carta="0"; mesa.jogadores[rodada].mao[0].naipe="0"; mesa.jogadores[rodada].mao[0].rank=0;
                rodada=1;
            }
            if(carta_escolhida==2){
                mesa.competidas[0]=mesa.jogadores[rodada].mao[1].rank;
                mesa.jogadores[rodada].mao[1].carta="0"; mesa.jogadores[rodada].mao[1].naipe="0"; mesa.jogadores[rodada].mao[1].rank=0;
                rodada=1;
            }
            if(carta_escolhida==3){
                mesa.competidas[0]=mesa.jogadores[rodada].mao[2].rank;
                mesa.jogadores[rodada].mao[2].carta="0"; mesa.jogadores[rodada].mao[2].naipe="0"; mesa.jogadores[rodada].mao[2].rank=0;
                rodada=1;
            }