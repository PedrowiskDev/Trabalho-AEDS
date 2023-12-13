#include "ordenar.h"

void ordenar (Veiculo *veiculos, bool *cancelarOperacao, int n) {
    bool escolhaValida = false;

    printf("1. Veiculo mais barato\n");
    printf("2. Veiculo mais caro\n");
    printf("3. Ordem alfabetica\n");
    printf("4. Cancelar\n");
    printf("\nPor favor, escolha uma opcao de ordenacao de busca de veiculo: ");

    int escolhaOrdenacao;
    scanf("%d", &escolhaOrdenacao);
    limpar();

    do {
        switch (escolhaOrdenacao) {
            case 1:
                escolhaValida = true;
                    for (int i = 0; i < n - 1; i++) {
                        for (int j = 0; j < n - i - 1; j++) {
                            if (veiculos[j].preco > veiculos[j + 1].preco) {
                                Veiculo temp = veiculos[j]; // Bubble sort para troca de posição dos veículos
                                veiculos[j] = veiculos[j + 1];
                                veiculos[j + 1] = temp;
                            }
                        }
                    }
                break;

            case 2:
                escolhaValida = true;
                    for (int i = 0; i < n - 1; i++) {
                        for (int j = 0; j < n - i - 1; j++) {
                            if (veiculos[j].preco < veiculos[j + 1].preco) {
                                Veiculo temp = veiculos[j]; // Bubble sort para troca de posição dos veículos
                                veiculos[j] = veiculos[j + 1];
                                veiculos[j + 1] = temp;
                            }
                        }
                    }
                break;

            case 3:
                escolhaValida = true;
                    for (int i = 0; i < n - 1; i++) {
                        for (int j = 0; j < n - i - 1; j++) {
                            if (strcmp(veiculos[j].modelo, veiculos[j+1].modelo) > 0) {
                                Veiculo temp = veiculos[j]; // Bubble sort para troca de posição dos veículos
                                veiculos[j] = veiculos[j + 1];
                                veiculos[j + 1] = temp;
                            }
                        }
                    }
                break;

            case 4:
                *cancelarOperacao = true;
                return;

            default:
                printf("Opcao invalida: por favor, digite um numero entre 1 e 4 que corresponda a opcao desejada.\n\n");
                break;
        }
    } while (!escolhaValida);
}