#include <stdio.h>
#include "consts.h"

void clear()
{
  printf("\e[1;1H\e[2J");
}

void printData(Data data)
{
  printf("[INFO] Key = %d | Data1 = %ld | Data2 = %s | Data3 = %s\n", data.key, data.data1, data.data2, data.data3);
}