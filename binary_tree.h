#pragma once
#include "consts.h"

typedef struct Node
{
  Index index;
  int leftNode;
  int rightNode;
  int pos;
} Node;

typedef Node *BinaryTree;

void startBinaryTree(Node **root);
bool insertBinaryTree(Index index);
void printBinaryTree(Node *root);
void createBinaryTree();
bool searchBinaryTree(Node *root, Data *item, FILE *dataFile, int *reads);