#include <stdio.h>

int main() {
    // ---------- DECLARAÇÃO DAS VARIÁVEIS ----------

    // Carta 1
    char estado1;
    char codigo1[4];
    char nomeCidade1[50];
    unsigned long int populacao1;
    float area1, pib1;
    int pontosTuristicos1;
    float densidade1, pibPerCapita1, superPoder1;

    // Carta 2
    char estado2;
    char codigo2[4];
    char nomeCidade2[50];
    unsigned long int populacao2;
    float area2, pib2;
    int pontosTuristicos2;
    float densidade2, pibPerCapita2, superPoder2;

    // ---------- LEITURA DOS DADOS DA CARTA 1 ----------
    printf("=== Cadastro da Carta 1 ===\n");
    printf("Estado (A-H): ");
    scanf(" %c", &estado1);
    printf("Código da Carta (ex: A01): ");
    scanf("%3s", codigo1);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade1);
    printf("População: ");
    scanf("%lu", &populacao1);
    printf("Área (km²): ");
    scanf("%f", &area1);
    printf("PIB (em bilhões de reais): ");
    scanf("%f", &pib1);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontosTuristicos1);

    // ---------- LEITURA DOS DADOS DA CARTA 2 ----------
    printf("\n=== Cadastro da Carta 2 ===\n");
    printf("Estado (A-H): ");
    scanf(" %c", &estado2);
    printf("Código da Carta (ex: B02): ");
    scanf("%3s", codigo2);
    printf("Nome da Cidade: ");
    scanf(" %[^\n]", nomeCidade2);
    printf("População: ");
    scanf("%lu", &populacao2);
    printf("Área (km²): ");
    scanf("%f", &area2);
    printf("PIB (em bilhões de reais): ");
    scanf("%f", &pib2);
    printf("Número de Pontos Turísticos: ");
    scanf("%d", &pontosTuristicos2);

    // ---------- CÁLCULOS ----------
    densidade1 = (float) populacao1 / area1;
    densidade2 = (float) populacao2 / area2;

    pibPerCapita1 = (pib1 * 1000000000.0f) / (float) populacao1;
    pibPerCapita2 = (pib2 * 1000000000.0f) / (float) populacao2;

    superPoder1 = (float) populacao1 + area1 + pib1 + (float) pontosTuristicos1 + pibPerCapita1 + (1.0f / densidade1);
    superPoder2 = (float) populacao2 + area2 + pib2 + (float) pontosTuristicos2 + pibPerCapita2 + (1.0f / densidade2);

    // ---------- RESULTADOS DAS COMPARAÇÕES ----------
    printf("\n=== Comparação de Cartas ===\n");
    printf("População: Carta 1 venceu (%d)\n", populacao1 > populacao2);
    printf("Área: Carta 1 venceu (%d)\n", area1 > area2);
    printf("PIB: Carta 1 venceu (%d)\n", pib1 > pib2);
    printf("Pontos Turísticos: Carta 1 venceu (%d)\n", pontosTuristicos1 > pontosTuristicos2);
    printf("Densidade Populacional: Carta 1 venceu (%d)\n", densidade1 < densidade2); // menor densidade vence
    printf("PIB per Capita: Carta 1 venceu (%d)\n", pibPerCapita1 > pibPerCapita2);
    printf("Super Poder: Carta 1 venceu (%d)\n", superPoder1 > superPoder2);

    // ---------- EXIBIÇÃO DAS CARTAS ----------
    printf("\n=== Dados Cadastrados ===\n");

    printf("\nCarta 1:\n");
    printf("Estado: %c\nCódigo: %s\nNome da Cidade: %s\n", estado1, codigo1, nomeCidade1);
    printf("População: %lu\nÁrea: %.2f km²\nPIB: %.2f bilhões de reais\n", populacao1, area1, pib1);
    printf("Pontos Turísticos: %d\n", pontosTuristicos1);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade1);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita1);
    printf("Super Poder: %.2f\n", superPoder1);

    printf("\nCarta 2:\n");
    printf("Estado: %c\nCódigo: %s\nNome da Cidade: %s\n", estado2, codigo2, nomeCidade2);
    printf("População: %lu\nÁrea: %.2f km²\nPIB: %.2f bilhões de reais\n", populacao2, area2, pib2);
    printf("Pontos Turísticos: %d\n", pontosTuristicos2);
    printf("Densidade Populacional: %.2f hab/km²\n", densidade2);
    printf("PIB per Capita: %.2f reais\n", pibPerCapita2);
    printf("Super Poder: %.2f\n", superPoder2);

    return 0;
}
