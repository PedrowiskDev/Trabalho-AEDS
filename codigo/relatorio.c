#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "relatorio.h"

#define MAX_TRANSACOES 100

// Estrutura para representar uma transação (compra ou venda)
struct Transacao
{
    char tipo; // 'C' para compra, 'V' para venda
    char marca[20];
    char modelo[20];
    char cor[20];
    float valor;
    char data[11];
};

// Função para ler transações de um arquivo .csv e preencher a estrutura de transações
int lerTransacoesCSV(const char *nomeArquivo, struct Transacao transacoes[])
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    int i = 0;
    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) && i < MAX_TRANSACOES)
    {
        // O arquivo CSV tem o formato: tipo,valor,data
        sscanf(linha, "%c,%19[^,],%19[^,],%19[^,],%f,%10s", &transacoes[i].tipo, transacoes[i].marca, transacoes[i].modelo, transacoes[i].cor, &transacoes[i].valor, transacoes[i].data);
        i++;
    }

    fclose(arquivo);
    return i; // Retorna o número de transações lidas
}

// Função para escrever transações filtradas por data no arquivo CSV
void escreverTransacoes(const char *nomeArquivo, struct Transacao transacoes[], int tamanho, const char *dataBusca, int tipotranacao)
{
    FILE *arquivo = fopen(nomeArquivo, "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    if (tipotranacao == 'V')
    {
        fprintf(arquivo, "Compras feitas na data: %s\n", dataBusca);
    }
    else if (tipotranacao == 'C')
    {
        fprintf(arquivo, "Vendas feitas na data: %s\n", dataBusca);
    }

    fprintf(arquivo, "Tipo,Marca,Modelo,Cor,Valor,Data\n");

    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(transacoes[i].data, dataBusca) == 0)
        {
            fprintf(arquivo, "%c,%s,%s,%s,%.2f,%s\n", transacoes[i].tipo, transacoes[i].marca, transacoes[i].modelo, transacoes[i].cor, transacoes[i].valor, transacoes[i].data);
        }
    }

    fclose(arquivo);
}

void gerarExtrato()
{
    struct Transacao transacoesVenda[MAX_TRANSACOES];
    struct Transacao transacoesCompra[MAX_TRANSACOES];

    int tamanhoVendas = 0;
    int tamanhoCompras = 0;
    char dataBusca[11];
    char continuar;

    do
    {
        printf("Digite a data para a busca de compra e venda neste formato 'dd/mm/aaaa':\n");
        scanf("%s", dataBusca);

        // Lendo arquivos
        tamanhoVendas = lerTransacoesCSV("./arquivos/historico_vendas.csv", transacoesVenda);

        tamanhoCompras = lerTransacoesCSV("./arquivos/historico_compras.csv", transacoesCompra);

        // Escrevendo no relatorio o resultado
        escreverTransacoes("./arquivos/relatorio.csv", transacoesVenda, tamanhoVendas, dataBusca, 'V');

        escreverTransacoes("./arquivos/relatorio.csv", transacoesCompra, tamanhoCompras, dataBusca, 'C');

        // Pesquisa nas vendas pela data inserida
        bool encontrouVendas = false;
        printf("Transacoes de vendas na data %s:\n", dataBusca);
        for (int i = 0; i < tamanhoVendas; i++)
        {
            if (strcmp(transacoesVenda[i].data, dataBusca) == 0)
            {
                printf("Marca: %s \nModelo: %s \nCor: %s \nValor: %.2f \nData: %s\n", transacoesVenda[i].marca, transacoesVenda[i].modelo, transacoesVenda[i].cor, transacoesVenda[i].valor, transacoesVenda[i].data);
                encontrouVendas = true;
            }
        }

        if (!encontrouVendas)
        {
            printf("Erro: Nenhuma transacao de vendas encontrada para a data %s\n", dataBusca);
        }

        // Pesquisa nas compras pela data inserida
        bool encontrouCompras = false;
        printf("\nTransacoes de compras na data %s:\n", dataBusca);
        for (int i = 0; i < tamanhoCompras; i++)
        {
            if (strcmp(transacoesCompra[i].data, dataBusca) == 0)
            {
                printf("Marca: %s \nModelo: %s \nCor: %s \nValor: %.2f \nData: %s\n", transacoesCompra[i].marca, transacoesCompra[i].modelo, transacoesCompra[i].cor, transacoesCompra[i].valor, transacoesCompra[i].data);
                encontrouCompras = true;
            }
        }

        if (!encontrouCompras)
        {
            printf("Erro: Nenhuma transacao de compras encontrada para a data %s\n", dataBusca);
        }

        if (encontrouCompras && encontrouVendas != false)
        {
            printf("\n## Os dados foram salvos em relatorio.csv com sucesso! ##\n");
        }
        

        printf("Deseja fazer outra pesquisa? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's');

    return;
}