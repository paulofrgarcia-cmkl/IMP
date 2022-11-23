/**
 * @file util.c
 * @brief Module containing miscellaneous functions, generally utility functions
 * created to avoid code duplication.
 */
#include <stdlib.h>
#include <string.h>

#include <util.h>

/**
 * @brief Copy a string from @c src to @c dest, allocating suffient memory to do
 * so.
 *
 * Pulling this out into a function saves a lot of duplicate code, especially
 * during elaboration and when building exec_cores.
 *
 * @param[out] dest Pointer to destination character array.
 * @param[in] src Pointer to source character array.
 */
void deep_copy_string(char **dest, char **src)
{
    if (*src != NULL)
    {
        int len = strlen(*src);
        *dest = calloc(len + 1, sizeof(char));
        strncpy(*dest, *src, len);
    }
    else
    {
        *dest = NULL;
    }
}