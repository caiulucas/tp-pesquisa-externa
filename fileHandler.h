#pragma once
#include "sizes.h"

void generateRandomData(Data *data, int key);
void generateBinaryFile(const char* filename, int numRecords);
void printBinaryFile(FILE *file);