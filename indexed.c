#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "indexed.h"

bool indexedSearch(Index indexes[], int size, Data *item, FILE *file, Situation situation)
{
  Data page[PAGE_ITEMS];

  // Procura pela página onde o item pode estar
  int i = 0;

  if (situation == ASC)
  {
    while (i < size && indexes[i].key < item->key)
      i++;
  }
  else
  {
    while (i < size && indexes[i].key > item->key)
      i++;
  }

  // Caso a chave desejada seja menor que a primeira chave, o item não existe
  if (i == 0)
    return false;

  size_t pageLength = PAGE_ITEMS;

  // Lê a página do arquivo
  size_t displacement = (indexes[i - 1].pos - 1) * PAGE_ITEMS * sizeof(Data);
  fseek(file, displacement, SEEK_SET);
  fread(&page, sizeof(Data), pageLength, file);

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