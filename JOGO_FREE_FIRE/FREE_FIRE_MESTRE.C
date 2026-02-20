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

                