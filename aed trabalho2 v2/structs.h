/*Esse modulo guarda todas as structs utilizadas no jogo*/
#ifndef STRUCTS_H
#define STRUCTS_H

/*Estrtura "cartas" que guarda o naipe, o numero (escrito como carta [culpe nathan]) e o rank de poder dela*/
typedef struct cartas {
    char naipe;
    char carta;
    int rank;
} cartas;

typedef struct tp_listase_carta{ //tanto tp_no quanto tp_listase_carta e usado
    cartas info;
    struct tp_listase_carta *prox;    
} tp_listase_carta;

/*Estrutura "jogador" que guarada o nome, a dupla no qual ele esta associado, um vetor tipo cartas para representar a mao que tem,
quantas vitorias o jogador possui pelo bar e os pontos dele dentro de uma sessão de jogo*/
/*vitorias nao esta sendo usada agora para a primeira entrega mas decidi deixar logo ai pra dar menos dor de cabeca depois*/
typedef struct jogador {
    char nome[50];
    int dupla;
    tp_listase_carta *mao;
    int vitorias;
    int pontos;
} jogador;

/*Estrutura "mesa" para centralizar informações e facilitar exportação de estatitiscas de rodadas */
typedef struct mesa {
    jogador jogadores[4];
    int rodada;
    tp_listase_carta *cartas_mesa;
} mesa;

/* Struct para tirar uma "foto" da partida atual!*/
typedef struct var_registro {
    int mao;                 // numero da mao (contagem de embaralhamentos)
    int rodada;              // numero da rodada dentro da mao (1 a 3)
    cartas vira, manilha;
    int n_jogadas;           // quantas cartas foram jogadas
    char nomes[4][50];       // nomes na ordem em que jogaram
    int duplas[4];
    cartas jogadas[4];       // identificação de quais cartas foram jogadas e por quem foram
    int vencedor;            // flag de vencedor da rodada
    int pontos[4];           // pontuação dos jogadores após a rodada
} var_registro;

#endif