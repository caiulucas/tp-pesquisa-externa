#include <stdio.h>
#include <stdlib.h>
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
  startBTree(tree);

  fseek(file, 0, SEEK_SET);
  while (fread(&reg, sizeof(Register), 1, file))
    insertBTree(reg, &tree);
    
  printf("Digite a chave do item que deseja buscar: ");
  scanf("%d", &reg.key);

  searchBTree(&reg, tree);

  printf("%d %ld", reg.key, reg.data1);
}

int main()
{
  FILE *file = fopen(DATA_FILE, "rb");

  if (!file)
  {
    printf("[-] Arquivo de dados não encontrado.\n");
    generateBinaryFile(200);
    file = fopen(DATA_FILE, "rb");
  }

  if (!file)
  {
    printf("[-] Erro ao abrir o arquivo de dados.");
    return EXIT_FAILURE;
  }

  printBinaryFile(file);
  printf("-------------------------\n");

  bTreeSearch(file);

  return EXIT_SUCCESS;
}
