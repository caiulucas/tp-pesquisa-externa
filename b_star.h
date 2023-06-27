#pragma once
#include "consts.h"
#include <stdbool.h>
#include <stdlib.h>

typedef enum
{
  Internal,
  External
} TipoIntExt;
typedef struct PageType *PointerType;
typedef long KeyType;
typedef Data PageStar[PAGE_ITEMS];
typedef struct PageType
{
  TipoIntExt Pt;
  union
  {
    struct
    {
      int ni;
      KeyType ri[MM];
      PointerType pi[MM + 1];
    } U0;
    struct
    {
      int ne;
      Data re[MM2];
    } U1;
  } UU;
} PageType;

bool BStarSearch(Data *x, PointerType *Pt);
void InitializeBStar(PointerType *root);
bool CreateBStar(FILE *file, Input *input, PointerType *bstar);
bool insertIntoBStar(Data data, PointerType *raiz);
bool recursiveInsertion(Data data, PointerType paginaAtual, bool *hasGrown, Data *registerReturning, PointerType *returnPointer);
bool insertIntoInternalPage(PointerType page, int key, PointerType rightPointer);
bool insertIntoExternalPage(PointerType page, Data data);