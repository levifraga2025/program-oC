#include <stdio.h>
#include <string.h>

// 1. Criação da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Definindo um array de structs para armazenar 5 territórios
    struct Territorio territorios[5];
    int i;

    printf("--- Cadastro de Territorios ---\n");

    // 2. Cadastro dos territórios
    for (i = 0; i < 5; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        
        printf("Nome: ");
        scanf(" %[^\n]s", territorios[i].nome); // O " %[^\n]s" lê nomes com espaços

        printf("Cor do exercito: ");
        scanf(" %s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // 3. Exibição dos dados
    printf("\n--- Dados dos Territorios Registrados ---\n");
    printf("--------------------------------------------------\n");
    printf("%-20s | %-10s | %-s\n", "Nome", "Cor", "Tropas");
    printf("--------------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("%-20s | %-10s | %-d\n", 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
    }

    return 0;
}