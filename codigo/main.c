#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "utils.h"
#include "structs.h"
#include "buscar.h"
#include "relatorio.h"
#include "comprar.h"
#include "venda.h"
#include "alterardados.h"

int main () {
    printf("VrumVrum Corporation ©\n\n");

    while (1) {
        printf("1. Compra de veiculos\n");
        printf("2. Venda de veiculos\n");
        printf("3. Alterar dados de veiculo\n");
        printf("4. Gerar extrato\n");
        printf("5. Fazer backup\n");
        printf("6. Sair\n");
        printf("\nPor favor, escolha uma opcao: ");

        bool cancelarOperacao = false;
        int opcao;
        scanf("%d", &opcao);
        limpar();

        Veiculo *veiculosRetornados;
        int posicoesPreenchidasVeiculos = 0;

        switch(opcao) {
            case 1:
                veiculosRetornados = buscar(opcao, &cancelarOperacao, &posicoesPreenchidasVeiculos, "./arquivos/veiculos_oferta.csv"); // Filtragem e ordenacao de veiculos antes de realizar operacao
                if (!cancelarOperacao) comprar(veiculosRetornados, posicoesPreenchidasVeiculos);
                break;

            case 2:
                veiculosRetornados = buscar(opcao, &cancelarOperacao, &posicoesPreenchidasVeiculos, "./arquivos/veiculos_estoque.csv");
                if (!cancelarOperacao) venda(veiculosRetornados, posicoesPreenchidasVeiculos);
                break;

            case 3:
                veiculosRetornados = buscar(opcao, &cancelarOperacao, &posicoesPreenchidasVeiculos, "./arquivos/veiculos_oferta.csv");
                if (!cancelarOperacao) alterarDados(veiculosRetornados, posicoesPreenchidasVeiculos);
                break;

            case 4:
                gerarExtrato();
                break;

            case 5:
                //fazerBackup();
                break;

            case 6:
                free(veiculosRetornados);
                printf("Saindo...");
                exit(EXIT_SUCCESS);
                break;

            default:
                printf("Opcao invalida: por favor, digite um numero entre 1 e 6 que corresponda a opcao desejada.\n\n");
                break;
        }
    }

    return 0;
}