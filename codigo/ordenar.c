#include "ordenar.h"

void ordenar (Veiculo *veiculos, bool *cancelarOperacao) {
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
                // Ordenar `veiculos` de acordo
                break;

            case 2:
                escolhaValida = true;
                // Ordenar `veiculos` de acordo
                break;

            case 3:
                escolhaValida = true;
                // Ordenar `veiculos` de acordo
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