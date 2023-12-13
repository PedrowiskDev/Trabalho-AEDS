#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char nome[255];
    float taxa;
} Marca;

typedef struct {
    Marca marca;
    char modelo[255];
    char cor[255];
    float preco;
} Veiculo;

#endif