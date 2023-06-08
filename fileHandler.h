#pragma once
#include "consts.h"

void generateRandomData(Data *data, int key);
FILE *generateBinaryFile(int numRecords);
void printBinaryFile(FILE *file);