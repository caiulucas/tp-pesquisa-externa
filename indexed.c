#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "indexed.h"
#include "utils.h"

bool indexedSearch(Data *item, FILE *file, Situation situation, Quantifier *quantifier)
{
  // Abre arquivo
  FILE *indexesFile = fopen(INDEXES_FILE, "rb");

  if (!indexesFile)
    return false;

  // Calcula quantos itens existem no arquivo
  fseek(indexesFile, 0, SEEK_END);
  size_t size = ftell(indexesFile) / sizeof(Index);

  // Volta para o início do arquivo
  rewind(indexesFile);

  // Armazena os dados de um índice
  Data page[PAGE_ITEMS];

  // Pega a primeira página
  Index index;
  fread(&index, sizeof(Index), 1, indexesFile);
  quantifier->reads += 1;

  int i;
  // Pesquisa sequencial no arquivo de índices
  for (i = 0; i < size; i++)
  {
    if (feof(indexesFile))
      break;

    quantifier->comparisons += 1;

    // Se a chave desejada for menor que a chave do índice, volta uma posição
    if ((situation == ASC && index.key >= item->key) || (situation == DESC && index.key <= item->key))
    {
      fseek(indexesFile, -sizeof(Index), SEEK_CUR);
      break;
    }

    // Se a chave desejada for maior que a chave do índice, pega o próximo índice
    fread(&index, sizeof(Index), 1, indexesFile);
    quantifier->reads += 1;
  }

  // Volta uma página e lê a página
  fseek(indexesFile, -sizeof(Index), SEEK_CUR);
  fread(&index, sizeof(Index), 1, indexesFile);
  quantifier->reads += 1;

  size_t pageLength = PAGE_ITEMS;

  // Calcula o deslocamento da página no arquivo e busca por seus itens
  size_t displacement = (index.pos - 1) * PAGE_ITEMS * sizeof(Data);

  fseek(file, displacement, SEEK_SET);
  fread(&page, sizeof(Data), pageLength, file);
  quantifier->reads += 1;

  // Pesquisa sequencial na página lida
  for (i = 0; i < pageLength; i++)
  {
    // Se achou o item, retorna verdadeiro e o item
    if (page[i].key == item->key)
    {
      rewind(file);
      *item = page[i];
      return true;
    }
  }

  // Rebobina o arquivo e retorna falso
  rewind(file);
  return false;
}

int createIndexesTable(Index *indexes, FILE *dataFile)
{
  // Abre o arquivo de índices
  FILE *file = fopen(INDEXES_FILE, "wb");

  if (file == NULL)
  {
    printf("[-] Erro ao abrir o arquivo\n");
    return 0;
  }

  Data item;

  // Posição do índice no arquivo
  int pos = 0;

  // Lê os dados do arquivo de dados e cria os índices
  while (fread(&item, sizeof(Data), 1, dataFile) == 1)
  {
    indexes[pos].key = item.key;
    indexes[pos].pos = pos + 1;
    fwrite(&indexes[pos], sizeof(Index), 1, file);
    pos++;
    // Pula para o primeiro item da próxima página
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
  // Calcula o tamanho da tabela de índices
  size_t indexesSz = (sizeof(Index) * input.quantity) / PAGE_ITEMS;
  Index *indexes = malloc(indexesSz);

  Quantifier quantifier;

  Data item;
  item.key = input.key;

  // Busca o item no arquivo e imprime o resultado
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
