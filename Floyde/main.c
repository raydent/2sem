#include "cl-impl.h"

int main(){
  list* head  = cl_create(0);
  list* temp = head;
  for (int i = 1; i < 10; i++){
    temp = cl_push(temp, i);
  }
  temp -> next = head -> next;
  isItLooped(head);
  // empty(head);
}
