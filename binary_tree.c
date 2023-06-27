#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"

void startBinaryTree(Node **root)
{
  *root = NULL;
}

// Node createNode(Data data, size_t pos, Node previousNode)
// {
//   Node aux;
//   aux.index = index;
//   aux.pos = pos;
//   aux.leftNode = previousNode.leftNode;
//   aux.rightNode = previousNode.rightNode;
//   return aux;
// }

bool insertBinaryTree(Data data, FILE *binaryTreeFile)
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

  if (!binaryTreeFile)
    return false;

  Node *aux;

  fseek(binaryTreeFile, 0, SEEK_END);
  size_t length = ftell(binaryTreeFile) / sizeof(Node);
  rewind(binaryTreeFile);

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    size_t displacement;

    if (data.key <= aux->key)
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
    }
    else
    {
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

bool findBinaryTree(int key, Data *data, int *reads)
{
  // FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  // if (!binaryTreeFile)
  //   return false;

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

  return false;
}

bool searchBinaryTree(Data *item, FILE *dataFile, Situation situation, int *reads)
{
  int indexKey = (item->key / PAGE_ITEMS) * PAGE_ITEMS;
  if (situation == DESC)
    indexKey--;

  Data data;

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

  Data data;

  while (fread(&data, sizeof(Data), 1, dataFile) == 1)
    insertBinaryTree(data);
}

void printBinaryTree(FILE *file) {
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  if (!binaryTreeFile)
    return;

  Node *aux;

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    fprintf(file, "Key: %d\n", aux->key);
    fprintf(file, "Left: %d\n", aux->leftNode);
    fprintf(file, "Right: %d\n", aux->rightNode);
    fprintf(file, "Pos: %d\n", aux->pos);
    fprintf(file, "\n");
  }
}