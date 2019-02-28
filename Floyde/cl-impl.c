#pragma once
#include "cl-impl.h"
list *cl_create(int d){
  list* newlist = (list*) calloc (1, sizeof (list));
  newlist -> data = d;
  newlist -> next = NULL;
  newlist -> num = 0;
  return newlist;
}
list *cl_push(list *pre, int d){
  list* newlist = cl_create(d);
  newlist -> next = pre -> next;
  pre -> next = newlist;
  return newlist;
}
list *cl_pop(list *pre){
  if (pre -> next != NULL){
    list* temp = pre -> next -> next;
    free(pre -> next);
    pre -> next = temp;
  }
}
void empty(list* top){
  list* temp = top -> next;
  free(top);
  if (temp != NULL){
    empty(temp);
  }
}
void isItLooped(list* head){
  list* rabbit = head;
  list* turtle = head;
  int count = 0;
  int state = 0;
  for (;;){
    if (rabbit == turtle){
      state = 1;
      break;
    }
    if (rabbit -> next != NULL){
      turtle = turtle -> next;
      rabbit = rabbit -> next;
    }
    else if (rabbit -> next == NULL){
      break;
    }
    if (rabbit -> next != NULL){
      rabbit = rabbit -> next;
    }
    else if (rabbit -> next == NULL){
      break;
    }
  }
  printf("state = %d\n", state);
  turtle = turtle -> next;
  if (state != 0){
    while ((turtle -> next) != (rabbit -> next)){
      turtle = turtle -> next;
      count++;
    }
  }
  if (count == 0)
    printf("It's not looped\n");
  else
    printf("size of loop is %d\n", count);
}
