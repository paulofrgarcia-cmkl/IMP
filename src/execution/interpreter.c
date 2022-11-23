#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <exec_printer.h>
#include <interpreter.h>
#include <var_mapping.h>

/**
 * @brief Extract the ID of a core based on its name.
 *
 * @param name The name of the core.
 * @return The ID number of a core.
 */
int core_id_from_name(char *name)
{
    int id;
    int name_len = strnlen(name, 5);
    if (name_len == 4)
    {
        // single digit id
        char digit[2];
        digit[0] = name[3];
        digit[1] = '\0';
        id = atoi(digit);
    }
    else if (name_len == 5)
    {
        // double digit id
        char digits[3];
        digits[0] = name[3];
        digits[1] = name[4];
        digits[2] = '\0';
        id = atoi(digits);
    }
    else
    {
        // error
        id = -1;
    }
    return id;
}

/**
 * @brief Set an exec_function's program counter to an arbitrary value
 *
 * The jump adjusts the PC to 1 instruction behind the target, as after the
 * execution of the branching instruction that calls this function, the
 * PC will auto-increment.
 *
 * @param fxn
 * @param target
 */
void jump(struct exec_function *fxn, int target)
{
    // jump to 1 instruction behind target, as PC will auto-increment
    // after instruction execution
    fxn->pc = target - 1;
}

struct io_stream *get_iostream(struct exec_function *fxn, char *core_name, char *stream_name)
{
    int core_id = core_id_from_name(core_name);
    struct exec_core *core = fxn->parent->parent[core_id];
    return get_stream_function_by_name(core, stream_name);
}

int retrieve_variable(struct exec_function *fxn, char *identifier)
{
    bool exists_locally = var_exists(fxn->locals, identifier);
    int val;
    if (exists_locally)
    {
        val = read_var_mapping(fxn->locals, identifier);
    }
    else
    {
        bool exists_globally = var_exists(fxn->parent->globals, identifier);
        if (exists_globally)
        {
            val = read_var_mapping(fxn->parent->globals, identifier);
        }
        else
        {
            printf("Tried to retrieve nonexistent variable %s!\n", identifier);
            return -999;
        }
    }
    return val;
}

/**
 * @brief Execute a single instruction.
 *
 * @param fxn The function that is running.
 * @param ins The instruction from @a fxn to be run.
 */
void execute_instruction(struct exec_function *fxn, struct ir_instruction ins, FILE *log)
{
    // We are restricting PC to only point to instructions, so
    // the "union code_stack_elem" SHOULD always be of instruction type
    switch (ins.opcode)
    {
    case PUSH_t:
        // Verify stack has room to push onto
        if (!(fxn->sp < fxn->exec_stack_size))
        {
            double_stack_memory(fxn);
        }
        switch (ins.sub_opcode.PUSH_t_opcode)
        {
        case PUSH_I32_CONST:
            // push constant onto stack
            fxn->exec_stack[fxn->sp + 1] = ins.constant;
            fxn->sp += 1;
            break;
        case PUSH_I32_IDENTIFIER:
            // push variable onto stack
            (void *)0;
            fxn->exec_stack[fxn->sp + 1] = retrieve_variable(fxn, ins.identifier);
            fxn->sp += 1;
            break;
        }
        break;

    case POP_t:
        (void *)0;
        // pop from stack into identifier
        int val = fxn->exec_stack[fxn->sp];
        bool exists_locally = var_exists(fxn->locals, ins.identifier);
        if (exists_locally)
        {
            write_var_mapping(fxn->locals, ins.identifier, val);
        }
        else
        {
            bool exists_globally = var_exists(fxn->parent->globals, ins.identifier);
            if (exists_globally)
            {
                write_var_mapping(fxn->parent->globals, ins.identifier, val);
            }
            else
            {
                printf("Tried to retrieve nonexistent variable %s!\n", ins.identifier);
            }
        }
        fxn->sp -= 1;
        break;

    case JMP_t:
        switch (ins.sub_opcode.JMP_t_opcode)
        {
        case JMP_JMP:
            // unconditional jump
            jump(fxn, ins.jmp_target);
            break;
        case JMP_BRT:
            // branch if true
            if (fxn->exec_stack[fxn->sp] != 0)
            {
                jump(fxn, ins.jmp_target);
            }
            fxn->sp -= 1;
            break;
        case JMP_BRF:
            // branch if false
            if (fxn->exec_stack[fxn->sp] == 0)
            {
                jump(fxn, ins.jmp_target);
            }
            fxn->sp -= 1;
            break;
        }
        break;

    case CTRL_t:
        switch (ins.sub_opcode.CONTROL_t_opcode)
        {
        case CONTROL_SIGEN:
            // enable interrupts
            fxn->parent->sigen = true;
            break;
        case CONTROL_SIGDIS:
            // disable interrupts
            fxn->parent->sigen = false;
            break;
        case CONTROL_PRINT:
            // pring value to stdout
            printf("%s: %d\n", fxn->parent->name, ins.constant);
            break;
        case CONTROL_PRINT_STRING:
            // print string to stdout
            printf("%s: %s\n", fxn->parent->name, ins.identifier);
            break;
        case CONTROL_PRINT_IDENTIFIER:
            printf("%s: %d\n", fxn->parent->name, retrieve_variable(fxn, ins.identifier));
            break;
        case CONTROL_HALT:
            printf("%s: Core halting\n", fxn->parent->name);
            fxn->parent->core_halted = true;
            break;
        case CONTROL_FIRE:
            printf("Core %s temperature rapidly increasing!!!\n Shutting down interpeter as a safety measure...\n", fxn->parent->name);
            exit(999);
            break;
        }
        break;

    case ALU_t:
        (void)0; // dummy statement to allow var declaration after switch label
        int a;
        int b;
        switch (ins.sub_opcode.ALU_t_opcode)
        {
        // Pop two operands from top of stack, perform operation, then push
        // the result onto the top of the stack
        case ALU_ADD:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            fxn->exec_stack[fxn->sp - 1] = b + a;
            fxn->sp -= 1;
            break;

        case ALU_SUB:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            fxn->exec_stack[fxn->sp - 1] = b - a;
            fxn->sp -= 1;
            break;

        case ALU_MUL:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            fxn->exec_stack[fxn->sp - 1] = b * a;
            fxn->sp -= 1;
            break;

        case ALU_DIV:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            fxn->exec_stack[fxn->sp - 1] = b / a;
            fxn->sp -= 1;
            break;

        case ALU_AND:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            if (a != 0 && b != 0)
            {
                fxn->exec_stack[fxn->sp - 1] = 1;
            }
            else
            {
                fxn->exec_stack[fxn->sp - 1] = 0;
            }
            fxn->sp -= 1;
            break;

        case ALU_OR:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            if (a != 0 || b != 0)
            {
                fxn->exec_stack[fxn->sp - 1] = 1;
            }
            else
            {
                fxn->exec_stack[fxn->sp - 1] = 0;
            }
            fxn->sp -= 1;
            break;

        case ALU_LT:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            if (b < a)
            {
                fxn->exec_stack[fxn->sp - 1] = 1;
            }
            else
            {
                fxn->exec_stack[fxn->sp - 1] = 0;
            }
            fxn->sp -= 1;
            break;

        case ALU_LEQ:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            if (b <= a)
            {
                fxn->exec_stack[fxn->sp - 1] = 1;
            }
            else
            {
                fxn->exec_stack[fxn->sp - 1] = 0;
            }
            fxn->sp -= 1;
            break;

        case ALU_GT:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            if (b > a)
            {
                fxn->exec_stack[fxn->sp - 1] = 1;
            }
            else
            {
                fxn->exec_stack[fxn->sp - 1] = 0;
            }
            fxn->sp -= 1;
            break;

        case ALU_GEQ:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            if (b >= a)
            {
                fxn->exec_stack[fxn->sp - 1] = 1;
            }
            else
            {
                fxn->exec_stack[fxn->sp - 1] = 0;
            }
            fxn->sp -= 1;
            break;

        case ALU_EQ:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            if (a == b)
            {
                fxn->exec_stack[fxn->sp - 1] = 1;
            }
            else
            {
                fxn->exec_stack[fxn->sp - 1] = 0;
            }
            fxn->sp -= 1;
            break;

        case ALU_NEQ:
            a = fxn->exec_stack[fxn->sp];
            b = fxn->exec_stack[fxn->sp - 1];
            if (a != b)
            {
                fxn->exec_stack[fxn->sp - 1] = 1;
            }
            else
            {
                fxn->exec_stack[fxn->sp - 1] = 0;
            }
            fxn->sp -= 1;
            break;
        }
        break;

    case NOP:
        // do nothing
        break;

    case REF_t:
        (void *)0;
        int stream_val;
        struct io_stream *target_iostream;
        struct var_mapping *target_arg;
        switch (ins.sub_opcode.REF_t_opcode)
        {
        case REF_MATCH_SOURCE:
            // match signal source
            asm("nop");
            int query_id = core_id_from_name(ins.identifier);
            // Check if sigvec has a request from that core
            if (fxn->parent->sigvec[query_id] == true)
            {
                // if so, continue
            }
            else
            {
                jump(fxn, ins.jmp_target);
            }

            break;
        case REF_TRIGGER:
            (void *)0;
            // send interrupt to core
            int target_id = core_id_from_name(ins.identifier);
            int source_id = core_id_from_name(fxn->parent->name);
            // Signal an interrupt from core source_id in core target_id
            struct exec_core *triggered_core = fxn->parent->parent[target_id];
            if (triggered_core->sigen == true)
            {
                triggered_core->sigvec[source_id] = true;
            }
            break;
        case REF_S_PUSH:
            // push value to input stream
            // Identify destination
            target_iostream = get_iostream(fxn, ins.core, ins.stream);
            // Get value from top of stack
            stream_val = fxn->exec_stack[fxn->sp];
            fxn->sp -= 1;
            // If the iostream doesn't have a packet currently under construction,
            // make a new one
            if (target_iostream->pkt_under_construction == NULL)
            {
                target_iostream->pkt_under_construction = build_stream_packet(target_iostream);
            }
            // Write the value to the targeted argument in the packet
            write_var_mapping(target_iostream->pkt_under_construction->args, ins.identifier, stream_val);

            break;
        case REF_S_PULL:
            // pull value from output stream, leave on stack
            // Get stream to pull from
            target_iostream = get_iostream(fxn, ins.core, ins.stream);
            // Get argument to pull

            // If there is a packet in the output queue, take the corresponding
            // value from it.
            // If there is no packet, block/wait until there is.
            if (target_iostream->queue->queue == NULL)
            {
                fxn->waiting = true;
            }
            else
            {
                fxn->waiting = false;
                // Take argument's value and push onto stack
                stream_val = get_stream_packet_arg(target_iostream->queue->queue, ins.identifier)->val;
                if (!(fxn->sp < fxn->exec_stack_size))
                {
                    double_stack_memory(fxn);
                }
                fxn->sp += 1;
                fxn->exec_stack[fxn->sp] = stream_val;
            }
            break;
        case REF_S_COMMIT:
            // // trigger input stream to consume arguments
            target_iostream = get_iostream(fxn, ins.core, ins.stream);
            struct stream_queue *queue = target_iostream->queue;
            stream_enqueue(queue, target_iostream->pkt_under_construction);
            target_iostream->pkt_under_construction = NULL;
            break;
        case REF_S_SINK:
            // delete queue entry from output stream
            target_iostream = get_iostream(fxn, ins.core, ins.stream);
            stream_dequeue(target_iostream->queue);
            break;
        }
    } // end opcode switch
    print_curr_state(*fxn, log);
    // If not at last instruction, increment PC
    if (!exec_function_completed(fxn))
    {
        if (!fxn->waiting)
        {
            fxn->pc += 1;
        }
        else
        {
            fxn->parent->time_blocking += 1;
        }
    }
}

/**
 * @brief Return the ID of a core that issued an interrupt to this one.
 *
 * @details If any elements of sigvec are triggered, return the index of that
 * element (i.e. which core caused the interrupt). If there are multiple pending
 * interrupts, only the first (in ascending numerical order) will be returned.
 *
 * @param[in] num_cores The number of cores being used (and thus the size of the sigvec).
 * @param[in] core Pointer to
 * @return The index of the an interrupting core; -1 if no interrupts are active.
 */
int interrupt_active(int num_cores, struct exec_core *core)
{
    for (int i = 0; i < num_cores; i++)
    {
        if (core->sigvec[i] == true)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Execute the program on all cores.
 *
 * @param[in] num_cores The number of cores being used in this run.
 * @param cores An array of pointers to the @c exec_cores.
 */
void execute(int num_cores, struct exec_core **cores)
{
    FILE *core_logs[num_cores];
    system("rm -r logs");
    system("mkdir -p logs");
    for (int i = 0; i < num_cores; i++)
    {
        char filename[30];
        sprintf(filename, "logs/core%d.out", i);
        core_logs[i] = fopen(filename, "w");
    }

    int time = 0;
    int parallel_cycles = 0;
    int streams_running = 0;
    bool running = true;
    while (running)
    {
        // If a core's main function is still runnable, give it a turn to execute
        int num_active = 0;
        for (int c = 0; c < num_cores; c++)
        {
            struct exec_core *curr_core = cores[c];
            struct exec_function *curr_fxn;

            if (curr_core->core_halted == true)
            {
                break;
            }

            if (interrupt_active(num_cores, curr_core) != -1)
            {
                // do execution on interrupt function
                curr_fxn = &curr_core->signal_fxn;
                if (!exec_function_completed(curr_fxn))
                {
                    curr_fxn->running = true;
                    execute_instruction(curr_fxn, curr_fxn->code_stack[curr_fxn->pc].ins, core_logs[c]);
                }
                else
                {
                    // interrupt function complete, deactivate the interrupt signal
                    int interrupt_id = interrupt_active(num_cores, curr_core);
                    curr_core->sigvec[interrupt_id] = false;
                    curr_fxn->running = false;
                    reset_exec_function(curr_fxn);
                    // core will return to executing main
                }
                num_active += 1;
            }

            else
            {
                // Run the main function, if possible
                if (exec_function_runnable(&curr_core->main_fxn))
                {
                    curr_fxn = &curr_core->main_fxn;
                    curr_fxn->running = true;
                    // mark this core as active
                    num_active += 1;
                    // execute instruction at PC
                    execute_instruction(curr_fxn, curr_fxn->code_stack[curr_fxn->pc].ins, core_logs[c]);
                }
                // Run any stream functions, if needed
                curr_fxn = curr_core->stream_fxns;
                while (curr_fxn != NULL)
                {
                    if (stream_function_runnable(curr_fxn))
                    {
                        streams_running += 1;
                        // If the function has not yet begun running, but is eligible to,
                        // then load the values from the input packet and put
                        // them into its local variables.
                        if (!curr_fxn->running)
                        {
                            curr_fxn->running = true;
                            translate_input_packet(curr_fxn);
                        }
                        num_active += 1;
                        execute_instruction(curr_fxn, curr_fxn->code_stack[curr_fxn->pc].ins, core_logs[c]);
                        // Once the stream function is finished/returns,
                        // reset its state and remove the data it was using
                        // from the queue. If there is still other data in the
                        // queue, it will run next cycle using that.
                        if (exec_function_completed(curr_fxn))
                        {
                            finish_stream_function(curr_fxn);
                        }
                    }
                    curr_fxn = curr_fxn->next;
                }
            }
        }

        // End execution if all main cores are terminated
        if (num_active == 0)
        {
            running = false;
        }

        if (streams_running > 0)
        {
            parallel_cycles += 1;
        }

        time += 1;
    }
    printf("Program execution finished after %d cycles\n", time);
    printf("Of those, %d cycles involved parallel execution\n", parallel_cycles);

    for (int c = 0; c < num_cores; c++)
    {
        printf("Core %s spent %d cycles I/O blocked\n", cores[c]->name, cores[c]->time_blocking);
    }
}