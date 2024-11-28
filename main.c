#include <stdio.h>    // Biblioteca padrão de entrada e saída
#include <stdlib.h>   // Biblioteca para malloc, realloc e srand
#include <string.h>   // Biblioteca com diversas operações sobre strings
#include <ctype.h>    // Biblioteca para manipulação de caracteres
#include <time.h>     // Biblioteca para srand e time

#define MAX_TENTATIVAS 6 // Número máximo de tentativas (partes do boneco)
#define MAX_PALAVRA 100  // Número máximo de palavras

typedef struct {
    char palavra[MAX_PALAVRA];
    char tema[50];
} PalavraTema;

void exibir_forca(int tentativas) {
    switch (tentativas) {
        case 6: printf("\n\n\n\n\n"); break;
        case 5: printf("\n\n\n\n O\n"); break;
        case 4: printf("\n\n\n O\n | \n"); break;
        case 3: printf("\n\n O\n | \n"); break;
        case 2: printf("\n O\n/|\\\n"); break;
        case 1: printf("\n O\n/|\\\n/ \n"); break;
        case 0: printf("\n O\n/|\\\n/ \\\n"); break;
    }
}

int main() {
    PalavraTema *palavras = NULL;
    int num_palavras = 0;
    int capacidade = 2;

    palavras = malloc(capacidade * sizeof(PalavraTema));
    if (palavras == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        return 1;
    }

    while (1) {
        if (num_palavras >= capacidade) {
            capacidade *= 2;
            palavras = realloc(palavras, capacidade * sizeof(PalavraTema));
            if (palavras == NULL) {
                fprintf(stderr, "Erro ao realocar memória.\n");
                return 1;
            }
        }

        printf("Digite uma palavra (ou 'sair' para terminar): ");
        scanf("%s", palavras[num_palavras].palavra);
        if (strcmp(palavras[num_palavras].palavra, "sair") == 0) {
            break;
        }

        printf("Digite o tema da palavra: ");
        scanf(" %[^\n]", palavras[num_palavras].tema);

        num_palavras++;
    }

    srand(time(NULL));
    int indice = rand() % num_palavras;
    char *palavra = palavras[indice].palavra;
    char *tema = palavras[indice].tema;

    char tentativa[MAX_PALAVRA] = "";
    char acertos[MAX_PALAVRA];
    int tentativas = MAX_TENTATIVAS;
    int acertos_count = 0;
    int palavra_len = strlen(palavra);

    for (int i = 0; i < palavra_len; i++) {
        acertos[i] = '_';
    }
    acertos[palavra_len] = '\0';

    printf("Tema: %s\n", tema);

    while (tentativas > 0 && acertos_count < palavra_len) {
        printf("\nPalavra: %s", acertos);
        printf("\nTentativas restantes: %d", tentativas);
        exibir_forca(tentativas);
        printf("\nDigite uma letra: ");

        char letra;
        scanf(" %c", &letra);

        if (!isalpha(letra)) {
            printf("Entrada inválida! Por favor, digite apenas uma letra.\n");
            continue;
        }

        letra = tolower(letra);

        if (strchr(tentativa, letra)) {
            printf("Você já tentou essa letra!\n");
            continue;
        }

        strncat(tentativa, &letra, 1);

        int acertou = 0;
        for (int i = 0; i < palavra_len; i++) {
            if (palavra[i] == letra && acertos[i] == '_') {
                acertos[i] = letra;
                acertos_count++;
                acertou = 1;
            }
        }

        if (!acertou) {
            tentativas--;
        }
    }

    if (acertos_count == palavra_len) {
        printf("\nParabéns! Você acertou a palavra: %s\n", palavra);
    } else {
        printf("\nVocê perdeu! A palavra era: %s\n", palavra);
    }

    free(palavras); // Libera a memória alocada
    return 0;
}