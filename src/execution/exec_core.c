/**
 * @file exec_core.c
 * @brief Foo Bar
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ast.h>
#include <util.h>

#include <exec_core.h>
#include <io_stream.h>
#include <var_mapping.h>

/**
 * @brief Build a new exec_core with null-valued fields and name @a name.
 *
 * @details Allocate memory for the exec_core. Assign its name, provided as
 * @a name. Allocate memory for and initialize its signal vector. Initialize
 * the core's fields with null values.
 *
 * @param name The name to assign to the exec_core.
 * @param num_cores The number of exec_cores being used in this run.
 * @return Pointer to the initialized exec_core.
 */
struct exec_core *initialize_exec_core(char *name, int num_cores)
{
    struct exec_core *new_core = malloc(sizeof(struct exec_core));
    new_core->sigen = false;
    new_core->core_halted = false;
    new_core->name = (char *)malloc(strlen(name) + 1);
    strcpy(new_core->name, name);
    new_core->time_blocking = 0;

    // Set up the sigvec as an array big enough to handle one boolean value
    // for each exec_core in the system.
    // The value at the index corresponding to the ID of the triggering core
    // will be set to true.
    bool *sigvec = malloc(sizeof(bool) * num_cores);
    for (int i = 0; i < num_cores; i++)
    {
        sigvec[i] = false;
    }
    new_core->sigvec = sigvec;

    initialize_exec_function(&new_core->main_fxn, MAIN_FXN);
    initialize_exec_function(&new_core->signal_fxn, SIGNAL_FXN);
    new_core->stream_fxns = NULL;

    new_core->globals = NULL;
    new_core->parent = NULL;

    return new_core;
}

/**
 * @brief Copy a linked list of arch_symbol s to an exec_core's set of global
 * variables.
 *
 * @details Count the number of symbols in @a g_vars. For each arch_symbol,
 * create a var_mapping, populate it with information from the arch_symbol, and
 * add it to the exec_core's global variable list.
 *
 * @param[out] core Pointer to the destination exec_core.
 * @param[in] g_vars
 * @return Nothing.
 */
void *translate_global_vars(struct exec_core *core, struct arch_symbol *g_vars)
{
    int num_symbols = count_symbols(g_vars);
    if (num_symbols > 0)
    {
        struct arch_symbol *curr_symbol = g_vars;
        for (int i = 0; i < num_symbols; i++)
        {
            struct var_mapping *new_map = new_var_mapping(curr_symbol->name);
            new_map->next = core->globals;
            core->globals = new_map;
            curr_symbol = curr_symbol->next;
        }
    }
}

/**
 * @brief Translate stream functions from the elaboration step into ones suitable
 * for runtime.
 *
 * @details Build an empty exec_function, initialized with values required
 * for a stream function. Then, copy arguments and instructions from the
 * arch_function to the exec_function. Finally, add the built
 * exec_function to the exec_core's list of stream functions.
 *
 * @param[in,out] exec_core Pointer to the exec_core to translate to.
 * @param[in] ast_core Pointer to the arch_core representation to translate from.
 */
void build_stream_function(struct exec_core *exec_core, struct arch_core *ast_core)
{
    struct arch_function *ast_stream_fxn = ast_core->stream_functions;
    while (ast_stream_fxn != NULL)
    {
        // Build a new exec_function and add it to the linked list
        struct exec_function *new_stream = malloc(sizeof(struct exec_function));
        initialize_exec_function(new_stream, STREAM_FXN);
        new_stream->in_stream = new_io_stream(ast_stream_fxn->in_name, STREAM_IN);
        new_stream->out_stream = new_io_stream(ast_stream_fxn->out_name, STREAM_OUT);
        new_stream->is_stream = true;

        assign_stream_args(ast_stream_fxn->symbols, new_stream);

        // build code stack
        build_function_stacks(new_stream, translate_function(ast_stream_fxn), ast_stream_fxn);

        // add to the core's list of stream functions
        new_stream->parent = exec_core;
        if (exec_core->stream_fxns == NULL)
        {
            exec_core->stream_fxns = new_stream;
        }
        else
        {
            new_stream->next = exec_core->stream_fxns;
            exec_core->stream_fxns = new_stream;
        }
        ast_stream_fxn = ast_stream_fxn->next;
    }
}

/**
 * @brief Build exec_cores by assigning their main, signal, and stream
 * functions, if applicable.
 *
 * @details
 *
 * @param[in] num_cores The number of exec_cores being used in this run.
 * @param[out] exec_cores Array of pointers to exec_cores.
 * @param[in] ast_cores Array of arch_cores generated during parsing.
 * @return Nothing.
 */
void assign_exec_core_functions(int num_cores, struct exec_core **exec_cores, struct arch_core *ast_cores)
{
    // For each function of each core:
    // Get length of generated code linked-list
    // Create array of said length
    // Copy code linked-list to array for easier execution
    // (with jump addresses converted to array indices)

    struct arch_core *curr_core = ast_cores;
    // Build relevant function stacks for each core
    for (int c = num_cores - 1; c >= 0; c--)
    {
        // main function
        if (curr_core->main_function != NULL)
        {
            build_function_stacks(&exec_cores[c]->main_fxn, translate_function(curr_core->main_function), curr_core->main_function);
        }
        else
        {
            printf("No main function on core %s\n", curr_core->name);
        }

        // signal function
        if (curr_core->signal_function != NULL)
        {
            build_function_stacks(&exec_cores[c]->signal_fxn, translate_function(curr_core->signal_function), curr_core->signal_function);
        }
        else
        {
            printf("No signal fxn on core %s\n", curr_core->name);
        }

        // stream function(s)
        if (curr_core->stream_functions != NULL)
        {
            // iterate over stream functions and translate them
            // struct function *foo = curr_core->stream_functions;
            // int stream_id = 0;
            build_stream_function(exec_cores[c], curr_core);
        }
        else
        {
            printf("No stream fxns on core %s\n", curr_core->name);
        }

        // Transfer global variables into exec core
        translate_global_vars(exec_cores[c], curr_core->g_symbols);

        // Assign parent references (for when moving up in hierarchy is needed)
        exec_cores[c]->main_fxn.parent = exec_cores[c];
        exec_cores[c]->signal_fxn.parent = exec_cores[c];
        exec_cores[c]->parent = exec_cores;

        curr_core = curr_core->next;
    }
}

/**
 * @brief Set up the exec_cores for a run.
 *
 * @details Allocates memory for @a num_cores exec_cores. Then, for each core
 * allocated, gives that core a name, initializes its fields, and adds a pointer
 * to it to the list of pointers that will be returned.
 *
 * @param[in] num_cores The number of cores to set up.
 * @return Array of pointers to the created exec_cores.
 */
struct exec_core **setup_cores(int num_cores)
{
    if (num_cores > 99)
    {
        // this is a silly limit, but for now it makes string processing simple
        // "cpuXX", 5 characters
        printf("Too many cores!");
        return false;
    }

    struct exec_core **cores = malloc(sizeof(struct exec_core *) * num_cores);
    for (int i = 0; i < num_cores; i++)
    {
        char name[10];
        // keeping this here for now in case I need to change it back:

        // // when building architecture, cores are named in reverse order, so
        // // work backwards here so that names match up
        // snprintf(name, 5, "cpu%d", (num_cores - (i + 1)));
        snprintf(name, 5, "cpu%d", (i));

        struct exec_core *new_core = initialize_exec_core(name, num_cores);
        cores[i] = new_core;
    }

    return cores;
}

/**
 * @brief Free memory allocated to exec_cores.
 *
 * @details Iterates over the first @a num_cores pointers in the the array
 * provided as @a cores, and frees its fields before finally freeing the
 * pointer to the exec_core.
 *
 * @param[in] cores Array of pointers to exec_cores to be freed.
 * @param[in] num_cores Number of exec_cores contained in the array.
 * @return Nothing.
 */
void free_cores(struct exec_core **cores, int num_cores)
{
    for (int i = 0; i < num_cores; i++)
    {
        struct exec_core *curr_core = cores[i];
        free_var_mapping(curr_core->globals);
        free(curr_core->sigvec);
        free(curr_core->name);
        free_exec_function(curr_core->main_fxn);
        free_exec_function(curr_core->signal_fxn);
        free(curr_core);
    }
}
