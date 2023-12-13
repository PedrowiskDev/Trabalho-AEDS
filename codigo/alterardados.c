#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "structs.h"

void alterarDadosVeiculo(Veiculo* veiculo) {
    printf("Digite os novos dados do veiculo:\n");
    printf("Modelo: ");
    scanf("%s", veiculo->modelo);
    limpar();
    printf("Cor: ");
    scanf("%s", veiculo->cor);
    limpar();
    printf("Preco: ");
    scanf("%f", &(veiculo->preco));
    limpar();
}

// Função para alterar taxas de uma marca
void alterarTaxaMarca(Marca* marca) {
    printf("Digite a nova taxa para a marca %s: ", marca->marca);
    scanf("%f", &(marca->taxa));
    limpar();
}

// Função para buscar uma marca pelo nome
Marca* buscarMarca(const char* nomeMarca) {
    FILE* arquivoMarcas = fopen("marcas.csv", "r");
    if (arquivoMarcas == NULL) {
        printf("Erro ao abrir o arquivo de marcas.\n");
        exit(EXIT_FAILURE);
    }

    Marca* marcas = NULL;
    char linha[1024];
    int numMarcas = 0;

    // Contar quantas marcas existem no arquivo para alocar memória
    while (fgets(linha, sizeof(linha), arquivoMarcas) != NULL) {
        numMarcas++;
    }

    // Voltar ao início do arquivo para leitura
    fseek(arquivoMarcas, 0, SEEK_SET);

    // Alocar memória para as marcas
    marcas = malloc(numMarcas * sizeof(Marca));

    // Ler e armazenar as marcas
    for (int i = 0; i < numMarcas; i++) {
        fscanf(arquivoMarcas, "%s,%f\n", marcas[i].marca, &(marcas[i].taxa));
    }

    fclose(arquivoMarcas);

    // Procurar a marca pelo nome
    for (int i = 0; i < numMarcas; i++) {
        if (strcmp(marcas[i].marca, nomeMarca) == 0) {
            return &(marcas[i]);
        }
    }

    // Se a marca não for encontrada, liberar memória e retornar NULL
    free(marcas);
    return NULL;
}

// Função para salvar as marcas de volta no arquivo após as alterações
void salvarMarcasNoArquivo(const Marca* marcas, int numMarcas) {
    FILE* arquivoMarcas = fopen("marcas.csv", "w");
    if (arquivoMarcas == NULL) {
        printf("Erro ao abrir o arquivo de marcas.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numMarcas; i++) {
        fprintf(arquivoMarcas, "%s,%.2f\n", marcas[i].marca, marcas[i].taxa);
    }

    fclose(arquivoMarcas);
}

// Função para alterar dados do veículo e taxas
void alterarDados() {
    printf("1. Alterar dados de um veiculo\n");
    printf("2. Alterar taxa de uma marca\n");
    printf("3. Voltar\n");
    printf("\nPor favor, escolha uma opcao: ");

    int escolha;
    scanf("%d", &escolha);
    limpar();

    switch (escolha) {
        case 1: {
            bool cancelarOperacao = false;
            Veiculo* resultadoBusca = buscar(3, &cancelarOperacao);

            if (!cancelarOperacao && resultadoBusca != NULL) {
                alterarDadosVeiculo(resultadoBusca);
                // Atualizar o veículo no arquivo de estoque
                removerVeiculoEstoque(resultadoBusca->marca.marca, resultadoBusca->modelo);
                adicionarVeiculoEstoque(*resultadoBusca);
                printf("Dados do veiculo alterados com sucesso!\n");
            }

            free(resultadoBusca);
            break;
        }

        case 2: {
            char nomeMarca[50];
            printf("Digite o nome da marca: ");
            scanf("%s", nomeMarca);
            limpar();

            Marca* marca = buscarMarca(nomeMarca);

            if (marca != NULL) {
                alterarTaxaMarca(marca);
                printf("Taxa da marca alterada com sucesso!\n");
            } else {
                printf("Marca nao encontrada.\n");
            }
            break;
        }

        case 3:
        // Volta pro inicio
            break;

        default:
            printf("Opcao invalida.\n");
            break;
    }
}
