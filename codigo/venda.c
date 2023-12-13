#include "venda.h"

void removerVeiculoEstoque(const char *marca, const char *modelo)
{
    FILE *arquivoEntrada = fopen("veiculos_estoque.csv", "r");
    if (arquivoEntrada == NULL)
    {
        printf("Erro ao abrir o arquivo de estoque.\n");
        exit(EXIT_FAILURE);
    }

    // Abrir um novo arquivo temporário para escrita
    FILE *arquivoTemp = fopen("temp.csv", "w");
    if (arquivoTemp == NULL)
    {
        fclose(arquivoEntrada);
        printf("Erro ao abrir o arquivo temporário.\n");
        exit(EXIT_FAILURE);
    }

    // Copiar veículos para o arquivo temporário, excluindo o veículo desejado
    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL)
    {
        // Verificar se a linha contém o veículo a ser removido
        if (strstr(linha, marca) != NULL && strstr(linha, modelo) != NULL)
        {
            continue; // Ignorar a linha, pois é o veículo que será removido
        }

        // Escrever a linha no arquivo temporário
        fprintf(arquivoTemp, "%s", linha);
    }

    // Fechar os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("veiculos_estoque.csv");

    // Renomear o arquivo temporário para o nome original
    rename("temp.csv", "veiculos_estoque.csv");
}

void registrarVenda(const Veiculo *veiculo, float taxa)
{
    FILE *arquivoVendas = fopen("historico_vendas.csv", "a");
    if (arquivoVendas == NULL)
    {
        printf("Erro ao abrir o arquivo de histórico de vendas.\n");
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

        printf("Veículos encontrados:\n");
        for (int i = 0; i < posicoesPreenchidasVeiculos; i++)
        {
            printf("%d. %s %s %s, %.2f\n", i + 1, veiculosEncontrados[i].marca.nome,
                   veiculosEncontrados[i].modelo, veiculosEncontrados[i].cor, veiculosEncontrados[i].preco);
        }

        printf("\nEscolha o número do veículo que deseja vender (ou 0 para cancelar): ");
        int escolha;
        scanf("%d", &escolha);

        if (escolha < 0 || escolha > posicoesPreenchidasVeiculos)
        {
            printf("Escolha inválida. Operação cancelada.\n");
            return;
        }

        if (escolha == 0)
        {
            printf("Venda cancelada.\n");
            return;
        }

        Veiculo veiculoVendido = veiculosEncontrados[escolha - 1];
        registrarVenda(&veiculoVendido, taxa);
        removerVeiculoEstoque(veiculoVendido.marca.nome, veiculoVendido.modelo);
        printf("Venda realizada com sucesso!\n");
    }

    // Limpeza do array, se necessário
    for (int i = 0; i < posicoesPreenchidasVeiculos; i++)
    {
        free(veiculosEncontrados[i].marca.nome);
        free(veiculosEncontrados[i].modelo);
        free(veiculosEncontrados[i].cor);
        free(veiculosEncontrados[i].preco);
    }
}
