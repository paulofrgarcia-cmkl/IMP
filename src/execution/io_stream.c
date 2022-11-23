#include <stdlib.h>
#include <string.h>

#include <io_stream.h>
#include <stream_queue.h>
#include <var_mapping.h>
#include <util.h>

/**
 * @brief Allocate and initialize a new stream_argument.
 *
 * @param name The name to give the new stream_argument.
 * @param type The data type that the argument holds.
 * @return A pointer to the new stream_argument.
 */
struct stream_argument *new_stream_arg(char *name, enum var_type type)
{
    struct stream_argument *new_arg = malloc(sizeof(struct stream_argument));
    deep_copy_string(&new_arg->arg_name, &name);
    new_arg->type = type;
    new_arg->next = NULL;
    return new_arg;
}

/**
 * @brief Allocate and initialize a new io_stream.
 *
 * @param name The name to give the new io_stream.
 * @param dir Whether the io_stream is the input or output of the stream function.
 * @return A pointer to the new io_stream.
 */
struct io_stream *new_io_stream(char *name, enum stream_direction dir)
{
    struct io_stream *new_stream = malloc(sizeof(struct io_stream));
    deep_copy_string(&new_stream->name, &name);
    new_stream->direction = dir;
    new_stream->args = NULL;
    new_stream->pkt_under_construction = NULL;
    new_stream->queue = initialize_queue();
    return new_stream;
}

/**
 * @brief Translate an arch_symbol into a stream_argument.
 *
 * This is used when building stream functions and assigning their arguments.
 *
 * @param sym The symbol to translate.
 * @return A pointer to the new stream_argument.
 */
struct stream_argument *symbol_to_arg(struct arch_symbol *sym)
{
    struct stream_argument *new_arg = new_stream_arg(sym->name, sym->type);
}

/**
 * @brief Add a new argument to an io_stream.
 *
 * @param stream The io_stream to add an argument to.
 * @param sym The symbol to translate into the new argument.
 */
void add_stream_arg(struct io_stream *stream, struct arch_symbol *sym)
{
    struct stream_argument *new_arg = symbol_to_arg(sym);

    if (stream->args == NULL)
    {
        stream->args = new_arg;
    }
    else
    {
        new_arg->next = stream->args;
        stream->args = new_arg;
    }
}

/**
 * @brief Get a reference to a specific stream_argument based on its name.
 *
 * This does assume that no stream functions are written with two arguments
 * that share a name.
 *
 * @param stream The io_stream the target argument belongs to.
 * @param name The name of the target argument.
 * @return A pointer to the target argument, if it was found, NULL otherwise.
 */
struct stream_argument *get_iostream_arg_by_name(struct io_stream *stream, char *name)
{
    struct stream_argument *curr_arg = stream->args;
    while (curr_arg != NULL)
    {
        if (!strcmp(curr_arg->arg_name, name))
        {
            return curr_arg;
        }
        else
        {
            curr_arg = curr_arg->next;
        }
    }
    return NULL;
}

void commit_args(struct io_stream *stream)
{
}

/**
 * @brief Determine whether a stream function is runnable.
 *
 * A stream function is runnable if its input queue is not empty.
 * When the function completes (see exec_function_completed()), it should remove
 * the stream_packet it used from the head of the queue.
 *
 * @param fxn
 * @return bool
 */
bool stream_function_runnable(struct exec_function *fxn)
{
    // Input queue must not be empty
    if (stream_peek(fxn->in_stream->queue) == NULL)
    {
        return false;
    }
    return true;
}

/**
 * @brief Generate an empty stream_packet that fits the interface of the
 * provided io_stream.
 *
 * @param stream The stream whose interface is to be matched.
 * @return A pointer to the generated packet.
 */
struct stream_packet *build_stream_packet(struct io_stream *stream)
{
    struct stream_packet *new_pkt = initialize_stream_packet();
    struct stream_argument *args = stream->args;
    while (args != NULL)
    {
        struct var_mapping *new_map = new_var_mapping(args->arg_name);
        new_map->next = new_pkt->args;
        new_pkt->args = new_map;
        args = args->next;
    }
    return new_pkt;
}
