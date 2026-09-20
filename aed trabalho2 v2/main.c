/*Modulo da main, reune todas a funcoes*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"
#include "fila.h"
#include "structs.h"
#include "juggle.h"
#include "utils.h"

int main(){
    tp_fila jogadores1, jogadores2;
    inicializafila(&jogadores1); inicializafila(&jogadores2);
    printf("=== INICIO DO JOGO ===\n");
    mesa mesa;
    cartas manilha, virada;
    entradaDados(&mesa.jogadores);
    int contador=1, rodada = 1, jogoRodando = 1;
    int embaralho=1;
    for(int i=0; i<4; i++){
        mesa.jogadores[i].vitorias=0;
        inserefila(&jogadores1, mesa.jogadores[i]);
    }
    while (jogoRodando==1) { 
        if(embaralho==0){ //Reorganiza as filas quando ainda nao e hora de embaralhar
            while(filavazia(&jogadores2)!=1){
                jogador temp;
                removefila(&jogadores2, &temp);
                inserefila(&jogadores1, temp);
            }
        }
        /*Embaralhamento comeca aqui*/
        if(embaralho==1){
            while(filavazia(&jogadores2) != 1){
                jogador temp;
                removefila(&jogadores2, &temp);
                inserefila(&jogadores1, temp);
            }
            contador=1;
            tp_pilha baralho;
            iniPilha(&baralho);
            embaralhador(&baralho); //AVISO: professor, se seu terminal for baixo lembre de dar um scroll pra cima para ver o baralho pre e pos uso do embaralhador
            manilhadora(&baralho, &manilha, &virada);
            distribuirCartas(&baralho, &jogadores1);
            sync(&jogadores1, &mesa);
            embaralho=0;
        }

        /*Eu (felipe) adicionaria um sistema que identifica os pontos aqui mas isso e da segunda entrega e considerando os assuntos por vir + o fato que vai ser obrigatorio adicionar mais modelo de data vou deixar isso pro futuro*/
        // ^^ A dor de cabeca que foi adaptar o sistema de rodadas ja me traumatizou o suficiente para nao avancar muito alem do que a entrega demanda

        /*Aqui comeca a parte das rodadas ESPECIFICAMENTE usando filas*/
        rodada=0;
        printf("\n--- RODADA %d ---\n", contador);
        while(filavazia(&jogadores1)!=1){
            int carta_escolhida, check=1;
            jogador temp;
            removefila(&jogadores1, &temp);
            printf("\nVez de %s\n", mesa.jogadores[rodada].nome);
            imprimeManilha(&manilha, &virada);
            imprimeMao(&temp.mao);
            printf("Escolha uma carta de 1 a 3 (cima para baixo) para jogar\n");
            while(check==1){
                scanf("%d", &carta_escolhida);
                if(carta_escolhida<4){check=0;}
                else{printf("Escolha invalida, insira um numero de 1 a 3 para fazer sua escolha\n");}
            }
            jogada(&mesa, &temp, carta_escolhida, rodada);
            mesa.jogadores[rodada]=temp;
            inserefila(&jogadores2, temp);
            rodada++;
        }
        contador++; //acompanha quantas vezes a mesa rodou

        /*Pesamento das cartas jogadas*/
        int carta_maior=0;
        for(int i=0; i<4; i++){
            if(mesa.competidas[i]>mesa.competidas[carta_maior]){carta_maior=i;}
        }
        printf("Jogador %s venceu a rodada!\n", mesa.jogadores[carta_maior].nome);
        jogadores1.item[carta_maior].pontos++;

        /*Checa se necessita embaralhar denovo + averiguacao de encerrar teste*/
        if(contador>3){
            int teste=0;
            printf("Terminar teste? (1=sim, 0=nao)\n"); //Forma simples de encerrar o teste do codigo, cortesia de C Afiados™
            scanf("%d", &teste);
            if(teste==1){
                jogoRodando=0;
            }
            embaralho=1;
        }
    }
    return 0;
}