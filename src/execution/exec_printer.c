#include <stdio.h>

#include <arch.h>
#include <code_printer.h>

#include <exec_printer.h>
#include <var_mapping.h>

// char *opcode_strings[] = {"push", "pop", "jmp", "alu", "ctrl", "nop", "ref"};
// char *alu_ops_strings[] = {"add", "sub", "mul", "div", "and", "or", "lt", "leq", "gt", "geq", "eq", "neq"};

void print_var_mappings(FILE *out, struct var_mapping *vars)
{
    while (vars != NULL)
    {
        fprintf(out, "%s:%d ", vars->name, vars->val);
        vars = vars->next;
    }
}

void print_curr_state(struct exec_function fxn, FILE *out)
{
    fprintf(out, "----------\n");
    fprintf(out, "%s\n", fxn.parent->name);
    fprintf(out, "GLOBALS\n");
    print_var_mappings(out, fxn.parent->globals);
    fprintf(out, "\n");
    fprintf(out, "LOCALS\n");
    print_var_mappings(out, fxn.locals);
    fprintf(out, "\n\n");
    fprintf(out, "PC:%d", fxn.pc);
    print_instruction(out, &fxn.code_stack[fxn.pc].ins);
    int top = fxn.exec_stack[fxn.sp];
    int second;

    fprintf(out, "Stack: \t\t%d\n", top);
    if (fxn.sp > 0)
    {
        second = fxn.exec_stack[fxn.sp - 1];
        fprintf(out, "Stack-1: \t%d\n", second);
    }
    else
    {
        fprintf(out, "Stack-1: \t--\n");
    }
}