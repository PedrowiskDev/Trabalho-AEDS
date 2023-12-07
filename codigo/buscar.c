#include <buscar.h>
#include <structs.h>

Veiculo buscar (int opcaoOperacao) {
    bool escolhaValida = false;

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
                char aux[255];

                FILE *veiculos_estoque = fopen ("arquivos\veiculos_estoque.csv", "r");
                if(veiculos_estoque == NULL) {
                    printf("Ocorreu um erro ao abrir o arquivo.");
                    exit (EXIT_FAILURE);
                } else {
                    int numLinhas = 0, i = 0; // Descobrir quantas linhas tem no arquivo
                    char letra;
                    do {
                        letra = fgetc(veiculos_estoque);
                        if(letra == '\n')
                            numLinhas++;
                    } while(letra != EOF);

                    Veiculo veiculos[numLinhas]; // Vetor de objetos que armazena os resultados da busca

                    char *marca = (char*)malloc(255 * sizeof(char));
                    printf("Por favor, digite uma opção de marca: ");
                    scanf("%s ", marca); // Usuário digita uma opção de marca

                    while(fgets(aux, sizeof(aux), veiculos_estoque)) { // Percorrer o arquivo procurando por strings que correspondam ao que o usuário digitou
                        char *token = strtok(aux, ";");
                        token = strtok(NULL, ";");

                        if (strcmp(marca, token)) {
                            Veiculo veiculoMatch;

                            veiculoMatch.marca = token;
                            veiculoMatch.modelo = strtok(NULL, ";");
                            veiculoMatch.cor = strtok(NULL, ";");
                            veiculoMatch.preco = atof(strtok(NULL, ";"));

                            veiculos[i] = veiculoMatch; // Adiciona ao vetor de objetos os veículos da marca digitada pelo usuário
                        }
                    }

                    if () // Se array de structs estiver vazio, exibir uma mensagem
                        printf ("\n\nA busca não retornou nenhum resultado no banco de dados.\n\n");
                    else {
                        if (opcaoOperacao == 1 || opcaoOperacao == 2) {
                            ordenar(veiculos);
                        }
                    }

                }
                fflush(veiculos_estoque);
                fclose(veiculos_estoque);
                break;

            case 2:
                escolhaValida;
                break;

            case 3:
                escolhaValida;
                break;

            case 4:
                escolhaValida;
                break;

            default:
                printf("\n\nOpção inválida: por favor, digite um número entre 1 e 4 que corresponda à opção desejada.\n\n");
                break;
        }
    } while (!escolhaValida);

    return veiculos;
}