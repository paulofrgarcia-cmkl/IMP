#ifndef SEM_ANALYSIS_H
#define SEM_ANALYSIS_H

#include <ast.h>
#include <symbol_table.h>

int check_semantics(struct ast_node *a, struct symbol_node *symtable);

#endif