#pragma once
#include "consts.h"

typedef struct
{
  int key;
  long int data1;
  char data2[DATA2_SIZE];
  char data3[DATA3_SIZE];
} Register;

typedef struct Page
{
  short n;
  Register registers[MM];
  struct Page *pointers[MM + 1];
} Page;

void startBTree(Page *tree);
void printBTree(Page *tree);
bool searchBTree(Register *item, Page *node, FILE *file);
void saveBTree(Page *node, FILE *file);
void loadBTree(Page *node, FILE *file);
void insertBTree(Register reg, Page **ptr, FILE *file);