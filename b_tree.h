#pragma once
#include "consts.h"

typedef struct Page
{
  short n;
  Data regs[MM];
  struct Page *pointers[MM + 1];
} Page;

void insertBTree(Data reg, Page **node, FILE *file);
bool runBTree(int key, FILE *file);