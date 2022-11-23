/**
 * @file exec_function.c
 * @brief Module detailing representations of functions
 */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <util.h>

#include <exec_function.h>
#include <io_stream.h>
#include <var_mapping.h>

#define EXEC_STACK_INIT_SIZE 16

/**
 * @brief Check whether a function has reached the end of its code.
 *
 * This is done by comparing the program counter to the index of the final
 * instruction in the code stack.
 *
 * @param fxn The function in question.
 * @return True if the end of code has been reached, false otherwise.
 */
bool exec_function_completed(struct exec_function *fxn)
{
    return (fxn->pc > fxn->ins_end);
}

/**
 * @brief Check whether a function is eligible to be run.
 *
 * This means that the function must not have an empty code stack, and not have
 * run through all its code without being reset.
 *
 * @param fxn The function in question.
 * @return True if the function is runnable, false otherwise.
 */
bool exec_function_runnable(struct exec_function *fxn)
{
    if (fxn->code_stack == NULL || fxn->force_stopped == true)
    {
        return false;
    }
    else if (exec_function_completed(fxn))
    {
        return false;
    }
    return true;
}

/**
 * @brief Calculate the smallest power of 2 that is greater than a given number.
 *
 * This is useful when allocating memory to a stack; count the number of
 * elements needed for the stack and allocate this many bytes.
 *
 * @param target The number that needs to fit into a power of 2.
 * @return The smallest power of 2 that will fit the target number.
 */
int nearest_power_two(int target)
{
    int power = 1;
    while (pow(2, power) <= target)
    {
        power += 1;
    }
    return pow(2, power);
}

/**
 * @brief Perform a deep copy of an instruction.
 *
 * Copy all fields from ir_instruction @c src to @c dest. @c Dest must already
 * have memory allocated.
 *
 * SMELL: This should maybe not be in this file. Consider moving to code_gen.h?
 *
 * @param[out] dest An allocated, empty instruction.
 * @param[in] src The source instruction.
 */
void copy_instruction(struct ir_instruction *dest, struct ir_instruction *src)
{
    dest->address = src->address;
    dest->label = src->label;
    dest->opcode = src->opcode;
    dest->sub_opcode = src->sub_opcode;
    dest->jmp_target = src->jmp_target;
    dest->constant = src->constant;
    dest->next = src->next;

    deep_copy_string(&dest->identifier, &src->identifier);
    deep_copy_string(&dest->stream, &src->stream);
    deep_copy_string(&dest->core, &src->core);
}

/**
 * @brief Double the memory allocated to the exec_stack of provided function.
 *
 * This is to be used when the stack grows up against its current limit.
 *
 * @param fxn The function whose stack is to be doubled.
 */
void double_stack_memory(struct exec_function *fxn)
{
    int new_size = fxn->exec_stack_size * 2;
    int *new_stack = calloc(new_size, sizeof(int));
    memcpy(new_stack, fxn->exec_stack, fxn->exec_stack_size * sizeof(int));
    free(fxn->exec_stack);
    fxn->exec_stack = new_stack;
    fxn->exec_stack_size = new_size;
}

/**
 * @brief Initialize an exec_function structure with null values.
 *
 * @param fxn The function to initialize.
 * @param type The type of the function.
 */
void initialize_exec_function(struct exec_function *fxn, enum exec_fxn_type type)
{
    fxn->pc = 0;
    fxn->sp = 0;
    fxn->waiting = false;

    fxn->type = type;

    fxn->ins_end = 0;
    fxn->code_stack_size = 0;
    fxn->exec_stack_size = 0;
    fxn->num_locals = 0;
    fxn->code_stack = NULL;
    fxn->exec_stack = NULL;

    fxn->locals = NULL;
    fxn->parent = NULL;

    fxn->running = false;
    fxn->force_stopped = false;

    // stream function related properties
    fxn->is_stream = false;
    fxn->num_args = 0;
    fxn->in_stream = NULL;
    fxn->out_stream = NULL;
    fxn->next = NULL;
}

/**
 * @brief Free memory allocated to an exec_function and its members.
 *
 * @param fxn The exec_function in question.
 */
void free_exec_function(struct exec_function fxn)
{
    // clean up instructions in code stack
    for (int i = 0; i <= fxn.ins_end; i++)
    {
        free_instruction(&fxn.code_stack[i].ins);
    }
    // clean up symbols in code stack
    for (int j = 0; j < fxn.num_locals; j++)
    {
        free_symbol(&fxn.code_stack[fxn.ins_end + 1 + j].sym);
    }

    free(fxn.code_stack);
    free(fxn.exec_stack);
    free_var_mapping(fxn.locals);
}

/**
 * @brief Perform a deep copy of an arch_symbol.
 *
 * SMELL: May want to relocate this to arch.h.
 *
 * @param dest An allocated, empty symbol.
 * @param src The symbol to be copied.
 */
void copy_symbol(struct arch_symbol *dest, struct arch_symbol *src)
{
    dest->index = src->index;
    dest->type = src->type;
    dest->status = src->status;
    dest->next = src->next;

    deep_copy_string(&dest->name, &src->name);
}

/**
 * @brief Allocate and initialize a function's execution stack.
 *
 * The execution stack is the stack on which values will be pushed/popped when
 * carrying out instructions.
 *
 * @param fxn The destination function.
 * @param size The number of elements to allocate to the stack.
 */
void build_exec_stack(struct exec_function *fxn, int size)
{
    int *exec_stack = malloc(sizeof(int) * size);
    memset(exec_stack, 0, size);
    fxn->exec_stack = exec_stack;
}

/**
 * @brief Copy instructions and variables into a function's code stack. The code
 * stack contains the instructions for a function as well as a list of the
 * variables that it will use.
 *
 * Allocate an array large enough to hold all elements, copy over the IR
 * instructions, then the variables/symbols.
 *
 * SMELL: having both code_arr and ast_function seems redundant; perhaps translate
 * linked-list -> instruction array in this function instead of separately.
 *
 * @param[out] fxn The destination function.
 * @param[in] code_arr An array of instructions comprising the function's code.
 * @param[in] ast_function The IR function to copy code from.
 */
void build_code_stack(struct exec_function *fxn, struct ir_instruction **code_arr, struct arch_function *ast_function)
{
    // Determine initial size to allocate to stack
    int code_length = count_instructions(ast_function);
    int num_symbols = count_symbols(ast_function->symbols);
    int code_stack_size = nearest_power_two(code_length + num_symbols);

    fxn->ins_end = code_length - 1;
    fxn->code_stack_size = code_stack_size;
    fxn->num_locals = num_symbols;

    // Initialize code stack
    union code_stack_elem *code_stack = malloc(sizeof(union code_stack_elem) * code_stack_size);

    // copy instructions into stack
    for (int i = 0; i < code_length; i++)
    {
        copy_instruction(&code_stack[i].ins, code_arr[i]);
    }

    // copy variables into stack
    struct arch_symbol *curr_sym = ast_function->symbols;
    // variables in ast_function->symbols are in reverse order, so traverse backwards
    for (int i = code_length + num_symbols - 1; i >= code_length; i--)
    {
        copy_symbol(&code_stack[i].sym, curr_sym);

        // // offset index stored in symbol to account for being placed
        // // after all the instructions
        // stack[i].sym.index += code_length;

        // Allocate storage for its value
        struct var_mapping *new_map = new_var_mapping(curr_sym->name);
        new_map->next = fxn->locals;
        fxn->locals = new_map;

        curr_sym = curr_sym->next;
    }
    // assign stack to exec_core
    fxn->code_stack = code_stack;
}

// Assign symbols from AST to stream function arguments
void assign_stream_args(struct arch_symbol *sym, struct exec_function *stream)
{
    struct arch_symbol *curr_symbol = sym;
    while (curr_symbol != NULL)
    {
        if (curr_symbol->status == ARG_IN)
        {
            // Add input argument to input stream
            add_stream_arg(stream->in_stream, curr_symbol);
        }
        else if (curr_symbol->status == ARG_OUT)
        {
            // Add output argument to output stream
            add_stream_arg(stream->out_stream, curr_symbol);
        }
        else
        {
            printf("Encountered invalid stream type\n");
        }
        curr_symbol = curr_symbol->next;
    }
}

/**
 * @brief Construct the code stack and execution stack for an exec_function.
 *
 * @param[out] fxn The function to build the stacks for.
 * @param[in] code_arr An array of instructions comprising the function's code.
 * @param[in] ast_function The IR function to copy code from.
 */
void build_function_stacks(struct exec_function *fxn, struct ir_instruction **code_arr, struct arch_function *ast_function)
{
    if (ast_function != NULL)
    {
        int exec_stack_size = EXEC_STACK_INIT_SIZE;
        fxn->sp = 0;
        fxn->exec_stack_size = exec_stack_size;
        // if stream function, copy over input and output names
        if (ast_function->in_name != NULL && ast_function->out_name != NULL)
        {
            deep_copy_string(&fxn->in_stream->name, &ast_function->in_name);
            deep_copy_string(&fxn->out_stream->name, &ast_function->out_name);
        }

        build_code_stack(fxn, code_arr, ast_function);
        build_exec_stack(fxn, exec_stack_size);
    }
}

// Return pointer to the io_stream of a given name on a given core, if one exists
struct io_stream *get_stream_function_by_name(struct exec_core *core, char *name)
{
    struct exec_function *curr_fxn = core->stream_fxns;
    while (curr_fxn != NULL)
    {
        if (!strcmp(curr_fxn->in_stream->name, name))
        {
            return curr_fxn->in_stream;
        }
        else if (!strcmp(curr_fxn->out_stream->name, name))
        {
            return curr_fxn->out_stream;
        }
        else
        {
            curr_fxn = curr_fxn->next;
        }
    }
    return NULL;
}

struct var_mapping *get_local_var_by_name(struct var_mapping *locals, char *name)
{
    struct var_mapping *curr_var = locals;
    while (curr_var != NULL)
    {
        if (!strcmp(curr_var->name, name))
        {
            return curr_var;
        }
        else
        {
            curr_var = curr_var->next;
        }
    }
    return NULL;
}

void translate_input_packet(struct exec_function *fxn)
{
    // For each value in the input packet, assign that
    // value to a local variable.
    struct stream_packet *in_pkt = fxn->in_stream->queue->queue;
    struct var_mapping *pkt_args = in_pkt->args;
    while (pkt_args != NULL)
    {
        struct var_mapping *local = get_local_var_by_name(fxn->locals, pkt_args->name);
        if (local == NULL)
        {
            // we have a problem
            printf("mismatch between input stream args and stream function vars");
        }
        else
        {
            if (pkt_args->null)
            {
                local->null = true;
            }
            else
            {
                local->null = false;
                local->val = pkt_args->val;
            }
        }
        pkt_args = pkt_args->next;
    }
}
void build_output_packet(struct exec_function *fxn)
{
    fxn->out_stream->pkt_under_construction = build_stream_packet(fxn->out_stream);

    // for each variable in the output arguments, assign
    // a variable and value to the output packet
    struct stream_argument *curr_arg = fxn->out_stream->args;
    while (curr_arg != NULL)
    {
        struct var_mapping *local = get_local_var_by_name(fxn->locals, curr_arg->arg_name);
        write_var_mapping(fxn->out_stream->pkt_under_construction->args,
                          curr_arg->arg_name, local->val);
        curr_arg = curr_arg->next;
    }
}

void finish_stream_function(struct exec_function *fxn)
{
    build_output_packet(fxn);
    // Push completed packet to output queue
    stream_enqueue(fxn->out_stream->queue, fxn->out_stream->pkt_under_construction);
    reset_exec_function(fxn);
    stream_dequeue(fxn->in_stream->queue);
}

/**
 * @brief Reset a function to its initial execution state.
 *
 * Set its program counter to the first instruction, reset all values in the
 * execution stack, and set the stack pointer back to its base.
 *
 * @param fxn The function to reset.
 */
void reset_exec_function(struct exec_function *fxn)
{
    fxn->pc = 0;
    fxn->sp = 0;
    fxn->running = false;
    // Clear exec_stack
    memset(fxn->exec_stack, 0, fxn->exec_stack_size);
    // Reset local variables
    struct var_mapping *curr_local = fxn->locals;
    while (curr_local != NULL)
    {
        curr_local->null = true;
        curr_local->val = 0;
        curr_local = curr_local->next;
    }
}
