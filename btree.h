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

void Initialize (pointerType tree);

//IMPLEMENTAR O CAMINHAMENTO QUE IMPRIMA OS ITENS DE FORMA ORDENADA

bool Search (Data *x, pointerType pt); 

void InsertIntoThePage (pointerType pt, Data data, pointerType rightpt);

void Ins (Data data, pointerType pt, short *Cresceu, Data *dataReturn, pointerType *ptReturn);

void Insert (Data data, pointerType *pt);