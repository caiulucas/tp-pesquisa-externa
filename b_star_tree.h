#pragma once
#include "consts.h"

typedef enum
{
  Internal,
  External
} InternalOrExternal;

typedef struct InternalPage
{
  int nInternal;
  int internalRegisters[MM];
  struct Page *internalPointers[MM + 1];
} InternalPage;

typedef struct ExternalPage
{
  int nExternal;
  Data externalReg[MM2];
} ExternalPage;

typedef struct Page
{
  InternalOrExternal ptr;
  union
  {
    InternalPage internalPage;
    ExternalPage externalPage;

  } pages;
} Page;

bool searchBStarTree(Data *reg, Page **node);