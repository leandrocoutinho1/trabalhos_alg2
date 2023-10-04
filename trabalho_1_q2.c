//Codigo fonte criado por alunos de SI da UFU:
//Diogo Arantes Borges Andrade
//Bruno Henrique Oliveira
//Leandro Coutinho Cesário Junior

#include <stdio.h>
#include <stdlib.h>
#define N 15000

int main() {
    // Declaração de variáveis //

    int M; // Número de turnos
    int Ti; // Número Ti que será usado para remover súditos da lista

    int *Convidados = (int *)malloc(N * sizeof(int)); // Alocando a memória necessária para a lista de convidados
    // Retornando erro ao tentar alocar a memória
    if (Convidados == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
    }

    int Num_suditos = N; // Quantidade de súditos


    // Solicitando o número de turnos para o usuário
    printf("Digite o numero de turnos desejado (M):\n");
    scanf("%d", &M);


    //Criando lista de convidados (Utilizando aritmétca de ponteiros)
    for (int i = 0; i < Num_suditos; i++) {
        *(Convidados + i) = i + 1;
    }

    // Realizando os turnos e atualizando a lista de convidados conforme a Lei
    for (int i = 0; i < M; i++) {
        
        printf("\nDigite o valor Ti do turno %d:\n", i + 1);
        scanf("%d", &Ti);

        // Criando uma lista temporária que armazene os súditos após cada turno
        int *novaLista = (int *)malloc(Num_suditos * sizeof(int));
        // Retornando erro ao tentar alocar a memória
        if (novaLista == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        int temp = 0; // Declarando a variável que armazenará temporariamente o número de súditos após o turno

        // Percorrendo a lista de convidados e copiando os súditos que não foram removidos
        for (int i = 0; i < Num_suditos; i++) {
            if ((*(Convidados + i)) % Ti != 0) {
                novaLista[temp] = Convidados[i];
                temp++;
            }
        }

        // Liberar a memória da lista antiga e atualizar com a nova lista
        free(Convidados);
        Convidados = novaLista;
        Num_suditos = temp;
    }

    // Definindo o número máximo de convidados (No máximo 10.000)
    int Max_Convidados; // Armazenará o valor máximo de convidados

    // Verificando se o número de convidados ultrapassa o valor máximo
    if (Num_suditos > 10000) {
        Max_Convidados = 10000;
    } else {
        Max_Convidados = Num_suditos;
    }

    // Imprimindo a lista de convidados
    printf("\n=> Lista de Convidados <=\n \n");
    for (int i = 0; i < Max_Convidados; i++) {
        printf("Convidado %d: %d\n", i + 1, Convidados[i]);
    }

    free(Convidados); // Liberar a memória alocada

    return 0;
}
