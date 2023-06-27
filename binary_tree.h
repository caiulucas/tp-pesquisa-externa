#pragma once
#include <stdbool.h>
#include "consts.h"

typedef struct Node
{ 
  Data data;
  int leftNode;
  int rightNode;
  int pos;
} Node;

void startBinaryTree(Node **root);
void printBinaryTree();
void createBinaryTree();
bool searchBinaryTree(Data *item, FILE *dataFile, Situation situation, int *reads);
