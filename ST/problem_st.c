#include "problem_st.h"

// Grammar:
// expr ::= mult {+, -} expr | mult
// mult ::= term {*, /} mult | term
// term ::= ( expr ) | number
struct node_t* parse_expr(const struct lexem_t* lexems, int size){
  // struct node_t* node = (struct node_t*) calloc (1, sizeof(struct node_t));
  // node -> right = NULL;
  // node -> left = NULL;
  int count = 0;
  int state = 0;
  printLexString(lexems, size);
  struct node_t* node = (struct node_t*) calloc (1, sizeof(struct node_t));
  if (size == 1 && lexems[0].kind == NUM){
    node -> data.k = NODE_VAL;
    node -> data.u.d = lexems[0].lex.num;
    printf("num state\n");
    return node;
  }
  int num = maybe_plusminus_braces(lexems, size);
  if (num){
    printf("subadd state\n");
    node -> data.k = NODE_OP;
    node -> data.u.op = lexems[num].lex.op;
    node -> left = parse_expr(lexems, num);
    node -> right = parse_expr(lexems + num + 1, size - num - 1);
    return node;
  }
  num = maybe_muldiv_braces(lexems, size);
  if (num){
    printf("divmul state\n");
    node -> data.k = NODE_OP;
    node -> data.u.op = lexems[num].lex.op;
    node -> left = parse_expr(lexems, num);
    node -> right = parse_expr(lexems + num + 1, size - num - 1);
    return node;
  }
  int counter = 0;
  for (int i = 0; i < size; i++){
    if (lexems[i].kind == OP || lexems[i].kind == NUM){
      counter++;
    }
  }
  if (counter == 1){
    for (int i = 0; i < size; i++){
      if (lexems[i].kind == NUM){
        node -> data.k = NODE_VAL;
        node -> data.u.d = lexems[i].lex.num;
        printf("broken braces + num state\n");
        return node;
      }
    }
  }
  if (lexems[0].kind == BRACE && lexems[size - 1].kind == BRACE && lexems[0].lex.b == LBRAC && lexems[size - 1].lex.b == RBRAC){
    printf("size - 2 = %d\n", size - 2);
    int amount = 0;
    for (int i = 1; i < size; i++){
      if (lexems[i].kind == BRACE){
        if (lexems[i].lex.b == LBRAC){
          printf("+");
          amount++;
        }
        if (lexems[i].lex.b == RBRAC){
          amount--;
          printf("-");
        }
      }
    }
    printf("\n");
    if (amount == 0){
      printf("too much braces state\n");
      node =  parse_expr(lexems + 1, size - 2);
      // free(node);
      return node;
    }
  }
  printf("3\n");
  int k = findBestOp(lexems, size);
  if (k){
    printf("4\n");
    node -> data.k = NODE_OP;
    node -> data.u.op = lexems[k].lex.op;
    node -> left = parse_expr(lexems, k);
    node -> right = parse_expr(lexems + k + 1, size - k - 1);
    printf("bestopstate\n");
    return node;
  }
    printf("how?\n");
}
int findBestOp(const struct lexem_t* lexems, int size){
  int min = 100;
  int count = 0;
  int pos = 0;
  for (int i = 0; i < size; i++){
    if (lexems[i].kind == BRACE){
      if (lexems[i].lex.b == LBRAC){
        count++;
      }
      if (lexems[i].lex.b == RBRAC){
        count--;
      }
    }
    if (lexems[i].kind == OP && (lexems[i].lex.op == ADD || lexems[i].lex.op == SUB) && count < min){
      min = count;
      pos = i;
    }
  }
  for (int i = 0; i < size; i++){
    if (lexems[i].kind == BRACE){
      if (lexems[i].lex.b == LBRAC){
        count++;
      }
      if (lexems[i].lex.b == RBRAC){
        count--;
      }
    }
    if (lexems[i].kind == OP && (lexems[i].lex.op == MUL || lexems[i].lex.op == DIV) && count < min){
      min = count;
      pos = i;
    }
  }
  return pos;
}
int maybe_plusminus_braces(const struct lexem_t* lexems, int size){
  int count = 0;
  for (int i = 0; i < size; i++){
    if (lexems[i].kind == BRACE){
      if (lexems[i].lex.b == LBRAC){
        count++;
      }
      if (lexems[i].lex.b == RBRAC){
        count--;
      }
    }
    // printf("count = %d\n", count);
    if (count == 0 && lexems[i].kind == OP){
      if (lexems[i].lex.op == ADD || lexems[i].lex.op == SUB){
        assert(i);
        return i;
      }
    }
  }
  printf("break plusminus\n");
  return 0;
}
int maybe_muldiv_braces(const struct lexem_t* lexems, int size){
  int count = 0;
  for (int i = 0; i < size; ++i){
    if (lexems[i].kind == BRACE){
      if (lexems[i].lex.b == LBRAC){
        count++;
      }
      if (lexems[i].lex.b == RBRAC){
        count--;
      }
    }
    if (count == 0 && lexems[i].kind == OP){
      if (lexems[i].lex.op == MUL || lexems[i].lex.op == DIV){
        assert(i);
        return i;
      }
    }
  }
  return 0;
}
// int parse_term(node_t* node, char* arr);
// int FindBehindBraces(struct lexem_t* lexems, int size){
void printLexString(const struct lexem_t* lexems, int size){
  for (int i = 0; i < size; i++){
    if (lexems[i].kind == BRACE){
      if (lexems[i].lex.b == LBRAC){
        printf(" ( ");
      }
      if (lexems[i].lex.b == RBRAC){
        printf(" ) ");
      }
    }
    if (lexems[i].kind == NUM){
      printf(" %d ", lexems[i].lex.num);
    }
    if (lexems[i].kind == OP){
      if (lexems[i].lex.op == SUB){
        printf(" - ");
      }
      if (lexems[i].lex.op == ADD){
        printf(" + ");
      }
      if (lexems[i].lex.op == DIV){
        printf(" \\ ");
      }
      if (lexems[i].lex.op == MUL){
        printf(" * ");
      }
    }
  }
  printf("\n");
}
struct node_t* build_syntax_tree(struct lex_array_t lexarr) {
  // TODO: your code here
  // printLexString(lexarr.lexems, lexarr.size);
  return parse_expr(lexarr.lexems, lexarr.size);
}
void TruePrint(struct node_t* head){
  if (head -> data.k == NODE_OP){
    if (head -> data.u.op == SUB){
      printf("-\n");
    }
    if (head -> data.u.op == ADD){
      printf("+\n");
    }
    if (head -> data.u.op == MUL){
      printf("*\n");
    }
    if (head -> data.u.op == DIV){
      printf("делить\n");
    }
  }
  if (head -> data.k == NODE_VAL){
    printf("%d\n", head -> data.u.d);
  }
  if (head -> right != NULL){
    TruePrint(head -> right);
  }
  if (head -> left != NULL){
    TruePrint(head -> left);
  }
}
int calc_result(struct node_t *top) {
  // TODO: your code here
  // printf("turn\n");
  if (top -> data.k == NODE_OP){
    if (top -> right == NULL){
      printf("Error\n");
      exit(0);
    }
    if (top -> left == NULL){
      printf("ERROR\n");
      exit(0);
    }
    if (top -> data.u.op == ADD){
      return (calc_result(top -> left) + calc_result(top -> right));
    }
    if (top -> data.u.op == SUB){
      return (calc_result(top -> left) - calc_result(top -> right));
    }
    if (top -> data.u.op == DIV){
      return (calc_result(top -> left) / calc_result(top -> right));
    }
    if (top -> data.u.op == MUL){
      return (calc_result(top -> left) * calc_result(top -> right));
    }
  }
  if (top -> data.k == NODE_VAL){
    return top -> data.u.d;
  }
}

void free_syntax_tree(struct node_t * top) {
  // TODO: your code here
}
