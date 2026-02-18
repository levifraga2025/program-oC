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

// Variáveis globais para controle do inventário
Item mochila[MAX_ITENS];
int totalItens = 0;

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBuffer();

int main() {
    int opcao;

    do {
        printf("\n--- MOCHILA DE LOOT ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Buscar Item\n");
        printf("4. Listar Tudo\n");
        printf("0. Sair\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        limparBuffer();

        int main() {
    int opcao;

    do {
        printf("\n--- MOCHILA DE LOOT ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Buscar Item\n");
        printf("4. Listar Tudo\n");
        printf("0. Sair\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: buscarItem(); break;
            case 4: listarItens(); break;
            case 0: printf("Saindo do jogo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
        
        // Listagem automática após cada operação conforme requisito
        if(opcao != 0 && opcao != 4) {
            listarItens();
        }

    } while(opcao != 0);

    return 0;
}