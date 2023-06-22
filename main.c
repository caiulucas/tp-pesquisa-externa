#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fileHandler.h"
#include "indexed.h"
#include "indexesTable.h"
#include "consts.h"
#include "b_tree.h"

bool fileHandling(Input input, FILE *file)
{
  return true;
}

bool indexSearch(FILE *file, Input input)
{
  size_t indexesSz = (sizeof(Index) * input.quantity) / PAGE_ITEMS;
  Index *indexes = malloc(indexesSz);

  int pos = readIndexesTable(indexes);
  if (pos == -1)
  {
    pos = createIndexesTable(indexes, file);
    pos = readIndexesTable(indexes);
  }

  printIndexedTable(indexes, input.quantity / PAGE_ITEMS);

  Data item;
  fflush(stdout);
  item.key = input.key;

  if (indexedSearch(indexes, pos, &item, file))
  {
    printf("Item encontrado: %d %ld\n", item.key, item.data1);
    return true;
  }

  printf("Item não encontrado\n");
  free(indexes);
  return false;
}

bool bTree(int key, FILE *file)
{
  // Lê a página do arquivo
  Page *tree = malloc(sizeof(Page) * 1000000);
  FILE *bTreeFile = fopen(B_TREE_FILE, "wb");

  if(!bTreeFile)
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
    printf("Key -> %d | data1 -> %ld\n", item.key, item.data1);
    return true;
  }

  printf("Chave não encontrada!\n");
  return false;
}

int main(int argc, char *argv[])
{
  //  pesquisa <método> <quantidade> <situação> <chave> [-P]

  /* 1- método
     2 - quantidade
     3 - chave
     5 -
  */
  clock_t startClock = clock();
  if (argc < 4)
  {
    printf("[-] Número de argumentos inválidos.\n");
    return EXIT_FAILURE;
  }

  Input input;
  input.method = atoi(argv[1]);
  input.quantity = atoi(argv[2]);
  input.key = atoi(argv[3]);

  FILE *file = fopen(DATA_FILE, "rb");
  if (!file)
  {
    printf("[-] Arquivo de dados não encontrado.\n");
    generateBinaryFile(input.quantity);
    file = fopen(DATA_FILE, "rb");
  }

  if (!file)
  {
    printf("[-] Erro ao abrir o arquivo de dados.");
    return EXIT_FAILURE;
  }

  if (argc > 4 && strcmp(argv[4], "-p\n"))
    printBinaryFile(file);

  printf("%d %d\n", input.method, input.key);

  switch (input.method)
  {
  case 1:
    if (!indexSearch(file, input))
      return EXIT_FAILURE;
    break;
  case 2:
    if (!bTree(input.key, file))
      return EXIT_FAILURE;

    break;
  case 3:
    break;
  }
  clock_t endClock = clock();
  double executionType = (double)(endClock - startClock) / CLOCKS_PER_SEC;

  printf("[+] Tempo de execução = %lfs.\n", executionType);

  return EXIT_SUCCESS;
}
