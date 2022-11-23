#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ast.h>
#include <arch.h>
#include <code_gen.h>

extern int errors;

// allocates space for a new instruction, and ensures pointer fields are null'ed
struct ir_instruction *alloc_instruction()
{
	struct ir_instruction *i = (struct ir_instruction *)malloc(sizeof(struct ir_instruction));

	i->identifier = (char *)0;
	i->next = (struct ir_instruction *)0;
	i->core = (char *)0;
	i->stream = (char *)0;

	i->label = 0;

	return i;
}

// We'll probably collapse all arguments to this function (except h) into a struct called "context"

struct ir_instruction *generate_code(struct ast_node *h, int match_statement_end, int stream_call_index)
{
	struct ir_instruction *i;

	if (h == (struct ast_node *)0)
	{
		return (struct ir_instruction *)0;
	}

	i = alloc_instruction();

	struct ir_instruction *ptr;

	switch (h->type)
	{
	case MAIN:
	case SIGNAL:
	case STREAM:
		free(i);
		i = generate_code(h->down, match_statement_end, 0);
		break;
	case VAR_DECL:
		free(i);
		i = generate_code(h->side, match_statement_end, 0);
		break;
	// variable use: push identifier
	case VARIABLE:
		i->opcode = PUSH_t;
		i->sub_opcode.PUSH_t_opcode = PUSH_I32_IDENTIFIER;
		i->identifier = (char *)malloc(strlen(h->name) + 1);
		strcpy(i->identifier, h->name);
		i->next = (struct ir_instruction *)0;
		break;
	case CONSTANT:
		i->opcode = PUSH_t;
		i->sub_opcode.PUSH_t_opcode = PUSH_I32_CONST;
		i->constant = h->value;
		i->next = (struct ir_instruction *)0;
		break;
	case EXPRESSION:
		free(i);
		i = generate_code(h->left, match_statement_end, 0);
		ptr = i;
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = generate_code(h->right, match_statement_end, 0);
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = alloc_instruction();
		ptr = ptr->next;
		ptr->opcode = ALU_t;
		ptr->sub_opcode.ALU_t_opcode = get_ALU_opcode(h->operation);
		ptr->next = (struct ir_instruction *)0;
		break;
	case VAR_ASSIGN:
		free(i);
		i = generate_code(h->down, match_statement_end, 0);
		ptr = i;
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = alloc_instruction();
		ptr = ptr->next;
		ptr->opcode = POP_t;
		ptr->sub_opcode.POP_t_opcode = POP_I32_IDENTIFIER;
		ptr->identifier = (char *)malloc(strlen(h->name) + 1);
		strcpy(ptr->identifier, h->name);
		ptr->next = generate_code(h->side, match_statement_end, 0);
		break;
	case ELSE:
		free(i);
		i = generate_code(h->down, match_statement_end, 0);
		break;
	case IF:
		free(i);
		// if no else
		if (h->else_node == (struct ast_node *)0)
		{
			// label for end of if code
			int if_end = gen_label();
			i = generate_code(h->condition, match_statement_end, 0);
			ptr = i;
			while (ptr->next != (struct ir_instruction *)0)
			{
				ptr = ptr->next;
			}
			ptr->next = alloc_instruction();
			ptr = ptr->next;
			ptr->opcode = JMP_t;
			ptr->sub_opcode.JMP_t_opcode = JMP_BRF;
			ptr->jmp_target = if_end;
			ptr->next = generate_code(h->down, match_statement_end, 0);
			while (ptr->next != (struct ir_instruction *)0)
			{
				ptr = ptr->next;
			}
			ptr->next = alloc_instruction();
			ptr = ptr->next;
			ptr->opcode = NOP;
			ptr->label = if_end;
		}
		// if has an else node
		else
		{
			// label for beginning of else code
			int l_else = gen_label();
			// label for end of else code
			int if_end = gen_label();
			i = generate_code(h->condition, match_statement_end, 0);
			ptr = i;
			while (ptr->next != (struct ir_instruction *)0)
			{
				ptr = ptr->next;
			}
			ptr->next = alloc_instruction();
			ptr = ptr->next;
			ptr->opcode = JMP_t;
			ptr->sub_opcode.JMP_t_opcode = JMP_BRF;
			ptr->jmp_target = l_else;
			ptr->next = generate_code(h->down, match_statement_end, 0);
			while (ptr->next != (struct ir_instruction *)0)
			{
				ptr = ptr->next;
			}
			// end of if at this point
			ptr->next = alloc_instruction();
			ptr = ptr->next;
			ptr->opcode = JMP_t;
			ptr->sub_opcode.JMP_t_opcode = JMP_JMP;
			ptr->jmp_target = if_end;
			// generate else code
			ptr->next = generate_code(h->else_node, match_statement_end, 0);
			ptr = ptr->next;
			ptr->label = l_else;
			while (ptr->next != (struct ir_instruction *)0)
			{
				ptr = ptr->next;
			}
			ptr->next = alloc_instruction();
			ptr = ptr->next;
			ptr->opcode = NOP;
			ptr->label = if_end;
			ptr->label = if_end;
		}
		ptr->next = generate_code(h->side, match_statement_end, 0);
		break;
	case SIGEN:
		i->opcode = CTRL_t;
		i->sub_opcode.PUSH_t_opcode = CONTROL_SIGEN;
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case SIGDIS:
		i->opcode = CTRL_t;
		i->sub_opcode.PUSH_t_opcode = CONTROL_SIGDIS;
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case WHILE:
		free(i);
		int while_start = gen_label();
		int while_end = gen_label();
		i = generate_code(h->condition, match_statement_end, 0);
		i->label = while_start;
		ptr = i;
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = alloc_instruction();
		ptr = ptr->next;
		ptr->opcode = JMP_t;
		ptr->sub_opcode.JMP_t_opcode = JMP_BRF;
		ptr->jmp_target = while_end;
		ptr->next = generate_code(h->down, match_statement_end, 0);
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = alloc_instruction();
		ptr = ptr->next;
		ptr->opcode = JMP_t;
		ptr->sub_opcode.JMP_t_opcode = JMP_JMP;
		ptr->jmp_target = while_start;
		ptr->next = alloc_instruction();
		ptr = ptr->next;
		ptr->opcode = NOP;
		ptr->label = while_end;
		ptr->next = generate_code(h->side, match_statement_end, 0);
		break;
	case MATCH_SOURCE:
		free(i);
		int true_match_end = gen_label();
		i = generate_code(h->down, true_match_end, 0);
		ptr = i;
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = generate_code(h->side, match_statement_end, 0);
		// in case there's no more code
		if (ptr->next == (struct ir_instruction *)0)
		{
			ptr->next = alloc_instruction();
			ptr = ptr->next;
			ptr->opcode = NOP;
			ptr->label = true_match_end;
		}
		else
		{
			ptr = ptr->next;
			ptr->label = true_match_end;
		}
		break;
	case MATCH_CASE_IDENTIFIER:
	{
		int match_end = gen_label();
		i->opcode = REF_t;
		i->sub_opcode.REF_t_opcode = REF_MATCH_SOURCE;
		i->identifier = (char *)malloc(strlen(h->name) + 1);
		strcpy(i->identifier, h->name);
		i->jmp_target = match_end;
		i->next = generate_code(h->down, match_statement_end, 0);
		ptr = i;
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = alloc_instruction();
		ptr = ptr->next;
		ptr->opcode = JMP_t;
		ptr->sub_opcode.JMP_t_opcode = JMP_JMP;
		ptr->jmp_target = match_statement_end;

		ptr->next = generate_code(h->side, match_statement_end, 0);
		// in case there's no more code
		if (ptr->next == (struct ir_instruction *)0)
		{
			ptr->next = alloc_instruction();
			ptr = ptr->next;
			ptr->opcode = NOP;
			ptr->label = match_end;
		}
		else
		{
			ptr = ptr->next;
			ptr->label = match_end;
		}
		break;
	}
	case TRIGGER:
		i->opcode = REF_t;
		i->sub_opcode.REF_t_opcode = REF_TRIGGER;
		i->identifier = (char *)malloc(strlen(h->name) + 1);
		strcpy(i->identifier, h->name);
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case STREAM_PUSH:
		free(i);
		i = generate_code(h->down, match_statement_end, 0);
		ptr = i;
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = alloc_instruction();
		ptr = ptr->next;
		ptr->opcode = REF_t;
		ptr->sub_opcode.REF_t_opcode = REF_S_COMMIT;
		ptr->stream = (char *)malloc(strlen(h->port_name) + 1);
		strcpy(ptr->stream, h->port_name);
		ptr->core = (char *)malloc(strlen(h->name) + 1);
		strcpy(ptr->core, h->name);
		ptr->next = generate_code(h->side, match_statement_end, 0);
		break;
	case STREAM_CALL_ARG:
		free(i);
		i = generate_code(h->down, match_statement_end, 0);
		ptr = i;
		// special case for NOP (generated from null arg)
		if (ptr->opcode == NOP)
		{
			// do nothing
		}
		// here, we're passing an argument
		else
		{
			while (ptr->next != (struct ir_instruction *)0)
			{
				ptr = ptr->next;
			}
			ptr->next = alloc_instruction();
			ptr = ptr->next;
			ptr->opcode = REF_t;
			ptr->sub_opcode.REF_t_opcode = REF_S_PUSH;

			ptr->stream = (char *)malloc(strlen(h->port_name) + 1);
			strcpy(ptr->stream, h->port_name);
			ptr->core = (char *)malloc(strlen(h->core_name) + 1);
			strcpy(ptr->core, h->core_name);

			// ptr->identifier must be name of specific argument in stream
			ptr->identifier = strdup(get_stream_inarg_name_by_index(ptr->core, ptr->stream, stream_call_index));

			ptr->next = generate_code(h->side, match_statement_end, stream_call_index + 1);
		}
		break;
	case AST_NULL:
		i->opcode = NOP;
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case AST_NOP:
		i->opcode = NOP;
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case HALT:
		i->opcode = CTRL_t;
		i->sub_opcode.CONTROL_t_opcode = CONTROL_HALT;
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case CATCH_FIRE:
		i->opcode = CTRL_t;
		i->sub_opcode.CONTROL_t_opcode = CONTROL_FIRE;
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case PRINT:
		i->opcode = CTRL_t;
		i->sub_opcode.CONTROL_t_opcode = CONTROL_PRINT;
		i->constant = h->value;
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case PRINT_IDENTIFIER:
		i->opcode = CTRL_t;
		i->sub_opcode.CONTROL_t_opcode = CONTROL_PRINT_IDENTIFIER;
		i->identifier = (char *)malloc(strlen(h->name) + 1);
		strcpy(i->identifier, h->name);
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case PRINT_STRING:
		i->opcode = CTRL_t;
		i->sub_opcode.CONTROL_t_opcode = CONTROL_PRINT_STRING;
		i->identifier = (char *)malloc(strlen(h->name) + 1);
		strcpy(i->identifier, h->name);
		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	case STREAM_PULL:
		free(i);
		i = generate_code(h->down, match_statement_end, 0);
		ptr = i;
		while (ptr->next != (struct ir_instruction *)0)
		{
			ptr = ptr->next;
		}
		ptr->next = alloc_instruction();
		ptr = ptr->next;
		ptr->opcode = REF_t;
		ptr->sub_opcode.REF_t_opcode = REF_S_SINK;
		ptr->stream = (char *)malloc(strlen(h->port_name) + 1);
		strcpy(ptr->stream, h->port_name);
		ptr->core = (char *)malloc(strlen(h->name) + 1);
		strcpy(ptr->core, h->name);
		ptr->next = generate_code(h->side, match_statement_end, 0);
		break;
	case STREAM_PULL_ARG:

		i->opcode = REF_t;
		i->sub_opcode.REF_t_opcode = REF_S_PULL;

		i->stream = (char *)malloc(strlen(h->port_name) + 1);
		strcpy(i->stream, h->port_name);
		i->core = (char *)malloc(strlen(h->core_name) + 1);
		strcpy(i->core, h->core_name);

		// ptr->identifier must be name of specific argument in stream
		i->identifier = strdup((h->down)->name);

		i->next = generate_code(h->side, match_statement_end, 0);
		break;
	default:
		// errors++;
		printf("Error: found unknown ast node type during code generation.\n");
		return (struct ir_instruction *)0;
		break;
	}

	return i;
}

enum ALU_T_opcode_type get_ALU_opcode(enum operator_type o)
{
	switch (o)
	{
	case PLUS:
		return ALU_ADD;
	case TIMES:
		return ALU_MUL;
	case MINUS:
		return ALU_SUB;
	case DIVIDE:
		return ALU_DIV;
	case AND:
		return ALU_AND;
	case OR:
		return ALU_OR;
	case LESS:
		return ALU_LT;
	case LESSEQUAL:
		return ALU_LEQ;
	case GREATER:
		return ALU_GT;
	case GREATEREQUAL:
		return ALU_GEQ;
	case EQUALS:
		return ALU_EQ;
	case NOTEQUALS:
		return ALU_NEQ;
	default:
		return ALU_ADD;
	}
}

int gen_label()
{
	static int label = 0;
	label++;
	if (label == 0)
	{
		errors++;
		printf("Error: max number of labels in code exceeded.\n");
	}
	return label;
}

void free_instruction(struct ir_instruction *ins)
{
	if (ins != NULL)
	{
		free(ins->identifier);
		free(ins->stream);
		free(ins->core);
	}
}