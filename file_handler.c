#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file_handler.h"
#include "utils.h"

void generateRandomData(Data *data, int key)
{
  data->key = key;
  data->data1 = rand();

  // Gera dados aleatórios para data2
  for (int i = 0; i < DATA2_SIZE; i++)
  {
    data->data2[i] = 'A' + rand() % 26;
  }
  data->data2[DATA2_SIZE - 1] = '\0';

  // Gera dados aleatórios para data3
  for (int i = 0; i < DATA3_SIZE; i++)
  {
    data->data3[i] = 'a' + rand() % 26;
  }
  data->data3[DATA3_SIZE - 1] = '\0';
}

void generateAsc(Data *data, int length, FILE *file)
{
  for (int i = 0; i < length; i++)
  {
    clear();
    printf("[+] %d de %d dados gerados.\n", i + 1, length);

    // Gera dados aleatórios e salva em arquivo
    generateRandomData(data, i);
    fwrite(data, sizeof(Data), 1, file);
  }
}

void generateDesc(Data *data, int length, FILE *file)
{
  for (int i = length - 1; i >= 0; i--)
  {
    clear();
    printf("[+] %d de %d dados gerados.\n", length - i, length);

    // Gera dados aleatórios e salva em arquivo
    generateRandomData(data, i);
    fwrite(data, sizeof(Data), 1, file);
  }
}

void generateRandom(Data *data, int length, FILE *file)
{
  // Armazena os índices
  int *indices = (int *)malloc(length * sizeof(int)); 

  // Inicializa o array de índices
  for (int i = 0; i < length; i++)
  {
    indices[i] = i;
  }

  // Embaralha os índices do array
  for (int i = length - 1; i > 0; i--)
  {
    int j = rand() % (i + 1);
    int temp = indices[i];
    indices[i] = indices[j];
    indices[j] = temp;
  }

  for (int i = 0; i < length; i++)
  {
    // Pega a posição embaralhada e gera os dados
    int index = indices[i];
    clear();
    printf("[+] %d de %d dados gerados.\n", i + 1, length);

    generateRandomData(data, index);
    fwrite(data, sizeof(Data), 1, file);
  }

  free(indices);
}

void generateBinaryFile(int numRecords, Situation situation)
{
  Data data;
  FILE *file = fopen(DATA_FILE, "wb");

  if (file == NULL)
  {
    printf("[-] Não foi possível abrir o arquivo de dados.\n");
    return;
  }

  srand(time(NULL));
  // Marca o tempo de execução
  const clock_t startClock = clock();

  // Gera os dados de acordo com a situação
  switch (situation)
  {
  case ASC:
    generateAsc(&data, numRecords, file);
    break;
  case DESC:
    generateDesc(&data, numRecords, file);
    break;
  case RANDOM:
    generateRandom(&data, numRecords, file);
    break;
  default:
    break;
  }

  const clock_t endClock = clock();

  // Calcula o tempo de execução
  const double creationTime = ((double)(endClock - startClock)) / CLOCKS_PER_SEC;
  printf("[+] Arquivo de dados criado com sucesso em %lf segundos!\n", creationTime);
  fclose(file);
}

void printBinaryFile(FILE *file)
{
  Data data;
  while (fread(&data, sizeof(Data), 1, file) == 1)
  {
    printf("key: %d - data1: %ld - data2: %s - data3: %s\n", data.key, data.data1, data.data2, data.data3);
  }
  rewind(file);
}