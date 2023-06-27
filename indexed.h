#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "consts.h"

int createIndexesTable(Index *indexes, FILE *dataFile);
bool indexedSearch(Data *item, FILE *file, Situation situation, int *reads);
int readIndexesTable(Index *indexes, int *reads);
int createIndexesTable(Index *indexes, FILE *dataFile);
int createIndexesTable(Index *indexes, FILE *dataFile);
void printIndexedTable(Index *indexes, size_t quantity);