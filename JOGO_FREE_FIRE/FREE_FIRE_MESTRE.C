

    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Protótipos das funções
void bubbleSortNome(Componente v[], int n);
void insertionSortTipo(Componente v[], int n);
void selectionSortPrioridade(Componente v[], int n);
int buscaBinariaPorNome(Componente v[], int n, char nomeBusca[]);
void mostrarComponentes(Componente v[], int n);
void limparBuffer();

int main() {
    Componente mochila[MAX_COMP];
    int total = 0;
    int opcao;
    int ordenadoPorNome = 0;

    while (1) {
        printf("\n==========================================================\n");
        printf("       PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)      \n");
        printf("==========================================================\n");
        printf("Itens na Mochila: %d/%d\n", total, MAX_COMP);
        printf("Status da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("\n1. Adicionar Componente");
        printf("\n2. Descartar Componente");
        printf("\n3. Listar Componentes (Inventario)");
        printf("\n4. Organizar Mochila (Ordenar Componentes)");
        printf("\n5. Busca Binaria por Componente-Chave (por nome)");
        printf("\n0. ATIVAR TORRE DE FUGA (Sair)");
        printf("\n----------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            continue;
        }
        limparBuffer();

        if (opcao == 0) break;

        switch (opcao) {
            case 1:
                if (total < MAX_COMP) {
                    printf("Nome do componente: ");
                    fgets(mochila[total].nome, 30, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = 0;
                    
                    printf("Tipo: ");
                    fgets(mochila[total].tipo, 20, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = 0;
                    
                    printf("Prioridade (1-10): ");
                    scanf("%d", &mochila[total].prioridade);
                    total++;
                    ordenadoPorNome = 0; 
                } else {
                    printf("Mochila cheia!\n");
                }
                break;

            case 2:
                if (total > 0) {
                    total--;
                    printf("Componente descartado.\n");
                }
                break;

            case 3:
                mostrarComponentes(mochila, total);
                break;

            case 4: { // CHAVES ADICIONADAS PARA CORRIGIR "JUMP TO CASE LABEL"
                if (total < 2) {
                    printf("Itens insuficientes para ordenar.\n");
                    break;
                }
                int subOpcao;
                printf("\n1. Bubble Sort (Nome)\n2. Insertion Sort (Tipo)\n3. Selection Sort (Prioridade)\nEscolha: ");
                scanf("%d", &subOpcao);

                clock_t t = clock();
                if (subOpcao == 1) {
                    bubbleSortNome(mochila, total);
                    ordenadoPorNome = 1;
                } else if (subOpcao == 2) {
                    insertionSortTipo(mochila, total);
                    ordenadoPorNome = 0;
                } else if (subOpcao == 3) {
                    selectionSortPrioridade(mochila, total);
                    ordenadoPorNome = 0;
                }
                t = clock() - t;
                printf("\nTempo de execucao: %f segundos.\n", ((double)t)/CLOCKS_PER_SEC);
                mostrarComponentes(mochila, total);
                break;
            }

            case 5: { // CHAVES ADICIONADAS PARA CORRIGIR "JUMP TO CASE LABEL"
                if (!ordenadoPorNome) {
                    printf("Erro: Ordene por NOME (Bubble) antes da busca binaria!\n");
                } else {
                    char busca[30];
                    printf("Nome do componente-chave: ");
                    fgets(busca, 30, stdin);
                    busca[strcspn(busca, "\n")] = 0;
                    
                    int pos = buscaBinariaPorNome(mochila, total, busca);
                    if (pos != -1) {
                        printf("\n[SUCESSO] Item encontrado na posicao %d\n", pos + 1);
                    } else {
                        printf("\n[ERRO] Item nao encontrado.\n");
                    }
                }
                break;
            }

            default:
                printf("Opcao invalida.\n");
        }
    }
    return 0;
}

// --- Funções Auxiliares ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n--- INVENTARIO ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. [%s] Tipo: %s | Prioridade: %d\n", i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

void bubbleSortNome(Componente v[], int n) {
    int comp = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comp++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
    printf("Comparacoes: %d\n", comp);
}

void insertionSortTipo(Componente v[], int n) {
    int comp = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comp++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
    printf("Comparacoes: %d\n", comp);
}

void selectionSortPrioridade(Componente v[], int n) {
    int comp = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comp++;
            if (v[j].prioridade < v[min].prioridade) min = j;
        }
        Componente temp = v[min];
        v[min] = v[i];
        v[i] = temp;
    }
    printf("Comparacoes: %d\n", comp);
}

int buscaBinariaPorNome(Componente v[], int n, char nomeBusca[]) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        int res = strcmp(v[meio].nome, nomeBusca);
        if (res == 0) return meio;
        if (res < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}            