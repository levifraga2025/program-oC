#include <stdio.h>
#include <string.h>

// Estrutura da carta
struct Carta {
    char estado[3];
    char codigo[4];
    char nomeCidade[30];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadeDemografica;
    float pibPerCapita;
};

// Função para calcular atributos derivados
void calcularAtributos(struct Carta *carta) {
    carta->densidadeDemografica = carta->populacao / carta->area;
    carta->pibPerCapita = carta->pib / carta->populacao;
}

// Função para exibir menu de atributos
void mostrarMenu(int opcaoBloqueada) {
    printf("\nEscolha um atributo para comparação:\n");
    if (opcaoBloqueada != 1) printf("1 - População\n");
    if (opcaoBloqueada != 2) printf("2 - Área\n");
    if (opcaoBloqueada != 3) printf("3 - PIB\n");
    if (opcaoBloqueada != 4) printf("4 - Número de pontos turísticos\n");
    if (opcaoBloqueada != 5) printf("5 - Densidade Demográfica\n");
}

// Função para obter valor numérico do atributo
float getValor(struct Carta carta, int atributo) {
    switch (atributo) {
        case 1: return carta.populacao;
        case 2: return carta.area;
        case 3: return carta.pib;
        case 4: return carta.pontosTuristicos;
        case 5: return carta.densidadeDemografica;
        default: return 0;
    }
}

// Função para exibir nome do atributo
const char* nomeAtributo(int atributo) {
    switch (atributo) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        default: return "Desconhecido";
    }
}

int main() {
    struct Carta carta1 = {"SP", "A01", "São Paulo", 12300000, 1521.0, 699000.0, 50};
    struct Carta carta2 = {"RJ", "B02", "Rio de Janeiro", 6710000, 1182.3, 400000.0, 30};

    calcularAtributos(&carta1);
    calcularAtributos(&carta2);

    int atributo1, atributo2;

    printf("\n===== SUPER TRUNFO - COMPARAÇÃO COM DOIS ATRIBUTOS =====\n");

    // Escolha do primeiro atributo
    mostrarMenu(0);
    printf("Digite a opção do primeiro atributo: ");
    scanf("%d", &atributo1);

    // Escolha do segundo atributo (menu dinâmico)
    mostrarMenu(atributo1);
    printf("Digite a opção do segundo atributo: ");
    scanf("%d", &atributo2);

    // Obter valores dos atributos
    float valor1_attr1 = getValor(carta1, atributo1);
    float valor2_attr1 = getValor(carta2, atributo1);
    float valor1_attr2 = getValor(carta1, atributo2);
    float valor2_attr2 = getValor(carta2, atributo2);

    // Comparar atributos individualmente
    int resultado1 = (atributo1 == 5) ? // densidade
                     (valor1_attr1 < valor2_attr1 ? 1 : (valor2_attr1 < valor1_attr1 ? 2 : 0))
                     :
                     (valor1_attr1 > valor2_attr1 ? 1 : (valor2_attr1 > valor1_attr1 ? 2 : 0));

    int resultado2 = (atributo2 == 5) ? // densidade
                     (valor1_attr2 < valor2_attr2 ? 1 : (valor2_attr2 < valor1_attr2 ? 2 : 0))
                     :
                     (valor1_attr2 > valor2_attr2 ? 1 : (valor2_attr2 > valor1_attr2 ? 2 : 0));

    // Soma dos valores para comparação final
    float soma1 = valor1_attr1 + valor1_attr2;
    float soma2 = valor2_attr1 + valor2_attr2;

    int vencedorFinal = (soma1 > soma2) ? 1 : (soma2 > soma1 ? 2 : 0);

    // Exibir resultado
    printf("\n===== RESULTADO =====\n");
    printf("Carta 1: %s\n", carta1.nomeCidade);
    printf("Carta 2: %s\n\n", carta2.nomeCidade);

    printf("Atributo 1: %s\n", nomeAtributo(atributo1));
    printf(" - %s: %.2f\n", carta1.nomeCidade, valor1_attr1);
    printf(" - %s: %.2f\n\n", carta2.nomeCidade, valor2_attr1);

    printf("Atributo 2: %s\n", nomeAtributo(atributo2));
    printf(" - %s: %.2f\n", carta1.nomeCidade, valor1_attr2);
    printf(" - %s: %.2f\n\n", carta2.nomeCidade, valor2_attr2);

    printf("Soma dos atributos:\n");
    printf(" - %s: %.2f\n", carta1.nomeCidade, soma1);
    printf(" - %s: %.2f\n\n", carta2.nomeCidade, soma2);

    if (vencedorFinal == 1)
        printf("Resultado Final: Carta 1 (%s) venceu!\n", carta1.nomeCidade);
    else if (vencedorFinal == 2)
        printf("Resultado Final: Carta 2 (%s) venceu!\n", carta2.nomeCidade);
    else
        printf("Resultado Final: Empate!\n");

    return 0;
}
