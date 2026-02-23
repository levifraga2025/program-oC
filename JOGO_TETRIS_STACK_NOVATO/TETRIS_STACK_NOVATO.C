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
// Insere uma nova peça no final da fila (Enqueue)
void inserirPeca(FilaPecas *f) {
    if (filaCheia(f)) {
        printf("\n[AVISO] A fila esta cheia! Nao e possivel adicionar novas pecas.\n");
        return;
    }
    // Lógica circular: o próximo índice volta ao zero se atingir o limite
    f->tras = (f->tras + 1) % TAMANHO_FILA;
    f->itens[f->tras] = gerarPeca();
    f->total_elementos++;
}

// Remove a peça da frente da fila para "jogar" (Dequeue)
void jogarPeca(FilaPecas *f) {
    if (filaVazia(f)) {
        printf("\n[AVISO] Nao ha pecas na fila para jogar!\n");
        return;
    }
    Peca removida = f->itens[f->frente];
    printf("\n>>> Voce jogou a peca [%c %d]!\n", removida.nome, removida.id);