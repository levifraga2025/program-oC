#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura para o Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirMapa(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    int qtd;
    int opAtacante, opDefensor;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("--- BEM-VINDO AO SIMULADOR DE ATAQUE WAR ---\n");
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação dinâmica usando calloc (limpa a memória com zeros)
    Territorio* mapa = (Territorio*) calloc(qtd, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int jogando = 1;
    while (jogando) {
        exibirMapa(mapa, qtd);

        printf("\n--- FASE DE ATAQUE ---\n");
        printf("Escolha o indice do territorio ATACANTE (0 a %d) ou -1 para sair: ", qtd - 1);
        scanf("%d", &opAtacante);

        if (opAtacante == -1) break;

        printf("Escolha o indice do territorio DEFENSOR (0 a %d): ", qtd - 1);
        scanf("%d", &opDefensor);

        // Validações básicas
        if (opAtacante < 0 || opAtacante >= qtd || opDefensor < 0 || opDefensor >= qtd) {
            printf("\n[ERRO] Indices invalidos!\n");
        } else if (strcmp(mapa[opAtacante].cor, mapa[opDefensor].cor) == 0) {
            printf("\n[AVISO] Voce nao pode atacar seu proprio territorio!\n");
        } else if (mapa[opAtacante].tropas < 2) {
            printf("\n[AVISO] O atacante precisa de pelo menos 2 tropas para atacar!\n");
        } else {
            // Chamada da função de ataque usando ponteiros (endereços)
            atacar(&mapa[opAtacante], &mapa[opDefensor]);
        }
    }

    liberarMemoria(mapa);
    printf("\nSistema encerrado. Obrigado por jogar!\n");

    return 0;
}

// Implementação: Cadastro via ponteiro
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio [%d]:\n", i);
        printf("Nome: ");
        scanf(" %29[^\n]", (mapa + i)->nome);
        printf("Cor do Exercito: ");
        scanf(" %9[^\n]", (mapa + i)->cor);-1-
        printf("Quantidade de Tropas: ");
        scanf("%d", &(mapa + i)->tropas);
    }
}

// Implementação: Exibição via ponteiro
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n========= ESTADO DO MAPA =========\n");
    printf("ID | NOME           | COR      | TROPAS\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%-2d | %-14s | %-8s | %d\n", 
                i, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
    printf("==================================\n");
}

// Implementação: Função de ataque 
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DOS DADOS ---\n");
    printf("%s (Atacante): %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATACANTE! %s conquistou %s.\n", atacante->nome, defensor->nome);
        
        // Atualização dos campos: troca a cor e move metade das tropas
        strcpy(defensor->cor, atacante->cor);
        int tropasMovidas = atacante->tropas / 2;
        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;
        
    } else { // Este é o else da linha 116 do seu erro
        printf("DEFESA VENCEU! %s perdeu 1 tropa.\n", atacante->nome);
        atacante->tropas--;
    } // <-- Faltava esta chave para fechar o else
} // <-- Faltava esta chave para fechar a função atacar

// Função essencial para liberar a memória alocada com malloc/calloc
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}