#ifndef SYM_TABLE_H
#define SYM_TABLE_H

#include <ast.h>
#include <stdbool.h>

enum symbol_type
{
    VAR,
    FUNC
};

struct symbol_scope
{
    char *core;
    char *func;
};

struct symbol_node
{
    char *name;
    struct symbol_scope scope;
    enum symbol_type sym_type;
    enum var_type val_type; // variable type for variables, return type for fxns
    struct symbol_node *next;
};

int build_symbol_table(struct ast_node *a);
void print_symbol_table();
struct symbol_node *get_table();
bool check_exists(char *name, enum symbol_type type, char *core, char *fxn);
char *function_type_to_string(enum ast_type type);

#endif