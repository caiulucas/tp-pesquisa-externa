#pragma once
#include <stdio.h>
#include "consts.h"

int readIndexesTable(Index *indexes);
int createIndexesTable(Index *indexes, FILE *dataFile);
void printIndexedTable(Index *indexes, size_t quantity);
