#ifndef EXEC_CORE_H
#define EXEC_CORE_H

#include <stdbool.h>

#include <arch.h>
#include <ast.h>

#include <exec_function.h>
#include <io_stream.h>

struct exec_core
{
    // interrupt enable toggle, should default to false
    bool sigen;
    // core name
    char *name;
    // signal vector listing which cores have triggered this one
    bool *sigvec;

    bool core_halted;

    int time_blocking;

    struct exec_function main_fxn;
    struct exec_function signal_fxn;
    // Linked list of stream functions, maybe?
    // separate lists for in and out streams
    // input port is pointer to in queue
    // output queue is pointer to out port
    // struct stream_data in_streams;
    // struct stream_data out_streams;
    struct exec_function *stream_fxns;

    // Stack containing global variables for this core
    struct var_mapping *globals;

    // Pointer to other cores in the system
    // Need to reach them to cause interrupts
    // (possible alternative system: common pool/message queue that cores query?)
    struct exec_core **parent;
};

struct exec_core **setup_cores(int num_cores);
void assign_exec_core_functions(int num_cores, struct exec_core **exec_cores, struct arch_core *ast_cores);
bool main_runnable(struct exec_core *core);
void double_stack_memory(struct exec_function *fxn);
void free_cores(struct exec_core **cores, int num_cores);
struct stream_function *get_stream_function(char *core, char *fxn);

#endif