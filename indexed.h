#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "consts.h"

int createIndexesTable(Index *indexes, FILE *dataFile);
int createIndexesTable(Index *indexes, FILE *dataFile);
void printIndexedTable(Index *indexes, size_t quantity);
bool runIndexedSearch(FILE *file, Input input);