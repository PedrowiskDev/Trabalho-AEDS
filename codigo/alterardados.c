#include "alterardados.h"

void alterarDados(Veiculo *veiculos, int posicoesPreenchidasVeiculos) {
    if (posicoesPreenchidasVeiculos == 0) {
        printf("Nenhum veículo encontrado para alteração.\n");
        return;
    }

    printf("Veículos encontrados:\n");
    for (int i = 0; i < posicoesPreenchidasVeiculos; i++) {
        printf("%d. %s %s %s, %.2f\n", i + 1, veiculos[i].marca.nome,
            veiculos[i].modelo, veiculos[i].cor, veiculos[i].preco);
    }

    printf("\nEscolha o número do veículo que deseja alterar (ou 0 para cancelar): ");
    int escolha;
    scanf("%d", &escolha);

    if (escolha < 0 || escolha > posicoesPreenchidasVeiculos) {
        printf("Escolha inválida. Operação cancelada.\n");
        return;
    }

    if (escolha == 0) {
        printf("Alteração cancelada.\n");
        return;
    }

    Veiculo *veiculoAlterado = &veiculos[escolha - 1];

    printf("Novo modelo (pressione Enter para manter o mesmo): ");
    char novoModelo[100];
    scanf(" %[^\n]", novoModelo);
    if (strlen(novoModelo) > 0) {
        // O usuário inseriu um novo modelo
        strcpy(veiculoAlterado->modelo, novoModelo);
    }

    printf("Nova cor (pressione Enter para manter a mesma): ");
    char novaCor[100];
    scanf(" %[^\n]", novaCor);
    if (strlen(novaCor) > 0) {
        // O usuário inseriu uma nova cor
        strcpy(veiculoAlterado->cor, novaCor);
    }

    printf("Novo preço (pressione Enter para manter o mesmo): ");
    char novoPreco[100];
    scanf(" %[^\n]", novoPreco);
    if (strlen(novoPreco) > 0) {
        // O usuário inseriu um novo preço
        veiculoAlterado->preco = atof(novoPreco);
    }

    printf("Dados do veículo alterados com sucesso!\n");
}
