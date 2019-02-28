#pragma once
#include "cl-impl.h"
const int P = 31;
size_t fileSize (FILE* file);
char* readFile(FILE* file, size_t size);
long long int hash(char* arr, int size);
void AddToHash(list** table, char* arr, int size);
void FillTable(char* arr, list** table);
void printTable(list** table);
void emptyTable(list** table);
int findWord(list** table, char* word);
void equaliser(char* arr, int size);
#include "hash.c"
