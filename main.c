#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>



//Estrutura do banco de palavras
typedef struct BancoDePalavras {
    char *tema;
    char **palavras;
    int qtd_palavras;
} bdPlvr;


//Inicializando função sortearTemaEPalavra
void sortearTemaEPalavra(bdPlvr *banco, int num_temas, char **tema, char **palavra);

//Função para criar um banco de palavras
bdPlvr *criarBancoPlvr(int num_temas) {
    bdPlvr *banco = (bdPlvr *)malloc(num_temas * sizeof(bdPlvr)); //Alocando as struct bdPlvr
    //Verificando se a alocação foi feita
    if (!banco) {
        printf("Falha ao alocar memoria para o banco de palavras.\n");
        exit(1);
    }
    //Inicializando tema/palavras/qtd_palavras dos bancos de palavras criados, que são baseado em num_temas.
    for (int i = 0; i < num_temas; i++) {
        banco[i].tema = NULL;
        banco[i].palavras = NULL;
        banco[i].qtd_palavras = 0;
    }
    //Retorna o banco de dados criado.
    return banco;
}

//Adicionar um tema ao banco de palavras
void adicionarTema(bdPlvr *banco, int indice_tema, char *tema) {

    banco[indice_tema].tema = strdup(tema); //Adicionando o tema no banco[indice]

    //Verificando se o tema foi duplicado
    if (!banco[indice_tema].tema) {
        printf("Falha ao duplicar o tema.\n");
        exit(1);
    }

    banco[indice_tema].palavras = NULL; //Ainda não tem palavra
    banco[indice_tema].qtd_palavras = 0; //Ainda não tem palavra
}

// Função para adicionar uma palavra a um tema no banco.
void adicionarPalavraAoTema(bdPlvr *banco, int indice_tema, char *palavra) {
    banco[indice_tema].palavras = (char **)realloc(banco[indice_tema].palavras, (banco[indice_tema].qtd_palavras + 1) * sizeof(char *)); //Realocando o array dentro de banco de palavras para adicionar mais 1 palavra;
    //Verificar se a realocação foi feita com sucesso
    if (!banco[indice_tema].palavras) {
        printf("Erro ao realocar memoria para palavras.\n");
        exit(1);
    }
    //Copiando a palavra para dneotro do array palavra dentro do banco[indice]
    banco[indice_tema].palavras[banco[indice_tema].qtd_palavras] = strdup(palavra);

    //Verificando se foi copiado com sucesso
    if (!banco[indice_tema].palavras[banco[indice_tema].qtd_palavras]) {
        printf("Falha ao duplicar a palavra.\n");
        exit(1);
    }

    //Aumentando o contador de qtd_palavras dentro do banco[indice]
    banco[indice_tema].qtd_palavras++;
}

//Funçaõ para liberar memoria alocada para o banco de palavras.
void liberarBanco(bdPlvr *banco, int num_temas) {
    for (int i = 0; i < num_temas; i++) {
        free(banco[i].tema);
        for (int j = 0; j < banco[i].qtd_palavras; j++) {
            free(banco[i].palavras[j]);
        }
        free(banco[i].palavras);
    }
    free(banco);
}

//Funcao para exibir o menu principal.
void menu(bdPlvr **banco, int *num_temas) {
    int opcao;
    char *criadores[] = {"Fernando", "Italo", "Marcelo", "Alik", "Luy"};

    //Enquanto o comando do usuário não for válida ele continuará exibindo o menu e pedindo o comando, quando o comando for válido ele dá break.
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1. Jogar\n");
        printf("2. Ver ranking\n");
        printf("3. Listar Temas\n");
        printf("4. Adicionar Novo Tema e Palavras\n");
        printf("5. Creditos\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: \n");
        printf("---> ");

        //Verificando se o comando do usuário é um número e menor igual a 6.
        if (scanf("%d", &opcao) == 1 && opcao >= 1 && opcao <= 6) {
            while (getchar() != '\n'); // Limpa o buffer
            break;
        } else {
            printf("\nComando invalido. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer
        }
    }

    //Switch case da escolha do usuário
    switch (opcao) {

        //Jogar
        // A palavra e o tema são sorteadores
        case 1: {
            char *tema_sorteado;
            char *palavra_sorteada;

            sortearTemaEPalavra(*banco, *num_temas, &tema_sorteado, &palavra_sorteada);

            printf("Tema sorteado foi %s e a palavra sorteada foi %s",tema_sorteado,palavra_sorteada);
            break;

            //------------------------------------------ALIK---------------------
















        case 2:
            printf("Opcao Ver Ranking ainda nao implementada.\n");
            break;

        //Exibir temas
        // Os temas disponiveis são exibidos.
        case 3:
            system("cls");
            printf("\n=== Temas Disponiveis ===\n");
            for (int i = 0; i < *num_temas; i++) {
                printf("%d. %s\n", i + 1, (*banco)[i].tema);
            }
            break;
        }

        //Adicionar novo tema
        case 4: {
            system("cls");
            char novo_tema[50];
            int qtd_novas_palavras;

            // Verificar se a entrada do usuário é válida.
            while (1) {
                printf("\nQuantas palavras deseja adicionar ao novo tema? "); //Obtendo a quantidade de palavras que o novo tema terá.
                if (scanf("%d", &qtd_novas_palavras) == 1 && qtd_novas_palavras > 0) {
                    while (getchar() != '\n'); // Limpa o buffer de entrada
                    break; // Entrada válida, sair do loop
                } else {
                    printf("Entrada inválida. Tente novamente: ");
                    while (getchar() != '\n'); // Limpa o buffer de entrada
                }
            }

            printf("\nInsira o nome do novo tema: ");   //Obtendo o nome do novo tema

            //Verifica se o que foi digitado pelo usuário não é nulo
            if (fgets(novo_tema, sizeof(novo_tema), stdin) != NULL) {
                novo_tema[strcspn(novo_tema, "\n")] = '\0';

                if (strlen(novo_tema) > 0) {
                    //Realocando memória para adicionar um novo tema.
                    bdPlvr *novo_banco = realloc(*banco, (*num_temas + 1) * sizeof(bdPlvr));
                    //Verificando se a realocação foi feita com sucesso.
                    if (!novo_banco) {
                        printf("Erro ao realocar banco de palavras.\n");
                        return;
                    }
                    //Incrementando em *banco
                    *banco = novo_banco;

                    //Adicionando o tema
                    adicionarTema(*banco, *num_temas, novo_tema);

                    //Loop para adicionar as palavras ao tema
                    for (int i = 0; i < qtd_novas_palavras; i++) {
                        char palavra[50];
                        printf("%dª Palavra: ", i + 1);
                        //Verificando se o palavra do usuário não é nulo
                        if (fgets(palavra, sizeof(palavra), stdin) != NULL) {
                            palavra[strcspn(palavra, "\n")] = '\0';
                            if (strlen(palavra) > 0) {
                                //Adicionando as palavras ao tema que o usuário criou.
                                adicionarPalavraAoTema(*banco, *num_temas, palavra);
                            } else {
                                printf("Palavra invalida. Tente novamente.\n");
                                i--;
                            }
                        }
                    }
                    (*num_temas)++;
                    printf("\nTema '%s' adicionado com sucesso!\n", novo_tema);
                } else {
                    printf("O tema nao pode estar vazio.\n");
                }
            }
            break;
        }

        case 5:
            system("cls");
            printf("\n=== Creditos ===\n");
            for (int i = 0; i < 5; i++) {
                printf("- %s\n", criadores[i]);
            }
            break;

        case 6:
            system("cls");
            printf("\nSaindo...\n");
            exit(0);
    }
}

//Função para sortear os temas e palavras.
void sortearTemaEPalavra(bdPlvr *banco, int num_temas, char **tema, char **palavra) {
    if (num_temas == 0) {
        *tema = NULL;
        *palavra = NULL;
        return;
    }

    // Sorteia um tema aleatoriamente
    int indice_tema = rand() % num_temas;

    // Verifica se o tema tem palavras associadas
    if (banco[indice_tema].qtd_palavras == 0) {
        *tema = NULL;
        *palavra = NULL;
        return;
    }

    // Sorteia uma palavra aleatoriamente dentro do tema selecionado
    int indice_palavra = rand() % banco[indice_tema].qtd_palavras;

    // Retorna os resultados
    *tema = banco[indice_tema].tema;
    *palavra = banco[indice_tema].palavras[indice_palavra];
}


int main() {
    setlocale(LC_ALL, "");

    int qtd_palavras = 5;

    //Lista de temas predefinidos
    char *lista_temas_pred[] = {
    "Veiculos", "Animais", "Frutas", "Paises", "Objetos", "Corpo Humano", "Cores", "Instrumentos Musicais", "Esportes", "Tecnologia"
    };

    //Lista de palavras predefinidas.
    char *lista_palavras_pred[][5] = {
        {"Carro", "Moto", "Barco", "Aviao", "Helicoptero"},           // Veiculos
        {"Cachorro", "Gato", "Leao", "Macaco", "Flamingo"},            // Animais
        {"Maca", "Banana", "Laranja", "Mango", "Uva"},                 // Frutas
        {"Brasil", "Estados Unidos", "China", "Franca", "Japao"},      // Paises
        {"Cadeira", "Mesa", "Televisao", "Computador", "Lampada"},     // Objetos
        {"Coracao", "Pulmao", "Cerebro", "Estomago", "Rim"},           // Corpo Humano
        {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"},             // Cores
        {"Violao", "Piano", "Guitarra", "Bateria", "Flauta"},          // Instrumentos Musicais
        {"Futebol", "Basketball", "Volei", "Natacao", "Ciclismo"},     // Esportes
        {"Computador", "Smartphone", "Tablet", "Router", "Impressora"} // Tecnologia
    };

    //Obtendo o quantidade de temas, pelos temas predefinido.
    int num_temas = sizeof(lista_temas_pred) / sizeof(lista_temas_pred[0]);

    //Criar o banco de palavras com base em num_temas
    bdPlvr *banco = criarBancoPlvr(num_temas);

    //Adicionando os temas no banco de palavras
    for (int i = 0; i < num_temas; i++) {
        adicionarTema(banco, i, lista_temas_pred[i]); //Tema
        for (int j = 0; j < qtd_palavras; j++) {
            adicionarPalavraAoTema(banco, i, lista_palavras_pred[i][j]); //Adicionando as palavras.
        }
    }

    //Loop do menu
    while(1){
    menu(&banco, &num_temas);
    }

    //Liberando o espaço de memória do banco de palavras.
    liberarBanco(banco, num_temas);
    return 0;
}
