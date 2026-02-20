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

