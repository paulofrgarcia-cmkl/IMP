#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <semantic_analysis.h>

struct symbol_scope semantic_scope = {.core = "TOP", .func = "GLOBAL"};

// Confirm that value assigned to a variable is of the proper type
bool check_type_agreement(struct ast_node *node, struct symbol_node *symtable, struct symbol_scope scope)
{
    if (node->variable_type == I32)
    {
        enum ast_type child_type = node->down->type;
        if (child_type == CONSTANT)
        {
            return true;
        }
        else if (child_type == VARIABLE)
        {
            // Verify variable's type using symbol table
            return check_exists(node->down->name, VAR, semantic_scope.core, semantic_scope.func);
        }
        else if (child_type == EXPRESSION)
        {
            // TODO: verify expression returns compatible type
            // What does this mean?
            // I suppose: the operator must sensibly return that type, given
            // the children of that operator
            // TODO:implement booleans? some other simple type?
            return true;
        }
        else if (child_type == STREAM_PULL)
        {
            // TODO: verify stream pull returns compatible type
            return true;
        }
    }

    return false;
}

// Iterate through an AST and check rules compliance
int check_semantics(struct ast_node *a, struct symbol_node *symtable)
{
    int num_errors = 0;

    if (a == NULL)
    {
        return 0;
    }

    else if (a->type == MAIN || a->type == SIGNAL)
    {
        semantic_scope.func = function_type_to_string(a->type);
    }

    else if (a->type == STREAM)
    {
        semantic_scope.func = a->name;
    }

    else if (a->type == VAR_ASSIGN)
    {
        if (!check_type_agreement(a, symtable, semantic_scope))
        {
            num_errors += 1;
        }

        // Check that variable has been declared/exists in symbol table
        else if (!check_exists(a->name, VAR, semantic_scope.core, semantic_scope.func))
        {
            // if not found in local function, make sure it's not actually a global
            if (!check_exists(a->name, VAR, semantic_scope.core, "GLOBAL"))
            {
                printf("Use of undeclared variable %s in core %s function %s\n", a->name, semantic_scope.core, semantic_scope.func);
                num_errors += 1;
            }
        }
    }

    else if (a->type == CORE)
    {
        semantic_scope.core = a->name;
        semantic_scope.func = "GLOBAL";
    }

    num_errors += check_semantics(a->down, symtable);
    num_errors += check_semantics(a->side, symtable);

    return num_errors;
}