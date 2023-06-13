#include <stdio.h>
#include "indexesTable.h"

int readIndexesTable(Index *indexes)
{
  FILE *file = fopen(INDEXES_FILE, "rb");

  if (file == NULL)
  {
    printf("Tabela de indices não encontrada!!\n");
    return -1;
  }

  int pos = 0;
  while (fread(&indexes[pos], sizeof(Index), 1, file) == 1)
  {
    pos++;
  }

  printf("Tabela de índices encontrada!!\n");
  fclose(file);
  return pos;
}

int createIndexesTable(Index *indexes, FILE *dataFile)
{
  FILE *file = fopen(INDEXES_FILE, "wb");

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo\n");
    return 0;
  }

  Data item;

  int count = 0;
  int pos = 0;

  printf("Criando tabela de índices...\n");
  while (fread(&item, sizeof(Data), 1, dataFile) == 1)
  {
    count++;
    if (count % PAGE_ITEMS == 1) // sugerir mudar o resto para 3
    {
      indexes[pos].key = item.key;
      indexes[pos].pos = pos + 1;
      pos++;
    }
  }

  for (int i = 0; i < pos; i++)
  {
    fwrite(&indexes[i], sizeof(Index), 1, file);
  }

  printf("Tabela de índices criada com sucesso!\n");
  // fclose(file);
  fseek(dataFile, 0, SEEK_SET);

  return pos;
}