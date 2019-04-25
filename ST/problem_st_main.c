#include "problem_st.h"

enum { MAXLEN = 1024 };

int main() {
  int res, result;
  struct lex_array_t larr;
  struct node_t *stree;
  char inp[MAXLEN] = {0};

  res = scanf("%1024c", inp);

  assert(res == 1);
  printf("inp = %s", inp);
  // lex to array of lexems
  larr = lex_string(inp);
  printLexString(larr.lexems, larr.size);
  // printLexString(larr.lexems, larr.size);
  // printf("x = %d\n", larr.size);
  if (larr.lexems == NULL) {
    printf("ERROR\n");
    return 0;
  }
  stree = build_syntax_tree(larr);
  // printf("end\n");
  // TruePrint(stree);
  // printf("res = %d", calc_result(stree));
  result = calc_result(stree);

  printf("res = %d\n", result);
  //
  free_syntax_tree(stree);
  free(larr.lexems);
  return 0;
}
