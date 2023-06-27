#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file_handler.h"
#include "indexed.h"
#include "consts.h"
#include "b_tree.h"
#include "b_star.h"
#include "binary_tree.h"
#include "utils.h"

int main(int argc, char *argv[])
{
  //  pesquisa <método> <quantidade> <situação> <chave> [-P]

  /* 1- método
     2 - quantidade
     3 - chave
     5 -
  */

  clock_t startClock = clock();
  if (argc < 5)
  {
    printf("[-] Número de argumentos inválidos.\n");
    return EXIT_FAILURE;
  }

  Input input;
  input.method = atoi(argv[1]);
  input.quantity = atoi(argv[2]);
  input.situation = atoi(argv[3]);
  input.key = atoi(argv[4]);

  if (argc > 5 && !strcmp(argv[5], "-s"))
  {
    setup(input);
    return EXIT_SUCCESS;
  }

  FILE *file = fopen(DATA_FILE, "rb");

  if (!file)
  {
    printf("[FAIl] Erro ao abrir o arquivo de dados.");
    return EXIT_FAILURE;
  }

  switch (input.method)
  {
  case INDEX:
    runIndexedSearch(file, input);
    break;
  case BINARY_TREE:
    runBinaryTree(input, file);
    break;
  case B_TREE:
    runBTree(input.key, file);
    break;
  case B_STAR:
    PointerType bstar = NULL;
    Data x;
    x.key = input.key;
    Quantifier quantifier = {0, 0};
    if (CreateBStar(file, input.quantity, &bstar, &quantifier))
    {

      printf("[Iniciando pesquisa na árvore B*...]");

      if (BStarSearch(&x, &bstar))
      {
        printf("Registro encontrado!");
      }

      else
      {
        printf("Registro não encontrado.");
      }
    }

    else
    {
      printf("Falha na criação da árvore B*.");
      return 0;
    }
    break;
  default:
    printf("[FAIL] Método inválido.\n");
    return EXIT_FAILURE;
  }
  if (argc > 5 && !strcmp(argv[5], "-p"))
    printBinaryFile(file);

  fclose(file);
  clock_t endClock = clock();
  double executionType = (double)(endClock - startClock) / CLOCKS_PER_SEC;

  printf("[INFO] Tempo de execução = %lfs.\n", executionType);

  return EXIT_SUCCESS;
}
