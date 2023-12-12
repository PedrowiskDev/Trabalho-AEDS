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

void registrarVenda(const Veiculo* veiculo) {
    FILE* arquivoVendas = fopen("historico_vendas.csv", "a");
    if (arquivoVendas == NULL) {
        printf("Erro ao abrir o arquivo de histórico de vendas.\n");
        exit(EXIT_FAILURE);
    }

    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fprintf(arquivoVendas, "%02d/%02d/%04d %02d:%02d:%02d - %s %s, %.2f\n",
            timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            veiculo->marca, veiculo->modelo, veiculo->preco);

    fclose(arquivoVendas);
}

void venda() {
    bool cancelarOperacao = false;
    Veiculo* resultadoBusca = buscar(2, &cancelarOperacao);
if (!cancelarOperacao && resultadoBusca != NULL) {
        float taxa;
        printf("Digite a taxa de compra (em decimal): ");
        scanf("%f", &taxa);
        limpar();
}
    if (!cancelarOperacao && resultadoBusca != NULL) {
        Veiculo veiculoVendido = *resultadoBusca;
        registrarVenda(&veiculoVendido);
        removerVeiculoEstoque(veiculoVendido.marca, veiculoVendido.modelo);
        printf("Venda realizada com sucesso!\n");
    }

    free(resultadoBusca);
}