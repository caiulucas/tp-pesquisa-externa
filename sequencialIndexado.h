#pragma once
#include "sizes.h"
#include <stdio.h>


// definição de uma entrada da tabela de índice das páginas
typedef struct {
    int pos;
    int key;
} tipoindice;

int pesquisa(tipoindice tab[], int tam, Data *item, FILE *arq);