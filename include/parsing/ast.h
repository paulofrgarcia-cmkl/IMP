/**
 * @file ast.h
 * @brief fdfsd
 */
#ifndef AST_H
#define AST_H

/**
 * @brief Enum of all possible AST node types.
 */
enum ast_type
{
	PROGRAM,
	CORE,
	MAIN,
	SIGNAL,
	MATCH_SOURCE,
	MATCH_CASE_IDENTIFIER,
	SIGEN,
	SIGDIS,
	VAR_DECL,
	CONSTANT,
	VAR_ASSIGN,
	IF,
	ELSE,
	STREAM,
	FUNC_HEADER,
	WHILE,
	EXPOSE,
	PIPELINE,
	LINK_PORT,
	LINK,
	EXPRESSION,
	VARIABLE,
	TRIGGER,
	STREAM_PUSH,
	AST_NULL,
	STREAM_CALL_ARG,
	STREAM_PULL,
	STREAM_PULL_ARG,
	AST_NOP,
	PRINT,
	PRINT_STRING,
	PRINT_IDENTIFIER,
	HALT,
	CATCH_FIRE
};

/**
 * @brief Enum of all possible AST node variable types.
 */
enum var_type
{
	I32
};

/**
 * @brief Enum of all possible AST node operators.
 */
enum operator_type
{
	PLUS,
	TIMES,
	MINUS,
	DIVIDE,
	AND,
	OR,
	LESS,
	LESSEQUAL,
	GREATER,
	GREATEREQUAL,
	EQUALS,
	NOTEQUALS
};

/**
 * @brief A single node in an AST, representing an instruction parsed from code.
 */
struct ast_node
{
	/// not used for any AST stuff, but useful for printing it
	int node_id;

	/// type of AST node for all sorts of processing
	enum ast_type type;

	/// name of core or variable
	char *name;
	/// if variable, its type
	enum var_type variable_type;
	/// if constant, value
	int value;

	/// for the case of stream operations, name of port
	char *port_name;
	/// for the case of stream operations, name of core
	char *core_name;
	/// for the case of stream operations, name of argument
	char *arg_name;

	/// for link operations, pointer to destination to keep names to a minimum
	struct ast_node *link_port;

	/// next element at same syntactic level
	struct ast_node *side;
	/// first element in deeper syntactic level
	struct ast_node *down;

	/// constructs like "if" need an additional element for the condition
	struct ast_node *condition;
	/// and it's convenient for parsing to have dedicated "else" here
	struct ast_node *else_node;

	/// stream constructs hold in/out headers (each same as function headers)
	struct ast_node *stream_in;
	struct ast_node *stream_out;

	/** expression constructs hold left and right pointers for operator args
	 * and corresponding operator */
	struct ast_node *left;
	struct ast_node *right;
	enum operator_type operation;
};

struct ast_node *new_ast_program(struct ast_node *a);
struct ast_node *new_ast_core(char *core_name, struct ast_node *a);
struct ast_node *new_ast_main(struct ast_node *a);
struct ast_node *new_ast_signal(struct ast_node *a);
struct ast_node *new_ast_match_source(struct ast_node *a);
struct ast_node *new_ast_match_case_identifier(char *identifier, struct ast_node *a);
struct ast_node *new_ast_sigen(void);
struct ast_node *new_ast_sigdis(void);
struct ast_node *new_ast_i32var_decl(char *identifier);

struct ast_node *new_ast_var_assign(char *identifier, struct ast_node *a);
struct ast_node *new_ast_const(int i);

struct ast_node *new_ast_if(struct ast_node *e);
struct ast_node *new_ast_else(struct ast_node *e);

struct ast_node *new_ast_while();

struct ast_node *new_ast_stream(char *in, char *out);
struct ast_node *new_ast_func_header(char *n);

struct ast_node *new_ast_expose(char *var, char *port);

struct ast_node *new_ast_pipeline(char *var);

struct ast_node *new_ast_linkport(char *var, char *port);

struct ast_node *new_ast_link(char *var, char *port);

struct ast_node *new_ast_expression(enum operator_type o);
struct ast_node *new_ast_identifier(char *i);

struct ast_node *new_ast_trigger(char *i);

struct ast_node *new_ast_stream_push(char *port, char *core);
struct ast_node *new_ast_stream_pull(char *port, char *core);

struct ast_node *new_ast_null();
struct ast_node *new_ast_nop();
struct ast_node *new_ast_halt();
struct ast_node *new_ast_fire();

struct ast_node *new_ast_print(int val);
struct ast_node *new_ast_printstring(char *str);
struct ast_node *new_ast_print_identifier(char *name);

struct ast_node *new_ast_call_arg();
struct ast_node *new_ast_pull_arg();

void populate_stream_names(char *p, char *c, struct ast_node *args);
void populate_pull_stream_names(char *p, char *c, struct ast_node *args);

#endif