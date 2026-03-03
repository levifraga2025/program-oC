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