#ifndef ARCH_H
#define ARCH_H

#include "ast.h"
#include "code_gen.h"

enum arg_status
{
	ARG_IN,
	ARG_OUT,
	LOCAL,
	GLOBAL
};

// symbols in each function
struct arch_symbol
{
	char *name;
	// memory index for code generation
	int index;
	// eventually, type here
	enum var_type type;

	// for streams, we need to know if variable is in or out argument
	enum arg_status status;

	// pointer to next symbol in function
	struct arch_symbol *next;
};

// implements code for any function
struct arch_function
{

	// list of inner symbols
	struct arch_symbol *symbols;

	// for regular "functions", this is function name
	// for stream functions, name of input port
	char *in_name;

	// for stream functions, name of output port
	char *out_name;

	// pointer to next function at the same hierarchical level
	struct arch_function *next;

	// list of instructions that make up the function
	struct ir_instruction *code;
};

struct arch_core
{
	// uniquely identifies each core
	char *name;

	// global variables
	struct arch_symbol *g_symbols;

	// core's "main" function
	struct arch_function *main_function;

	// core's interrupt (signal) function
	struct arch_function *signal_function;

	struct arch_function *stream_functions;

	// sub-cores instantiated here
	struct arch_core *inner_cores;

	// pointer to next core at the same hierarchical level
	struct arch_core *next;
};

struct arch
{
	// list of all the top level cores defined in the system
	struct arch_core *arch_cores;
};

struct arch *generate_arch(struct ast_node *head);
struct arch_core *generate_core_symbols(struct ast_node *head);
void generate_core_code(struct arch_core *curr_core, struct ast_node *head);
void generate_function(struct arch_core *my_core, struct ast_node *head);
void generate_symbols(struct arch_core *my_core, struct ast_node *head);
void generate_arch_code(struct arch *my_arch, struct ast_node *head);

/*
	Code generation helper functions

	Traverse arch data structures to obtain specific info for code generation
	Most semantic analysis and sanity checks should probably be placed here as well
*/
char *get_stream_inarg_name_by_index(char *core, char *stream, int index);
int count_cores(struct arch *a);
int count_instructions(struct arch_function *fxn);
void function_to_array(struct ir_instruction **code_arr, int *label_table, struct arch_function *fxn);
void resolve_jmp(struct ir_instruction **code_arr, int *label_table, int len);
struct ir_instruction **translate_function(struct arch_function *fxn);
char *filename_from_path(char *source);
int count_symbols(struct arch_symbol *s);
void free_symbol(struct arch_symbol *sym);

#endif