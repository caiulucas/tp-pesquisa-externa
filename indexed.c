#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "indexed.h"

bool search(Index indexes[], int size, Data *item, FILE *file)
{
  Data page[PAGE_ITEMS];

  // Procura pela página onde o item pode estar
  int i = 0;
  while (i < size && indexes[i].key <= item->key)
    i++;

  // Caso a chave desejada seja menor que a primeira chave, o item não existe
  if (i == 0)
    return false;

  int pageLength = PAGE_ITEMS;
  // A última página não deve ser completa
  if (i == size) //qual a necessidade?
  {
    fseek(file, 0, SEEK_END);
    pageLength = (ftell(file) / sizeof(Data)) % PAGE_ITEMS;
  }

  // Lê a página do arquivo
  int displacement = (indexes[i - 1].pos - 1) * PAGE_ITEMS * sizeof(Data);
  fseek(file, displacement, SEEK_SET);
  fread(&page, sizeof(Data), pageLength, file);

  // Pesquisa sequencial na página lida
  for (i = 0; i < pageLength; i++)
  {
    if (page[i].key == item->key)
    {
      *item = page[i];
      return true;
    }
  }

  return false;
}