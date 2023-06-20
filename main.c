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
  size_t indexesSz = sizeof(Index) * input.quantity / PAGE_ITEMS;
  Index *indexes = malloc(indexesSz);
  int pos = readIndexesTable(indexes);
  if (pos == -1)
  {
    pos = createIndexesTable(indexes, file);
    pos = readIndexesTable(indexes);
  }
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

  Page *tree;
  startBTree(tree);
  Data x;
  x.key = key;

  fseek(file, 0, SEEK_SET);
  while (fread(&x, sizeof(Data), 1, file) == 1)
  {
    insertBTree(x, &tree, NULL);
  }

  x.key = key;

  // printBTree(tree);
  if (searchBTree(&x, tree, NULL))
  {
    printf("[+] Chave encontrada!\n");
    printf("Key -> %d | data1 -> %ld\n", x.key, x.data1);
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
  if (argc < 3)
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
  // printBinaryFile(file);

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
