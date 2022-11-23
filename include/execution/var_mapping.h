#ifndef VAR_MAPPING_H
#define VAR_MAPPING_H

#include <stdbool.h>
#include <string.h>

/**
 * @brief Mapping of a variable, identified by name, to an integer value.
 *
 * @details Intended to be used as a linked list of all variables in a given
 * scope.
 */
struct var_mapping
{
    char *name;
    int val;
    bool null;
    struct var_mapping *next;
};

struct var_mapping *new_var_mapping(char *name);
int read_var_mapping(struct var_mapping *vars, char *name);
void write_var_mapping(struct var_mapping *vars, char *name, int val);
bool var_exists(struct var_mapping *vars, char *name);
bool var_is_null(struct var_mapping *var);
void free_var_mapping(struct var_mapping *vars);

#endif