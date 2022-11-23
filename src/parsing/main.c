/**
 * @file main.c
 * @brief The main/runner file.
 *
 * @details Parse the provided input file and generate an AST. Generate a symbol
 * table from the parsed code, and perform semantic analysis. Traverse the AST
 * to generate a description of core architecture, and use this to generate
 * representations better suited to execution. Then, execute the program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.tab.h"

#include <arch.h>
#include <arch_printer.h>
#include <ast.h>
#include <ast_printer.h>
#include <code_printer.h>
#include <semantic_analysis.h>
#include <symbol_table.h>

#include <exec_core.h>
#include <interpreter.h>

extern FILE *yyin;
extern struct ast_node *ast_head;

struct arch *my_arch = (struct arch *)0;

int errors = 0;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Undefined input file. Usage: \"aslc <source file>\"\n");
		return 0;
	}
	yyin = fopen(argv[1], "r");
	if (yyin == NULL)
	{
		printf("Could not open input file %s\n", argv[1]);
		return 0;
	}

	// uncomment the following lines to debug parsing

	// extern int yydebug;
	// yydebug = 1;

	yyparse();
	printf("Parsing complete.\n");

	if (errors != 0)
		return 0;
	print_ast(ast_head);

	printf("AST printed.\n");

	// generate symbol table for later code generation
	int sym_errors = build_symbol_table(ast_head);
	print_symbol_table();
	printf("Symbol table built with %d errors\n", sym_errors);
	if (sym_errors > 0)
	{
		return EXIT_FAILURE;
	}

	// semantic analysis
	// verify that the AST makes sense and all rules are obeyed
	int sem_errors = check_semantics(ast_head, get_table());
	printf("Semantic analysis encountered %d errors\n", sem_errors);
	if (sem_errors > 0)
	{
		return EXIT_FAILURE;
	}

	// code generation
	// traverse the AST to generate architecture, cores description
	my_arch = generate_arch(ast_head);
	// and generate code for all functions in cores5

	if (errors != 0)
		return 0;

	printf("Architecture generated.\n");

	generate_arch_code(my_arch, ast_head);

	if (errors != 0)
		return 0;

	printf("Code generated.\n");

	int num_cores = count_cores(my_arch);
	printf("%d cores found\n", num_cores);

	print_arch(my_arch);

	if (errors != 0)
		return 0;

	print_code(my_arch);

	// Setup execution
	struct exec_core **run_cores = setup_cores(num_cores);
	assign_exec_core_functions(num_cores, run_cores, my_arch->arch_cores);

	// Begin code execution
	execute(num_cores, run_cores);

	printf("Cleaning up...\n");
	free_cores(run_cores, num_cores);
	free(run_cores);
}