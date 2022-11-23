/**
 * @file var_mapping.c
 * @brief Module for handling variable-value mappings during execution.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <var_mapping.h>

/**
 * @brief Create a new variable mapping with empty values, based on a symbol
 * parsed into the AST, and attach it to a linked list.
 *
 * @param[in] name
 * @return struct var_mapping*
 */
struct var_mapping *new_var_mapping(char *name)
{
    struct var_mapping *new_local = malloc(sizeof(struct var_mapping));
    new_local->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(new_local->name, name);
    new_local->val = 0;
    new_local->null = true;
    return new_local;
}

/**
 * @brief Check whether a variable with a given name exists in the provided
 * scope.
 *
 * @param[in] vars List of variable mappings for the target scope.
 * @param[in] name Name of the target variable.
 * @return True if the variable was found, false otherwise.
 */
bool var_exists(struct var_mapping *vars, char *name)
{
    while (vars != NULL)
    {
        if (!strcmp(vars->name, name))
        {
            return true;
        }
        vars = vars->next;
    }
    return false;
}

/**
 * @brief Read the value of a variable with a given name in the provided scope.
 *
 * HACK: Presently this function should only be run if the variable is checked
 * to have existed (var_exists). However, this function does almost the exact
 * same thing as var_exists. Potentially merge the two functions and introduce
 * some form of error handling.
 *
 * @param[in] vars List of variable mappings for the target scope.
 * @param[in] name Name of the target variable.
 * @return The value of the variable if it was found, INT_MAX otherwise.
 */
int read_var_mapping(struct var_mapping *vars, char *name)
{
    while (vars != NULL)
    {
        if (!strcmp(vars->name, name))
        {
            return vars->val;
        }
        vars = vars->next;
    }
    return __INT_MAX__;
}

/**
 * @brief Write a value to a variable with a given name in the provided scope.
 *
 * @param[in,out] vars List of variable mappings for the target scope.
 * @param[in] name Name of the target variable.
 * @param[in] val The value to be written.
 */
void write_var_mapping(struct var_mapping *vars, char *name, int val)
{
    while (vars != NULL)
    {
        if (!strcmp(vars->name, name))
        {
            vars->val = val;
            vars->null = false;
            return;
        }
        vars = vars->next;
    }
}

/**
 * @brief Count the number of variables in the provided scope.
 *
 * @param vars List of variable mappings for the target scope.
 * @return The number of variable mappings in scope.
 */
int count_vars(struct var_mapping *vars)
{
    int count = 0;
    while (vars != NULL)
    {
        count += 1;
        vars = vars->next;
    }
    return count;
}

/**
 * @brief Determine whether a given variable is mapped to null, or stores a
 * value.
 *
 * @param var The variable mapping in question.
 * @return True if the variable maps to null, false otherwise.
 */
bool var_is_null(struct var_mapping *var)
{
    return var->null == true;
}

/**
 * @brief Free all variable mappings in the provided scope.
 *
 * Note that if provided a var_mapping that is not the head of a list, this
 * function will only work forwards in the list, leaving the prior elements
 * intact (and possibly causing a leak).
 *
 * @param vars List of variable mappings for the target scope.
 */
void free_var_mapping(struct var_mapping *vars)
{
    if (vars == NULL)
    {
        return;
    }
    else if (vars->next == NULL)
    {
        free(vars->name);
        free(vars);
        return;
    }
    else
    {
        free_var_mapping(vars->next);
    }
}