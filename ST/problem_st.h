#pragma once

#include "problem_lx.h"
enum node_kind_t { NODE_OP, NODE_VAL};
struct node_data_t {
  enum node_kind_t k;
  union {
    enum operation_t op;
    int d;
  } u;
};

struct node_t {
  struct node_t *left, *right;
  struct node_data_t data;
};
struct node_t* init_node();
struct node_t* parse_expr(struct lexem_t* lexems, int size);

// int parse_term(struct node_t* node, char* arr);
void UpgPrint();
struct node_t* maybe_plusminus(const struct lexem_t* lexems, int size);
struct node_t* maybe_muldiv(const struct lexem_t* lexems, int size);
struct node_t* maybe_braces(const struct lexem_t* lexems, int size);
struct node_t* maybe_number(const struct lexem_t* lexems, int size);

struct node_t *build_syntax_tree(struct lex_array_t lexarr);

int calc_result(struct node_t *top);
void TruePrint(struct node_t* head);
void free_syntax_tree(struct node_t * top);
int findBestOp(const struct lexem_t* lexems, int size);
void printLexString(const struct lexem_t* lexems, int size);
