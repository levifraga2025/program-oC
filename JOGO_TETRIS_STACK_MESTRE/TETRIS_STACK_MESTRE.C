#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca itens[TAMANHO_FILA];
    int frente;
    int tras;
    int total_elementos;
} FilaPecas;

typedef struct {
    Peca itens[TAMANHO_PILHA];
    int topo;
} PilhaReserva;

// --- FUNÇÕES DE APOIO ---

void inicializarFila(FilaPecas *f) {
    f->frente = 0;
    f->tras = -1;
    f->total_elementos = 0;
}

void inicializarPilha(PilhaReserva *p) {
    p->topo = -1;
}

void gerarPecaAleatoria(Peca *p) {
    p->nome = 'A' + (rand() % 26);
    p->id = rand() % 100; // Aumentei o range para melhor visualização
}

void inserirFila(FilaPecas *f) {
    if (f->total_elementos < TAMANHO_FILA) {
        f->tras = (f->tras + 1) % TAMANHO_FILA;
        gerarPecaAleatoria(&f->itens[f->tras]);
        f->total_elementos++;
    }
}