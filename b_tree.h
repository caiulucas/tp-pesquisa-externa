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
void searchBTree(Register *item, Page *pointer);
void insertBTree(Register reg, Page **ptr);