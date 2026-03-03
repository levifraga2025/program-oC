#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS ---

// Estrutura para os nós da árvore de pistas (BST - Binary Search Tree)
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Definição da estrutura da Sala (Nó da Árvore Binária de navegação)
typedef struct Sala {
    char nome[50];
    char pista[100]; // Pista associada a este cômodo
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// --- FUNÇÕES DE PISTAS (BST) ---

// inserirPista: Insere uma nova pista na árvore BST de forma ordenada (alfabética)
PistaNode* inserirPista(PistaNode *raiz, char *novaPista) {
    if (novaPista == NULL || strlen(novaPista) == 0) return raiz;

    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->pista, novaPista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    // Comparação alfabética para decidir o lado da inserção
    if (strcmp(novaPista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, novaPista);
    } else {
        raiz->direita = inserirPista(raiz->direita, novaPista);
    }
    return raiz;
}

// exibirPistas: Imprime a árvore de pistas em ordem alfabética (In-order traversal)
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// --- FUNÇÕES DA MANSÃO ---

// criarSala: Aloca memória e inicializa um novo cômodo com sua respectiva pista
Sala* criarSala(char *nome, char *pista) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        strcpy(novaSala->pista, pista);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}