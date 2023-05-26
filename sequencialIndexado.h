#include <iostream>
#include <stdio.h>
#define ITENSPAGINA 4
#define MAXTABELA 100
// definição de uma entrada da tabela de índice das páginas
typedef struct {
    int posicao;
    int chave;
} tipoindice;
// definição de um item do arquivo de dados
typedef struct {
    char titulo[31]; int chave; float preco;
} tipoitem;