#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Biblioteca para gerar números aleatórios

// Define a struct para os temas e palavras
typedef struct {
    char *tema;         // Nome do tema
    char **palavras;    // Array de palavras do tema
    int quantidade;     // Quantidade de palavras no tema
} BancoDePalavras;

// Define a struct para o estado do jogo
typedef struct {
    char *ranking;      // Nome do jogador ou ranking do jogo
    char *palavraAtual; // Palavra que está sendo jogada
    char *temaAtual;    // Tema da palavra atual
    int erros;          // Número de erros cometidos
} EstadoDeJogo;

// Função para criar um banco de palavras
BancoDePalavras *criarBancoDePalavras(int numeroTemas) {
    BancoDePalavras *banco = (BancoDePalavras *)malloc(numeroTemas * sizeof(BancoDePalavras));
    if (!banco) {
        fprintf(stderr, "Erro: Falha ao alocar memória para banco de palavras\n");
        exit(1);
    }
    for (int i = 0; i < numeroTemas; i++) {
        banco[i].tema = NULL;
        banco[i].palavras = NULL;
        banco[i].quantidade = 0;
    }
    return banco;
}

// Adiciona um tema ao banco de palavras
void adicionarTema(BancoDePalavras *banco, int indice, const char *tema) {
    banco[indice].tema = strdup(tema);
    if (!banco[indice].tema) {
        fprintf(stderr, "Erro: Falha ao alocar memória para tema\n");
        exit(1);
    }
}

// Adiciona uma palavra a um tema específico
void adicionarPalavraAoTema(BancoDePalavras *banco, int indice, const char *palavra) {
    BancoDePalavras *tema = &banco[indice];
    tema->quantidade++;
    tema->palavras = (char **)realloc(tema->palavras, tema->quantidade * sizeof(char *));
    if (!tema->palavras) {
        fprintf(stderr, "Erro: Falha ao alocar memória para palavras\n");
        exit(1);
    }
    tema->palavras[tema->quantidade - 1] = strdup(palavra);
    if (!tema->palavras[tema->quantidade - 1]) {
        fprintf(stderr, "Erro: Falha ao alocar memória para palavra\n");
        exit(1);
    }
}

// Função para inicializar o estado do jogo
EstadoDeJogo inicializarEstadoDeJogo() {
    EstadoDeJogo estado;
    estado.ranking = strdup("Jogador Anônimo");
    estado.palavraAtual = NULL;
    estado.temaAtual = NULL;
    estado.erros = 0;
    return estado;
}

// Função para liberar memória do banco de palavras
void liberarBancoDePalavras(BancoDePalavras *banco, int numeroTemas) {
    for (int i = 0; i < numeroTemas; i++) {
        free(banco[i].tema);
        for (int j = 0; j < banco[i].quantidade; j++) {
            free(banco[i].palavras[j]);
        }
        free(banco[i].palavras);
    }
    free(banco);
}

// Função para liberar memória do estado do jogo
void liberarEstadoDeJogo(EstadoDeJogo *estado) {
    free(estado->ranking);
    free(estado->palavraAtual);
    free(estado->temaAtual);
}

// Função para selecionar aleatoriamente um tema e palavra
void atribuirTemaEPalavraAleatorios(EstadoDeJogo *estado, BancoDePalavras *banco, int numeroTemas) {
    int indiceTema = rand() % numeroTemas; // Seleciona um tema aleatório
    int indicePalavra = rand() % banco[indiceTema].quantidade; // Seleciona uma palavra aleatória do tema

    estado->temaAtual = strdup(banco[indiceTema].tema);
    estado->palavraAtual = strdup(banco[indiceTema].palavras[indicePalavra]);
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int numeroTemas = 7;
    BancoDePalavras *banco = criarBancoDePalavras(numeroTemas);

    // Adicionando temas
    adicionarTema(banco, 0, "Frutas");
    adicionarTema(banco, 1, "Animais");
    adicionarTema(banco, 2, "Comida");
    adicionarTema(banco, 3, "Cidades");
    adicionarTema(banco, 4, "Esportes");
    adicionarTema(banco, 5, "Países");
    adicionarTema(banco, 6, "Tecnologia");

    // Adicionando palavras aos temas
    char *frutas[] = {"Banana", "Maçã", "Uva", "Melancia", "Laranja", "Abacaxi", "Manga", "Pera", "Morango", "Cereja"};
    char *animais[] = {"Gato", "Cachorro", "Leão", "Elefante", "Tigre", "Pato", "Cavalo", "Porco", "Urso", "Cobra"};
    char *comida[] = {"Feijoada", "Costela", "Pizza", "Hambúrguer", "Sushi", "Picanha", "Lasanha", "Salada", "Risoto", "Torta"};
    char *cidades[] = {"João Pessoa", "Recife", "São Paulo", "Rio de Janeiro", "Curitiba", "Fortaleza", "Salvador", "Belém", "Manaus", "Brasília"};
    char *esportes[] = {"Futebol", "Vôlei", "Basquete", "Tênis", "Natação", "Ciclismo", "Corrida", "Boxe", "Judô", "Surf"};
    char *paises[] = {"Brasil", "Canadá", "Japão", "Alemanha", "França", "Itália", "China", "Espanha", "Argentina", "Índia"};
    char *tecnologia[] = {"Computador", "Smartphone", "Internet", "Robótica", "IA", "Blockchain", "Drone", "Satélite", "Hardware", "Software"};

    for (int i = 0; i < 10; i++) {
        adicionarPalavraAoTema(banco, 0, frutas[i]);
        adicionarPalavraAoTema(banco, 1, animais[i]);
        adicionarPalavraAoTema(banco, 2, comida[i]);
        adicionarPalavraAoTema(banco, 3, cidades[i]);
        adicionarPalavraAoTema(banco, 4, esportes[i]);
        adicionarPalavraAoTema(banco, 5, paises[i]);
        adicionarPalavraAoTema(banco, 6, tecnologia[i]);
    }

    // Inicializando estado do jogo
    EstadoDeJogo estado = inicializarEstadoDeJogo();

    // Atribuindo tema e palavra aleatórios
    atribuirTemaEPalavraAleatorios(&estado, banco, numeroTemas);

    // Exibindo tema e palavra atribuídos
    printf("Tema Atual: %s\n", estado.temaAtual);
    printf("Palavra Atual: %s\n", estado.palavraAtual);

    // Liberando memória
    liberarBancoDePalavras(banco, numeroTemas);
    liberarEstadoDeJogo(&estado);

    return 0;
}