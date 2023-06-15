#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fileHandler.h"
#include "utils.h"

void generateRandomData(Data *data, int key)
{
  data->key = key;
  data->data1 = rand();

  // Generate random values for data2
  for (int i = 0; i < DATA2_SIZE; i++)
  {
    data->data2[i] = 'A' + rand() % 26;
  }
  data->data2[9] = '\0';

  // Generate random values for data3
  for (int i = 0; i < DATA3_SIZE; i++)
  {
    data->data3[i] = 'a' + rand() % 26;
  }
  data->data3[49] = '\0';
}

void generateBinaryFile(int numRecords)
{
  Data dataList[1000];
  FILE *file = fopen(DATA_FILE, "wb");

  if (file == NULL)
  {
    printf("[-] Não foi possível abrir o arquivo de dados.\n");
    return;
  }

  srand(time(NULL));
  const clock_t startClock = clock();

  for (int i = 0; i < numRecords; i++)
  {
    clear();
    printf("[+] %d de %d dados gerados.\n", i + 1, numRecords);

    generateRandomData(&dataList[i % 1000], i);

    if (i % 1001 == 1)
      fwrite(&dataList, sizeof(Data), 1000, file);
  }

  const clock_t endClock = clock();

  const double creationTime = ((double)(endClock - startClock)) / CLOCKS_PER_SEC;
  printf("[+] Arquivo de dados criado com sucesso em %lf segundos!\n", creationTime);
  fclose(file);
}

void printBinaryFile(FILE *file)
{
  Data data;
  while (fread(&data, sizeof(Data), 1, file))
  {
    printf("key: %d - data1: %ld - data2: %s - data3: %s\n", data.key, data.data1, data.data2, data.data3);
  }
  fseek(file, 0, SEEK_SET);
}