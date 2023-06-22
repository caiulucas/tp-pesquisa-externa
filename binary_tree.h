#pragma once
#include "consts.h"

typedef struct Node
{
  Index index;
  struct Node *leftNode;
  struct Node *rightNode;
} Node;

typedef Node * BinaryTree;

void startBinaryTree(Node **root);
bool insertBinaryTree(Node **root, Index index);
void printBinaryTree(Node *root);
bool searchBinaryTree(Node *root, Data *item, FILE *dataFile);