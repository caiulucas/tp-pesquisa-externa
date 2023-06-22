#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"

Node *createNode(Data data)
{
  Node *aux = (Node *)malloc(sizeof(Node));
  aux->data = data;
  aux->leftNode = NULL;
  aux->rightNode = NULL;
  return aux;
}

bool insertBinaryTree(Node **root, Data data)
{
  Node **aux = root;

  while (*aux != NULL)
  {
    if (data.key < (*aux)->data.key)
      aux = &((*aux)->leftNode);
    else if (data.key > (*aux)->data.key)
      aux = &((*aux)->rightNode);
    else
      return false;
  }
  *aux = createNode(data);
  
  return true;
}

bool findBinaryTree(Node *root, int key, Data *data)
{
  Node *aux = root;

  while (aux)
  {
    if (key == aux->data.key)
    {
      *data = aux->data;
      return true;
    }

    if (key > aux->data.key)
      aux = aux->rightNode;
    else
      aux = aux->leftNode;
  }

  return false;
}