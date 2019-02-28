#include "hash.h"
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
  // size_t size = fileSize(file);
  char* arr = (char*) calloc (size, sizeof(char));
  fread(arr, sizeof(char), size, file);
	// printf("%s", arr);
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
  // int size = strlen(arr);
	// char* temparr = (char*) calloc (size, sizeof(char));
	// strncpy(temparr, arr, size);
	// equaliser(temparr, size);
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
			// temp = temp % 10;
    }
    hashsum += (long long int)temp;
    temp = 0;
  }
	// free(temparr);
  return (hashsum % HASHNUM);
}
void FillTable(char* arr, list** table){
  int size = strlen(arr);
  int left = 0;
  int right = 0;
  int stringsize = 0;
	// char* temparr = (char*) calloc (10, sizeof(char));
  long long int hashsum = 0;
  for (left = 0; left < size; left++){
		// printf("left 0 = %c\n", arr[left]);
    if ((arr[left] >= 'A' && arr[left] <= 'Z') || (arr[left] >= 'a' && arr[left] <= 'z')){
      right = left + 1;
      while((arr[right] >= 'A' && arr[right] <= 'Z') || (arr[right] >= 'a' && arr[right] <= 'z')){
        right++;
      }
			// printf("left = %d, arr[left] = %c arr[right - 1] = %c\n", left, arr[left], arr[right - 1]);
      // stringsize = right - left;
      // hashsum = hash(arr + left, right - left);
			// temparr = realloc(temparr, (right - left)* sizeof(char));
			// strncpy(temparr, arr + left, right - left);
      AddToHash(table, arr + left, right - left);
			left = right;
			// printf("left = %d right = %d leftchar = %c rightchar = %c", left, right, arr[left], arr[right]);
    }
  }
}
void AddToHash(list** table, char* arr, int size){
  // long long int hashsum = hash(arr, size);
  list* temp = NULL;
	char* temparr = (char*) calloc (20, sizeof(char));
	strncpy(temparr, arr, size);
	equaliser(temparr, size);
	long long int hashsum = hash(temparr, size);
	// printf("hashsum = %d\n", hashsum);
  for (int i = 0; i < HASHNUM; i++){
		// printf("table[i] = %d, hashsum = %d", table[i] -> hashsum, hashsum);
    if ((int)table[i] -> hashsum == hashsum){
      temp = table[i];
			// printf("%d\n", temp -> hashsum);
	    while(temp -> data != NULL && strcmp(temp -> data, temparr) != 0 && temp -> next != NULL){
				temp = temp -> next;
				// printf("n\n");
			}
			if (temp -> data != NULL && strcmp(temp -> data, temparr) == 0){
				temp -> num += 1;
				// printf("condition 1, word = %s hash = %d num = %d\n", table[i] -> data, table[i] -> hashsum, table[i] -> num);
			}else	if (temp -> data == NULL){
				temp -> data = (char*) calloc (20, sizeof(char));
				strncpy(temp -> data, temparr, size);
				// table[i] = temp;
				temp -> hashsum = hashsum;
				temp -> num += 1;
				// printf("condition 2, word = %s\n", table[i] -> data);
			}else {
				arr_push(table[i], temparr, size);
				table[i] -> next -> hashsum = i;
				// printf("condition 3, word = %s, hash = %d\n", temparr, table[i] -> hashsum);
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
				// printf("count = %d\n", count);
				count++;
				temp = temp -> next;
			}
			// if (i == 34){
			// 	printf("temp -> next -> data = %s\n", temp -> next -> data);
			// }
			// if (temp -> data != NULL){
			// 	printf("num = %d, word = %s \n", table[i] -> num, table[i] -> data);
			// 	// printf("count = %d\n", count);
			// }
			count = 1;
			// printf("num = %d word = %s\n", table[i] -> num, table[i] -> data);
		}
	}
}
int findWord(list** table, char* word){
	// equaliser(word, strlen(word));
	// for(int i = 0; i < strlen (word); i++){
	// 	printf("i = %d\n", i);
	// 	if (word[i] <= 'Z' && word[i] >= 'A'){
	// 		word[i] = word[i] - 'A' + 'a';
	// 	}
	// }
	int size = strlen(word);
	char* temparr = (char*) calloc (size, sizeof(char));
	strncpy(temparr, word, size);
	equaliser(temparr, size);
	// printf("0\n");
	long long int hashsum = hash(word, strlen(word));
	// printf("hashsum = %lld\n", hashsum);
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
				// printf("hash = %lld", temp -> hashsum);
				// printf("temp -> num = %d\n", temp -> num);
				// printf("num = %d\n", temp -> num);
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
