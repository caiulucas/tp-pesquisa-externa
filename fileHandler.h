#pragma once
#define DATA2SIZE 10
#define DATA3SIZE 50

struct Data {
    int key;
    long int data1;
    char data2[DATA2SIZE];
    char data3[DATA3SIZE];
};

void generateRandomData(struct Data *data);
void generateBinaryFile(const char* filename, int numRecords);
void printBinaryFile(const char *filename);