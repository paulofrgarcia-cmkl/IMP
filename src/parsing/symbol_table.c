#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ast_printer.h>
#include <symbol_table.h>

char *symbol_type_name[] = {"VAR", "FUNC"};

struct symbol_node *sym_table;
struct symbol_node *curr_node;
struct symbol_scope symtable_scope = {.core = "TOP", .func = "GLOBAL"};

struct symbol_node *get_table()
{
    return sym_table;
}

// Check equivalence of two scope structs
bool scope_eq(struct symbol_scope x, struct symbol_scope y)
{
    if (!strcmp(x.core, y.core) && !strcmp(x.func, y.func))
    {
        return true;
    }
    return false;
}

void add_to_table(struct symbol_node *node)
{
    if (curr_node == NULL)
    {
        sym_table = node;
        curr_node = node;
    }
    else
    {
        curr_node->next = node;
        curr_node = curr_node->next;
    }
}

// Check for duplicate table entries within a given scope
bool check_duplicates(struct symbol_node *node, char *name, struct symbol_scope scope)
{
    while (node != NULL)
    {
        if (!strcmp(name, node->name) && scope_eq(scope, node->scope))
        {
            printf("Duplicate declaration %s in scope %s\n", name, scope.func);
            return true;
        }
        node = node->next;
    }

    return false;
}

// if checking function existence, NULL should be supplied to fxn
bool check_exists(char *name, enum symbol_type type, char *core, char *fxn)
{
    struct symbol_node *node = sym_table;
    if (fxn == NULL)
    {
        fxn = "GLOBAL";
    }
    struct symbol_scope target_scope = {.core = core, .func = fxn};
    while (node != NULL)
    {
        if (!strcmp(name, node->name))
        {
            if (node->sym_type == type && scope_eq(node->scope, target_scope))
            {
                return true;
            }
        }
        node = node->next;
    }
    return false;
}

// Create an empty, fully-nulled symbol node
struct symbol_node *allocate_symbol_node()
{
    struct symbol_node *tmp;
    tmp = (struct symbol_node *)malloc(sizeof(struct symbol_node));

    tmp->name = NULL;
    tmp->scope.core = NULL;
    tmp->scope.func = NULL;
    tmp->sym_type = 0;
    tmp->val_type = 0;
    tmp->next = NULL;
}

// Add a variable to the symbol table
int sym_add_variable(struct ast_node *a, struct symbol_scope scope)
{
    // Check for duplicate declaration
    if (check_duplicates(sym_table, a->name, scope))
        return false;

    // If new, add to symbol table
    struct symbol_node *new_node = allocate_symbol_node();
    new_node->name = (char *)malloc(strlen(a->name) + 1);
    strcpy(new_node->name, a->name);
    new_node->sym_type = VAR;
    new_node->val_type = a->variable_type;
    new_node->scope = scope;

    add_to_table(new_node);
    return true;
}

// Add a function to the symbol table
int sym_add_function(struct ast_node *a, char *name)
{
    if (check_duplicates(sym_table, name, symtable_scope))
        return false;

    // If new, add to symbol table
    struct symbol_node *new_node = allocate_symbol_node();
    new_node->name = (char *)malloc(strlen(name) + 1);
    strcpy(new_node->name, name);
    new_node->sym_type = FUNC;
    new_node->val_type = 0;
    new_node->scope.core = symtable_scope.core;
    new_node->scope.func = "GLOBAL";

    add_to_table(new_node);
    return true;
}

// Helper function to convert function type enum to string for printing
char *function_type_to_string(enum ast_type type)
{
    switch (type)
    {
    case MAIN:
        return "main";
        break;
    case SIGNAL:
        return "signal";
        break;
    case STREAM: // STREAM not yet supported
        return "stream";
        break;
    }
}

char *symbol_type_to_string(enum symbol_type type)
{
    return symbol_type_name[type];
}

// // Helper function to convert symbol type enum to string for printing
// char *node_type_to_string(enum symbol_type type)
// {
//     switch(type)
//     {
//         case VAR:
//             return "VAR";
//             break;
//         case FUNC:
//             return "FUNC";
//             break;
//     }
// }

// Iterate over the AST and construct a symbol table from it
int build_symbol_table(struct ast_node *a)
{
    int num_errors = 0;
    // Parse through DST tree

    if (a == (struct ast_node *)0)
    {
        return 0;
    }

    else if (a->type == VAR_DECL)
    {
        if (!sym_add_variable(a, symtable_scope))
        {
            num_errors += 1;
        }
    }
    else if (a->type == MAIN || a->type == SIGNAL)
    {
        if (!sym_add_function(a, function_type_to_string(a->type)))
        {
            num_errors += 1;
        }
        // Update current scope since we will be recurring down into this fxn
        symtable_scope.func = function_type_to_string(a->type);
    }
    else if (a->type == STREAM)
    {
        if (!sym_add_function(a, a->name))
        {
            num_errors += 1;
        }
        // Update current scope since we will be recurring down into this fxn
        symtable_scope.func = a->name;
        // If stream function inputs and outputs are to be included in symbol
        // table, do that here
        num_errors += build_symbol_table(a->stream_in->down);
        num_errors += build_symbol_table(a->stream_out->down);
    }
    else if (a->type == CORE)
    {
        symtable_scope.core = a->name;
        symtable_scope.func = "GLOBAL";
    }

    num_errors += build_symbol_table(a->down);
    num_errors += build_symbol_table(a->side);

    return num_errors;
}

void print_symbol_node(struct symbol_node *node)
{
    if (node == NULL)
    {
        printf("Null Node");
    }
    else
    {
        // char *sym_type_str = node_type_to_string(node->sym_type);
        char *sym_type_str = symbol_type_to_string(node->sym_type);
        char *val_type_str = var_type_to_str(node->val_type);
        printf("%-15.15s\t%s\t%s\t%s\t%s\n", node->name, sym_type_str, val_type_str, node->scope.core, node->scope.func);
    }
}

void print_symbol_table()
{
    struct symbol_node *node = sym_table;
    printf("----- Symbol Table -----\n");
    printf("%-15.15s\tType\tData\tCore\tScope\n", "Name");
    // Traverse and print the symbol table
    while (node != NULL)
    {
        print_symbol_node(node);
        node = node->next;
    }
    printf("----- End Table -----\n");
}