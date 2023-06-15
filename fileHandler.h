#pragma once
#include "consts.h"

void clear();
void generateRandomData(Data *data, int key);
void generateBinaryFile(int numRecords);
void printBinaryFile(FILE *file);