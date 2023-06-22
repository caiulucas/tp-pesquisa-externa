#pragma once
#include "consts.h"

typedef struct Page
{
  short n;
  int pos;
  int keys[MM];
  int children[MM + 1];
} Page;

void startBTree(Page *tree);
void printBTree(Page *tree, FILE *bTreeFile);
bool searchBTree(Data *item, Page *node, FILE *dataFile, FILE *bTreeFile);
void insertBTree(Data reg, Page **node, FILE *dataFile, FILE *bTreeFile, int pos);
