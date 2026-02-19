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

// VARIÁVEIS DE CONTROLE
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;
No* cabecaLista = NULL;
int contadorComparacoes = 0;

// PROTÓTIPOS
void menuPrincipal();
void limparBuffer();

// FUNÇÕES DE VETOR
void inserirVetor();
void listarVetor();
void buscarBinariaVetor();
void ordenarVetorNome();

// FUNÇÕES DE LISTA
void inserirLista();
void listarLista();
void removerLista();

int main() {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int escolha;
    do {
        printf("\n========================================");
        printf("\n      SISTEMA DE LOOT - FREE FIRE       ");
        printf("\n========================================");
        printf("\n1. [VETOR] Adicionar Item (Loot)");
        printf("\n2. [VETOR] Buscar Item (Busca Binaria)");
        printf("\n3. [VETOR] Listar Mochila");
        printf("\n----------------------------------------");
        printf("\n4. [LISTA] Adicionar Item (Drop)");
        printf("\n5. [LISTA] Remover Item (Descartar)");
        printf("\n6. [LISTA] Listar Chao/Drop");
        printf("\n0. Sair do Jogo");
        printf("\nEscolha: ");
        if (scanf("%d", &escolha) != 1) {
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch(escolha) {
            case 1: inserirVetor(); break;
            case 2: buscarBinariaVetor(); break;
            case 3: listarVetor(); break;
            case 4: inserirLista(); break;
            case 5: removerLista(); break;
            case 6: listarLista(); break;
        }
    } while(escolha != 0);
}

// --- LOGICA DE VETOR (MOCHILA DO JOGADOR) ---

void inserirVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("\n[!] Mochila cheia! Descarte algo para pegar mais loot.\n");
        return;
    }

    Item novo;
    printf("\nNome do Item (Ex: M4A1, MP40): ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Categoria (AR, SMG, Sniper, Cura): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    mochilaVetor[totalVetor] = novo;
    totalVetor++;
    
    ordenarVetorNome();
    printf("\n[+] %s adicionado a mochila!\n", novo.nome);
}

void ordenarVetorNome() {
    for (int i = 0; i < totalVetor - 1; i++) {
        int min = i;
        for (int j = i + 1; j < totalVetor; j++) {
            if (strcasecmp(mochilaVetor[j].nome, mochilaVetor[min].nome) < 0)
                min = j;
        }
        Item temp = mochilaVetor[min];
        mochilaVetor[min] = mochilaVetor[i];
        mochilaVetor[i] = temp;
    }
}

void buscarBinariaVetor() {
    char busca[30];
    contadorComparacoes = 0;
    printf("\nBuscar item na mochila: ");
    fgets(busca, 30, stdin);
    busca[strcspn(busca, "\n")] = 0;

    int esq = 0, dir = totalVetor - 1;
    while (esq <= dir) {
        contadorComparacoes++;
        int meio = (esq + dir) / 2;
        int res = strcasecmp(mochilaVetor[meio].nome, busca);

        if (res == 0) {
            printf("\n>>> ITEM ENCONTRADO <<<");
            printf("\nNome: %s | Tipo: %s | Qtd: %d", 
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("\nComparacoes realizadas: %d\n", contadorComparacoes);
            return;
        }
        if (res < 0) esq = meio + 1;
        else dir = meio - 1;
    }
    printf("\n[!] Item '%s' nao esta na sua mochila. (Comparacoes: %d)\n", busca, contadorComparacoes);
}

void listarVetor() {
    printf("\n--- SUA MOCHILA (ORDENADA) ---");
    if(totalVetor == 0) printf("\nVazia.");
    for(int i = 0; i < totalVetor; i++) {
        printf("\n[%d] %-12s | %-8s | Qtd: %02d", 
               i+1, mochilaVetor[i].nome, mochilaVetor[i].tipo, 
               mochilaVetor[i].quantidade);
    }
    printf("\n------------------------------\n");
}

// --- LOGICA DE LISTA (DROPS NO CHÃO) ---

void inserirLista() {
    No* novo = (No*)malloc(sizeof(No));
    if(!novo) return;

    printf("\nNome do Drop no chao: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = 0;
    
    novo->dados.quantidade = 1;
    strcpy(novo->dados.tipo, "Drop");

    novo->proximo = cabecaLista;
    cabecaLista = novo;
    printf("[!] Novo loot caiu no chao: %s!\n", novo->dados.nome);
}

void listarLista() {
    No* atual = cabecaLista;
    printf("\n--- ITENS NO CHAO (LOOT BOX) ---");
    if(!atual) printf("\nNada por aqui.");
    while(atual) {
        printf("\n[V] %s", atual->dados.nome);
        atual = atual->proximo;
    }
    printf("\n--------------------------------\n");
}

void removerLista() {
    char busca[30];
    printf("\nNome do item para coletar do chao: ");
    fgets(busca, 30, stdin);
    busca[strcspn(busca, "\n")] = 0;

    No *atual = cabecaLista, *anterior = NULL;
    while(atual) {
        if(strcasecmp(atual->dados.nome, busca) == 0) {
            if(!anterior) cabecaLista = atual->proximo;
            else anterior->proximo = atual->proximo;
            
            printf("\n[+] Voce coletou: %s\n", atual->dados.nome);
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("\n[!] Esse item nao esta no chao.\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}