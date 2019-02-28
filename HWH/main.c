
#include "hash.h"
int main(){
  list** table = initTable();
  FILE* source = fopen("data.dat", "r");
  size_t size = fileSize(source);
  char* arr = readFile(source, size);
  FillTable(arr, table);;
  int num  = findWord(table, "crumpled");
  printf("num = %d", num);
  emptyTable(table);
}
