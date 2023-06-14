#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "b_tree.h"

void startBTree(Page *tree)
{
  tree = NULL;
}

void searchBTree(Register *item, Page *ptr)
{
  long i = 1;

  if (ptr == NULL)
  {
    printf("[-] Registro não está presente na árvore.\n");
    return;
  }

  Register prevRegister = ptr->registers[0];

  // Pesquisa sequencial para encontrar o intervalo desejado
  while (i < ptr->n && item->key > prevRegister.key)
  {
    prevRegister = ptr->registers[i];
    i++;
  }

  if (item->key == prevRegister.key)
  {
    *item = prevRegister;
    return;
  }

  // Pesquisa em subárvores da esquerda
  if (item->key < prevRegister.key)
  {
    searchBTree(item, ptr->pointers[i - 1]);
    return;
  }

  // Pesquisa em subárvores da direita
  searchBTree(item, ptr->pointers[i]);
}

void printBTree(Page *tree)
{
  if (tree == NULL)
    return;

  for (int i = 0; i < tree->n; i++)
  {
    printBTree(tree->pointers[i]);

    if (i != tree->n)
    {
      printf(
          "Key: %d | data1: %ld | data2: %s | data3: %s  \n",
          tree->registers[i].key, tree->registers[i].data1,
          tree->registers[i].data2, tree->registers[i].data3);
    }
  }
}

void insertOnPage(Page *ptr, Register reg, Page *rightPtr)
{
  int k = ptr->n;
  bool foundPos = k <= 0;

  while (!foundPos)
  {
    if (reg.key >= ptr->registers[k - 1].key)
    {
      foundPos = true;
      break;
    }

    ptr->registers[k] = ptr->registers[k - 1];
    ptr->pointers[k + 1] = ptr->pointers[k];
    k--;

    if (k < 1)
      foundPos = true;
  }

  ptr->registers[k] = reg;
  ptr->pointers[k + 1] = rightPtr;
  ptr->n++;
}

void insert(Register reg, Page *ptr, bool *hasGrown, Register *returnReg, Page **returnPtr)
{
  long i = 1;
  long j;

  if (ptr == NULL)
  {
    *hasGrown = true;
    *returnReg = reg;
    *returnPtr = NULL;
    return;
  }

  while (i < ptr->n && reg.key > ptr->registers[i - 1].key)
    i++;

  if (reg.key == ptr->registers[i - 1].key)
  {
    printf("[-] Erro: Registro já está presente\n");
    *hasGrown = false;
    return;
  }

  if (reg.key < ptr->registers[i - 1].key)
    i--;

  insert(reg, ptr->pointers[i], hasGrown, returnReg, returnPtr);

  if (!*hasGrown)
    return;

  if (ptr->n < MM)
  {
    insertOnPage(ptr, *returnReg, *returnPtr);
    *hasGrown = false;
    return;
  }

  Page *tempPtr = (Page *)malloc(sizeof(Page));
  tempPtr->n = 0;
  tempPtr->pointers[0] = NULL;

  if (i < (M + 1))
  {
    insertOnPage(tempPtr, ptr->registers[MM - 1], ptr->pointers[MM]);
    ptr->n--;
    insertOnPage(ptr, *returnReg, *returnPtr);
  }
  else
    insertOnPage(tempPtr, *returnReg, *returnPtr);

  for (j = M + 2; j <= MM; j++)
  {
    insertOnPage(tempPtr, ptr->registers[j - 1], ptr->pointers[j]);
    ptr->n = M;
    tempPtr->pointers[0] = ptr->pointers[M + 1];
    *returnReg = ptr->registers[M];
    *returnPtr = tempPtr;
  }
}

void insertBTree(Register reg, Page **ptr)
{
  bool hasGrown;
  Register returnReg;
  Page *returnPtr;

  insert(reg, *ptr, &hasGrown, &returnReg, &returnPtr);

  if (hasGrown)
  {
    Page *tempPtr = (Page *)malloc(sizeof(Page));
    tempPtr->n = 1;
    tempPtr->registers[0] = returnReg;
    tempPtr->pointers[0] = *ptr;
    tempPtr->pointers[1] = returnPtr;
    *ptr = tempPtr;
  }
}