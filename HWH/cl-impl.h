#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
enum { HASHNUM = 50 };
typedef struct list{
    struct list* next;
    int d;
    char* data;
    long long int hashsum;
    int num;
}list;
list *cl_init();
list *arr_push(list *pre, char* arr, int size);
list *cl_create(int d);
list *cl_push(list *pre, int d);
list *cl_pop(list *pre);
list* createCycleList(int* arr, int amount);
void empty(list* top);
void popArr(list* pre);
// #include "cl-impl.c"
