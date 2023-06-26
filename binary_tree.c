#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"

void startBinaryTree(Node **root)
{
  *root = NULL;
}

Node *createNode(Index index, size_t pos)
{
  Node *aux = (Node *)malloc(sizeof(Node));
  aux->index = index;
  aux->pos = pos;
  aux->leftNode = -1;
  aux->rightNode = -1;
  return aux;
}

bool insertBinaryTree(Index index)
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "wb");

  if (!binaryTreeFile)
    return false;

  Node *aux;

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    size_t displacement;

    if (index.key < aux->index.key)
      displacement = (size_t)(aux->leftNode) * PAGE_ITEMS * sizeof(Data);
    else if (index.key > aux->index.key)
      displacement = (size_t)(aux->rightNode) * PAGE_ITEMS * sizeof(Data);
    else
      return false;

    fseek(binaryTreeFile, displacement, SEEK_SET);
    printf("aux: %p\n", aux);
  }

  aux = createNode(index, ftell(binaryTreeFile) / sizeof(Node));

  fwrite(aux, sizeof(Node), 1, binaryTreeFile);

  return true;
}

int binarySearch(Data data[PAGE_ITEMS], int key)
{
  int left = 0;
  int right = PAGE_ITEMS - 1;
  int middle = (left + right) / 2;

  while (left <= right)
  {
    if (data[middle].key == key)
    {
      return middle;
    }
    else if (data[middle].key < key)
    {
      left = middle + 1;
    }
    else
    {
      right = middle - 1;
    }

    middle = (left + right) / 2;
  }

  return -1;
}

bool findBinaryTree(Node *root, int key, Index *index, int *reads)
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  if (!binaryTreeFile)
    return false;

  Node *aux = root;
  while (aux)
  {
    if (key == aux->index.key)
    {
      *index = aux->index;
      return true;
    }

    size_t displacement;
    if (key > aux->index.key)
      displacement = (size_t)(aux->rightNode) * PAGE_ITEMS * sizeof(Data);
    else
      displacement = (size_t)(aux->leftNode) * PAGE_ITEMS * sizeof(Data);

    fseek(binaryTreeFile, displacement, SEEK_SET);
    fread(&aux, sizeof(Node), 1, binaryTreeFile);
  }

  return false;
}

bool searchBinaryTree(Node *root, Data *item, FILE *dataFile, int *reads)
{
  int indexKey = (item->key / PAGE_ITEMS) * PAGE_ITEMS;

  Index index;

  if (!findBinaryTree(root, indexKey, &index, reads))
    return false;

  Data dataList[PAGE_ITEMS];

  size_t displacement = (index.pos - 1) * PAGE_ITEMS * sizeof(Data);
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
  FILE *indexesFile = fopen(INDEXES_FILE, "rb");

  Index index;

  while (fread(&index, sizeof(Index), 1, indexesFile) == 1)
    insertBinaryTree(index);
}