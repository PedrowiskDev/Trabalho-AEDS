#include "ordenar.h"

void ordenar (Veiculo *veiculos, bool *cancelarOperacao) {
    bool escolhaValida = false;

    printf("1. veiculo mais barato\n");
    printf("2. veiculo mais caro\n");
    printf("3. Ordem alfabética\n");
    printf("4. Cancelar\n");
    printf("\nPor favor, escolha uma opcao de ordenacao de busca de veiculo: ");

    int escolhaOrdenacao;
    scanf("%d", &escolhaOrdenacao);
    limpar();

    do {
        switch (escolhaOrdenacao) {
            case 1:
                escolhaValida;
                // Ordenar `veiculos` de acordo
                break;

            case 2:
                escolhaValida;
                // Ordenar `veiculos` de acordo
                break;

            case 3:
                escolhaValida;
                // Ordenar `veiculos` de acordo
                break;

            case 4:
                *cancelarOperacao = true;
                return;

            default:
                printf("Opcao inválida: por favor, digite um número entre 1 e 4 que corresponda à opcao desejada.\n\n");
                break;
        }
    } while (!escolhaValida);
}