#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// --- ESTRUTURAS ---

// Nó da Árvore BST de Pistas Coletadas
typedef struct PistaNode {
    char descricao[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Estrutura para a Tabela Hash (Pista -> Suspeito)
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode *proximo;
} HashNode;

// Nó da Árvore Binária da Mansão (Navegação)
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// --- FUNÇÕES DE TABELA HASH ---

// Função Hash simples baseada na soma dos caracteres
int calcularIndice(char *str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++) soma += str[i];
    return soma % TAM_HASH;
}

// inserirNaHash: Associa uma pista a um suspeito na tabela
void inserirNaHash(HashNode *tabela[], char *pista, char *suspeito) {
    int indice = calcularIndice(pista);
    HashNode *novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabela[indice];
    tabela[indice] = novo;
}

// encontrarSuspeito: Retorna o nome do suspeito associado a uma pista
char* encontrarSuspeito(HashNode *tabela[], char *pista) {
    int indice = calcularIndice(pista);
    HashNode *atual = tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) return atual->suspeito;
        atual = atual->proximo;
    }
    return "Desconhecido";
}

// --- FUNÇÕES DE PISTAS (BST) ---

// inserirPista: Adiciona a pista coletada na árvore BST de forma ordenada
PistaNode* inserirPista(PistaNode *raiz, char *pista) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->descricao, pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->descricao) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->descricao) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);
    return raiz;
}

// listarPistas: Exibe as pistas coletadas em ordem alfabética
void listarPistas(PistaNode *raiz) {
    if (raiz != NULL) {
        listarPistas(raiz->esquerda);
        printf("- %s\n", raiz->descricao);
        listarPistas(raiz->direita);
    }
}

// --- LÓGICA DE JULGAMENTO ---

// Conta quantas pistas na BST apontam para o suspeito acusado usando a Hash
int contarEvidencias(PistaNode *raizPistas, HashNode *tabela[], char *acusado) {
    if (raizPistas == NULL) return 0;
    
    int conta = 0;
    char *suspeitoVinculado = encontrarSuspeito(tabela, raizPistas->descricao);
    
    if (strcmp(suspeitoVinculado, acusado) == 0) conta = 1;
    
    return conta + contarEvidencias(raizPistas->esquerda, tabela, acusado) + 
                   contarEvidencias(raizPistas->direita, tabela, acusado);
}

// verificarSuspeitoFinal: Realiza o julgamento com base nas pistas coletadas
void verificarSuspeitoFinal(PistaNode *raizPistas, HashNode *tabela[]) {
    char acusado[50];
    printf("\n--- FASE DE JULGAMENTO ---\n");
    printf("Pistas coletadas em ordem alfabetica:\n");
    listarPistas(raizPistas);
    
    printf("\nQuem voce deseja acusar? (Mordomo / Cozinheira / Jardineiro): ");
    scanf(" %s", acusado);
    
    int evidencias = contarEvidencias(raizPistas, tabela, acusado);
    
    printf("\nAnalisando evidencias contra %s...\n", acusado);
    printf("Total de pistas encontradas que apontam para ele(a): %d\n", evidencias);
    
    if (evidencias >= 2) {
        printf("SUCESSO! Voce apresentou provas suficientes e o culpado foi preso.\n");
    } else {
        printf("FRACASSO! Provas insuficientes. O culpado escapou ou voce acusou um inocente.\n");
    }
}

// --- FUNÇÕES DA MANSÃO ---

Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

void explorarSalas(Sala *raiz, HashNode *tabela[]) {
    Sala *atual = raiz;
    PistaNode *inventario = NULL;
    char escolha;

    while (atual != NULL) {
        printf("\nVoce esta no(a): %s\n", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("[!] Pista encontrada: %s\n", atual->pista);
            inventario = inserirPista(inventario, atual->pista);
        }

        printf("Caminhos: ");
        if (atual->esquerda) printf("[e] %s ", atual->esquerda->nome);
        if (atual->direita) printf("[d] %s ", atual->direita->nome);
        printf("\nEscolha (e/d) ou [s] para acusar alguem: ");
        scanf(" %c", &escolha);

        if (escolha == 's') break;
        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
        else printf("Caminho invalido!\n");
    }
    
    verificarSuspeitoFinal(inventario, tabela);
}

int main() {
    // 1. Inicializar Tabela Hash
    HashNode *tabelaHash[TAM_HASH] = {NULL};
    
    // 2. Definir Associações (Pista -> Suspeito)
    inserirNaHash(tabelaHash, "Veneno de rato", "Cozinheira");
    inserirNaHash(tabelaHash, "Faca amolada", "Cozinheira");
    inserirNaHash(tabelaHash, "Luvas sujas", "Jardineiro");
    inserirNaHash(tabelaHash, "Tesoura de poda", "Jardineiro");
    inserirNaHash(tabelaHash, "Chave mestra", "Mordomo");
    inserirNaHash(tabelaHash, "Relogio quebrado", "Mordomo");

    // 3. Montar Mansão (Árvore Binária)
    Sala *hall = criarSala("Hall", "");
    hall->esquerda = criarSala("Cozinha", "Veneno de rato");
    hall->direita = criarSala("Escritorio", "Chave mestra");
    hall->esquerda->esquerda = criarSala("Despensa", "Faca amolada");
    hall->direita->direita = criarSala("Jardim", "Luvas sujas");

    // 4. Iniciar Jogo
    printf("--- DETECTIVE QUEST: NIVEL MESTRE ---\n");
    explorarSalas(hall, tabelaHash);

    return 0;
}