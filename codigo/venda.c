#include "venda.h"

bool marcaEhUltimoVeiculo(const char *marca) {
    FILE *veiculos_estoque = fopen("./arquivos/veiculos_estoque.csv", "r");
    if (veiculos_estoque == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        exit(EXIT_FAILURE);
    }

    char linha[1024];
    bool ultimaMarca = true;

    while (fgets(linha, sizeof(linha), veiculos_estoque) != NULL) {
        char *token = strtok(linha, ",");
        if (strcmp(marca, strdup(token)) == 0) {
            ultimaMarca = false; // Marca found, not the last one
        }
    }

    fclose(veiculos_estoque);
    return ultimaMarca;
}

void removerMarca(const char* marca) {
    FILE* arquivoMarcas = fopen ("./arquivos/marcas.csv", "r");
    if (arquivoMarcas == NULL) {
        printf("Erro ao abrir o arquivo de marcas.\n");
        exit(EXIT_FAILURE);
    }

    // Abrir um novo arquivo temporário para escrita
    FILE* arquivoTemp = fopen ("./arquivos/temp_marcas.csv", "w");
    if (arquivoTemp == NULL) {
        fclose(arquivoMarcas);
        printf("Erro ao abrir o arquivo temporario.\n");
        exit(EXIT_FAILURE);
    }

    // Copiar as marcas para o arquivo temporário, excluindo a marca desejada
    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivoMarcas) != NULL) {
        // Verificar se a linha contém a marca a ser removida
        if (strstr(linha, marca) != NULL) {
            continue;  // Ignorar a linha, pois é a marca que será removida
        }

        // Escrever a linha no arquivo temporário
        fprintf(arquivoTemp, "%s", linha);
    }

    // Fechar os arquivos
    fclose(arquivoMarcas);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("./arquivos/marcas.csv");

    // Renomear o arquivo temporário para o nome original
    rename("./arquivos/temp_marcas.csv", "./arquivos/marcas.csv");
}

void removerVeiculoEstoque(const char *marca, const char *modelo)
{
    FILE *arquivoEntrada = fopen("./arquivos/veiculos_estoque.csv", "r");
    if (arquivoEntrada == NULL)
    {
        printf("Erro ao abrir o arquivo de estoque.\n");
        exit(EXIT_FAILURE);
    }

    // Abrir um novo arquivo temporário para escrita
    FILE *arquivoTemp = fopen("./arquivos/temp_vendas.csv", "w");
    if (arquivoTemp == NULL)
    {
        fclose(arquivoEntrada);
        printf("Erro ao abrir o arquivo temporario.\n");
        exit(EXIT_FAILURE);
    }

    // Copiar veículos para o arquivo temporário, excluindo o veículo desejado
    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL)
    {
        // Verificar se a linha contém o veículo a ser removido
        if (strstr(linha, modelo) != NULL)
            continue; // Ignorar a linha, pois é o veículo que será removido

        // Escrever a linha no arquivo temporário
        fprintf(arquivoTemp, "%s", linha);
    }

    // Fechar os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("./arquivos/veiculos_estoque.csv");

    // Renomear o arquivo temporário para o nome original
    rename("./arquivos/temp_vendas.csv", "./arquivos/veiculos_estoque.csv");
}

void registrarVenda(const Veiculo *veiculo, float taxa)
{
    FILE *arquivoVendas = fopen("./arquivos/historico_vendas.csv", "a");
    if (arquivoVendas == NULL)
    {
        printf("Erro ao abrir o arquivo de historico de vendas.\n");
        exit(EXIT_FAILURE);
    }

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    float precoFinal = veiculo->preco * (1.0 + taxa); // Aplica a taxa ao preço
    fprintf(arquivoVendas, "%02d/%02d/%04d %02d:%02d:%02d - %s %s %s, %.2f\n",
            timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            veiculo->marca.nome, veiculo->modelo, veiculo->cor, precoFinal);

    fclose(arquivoVendas);
}

void venda(Veiculo *veiculosEncontrados, int posicoesPreenchidasVeiculos)
{
    bool cancelarOperacao = false;
    if (!cancelarOperacao && posicoesPreenchidasVeiculos > 0)
    {
        float taxa;
        printf("Digite a taxa de venda (em decimal): ");
        scanf("%f", &taxa);
        limpar();

        printf("Veiculos encontrados:\n");
        for (int i = 0; i < posicoesPreenchidasVeiculos; i++)
            printf("%d. %s %s %s, %.2f\n", i + 1, veiculosEncontrados[i].marca.nome,
                veiculosEncontrados[i].modelo, veiculosEncontrados[i].cor, veiculosEncontrados[i].preco);

        printf("\nDigite o numero correspondente ao veiculo que deseja vender (ou 0 para cancelar): ");
        int escolha;
        scanf("%d", &escolha);
        limpar();

        if (escolha < 0 || escolha > posicoesPreenchidasVeiculos)
        {
            printf("Escolha invalida. Operacao cancelada.\n");
            return;
        } else if (escolha == 0) {
            printf("Venda cancelada.\n");
            return;
        } else {
            Veiculo veiculoVendido = veiculosEncontrados[escolha - 1];
            if (marcaEhUltimoVeiculo(veiculoVendido.marca.nome))
                removerMarca(veiculoVendido.marca.nome);

            registrarVenda(&veiculoVendido, taxa);
            removerVeiculoEstoque(veiculoVendido.marca.nome, veiculoVendido.modelo);
            printf("Venda realizada com sucesso!\n");
        }
    }
}