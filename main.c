#include <stdio.h>
#include <stdlib.h>
#include "fileHandler.h"
#include "indexed.h"
#include "indexesTable.h"
#include "consts.h"

int main()
{
  FILE *file = fopen(DATA_FILE, "rb");

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }

  printBinaryFile(file);
  printf("-------------------------\n");

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

  return 0;
}
