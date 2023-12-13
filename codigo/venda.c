<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "structs.h"

void registrarVenda(const Veiculo* veiculo, float taxa) {
=======
#include "venda.h"

void registrarVenda(const Veiculo* veiculo) {
>>>>>>> bf39c2adfe3fb88a73dc05740d993271f39f52b6
    FILE* arquivoVendas = fopen("historico_vendas.csv", "a");
    if (arquivoVendas == NULL) {
        printf("Erro ao abrir o arquivo de histórico de vendas.\n");
        exit(EXIT_FAILURE);
    }

    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    float precoFinal = veiculo->preco * (1.0 + taxa);
    fprintf(arquivoVendas, "%02d/%02d/%04d %02d:%02d:%02d - %s %s %s, %.2f\n",
            timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            veiculo->marca.marca, veiculo->modelo, veiculo->cor, precoFinal);

    fclose(arquivoVendas);
}

void venda(Veiculo veiculosEncontrados,int quantidadeEncontrada) {
    bool cancelarOperacao = false;
<<<<<<< HEAD
    
    if (!cancelarOperacao && quantidadeEncontrada > 0) {
=======
if (!cancelarOperacao && resultadoBusca != NULL) {
>>>>>>> bf39c2adfe3fb88a73dc05740d993271f39f52b6
        float taxa;
        printf("Digite a taxa de venda (em decimal): ");
        scanf("%f", &taxa);
        limpar();

        printf("Veículos encontrados:\n");
        for (int i = 0; i < quantidadeEncontrada; i++) {
            printf("%d. %s %s %s, %.2f\n", i + 1, veiculosEncontrados[i].marca.marca,
                veiculosEncontrados[i].modelo, veiculosEncontrados[i].cor, veiculosEncontrados[i].preco);
        }

        printf("\nEscolha o número do veículo que deseja vender (ou 0 para cancelar): ");
        int escolha;
        scanf("%d", &escolha);

        if (escolha < 0 || escolha > quantidadeEncontrada) {
            printf("Escolha inválida. Operação cancelada.\n");
            return;
        }

        if (escolha == 0) {
            printf("Venda cancelada.\n");
            return;
        }

        Veiculo veiculoVendido = veiculosEncontrados[escolha - 1];
        registrarVenda(&veiculoVendido, taxa);
        removerVeiculoEstoque(veiculoVendido.marca.marca, veiculoVendido.modelo);
        printf("Venda realizada com sucesso!\n");
    }
    
    // Limpeza do array, se necessário
    for (int i = 0; i < quantidadeEncontrada; i++) {
        free(veiculosEncontrados[i].marca.marca);
        // ... Limpeza de outras propriedades se necessário
    }
}
