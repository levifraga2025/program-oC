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
