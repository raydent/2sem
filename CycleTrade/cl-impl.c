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
// list* createCycleList(int* arr, int amount){
//   list* first = cl_create(arr[0]);
//   list* temp = first;
//   for (int i = 1; i < arr[amount - 1]; i++){
//     temp = cl_push(temp, arr[i]);
//   }
//   temp -> next = first;
//   return temp;
// }
void empty(list* top){
  list* temp = top -> next;
  free(top);
  if (temp != NULL){
    empty(temp);
  }
}
