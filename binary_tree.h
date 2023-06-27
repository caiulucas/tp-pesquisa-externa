#pragma once
<<<<<<< HEAD
#include <stdbool.h>
<<<<<<< HEAD
=======
>>>>>>> bc6c119 (better binary_tree)
#include <stdlib.h>
#include "consts.h"

typedef struct Node
{
  int key;
<<<<<<< HEAD
=======
#include "consts.h"

typedef struct Node
{ 
  Data data;
>>>>>>> 012ec88 (feat: another type of tree)
=======
>>>>>>> bc6c119 (better binary_tree)
  int leftNode;
  int rightNode;
} Node;

void startBinaryTree(Node **root);
<<<<<<< HEAD
void printBinaryTree();
<<<<<<< HEAD
void createBinaryTree(FILE *file);
bool findBinaryTree(Data *data, FILE *dataFile, Quantifier *quantifier);
bool runBinaryTree(Input input, FILE *dataFile);
=======
=======
bool insertBinaryTree(Data data);
void printBinaryTree(FILE *file);
>>>>>>> bc6c119 (better binary_tree)
void createBinaryTree();
bool searchBinaryTree(Data *item, FILE *dataFile, Situation situation, int *reads);
>>>>>>> 012ec88 (feat: another type of tree)
