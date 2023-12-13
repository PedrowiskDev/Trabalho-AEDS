#include "comprar.h"

void adicionarMarca(const char* marca) {
    FILE* arquivoMarcas = fopen("marcas.csv", "r");
    if (arquivoMarcas == NULL) {
        printf("Erro ao abrir o arquivo de marcas.\n");
        exit(EXIT_FAILURE);
    }

    // Verificar se a marca já existe no arquivo
    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivoMarcas) != NULL) {
        if (strstr(linha, novaMarca) != NULL) {
            // A marca já existe, então não é necessário fazer nada
            fclose(arquivoMarcas);
            return;
        }
    }

    // Fechar o arquivo antes de abrir novamente para escrita
    fclose(arquivoMarcas);

    // Abrir o arquivo de marcas para escrita (append)
    arquivoMarcas = fopen("marcas.csv", "a");
    if (arquivoMarcas == NULL) {
        printf("Erro ao abrir o arquivo de marcas para escrita.\n");
        exit(EXIT_FAILURE);
    }

    // Adicionar a nova marca ao final do arquivo
    fprintf(arquivoMarcas, "%s\n", novaMarca);

    // Fechar o arquivo
    fclose(arquivoMarcas);
}

void removerMarca(const char* marca) {
   FILE* arquivoMarcas = fopen("marcas.csv", "r");
    if (arquivoMarcas == NULL) {
        printf("Erro ao abrir o arquivo de marcas.\n");
        exit(EXIT_FAILURE);
    }

    // Abrir um novo arquivo temporário para escrita
    FILE* arquivoTemp = fopen("temp_marcas.csv", "w");
    if (arquivoTemp == NULL) {
        fclose(arquivoMarcas);
        printf("Erro ao abrir o arquivo temporário.\n");
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
    remove("marcas.csv");

    // Renomear o arquivo temporário para o nome original
    rename("temp_marcas.csv", "marcas.csv");
}

void adicionarVeiculoEstoque(const Veiculo* veiculo) {
    FILE* arquivoEstoque = fopen("veiculos_estoque.csv", "a");
    if (arquivoEstoque == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        exit(EXIT_FAILURE);
    }

    // Escrever o veículo no arquivo
    fprintf(arquivoEstoque, "%s,%s,%s,%.2f\n", veiculo->marca.nome,
            veiculo->modelo, veiculo->cor, veiculo->preco);

    // Fechar o arquivo
    fclose(arquivoEstoque);
}


void removerVeiculoOferta(const char* marca, const char* modelo) {
    FILE* arquivoEntrada = fopen("veiculos_oferta.csv", "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de oferta.\n");
        exit(EXIT_FAILURE);
    }

    // Abrir um novo arquivo temporário para escrita
    FILE* arquivoTemp = fopen("temp_oferta.csv", "w");
    if (arquivoTemp == NULL) {
        fclose(arquivoEntrada);
        printf("Erro ao abrir o arquivo temporário.\n");
        exit(EXIT_FAILURE);
    }

    // Copiar veículos para o arquivo temporário, excluindo o veículo desejado
    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        // Verificar se a linha contém o veículo a ser removido
        if (strstr(linha, marca) != NULL && strstr(linha, modelo) != NULL) {
            continue;  // Ignorar a linha, pois é o veículo que será removido
        }

        // Escrever a linha no arquivo temporário
        fprintf(arquivoTemp, "%s", linha);
    }

    // Fechar os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoTemp);

    // Remover o arquivo original
    remove("veiculos_oferta.csv");

    // Renomear o arquivo temporário para o nome original
    rename("temp_oferta.csv", "veiculos_oferta.csv");
}

void registrarCompra(const Veiculo* veiculo) {
    FILE* arquivoCompras = fopen("historico_compras.csv", "a");
    if (arquivoCompras == NULL) {
        printf("Erro ao abrir o arquivo de histórico de compras.\n");
        exit(EXIT_FAILURE);
    }

    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fprintf(arquivoCompras, "%02d/%02d/%04d %02d:%02d:%02d - %s %s %s, %.2f\n",
            timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
            veiculo->marca.nome, veiculo->modelo, veiculo->cor, veiculo->preco);

    fclose(arquivoCompras);
}

void comprar(Veiculo *veiculosRetornados, int posicoesPreenchidasVeiculos) {
    if (posicoesPreenchidasVeiculos == 0) {
        printf("Nenhum veículo encontrado para compra.\n");
        return;
    }

    printf("Veículos encontrados:\n");
    for (int i = 0; i < posicoesPreenchidasVeiculos; i++) {
        printf("%d. %s %s %s, %.2f\n", i + 1, veiculosRetornados[i].marca.nome,
               veiculosRetornados[i].modelo, veiculosRetornados[i].cor, veiculosRetornados[i].preco);
    }

    printf("\nEscolha o número do veículo que deseja comprar (ou 0 para cancelar): ");
    int escolha;
    scanf("%d", &escolha);

    if (escolha < 0 || escolha > posicoesPreenchidasVeiculos) {
        printf("Escolha inválida. Operação cancelada.\n");
        return;
    }

    if (escolha == 0) {
        printf("Compra cancelada.\n");
        return;
    }

    Veiculo veiculoComprado = veiculosRetornados[escolha - 1];
    
    // Adiciona a marca ao arquivo marcas.csv se necessário
    adicionarMarca(veiculoComprado.marca.nome);

    // Adiciona o veículo ao estoque
    adicionarVeiculoEstoque(&veiculoComprado);

    // Remove o veículo da oferta
    removerVeiculoOferta(veiculoComprado.marca.nome veiculoComprado.modelo);

    // Registra a compra no histórico
    registrarCompra(&veiculoComprado);

    printf("Compra realizada com sucesso!\n");
}
