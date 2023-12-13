#include "alterardados.h"

void atualizarDadosVeiculo(const char* marca, const char* modelo, float novoPreco) {
    FILE* arquivoEstoque = fopen("./arquivos/veiculos_estoque.csv", "r");
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

    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivoEstoque) != NULL) {
        char marcaEstoque[50], modeloEstoque[50];
        float precoEstoque;
        sscanf(linha, "%[^,],%[^,],%f", marcaEstoque, modeloEstoque, &precoEstoque);

        if (strcmp(marcaEstoque, marca) == 0 && strcmp(modeloEstoque, modelo) == 0) {
            fprintf(novoArquivoEstoque, "%s,%s,%.2f\n", marcaEstoque, modeloEstoque, novoPreco);
        } else {
            fprintf(novoArquivoEstoque, "%s", linha);
        }
    }

    fclose(arquivoEstoque);
    fclose(novoArquivoEstoque);

    remove("veiculos_estoque.csv");
    rename("temp_estoque.csv", "veiculos_estoque.csv");
}

void alterarDados() {
    bool cancelarOperacao = false;

    if (!cancelarOperacao && resultadoBusca != NULL) {
        float novoPreco;
        printf("Digite o novo preço: ");
        scanf("%f", &novoPreco);
        limpar();

        atualizarDadosVeiculo(resultadoBusca.marca.nome, resultadoBusca.modelo, novoPreco);
        printf("Dados atualizados com sucesso!\n");
    }
}