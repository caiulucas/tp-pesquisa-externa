#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "b_tree.h"
#include "utils.h"

void startBTree(Page *tree)
{
  tree = NULL;
}

bool searchBTree(Data *item, Page *node, Quantifier *quantifier)
{
  if (node == NULL)
  {
    quantifier->comparisons++;
    printf("[-] Registro não está presente na árvore.\n");
    return false;
  }

  // Pesquisa sequencial para encontrar o intervalo desejado
  int i = 1;

  // Encontra o intervalo
  while (i < node->n && item->key > node->regs[i - 1].key)
    i++;

  // Se a chave desejada for igual a chave do índice, retorna o item
  if (item->key == node->regs[i - 1].key)
  {
    quantifier->comparisons++;
    *item = node->regs[i - 1];
    return true;
  }

  // Pesquisa em subárvores da esquerda
  if (item->key < node->regs[i - 1].key)
  {
    quantifier->comparisons++;
    return searchBTree(item, node->pointers[i - 1], quantifier);
  }

  // Pesquisa em subárvores da direita
  quantifier->comparisons++;
  return searchBTree(item, node->pointers[i], quantifier);
}

void printBTree(Page *node)
{
  if (node == NULL)
    return;

  for (int i = 0; i < node->n; i++)
    printBTree(node->pointers[i]);
}

void insertOnPage(Page *node, Data reg, Page *rightNode)
{
  // Encontra a posição correta para inserir o registro
  int index = node->n;
  bool foundPos = index <= 0;

  // Se não achou posição, procura a posição correta
  while (!foundPos)
  {
    if (reg.key >= node->regs[index - 1].key)
    {
      foundPos = true;
      break;
    }

    // Move os registros e ponteiros para a direita
    node->regs[index] = node->regs[index - 1];
    node->pointers[index + 1] = node->pointers[index];
    index--;

    if (index < 1)
      foundPos = true;
  }

  // Insere o registro na posição correta
  node->regs[index] = reg;
  node->pointers[index + 1] = rightNode;
  node->n++;
}

void insert(Data reg, Page *node, bool *hasGrown, Data *returnReg, Page **returnNode, FILE *file)
{
  // Se a página for nula, cria uma nova página
  if (!node)
  {
    *hasGrown = true;
    *returnReg = reg;
    *returnNode = NULL;
    return;
  }

  // Encontra a posição correta para inserir o registro
  int index = 1;

  while (index < node->n && reg.key > node->regs[index - 1].key)
    index++;

  // Verifica se o registro já está presente
  if (reg.key == node->regs[index - 1].key && reg.key != 0)
  {
    clear();
    printf("[-] Erro: Registro %d já está presente\n", node->regs[index - 1].key);
    *hasGrown = false;
    return;
  }

  // Verifica se o registro deve ser inserido na subárvore da esquerda ou direita
  if (reg.key < node->regs[index - 1].key)
    index--;

  insert(reg, node->pointers[index], hasGrown, returnReg, returnNode, file);

  if (!*hasGrown)
    return;

  // Se a página não estiver cheia, insere o registro na página
  if (node->n < MM)
  {
    insertOnPage(node, *returnReg, *returnNode);
    *hasGrown = false;
    return;
  }

  // Se a página estiver cheia, divide a página
  Page *tempNode = (Page *)malloc(sizeof(Page));
  tempNode->n = 0;
  tempNode->pointers[0] = NULL;

  // Se índice menor q M + 1, registro deve ser inserido na primeira metade da página
  if (index < (M + 1))
  {
    insertOnPage(tempNode, node->regs[MM - 1], node->pointers[MM]);
    node->n--;
    insertOnPage(node, *returnReg, *returnNode);
  }
  else // Se índice maior q M + 1, registro deve ser inserido na segunda metade da página
    insertOnPage(tempNode, *returnReg, *returnNode);

  // Move os registros e ponteiros para a nova página
  for (int j = M + 2; j <= MM; j++)
  {
    insertOnPage(tempNode, node->regs[j - 1], node->pointers[j]);
    node->n = M;
    tempNode->pointers[0] = node->pointers[M + 1];
    *returnReg = node->regs[M];
    *returnNode = tempNode;
  }
}

void insertBTree(Data reg, Page **node, FILE *file)
{
  bool hasGrown;
  Data returnReg;
  Page *returnNode;

  // Insere o registro na árvore
  insert(reg, *node, &hasGrown, &returnReg, &returnNode, file);

  // Se a árvore cresceu, cria uma nova raiz
  if (hasGrown)
  {
    Page *tempNode = (Page *)malloc(sizeof(Page));
    tempNode->n = 1;
    tempNode->regs[0] = returnReg;
    tempNode->pointers[0] = *node;
    tempNode->pointers[1] = returnNode;
    *node = tempNode;
  }
}

bool runBTree(int key, FILE *file)
{
  // Lê a página do arquivo
  Page *tree = (Page *)malloc(sizeof(Page));
  startBTree(tree);

  Data item;
  item.key = key;

  rewind(file);

  // Insere os registros na árvore
  while (fread(&item, sizeof(Data), 1, file) == 1)
    insertBTree(item, &tree, file);

  item.key = key;
  Quantifier quantifier = {0, 0};

  // Pesquisa o registro na árvore
  if (searchBTree(&item, tree, &quantifier))
  {
    printf("[SUCCESS] Chave encontrada!\n");
    printf("[INFO] Quantidade de leituras: %d\n", quantifier.reads);
    printf("[INFO] Quantidade de comparações: %d\n", quantifier.comparisons);
    printData(item);
    return true;
  }

  printf("[FAIL] Chave não encontrada!\n");
  printf("[INFO] Quantidade de leituras: %d\n", quantifier.reads);
  printf("[INFO] Quantidade de comparações: %d\n", quantifier.comparisons);
  return false;
}
