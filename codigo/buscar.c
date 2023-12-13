#include "buscar.h"

Veiculo *buscar (int opcaoOperacao, bool *cancelarOperacao, int *posicoesPreenchidasVeiculos) {
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
                escolhaValida = true;
                strcpy(opcaoFiltro, "marca"); // substituir por sprintf(vetor, "marca");
                break;

            case 2:
                escolhaValida = true;
                strcpy(opcaoFiltro, "modelo");
                break;

            case 3:
                escolhaValida = true;
                strcpy(opcaoFiltro, "cor");
                break;

            case 4:
                *cancelarOperacao = true;
                return NULL;

            default:
                printf("\n\nOpcao invalida: por favor, digite um numero entre 1 e 4 que corresponda a opcao desejada.\n\n");
                break;
        }
    } while (!escolhaValida);

    Veiculo *veiculos = malloc(255 * sizeof(Veiculo)); // Vetor de objetos que armazena os resultados da busca
    char aux[255];
    bool sucessoBusca = false;

    FILE *veiculos_oferta = fopen ("./arquivos/veiculos_oferta.csv", "r");

    if (veiculos_oferta == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo.");
        exit (EXIT_FAILURE);
    } else {
        int i = 0;

        char *filtro = (char*)malloc(255 * sizeof(char));
        printf("Por favor, digite uma opcao de %s: ", opcaoFiltro);
        scanf("%s", filtro); // Usuario digita uma opcao de marca/modelo/cor
        fflush(stdin);
        limpar();

        while(fgets(aux, sizeof(aux), veiculos_oferta) != NULL) { // Percorrer o arquivo procurando por strings que correspondam ao que o usuario digitou
            char *token = strtok(aux, ",");

            Veiculo veiculoMatch; // Armazena os dados do veiculo do filtro correspondente em um "objeto" da "classe" `Veiculo`

            veiculoMatch.marca.nome = strdup(token); // Uso de `strdup` para duplicar strings e evitar que atributos utilizem os mesmos endereços de memória, já que `token` é um ponteiro
            veiculoMatch.modelo = strdup(strtok(NULL, ","));
            veiculoMatch.cor = strdup(strtok(NULL, ","));
            veiculoMatch.preco = atof(strtok(NULL, ","));

            switch (escolhaFiltro) {
                case 1: // Compara as marcas de veiculo no arquivo `veiculos_oferta.csv`
                    if (strcmp(filtro, veiculoMatch.marca.nome) == 0) {
                        sucessoBusca = true;
                        veiculos[i] = veiculoMatch; // Adiciona ao vetor de objetos os veiculos da marca/modelo/cor digitada pelo usuario
                        i++;
                    }
                    break;

                case 2: // Compara os modelos de veiculo no arquivo `veiculos_oferta.csv`
                    if (strcmp(filtro, veiculoMatch.modelo) == 0) {
                        sucessoBusca = true;
                        veiculos[i] = veiculoMatch;
                        i++;
                    }
                    break;

                case 3: // Compara as cores de veiculo no arquivo `veiculos_oferta.csv`
                    if (strcmp(filtro, veiculoMatch.cor) == 0) {
                        sucessoBusca = true;
                        veiculos[i] = veiculoMatch;
                        i++;
                    }
                    break;
            }
        }
        free(filtro);
        *posicoesPreenchidasVeiculos = i;
    }
    free(opcaoFiltro);

    if (!sucessoBusca) // Se array de structs estiver vazio, exibir uma mensagem
        printf ("A busca nao retornou nenhum resultado do banco de dados.\n\n");
    else {
        if (opcaoOperacao == 1 || opcaoOperacao == 2) {
            ordenar(veiculos, cancelarOperacao, *posicoesPreenchidasVeiculos);
        }
    }

    fflush(veiculos_oferta);
    fclose(veiculos_oferta);

    return veiculos;
}