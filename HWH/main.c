// #include "cl-impl.h"
// #include "trade.h"
#include "hash.h"
int main(){
  list** table = initTable();
  FILE* source = fopen("data.dat", "r");
  size_t size = fileSize(source);
  char* arr = readFile(source, size);
  // printf("%s", arr);
  FillTable(arr, table);
  // printf("table[34] = %s %s %d\n", table[34] -> data, table[34] -> next -> data, table[34] -> num);
  // printTable(table);
  int num  = findWord(table, "shaven");
  // long long int num = hash("man", strlen("worried"));
  printf("num = %d", num);
  // printf("table[i] = %s\n", table[num] -> next -> data);
  emptyTable(table);
}
