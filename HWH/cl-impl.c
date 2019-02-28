#include "cl-impl.h"
// const int HASHNUM = 50;
list *cl_create(int d){
  list* newlist = (list*) calloc (1, sizeof (list));
  newlist -> data = NULL;
  newlist -> next = NULL;
  newlist -> num = 0;
  return newlist;
}
list *cl_init(){
  list* newlist = (list*) calloc (1, sizeof (list));
  newlist -> data = NULL;
  newlist -> next = NULL;
  newlist -> hashsum = HASHNUM;
  newlist -> num = 0;
}
list *arr_create(char* arr, int size){
  list* newlist = cl_init();
  newlist -> data = (char*) calloc (size, sizeof (char));
  strncpy(newlist -> data, arr, size);
  return newlist;
}
list *arr_push(list *pre, char* arr, int size){
  list* newlist = arr_create(arr, size);
  newlist -> num = 1;
  newlist -> next = pre -> next;
  pre -> next = newlist;
  // return newlist;
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
void popArr(list* pre){
  if (pre -> next != NULL){
    popArr(pre -> next);
  }
  if (pre -> data != NULL){
    free(pre -> data);
  }
  free(pre);
}
void empty(list* top){
  while (top -> next != NULL){
    empty(top);
  }
  free(top);
}
