#include <stdio.h> // Biblioteca padrão de entrada e saída (Standard Input/Output)
#include <stdlib.h> // Biblioteca padrão para utilidades gerais (Standard Library)
#include <string.h> // Biblioteca  padrão para manipulação de strings(Standard String Library )
#include <time.h> // Biblioteca para geração de números aleatórios (Time library)

// Estrutura para armazenar os temas e suas respectivas palavras
typedef struct {
    char *tema;         // Nome do tema
    char **palavras;    // Lista de palavras relacionadas ao tema
    int quantidade;     // Número de palavras no tema
} BancoDePalavras;

// Estrutura para armazenar o estado do jogo
typedef struct {
    char *ranking;      // Nome do jogador (ou ranking, se aplicável)
    char *palavraAtual; // Palavra sendo jogada no momento
    char *temaAtual;    // Tema da palavra atual
    int erros;          // Número de erros cometidos pelo jogador
} EstadoDeJogo;

// Função para criar um banco de palavras com um número especificado de temas
BancoDePalavras *criarBancoDePalavras(int numeroTemas) {
    // Alocação dinâmica para armazenar os temas
    BancoDePalavras *banco = (BancoDePalavras *)malloc(numeroTemas * sizeof(BancoDePalavras));
    if (!banco) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o banco de palavras.\n");
        exit(1);
    }

    // Inicializando os campos de cada tema
    for (int i = 0; i < numeroTemas; i++) {
        banco[i].tema = NULL;
        banco[i].palavras = NULL;
        banco[i].quantidade = 0;
    }
    return banco;
}

// Função para adicionar um novo tema ao banco de palavras
void adicionarTema(BancoDePalavras *banco, int indice, const char *tema) {
    banco[indice].tema = strdup(tema); // Duplicar a string do tema
    if (!banco[indice].tema) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o tema.\n");
        exit(1);
    }
}

// Função para adicionar uma nova palavra a um tema específico
void adicionarPalavraAoTema(BancoDePalavras *banco, int indice, const char *palavra) {
    BancoDePalavras *tema = &banco[indice];

    // Aumentar o espaço de memória para armazenar a nova palavra
    tema->quantidade++;
    tema->palavras = (char **)realloc(tema->palavras, tema->quantidade * sizeof(char *));
    if (!tema->palavras) {
        fprintf(stderr, "Erro: Falha ao alocar memória para as palavras do tema.\n");
        exit(1);
    }

    // Adicionar a nova palavra
    tema->palavras[tema->quantidade - 1] = strdup(palavra);
    if (!tema->palavras[tema->quantidade - 1]) {
        fprintf(stderr, "Erro: Falha ao alocar memória para a palavra.\n");
        exit(1);
    }
}

// Função para inicializar o estado do jogo
EstadoDeJogo inicializarEstadoDeJogo() {
    EstadoDeJogo estado;

    // Configurações iniciais do estado
    estado.ranking = strdup("Jogador Anônimo"); // Nome padrão do jogador
    estado.palavraAtual = NULL; // Nenhuma palavra selecionada inicialmente
    estado.temaAtual = NULL;    // Nenhum tema selecionado inicialmente
    estado.erros = 0;           // Nenhum erro no início do jogo

    return estado;
}

// Função para liberar a memória alocada para o banco de palavras
void liberarBancoDePalavras(BancoDePalavras *banco, int numeroTemas) {
    for (int i = 0; i < numeroTemas; i++) {
        free(banco[i].tema); // Liberar memória do tema
        for (int j = 0; j < banco[i].quantidade; j++) {
            free(banco[i].palavras[j]); // Liberar cada palavra
        }
        free(banco[i].palavras); // Liberar a lista de palavras
    }
    free(banco); // Liberar o banco de palavras
}

// Função para liberar a memória alocada para o estado do jogo
void liberarEstadoDeJogo(EstadoDeJogo *estado) {
    free(estado->ranking);
    free(estado->palavraAtual);
    free(estado->temaAtual);
}

// Seleciona um tema e uma palavra aleatórios do banco de palavras
void atribuirTemaEPalavraAleatorios(EstadoDeJogo *estado, BancoDePalavras *banco, int numeroTemas) {
    // Seleciona um tema e uma palavra aleatórios
    int indiceTema = rand() % numeroTemas;
    int indicePalavra = rand() % banco[indiceTema].quantidade;

    // Define o tema e a palavra no estado atual do jogo
    estado->temaAtual = strdup(banco[indiceTema].tema);
    estado->palavraAtual = strdup(banco[indiceTema].palavras[indicePalavra]);
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Define o número de temas e cria o banco de palavras
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

    // Palavras para cada tema
    char *frutas[] = {"Banana", "Maçã", "Uva", "Melancia", "Laranja", "Abacaxi", "Manga", "Pera", "Morango", "Cereja"};
    char *animais[] = {"Gato", "Cachorro", "Leão", "Elefante", "Tigre", "Pato", "Cavalo", "Porco", "Urso", "Cobra"};
    char *comida[] = {"Feijoada", "Costela", "Pizza", "Hambúrguer", "Sushi", "Picanha", "Lasanha", "Salada", "Risoto", "Torta"};
    char *cidades[] = {"João Pessoa", "Recife", "São Paulo", "Rio de Janeiro", "Curitiba", "Fortaleza", "Salvador", "Belém", "Manaus", "Brasília"};
    char *esportes[] = {"Futebol", "Vôlei", "Basquete", "Tênis", "Natação", "Ciclismo", "Corrida", "Boxe", "Judô", "Surf"};
    char *paises[] = {"Brasil", "Canadá", "Japão", "Alemanha", "França", "Itália", "China", "Espanha", "Argentina", "Índia"};
    char *tecnologia[] = {"Computador", "Smartphone", "Internet", "Robótica", "IA", "Blockchain", "Drone", "Satélite", "Hardware", "Software"};

    // Adicionando palavras aos temas
    for (int i = 0; i < 10; i++) {
        adicionarPalavraAoTema(banco, 0, frutas[i]);
        adicionarPalavraAoTema(banco, 1, animais[i]);
        adicionarPalavraAoTema(banco, 2, comida[i]);
        adicionarPalavraAoTema(banco, 3, cidades[i]);
        adicionarPalavraAoTema(banco, 4, esportes[i]);
        adicionarPalavraAoTema(banco, 5, paises[i]);
        adicionarPalavraAoTema(banco, 6, tecnologia[i]);
    }

    // Inicializando o estado do jogo
    EstadoDeJogo estado = inicializarEstadoDeJogo();

    // Selecionando tema e palavra aleatórios
    atribuirTemaEPalavraAleatorios(&estado, banco, numeroTemas);

    // Exibindo tema e palavra selecionados
    printf("Tema Atual: %s\n", estado.temaAtual);
    printf("Palavra Atual: %s\n", estado.palavraAtual);

    // Liberando memória alocada
    liberarBancoDePalavras(banco, numeroTemas);
    liberarEstadoDeJogo(&estado);

    return 0;
}