#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ast.h>
#include <arch.h>

extern int errors;

/*
	First, generate each core, with a list of functions
	Generate symbols for those functions, marking arguments

	Then we re-iterate over all cores, generating code

*/

// traverses the AST to generate an architecture description (collection of cores and their relationships)
struct arch *generate_arch(struct ast_node *head)
{
	struct arch *my_arch;

	my_arch = (struct arch *)malloc(sizeof(struct arch));

	// if called and head is not program, return
	if (head->type != PROGRAM)
	{
		errors++;
		printf("Error: attempting to generate architecture from non-program type AST node.\n");
		return (struct arch *)0;
	}

	my_arch->arch_cores = (struct arch_core *)0;

	// all cores should be at same hierarchical level
	head = head->down;

	struct ast_node *ptr = head;

	while (ptr != (struct ast_node *)0)
	{
		// this will generate functions and symbols for cores, but no code
		struct arch_core *new_core = generate_core_symbols(ptr);

		if (new_core == (struct arch_core *)0)
		{
			errors++;
			printf("Error: failed to generate core from AST node.\n");
			return (struct arch *)0;
		}

		new_core->next = my_arch->arch_cores;
		my_arch->arch_cores = new_core;

		ptr = ptr->side;
	}

	// at this point, we should have an architecture description, all cores should be described
	return my_arch;
}

void generate_arch_code(struct arch *my_arch, struct ast_node *head)
{

	// now generate code for all functions in all cores
	struct arch_core *current_core = my_arch->arch_cores;
	head = head->down;

	while (current_core != (struct arch_core *)0)
	{
		generate_core_code(current_core, head);
		current_core = current_core->next;
	}

	// at this point, we should have an architecture description, all cores should be described, and all code generated
	return;
}

void generate_core_code(struct arch_core *curr_core, struct ast_node *head)
{
	// TODO here
	while (strcmp(curr_core->name, head->name) != 0)
	{
		head = head->side;
		if (head == (struct ast_node *)0)
		{
			errors++;
			printf("Error: could not find ast node for core \"%s\".\n", curr_core->name);
			return;
		}
	}

	head = head->down;
	// head now pointing to functions

	while (head != (struct ast_node *)0)
	{
		generate_function(curr_core, head);
		head = head->side;
	}
}

// This is required to generate correct offsets for global variables
int g_cntr = 0;

struct arch_core *generate_core_symbols(struct ast_node *head)
{
	struct arch_core *my_core;

	my_core = (struct arch_core *)malloc(sizeof(struct arch_core));

	// if called and head is not core, return
	if (head->type != CORE)
	{
		errors++;
		printf("Error: attempting to generate core from non-core type AST node.\n");
		return (struct arch_core *)0;
	}

	my_core->name = (char *)malloc(strlen(head->name) + 1);
	strcpy(my_core->name, head->name);

	my_core->main_function = (struct arch_function *)0;
	my_core->signal_function = (struct arch_function *)0;
	my_core->stream_functions = (struct arch_function *)0;
	my_core->g_symbols = (struct arch_symbol *)0;

	// generate symbols for each function

	// generate code for each core function
	// NULL stubs for now
	struct ast_node *function = head->down;
	g_cntr = 0;
	while (function != (struct ast_node *)0)
	{
		generate_symbols(my_core, function);
		function = function->side;
	}

	// point to inner cores
	// NULL stubs for now
	my_core->inner_cores = (struct arch_core *)0;
	my_core->next = (struct arch_core *)0;

	return my_core;
}

void generate_symbols(struct arch_core *my_core, struct ast_node *head)
{

	// if called and head is not valid function, return
	if ((head->type != MAIN) && (head->type != SIGNAL) && (head->type != STREAM))
	{
		// might be global variable declaration, to add to global symbols
		if (head->type == VAR_DECL)
		{
			struct arch_symbol *new_symbol = (struct arch_symbol *)malloc(sizeof(struct arch_symbol));

			new_symbol->name = (char *)malloc(strlen(head->name) + 1);
			strcpy(new_symbol->name, head->name);
			new_symbol->type = head->variable_type;

			new_symbol->index = g_cntr;

			new_symbol->status = GLOBAL;

			g_cntr += 4;

			new_symbol->next = my_core->g_symbols;
			my_core->g_symbols = new_symbol;
		}
		else
		{
			errors++;
			printf("Error: attempting to generate symbols from non-function type (main/signal) AST node.\n");
			return;
		}
	}

	struct arch_function *f;

	f = (struct arch_function *)malloc(sizeof(struct arch_function));

	f->next = (struct arch_function *)0;

	f->symbols = (struct arch_symbol *)0;

	f->code = (struct ir_instruction *)0;

	f->in_name = NULL;
	f->out_name = NULL;

	struct ast_node *sym_finder;
	int index_ctr = 0;

	if (head->type == STREAM)
	{
		sym_finder = (head->stream_in)->down;
		while (sym_finder != (struct ast_node *)0)
		{
			if (sym_finder->type == VAR_DECL)
			{
				struct arch_symbol *new_symbol = (struct arch_symbol *)malloc(sizeof(struct arch_symbol));

				new_symbol->name = (char *)malloc(strlen(sym_finder->name) + 1);
				strcpy(new_symbol->name, sym_finder->name);
				new_symbol->type = sym_finder->variable_type;

				new_symbol->index = index_ctr;

				new_symbol->status = ARG_IN;

				index_ctr += 4;

				new_symbol->next = f->symbols;
				f->symbols = new_symbol;
			}

			sym_finder = sym_finder->side;
		}
		sym_finder = (head->stream_out)->down;
		while (sym_finder != (struct ast_node *)0)
		{
			if (sym_finder->type == VAR_DECL)
			{
				struct arch_symbol *new_symbol = (struct arch_symbol *)malloc(sizeof(struct arch_symbol));

				new_symbol->name = (char *)malloc(strlen(sym_finder->name) + 1);
				strcpy(new_symbol->name, sym_finder->name);
				new_symbol->type = sym_finder->variable_type;

				new_symbol->index = index_ctr;

				new_symbol->status = ARG_OUT;

				index_ctr += 4;

				new_symbol->next = f->symbols;
				f->symbols = new_symbol;
			}

			sym_finder = sym_finder->side;
		}
	}

	// populate function symbol table
	sym_finder = head->down;

	while (sym_finder != (struct ast_node *)0)
	{
		if (sym_finder->type == VAR_DECL)
		{
			struct arch_symbol *new_symbol = (struct arch_symbol *)malloc(sizeof(struct arch_symbol));

			new_symbol->name = (char *)malloc(strlen(sym_finder->name) + 1);
			strcpy(new_symbol->name, sym_finder->name);
			new_symbol->type = sym_finder->variable_type;

			new_symbol->index = index_ctr;

			new_symbol->status = LOCAL;

			index_ctr += 4;

			new_symbol->next = f->symbols;
			f->symbols = new_symbol;
		}

		sym_finder = sym_finder->side;
	}

	// tidy up by mapping functions to core pointers
	if (head->type == MAIN)
	{
		if (my_core->main_function != (struct arch_function *)0)
		{
			errors++;
			printf("Error: attempting to override main function in core %s.\n", my_core->name);
			return;
		}
		else
		{
			my_core->main_function = f;
		}
	}
	if (head->type == SIGNAL)
	{
		if (my_core->signal_function != (struct arch_function *)0)
		{
			errors++;
			printf("Error: attempting to override signal function in core %s.\n", my_core->name);
			return;
		}
		else
		{
			my_core->signal_function = f;
		}
	}
	// for stream functions, we want to make sure we keep the names of input/output ports
	if (head->type == STREAM)
	{
		f->in_name = (char *)malloc(strlen((head->stream_in)->name) + 1);
		strcpy(f->in_name, (head->stream_in)->name);

		f->out_name = (char *)malloc(strlen((head->stream_out)->name) + 1);
		strcpy(f->out_name, (head->stream_out)->name);

		if (my_core->stream_functions == (struct arch_function *)0)
		{
			my_core->stream_functions = f;
		}
		else
		{
			struct arch_function *tmp_f = my_core->stream_functions;
			while (tmp_f->next != (struct arch_function *)0)
			{
				tmp_f = tmp_f->next;
			}
			tmp_f->next = f;
		}
	}
}

void generate_function(struct arch_core *my_core, struct ast_node *head)
{
	// if called and head is not valid function, return
	if ((head->type != MAIN) && (head->type != SIGNAL) && (head->type != STREAM))
	{
		// skip for global variable declaration
		if (head->type == VAR_DECL)
		{
			return;
		}
		errors++;
		printf("Error: attempting to generate function from non-function type (main/signal/stream) AST node.\n");
		return;
	}

	if (head->type == MAIN)
	{
		if (my_core->main_function == (struct arch_function *)0)
		{
			errors++;
			printf("Error: attempting to generate code for non symbol-initialized main function in core %s.\n", my_core->name);
			return;
		}
		else
		{
			(my_core->main_function)->code = generate_code(head, 0, 0);
		}
	}
	if (head->type == SIGNAL)
	{
		if (my_core->signal_function == (struct arch_function *)0)
		{
			errors++;
			printf("Error: attempting to generate code for non symbol-initialized signal function in core %s.\n", my_core->name);
			return;
		}
		else
		{
			(my_core->signal_function)->code = generate_code(head, 0, 0);
		}
	}
	// for stream functions, we want to make sure we keep the names of input/output ports
	if (head->type == STREAM)
	{
		struct arch_function *f = my_core->stream_functions;

		while (f != (struct arch_function *)0)
		{
			f->code = generate_code(head, 0, 0);
			f = f->next;
		}
	}
}

/*
	Code generation helper functions

	Traverse arch data structures to obtain specific info for code generation
	Most semantic analysis and sanity checks should probably be placed here as well
*/

extern struct arch *my_arch;

// returns name of argument in stream
char *get_stream_inarg_name_by_index(char *core, char *stream, int index)
{

	struct arch_core *cores = my_arch->arch_cores;

	while (strcmp(core, cores->name) != 0)
	{
		cores = cores->next;
		if (cores == (struct arch_core *)0)
		{
			errors++;
			printf("Error: attempting to find non-existing core \"%s\".\n", core);
			return (char *)0;
		}
	}

	struct arch_function *f = cores->stream_functions;

	while (strcmp(stream, f->in_name) != 0)
	{
		f = f->next;
		if (f == (struct arch_function *)0)
		{
			errors++;
			printf("Error: attempting to find non-existing stream \"%s\" in core \"%s\".\n", stream, core);
			return (char *)0;
		}
	}

	// I suspect this will be in reverse order, but we can correct this later
	struct arch_symbol *s = f->symbols;

	while (s != (struct arch_symbol *)0)
	{
		if (s->status == ARG_IN)
		{
			if (index == 0)
				return s->name;
			index--;
		}
		s = s->next;
	}

	errors++;
	printf("Error: too many arguments in stream\n.");
	return (char *)0;
}

// Traverse list and count number of cores in arch
int count_cores(struct arch *a)
{
	int num_cores = 0;
	struct arch_core *curr_core = a->arch_cores;
	while (curr_core != NULL)
	{
		num_cores += 1;
		curr_core = curr_core->next;
	}

	return num_cores;
}

int count_instructions(struct arch_function *fxn)
{
	struct ir_instruction *ins_list = fxn->code;
	int ins_len = 0;
	// iterate over instruction list
	while (ins_list != NULL)
	{
		ins_len += 1;
		ins_list = ins_list->next;
	}
	return ins_len;
}

// Count the number of symbols in a provided linked list
int count_symbols(struct arch_symbol *s)
{
	struct arch_symbol *curr_sym = s;
	int num_symbols = 0;
	while (curr_sym != NULL)
	{
		num_symbols += 1;
		curr_sym = curr_sym->next;
	}
	return num_symbols;
}

// Translate a function held into a linked-list into a provided array.
void function_to_array(struct ir_instruction **code_arr, int *label_table, struct arch_function *fxn)
{
	// number of instructions in function
	int ins_len = count_instructions(fxn);

	// pointer to current instruction in instruction linked list
	struct ir_instruction *ins_list = fxn->code;
	for (int i = 0; i < ins_len; i++)
	{
		code_arr[i] = ins_list;
		if (ins_list->label != 0)
		{
			label_table[ins_list->label] = i;
		}
		ins_list = ins_list->next;
	}
}

// Replace JMP addresses in instructions with code array indices
void resolve_jmp(struct ir_instruction **code_arr, int *label_table, int ins_len)
{
	// iterate over array and replace
	for (int i = 0; i < ins_len; i++)
	{
		if (code_arr[i]->opcode == JMP_t ||
			(code_arr[i]->opcode == REF_t && code_arr[i]->sub_opcode.REF_t_opcode == REF_MATCH_SOURCE))
		{
			// replace the JMP target with the appropriate index, as stored
			// in the label table.
			code_arr[i]->jmp_target = label_table[code_arr[i]->jmp_target];
		}
	}
}

// Replace instruction labels with their translated counterparts
// (for the purposes of printed code making sense)
// Tecnically redundant, since this just prints out line numbers??
void replace_labels(struct ir_instruction **code_arr, int *label_table, int ins_len)
{
	for (int i = 0; i < ins_len; i++)
	{
		if (code_arr[i]->label != 0)
		{
			code_arr[i]->label = label_table[code_arr[i]->label];
		}
	}
}

struct ir_instruction **translate_function(struct arch_function *fxn)
{
	// number of instructions in function
	int ins_len = count_instructions(fxn);
	struct ir_instruction **code_arr = malloc(sizeof(struct ir_instruction *) * ins_len);
	// table to map labels to array indices; line number is stored at index <label>
	int label_table[ins_len];
	// Initialize label table to 0; 0 should be invalid label.
	memset(label_table, 0, sizeof(label_table));

	function_to_array(code_arr, label_table, fxn);
	// note: resolving jump addresses is currently a destructive process
	// (does not preserve original labels)
	resolve_jmp(code_arr, label_table, ins_len);
	replace_labels(code_arr, label_table, ins_len);
	return code_arr;
}

char *filename_from_path(char *source)
{
	int length = 0;
	int i = 0;
	while (source[i] != '\0')
	{
		length++;
		i++;
	}

	int string_end = length - 1;
	// char name[length];
	// start working backwards
	// first, skip over file extension
	int curr_pos = string_end;
	while (source[curr_pos] != '.')
	{
		curr_pos--;
	}
	// skip over dot
	// curr_pos--;
	int name_end = curr_pos;
	// keep going back until we hit a slash
	while (source[curr_pos] != '/')
	{
		curr_pos--;
	}
	int name_start = curr_pos + 1;
	int name_len = name_end - name_start;

	char *name = malloc(sizeof(char) * name_len);
	curr_pos = name_start;
	// start copying into name array
	for (int i = 0; i < name_len; i++)
	{
		name[i] = source[curr_pos];
		curr_pos++;
	}

	return name;
}

void free_symbol(struct arch_symbol *sym)
{
	free(sym->name);
}