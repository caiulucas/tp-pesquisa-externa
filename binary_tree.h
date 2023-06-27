#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "consts.h"

typedef struct Node
{ 
  Data data;
{
  int key;
  int leftNode;
  int rightNode;
} Node;

typedef Node *BinaryTree;

void startBinaryTree(Node **root);
void printBinaryTree();
bool insertBinaryTree(Data data);
void printBinaryTree(FILE *file);
void createBinaryTree();
bool searchBinaryTree(Data *item, FILE *dataFile, Situation situation, int *reads);
