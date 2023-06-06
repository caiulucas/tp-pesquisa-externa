#pragma once
#define DATA2_SIZE 10
#define DATA3_SIZE 50
#define PAGE_ITEMS 4
#define INDEXES_MAX 100
#define DATA_FILE "data/data.bin"
#define INDEXES_FILE "data/indexes.bin"

typedef struct
{
  int key;
  long int data1;
  char data2[DATA2_SIZE];
  char data3[DATA3_SIZE];
} Data;


typedef struct {
    int pos;
    int key;
} Index;