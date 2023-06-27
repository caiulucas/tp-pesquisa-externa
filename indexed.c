#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "indexed.h"
#include "utils.h"

bool indexedSearch(Data *item, FILE *file, Situation situation, Quantifier *quantifier)
{
  FILE *indexesFile = fopen(INDEXES_FILE, "rb");

  if (!indexesFile)
    return false;

  fseek(indexesFile, 0, SEEK_END);
  size_t size = ftell(indexesFile) / sizeof(Index);

  rewind(indexesFile);

  Data page[PAGE_ITEMS];

  // Procura pela página onde o item pode estar

  Index index;
<<<<<<< HEAD
  fread(&index, sizeof(Index), 1, indexesFile);
  quantifier->reads += 1;
=======
>>>>>>> d187e0d (feat: new branch)

  int i;
  for (i = 0; i < size; i++)
  {
    if (feof(indexesFile))
      break;

    quantifier->comparisons += 1;
    if ((situation == ASC && index.key >= item->key) || (situation == DESC && index.key <= item->key))
    {
      fseek(indexesFile, -sizeof(Index), SEEK_CUR);
      break;
    }

    fread(&index, sizeof(Index), 1, indexesFile);
    quantifier->reads += 1;
  }

  fseek(indexesFile, -sizeof(Index), SEEK_CUR);
  fread(&index, sizeof(Index), 1, indexesFile);
  quantifier->reads += 1;

  // Caso a chave desejada seja menor que a primeira chave, o item não existe

  size_t pageLength = PAGE_ITEMS;

  // Lê a página do arquivo
  size_t displacement = (index.pos - 1) * PAGE_ITEMS * sizeof(Data);

  fseek(file, displacement, SEEK_SET);
  fread(&page, sizeof(Data), pageLength, file);
  quantifier->reads += 1;

  // Pesquisa sequencial na página lida
  for (i = 0; i < pageLength; i++)
  {
    if (page[i].key == item->key)
    {
      rewind(file);
      *item = page[i];
      return true;
    }
  }

  rewind(file);
  return false;
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
    printf("Key -> %d | Pos -> %d\n", indexes[i].key, indexes[i].pos);
}

bool runIndexedSearch(FILE *file, Input input)
{
  size_t indexesSz = (sizeof(Index) * input.quantity) / PAGE_ITEMS;
  Index *indexes = malloc(indexesSz);

  Quantifier quantifier;

  Data item;
  item.key = input.key;

  if (indexedSearch(&item, file, input.situation, &quantifier))
  {
    printf("[SUCCESS] Item encontrado.\n");
    printf("[INFO] %d leituras realizadas.\n", quantifier.reads);
    printf("[INFO] %d comparações realizadas.\n", quantifier.comparisons);
    printData(item);
    return true;
  }

  printf("[INFO] %d leituras realizadas.\n", quantifier.reads);
  printf("[INFO] %d comparações realizadas.\n", quantifier.comparisons);
  printf("[FAIL] Item não encontrado\n");
  free(indexes);
  return false;
}
