#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura dos territórios
typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
} Territorio;