#include <stdio.h>
#include <stdlib.h>
#include "consts.h"
#include "utils.h"
#include "file_handler.h"
#include "binary_tree.h"
#include "indexed.h"

void clear()
{
  printf("\e[1;1H\e[2J");
}

void printData(Data data)
{
  printf("[INFO] Key = %d | Data1 = %ld | Data2 = %s | Data3 = %s\n", data.key, data.data1, data.data2, data.data3);
}

void setup(Input input)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 583cf9f (feat: implement binary tree)
  remove(DATA_FILE);
  remove(INDEXES_FILE);
  remove(B_TREE_FILE);

  generateBinaryFile(input.quantity, input.situation);

<<<<<<< HEAD
  FILE *file = fopen(DATA_FILE, "rb");
=======
  FILE *file = fopen(DATA_FILE, "rb");
  if (!file)
  {
    printf("[FAIL] Arquivo de dados não encontrado.\n");
    generateBinaryFile(input.quantity, input.situation);
  }
>>>>>>> 012ec88 (feat: another type of tree)
=======
  FILE *file = fopen(DATA_FILE, "rb");
>>>>>>> 583cf9f (feat: implement binary tree)

  size_t indexesSz = (sizeof(Index) * input.quantity) / PAGE_ITEMS;
  Index *indexes = malloc(indexesSz);

  createIndexesTable(indexes, file);
<<<<<<< HEAD
<<<<<<< HEAD

  createBinaryTree(file);
=======
  createBinaryTree();

  fclose(file);
>>>>>>> 012ec88 (feat: another type of tree)
=======

  createBinaryTree(file);
>>>>>>> 583cf9f (feat: implement binary tree)
  free(indexes);
}