#include <stdio.h>
#include "indexesTable.h"
#include "utils.h"

int readIndexesTable(Index *indexes)
{
  FILE *file = fopen(INDEXES_FILE, "rb");

  if (file == NULL)
  {
    printf("Tabela de indices não encontrada!\n");
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
    printf("[-] Erro ao abrir o arquivo\n");
    return 0;
  }

  Data item;

  // int count = 0;
  int pos = 0;

  while (fread(&item, sizeof(Data), 1, dataFile) == 1)
  {
    indexes[pos].key = item.key;
    indexes[pos].pos = pos + 1;
    fwrite(&indexes[pos], sizeof(Index), 1, file);
    pos++;
    fseek(dataFile, sizeof(Data) * (PAGE_ITEMS - 1), SEEK_CUR);

    clear();
    printf("[+] %d índices criados.\n", pos);
  }

  printf("[+] Tabela de índices criada com sucesso!\n");
  fclose(file);
  rewind(dataFile);
  return pos;
}

void printIndexedTable(Index *indexes, size_t quantity)
{
  for (size_t i = 0; i < quantity; i++)
  {
    printf("Key -> %d | Pos -> %d\n", indexes[i].key, indexes[i].pos);
  }
}