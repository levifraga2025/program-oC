#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura da Sala (Nó da Árvore Binária)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função criarSala: Aloca memória e inicializa um novo cômodo
Sala* criarSala(char *nome) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}