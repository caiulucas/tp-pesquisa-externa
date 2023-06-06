#include <stdio.h>
#include "sizes.h"

int readIndexesTable(Index **indexes)
{
  FILE *file = fopen("indexes.bin", "rb");

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
  FILE *file = fopen("indexes.bin", "wb");

  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo\n");
    return 0;
  }

  Data item;

  int count = 0;
  int pos = 0;

  fseek(dataFile, 0, SEEK_SET);

  printf("Criando tabela de índices...\n");
  while (fread(&item, sizeof(Data), 1, dataFile) == 1)
  {
    count++;
    if (count % PAGE_ITEMS == 1)
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
  fclose(file);

  return pos;
}