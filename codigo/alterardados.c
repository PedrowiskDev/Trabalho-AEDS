#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct {
    char marca[50];
    char modelo[50];
    float preco;
} Veiculo;

typedef struct {
    char marca[50];
    char modelo[50];
    float preco;
} Veiculo;

void atualizarDadosVeiculo(const char* marca, const char* modelo, float novoPreco) {
    FILE* arquivoEstoque = fopen("veiculos_estoque.csv", "r");
    if (arquivoEstoque == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        exit(EXIT_FAILURE);
    }

    FILE* novoArquivoEstoque = fopen("temp_estoque.csv", "w");
    if (novoArquivoEstoque == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivoEstoque);
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
    bool cancelarOperacao = false;
    Veiculo* resultadoBusca = buscar(3, &cancelarOperacao);

    if (!cancelarOperacao && resultadoBusca != NULL) {
        float novoPreco;
        printf("Digite o novo preço: ");
        scanf("%f", &novoPreco);
        limpar();

        atualizarDadosVeiculo(resultadoBusca->marca, resultadoBusca->modelo, novoPreco);
        printf("Dados atualizados com sucesso!\n");
    }

    free(resultadoBusca);
}