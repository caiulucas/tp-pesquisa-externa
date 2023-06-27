#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "consts.h"

typedef struct Node
{
  int key;
  int leftNode;
  int rightNode;
  int pos;
} Node;

void startBinaryTree(Node **root);
void printBinaryTree();
void createBinaryTree(FILE *file);
bool findBinaryTree(Data *data, FILE *dataFile, int *reads);
bool runBinaryTree(Input input, FILE *dataFile);