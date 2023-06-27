#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"
#include "utils.h"

void startBinaryTree(Node **root)
{
  *root = NULL;
}

// Node createNode(Index index, size_t pos, Node previousNode)
// {
//   Node aux;
//   aux.index = index;
//   aux.pos = pos;
//   aux.leftNode = previousNode.leftNode;
//   aux.rightNode = previousNode.rightNode;
//   return aux;
// }

Node *createNode(Data data, size_t pos)
{
  fseek(binaryTreeFile, 0, SEEK_END);
  size_t pos = ftell(binaryTreeFile) / sizeof(Node);

  Node newNode;
  newNode.data = data;
  newNode.leftNode = -1;
  newNode.rightNode = -1;

  if (pos == 0)
  {
    fwrite(&newNode, sizeof(Node), 1, binaryTreeFile);
    return true;
  }

  Node aux;

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

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    if (aux.data.key > newNode.data.key)
    {
      if (aux.leftNode != -1)
      {
        fseek(binaryTreeFile, (aux.leftNode) * sizeof(Node), SEEK_SET);
        continue;
      }

      aux.leftNode = pos;
      fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
    }
    else
    {
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
}

bool findBinaryTree(Data *data, FILE *dataFile, Quantifier *quantifier)
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  if (!binaryTreeFile)
    return false;

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
    quantifier->reads += 1;
    
  }

  rewind(dataFile);
  fclose(binaryTreeFile);
  return false;
}

void createBinaryTree(FILE *dataFile)
{
  Data data;
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "wb+");

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
}