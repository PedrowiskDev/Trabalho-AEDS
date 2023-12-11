#include "utils.h"

// Funcao para limpar a tela do console
void limpar() {
    #ifdef _WIN32
    system("cls"); // Limpa a tela no Windows
    #else
    system("clear"); // Limpa a tela no Linux e no Mac
    #endif
}