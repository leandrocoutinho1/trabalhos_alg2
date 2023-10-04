#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX_FILIAIS 10
#define TRIMESTRES 4

// Estrutura para representar uma venda de um produto em um trimestre
typedef struct {
    float vendas[TRIMESTRES];
} Venda;

// Função para encontrar o produto mais vendido por filial
int encontrarProdutoMaisVendidoPorFilial(Venda*** matriz, int filial, int trimestres, int nProdutos) {
    int produtoMaisVendido = 0;
    float maiorVenda = matriz[0][0][filial].vendas[0];

    for (int produto = 0; produto < nProdutos; produto++) {
        for (int trimestre = 0; trimestre < trimestres; trimestre++) {
            if (matriz[produto][trimestre][filial].vendas[trimestre] > maiorVenda) {
                maiorVenda = matriz[produto][trimestre][filial].vendas[trimestre];
                produtoMaisVendido = produto;
            }
        }
    }

    return produtoMaisVendido;
}

// Função para encontrar a filial que mais vende produtos
int encontrarFilialMaisVendida(int nProdutos, int nFiliais, Venda*** matriz, int trimestre) {
    int filialMaisVendida = 0;
    float maiorVenda = 0;

    for (int filial = 0; filial < nFiliais; filial++) {
        float totalVendas = 0;
        for (int produto = 0; produto < nProdutos; produto++) {
            totalVendas += matriz[produto][trimestre - 1][filial].vendas[trimestre - 1];
        }

        if (totalVendas > maiorVenda) {
            maiorVenda = totalVendas;
            filialMaisVendida = filial;
        }
    }

    return filialMaisVendida;
}

// Função para encontrar o produto mais vendido globalmente
int encontrarProdutoMaisVendidoGlobal(int nProdutos, int nFiliais, Venda*** matriz) {
    int produtoMaisVendido = 0;
    float maiorVenda = 0;

    for (int produto = 0; produto < nProdutos; produto++) {
        float totalVendas = 0;
        for (int filial = 0; filial < nFiliais; filial++) {
            for (int trimestre = 0; trimestre < TRIMESTRES; trimestre++) {
                totalVendas += matriz[produto][trimestre][filial].vendas[trimestre];
            }
        }

        if (totalVendas > maiorVenda) {
            maiorVenda = totalVendas;
            produtoMaisVendido = produto;
        }
    }

    return produtoMaisVendido;
}

// Função para encontrar a filial que mais vende globalmente
int encontrarFilialMaisVendidaGlobal(int nProdutos, int nFiliais, Venda*** matriz) {
    int filialMaisVendida = 0;
    float maiorVenda = 0;

    for (int filial = 0; filial < nFiliais; filial++) {
        float totalVendas = 0;
        for (int produto = 0; produto < nProdutos; produto++) {
            for (int trimestre = 0; trimestre < TRIMESTRES; trimestre++) {
                totalVendas += matriz[produto][trimestre][filial].vendas[trimestre];
            }
        }

        if (totalVendas > maiorVenda) {
            maiorVenda = totalVendas;
            filialMaisVendida = filial;
        }
    }

    return filialMaisVendida;
}

// Função para encontrar o melhor trimestre
int encontrarMelhorTrimestre(int nProdutos, int nFiliais, Venda*** matriz) {
    int melhorTrimestre = 0;
    float maiorVenda = 0;

    for (int trimestre = 0; trimestre < TRIMESTRES; trimestre++) {
        float totalVendas = 0;
        for (int produto = 0; produto < nProdutos; produto++) {
            for (int filial = 0; filial < nFiliais; filial++) {
                totalVendas += matriz[produto][trimestre][filial].vendas[trimestre];
            }
        }

        if (totalVendas > maiorVenda) {
            maiorVenda = totalVendas;
            melhorTrimestre = trimestre + 1; // Trimestre começa de 1
        }
    }

    return melhorTrimestre;
}

// Função para inserir o catálogo de produtos
void inserirCatalogoProdutos(char** catalogoProdutos, int nProdutos) {
    for (int i = 0; i < nProdutos; i++) {
        printf("Digite o nome do produto %d: ", i + 1);
        scanf("%s", catalogoProdutos[i]);
    }
}

// Função para inserir o catálogo de filiais
void inserirCatalogoFiliais(char** catalogoFiliais, int nFiliais) {
    for (int i = 0; i < nFiliais; i++) {
        printf("Digite o nome da filial %d: ", i + 1);
        scanf("%s", catalogoFiliais[i]);
    }
}

// Função para inserir venda de um produto/trimestre
void inserirVendaProdutoTrimestre(Venda*** matriz, char*** catalogoProdutos, int nProdutos, char*** catalogoFiliais, int nFiliais) {
    int trimestre;
    char produto[50];

    printf("Digite o trimestre (1-4): ");
    scanf("%d", &trimestre);

    printf("Digite o nome do produto: ");
    scanf("%s", produto);

    int produtoIndex = -1;
    for (int i = 0; i < nProdutos; i++) {
        if (strcmp(produto, (*catalogoProdutos)[i]) == 0) {
            produtoIndex = i;
            break;
        }
    }

    if (produtoIndex == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    for (int filial = 0; filial < nFiliais; filial++) {
        printf("Digite as vendas para a filial %s: ", (*catalogoFiliais)[filial]);
        scanf("%f", &matriz[produtoIndex][trimestre - 1][filial].vendas[trimestre - 1]);
    }
}

// Função para inserir venda de um produto/filial
void inserirVendaProdutoFilial(Venda*** matriz, char*** catalogoProdutos, int nProdutos, char*** catalogoFiliais, int nFiliais) {
    char filial[50];
    char produto[50];

    printf("Digite o nome da filial: ");
    scanf("%s", filial);

    printf("Digite o nome do produto: ");
    scanf("%s", produto);

    int filialIndex = -1;
    for (int i = 0; i < nFiliais; i++) {
        if (strcmp(filial, (*catalogoFiliais)[i]) == 0) {
            filialIndex = i;
            break;
        }
    }

    int produtoIndex = -1;
    for (int i = 0; i < nProdutos; i++) {
        if (strcmp(produto, (*catalogoProdutos)[i]) == 0) {
            produtoIndex = i;
            break;
        }
    }

    if (filialIndex == -1 || produtoIndex == -1) {
        printf("Filial ou produto nao encontrado!\n");
        return;
    }

    for (int trimestre = 0; trimestre < TRIMESTRES; trimestre++) {
        printf("Digite as vendas para o trimestre %d: ", trimestre + 1);
        scanf("%f", &matriz[produtoIndex][trimestre][filialIndex].vendas[trimestre]);
    }
}

// Função para encontrar o produto mais vendido por filial
void produtoMaisVendidoPorFilial(Venda*** matriz, char*** catalogoProdutos, int nProdutos, char*** catalogoFiliais, int nFiliais) {
    char filial[50];

    printf("Digite o nome da filial: ");
    scanf("%s", filial);

    int filialIndex = -1;
    for (int i = 0; i < nFiliais; i++) {
        if (strcmp(filial, (*catalogoFiliais)[i]) == 0) {
            filialIndex = i;
            break;
        }
    }

    if (filialIndex == -1) {
        printf("Filial nao encontrada!\n");
        return;
    }

    int produtoMaisVendido = encontrarProdutoMaisVendidoPorFilial(matriz, filialIndex, TRIMESTRES, nProdutos);
    printf("Produto mais vendido na filial %s: %s\n", filial, (*catalogoProdutos)[produtoMaisVendido]);
}

// Função para encontrar a filial que mais vende produtos
void filialMaisVendeProdutos(Venda*** matriz, char*** catalogoFiliais, int nFiliais, int nProdutos) {
    int trimestre;

    printf("Digite o trimestre (1-4): ");
    scanf("%d", &trimestre);

    int filialMaisVendida = encontrarFilialMaisVendida(nProdutos, nFiliais, matriz, trimestre);
    printf("Filial que mais vende produtos no trimestre %d: %s\n", trimestre, (*catalogoFiliais)[filialMaisVendida]);
}

// Função para encontrar o produto mais vendido globalmente
void produtoMaisVendidoGlobal(Venda*** matriz, char*** catalogoProdutos, int nProdutos, char*** catalogoFiliais, int nFiliais) {
    int produtoMaisVendido = encontrarProdutoMaisVendidoGlobal(nProdutos, nFiliais, matriz);
    printf("Produto mais vendido globalmente: %s\n", (*catalogoProdutos)[produtoMaisVendido]);
}

// Função para encontrar a filial que mais vende globalmente
void filialMaisVendeGlobal(Venda*** matriz, char*** catalogoFiliais, int nFiliais, int nProdutos) {
    int filialMaisVendida = encontrarFilialMaisVendidaGlobal(nProdutos, nFiliais, matriz);
    printf("Filial que mais vende globalmente: %s\n", (*catalogoFiliais)[filialMaisVendida]);
}

// Função para encontrar o melhor trimestre
void melhorTrimestre(Venda*** matriz, int nFiliais, int nProdutos) {
    int melhorTri = encontrarMelhorTrimestre(nProdutos, nFiliais, matriz);
    printf("Melhor trimestre: %d\n", melhorTri);
}

// Função para inserir um novo produto
void inserirNovoProduto(Venda*** matriz, char*** catalogoProdutos, int* nProdutos, int nFiliais) {
    if (*nProdutos >= MAX_PRODUTOS) {
        printf("Limite maximo de produtos atingido!\n");
        return;
    }

    printf("Digite o nome do novo produto: ");
    scanf("%s", (*catalogoProdutos)[*nProdutos]);

    for (int trimestre = 0; trimestre < TRIMESTRES; trimestre++) {
        for (int filial = 0; filial < nFiliais; filial++) {
            printf("Digite as vendas para a filial %s no trimestre %d: ", (*catalogoFiliais)[filial], trimestre + 1);
            scanf("%f", &matriz[*nProdutos][trimestre][filial].vendas[trimestre]);
        }
    }

    (*nProdutos)++;
}

// Função para inserir uma nova filial
void inserirNovaFilial(Venda*** matriz, char*** catalogoFiliais, int nProdutos, int* nFiliais) {
    if (*nFiliais >= MAX_FILIAIS) {
        printf("Limite maximo de filiais atingido!\n");
        return;
    }

    printf("Digite o nome da nova filial: ");
    scanf("%s", (*catalogoFiliais)[*nFiliais]);

    for (int produto = 0; produto < nProdutos; produto++) {
        for (int trimestre = 0; trimestre < TRIMESTRES; trimestre++) {
            printf("Digite as vendas para o produto %s no trimestre %d: ", (*catalogoProdutos)[produto], trimestre + 1);
            scanf("%f", &matriz[produto][trimestre][*nFiliais].vendas[trimestre]);
        }
    }

    (*nFiliais)++;
}

// Função para remover um produto
void removerProduto(Venda*** matriz, char*** catalogoProdutos, int* nProdutos, int nFiliais) {
    char produto[50];

    printf("Digite o nome do produto a ser removido: ");
    scanf("%s", produto);

    int produtoIndex = -1;
    for (int i = 0; i < *nProdutos; i++) {
        if (strcmp(produto, (*catalogoProdutos)[i]) == 0) {
            produtoIndex = i;
            break;
        }
    }

    if (produtoIndex == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }

    // Move todos os produtos após o produto removido para preencher a lacuna
    for (int i = produtoIndex; i < (*nProdutos) - 1; i++) {
        strcpy((*catalogoProdutos)[i], (*catalogoProdutos)[i + 1]);

        for (int trimestre = 0; trimestre < TRIMESTRES; trimestre++) {
            for (int filial = 0; filial < nFiliais; filial++) {
                matriz[i][trimestre][filial] = matriz[i + 1][trimestre][filial];
            }
        }
    }

    (*nProdutos)--;
    printf("Produto removido com sucesso!\n");
}

int main() {
    int nProdutos = 0;
    int nFiliais = 0;
    char* catalogoProdutos[MAX_PRODUTOS];
    char* catalogoFiliais[MAX_FILIAIS];
    Venda*** matriz = NULL;

    for (int i = 0; i < MAX_PRODUTOS; i++) {
        catalogoProdutos[i] = (char*)malloc(50 * sizeof(char));
    }

    for (int i = 0; i < MAX_FILIAIS; i++) {
        catalogoFiliais[i] = (char*)malloc(50 * sizeof(char));
    }

    printf("Bem-vindo ao sistema Market++ de controle de estoque!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inicializacao do sistema\n");
        printf("2. Catalogo do Sistema\n");
        printf("3. Catalogo de filiais\n");
        printf("4. Inserir venda de um produto/trimestre\n");
        printf("5. Inserir venda de um produto/filial\n");
        printf("6. Produto mais vendido por filial\n");
        printf("7. Filial que mais vende produtos\n");
        printf("8. Produto mais vendido\n");
        printf("9. Filial que mais vende\n");
        printf("10. Melhor trimestre\n");
        printf("11. Inserir novo produto\n");
        printf("12. Inserir nova filial\n");
        printf("13. Remover produto\n");
        printf("0. Sair\n");

        int escolha;
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o numero de produtos: ");
                scanf("%d", &nProdutos);
                printf("Digite o numero de filiais: ");
                scanf("%d", &nFiliais);

                // Aloca memória para a matriz de vendas
                matriz = (Venda***)malloc(nProdutos * sizeof(Venda**));
                for (int i = 0; i < nProdutos; i++) {
                    matriz[i] = (Venda**)malloc(TRIMESTRES * sizeof(Venda*));
                    for (int j = 0; j < TRIMESTRES; j++) {
                        matriz[i][j] = (Venda*)malloc(nFiliais * sizeof(Venda));
                    }
                }

                break;

            case 2:
                inserirCatalogoProdutos(catalogoProdutos, nProdutos);
                break;

            case 3:
                inserirCatalogoFiliais(catalogoFiliais, nFiliais);
                break;

            case 4:
                inserirVendaProdutoTrimestre(matriz, &catalogoProdutos, nProdutos, &catalogoFiliais, nFiliais);
                break;

            case 5:
                inserirVendaProdutoFilial(matriz, &catalogoProdutos, nProdutos, &catalogoFiliais, nFiliais);
                break;

            case 6:
                produtoMaisVendidoPorFilial(matriz, &catalogoProdutos, nProdutos, &catalogoFiliais, nFiliais);
                break;

            case 7:
                filialMaisVendeProdutos(matriz, &catalogoFiliais, nFiliais, nProdutos);
                break;

            case 8:
                produtoMaisVendidoGlobal(matriz, &catalogoProdutos, nProdutos, &catalogoFiliais, nFiliais);
                break;

            case 9:
                filialMaisVendeGlobal(matriz, &catalogoFiliais, nFiliais, nProdutos);
                break;

            case 10:
                melhorTrimestre(matriz, nFiliais, nProdutos);
                break;

            case 11:
                inserirNovoProduto(matriz, &catalogoProdutos, &nProdutos, nFiliais);
                break;

            case 12:
                inserirNovaFilial(matriz, &catalogoFiliais, nProdutos, &nFiliais);
                break;

            case 13:
                removerProduto(matriz, &catalogoProdutos, &nProdutos, nFiliais);
                break;

            case 0:
                // Libere a memória alocada
                for (int i = 0; i < nProdutos; i++) {
                    for (int j = 0; j < TRIMESTRES; j++) {
                        free(matriz[i][j]);
                    }
                    free(matriz[i]);
                }
                free(matriz);

                for (int i = 0; i < nProdutos; i++) {
                    free(catalogoProdutos[i]);
                }

                for (int i = 0; i < nFiliais; i++) {
                    free(catalogoFiliais[i]);
                }

                return 0;

            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
