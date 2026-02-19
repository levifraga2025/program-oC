#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ITENS 15

// 1. ESTRUTURAS TEMÁTICAS (FREE FIRE)
typedef struct {
    char nome[30];      
    char tipo[20];      
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;