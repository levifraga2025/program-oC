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

// --- Protótipos das Funções ---
void atribuirMissao(char** destino, const char* missoes[], int totalMissoes);
void exibirStatus(Territorio* mapa, int tamanho, const char* minhaCor, char* missao);
void atacar(Territorio* mapa, int tamanho, const char* minhaCor);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa, char* missao);
