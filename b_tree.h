#pragma once
#include "consts.h"

typedef struct
{
  int key;
} Register;

typedef struct Page
{
  short n;
  Register registers[MM];
  struct Page *pointers[MM + 1];
} Page;

void startBTree(Page *tree);
void printBTree(Page *tree);
bool searchBTree(Register *item, Page *pointer);
void insertBTree(Register reg, Page **ptr);