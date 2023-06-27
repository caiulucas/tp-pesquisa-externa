#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"
#include "utils.h"

void startBinaryTree(Node **root)
{
  *root = NULL;
}

<<<<<<< HEAD
// Node createNode(Index index, size_t pos, Node previousNode)
// {
//   Node aux;
//   aux.index = index;
//   aux.pos = pos;
//   aux.leftNode = previousNode.leftNode;
//   aux.rightNode = previousNode.rightNode;
//   return aux;
// }

<<<<<<< HEAD
Node *createNode(Data data, size_t pos)
=======
bool insertBinaryTree(Data data, FILE *binaryTreeFile)
>>>>>>> 012ec88 (feat: another type of tree)
{
  fseek(binaryTreeFile, 0, SEEK_END);
  size_t pos = ftell(binaryTreeFile) / sizeof(Node);

  Node newNode;
  newNode.data = data;
  newNode.leftNode = -1;
  newNode.rightNode = -1;
=======
Node *createNode(Data data, size_t pos)
{
  Node *aux = (Node *)malloc(sizeof(Node));
  aux->key = data.key;
  aux->pos = pos;
  aux->leftNode = -1;
  aux->rightNode = -1;
  return aux;
}

bool insertBinaryTree(Data data)
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "wb");
>>>>>>> bc6c119 (better binary_tree)

  if (pos == 0)
  {
    fwrite(&newNode, sizeof(Node), 1, binaryTreeFile);
    return true;
  }

  Node aux;
<<<<<<< HEAD

  fseek(binaryTreeFile, 0, SEEK_END);
  size_t length = ftell(binaryTreeFile) / sizeof(Node);
  rewind(binaryTreeFile);

  if (length == 0)
  {
    Node *newNode = createNode(data, length);
    fwrite(newNode, sizeof(Node), 1, binaryTreeFile);
    rewind(binaryTreeFile);
    return true;
  }
=======
>>>>>>> 012ec88 (feat: another type of tree)

  fseek(binaryTreeFile, 0, SEEK_END);
  size_t length = ftell(binaryTreeFile) / sizeof(Node);
  rewind(binaryTreeFile);

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    if (aux.data.key > newNode.data.key)
<<<<<<< HEAD
    {
      if (aux.leftNode != -1)
      {
        fseek(binaryTreeFile, (aux.leftNode) * sizeof(Node), SEEK_SET);
        continue;
      }

<<<<<<< HEAD
<<<<<<< HEAD
      aux.leftNode = pos;
      fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
=======
    if (index.key < aux->index.key)
=======
    if (data.key <= aux->key)
>>>>>>> bc6c119 (better binary_tree)
    {
      if (aux->leftNode == -1)
      {
        aux->leftNode = length;
        fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
        fwrite(aux, sizeof(Node), 1, binaryTreeFile);
      }
      displacement = (size_t)(aux->leftNode) * PAGE_ITEMS * sizeof(Data);
    }
    else if (data.key > aux->key)
    {
      if (aux->rightNode == -1)
      {
        aux->rightNode = aux->pos;
        fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
        fwrite(aux, sizeof(Node), 1, binaryTreeFile);
      }
      displacement = (size_t)(aux->rightNode) * PAGE_ITEMS * sizeof(Data);
>>>>>>> c1b13e5 (feat: add pos to node)
=======
    {
      if (aux.leftNode != -1)
      {
        fseek(binaryTreeFile, (aux.leftNode) * sizeof(Node), SEEK_SET);
        continue;
      }

      aux.leftNode = pos;
      fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
>>>>>>> 012ec88 (feat: another type of tree)
    }
    else
    {
<<<<<<< HEAD
      if (aux.rightNode != -1)
      {
        fseek(binaryTreeFile, (aux.leftNode) * sizeof(Node), SEEK_SET);
        continue;
      }

      aux.rightNode = pos;
      fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
    }

    fwrite(&aux, sizeof(Node), 1, binaryTreeFile);
    fseek(binaryTreeFile, 0, SEEK_END);
    fwrite(&newNode, sizeof(Node), 1, binaryTreeFile);
    rewind(binaryTreeFile);
    return true;
  }

  rewind(binaryTreeFile);
  return false;
<<<<<<< HEAD
=======
=======
      rewind(binaryTreeFile);
      return false;
    }

    fseek(binaryTreeFile, displacement, SEEK_SET);
  }


  Node *newNode = createNode(data, ftell(binaryTreeFile) / sizeof(Node));
  
  fseek(binaryTreeFile, 0, SEEK_END);
  fwrite(newNode, sizeof(Node), 1, binaryTreeFile);
  rewind(binaryTreeFile);

  return true;
>>>>>>> bc6c119 (better binary_tree)
}

void printBinaryTree()
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  if (!binaryTreeFile)
    return;

  Node aux;

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    printf("key: %d\n", aux.data.key);
    printf("leftNode: %d\n", aux.leftNode);
    printf("rightNode: %d\n", aux.rightNode);
    printf("\n");
  }
>>>>>>> 012ec88 (feat: another type of tree)
}

void printBinaryTree()
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

<<<<<<< HEAD
  if (!binaryTreeFile)
    return;

  Node aux;

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
=======
  while (left <= right) 
>>>>>>> 012ec88 (feat: another type of tree)
  {
    printf("key: %d\n", aux.data.key);
    printf("leftNode: %d\n", aux.leftNode);
    printf("rightNode: %d\n", aux.rightNode);
    printf("\n");
  }
}

<<<<<<< HEAD
bool findBinaryTree(Data *data, FILE *dataFile, Quantifier *quantifier)
=======
bool findBinaryTree(int key, Data *data, int *reads)
>>>>>>> 012ec88 (feat: another type of tree)
{
  // FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  // if (!binaryTreeFile)
  //   return false;

<<<<<<< HEAD
  Node aux;
  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    if (key == aux.data.key)
    {
      *data = aux.data;
      return true;
    }

    size_t displacement;
    printf("key: %d, index: %d \n", key, aux.data.key);
    if (key > aux.data.key)
      displacement = (size_t)(aux.rightNode) * PAGE_ITEMS * sizeof(Data);
    else
      displacement = (size_t)(aux.leftNode) * PAGE_ITEMS * sizeof(Data);

    fseek(binaryTreeFile, displacement, SEEK_SET);
<<<<<<< HEAD
    quantifier->reads += 1;
    
=======
>>>>>>> 012ec88 (feat: another type of tree)
  }
=======
  // Node *aux = root;
  // while (aux)
  // {
  //   if (key == aux->key)
  //   {
  //     *index = aux->index;
  //     return true;
  //   }

  //   size_t displacement;
  //   if (key > aux->index.key)
  //     displacement = (size_t)(aux->rightNode) * PAGE_ITEMS * sizeof(Data);
  //   else
  //     displacement = (size_t)(aux->leftNode) * PAGE_ITEMS * sizeof(Data);

  //   fseek(binaryTreeFile, displacement, SEEK_SET);
  //   fread(&aux, sizeof(Node), 1, binaryTreeFile);
  // }
>>>>>>> bc6c119 (better binary_tree)

  rewind(dataFile);
  fclose(binaryTreeFile);
  return false;
}

<<<<<<< HEAD
void createBinaryTree(FILE *dataFile)
{
  Data data;
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "wb+");

=======
bool searchBinaryTree(Data *item, FILE *dataFile, Situation situation, int *reads)
{
  int indexKey = (item->key / PAGE_ITEMS) * PAGE_ITEMS;
  if (situation == DESC)
    indexKey--;

  Data data;

>>>>>>> 012ec88 (feat: another type of tree)
  if (!findBinaryTree(indexKey, &data, reads))
    return false;

  Data dataList[PAGE_ITEMS];

  size_t displacement = (data.key - 1) * PAGE_ITEMS * sizeof(Data);
  fseek(dataFile, displacement, SEEK_SET);

  fread(dataList, sizeof(Data), PAGE_ITEMS, dataFile);
  *reads += 1;

  int pos = binarySearch(dataList, item->key);

  if (pos == -1)
    return false;

  *item = dataList[pos];

  return true;
}

void createBinaryTree()
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  FILE *dataFile = fopen(DATA_FILE, "rb");

  if (!dataFile)
    return;

  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "wb+");

  if (!binaryTreeFile)
    return;

  Data data;

  while (fread(&data, sizeof(Index), 1, dataFile) == 1)
    insertBinaryTree(data, binaryTreeFile);

  fclose(dataFile);
  fclose(binaryTreeFile);
}

bool runBinaryTree(Input input, FILE *dataFile)
{
  Quantifier quantifier;
  quantifier.reads = 0;
  quantifier.comparisons = 0;

  Data item;

  item.key = input.key;

  if (findBinaryTree(&item, dataFile, &quantifier))
  {
    printf("[SUCCESS] Item encontrado!\n");
    printf("[INFO] %d leituras realizadas.\n", quantifier.reads);
    printf("[INFO] %d comparações realizadas.\n", quantifier.comparisons);
    printData(item);
    return true;
  }

  printf("[INFO] %d leituras realizadas.\n", quantifier.reads);
  printf("[INFO] %d comparações realizadas.\n", quantifier.comparisons);
  printf("[FAIL] Item não encontrado!\n");
  return false;
=======
  FILE *indexesFile = fopen(INDEXES_FILE, "rb");
=======
  FILE *dataFile = fopen(DATA_FILE, "rb");
>>>>>>> 012ec88 (feat: another type of tree)

  if (!dataFile)
    return;

<<<<<<< HEAD
  while (fread(&index, sizeof(Index), 1, indexesFile) == 1)
    insertBinaryTree(index);
>>>>>>> d187e0d (feat: new branch)
=======
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "wb+");
=======
  FILE *dataFile = fopen(DATA_FILE, "rb");

  Data data;

  while (fread(&data, sizeof(Data), 1, dataFile) == 1)
    insertBinaryTree(data);
}

void printBinaryTree(FILE *file) {
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");
>>>>>>> bc6c119 (better binary_tree)

  if (!binaryTreeFile)
    return;

<<<<<<< HEAD
  Data data;

  while (fread(&data, sizeof(Index), 1, dataFile) == 1)
    insertBinaryTree(data, binaryTreeFile);

  fclose(dataFile);
  fclose(binaryTreeFile);
>>>>>>> 012ec88 (feat: another type of tree)
=======
  Node *aux;

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    fprintf(file, "Key: %d\n", aux->key);
    fprintf(file, "Left: %d\n", aux->leftNode);
    fprintf(file, "Right: %d\n", aux->rightNode);
    fprintf(file, "Pos: %d\n", aux->pos);
    fprintf(file, "\n");
  }
>>>>>>> bc6c119 (better binary_tree)
}