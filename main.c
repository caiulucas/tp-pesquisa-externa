#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fileHandler.h"
#include "indexed.h"
#include "indexesTable.h"
#include "consts.h"
#include "b_tree.h"

void indexedSearch(FILE *file)
{
  Index *indexes = malloc(sizeof(Index) * INDEXES_MAX);

  int pos = readIndexesTable(indexes);
  if (pos == -1)
    pos = createIndexesTable(indexes, file);

  Data item;
  fflush(stdout);
  printf("Digite a chave do item que deseja buscar: ");
  scanf("%d", &item.key);

  if (search(indexes, pos, &item, file))
  {
    printf("Item encontrado: %d %ld\n", item.key, item.data1);
  }
  else
  {
    printf("Item não encontrado\n");
  }

  fclose(file);
  free(indexes);
}

void bTreeSearch(FILE *file)
{
  Page *tree = (Page *)malloc(sizeof(Page));
  Register reg;
  Data data;
  startBTree(tree);

  FILE *bTreeFile = fopen(B_TREE_FILE, "rb");

  if (!bTreeFile)
  {
    bTreeFile = fopen(B_TREE_FILE, "wb");

    while (fread(&data, sizeof(Data), 1, file))
    {
      reg.key = data.key;
      reg.data1 = data.data1;
      strcpy(reg.data2, data.data2);
      strcpy(reg.data3, data.data3);

      insertBTree(reg, &tree, bTreeFile);
    } 
    fclose(bTreeFile);
    bTreeFile = fopen(B_TREE_FILE, "rb");
  }

  loadBTree(tree, bTreeFile);
  printBTree(tree);
  printf("Digite a chave do item que deseja buscar: ");
  scanf("%d", &reg.key);

  // printBTree(tree);
  if (searchBTree(&reg, tree, file))
    printf("Key: %d | Data1: %ld | Data2: %s | Data3: %s\n", reg.key, reg.data1, reg.data2, reg.data3);
  fclose(bTreeFile);
}

int main(int argc, char const *argv[])
{
  // if (argc < 5)
  // {
  //   printf("[-] Número de argumentos inválido.\n");
  //   printf("Padrão: ./exe <>");
  // }

  clock_t startTime = clock();
  FILE *file = fopen(DATA_FILE, "rb");

  if (!file)
  {
    printf("[-] Arquivo de dados não encontrado.\n");
    generateBinaryFile(100000);
    fclose(file);
    file = fopen(DATA_FILE, "rb");
  }

  if (!file)
  {
    printf("[-] Erro ao abrir o arquivo de dados.");
    return EXIT_FAILURE;
  }

  // printBinaryFile(file);
  printf("-------------------------\n");

  // indexedSearch(file);
  bTreeSearch(file);

  clock_t endTime = clock();

  double executionTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

  printf("[+] Tempo de execução = %lfs", executionTime);

  return EXIT_SUCCESS;
}
