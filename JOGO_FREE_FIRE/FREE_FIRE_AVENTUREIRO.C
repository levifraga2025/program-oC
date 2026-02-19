#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ITENS 15

// 1. ESTRUTURAS TEMÁTICAS (FREE FIRE)
typedef struct {
    char nome[30];      // Ex: AK47, Colete Nv3, Inalador
    char tipo[20];      // Ex: AR, SMG, Equipamento, Consumivel
    int quantidade;
    int raridade;       // 1: Comum, 2: Raro, 3: Lendario
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// VARIÁVEIS DE CONTROLE
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;
No* cabecaLista = NULL;
int contadorComparacoes = 0;

// PROTÓTIPOS
void menuPrincipal();
void limparBuffer();
const char* GetRaridade(int r);

// FUNÇÕES DE VETOR
void inserirVetor();
void listarVetor();
void buscarBinariaVetor();
void ordenarVetorNome();

// FUNÇÕES DE LISTA
void inserirLista();
void listarLista();
void removerLista();