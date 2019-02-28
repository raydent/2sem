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
  list* loop = isItLooped(top);
  while (loop != NULL){
    loop -> next = NULL;
    loop = isItLooped(top);
  }
  while(top -> next != NULL){
    cl_pop(top);
  }
  free(top);
}
list* isItLooped(list* head){
  list* rabbit = head;
  list* turtle = head;
  int count = 0;
  int state = 0;
  for (;;){
    if (rabbit -> next == turtle){
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
      if (rabbit -> next == turtle){
        state = 1;
        break;
      }
    }
    else if (rabbit -> next == NULL){
      break;
    }
  }
  // printf("state = %d\n", state);
  if (state == 1){
    return rabbit;
  }
  else
    return NULL;
}
int loopLen(list* head){
  list* turtle = head -> next;
  int counter = 1;
  while (turtle != head){
    turtle = turtle -> next;
    counter++;
  }
  return counter;
}
