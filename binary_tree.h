#pragma once
#include "consts.h"

typedef struct Node
{
  Data data;
  struct Node *leftNode;
  struct Node *rightNode;
} Node;

typedef Node * BinaryTree;

bool insertBinaryTree(Node **root, Data data)
void printBinaryTree(Node *root, FILE *file);
bool findBinaryTree(Node *root, int key, Data *data);