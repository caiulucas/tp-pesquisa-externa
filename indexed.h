#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "consts.h"

bool indexedSearch(Index indexes[], int size, Data *item, FILE *file, Situation situation);