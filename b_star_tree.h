#pragma once
#include "consts.h"

typedef struct
{
  int key;
  long int data1;
  char data2[DATA2_SIZE];
  char data3[DATA3_SIZE];
} Register;

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
  Register externalReg[MM2];
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

bool searchBStarTree(Register *reg, Page **node);