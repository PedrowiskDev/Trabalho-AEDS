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



void limpar() {
    while (getchar() != '\n');
}
void adicionarVeiculoEstoque(Veiculo veiculo) {
    FILE* arquivoEstoque = fopen("veiculos_estoque.csv", "a");
    if (arquivoEstoque == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivoEstoque, "%s,%s,%.2f\n", veiculo.marca, veiculo.modelo, veiculo.preco);
    fclose(arquivoEstoque);
}

void removerVeiculoEstoque(const char* marca, const char* modelo) {
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

    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivoEstoque) != NULL) {
        char marcaEstoque[50], modeloEstoque[50];
        sscanf(linha, "%[^,],%[^,],", marcaEstoque, modeloEstoque);

        if (strcmp(marcaEstoque, marca) != 0 || strcmp(modeloEstoque, modelo) != 0) {
            fprintf(novoArquivoEstoque, "%s", linha);
        }
    }

    fclose(arquivoEstoque);
    fclose(novoArquivoEstoque);

    remove("veiculos_estoque.csv");
    rename("temp_estoque.csv", "veiculos_estoque.csv");
}
void registrarCompra(const Veiculo* veiculo) {
    FILE* arquivoHistorico = fopen("historico_compras.csv", "a");
    if (arquivoHistorico == NULL) {
        printf("Erro ao abrir o arquivo de histórico de compras.\n");
        exit(EXIT_FAILURE);
    }

    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fprintf(arquivoHistorico, "%02d/%02d/%04d %02d:%02d:%02d - %s %s, %.2f\n",
            timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            veiculo->marca, veiculo->modelo, veiculo->preco);

    fclose(arquivoHistorico);
}
void compra() {
    bool cancelarOperacao = false;
    Veiculo* resultadoBusca = buscar(1, &cancelarOperacao);

    if (!cancelarOperacao && resultadoBusca != NULL) {
        Veiculo veiculoComprado = *resultadoBusca;
        adicionarVeiculoEstoque(veiculoComprado);
        removerVeiculoEstoque(veiculoComprado.marca, veiculoComprado.modelo);
        registrarCompra(&veiculoComprado);
        // Você pode adicionar mais lógica aqui, como atualizar taxas
        printf("Compra realizada com sucesso!\n");
    }

    free(resultadoBusca);
}
