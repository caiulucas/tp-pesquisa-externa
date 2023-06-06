#include <stdio.h>
#include "fileHandler.h"
#include "indexed.h"
#include "sizes.h"

// Indexada
// Arvore B
// Arvore B*

int main()
{
  FILE *file = fopen("data.bin", "rb");

  if(file == NULL)
  {
    printf("Erro ao abrir o arquivo\n");
    return 1;
  }

  printBinaryFile(file);
  printf("-------------------------\n");
  fseek(file, 0, SEEK_SET);

  Index indexes[INDEXES_MAX];
  Data item;
  
  int count = 0;
  int pos = 0;

  while(fread(&item, sizeof(Data), 1, file) == 1) {
    count++;
    if(count % PAGE_ITEMS == 1){
      indexes[pos].key = item.key;
      indexes[pos].pos = pos + 1;
      pos++;
    }
  }

  fflush(stdout);
  printf("Digite a chave do item que deseja buscar: ");
  scanf("%d", &item.key);

  if(search(indexes, pos, &item, file)) {
    printf("Item encontrado: %d %ld\n", item.key, item.data1);
  }
  else {
    printf("Item não encontrado\n");
  }

  fclose(file);
  return 0;
}
