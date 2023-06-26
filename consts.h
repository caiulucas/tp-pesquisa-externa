#pragma once
#define DATA2_SIZE 1000
#define DATA3_SIZE 5000
#define PAGE_ITEMS 1000
#define M 10
#define MM 2 * M
#define DATA_FILE "data/data.bin"
#define INDEXES_FILE "data/indexes.bin"
#define B_TREE_FILE "data/b_tree.bin"
#define BINARY_TREE_FILE "data/binary_tree.bin"
#define MM2 4

typedef enum Method
{
  INDEX = 1,
  BINARY_TREE = 2,
  B_TREE = 3
} Method;

typedef enum Situation
{
  ASC = 1,
  DESC = 2,
  RANDOM = 3
} Situation;

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

typedef struct
{
  int key;
  int quantity;
  Method method;
  Situation situation;
} Input;