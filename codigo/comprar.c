<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "structs.h"

void compra(Veiculo* veiculosEncontrados, int quantidadeEncontrada) {
    if (quantidadeEncontrada == 0) {
        printf("Nenhum veículo encontrado para compra.\n");
        return;
    }

    printf("Veículos encontrados:\n");
    for (int i = 0; i < quantidadeEncontrada; i++) {
        printf("%d. %s %s %s, %.2f\n", i + 1, veiculosEncontrados[i].marca.marca,
               veiculosEncontrados[i].modelo, veiculosEncontrados[i].cor, veiculosEncontrados[i].preco);
    }

    printf("\nEscolha o número do veículo que deseja comprar (ou 0 para cancelar): ");
    int escolha;
    scanf("%d", &escolha);

    if (escolha < 0 || escolha > quantidadeEncontrada) {
        printf("Escolha inválida. Operacao cancelada.\n");
        return;
    }

    if (escolha == 0) {
        printf("Compra cancelada.\n");
        return;
    }

    Veiculo veiculoComprado = veiculosEncontrados[escolha - 1];
    
    adicionarVeiculoEstoque(veiculoComprado);
    removerVeiculoEstoque(veiculoComprado.marca.marca, veiculoComprado.modelo);
    registrarCompra(&veiculoComprado);

    printf("Compra realizada com sucesso!\n");
=======
#include "comprar.h"

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

    if (!cancelarOperacao && resultadoBusca != NULL) {
        Veiculo veiculoComprado = *resultadoBusca;
        adicionarVeiculoEstoque(veiculoComprado);
        removerVeiculoEstoque(veiculoComprado.marca, veiculoComprado.modelo);
        registrarCompra(&veiculoComprado);
        // Você pode adicionar mais lógica aqui, como atualizar taxas
        printf("Compra realizada com sucesso!\n");
    }

    free(resultadoBusca);
>>>>>>> bf39c2adfe3fb88a73dc05740d993271f39f52b6
}
