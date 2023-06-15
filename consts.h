#pragma once
#define DATA2_SIZE 1000
#define DATA3_SIZE 5000
#define PAGE_ITEMS 4
#define INDEXES_MAX 100000
#define DATA_FILE "data/data.bin"
#define INDEXES_FILE "data/indexes.bin"
#define B_TREE_FILE "data/b_tree.bin"
#define M 2
#define MM 4
#define MM2 4

typedef struct
{
  int key;
  long int data1;
  char data2[DATA2_SIZE];
  char data3[DATA3_SIZE];
} Data;

typedef struct
{
  int pos;
  int key;
} Index;