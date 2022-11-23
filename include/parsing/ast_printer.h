#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include <ast.h>

void print_ast(struct ast_node *head);

char *ast_type_to_str(enum ast_type type);
char *var_type_to_str(enum var_type type);

#endif