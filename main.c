#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file_handler.h"
#include "indexed.h"
#include "consts.h"
#include "b_tree.h"
#include "binary_tree.h"
#include "utils.h"

bool indexSearch(FILE *file, Input input)
{
  size_t indexesSz = (sizeof(Index) * input.quantity) / PAGE_ITEMS;
  Index *indexes = malloc(indexesSz);

  int reads = 0;

  createIndexesTable(indexes, file);

  Data item;
  fflush(stdout);
  item.key = input.key;

  if (indexedSearch(&item, file, input.situation, &reads))
  {
    printf("[INFO] Item encontrado.\n");
    printf("[INFO] %d leituras realizadas.\n", reads);
    printData(item);
    return true;
  }

  printf("[INFO] %d leituras realizadas.\n", reads);
  printf("Item não encontrado\n");
  free(indexes);
  return false;
}

bool bTree(int key, FILE *file)
{
  // Lê a página do arquivo
  Page *tree = malloc(sizeof(Page) * 1000000);
  FILE *bTreeFile = fopen(B_TREE_FILE, "wb");

  if (!bTreeFile)
    return false;

  Data item;
  item.key = key;

  rewind(file);

  int pos = 1;
  while (fread(&item, sizeof(Data), 1, file) == 1)
  {
    insertBTree(item, &tree, file, bTreeFile, pos++);
  }

  item.key = key;

  // printBTree(tree);
  if (searchBTree(&item, tree, file, bTreeFile))
  {
    printf("[+] Chave encontrada!\n");
    printData(item);
    return true;
  }

  printf("Chave não encontrada!\n");
  return false;
}

bool binaryTree(int key, FILE *dataFile)
{
  Node *root;
  startBinaryTree(&root);

  int reads = 0;

  createBinaryTree();
  Data item;

  item.key = key;

  if (searchBinaryTree(root, &item, dataFile, &reads))
  {
    printf("[+] Item encontrado!\n");
    printf("[+] %d leituras realizadas.\n", reads);
    printData(item);
    return true;
  }

  printf("[+] %d leituras realizadas.\n", reads);
  printf("[+] Item não encontrado!\n");
  return false;
}

int main(int argc, char *argv[])
{
  //  pesquisa <método> <quantidade> <situação> <chave> [-P]

  /*
     1 - método
     2 - quantidade
     3 - situação
     4 - chave
     5 - [-p] opcional para printar todo o arquivo
  */
  clock_t startClock = clock();
  if (argc < 5)
  {
    printf("[-] Número de argumentos inválidos.\n");
    return EXIT_FAILURE;
  }

  Input input;
  input.method = atoi(argv[1]);
  input.quantity = atoi(argv[2]);
  input.situation = atoi(argv[3]);
  input.key = atoi(argv[4]);

  FILE *file = fopen(DATA_FILE, "rb");
  if (!file)
  {
    printf("[FAIL] Arquivo de dados não encontrado.\n");
    generateBinaryFile(input.quantity, input.situation);
    file = fopen(DATA_FILE, "rb");
  }

  if (!file)
  {
    printf("[FAIL] Erro ao abrir o arquivo de dados.");
    return EXIT_FAILURE;
  }

  switch (input.method)
  {
  case INDEX:
    indexSearch(file, input);
    break;

  case BINARY_TREE:
    binaryTree(input.key, file);
    break;

  case B_TREE:
    bTree(input.key, file);
    break;

  default:
    printf("[FAIL] Método de pesquisa inválido.");
    return EXIT_FAILURE;
  }

  if (argc > 5 && strcmp(argv[5], "-p\n"))
    printBinaryFile(file);

  fclose(file);
  clock_t endClock = clock();
  double executionType = (double)(endClock - startClock) / CLOCKS_PER_SEC;

  printf("[INFO] Tempo de execução = %lfs.\n", executionType);

  return EXIT_SUCCESS;
}
