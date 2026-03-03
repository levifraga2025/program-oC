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

// --- FUNÇÕES DE PISTAS (BST) ---

// inserirPista: Insere uma nova pista na árvore BST de forma ordenada (alfabética)
PistaNode* inserirPista(PistaNode *raiz, char *novaPista) {
    if (novaPista == NULL || strlen(novaPista) == 0) return raiz;

    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->pista, novaPista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    // Comparação alfabética para decidir o lado da inserção
    if (strcmp(novaPista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, novaPista);
    } else {
        raiz->direita = inserirPista(raiz->direita, novaPista);
    }
    return raiz;
}

// exibirPistas: Imprime a árvore de pistas em ordem alfabética (In-order traversal)
void exibirPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// --- FUNÇÕES DA MANSÃO ---

// criarSala: Aloca memória e inicializa um novo cômodo com sua respectiva pista
Sala* criarSala(char *nome, char *pista) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        strcpy(novaSala->pista, pista);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

// explorarSalasComPistas: Gerencia a navegação e a coleta automática de pistas
void explorarSalasComPistas(Sala *raizMansao) {
    Sala *atual = raizMansao;
    PistaNode *raizPistas = NULL; // Raiz da árvore de pistas coletadas
    char escolha;

    printf("\n--- Inicio da Investigacao ---\n");

    while (atual != NULL) {
        printf("\nVoce esta na: **%s**\n", atual->nome);

        // Coleta automática de pista se houver uma no cômodo
        if (strlen(atual->pista) > 0) {
            printf("[!] Voce encontrou uma pista: %s\n", atual->pista);
            raizPistas = inserirPista(raizPistas, atual->pista);
        } else {
            printf("Nao ha pistas relevantes neste comodo.\n");
        }

        printf("Caminhos disponiveis: ");
        if (atual->esquerda) printf("[e] Esquerda: %s  ", atual->esquerda->nome);
        if (atual->direita) printf("[d] Direita: %s", atual->direita->nome);
        
        printf("\nEscolha sua direcao (e/d) ou [s] para sair e ver o relatorio: ");
        scanf(" %c", &escolha);

        if (escolha == 's') {
            break;
        } else if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else {
            printf("Caminho invalido!\n");
        }
    }

    // Exibição final dos resultados
    printf("\n========================================\n");
    printf("RELATORIO FINAL - PISTAS COLETADAS\n");
    printf("========================================\n");
    if (raizPistas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistas(raizPistas);
    }
    printf("========================================\n");
}

// --- MAIN ---

int main() {
    // Montagem do mapa da mansão com pistas específicas
    // Parâmetros: criarSala("Nome do Cômodo", "Descrição da Pista")
    
    Sala *hall = criarSala("Hall de Entrada", "Chave velha no tapete");
    
    hall->esquerda = criarSala("Sala de Estar", "Mancha de cafe no sofa");
    hall->direita = criarSala("Cozinha", "Bilhete com horario de jantar");
    
    hall->esquerda->esquerda = criarSala("Jardim de Inverno", "Pegada na terra");
    hall->esquerda->direita = criarSala("Biblioteca", "Livro fora de lugar");
    
    hall->direita->direita = criarSala("Quarto do Suspeito", "Diario trancado");

    // Início do jogo
    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansao para encontrar pistas e desvendar o misterio.\n");
    
    explorarSalasComPistas(hall);

    printf("\nObrigado por jogar, Detetive!\n");

    return 0;
}