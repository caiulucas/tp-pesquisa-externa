#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "consts.h"

typedef struct PageType* pointerType; 
typedef struct PageType {
    short n;
    Data r[MM];
    pointerType p[MM + 1];
} PageType; //tipo pagina

void Initialize (pointerType tree);

//IMPLEMENTAR O CAMINHAMENTO QUE IMPRIMA OS ITENS DE FORMA ORDENADA

bool bTreeSearch (Data *x, pointerType pt); 

void InsertIntoThePage (pointerType pt, Data data, pointerType rightpt);

bool Ins (Data data, pointerType pt, bool *hasGrown, Data *dataReturn, pointerType *ptReturn);

void Insert (Data data, pointerType *pt);