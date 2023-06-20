#pragma once
#include "consts.h"

typedef struct Page
{
  short n;
  Data registers[MM];
  struct Page *pointers[MM + 1];
} Page;

void startBTree(Page *tree);
void printBTree(Page *tree);
bool searchBTree(Data *item, Page *node, FILE *file);
void saveBTree(Page *node, FILE *file);
void loadBTree(Page *node, FILE *file);
void insertBTree(Data reg, Page **ptr, FILE *file);