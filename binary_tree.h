#pragma once
#include <stdbool.h>
<<<<<<< HEAD
#include <stdlib.h>
#include "consts.h"

typedef struct Node
{
  int key;
=======
#include "consts.h"

typedef struct Node
{ 
  Data data;
>>>>>>> 012ec88 (feat: another type of tree)
  int leftNode;
  int rightNode;
} Node;

void startBinaryTree(Node **root);
void printBinaryTree();
<<<<<<< HEAD
void createBinaryTree(FILE *file);
bool findBinaryTree(Data *data, FILE *dataFile, Quantifier *quantifier);
bool runBinaryTree(Input input, FILE *dataFile);
=======
void createBinaryTree();
bool searchBinaryTree(Data *item, FILE *dataFile, Situation situation, int *reads);
>>>>>>> 012ec88 (feat: another type of tree)
