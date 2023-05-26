#pragma once
#include "sizes.h"
#define DATA2SIZE 10
#define DATA3SIZE 50

void generateRandomData(Data *data, int key);
void generateBinaryFile(const char* filename, int numRecords);
void printBinaryFile(const char *filename);