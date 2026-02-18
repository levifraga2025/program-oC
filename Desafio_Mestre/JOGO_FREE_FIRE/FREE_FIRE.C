#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct para representar cada objeto do jogo
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

