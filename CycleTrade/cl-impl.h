#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
typedef struct list{
    struct list* next;
    int data;
    int num;
}list;
list *cl_create(int d);
list *cl_push(list *pre, int d);
list *cl_pop(list *pre);
list* createCycleList(int* arr, int amount);
void empty(list* top);
list* isItLooped(list* head);
int LoopLen(list* head);
// #include "cl-impl.c"
