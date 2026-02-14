#include <stdio.h>
#include <string.h>

//Struct Território
struct territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main(){
    //Definindo um array de structs para armazenar 5 territórios
    struct Territorios territorios[5];
    int i;

    printf("--- Cadastro de Territorios ---\n");

    //Cadastro dos territórios
    for(int i =0; i <5; i++) {
        printf("\nTerritorios %d:\n", i +1);

        printf("Nome: ");
        scanf("%[^\n]s", territorios[i].nome); // Lê o nome do território
        getchar(); // Limpa o buffer do teclado

        printf("Cor do exército: ");
        scanf("%[^\n]s", territorios[i].cor); // Lê a cor do exército
        getchar(); // Limpa o buffer do teclado

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas); // Lê o número de tropas
        getchar(); // Limpa o buffer do teclado
    }
}