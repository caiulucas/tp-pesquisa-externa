#pragma once
#define DATA2_SIZE 10
#define DATA3_SIZE 50
#define PAGE_ITEMS 4
#define INDEXES_MAX 100

typedef struct
{
  int key;
  long int data1;
  char data2[DATA2_SIZE];
  char data3[DATA3_SIZE];
} Data;

