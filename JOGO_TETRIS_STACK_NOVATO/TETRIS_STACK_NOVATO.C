#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5


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

int contador_id = 0;

Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contador_id++;
    return nova;
}

void inicializarFila(FilaPecas *f) {
    f->frente = 0;
    f->tras = -1;
    f->total_elementos = 0;
}
// Verifica se a fila está cheia
int filaCheia(FilaPecas *f) {
    return f->total_elementos == TAMANHO_FILA;
}

// Verifica se a fila está vazia
int filaVazia(FilaPecas *f) {
    return f->total_elementos == 0;
}