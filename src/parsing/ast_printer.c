/**
 * @file ast_printer.c
 * @brief Module containing methods to display and log the creation of the AST
 * from the parsed code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ast.h>
#include <ast_printer.h>

/**
 * @brief Array containing names corresponding to values of the \ref ast_type
 * enum. The positions of strings in the array correspond to the integer values
 * of the enums they represent.
 */
char *ast_type_name[] = {"PROGRAM", "CORE", "MAIN", "SIGNAL", "MATCH_SOURCE",
						 "MATCH_CASE_IDENTIFIER", "SIGEN", "SIGDIS", "VAR_DECL", "CONSTANT", "VAR_ASSIGN",
						 "IF", "ELSE", "STREAM", "FUNC_HEADER", "WHILE", "EXPOSE", "PIPELINE", "LINK_PORT", "LINK",
						 "EXPRESSION", "VARIABLE", "TRIGGER", "STREAM_PUSH", "AST_NULL", "STREAM_CALL_ARG",
						 "STREAM_PULL", "STREAM_PULL_ARG", "AST_NOP", "PRINT", "PRINTSTRING"};

/**
 * @brief Array containing names corresponding to values of the \ref var_type
 * enum. The positions of strings in the array correspond to the integer values
 * of the enums they represent.
 */
char *variable_type_name[] = {"i32"};

/**
 * @brief Array containing names corresponding to values of the
 * \ref operator_type enum. The positions of strings in the array correspond to
 * the integer values of the enums they represent.
 */
char *op_type_name[] = {"+", "*", "-", "/", "&", "|", "<", "<=", ">", ">=", "==", "!="};

/**
 * @brief Get a string name corresponding to a provided AST node type.
 *
 * @param[in] type An AST node type.
 * @return char* The name of that AST node type.
 */
char *ast_type_to_str(enum ast_type type)
{
	return ast_type_name[type];
}

/**
 * @brief Get a string name corresponding to a provided AST variable type.
 *
 * @param[in] type An AST variable type.
 * @return char* The name of that AST variable type.
 */
char *var_type_to_str(enum var_type type)
{
	return variable_type_name[type];
}

/**
 * @brief Print the contents of an AST node (and, recursively, all nodes below
 * it) in a Graphviz-friendly format.
 *
 * @param[out] fp Pointer to an output stream.
 * @param[in] head Pointer to the head node of AST or subtree.
 */
void print_ast_node(FILE *fp, struct ast_node *head)
{

	if (head == (struct ast_node *)0)
		return;

	// printf("Printing %s\n",ast_type_name[head->type]);
	switch (head->type)
	{
	case VAR_DECL:
		fprintf(fp, "x%d [shape=box,label=\"%s\\n%s:i32\"]\n", head->node_id, ast_type_name[head->type], head->name);
		break;
	case CONSTANT:
		fprintf(fp, "x%d [shape=box,label=\"CONST\n%d\"]\n", head->node_id, head->value);
		break;
	case VAR_ASSIGN:
		fprintf(fp, "x%d [shape=box,label=\"%s\\n%s = \"]\n", head->node_id, ast_type_name[head->type], head->name);
		break;
	case IF:
		fprintf(fp, "x%d [shape=box,label=\"\\nIF\"]\n", head->node_id);
		print_ast_node(fp, head->condition);
		fprintf(fp, "x%d -> x%d[label=\"(condition)\"]\n", head->node_id, (head->condition)->node_id);
		break;
	case ELSE:
		fprintf(fp, "x%d [shape=box,label=\"\\nELSE\"]\n", head->node_id);
		break;
	case WHILE:
		fprintf(fp, "x%d [shape=box,label=\"\\nWHILE\"]\n", head->node_id);
		print_ast_node(fp, head->condition);
		fprintf(fp, "x%d -> x%d[label=\"(condition)\"]\n", head->node_id, (head->condition)->node_id);
		break;
	case FUNC_HEADER:
		fprintf(fp, "x%d [shape=box,label=\"%s()\"]\n", head->node_id, head->name);
		break;
	case STREAM:
		fprintf(fp, "x%d [shape=box,label=\"%s\"]\n", head->node_id, ast_type_name[head->type]);
		// fprintf(fp,"x%d [shape=box,label=\"->%s()\"]\n",(head->stream_in)->node_id,(head->stream_in)->name);
		print_ast_node(fp, head->stream_in);
		// fprintf(fp,"x%d [shape=box,label=\"%s()->\"]\n",(head->stream_out)->node_id,(head->stream_out)->name);
		print_ast_node(fp, head->stream_out);
		fprintf(fp, "x%d -> x%d\n", head->node_id, (head->stream_in)->node_id);
		fprintf(fp, "x%d -> x%d\n", head->node_id, (head->stream_out)->node_id);
		break;
	case EXPRESSION:
		fprintf(fp, "x%d [shape=box,label=\"%s\"]\n", head->node_id, op_type_name[head->operation]);
		print_ast_node(fp, head->left);
		print_ast_node(fp, head->right);
		fprintf(fp, "x%d -> x%d\n", head->node_id, (head->left)->node_id);
		fprintf(fp, "x%d -> x%d\n", head->node_id, (head->right)->node_id);
		break;
	case STREAM_PUSH:
		fprintf(fp, "x%d [shape=box,label=\"%s\\n%s().%s\"]\n", head->node_id, ast_type_name[head->type], head->name, head->port_name);
		break;
	case AST_NULL:
		fprintf(fp, "x%d [shape=box,label=\"null\"]\n", head->node_id);
		break;
	case TRIGGER:
		fprintf(fp, "x%d [shape=box,label=\"%s\\ntarget:%s\"]\n", head->node_id, ast_type_name[head->type], head->name);
		break;
	case MATCH_CASE_IDENTIFIER:
		fprintf(fp, "x%d [shape=box,label=\"%s\\nsource: %s\"]\n", head->node_id, ast_type_name[head->type], head->name);
		break;
	case VARIABLE:
		fprintf(fp, "x%d [shape=box,label=\"%s\\n%s:i32\"]\n", head->node_id, ast_type_name[head->type], head->name);
		break;
	case PRINT_STRING:
		fprintf(fp, "x%d [shape=box,label=\"%s\\n'%s'\"]\n", head->node_id, ast_type_name[head->type], head->name);
		break;
	case CORE:
		fprintf(fp, "x%d [shape=box,label=\"%s\\n%s\"]\n", head->node_id, ast_type_name[head->type], head->name);
		break;
	case HALT:
		fprintf(fp, "x%d [shape=box,label=\"HALT\"]\n", head->node_id);
		break;
	case CATCH_FIRE:
		fprintf(fp, "x%d [shape=box,label=\"?!?!\"]\n", head->node_id);
		break;
	default:
		fprintf(fp, "x%d [shape=box,label=\"%s\"]\n", head->node_id, ast_type_name[head->type]);
		break;
	}

	struct ast_node *tmp = head->down;

	while (tmp != (struct ast_node *)0)
	{
		print_ast_node(fp, tmp);
		tmp = tmp->side;
	}

	tmp = head->down;
	while (tmp != (struct ast_node *)0)
	{
		fprintf(fp, "x%d -> x%d\n", head->node_id, tmp->node_id);
		tmp = tmp->side;
	}

	if (head->type == IF)
	{
		print_ast_node(fp, head->else_node);
		// fprintf(fp,"x%d -> x%d [label=\"ELSE\"]\n",head->node_id,(head->else_node)->node_id);
		if (head->else_node != NULL)
		{
			fprintf(fp, "x%d -> x%d\n", head->node_id, (head->else_node)->node_id);
		}
		else
		{
			fprintf(fp, "x%d\n", head->node_id);
		}
	}
}

/**
 * @brief Recursively generate an ID for every node in the AST.
 *
 * @param[in] head Pointer to the head node of the AST.
 */
void id_ast(struct ast_node *head)
{
	static int cnt = 0;

	head->node_id = cnt;
	cnt++;
	if (head->down != (struct ast_node *)0)
		id_ast(head->down);
	if (head->side != (struct ast_node *)0)
		id_ast(head->side);
	if (head->condition != (struct ast_node *)0)
		id_ast(head->condition);
	if (head->else_node != (struct ast_node *)0)
		id_ast(head->else_node);
	if (head->stream_in != (struct ast_node *)0)
		id_ast(head->stream_in);
	if (head->stream_out != (struct ast_node *)0)
		id_ast(head->stream_out);
	if (head->right != (struct ast_node *)0)
		id_ast(head->right);
	if (head->left != (struct ast_node *)0)
		id_ast(head->left);
}

/**
 * @brief Print a diagram of the AST using Graphviz.
 *
 * @param[in] head Pointer to the head node of the AST.
 */
void print_ast(struct ast_node *head)
{
	FILE *fp;

	system("mkdir -p structures");

	fp = fopen("structures/ast.dot", "w");

	// print AST

	id_ast(head);

	fprintf(fp, "digraph ast {\n");

	print_ast_node(fp, head);

	fprintf(fp, "}\n");

	// system("cd structures");
	// system("cd ..");

	fclose(fp);
	system("dot -Tpng structures/ast.dot > structures/ast.png");
}