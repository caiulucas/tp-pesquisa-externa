#pragma once
#include <stdio.h>
#include "sizes.h"

int readIndexesTable(Index *indexes);
int createIndexesTable(Index *indexes, FILE *dataFile);
