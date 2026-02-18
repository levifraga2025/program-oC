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
// Função para cadastrar novos itens (limite de 10)
void inserirItem() {
    if (totalItens < MAX_ITENS) {
        printf("\nNome do item: ");
        fgets(mochila[totalItens].nome, 30, stdin);
        mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = 0; // Remove o \n

        printf("Tipo (Arma, Municao, Cura): ");
        fgets(mochila[totalItens].tipo, 20, stdin);
        mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = 0;

        printf("Quantidade: ");
        scanf("%d", &mochila[totalItens].quantidade);
        limparBuffer();

        totalItens++;
        printf("Item adicionado com sucesso!\n");
    } else {
        printf("\nMochila cheia! Descarte algo primeiro.\n");
    }
}

void listarItens() {
    printf("\n--- SEU INVENTARIO (%d/%d) ---\n", totalItens, MAX_ITENS);
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("[%d] %s | Tipo: %s | Qtd: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
}

// Busca sequencial por nome
void buscarItem() {
    char termo[30];
    int encontrado = 0;

    printf("\nDigite o nome do item para buscar: ");
    fgets(termo, 30, stdin);
    termo[strcspn(termo, "\n")] = 0;

    for (int i = 0; i < totalItens; i++) {
        if (strcasecmp(mochila[i].nome, termo) == 0) {
            printf("\nItem encontrado: %s | Tipo: %s | Qtd: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) printf("\nItem '%s' nao localizado.\n", termo);
}

// Remove item e reorganiza o vetor (lista sequencial)
void removerItem() {
    char termo[30];
    int encontrado = -1;

    printf("\nNome do item para remover: ");
    fgets(termo, 30, stdin);
    termo[strcspn(termo, "\n")] = 0;

    for (int i = 0; i < totalItens; i++) {
        if (strcasecmp(mochila[i].nome, termo) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        // Shifting: move os itens da frente para trás para não deixar "buracos"
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("Item removido!\n");
    } else {
        printf("Item nao encontrado.\n");
    }
}

// Auxiliar para evitar problemas com scanf e fgets
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}