#include <stdio.h> // Biblioteca padrão de entrada e saída (Standard Input/Output)
#include <stdlib.h> // Biblioteca padrão para utilidades gerais (Standard Library)
#include <string.h> // Biblioteca  padrão para manipulação de strings(Standard String Library )
#include <time.h> // Biblioteca para geração de números aleatórios (Time library)

// Estrutura para armazenar os temas e suas palavras
typedef struct {
    char *tema;          // Nome do tema
    char **palavras;     // Lista de palavras associadas ao tema
    int quantidade;      // Número de palavras no tema
} BancoDePalavras;

// Estrutura para armazenar o estado atual do jogo
typedef struct {
    char *ranking;       // Nome do jogador
    char *palavraAtual;  // Palavra selecionada no momento
    char *temaAtual;     // Tema da palavra atual
    int erros;           // Número de erros cometidos pelo jogador
} EstadoDeJogo;

// Funções para gerenciar o banco de palavras
BancoDePalavras *criarBancoDePalavras(int *numeroTemas);
void adicionarTema(BancoDePalavras **banco, int *numeroTemas, const char *tema);
void adicionarPalavraAoTema(BancoDePalavras *banco, int indice, const char *palavra);
int buscarTema(BancoDePalavras *banco, int numeroTemas, const char *tema);
void liberarBancoDePalavras(BancoDePalavras *banco, int numeroTemas);

// Funções para gerenciar o estado do jogo
EstadoDeJogo inicializarEstadoDeJogo();
void liberarEstadoDeJogo(EstadoDeJogo *estado);
void selecionarTemaEPalavra(EstadoDeJogo *estado, BancoDePalavras *banco, int numeroTemas);

// Funções interativas
void menuAdicionarTemaPalavra(BancoDePalavras **banco, int *numeroTemas);

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Inicializa o banco de palavras
    int numeroTemas = 0;
    BancoDePalavras *banco = criarBancoDePalavras(&numeroTemas);

    // Inicializa o estado do jogo
    EstadoDeJogo estado = inicializarEstadoDeJogo();

    int escolha;
    do {
        // Exibe o menu principal
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Adicionar Tema ou Palavra\n");
        printf("2. Selecionar Tema e Palavra (Jogar)\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                // Adicionar tema ou palavra
                menuAdicionarTemaPalavra(&banco, &numeroTemas);
                break;
            case 2:
                // Jogar com tema e palavra selecionados
                if (numeroTemas == 0) {
                    printf("Nenhum tema disponível. Adicione temas antes de jogar.\n");
                } else {
                    selecionarTemaEPalavra(&estado, banco, numeroTemas);
                    printf("Tema selecionado: %s\n", estado.temaAtual);
                    printf("Palavra selecionada: %s\n", estado.palavraAtual);
                }
                break;
            case 3:
                printf("Encerrando o programa. Até a próxima!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (escolha != 3);

    // Libera a memória antes de encerrar o programa
    liberarBancoDePalavras(banco, numeroTemas);
    liberarEstadoDeJogo(&estado);

    return 0;
}

// Cria o banco de palavras vazio
BancoDePalavras *criarBancoDePalavras(int *numeroTemas) {
    *numeroTemas = 0; // Inicialmente não há temas
    return NULL;      // Retorna um ponteiro nulo
}

// Adiciona um novo tema ao banco de palavras
void adicionarTema(BancoDePalavras **banco, int *numeroTemas, const char *tema) {
    (*numeroTemas)++; // Incrementa o número de temas
    *banco = realloc(*banco, (*numeroTemas) * sizeof(BancoDePalavras)); // Redimensiona o banco
    if (!*banco) {
        fprintf(stderr, "Erro ao alocar memória para o banco de palavras.\n");
        exit(1);
    }

    BancoDePalavras *novoTema = &(*banco)[*numeroTemas - 1]; // Aponta para o novo tema
    novoTema->tema = strdup(tema);    // Copia o nome do tema
    novoTema->palavras = NULL;        // Nenhuma palavra associada inicialmente
    novoTema->quantidade = 0;         // Nenhuma palavra ainda

    printf("Tema '%s' adicionado com sucesso!\n", tema);
}

// Adiciona uma palavra a um tema existente
void adicionarPalavraAoTema(BancoDePalavras *banco, int indice, const char *palavra) {
    BancoDePalavras *tema = &banco[indice];
    tema->quantidade++; // Incrementa o número de palavras
    tema->palavras = realloc(tema->palavras, tema->quantidade * sizeof(char *)); // Redimensiona o array de palavras
    tema->palavras[tema->quantidade - 1] = strdup(palavra); // Copia a nova palavra
    printf("Palavra '%s' adicionada ao tema '%s'.\n", palavra, tema->tema);
}

// Busca um tema pelo nome e retorna seu índice
int buscarTema(BancoDePalavras *banco, int numeroTemas, const char *tema) {
    for (int i = 0; i < numeroTemas; i++) {
        if (strcmp(banco[i].tema, tema) == 0) {
            return i; // Retorna o índice se encontrar o tema
        }
    }
    return -1; // Retorna -1 se o tema não existir
}

// Libera a memória alocada para o banco de palavras
void liberarBancoDePalavras(BancoDePalavras *banco, int numeroTemas) {
    for (int i = 0; i < numeroTemas; i++) {
        free(banco[i].tema); // Libera o nome do tema
        for (int j = 0; j < banco[i].quantidade; j++) {
            free(banco[i].palavras[j]); // Libera cada palavra
        }
        free(banco[i].palavras); // Libera o array de palavras
    }
    free(banco); // Libera o próprio banco
}

// Inicializa o estado do jogo
EstadoDeJogo inicializarEstadoDeJogo() {
    EstadoDeJogo estado;
    estado.ranking = strdup("Jogador Anônimo");
    estado.palavraAtual = NULL;
    estado.temaAtual = NULL;
    estado.erros = 0;
    return estado;
}

// Libera a memória alocada para o estado do jogo
void liberarEstadoDeJogo(EstadoDeJogo *estado) {
    free(estado->ranking);
    free(estado->palavraAtual);
    free(estado->temaAtual);
}

// Seleciona um tema e uma palavra aleatórios para o jogo
void selecionarTemaEPalavra(EstadoDeJogo *estado, BancoDePalavras *banco, int numeroTemas) {
    int indiceTema = rand() % numeroTemas;                // Seleciona um tema aleatório
    int indicePalavra = rand() % banco[indiceTema].quantidade; // Seleciona uma palavra aleatória
    free(estado->temaAtual); // Libera qualquer tema anterior
    free(estado->palavraAtual); // Libera qualquer palavra anterior
    estado->temaAtual = strdup(banco[indiceTema].tema);   // Copia o tema selecionado
    estado->palavraAtual = strdup(banco[indiceTema].palavras[indicePalavra]); // Copia a palavra selecionada
}

// Menu para adicionar temas e palavras
void menuAdicionarTemaPalavra(BancoDePalavras **banco, int *numeroTemas) {
    char tema[50], palavra[50];
    printf("Digite o nome do tema: ");
    scanf(" %[^\n]", tema);

    int indice = buscarTema(*banco, *numeroTemas, tema);
    if (indice == -1) { // Se o tema não existir, cria um novo
        adicionarTema(banco, numeroTemas, tema);
        indice = *numeroTemas - 1;
    }

    printf("Digite a palavra a ser adicionada ao tema '%s': ", tema);
    scanf(" %[^\n]", palavra);
    adicionarPalavraAoTema(*banco, indice, palavra);
}