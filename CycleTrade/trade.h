#pragma once
#include "cl-impl.h"
#include <stdio.h>
int* readFile(int* amount, int* summ, FILE* source);
int bestTrade(int* money, int amount, int summ);
int comp (const void *, const void *);
#include "trade.c"
