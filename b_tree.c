#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "b_tree.h"
#include "utils.h"

void startBTree(Page *tree)
{
  tree = NULL;
}

bool searchBTree(Register *item, Page *node)
{
  if (node == NULL)
  {
    printf("[-] Registro não está presente na árvore.\n");
    return false;
  }

  // Pesquisa sequencial para encontrar o intervalo desejado
  int i = 1;
  while (i < node->n && item->key > node->registers[i - 1].key)
    i++;

  if (item->key == node->registers[i - 1].key)
  {
    *item = node->registers[i - 1];
    return true;
  }

  // Pesquisa em subárvores da esquerda
  if (item->key < node->registers[i - 1].key)
  {
    return searchBTree(item, node->pointers[i - 1]);
  }

  // Pesquisa em subárvores da direita
  return searchBTree(item, node->pointers[i]);
}

void printBTree(Page *node)
{
  if (node == NULL)
    return;

  for (int i = 0; i < node->n; i++)
  {
    printBTree(node->pointers[i]);

    printf("Key: %d\n", node->registers[i].key);
  }
}

void insertOnPage(Page *node, Register reg, Page *rightNode)
{
  int index = node->n;
  bool foundPos = index <= 0;

  while (!foundPos)
  {
    if (reg.key >= node->registers[index - 1].key)
    {
      foundPos = true;
      break;
    }

    node->registers[index] = node->registers[index - 1];
    node->pointers[index + 1] = node->pointers[index];
    index--;

    if (index < 1)
      foundPos = true;
  }

  node->registers[index] = reg;
  node->pointers[index + 1] = rightNode;
  node->n++;
}

void insert(Register reg, Page *node, bool *hasGrown, Register *returnReg, Page **returnNode)
{
  if (node == NULL)
  {
    *hasGrown = true;
    *returnReg = reg;
    *returnNode = NULL;
    return;
  }

  int index = 1;

  while (index < node->n && reg.key > node->registers[index - 1].key)
    index++;

  if (reg.key == node->registers[index - 1].key)
  {
    clear();
    printf("[-] Erro: Registro %d já está presente\n", node->registers[index - 1].key);
    *hasGrown = false;
    return;
  }

  if (reg.key < node->registers[index - 1].key)
    index--;

  insert(reg, node->pointers[index], hasGrown, returnReg, returnNode);

  if (!*hasGrown)
    return;

  if (node->n < MM)
  {
    insertOnPage(node, *returnReg, *returnNode);
    *hasGrown = false;
    return;
  }

  Page *tempNode = (Page *)malloc(sizeof(Page));
  tempNode->n = 0;
  tempNode->pointers[0] = NULL;

  if (index < (M + 1))
  {
    insertOnPage(tempNode, node->registers[MM - 1], node->pointers[MM]);
    node->n--;
    insertOnPage(node, *returnReg, *returnNode);
  }
  else
    insertOnPage(tempNode, *returnReg, *returnNode);

  for (int j = M + 2; j <= MM; j++)
  {
    insertOnPage(tempNode, node->registers[j - 1], node->pointers[j]);
    node->n = M;
    tempNode->pointers[0] = node->pointers[M + 1];
    *returnReg = node->registers[M];
    *returnNode = tempNode;
  }
}

void insertBTree(Register reg, Page **node)
{
  bool hasGrown;
  Register returnReg;
  Page *returnNode;

  insert(reg, *node, &hasGrown, &returnReg, &returnNode);

  if (hasGrown)
  {
    Page *tempNode = (Page *)malloc(sizeof(Page));
    tempNode->n = 1;
    tempNode->registers[0] = returnReg;
    tempNode->pointers[0] = *node;
    tempNode->pointers[1] = returnNode;
    *node = tempNode;
  }
}