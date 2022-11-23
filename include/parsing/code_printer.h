#ifndef CODE_PRINTER_H
#define CODE_PRINTER_H

#include "ast.h"
#include "arch.h"

void print_code(struct arch *a);
void print_core_code(FILE *fp, struct arch_core *c);
void print_function_code(FILE *fp, struct ir_instruction *code);
void print_instruction(FILE *fp, struct ir_instruction *code);

#endif
