#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA2SIZE 10
#define DATA3SIZE 50

typedef struct
{
  int key;
  long int data1;
  char data2[DATA2SIZE];
  char data3[DATA3SIZE];
} Data;

void generateRandomData(Data *data, int key)
{
  data->key = key;

  // Generate random values for data1
  data->data1 = rand();

  // Generate random values for data2
  for (int i = 0; i < DATA2SIZE; i++)
  {
    data->data2[i] = 'A' + rand() % 26;
  }
  data->data2[9] = '\0';

  // Generate random values for data3
  for (int i = 0; i < DATA3SIZE; i++)
  {
    data->data3[i] = 'a' + rand() % 26;
  }
  data->data3[49] = '\0';
}

void generateBinaryFile(const char *filename, int numRecords)
{
  Data data;
  FILE *file = fopen(filename, "wb");
  if (file == NULL)
  {
    printf("Unable to open the file.\n");
    return;
  }

  srand(time(NULL));

  for (int i = 0; i < numRecords; i++)
  {
    printf("Generating data for record %d...\n", i + 1);

    generateRandomData(&data, i);
    fwrite(&data, sizeof(Data), 1, file);
  }

  fclose(file);

  printf("Binary file '%s' created successfully.\n", filename);
}

void printBinaryFile(const char *filename)
{
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
  {
    printf("Unable to open the file.\n");
    return;
  }
  
  while(!feof(file)) {
    Data data; 
    fread(&data, sizeof(Data), 1, file);

    printf("key: %d - data1: %ld - data2: %s - data3: %s\n", data.key, data.data1, data.data2, data.data3);
  }
}