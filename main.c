#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Função para limpar a tela do console
void limpar() {
    #ifdef _WIN32
    system("cls"); // Limpa a tela no Windows
    #else
    system("clear"); // Limpa a tela no Linux e no Mac
    #endif
}

bool buscar (int opcaoOperacao) {
    bool escolhaValida = false;
    bool cancelarOperacao = false;

    printf("1. Marca\n");
    printf("2. Modelo\n");
    printf("3. Cor\n");
    printf("4. Cancelar\n");
    printf("\nPor favor, escolha uma opção de filtro de busca de veículo: ");

    int escolhaFiltro;
    scanf("%d", &escolhaFiltro);
    limpar();

    do {
        switch (escolhaFiltro) {
            case 1:
                escolhaValida;
                if (opcaoOperacao == 1 || opcaoOperacao == 2) {
                    if (ordenar(escolhaFiltro))
                        cancelarOperacao = true;
                } else {
                    // Abrir arquivo `veiculos_estoque.csv`
                    // Filtrar de acordo com `escolhaFiltro`
                    // Exibir no terminal
                    // Fechar arquivo
                }
                break;

            case 2:
                escolhaValida;
                if (opcaoOperacao == 1 || opcaoOperacao == 2) {
                    if (ordenar(escolhaFiltro))
                        cancelarOperacao = true;
                } else {
                    // Abrir arquivo `veiculos_estoque.csv`
                    // Filtrar de acordo com `escolhaFiltro`
                    // Exibir no terminal
                    // Fechar arquivo

                }
                break;

            case 3:
                escolhaValida;
                if (opcaoOperacao == 1 || opcaoOperacao == 2) {
                    if (ordenar(escolhaFiltro))
                        cancelarOperacao = true;
                } else {
                    // Abrir arquivo `veiculos_estoque.csv`
                    // Filtrar de acordo com `escolhaFiltro`
                    // Exibir no terminal
                    // Fechar arquivo

                }
                break;

            case 4:
                escolhaValida;
                cancelarOperacao = true;
                break;

            default:
                printf("Opção inválida: por favor, digite um número entre 1 e 4 que corresponda à opção desejada.\n\n");
                break;
        }
    } while (!escolhaValida);

    return cancelarOperacao;
}

bool ordenar (int escolhaFiltro) {
    bool opcaoValida = false;
    bool cancelarOperacao = false;

    printf("1. Veículo mais barato\n");
    printf("2. Veículo mais caro\n");
    printf("3. Ordem alfabética\n");
    printf("4. Cancelar\n");
    printf("\nPor favor, escolha uma opção de ordenação de busca de veículo: ");

    int opcaoOrdenacao;
    scanf("%d", &opcaoOrdenacao);
    limpar();

    do {
        switch (opcaoOrdenacao) {
            case 1:
                opcaoValida;
                // Abrir arquivo `veiculos_estoque.csv`
                // Filtrar de acordo com `escolhaFiltro`
                // Ordenar os resultados de acordo com `opcaoOrdenacao`
                // Exibir no terminal
                // Fechar arquivo
                break;

            case 2:
                opcaoValida;
                // Abrir arquivo `veiculos_estoque.csv`
                // Filtrar de acordo com `escolhaFiltro`
                // Ordenar os resultados de acordo com `opcaoOrdenacao`
                // Exibir no terminal
                // Fechar arquivo
                break;

            case 3:
                opcaoValida;
                // Abrir arquivo `veiculos_estoque.csv`
                // Filtrar de acordo com `escolhaFiltro`
                // Ordenar os resultados de acordo com `opcaoOrdenacao`
                // Exibir no terminal
                // Fechar arquivo
                break;

            case 4:
                opcaoValida;
                cancelarOperacao = true;
                break;

            default:
                printf("Opção inválida: por favor, digite um número entre 1 e 4 que corresponda à opção desejada.\n\n");
                break;
        }
    } while (!opcaoValida);

    return cancelarOperacao;
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

        switch(opcao) {
            case 1:
                if (!buscar(opcao))
                    compra();
                break;

            case 2:
                if (!buscar(opcao))
                    venda();
                break;

            case 3:
                if (!buscar(opcao))
                    alterarDados();
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