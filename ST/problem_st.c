#include "problem_st.h"

// Grammar:
// expr ::= mult {+, -} expr | mult
// mult ::= term {*, /} mult | term
// term ::= ( expr ) | number

struct node_t* init_node(){
  struct node_t* node = (struct node_t*) calloc (1, sizeof(struct node_t));
  node -> right = NULL;
  node -> left = NULL;
};

struct lexem_t* p;
struct node_t* parse_expr(struct lexem_t* lexems, int size){
  p = lexems;
  struct node_t* node = maybe_plusminus(lexems, size);
  return node;
}

struct node_t* maybe_plusminus(const struct lexem_t* lexems, int size){
  UpgPrint();
  struct node_t* left = maybe_muldiv(lexems, size);
  if (p == lexems + size){
    printf("plusmin return case\n");
    return left;
  }
  // struct node_t* node = init_node();
  while ((*p).kind == OP && ((*p).lex.op == SUB || (*p).lex.op == ADD)){
    printf("+-\n");
    struct node_t* temp = init_node();
    temp -> data.k = NODE_OP;
    temp -> data.u.op = (*p).lex.op;
    p++;
    struct node_t* right = maybe_muldiv(lexems, size);
    temp -> left = left;
    temp -> right = right;
    left = temp;
  }
  return left;
}

struct node_t* maybe_muldiv(const struct lexem_t* lexems, int size){
  UpgPrint();
  struct node_t* left = maybe_braces(lexems, size);
  if (p == lexems + size){
    printf("muldiv return case\n");
    return left;
  }
  while ((*p).kind == OP && ((*p).lex.op == MUL || (*p).lex.op == DIV)){
    printf("*\\ \n");
    struct node_t* temp = init_node();
    temp -> data.k = NODE_OP;
    temp -> data.u.op = (*p).lex.op;
    p++;
    struct node_t* right = maybe_braces(lexems, size);
    temp -> left = left;
    temp -> right = right;
    left = temp;
  }
  return left;
}

struct node_t* maybe_braces(const struct lexem_t* lexems, int size){
  UpgPrint();
  if ((*p).kind == BRACE){
    if((*p).lex.b == LBRAC){
      p++;
      struct node_t* node = maybe_plusminus(lexems, size);
      // UpgPrint();
      assert((*p).kind == BRACE && (*p).lex.b == RBRAC);
      printf(")\n");
      p++;
      return node;
    }
    // else{
    //
    // }
  }
  else
    return maybe_number(lexems, size);
}

struct node_t* maybe_number(const struct lexem_t* lexems, int size){
  UpgPrint();
  assert(p <= lexems + size);
  if ((*p).kind == NUM){
    // printf("breakpoint1\n");
    struct node_t* node = init_node();
    // printf("breakpoint2\n");
    node -> data.k = NODE_VAL;
    node -> data.u.d = (*p).lex.num;
    p++;
    printf("returning");
    return node;
  }
  else {
    printf("Error with number occured, p - lexems = %d", p - lexems);
    exit(0);
  }
}

void UpgPrint(){
  if ((*p).kind == NUM){
    printf("%d\n", (*p).lex.num);
  }
  if ((*p).kind == BRACE){
    if ((*p).lex.b == RBRAC){
      printf(")\n");
    }
    if ((*p).lex.b == LBRAC){
      printf("(\n");
    }
  }
  if ((*p).kind == OP){
    if ((*p).lex.op == MUL)
      printf("*\n");
    if ((*p).lex.op == SUB)
      printf("-\n");
    if ((*p).lex.op == DIV)
      printf("\\\n");
    if ((*p).lex.op == ADD)
      printf("+\n");
  }
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
  if (top -> right != NULL){
    free_syntax_tree(top -> right);
  }
  if (top -> left != NULL){
    free_syntax_tree(top -> left);
  }
  free(top);
}
