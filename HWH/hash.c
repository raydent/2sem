#include "hash.h"
const int P = 31;
const int ARRSIZE = 30;
const int HASHNUM = 50;
size_t fileSize (FILE* file) {
	size_t size = 0;
	fseek (file, 0, SEEK_END);
	size = (size_t)ftell (file);
	if (size == 0) {
		printf ("File is empty\n");
		exit (1);
	}
	fseek (file, 0, SEEK_SET);
	return size;
}
char* readFile(FILE* file, size_t size){
  char* arr = (char*) calloc (size, sizeof(char));
  fread(arr, sizeof(char), size, file);
  return arr;
}
list** initTable(){
  list** hash_ = (list**) calloc (HASHNUM, sizeof(list*));
  for (int i = 0; i < HASHNUM; i++){
    hash_[i] = cl_init();
    hash_[i] -> hashsum = i;
		hash_[i] -> num = 0;
  }
  return hash_;
}
long long int hash(char* arr, int size){
	char tempchar = 0;
  long long int hashsum = 0;
  long long int temp = 0;
  for (int i = 0; i < size; i++){
		tempchar = arr[i];
		if (tempchar <= 'Z' && tempchar >= 'A'){
			tempchar = tempchar - 'A' + 'a';
		}
    temp = (long long int)(tempchar - 'a') * P;
    for (int n = 0; n < i; n++){
      temp *= P;
    }
    hashsum += (long long int)temp;
    temp = 0;
  }
  return (hashsum % HASHNUM);
}
void FillTable(char* arr, list** table){
  int size = strlen(arr);
  int left = 0;
  int right = 0;
  int stringsize = 0;
  long long int hashsum = 0;
  for (left = 0; left < size; left++){
    if ((arr[left] >= 'A' && arr[left] <= 'Z') || (arr[left] >= 'a' && arr[left] <= 'z')){
      right = left + 1;
      while((arr[right] >= 'A' && arr[right] <= 'Z') || (arr[right] >= 'a' && arr[right] <= 'z')){
        right++;
      }
      AddToHash(table, arr + left, right - left);
			left = right;
    }
  }
}
void AddToHash(list** table, char* arr, int size){
  list* temp = NULL;
	char* temparr = (char*) calloc (ARRSIZE, sizeof(char));
	strncpy(temparr, arr, size);
	equaliser(temparr, size);
	long long int hashsum = hash(temparr, size);
  for (int i = 0; i < HASHNUM; i++){
    if ((int)table[i] -> hashsum == hashsum){
      temp = table[i];
	    while(temp -> data != NULL && strcmp(temp -> data, temparr) != 0 && temp -> next != NULL){
				temp = temp -> next;
			}
			if (temp -> data != NULL && strcmp(temp -> data, temparr) == 0){
				temp -> num += 1;
			}else	if (temp -> data == NULL){
				temp -> data = (char*) calloc (ARRSIZE, sizeof(char));
				strncpy(temp -> data, temparr, size);
				temp -> hashsum = hashsum;
				temp -> num += 1;
			}else {
				arr_push(table[i], temparr, size);
				table[i] -> next -> hashsum = i;
			}
			break;
		}
  }
	free(temparr);
}
void printTable(list** table){
	list* temp = NULL;
	int count = 1;
	for (long long int i = 0; i < HASHNUM; i++){
		if (table[i] -> data != NULL){
			temp = table[i];
			while(temp -> next != NULL){
				printf("num = %d, word = %s \n", table[i] -> num, table[i] -> data);
				count++;
				temp = temp -> next;
			}
			count = 1;
		}
	}
}
int findWord(list** table, char* word){
	int size = strlen(word);
	char* temparr = (char*) calloc (size, sizeof(char));
	strncpy(temparr, word, size);
	equaliser(temparr, size);
	long long int hashsum = hash(word, strlen(word));
	for (long long int i = 0; i < HASHNUM; i++){
		if (i == hashsum){
			list* temp = table[i];
			while(temp -> data != NULL && strncmp(temp -> data, temparr, size) != 0 && temp -> next != NULL){
				temp = temp -> next;
			}
			if (temp -> data == NULL){
				free(temparr);
				printf("first state\n");
				return 0;
			}
			if (strncmp(temp -> data, temparr, size) == 0){
				free(temparr);
				return (temp -> num);
			}
			else{
				free(temparr);
				printf("third state\n");
				return 0;
			}
		}
	}
	return 0;
}
void emptyTable(list** table){
  for (int i = 0; i < HASHNUM; i++){
    popArr(table[i]);
  }
  free(table);
}
void equaliser(char* arr, int size){
	for (int i = 0; i < size; i++){
		if (arr[i] >= 'A' && arr[i] <= 'Z'){
			arr[i] = arr[i] - 'A' + 'a';
		}
	}
}
