#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    char *nome;
    float taxa;
} Marca;

typedef struct {
    Marca marca;
    char *modelo;
    char *cor;
    float preco;
} Veiculo;

#endif