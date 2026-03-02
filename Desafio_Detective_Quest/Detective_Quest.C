#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura da Sala (Nó da Árvore Binária)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função criarSala: Aloca memória e inicializa um novo cômodo
Sala* criarSala(char *nome) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

// Função explorarSalas: Gerencia a navegação interativa do jogador
void explorarSalas(Sala *raiz) {
    Sala *atual = raiz;
    char escolha;

    printf("\n--- Inicio da Investigacao ---\n");

    while (atual != NULL) {
        printf("\nVoce esta na: **%s**\n", atual->nome);

        // Verifica se é um nó-folha (fim do caminho)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Voce chegou a um beco sem saida ou ao fim da pista. Exploracao concluida!\n");
            break;
        }

        printf("Caminhos disponiveis: ");
        if (atual->esquerda) printf("[e] Esquerda: %s  ", atual->esquerda->nome);
        if (atual->direita) printf("[d] Direita: %s", atual->direita->nome);
        
        printf("\nEscolha sua direcao (e/d) ou [s] para sair: ");
        scanf(" %c", &escolha);

        if (escolha == 's') {
            printf("Saindo da investigacao...\n");
            break;
        } else if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else {
            printf("Caminho invalido! Tente novamente.\n");
        }
    }
}

int main() {
    // Montagem automática do mapa da mansão (Estrutura da Árvore)
    //         Hall
    //        /    \
    //    Sala    Cozinha
    //    /  \       \
    // Jardim Biblioteca Quarto
    
    Sala *hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");
    
    hall->esquerda->esquerda = criarSala("Jardim de Inverno");
    hall->esquerda->direita = criarSala("Biblioteca");
    
    hall->direita->direita = criarSala("Quarto do Suspeito");

    // Início do jogo
    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansao para encontrar pistas e desvendar o misterio.");
    
    explorarSalas(hall);

    // Nota: Em um sistema real, aqui teríamos uma função para liberar a memória (free)
    printf("\nObrigado por jogar!\n");

    return 0;
}