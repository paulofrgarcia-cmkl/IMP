#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ast.h>
#include <arch.h>
#include <code_printer.h>
#include <code_gen.h>

char *var_type_string[] = {"I32"};

char *var_status_string[] = {"arg_in", "arg_out", "local", "global"};

char *alu_ops_strings[] = {"add", "sub", "mul", "div", "and", "or", "lt", "leq", "gt", "geq", "eq", "neq"};

extern int errors;
// TODO: print scope (function name) if possible
void print_instruction(FILE *fp, struct ir_instruction *code)
{
	if (code != (struct ir_instruction *)0)
	{
		if (code->label != 0)
			fprintf(fp, "\t\t%2d:\t", code->label);
		else
			fprintf(fp, "\t\t  :\t");

		switch (code->opcode)
		{
		case PUSH_t:
			switch (code->sub_opcode.PUSH_t_opcode)
			{
			case PUSH_I32_IDENTIFIER:
				fprintf(fp, "push %s\n", code->identifier);
				break;
			case PUSH_I32_CONST:
				fprintf(fp, "push %d\n", code->constant);
				break;
			}
			break;
		case POP_t:
			fprintf(fp, "pop %s\n", code->identifier);
			break;
		case JMP_t:
			switch (code->sub_opcode.JMP_t_opcode)
			{
			case JMP_JMP:
				fprintf(fp, "jmp @%d\n", code->jmp_target);
				break;
			case JMP_BRT:
				fprintf(fp, "brt @%d\n", code->jmp_target);
				break;
			case JMP_BRF:
				fprintf(fp, "brf @%d\n", code->jmp_target);
				break;
			}
			break;
		case CTRL_t:
			switch (code->sub_opcode.CONTROL_t_opcode)
			{
			case CONTROL_SIGEN:
				fprintf(fp, "sigen\n");
				break;
			case CONTROL_SIGDIS:
				fprintf(fp, "sigdis\n");
				break;
			case CONTROL_PRINT:
				fprintf(fp, "print %d\n", code->constant);
				break;
			case CONTROL_PRINT_STRING:
				fprintf(fp, "print %s\n", code->identifier);
				break;
			case CONTROL_HALT:
				fprintf(fp, "halt\n");
				break;
			case CONTROL_FIRE:
				fprintf(fp, "???\n");
				break;
			}
			break;
		case ALU_t:
			fprintf(fp, "%s\n", alu_ops_strings[code->sub_opcode.ALU_t_opcode]);
			break;
		case NOP:
			fprintf(fp, "nop\n");
			break;
		case REF_t:
			switch (code->sub_opcode.REF_t_opcode)
			{
			case REF_MATCH_SOURCE:
				fprintf(fp, "match %s, @%d\n", code->identifier, code->jmp_target);
				break;
			case REF_TRIGGER:
				fprintf(fp, "trigger %s\n", code->identifier);
				break;
			case REF_S_COMMIT:
				fprintf(fp, "s_commit %s, %s\n", code->stream, code->core);
				break;
			case REF_S_PUSH:
				fprintf(fp, "s_push %s, %s, %s\n", code->identifier, code->stream, code->core);
				break;
			case REF_S_SINK:
				fprintf(fp, "s_sink %s, %s\n", code->stream, code->core);
				break;
			case REF_S_PULL:
				fprintf(fp, "s_pull %s, %s, %s\n", code->identifier, code->stream, code->core);
				break;
			}
			break;
		default:
			errors++;
			printf("Error: unknown opcode found during code printing.\n");
			break;
		}
	}
}

void print_function_code(FILE *fp, struct ir_instruction *code)
{

	while (code != (struct ir_instruction *)0)
	{
		print_instruction(fp, code);
		code = code->next;
	}
}

void print_core_code(FILE *fp, struct arch_core *c)
{

	fprintf(fp, "//Core %s:\n", c->name);

	// print core global variables
	struct arch_symbol *symbols = c->g_symbols;
	while (symbols != (struct arch_symbol *)0)
	{
		fprintf(fp, "\t%s: %s @%d (%s)\n", var_type_string[symbols->type], symbols->name, symbols->index, var_status_string[symbols->status]);

		symbols = symbols->next;
	}

	fprintf(fp, "\t//function \"main\":\n");

	struct arch_function *my_function = c->main_function;

	if (my_function != (struct arch_function *)0)
	{
		struct arch_symbol *symbols = my_function->symbols;

		while (symbols != (struct arch_symbol *)0)
		{
			fprintf(fp, "\t\t%s: %s @%d (%s)\n", var_type_string[symbols->type], symbols->name, symbols->index, var_status_string[symbols->status]);
			symbols = symbols->next;
		}

		struct ir_instruction *code = my_function->code;
		print_function_code(fp, code);
	}

	fprintf(fp, "\t//function \"signal\":\n");

	my_function = c->signal_function;

	if (my_function != (struct arch_function *)0)
	{
		struct arch_symbol *symbols = my_function->symbols;
		while (symbols != (struct arch_symbol *)0)
		{
			fprintf(fp, "\t\t%s: %s @%d (%s)\n", var_type_string[symbols->type], symbols->name, symbols->index, var_status_string[symbols->status]);

			symbols = symbols->next;
		}
		struct ir_instruction *code = my_function->code;
		print_function_code(fp, code);
	}
	fprintf(fp, "\n\n");

	// print all core streams

	my_function = c->stream_functions;

	while (my_function != (struct arch_function *)0)
	{
		fprintf(fp, "\t//stream function \"%s->%s\":\n", my_function->in_name, my_function->out_name);
		struct arch_symbol *symbols = my_function->symbols;
		while (symbols != (struct arch_symbol *)0)
		{
			fprintf(fp, "\t\t%s: %s @%d (%s)\n", var_type_string[symbols->type], symbols->name, symbols->index, var_status_string[symbols->status]);
			symbols = symbols->next;
		}
		struct ir_instruction *code = my_function->code;
		print_function_code(fp, code);
		my_function = my_function->next;
	}
}

void print_code(struct arch *a)
{
	FILE *fp;
	fp = fopen("structures/code.out", "w");

	struct arch_core *c = a->arch_cores;
	// print graph

	while (c != (struct arch_core *)0)
	{
		print_core_code(fp, c);
		c = c->next;
	}

	fclose(fp);
}