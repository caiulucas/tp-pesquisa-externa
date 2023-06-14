#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "consts.h"
#define M 2
#define MM 2*M
typedef struct PageType* pointerType;
typedef struct PageType {
    short n;
    Data r[MM];
    pointerType p[MM + 1];
} PageType;

void Inicializa (pointerType Arvore);

void Pesquisa (Data *x, pointerType Ap);