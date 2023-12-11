#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "utils.h"
#include "structs.h"
#include "buscar.h"

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

        Veiculo *resultadoBusca;

        if (opcao == 1 || opcao == 2 || opcao == 3) {
            resultadoBusca = buscar(opcao, &cancelarOperacao); // Filtragem e ordenacao de veiculos antes de realizar operacao
        }

        if (!cancelarOperacao) {
            switch(opcao) {
                case 1:
                    //compra(resultadoBusca);
                    break;

                case 2:
                    //venda(resultadoBusca);
                    break;

                case 3:
                    //alterarDados(resultadoBusca);
                    break;

                case 4:
                    //gerarExtrato();
                    break;

                case 5:
                    //fazerBackup();
                    break;

                case 6:
                    free(resultadoBusca);
                    printf("Saindo... Digite Enter para sair.");
                    getchar();
                    exit(EXIT_SUCCESS);
                    break;

                default:
                    printf("Opcao inválida: por favor, digite um número entre 1 e 6 que corresponda à opcao desejada.\n\n");
                    break;
            }
        }
    }

    return 0;
}