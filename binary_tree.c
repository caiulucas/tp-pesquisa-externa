#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"

void startBinaryTree(Node **root)
{
  *root = NULL;
}

Node *createNode(Index index)
{
  Node *aux = (Node *)malloc(sizeof(Node));
  aux->index = index;
  aux->leftNode = NULL;
  aux->rightNode = NULL;
  return aux;
}

bool insertBinaryTree(Node **root, Index index)
{
  Node **aux = root;

  while (*aux != NULL)
  {
    if (index.key < (*aux)->index.key)
      aux = &((*aux)->leftNode);  
    else if (index.key > (*aux)->index.key)
      aux = &((*aux)->rightNode);
    else
      return false;
  }
  *aux = createNode(index);

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

bool findBinaryTree(Node *root, int key, Index *index)
{
  Node *aux = root;
  while (aux)
  {
    if (key == aux->index.key)
    {
      *index = aux->index;
      return true;
    }

    if (key > aux->index.key)
      aux = aux->rightNode;
    else
      aux = aux->leftNode;
  }

  return false;
}

bool searchBinaryTree(Node *root, Data *item, FILE *dataFile)
{
  int indexKey = (item->key / PAGE_ITEMS) * PAGE_ITEMS;

  Index index;

  if (!findBinaryTree(root, indexKey, &index))
    return false;

  Data dataList[PAGE_ITEMS];

  size_t displacement = (index.pos - 1) * PAGE_ITEMS * sizeof(Data);
  fseek(dataFile, displacement, SEEK_SET);

  fread(dataList, sizeof(Data), PAGE_ITEMS, dataFile);

  int pos = binarySearch(dataList, item->key);

  if (pos == -1)
    return false;

  *item = dataList[pos];

  return true;
}
