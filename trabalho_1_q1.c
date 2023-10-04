//Codigo fonte criado por alunos de SI da UFU:
//Diogo Arantes Borges Andrade
//Bruno Henrique Oliveira
//Leandro Coutinho Cesário Junior

#include <stdio.h>
#include <stdlib.h>

#define MAX_LARGURA 300
#define MAX_COMP 1000

// Etrutura da data que ira para a Estrutura do raio
typedef struct
{
    int dia, mes, ano;
} Data;
// Estrutura do raio
typedef struct
{
    int intensidade;
    char condicoes_tempo[20];
    Data data;
} Raio;

// Função para marcar a queda de um raio em uma posição específica
void marcarRaio(Raio **cidade, int largura, int comp)
{
    int x, y;
    
    printf("Digite as coordenadas X e Y onde o raio caiu: ");
    scanf("%d %d", &x, &y);

    if (x < 0 || x >= largura || y < 0 || y >= comp)
    {
        printf("Coordenadas fora dos limites da cidade!\n");
        return;
    }

    // Usando aritmética de ponteiros para acessar a posição da cidade
    Raio *raio = cidade[x] + y;
    // Marcação se o raio caiu no mesmo lugar
    if (raio->intensidade > 0)
    {
        printf("Um raio caiu duas vezes no mesmo lugar!\n");
        exit(1);
    }

    printf("Digite a data:\n");
    printf("Dia: ");
    scanf("%d", &raio->data.dia);
    printf("Mes: ");
    scanf("%d", &raio->data.mes);
    printf("Ano: ");
    scanf("%d", &raio->data.ano);
    printf("Digite a intensidade do raio representada por uma escala de 1 a 10: ");
    scanf("%d", &raio->intensidade);

    printf("Digite as condicoes do tempo: ");
    scanf("%s", raio->condicoes_tempo);
}

// Função para contar quantos raios já caíram na cidade
int qntRaiosJaCairam(Raio **cidade, int largura, int comp)
{
    int contador = 0;
    for (int x = 0; x < largura; x++)
    {
        for (int y = 0; y < comp; y++)
        {
            // Usando aritmética de ponteiros para acessar a posição da cidade
            Raio *raio = cidade[x] + y;
            if (raio->intensidade > 0)
            {
                contador++;
            }
        }
    }
    return contador;
}

// Função para contar quantas áreas não foram afetadas por raios
int qntAreasNaoAfet(Raio **cidade, int largura, int comp)
{
    int contador = 0;
    for (int x = 0; x < largura; x++)
    {
        for (int y = 0; y < comp; y++)
        {
            // Usando aritmética de ponteiros para acessar a posição da cidade
            Raio *raio = cidade[x] + y;
            if (raio->intensidade == 0)
            {
                contador++;
            }
        }
    }
    return contador;
}

// Função para imprimir a matriz da cidade com os raios marcados com "X"
void imprimirMatriz(Raio **cidade, int largura, int comp)
{
    for (int x = 0; x < largura; x++)
    {
        for (int y = 0; y < comp; y++)
        {
            // Usando aritmética de ponteiros para acessar a posição da cidade
            Raio *raio = cidade[x] + y;
            if (raio->intensidade > 0)
            {
                printf(" [X] ");
            }
            else
            {
                printf(" [ ] ");
            }
        }
        printf("\n");
    }
}

int main()
{
    int largura, comp;
    // Fornecer o tamnho da cidade
    do
    {
        printf("\nDigite a largura da cidade (largura MAX = 300): ");
        scanf("%d", &largura);
        printf("\nDigite o comprimento da cidade (comprimento MAX = 1000): ");
        scanf("%d", &comp);

        if (largura > MAX_LARGURA || comp > MAX_COMP)
        {
            printf("\nOs limites da cidade excedem o maximo permitido.\n");
        }
    } while (largura > MAX_LARGURA || comp > MAX_COMP);

    // Alocação dinâmica da matriz da cidade
    Raio **cidade = (Raio **)calloc(largura, sizeof(Raio *));
    for (int x = 0; x < largura; x++)
    {
        cidade[x] = (Raio *)calloc(comp, sizeof(Raio));
    }
    // Menu de escolha
    int opcao;
    do
    {
        printf("\nMenu:\n");
        printf("1. Marcar Raio\n");
        printf("2. Quantos raios ja cairam\n");
        printf("3. Quantas areas nao foram afetadas por raio\n");
        printf("4. Imprimir matriz\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            marcarRaio(cidade, largura, comp);
            break;
        case 2:
            printf("\nQuantidade de raios ja caidos: %d\n", qntRaiosJaCairam(cidade, largura, comp));
            break;
        case 3:
            printf("\nQuantidade de areas nao afetadas por raio: %d\n", qntAreasNaoAfet(cidade, largura, comp));
            break;
        case 4:
            imprimirMatriz(cidade, largura, comp);
            break;
        case 0:
            printf("\nSaindo do programa...\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    // Liberação de memória alocada
    for (int x = 0; x < largura; x++)
    {
        free(cidade[x]);
    }
    free(cidade);

    return 0;
}
