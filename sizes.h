#pragma once
#define DATA2SIZE 10
#define DATA3SIZE 50
#define ITENSPAGINA 4
#define MAXTABELA 100

typedef struct
{
  int key;
  long int data1;
  char data2[DATA2SIZE];
  char data3[DATA3SIZE];
} Data;

