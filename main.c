#include <stdio.h>
#include "fileHandler.h"
#include "sequencialIndexado.h"
#include "sizes.h"

// Indexada
// Arvore B
// Arvore B*

int main()
{
  //printBinaryFile("data.bin");
  FILE *file = fopen("data.bin", "rb");


  tipoindice tab[ITENSPAGINA];
  Data *data;
  data->key = 9;

  int gotit = pesquisa(tab, 100, data, file);
  printf("%d", gotit);
  
  fclose(file);
  return 0;
}
