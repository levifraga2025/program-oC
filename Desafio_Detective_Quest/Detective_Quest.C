#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura da Sala (Nó da Árvore Binária)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;