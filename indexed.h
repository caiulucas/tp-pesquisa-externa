#pragma once
#include "sizes.h"
#include <stdio.h>
#include <stdbool.h>

// definição de uma entrada da tabela de índice das páginas
typedef struct {
    int pos;
    int key;
} Index;

bool search(Index indexes[], int size, Data *item, FILE *file);