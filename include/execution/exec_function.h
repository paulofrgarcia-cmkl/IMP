#ifndef EXEC_FUNCTION_H
#define EXEC_FUNCTION_H

#include <stdbool.h>

#include <arch.h>

#include <stream_queue.h>

union code_stack_elem
{
    struct ir_instruction ins;
    struct arch_symbol sym;
};

enum exec_fxn_type
{
    MAIN_FXN,
    SIGNAL_FXN,
    STREAM_FXN
};

/**
 * @brief Representation of a function (MAIN, SIGNAL, or STREAM) used during
 * program execution.
 */
struct exec_function
{
    enum exec_fxn_type type;

    /// program counter
    int pc;
    /// stack pointer; always points to top of exec_stack
    int sp;
    /// if true, program counter will not advance
    bool waiting;

    /// Index of last instruction in the stack
    int ins_end;

    /// Number of local variables in the stack. WARN: possibly obsolete?
    int num_locals;

    /// Number of elements allocated to the stack
    int code_stack_size;
    int exec_stack_size;

    // bool runnable;

    /// List containing code + variables
    /// Code at bottom, local variables above
    /// Stack grows upwards (so first instruction at address 0, second at 1, etc...)
    /// With current implementation, this should be read-only; exec_stack is the mutable stack.
    union code_stack_elem *code_stack;

    /// Stack that values are pushed onto / popped from
    int *exec_stack;

    /// Linked list of local variables for storage
    struct var_mapping *locals;

    /// Reference to parent core
    struct exec_core *parent;

    /// True if function is currently executing, false when idle
    bool running;

    /// True if a HALT command has been used to terminate execution
    bool force_stopped;

    /// Extra attributes for stream functions
    bool is_stream;
    int num_args;
    struct io_stream *in_stream;
    struct io_stream *out_stream;
    struct exec_function *next;
};

void build_code_stack(struct exec_function *fxn, struct ir_instruction **code_arr, struct arch_function *ast_function);
void build_function_stacks(struct exec_function *fxn, struct ir_instruction **code_arr, struct arch_function *ast_function);
void assign_stream_args(struct arch_symbol *sym, struct exec_function *stream);
void double_stack_memory(struct exec_function *fxn);
void free_exec_function(struct exec_function fxn);
void initialize_exec_function(struct exec_function *fxn, enum exec_fxn_type type);
struct io_stream *get_stream_function_by_name(struct exec_core *core, char *name);
struct stream_argument *get_stream_arg_by_name(struct io_stream stream, char *name);
struct var_mapping *get_local_var_by_name(struct var_mapping *locals, char *name);
bool exec_function_completed(struct exec_function *fxn);
void reset_exec_function(struct exec_function *fxn);
bool exec_function_runnable(struct exec_function *fxn);
void translate_input_packet(struct exec_function *fxn);
void finish_stream_function(struct exec_function *fxn);

#endif