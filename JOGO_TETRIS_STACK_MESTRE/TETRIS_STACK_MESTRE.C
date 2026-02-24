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

//Troca Múltipla: Troca N elementos (enquanto houver espaço/itens)
void trocaMultipla(FilaPecas *f, PilhaReserva *p) {
    int qtd;
    printf("Quantas trocas deseja realizar? ");
    scanf("%d", &qtd);

    for (int i = 0; i < qtd; i++) {
        if (p->topo >= i && i < f->total_elementos) {
            int idxFila = (f->frente + i) % TAMANHO_FILA;
            int idxPilha = p->topo - i;
            Peca temp = f->itens[idxFila];
            f->itens[idxFila] = p->itens[idxPilha];
            p->itens[idxPilha] = temp;
        } else {
            printf("\nLimite de troca atingido no item %d.\n", i + 1);
            break;
        }
    }
}

// Troca Toda a Reserva (Inversão/Reversão)
// Move todos da reserva para o início da fila, empurrando o resto
void trocarTodaReserva(FilaPecas *f, PilhaReserva *p) {
    if (p->topo == -1) {
        printf("\nReserva vazia!\n");
        return;
    }
    
    printf("\n[REVERSAO] Invertendo reserva para a fila...\n");
    while (p->topo > -1) {
        // Troca o topo da pilha com a frente da fila
        Peca temp = f->itens[f->frente];
        f->itens[f->frente] = p->itens[p->topo];
        p->itens[p->topo] = temp;

        f->frente = (f->frente + 1) % TAMANHO_FILA;
        p->topo--; // Remove da pilha conforme integra na fila
    }
}

void exibirEstado(FilaPecas *f, PilhaReserva *p) {
    printf("\n======= STATUS DO JOGO =======\n");
    printf("FILA (Proximas): ");
    for (int i = 0; i < f->total_elementos; i++) {
        int idx = (f->frente + i) % TAMANHO_FILA;
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    
    printf("\nRESERVA (Pilha): ");
    if (p->topo == -1) printf("[ VAZIA ]");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n------------------------------\n");
}

int main() {
    srand(time(NULL));
    FilaPecas fila;
    PilhaReserva reserva;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&reserva);

    for (int i = 0; i < TAMANHO_FILA; i++) inserirFila(&fila);

    do {
        exibirEstado(&fila, &reserva);
        printf("1 - Jogar peca (Fila)\n");
        printf("2 - Reservar peca (Fila -> Pilha)\n");
        printf("3 - Trocar peca atual (Fila <-> Topo Pilha)\n");
        printf("4 - Troca Multipla\n");
        printf("5 - Trocar TODA reserva (Reversao)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: jogarPeca(&fila); break;
            case 2: reservarPeca(&fila, &reserva); break;
            case 3: trocarPecaAtual(&fila, &reserva); break;
            case 4: trocaMultipla(&fila, &reserva); break;
            case 5: trocarTodaReserva(&fila, &reserva); break;
            case 0: break;
            default: printf("Invalido!\n");
        }
    } while (opcao != 0);

    return 0;
}