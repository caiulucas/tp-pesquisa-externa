#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "b_tree.h"
#include "utils.h"

bool searchBTree(Data *item, Page *node, FILE *dataFile, FILE *bTreeFile)
{
  if (node == NULL)
  {
    printf("[-] Registro não está presente na árvore.\n");
    return false;
  }

  // Pesquisa sequencial para encontrar o intervalo desejado
  int i = 1;

  while (i < node->n && item->key > node->keys[i - 1])
    i++;

  if (item->key == node->keys[i - 1])
  {
    size_t displacement = node->children[i - 1] * sizeof(Data);
    fseek(dataFile, displacement, SEEK_SET);
    fread(item, sizeof(Data), 1, dataFile);
    return true;
  }

  // Pesquisa em subárvores da esquerda
  size_t displacement;
  if (item->key < node->keys[i - 1])
    displacement = node->children[i - 1] * sizeof(Data);
  else
    displacement = node->children[i] * sizeof(Data);

  Page *aux = (Page *)malloc(sizeof(Page));
  fseek(bTreeFile, displacement, SEEK_SET);
  fread(aux, sizeof(Page), 1, bTreeFile);

  return searchBTree(item, aux, dataFile, bTreeFile);
}

void printBTree(Page *node, FILE *bTreeFile)
{
  if (node == NULL)
    return;

  for (int i = 0; i < node->n; i++)
  {
    Page *aux = (Page *)malloc(sizeof(Page));
    size_t displacement = node->children[i] * sizeof(Page);
    fseek(bTreeFile, displacement, SEEK_SET);
    fread(aux, sizeof(Page), 1, bTreeFile);
    printBTree(aux, bTreeFile);
    printf("Key: %d\n", node->keys[i]);
  }
}

void insertOnPage(Page *node, int key, Page *rightNode, FILE *bTreeFile)
{
  int index = node->n;
  bool foundPos = index <= 0;

  while (!foundPos)
  {
    if (key >= node->keys[index - 1])
    {
      foundPos = true;
      break;
    }

    node->keys[index] = node->keys[index - 1];
    node->children[index + 1] = node->children[index];
    index--;

    if (index < 1)
      foundPos = true;
  }

  node->keys[index] = key;
  node->children[index + 1] = rightNode->pos;
  node->n++;
  fwrite(node, sizeof(Page), 1, bTreeFile);
}

void insert(Data reg, Page *node, bool *hasGrown, Data *returnReg, Page **returnNode, FILE *file, FILE *bTreeFile)
{
  if (!node)
  {
    *hasGrown = true;
    *returnReg = reg;
    *returnNode = NULL;
    return;
  }

  int index = 1;

  while (index < node->n && reg.key > node->keys[index - 1])
    index++;

  // if (reg.key == node->keys[index - 1] && reg.key != 0)
  // {
  //   printf("[-] Erro: Registro %d já está presente\n", node->keys[index - 1]);
  //   *hasGrown = false;
  //   return;
  // }

  if (reg.key < node->keys[index - 1])
    index--;

  Page *aux = (Page *)malloc(sizeof(Page));
  size_t displacement = node->children[index] * sizeof(Page);
  fseek(bTreeFile, displacement, SEEK_SET);
  fread(aux, sizeof(Page), 1, bTreeFile);
  printf("children %d \n", index);
  insert(reg, aux, hasGrown, returnReg, returnNode, file, bTreeFile);

  if (!*hasGrown)
    return;

  if (node->n < MM)
  {
    insertOnPage(node, returnReg->key, *returnNode, bTreeFile);
    *hasGrown = false;
    return;
  }

  Page *tempNode = (Page *)malloc(sizeof(Page));
  tempNode->n = 0;
  tempNode->children[0] = -1;

  if (index < (M + 1))
  {
    aux = (Page *)malloc(sizeof(Page));
    size_t displacement = node->children[MM] * sizeof(Page);
    fseek(bTreeFile, displacement, SEEK_SET);
    fread(aux, sizeof(Page), 1, bTreeFile);

    insertOnPage(tempNode, node->keys[MM - 1], aux, bTreeFile);
    node->n--;
    insertOnPage(node, returnReg->key, *returnNode, bTreeFile);
  }
  else
    insertOnPage(tempNode, returnReg->key, *returnNode, bTreeFile);

  for (int j = M + 2; j <= MM; j++)
  {
    aux = (Page *)malloc(sizeof(Page));
    size_t displacement = node->children[j] * sizeof(Page);
    fseek(bTreeFile, displacement, SEEK_SET);
    fread(aux, sizeof(Page), 1, bTreeFile);

    insertOnPage(tempNode, node->keys[j - 1], aux, bTreeFile);
    node->n = M;
    tempNode->children[0] = node->children[M + 1];
    returnReg->key = node->keys[M];
    *returnNode = tempNode;
  }

  free(aux);
  free(tempNode);
}

void insertBTree(Data reg, Page **node, FILE *dataFile, FILE *bTreeFile, int pos)
{
  bool hasGrown;
  Data returnReg;
  Page *returnNode;

  insert(reg, *node, &hasGrown, &returnReg, &returnNode, dataFile, bTreeFile);

  if (hasGrown)
  {
    Page *tempNode = (Page *)malloc(sizeof(Page));
    tempNode->n = 1;
    tempNode->pos = pos;
    tempNode->keys[0] = returnReg.key;
    tempNode->children[0] = (*node)->pos;
    tempNode->children[1] = returnNode->pos;
    *node = tempNode;
    fwrite(tempNode, sizeof(Page), 1, bTreeFile);
    free(tempNode);
  }
}