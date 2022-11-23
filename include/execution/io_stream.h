#ifndef STREAM_DATA_H
#define STREAM_DATA_H

#include <stdbool.h>

#include <ast.h>
#include <arch.h>

#include <exec_core.h>

enum stream_direction
{
    STREAM_IN,
    STREAM_OUT
};

/**
 * @brief A single argument possessed by an io_stream.
 *
 * This is used to determine what values are to be passed in/out from the
 * io_stream.
 */
struct stream_argument
{
    char *arg_name;
    enum var_type type;
    struct stream_argument *next;
};

/**
 * @brief An input or output belonging to a stream function.
 *
 * Each core should have one input stream and one output stream. This struct
 * defines the name of that stream, whether it serves as input or output,
 * and the arguments that can be passed to the function. It also contains
 * a queue of inbound or outbound data.
 */
struct io_stream
{
    char *name;
    enum stream_direction direction;
    struct stream_queue *queue;
    struct stream_packet *pkt_under_construction;
    // linked-list of arguments
    struct stream_argument *args;
};

struct stream_argument *new_stream_arg(char *name, enum var_type type);
struct io_stream *new_io_stream(char *name, enum stream_direction dir);
// struct stream_function *new_stream_fxn(int id);

void add_stream_arg(struct io_stream *stream, struct arch_symbol *sym);
struct stream_argument *get_iostream_arg_by_name(struct io_stream *stream, char *name);

void commit_args(struct io_stream *stream);
bool stream_function_runnable(struct exec_function *fxn);

struct stream_packet *build_stream_packet(struct io_stream *stream);

#endif