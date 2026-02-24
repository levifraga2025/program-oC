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

// --- LOGICA DO JOGO ---

void jogarPeca(FilaPecas *f) {
    if (f->total_elementos == 0) {
        printf("\nErro: Fila vazia!\n");
        return;
    }
    Peca p = f->itens[f->frente];
    printf("\n[JOGADA] Voce usou a peca da fila: [%c %d]\n", p.nome, p.id);
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->total_elementos--;
    inserirFila(f);
}

void reservarPeca(FilaPecas *f, PilhaReserva *p) {
    if (p->topo == TAMANHO_PILHA - 1) {
        printf("\nErro: Reserva cheia!\n");
        return;
    }
    Peca pecaReservada = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->total_elementos--;
    
    p->topo++;
    p->itens[p->topo] = pecaReservada;
    printf("\n[RESERVA] [%c %d] movida para a reserva.\n", pecaReservada.nome, pecaReservada.id);
    inserirFila(f);
}

//Troca Direta: Troca a peça da frente da fila com o topo da pilha
void trocarPecaAtual(FilaPecas *f, PilhaReserva *p) {
    if (f->total_elementos == 0 || p->topo == -1) {
        printf("\nErro: Fila ou Pilha vazia para troca!\n");
        return;
    }
    Peca temp = f->itens[f->frente];
    f->itens[f->frente] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    printf("\n[TROCA] Pecas trocadas com sucesso!\n");
}

