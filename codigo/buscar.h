#ifndef BUSCAR_H
#define BUSCAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "utils.h"
#include "structs.h"
#include "ordenar.h"

Veiculo *buscar (int opcaoOperacao, bool *cancelarOperacao, int *posicoesPreenchidasVeiculos, const char *nomeArquivo);

#endif