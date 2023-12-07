#include <ordenar.h>

char *ordenar (int escolhaFiltro) {
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