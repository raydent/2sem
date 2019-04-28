#include "problem_lx.h"
#include <string.h>
#include <ctype.h>
struct lex_array_t lex_string(const char *str) {
  assert(str != NULL);

  struct lex_array_t larr = { malloc(ICAP * sizeof(struct lexem_t)),
                              0,
                              ICAP };
  assert(larr.lexems != NULL);
  // TODO:
  // for each char in str
  //   if char reminds space, skip it
  //   if char reminds number, lex number
  //   if char reminds brace, lex brace
  //   if char reminds operation, lex operation
  //   otherwise free lex array, return NULL
  int cap = ICAP * 2;
  // printf("str[i] = %c\n", str[strlen(str)]);
  int j = 0;
  int bracecount = 0;
  for (int i = 0; i < strlen(str) - 1; i++){
    if (j == larr.capacity){
      cap *= 2;
      larr.lexems = realloc(larr.lexems, cap * sizeof(struct lexem_t));
      larr.capacity = cap;
    }
    if (isdigit(str[i]) != 0){
      if (larr.lexems[j - 1].kind == NUM){
        if (!isdigit(str[i - 1])){
          printf("ERROR0");
          exit(0);
        }
        larr.lexems[j - 1].lex.num = larr.lexems[j - 1].lex.num * 10 + str[i] - '0';
        continue;
      }
      larr.lexems[j].kind = NUM;
      larr.lexems[j].lex.num = str[i] - '0';
      j++;
    }
    else if (str[i] == '('){
      larr.lexems[j].kind = BRACE;
      larr.lexems[j].lex.b = LBRAC;
      j++;
      bracecount++;
    }
    else if (str[i] == ')'){
      larr.lexems[j].kind = BRACE;
      larr.lexems[j].lex.b = RBRAC;
      j++;
      bracecount--;
    }
    else if (str[i] == '+'){
        larr.lexems[j].kind = OP;
      larr.lexems[j].lex.op = ADD;
      if (larr.lexems[j - 1].kind != NUM && larr.lexems[j - 1].kind != BRACE){
        printf("ERROR");
        exit(0);
      }
      j++;
    }
    else if (str[i] == '-'){
        larr.lexems[j].kind = OP;
      larr.lexems[j].lex.op = SUB;
      if (larr.lexems[j - 1].kind != NUM && larr.lexems[j - 1].kind != BRACE){
        printf("ERROR");
        exit(0);
      }
      j++;
    }
    else if (str[i] == '*'){
        larr.lexems[j].kind = OP;
      larr.lexems[j].lex.op = MUL;
      if (larr.lexems[j - 1].kind != NUM && larr.lexems[j - 1].kind != BRACE){
        printf("ERROR");
        exit(0);
      }
      j++;
    }
    else if (str[i] == '/'){
        larr.lexems[j].kind = OP;
      larr.lexems[j].lex.op = DIV;
      if (larr.lexems[j - 1].kind != NUM && larr.lexems[j - 1].kind != BRACE){
        printf("ERROR");
        exit(0);
      }
      j++;
    }
    else if (str[i] == ' '){
      continue;
    }
    else{
      free(larr.lexems);
      larr.lexems = NULL;
      return larr;
    }
  }
  if (bracecount != 0){
    printf("ERROR");
    exit(0);
  }
  larr.size = j;
  return larr;
}

static void
print_op(enum operation_t opcode) {
  switch(opcode) {
    case ADD: printf(" PLUS"); break;
    case SUB: printf(" MINUS"); break;
    case MUL: printf(" MUL"); break;
    case DIV: printf(" DIV"); break;
    default: assert(0 && "unknown opcode");
  }
}

static void
print_brace(enum braces_t bracetype) {
  switch(bracetype) {
    case LBRAC: printf(" LBRAC"); break;
    case RBRAC: printf(" RBRAC"); break;
    default: assert(0 && "unknown bracket");
  }
}

static void
print_num(int n) {
  printf(" NUMBER:%d", n);
}

void
print_lexem(struct lexem_t lxm) {
  switch(lxm.kind) {
    case OP: print_op(lxm.lex.op); break;
    case BRACE: print_brace(lxm.lex.b); break;
    case NUM: print_num(lxm.lex.num); break;
    default: assert(0 && "unknown lexem");
  }
}

void dump_lexarray(struct lex_array_t pl) {
  int i;
  assert(pl.lexems != NULL);
  for (i = 0; i < pl.size; ++i){
    // printf("i = %d", i);
    print_lexem(pl.lexems[i]);
  }
}

void push_back(struct lex_array_t** larr, struct lexem_t lx){

}
