#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"
#include "utils.h"

void startBinaryTree(Node **root)
{
  *root = NULL;
}

// Node createNode(Data data, size_t pos, Node previousNode)
// {
//   Node aux;
//   aux.index = index;
//   aux.pos = pos;
//   aux.leftNode = previousNode.leftNode;
//   aux.rightNode = previousNode.rightNode;
//   return aux;
// }

Node *createNode(Data data, size_t pos)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = data.key;
  node->pos = pos;
  node->leftNode = -1;
  node->rightNode = -1;
  return node;
}

bool insertBinaryTree(Data data, FILE *binaryTreeFile)
{
  if (!binaryTreeFile)
    return false;

  Node aux = {data.key, -1, -1, 0};

  fseek(binaryTreeFile, 0, SEEK_END);
  size_t length = ftell(binaryTreeFile) / sizeof(Node);
  rewind(binaryTreeFile);

  if (length == 0)
  {
    Node *newNode = createNode(data, length);
    fwrite(newNode, sizeof(Node), 1, binaryTreeFile);
    rewind(binaryTreeFile);
    return true;
  }

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    size_t displacement;

    if (data.key < aux.key)
    {
      if (aux.leftNode == -1)
      {
        aux.leftNode = length;
        fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
        fwrite(&aux, sizeof(Node), 1, binaryTreeFile);
        break;
      }
      displacement = (size_t)(aux.leftNode) * sizeof(Node);
    }
    else if (data.key > aux.key)
    {
      if (aux.rightNode == -1)
      {
        aux.rightNode = length;
        fseek(binaryTreeFile, -sizeof(Node), SEEK_CUR);
        fwrite(&aux, sizeof(Node), 1, binaryTreeFile);
        break;
      }

      displacement = (size_t)(aux.rightNode) * sizeof(Node);
    }
    else
    {
      rewind(binaryTreeFile);
      return false;
    }

    fseek(binaryTreeFile, displacement, SEEK_SET);
  }

  Node *newNode = createNode(data, length);

  fseek(binaryTreeFile, 0, SEEK_END);
  fwrite(newNode, sizeof(Node), 1, binaryTreeFile);
  rewind(binaryTreeFile);

  return true;
}

bool findBinaryTree(Data *data, FILE *dataFile, Quantifier *quantifier)
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  if (!binaryTreeFile)
    return false;

  Node aux;
  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    if (data->key == aux.key)
    {
      fseek(dataFile, aux.pos * sizeof(Data), SEEK_SET);
      fread(data, sizeof(Data), 1, dataFile);
      quantifier->reads += 1;
      quantifier->comparisons += 1;

      rewind(dataFile);
      fclose(binaryTreeFile);
      return true;
    }

    size_t displacement;

    quantifier->comparisons += 1;
    if (data->key > aux.key)
      displacement = (size_t)(aux.rightNode) * sizeof(Node);
    else
      displacement = (size_t)(aux.leftNode) * sizeof(Node);

    fseek(binaryTreeFile, displacement, SEEK_SET);
    quantifier->reads += 1;
    
  }

  rewind(dataFile);
  fclose(binaryTreeFile);
  return false;
}

void createBinaryTree(FILE *dataFile)
{
  Data data;
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "wb+");

  if (!binaryTreeFile)
    return;

  rewind(dataFile);
  int i = 1;
  while (fread(&data, sizeof(Data), 1, dataFile) == 1)
  {
    clear();
    printf("[INFO] Gerando %d arquivos.\n", i++);
    insertBinaryTree(data, binaryTreeFile);
  }

  fclose(dataFile);
}

void printBinaryTree()
{
  FILE *binaryTreeFile = fopen(BINARY_TREE_FILE, "rb");

  if (!binaryTreeFile)
    return;

  Node aux;

  while (fread(&aux, sizeof(Node), 1, binaryTreeFile) == 1)
  {
    printf("Key: %d ", aux.key);
    printf("Left: %d ", aux.leftNode);
    printf("Right: %d ", aux.rightNode);
    printf("Pos: %d ", aux.pos);
    printf("\n");
  }

  fclose(binaryTreeFile);
}

bool runBinaryTree(Input input, FILE *dataFile)
{
  Quantifier quantifier;
  quantifier.reads = 0;
  quantifier.comparisons = 0;

  Data item;

  item.key = input.key;

  if (findBinaryTree(&item, dataFile, &quantifier))
  {
    printf("[SUCCESS] Item encontrado!\n");
    printf("[INFO] %d leituras realizadas.\n", quantifier.reads);
    printf("[INFO] %d comparações realizadas.\n", quantifier.comparisons);
    printData(item);
    return true;
  }

  printf("[INFO] %d leituras realizadas.\n", quantifier.reads);
  printf("[INFO] %d comparações realizadas.\n", quantifier.comparisons);
  printf("[FAIL] Item não encontrado!\n");
  return false;
}