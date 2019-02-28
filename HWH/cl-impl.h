#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
const int HASHNUM = 50;
typedef struct list{
    struct list* next;
    int d;
    char* data;
    long long int hashsum;
    int num;
}list;
list *cl_init();
list *cl_create(int d);
list *cl_push(list *pre, int d);
list *cl_pop(list *pre);
list* createCycleList(int* arr, int amount);
void empty(list* top);
void popArr(list* pre);
#include "cl-impl.c"
