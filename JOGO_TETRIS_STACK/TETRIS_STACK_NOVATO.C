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

    // Move a frente de forma circular
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->total_elementos--;
}

// Exibe o estado visual da fila para o jogador
void exibirFila(FilaPecas *f) {
    printf("\nFila de pecas: ");
    if (filaVazia(f)) {
        printf("[ VAZIA ]");
    } else {
        for (int i = 0; i < f->total_elementos; i++) {
            // Calcula o índice real considerando a circularidade
            int indice = (f->frente + i) % TAMANHO_FILA;
            printf("[%c %d] ", f->itens[indice].nome, f->itens[indice].id);
        }
    }
    printf("\n------------------------------------\n");
}

int main() {
    srand(time(NULL)); // Semente para aleatoriedade
    FilaPecas fila;
    int opcao;

    inicializarFila(&fila);

    // Inicializa a fila com 5 elementos conforme requisito
    for (int i = 0; i < TAMANHO_FILA; i++) {
        inserirPeca(&fila);
    }

    do {
        exibirFila(&fila);
        printf("Opcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila);
                break;
            case 0:
                printf("Encerrando sistema da ByteBros...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}