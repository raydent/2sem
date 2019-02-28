#include "trade.h"
const int MOVE = 24;
int* readFile(int* amount, int* summ, FILE* source){
  fscanf(source, "%d %d", summ, amount);
  int* money = (int*) calloc (*amount, sizeof(int));
  for (int i = 0; i < *amount; i++){
    fscanf(source, "%d", &money[i]);
  }
  return money;
}
int bestTrade(int* money, int amount, int summ){
  qsort(money, amount, sizeof (int), comp);
  list* top = cl_create(money[0]);
  if (money[0] == 1){
    top -> num = 1;
  }
  list* temp = top;
  for (int i = 2; i <= money[amount - 1]; i++){
    temp = cl_push(temp, i);
    for (int n = 0; n < amount; n++){
      if (i == money[n]){
        temp -> num = 1;
      }
    }
  }
  temp -> next = top;
  temp = top;
  int min = 10000000;
  int count = 0;
  int max = summ + money[amount - 1];
  for (;;){
    if (temp -> data == summ && temp -> num < min){
      min = temp -> num;
    }
    if (temp -> data == max){
      break;
    }
    for (int i = 0; i < amount - 1; i++){
      list* temp2 = temp;
      count = money[i];
      while (count != 0){
        temp2 = temp2 -> next;
        count--;
      }
      if (temp2 -> num == 0 || (temp2 -> num > temp -> num)){
        temp2 -> num = temp -> num + 1;
      }
    }
    temp -> num ++;
    temp -> data = temp -> data + money[amount - 1];
    temp = temp -> next;
  }
  printf("min = %d", min);
  empty(top);
}
int comp (const void *i, const void *j){
return *(int*)i - *(int*)j;
}
