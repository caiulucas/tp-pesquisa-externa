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
<<<<<<< HEAD
=======
#include "consts.h"

typedef struct Node
{ 
  Data data;
>>>>>>> 012ec88 (feat: another type of tree)
=======
>>>>>>> bc6c119 (better binary_tree)
=======
>>>>>>> 583cf9f (feat: implement binary tree)
  int leftNode;
  int rightNode;
  int pos;
} Node;

void startBinaryTree(Node **root);
<<<<<<< HEAD
void printBinaryTree();
<<<<<<< HEAD
<<<<<<< HEAD
void createBinaryTree(FILE *file);
<<<<<<< HEAD
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
=======
void createBinaryTree(FILE *file);
<<<<<<< HEAD
bool findBinaryTree(Data *data, FILE *dataFile, int *reads);
>>>>>>> 583cf9f (feat: implement binary tree)
=======
bool findBinaryTree(Data *data, FILE *dataFile, int *reads);
bool runBinaryTree(Input input, FILE *dataFile);
>>>>>>> 54ee3d0 (add reads)
=======
bool findBinaryTree(Data *data, FILE *dataFile, Quantifier *quantifier);
bool runBinaryTree(Input input, FILE *dataFile);
>>>>>>> 829a1d7 (feat: add comparisons)
