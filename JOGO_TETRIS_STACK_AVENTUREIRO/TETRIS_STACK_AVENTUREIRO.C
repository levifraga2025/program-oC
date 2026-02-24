#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 5

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
    p->nome = 'A' + (rand() % 26); // Letra aleatória
    p->id = rand() % 10;         // ID aleatório
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
        printf("\nErro: Nao ha pecas na fila!\n");
        return;
    }
    Peca p = f->itens[f->frente];
    printf("\n[JOGADA] Voce usou a peca: [%c %d]\n", p.nome, p.id);
    
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->total_elementos--;
    
    // Repõe automaticamente para manter a fila cheia
    inserirFila(f);
}

// Reservar Peça (Move da Fila para a Pilha - PUSH)
void reservarPeca(FilaPecas *f, PilhaReserva *p) {
    if (f->total_elementos == 0) {
        printf("\nFila vazia!\n");
        return;
    }
    if (p->topo == TAMANHO_PILHA - 1) {
        printf("\nReserva (Pilha) cheia!\n");
        return;
    }

    // Pega a peça da frente da fila
    Peca pecaReservada = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->total_elementos--;

    // Coloca na pilha
    p->topo++;
    p->itens[p->topo] = pecaReservada;
    
    printf("\n[RESERVA] Peca [%c %d] movida para a reserva.\n", pecaReservada.nome, pecaReservada.id);
    
    // Repõe a fila
    inserirFila(f);
}

// Usar Reserva (Move da Pilha para o Jogo - POP)
void usarReserva(PilhaReserva *p) {
    if (p->topo == -1) {
        printf("\nNao ha pecas na reserva!\n");
        return;
    }
    Peca pecaUsada = p->itens[p->topo];
    p->topo--;
    printf("\n[USO RESERVA] Voce usou a peca reservada: [%c %d]\n", pecaUsada.nome, pecaUsada.id);
}

// --- INTERFACE ---

void exibirEstado(FilaPecas *f, PilhaReserva *p) {
    printf("\n======= STATUS DO JOGO =======\n");
    printf("FILA (Proximas): ");
    for (int i = 0; i < f->total_elementos; i++) {
        int idx = (f->frente + i) % TAMANHO_FILA;
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    
    printf("\nRESERVA (Topo): ");
    if (p->topo == -1) printf("[ VAZIA ]");
    else printf("[%c %d]", p->itens[p->topo].nome, p->itens[p->topo].id);
    printf("\n------------------------------\n");
}