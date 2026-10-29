/*Modulo da main, reune todas a funcoes*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pilha.h"
#include "fila.h"
#include "structs.h"
#include "juggle.h"
#include "utils.h"
#include "var.h"

int main(){
    tp_fila jogadores1, jogadores2;
    inicializafila(&jogadores1); inicializafila(&jogadores2);
    tp_var var; var_inicializa(&var);        // Inicializa o VAR

    printf("=== INICIO DO JOGO ===\n");

    mesa mesa; mesa.cartas_mesa=NULL;
    cartas manilha, virada;
    

    entradaDados(&mesa.jogadores);
    limpezaDados(&mesa, &jogadores1);

    int contador=1, rodada = 1, jogoRodando = 1, embaralho=1, maoNum = 0;

    

    while (jogoRodando==1) { 
        if(embaralho==0){
            reorg(&jogadores1, &jogadores2);
        }
        /*Embaralhamento comeca aqui*/
        if(embaralho==1){
            reorg(&jogadores1, &jogadores2); //Não me lembro por que raios ela tem que aparecer aqui mas sei que caso nao o algoritimo explode sem sobreviventes //Ponteiro de ponteiro jovem padawan.
            contador=1;
            maoNum++; // [VAR] contagem
            tp_pilha baralho;
            iniPilha(&baralho);
            embaralhador(&baralho); //AVISO: professor, se seu terminal for baixo lembre de dar um scroll pra cima para ver o baralho pre e pos uso do embaralhador
            manilhadora(&baralho, &manilha, &virada);
            for (int i = 0; i < 4; i++) {
                destroi_listase(&mesa.jogadores[i].mao);
            }
            distribuirCartas(&baralho, &mesa);
            sync(&jogadores1, &mesa);
            embaralho=0;
        }

        /*Aqui comeca a parte das rodadas ESPECIFICAMENTE usando filas*/
        rodada=0;
        printf("\n--- RODADA %d ---\n", contador);
        while(filavazia(&jogadores1)!=1){
            int check=1;
            jogador temp;
            removefila(&jogadores1, &temp);
            imprimeRodada(temp.nome, &manilha, &virada, temp.mao);
            while(check==1){
                char carta_escolhida[10];
                scanf("%s", &carta_escolhida);
                if(validar_jogada(carta_escolhida, temp.mao)==1){
                    char numero=carta_escolhida[0], naipe=carta_escolhida[1];
                    jogar_carta(&temp.mao, &mesa.cartas_mesa, naipe, numero);
                    check=0;
                }
            }
            int pts=mesa.jogadores[rodada].pontos;
            mesa.jogadores[rodada]=temp;
            mesa.jogadores[rodada].pontos=pts;
            inserefila(&jogadores2, temp);
            rodada++;
        }
        contador++; //acompanha quantas vezes a mesa rodou

        /*Pesamento das cartas jogadas*/
        int vitorioso=0;
        vitorioso=pesamento(mesa.cartas_mesa, mesa);
        mesa.jogadores[vitorioso].pontos++; 

        var_registrar(&var, maoNum, contador-1, &mesa, &manilha, &virada, vitorioso);   //Chamada do registro do VAR, salvando a rodada atual
        destroi_listase(&mesa.cartas_mesa);      // liberando memória para não criar listas infinitas

        printf("Chamar o VAR? (1=sim, 0=nao): ");
        int op; scanf("%d", &op);
        if(op==1) var_revisar(&var); // Aqui a brincadeira fica interessante, função para chamar o VAR! Por enquanto está aqui para testes.

        /*Checa se necessita embaralhar denovo + averiguacao de encerrar teste*/
        if(contador>3){
            if(teste()==0){
                jogoRodando=0;
            }
            embaralho=1;
        }
    }
    var_destroi(&var); // Encerra o var e libera a memória
    return 0;
}