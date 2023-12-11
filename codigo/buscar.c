#include "buscar.h"

Veiculo *buscar (int opcaoOperacao, bool *cancelarOperacao) {
    bool escolhaValida = false;

    printf("1. Marca\n");
    printf("2. Modelo\n");
    printf("3. Cor\n");
    printf("4. Cancelar\n");
    printf("\nPor favor, escolha uma opcao de filtro de busca de veiculo: ");

    int escolhaFiltro;
    scanf("%d", &escolhaFiltro);
    limpar();

    char *opcaoFiltro = (char*)malloc(7 * sizeof(char));

    do {
        switch (escolhaFiltro) {
            case 1:
                escolhaValida;
                strcpy(opcaoFiltro, "marca");
                break;

            case 2:
                escolhaValida;
                strcpy(opcaoFiltro, "modelo");
                break;

            case 3:
                escolhaValida;
                strcpy(opcaoFiltro, "cor");
                break;

            case 4:
                *cancelarOperacao = true;
                return NULL;

            default:
                printf("\n\nOpcao inválida: por favor, digite um número entre 1 e 4 que corresponda à opcao desejada.\n\n");
                break;
        }
    } while (!escolhaValida);

    Veiculo *veiculos = malloc(255 * sizeof(Veiculo)); // Vetor de objetos que armazena os resultados da busca
    char aux[255];
    bool sucessoBusca = false;

    FILE *veiculos_estoque = fopen ("arquivos\veiculos_estoque.csv", "r");

    if (veiculos_estoque == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo.");
        exit (EXIT_FAILURE);
    } else {
        int i = 0;

        char *filtro = (char*)malloc(255 * sizeof(char));
        printf("Por favor, digite uma opcao de %s: ", opcaoFiltro);
        scanf("%s ", filtro); // Usuário digita uma opcao de marca/modelo/cor

        while(fgets(aux, sizeof(aux), veiculos_estoque)) { // Percorrer o arquivo procurando por strings que correspondam ao que o usuário digitou
            char *token = strtok(aux, ";"); // Seleciona as marcas de veiculo no arquivo `veiculos_estoque.csv`

            switch (escolhaFiltro) {
                case 2:
                    token = strtok(NULL, ";"); // Seleciona os modelos de veiculo no arquivo `veiculos_estoque.csv`
                    break;

                case 3:
                    token = strtok(NULL, ";");
                    token = strtok(NULL, ";"); // Seleciona as cores de veiculo no arquivo `veiculos_estoque.csv`
                    break;
            }


            if (strcmp(filtro, token)) {
                sucessoBusca;
                Veiculo veiculoMatch; // Armazena os dados do veiculo do filtro correspondente em um "objeto" da "classe" `Veiculo`

                //veiculoMatch.marca = strtok(aux, ";");
                veiculoMatch.modelo = strtok(NULL, ";");
                veiculoMatch.cor = strtok(NULL, ";");
                veiculoMatch.preco = atof(strtok(NULL, ";"));

                veiculos[i] = veiculoMatch; // Adiciona ao vetor de objetos os veiculos da marca/modelo/cor digitada pelo usuário
                i++;
            }
        }
    }

    if (!sucessoBusca) // Se array de structs estiver vazio, exibir uma mensagem
        printf ("\n\nA busca nao retornou nenhum resultado no banco de dados.\n\n");
    else {
        if (opcaoOperacao == 1 || opcaoOperacao == 2)
            ordenar(veiculos, cancelarOperacao);
    }

    fflush(veiculos_estoque);
    fclose(veiculos_estoque);

    return veiculos;
}