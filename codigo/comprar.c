#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "structs.h"

void compra(Veiculo* veiculosEncontrados, int quantidadeEncontrada) {
    if (quantidadeEncontrada == 0) {
        printf("Nenhum veículo encontrado para compra.\n");
        return;
    }

    printf("Veículos encontrados:\n");
    for (int i = 0; i < quantidadeEncontrada; i++) {
        printf("%d. %s %s %s, %.2f\n", i + 1, veiculosEncontrados[i].marca.marca,
               veiculosEncontrados[i].modelo, veiculosEncontrados[i].cor, veiculosEncontrados[i].preco);
    }

    printf("\nEscolha o número do veículo que deseja comprar (ou 0 para cancelar): ");
    int escolha;
    scanf("%d", &escolha);

    if (escolha < 0 || escolha > quantidadeEncontrada) {
        printf("Escolha inválida. Operação cancelada.\n");
        return;
    }

    if (escolha == 0) {
        printf("Compra cancelada.\n");
        return;
    }

    Veiculo veiculoComprado = veiculosEncontrados[escolha - 1];
    
    adicionarVeiculoEstoque(veiculoComprado);
    removerVeiculoEstoque(veiculoComprado.marca.marca, veiculoComprado.modelo);
    registrarCompra(&veiculoComprado);

    printf("Compra realizada com sucesso!\n");
}
