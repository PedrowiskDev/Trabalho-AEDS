#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <structs.h>
#include <buscar.h>

// Função para limpar a tela do console
void limpar() {
    #ifdef _WIN32
    system("cls"); // Limpa a tela no Windows
    #else
    system("clear"); // Limpa a tela no Linux e no Mac
    #endif
}

int main () {
    bool continuar = true;

    printf("VrumVrum Corporation ©\n\n");

    do {
        printf("1. Compra de veículos\n");
        printf("2. Venda de veículos\n");
        printf("3. Alterar dados de veículo\n");
        printf("4. Gerar extrato\n");
        printf("5. Fazer backup\n");
        printf("6. Sair\n");
        printf("\nPor favor, escolha uma opção: ");

        int opcao;
        scanf("%d", &opcao);
        limpar();

        char *resultadoBusca = (char*)malloc(255 * sizeof(char));

        if (opcao == 1 || opcao == 2 || opcao == 3) {
            resultadoBusca = buscar(opcao); // Filtragem e ordenação de veículos antes de realizar operação
        }

        switch(opcao) {
            case 1:
                compra(resultadoBusca);
                break;

            case 2:
                venda(resultadoBusca);
                break;

            case 3:
                alterarDados(resultadoBusca);
                break;

            case 4:
                gerarExtrato();
                break;

            case 5:
                fazerBackup();
                break;

            case 6:
                printf("Saindo... Digite Enter para sair.");
                getchar();
                continuar = false;
                break;
            
            default:
                printf("Opção inválida: por favor, digite um número entre 1 e 6 que corresponda à opção desejada.\n\n");
                break;
        }

    } while (continuar);

    return 0;
}