#include <stdio.h>
#include <stdlib.h>
#include "fileHandler.h"
#include "indexed.h"
#include "indexesTable.h"
#include "consts.h"
#include "btree.h"
#include <stdlib.h>
bool fileHandling(Input input)
{
  FILE *file = fopen(DATA_FILE, "rb");
  if (!file)
  {
    printf("[-] Arquivo de dados não encontrado.\n");
    generateBinaryFile(input.quantity);
    file = fopen(DATA_FILE, "rb");
  }

  if (!file)
  {
    printf("[-] Erro ao abrir o arquivo de dados.");
    return false;
  }

  return true;
  printBinaryFile(file);
  printf("-------------------------\n");
}

bool index(FILE *file, int key)
{
  Index *indexes = malloc(sizeof(Index) * INDEXES_MAX);
  int pos = readIndexesTable(indexes);
  if (pos == -1)
    pos = createIndexesTable(indexes, file);
  Data item;
  fflush(stdout);
  item.key = key;

  free(indexes);

  if (indexedSearch(indexes, pos, &item, file))
  {
    printf("Item encontrado: %d %ld\n", item.key, item.data1);
    return true;
  }

  printf("Item não encontrado\n");
  free(indexes);
  return false;
}

bool bTree(FILE *file, int key)
{
   // Lê a página do arquivo
  pointerType tree;
  Initialize (tree);
  Data x;
  x.key = key;
  fread(&x, sizeof(Data), MM, file);
  if(bTreeSearch(&x, tree))
    printf ("Chave encontrada!") ;
  else
    printf ("Chave não encontrada!");

}



int main(int argc, char *argv[]) 
{
  //  pesquisa <método> <quantidade> <situação> <chave> [-P] 

  /* 1- método
     2 - quantidade
     3 - chave
     5 - 
  */
  FILE *file;
  
  Input input;
  input.method = atoi (argv[1]);
  input.quantity = atoi (argv[2]);
  input.key= atoi (argv[3]);

  printf ("%d %d\n", input.method, input.key);
  if(!fileHandling(input)) 
  {
    printf("[-] Falha ao abrir o arquivo.");
    return EXIT_FAILURE;
  }

  switch (input.method)
  {
  case 1:
    if(!index(file,input.key))
    {
      return EXIT_FAILURE;
    }
    break;
  case 2:
    if(!bTree(file,input.key))
    {
      return EXIT_FAILURE;
    }
    break;
  case 3:
  
    break;
  }
  return EXIT_SUCCESS;
}
