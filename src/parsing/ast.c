#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ast.h>

struct ast_node *ast_head = (struct ast_node *)0;
extern int errors;

/*
	Helper function to propagate stream arg/port/core names across stream args
	(very useful for code generation)
*/
void populate_stream_names(char *p, char *c, struct ast_node *args)
{
	if (args == (struct ast_node *)0)
		return;
	if (args->type != STREAM_CALL_ARG)
	{
		errors++;
		printf("Error: invalid argument passing in stream call.\n");
	}

	// populate p and c
	args->port_name = (char *)malloc(strlen(p) + 1);
	strcpy(args->port_name, p);

	args->core_name = (char *)malloc(strlen(c) + 1);
	strcpy(args->core_name, c);

	// need to find argument name, based on order
	// but we don't have that information at parsing time
	// so need to do this later, during code generation

	populate_stream_names(p, c, args->side);
}

void populate_pull_stream_names(char *p, char *c, struct ast_node *args)
{
	if (args == (struct ast_node *)0)
		return;
	if (args->type != STREAM_PULL_ARG)
	{
		errors++;
		printf("Error: invalid argument passing in stream call.\n");
	}

	// populate p and c
	args->port_name = (char *)malloc(strlen(p) + 1);
	strcpy(args->port_name, p);

	args->core_name = (char *)malloc(strlen(c) + 1);
	strcpy(args->core_name, c);

	// need to find argument name, based on order
	// but we don't have that information at parsing time
	// so need to do this later, during code generation

	populate_stream_names(p, c, args->side);
}

// allocates a new ast node and ensures all pointer fields are properly null'ed
struct ast_node *alloc_ast_node()
{
	struct ast_node *tmp;
	tmp = (struct ast_node *)malloc(sizeof(struct ast_node));

	tmp->node_id = 0;
	tmp->name = (char *)0;
	tmp->port_name = (char *)0;

	tmp->link_port = (struct ast_node *)0;
	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	tmp->condition = (struct ast_node *)0;
	tmp->else_node = (struct ast_node *)0;
	tmp->stream_in = (struct ast_node *)0;
	tmp->stream_out = (struct ast_node *)0;
	tmp->left = (struct ast_node *)0;
	tmp->right = (struct ast_node *)0;

	tmp->core_name = (char *)0;
	tmp->arg_name = (char *)0;

	tmp->variable_type = I32;

	return tmp;
}

struct ast_node *new_ast_program(struct ast_node *a)
{
	struct ast_node *tmp = alloc_ast_node();

	tmp->type = PROGRAM;

	tmp->side = (struct ast_node *)0;
	tmp->down = a;

	return tmp;
}

struct ast_node *new_ast_core(char *core_name, struct ast_node *a)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = CORE;

	tmp->name = (char *)malloc(strlen(core_name) + 1);
	strcpy(tmp->name, core_name);

	tmp->side = (struct ast_node *)0;
	tmp->down = a;

	return tmp;
}

struct ast_node *new_ast_main(struct ast_node *a)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = MAIN;

	tmp->side = (struct ast_node *)0;
	tmp->down = a;

	return tmp;
}

struct ast_node *new_ast_signal(struct ast_node *a)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = SIGNAL;

	tmp->side = (struct ast_node *)0;
	tmp->down = a;

	return tmp;
}

struct ast_node *new_ast_match_source(struct ast_node *a)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = MATCH_SOURCE;

	tmp->side = (struct ast_node *)0;
	tmp->down = a;

	return tmp;
}

struct ast_node *new_ast_match_case_identifier(char *identifier, struct ast_node *a)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = MATCH_CASE_IDENTIFIER;

	tmp->name = (char *)malloc(strlen(identifier) + 1);
	strcpy(tmp->name, identifier);

	tmp->side = (struct ast_node *)0;
	tmp->down = a;

	return tmp;
}

struct ast_node *new_ast_trigger(char *i)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = TRIGGER;

	tmp->name = (char *)malloc(strlen(i) + 1);
	strcpy(tmp->name, i);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_sigen(void)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = SIGEN;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_sigdis(void)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = SIGDIS;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_i32var_decl(char *identifier)
{
	// TODO: Check that no other variable in scope already has this name,
	// and that no global variables have this name
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = VAR_DECL;

	tmp->name = (char *)malloc(strlen(identifier) + 1);
	strcpy(tmp->name, identifier);

	tmp->variable_type = I32;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_var_assign(char *identifier, struct ast_node *a)
{
	// TODO: Check that a variable with this identifier exists in scope or global
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = VAR_ASSIGN;

	tmp->name = (char *)malloc(strlen(identifier) + 1);
	strcpy(tmp->name, identifier);

	tmp->side = (struct ast_node *)0;
	tmp->down = a;

	return tmp;
}

struct ast_node *new_ast_const(int i)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = CONSTANT;

	tmp->value = i;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_if(struct ast_node *e)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = IF;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	tmp->else_node = e;

	return tmp;
}
struct ast_node *new_ast_else(struct ast_node *e)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = ELSE;

	tmp->side = (struct ast_node *)0;
	tmp->down = e;

	return tmp;
}

struct ast_node *new_ast_while(struct ast_node *e)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = WHILE;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	tmp->else_node = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_stream(char *in, char *out)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = STREAM;

	tmp->name = (char *)malloc(strlen(in) + strlen(out) + 1);
	strcpy(tmp->name, in);
	strcat(tmp->name, out);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_func_header(char *n)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = FUNC_HEADER;

	tmp->name = (char *)malloc(strlen(n) + 1);
	strcpy(tmp->name, n);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_expose(char *var, char *port)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = EXPOSE;

	tmp->name = (char *)malloc(strlen(var) + 1);
	strcpy(tmp->name, var);

	tmp->port_name = (char *)malloc(strlen(port) + 1);
	strcpy(tmp->port_name, port);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_pipeline(char *var)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = PIPELINE;

	tmp->name = (char *)malloc(strlen(var) + 1);
	strcpy(tmp->name, var);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_linkport(char *var, char *port)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = LINK_PORT;

	tmp->name = (char *)malloc(strlen(var) + 1);
	strcpy(tmp->name, var);

	tmp->port_name = (char *)malloc(strlen(port) + 1);
	strcpy(tmp->port_name, port);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_link(char *var, char *port)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = LINK;

	tmp->name = (char *)malloc(strlen(var) + 1);
	strcpy(tmp->name, var);

	tmp->port_name = (char *)malloc(strlen(port) + 1);
	strcpy(tmp->port_name, port);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_expression(enum operator_type o)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = EXPRESSION;

	tmp->operation = o;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_identifier(char *i)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = VARIABLE;

	tmp->name = (char *)malloc(strlen(i) + 1);
	strcpy(tmp->name, i);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_stream_push(char *port, char *core)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = STREAM_PUSH;

	tmp->name = (char *)malloc(strlen(core) + 1);
	strcpy(tmp->name, core);

	tmp->port_name = (char *)malloc(strlen(port) + 1);
	strcpy(tmp->port_name, port);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_stream_pull(char *port, char *core)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = STREAM_PULL;

	tmp->name = (char *)malloc(strlen(core) + 1);
	strcpy(tmp->name, core);

	tmp->port_name = (char *)malloc(strlen(port) + 1);
	strcpy(tmp->port_name, port);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_null()
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = AST_NULL;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_nop()
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = AST_NOP;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_halt()
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = HALT;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_fire()
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = CATCH_FIRE;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_print(int val)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = PRINT;

	tmp->value = val;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_print_identifier(char *name)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = PRINT_IDENTIFIER;

	tmp->name = (char *)malloc(strlen(name) + 1);
	strcpy(tmp->name, name);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_printstring(char *str)
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = PRINT_STRING;

	tmp->name = (char *)malloc(strlen(str) + 1);
	strcpy(tmp->name, str);

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_call_arg()
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = STREAM_CALL_ARG;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}

struct ast_node *new_ast_pull_arg()
{
	struct ast_node *tmp = alloc_ast_node();
	tmp->type = STREAM_PULL_ARG;

	tmp->side = (struct ast_node *)0;
	tmp->down = (struct ast_node *)0;

	return tmp;
}