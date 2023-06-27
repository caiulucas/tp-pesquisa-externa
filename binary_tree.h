#pragma once
#include <stdlib.h>
#include "consts.h"

typedef struct Node
{
  int key;
  int leftNode;
  int rightNode;
  int pos;
} Node;

typedef Node *BinaryTree;

void startBinaryTree(Node **root);
bool insertBinaryTree(Data data);
void printBinaryTree(FILE *file);
void createBinaryTree();
bool searchBinaryTree(Node *root, Data *item, FILE *dataFile, int *reads);