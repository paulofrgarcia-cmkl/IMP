#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "ast.h"

/********************************************************************************


		IR instructions

		We're keeping to stack-based processing, just because it makes code
		generation really simple - can optimize to 3-address code later

		(at this point, we're keeping everything as i32: have to support variable
		data sizes later, implying different versions of each instruction)

		Let's use one opcode for each type, then a subfield for the specific one
		(just because it will keep interpreter code neater later on)


		Push-type instructions
		-	Push variable	(PUSH <identifier>)
		-	Push constant	(PUSH <value>)

		Pop-type instructions
		-	Pop variable 	(POP <identifier>)

		Jmp-type instructions
		-	Unconditional jump	(JMP <label>)
		-	Branch if true		(BRT <label>)	;pops stack: jumps if != 0
		-	Branch if false		(BRF <label>)	;pops stack: jumps if == 0

		ALU-type instructions
		-	Addition		(ADD) 	; pops two values from stack, adds, pushes result
									; all other arithmetic ops do the same
		-	Subtraction		(SUB)
		-	Multiplication	(MUL)
		-	Division		(DIV)
		-	Logical AND 	(AND)
		-	Logical OR 		(OR)
		-	Less than		(LT)
		-	Less or equal	(LEQ)
		-	Greater	than	(GT)
		-	Greater or equal(GEQ)
		-	Equal			(EQ)
		-	Not equal		(NEQ)

		Control-type instructions
		-	Enables interrupts	(SIGEN)
		-	Disables interrupts	(SIGDIS)

		Do nothing instruction
		-	Does nothing (NOP) ; very useful for code generation

		Referencial instructions: (reference other cores/functions)
		-	Matches signal source 	(MATCH <identifier>, <label>)
					; generated from MATCH SOURCE high level statement: can only be used
					; in a "signal" function (ISR)
					; checks whether <identifier> (module name) is in the list of source modules
					; that triggered this interrupt
					; if yes, execution continues to run code
					; if not, branches to <label> to either test for next one,
					; or exit match statement
		-	Triggers core's signal (TRIGGER <identifier>)
					; sends an interrupt signal to core <identifier>
					; if signals are enabled in core <identifier>, core will suspend
					; all its functions and execute signal function
					; even if signals are not enabled, trigger is latched
					; so will eventually trigger signal when signals are enabled
					; triggering an already triggered signal has no effect
		-	Sends value to an input stream (S_PUSH <arg name>, <stream name>, <core name>)
					; Sends value from the top of the stack (popping it)
					; to the argument <arg name> of the input stream <stream name> of core <core name>
		-	Triggers input stream to consume arguments (S_COMMIT <stream name>, <core name>)
					; the idea of separating argument push and argument consumption
					; is to ensure we can push a variable number of arguments per call
					; pattern will be:
					; if stream is "read(i32 a, i32 b)" in "core0"
					;	called as "read(7,8)"
					;		push 7
					;		s_push a, read, core0
					;		push 8
					;		s_push b, read, core0
					;		s_commit read, core0
					;	instead, if called as "read(null,8)"
					;		push 8
					;		s_push b, read, core0
					;		s_commit read, core0
		-	Pulls value from an output stream (S_PULL <arg name>, <stream name>, <core name>)
					; Leaving value on top of stack
		-	Triggers output stream to delete queue entry (S_SINK <stream name>, <core name>)


		TO-DO
		-	Function call 		TODO
		-	Stream call			TODO
		-	Pipeline (dynamic data structures)	TODO
		-	Match (pattern match)	TODO (done for signal sources, but useful for variables as well)



********************************************************************************/

// instruction families
enum ir_opcode_type
{
	PUSH_t,
	POP_t,
	JMP_t,
	ALU_t,
	CTRL_t,
	NOP,
	REF_t
};

// Push instruction types
enum PUSH_t_opcode_type
{
	PUSH_I32_IDENTIFIER,
	PUSH_I32_CONST
};

// Pop instruction types
enum POP_T_opcode_type
{
	POP_I32_IDENTIFIER
};

// Jump type instructions
enum JMP_T_opcode_type
{
	JMP_JMP,
	JMP_BRT,
	JMP_BRF
};

// ALU type instructions
enum ALU_T_opcode_type
{
	ALU_ADD,
	ALU_SUB,
	ALU_MUL,
	ALU_DIV,
	ALU_AND,
	ALU_OR,
	ALU_LT,
	ALU_LEQ,
	ALU_GT,
	ALU_GEQ,
	ALU_EQ,
	ALU_NEQ
};

// Control type instructions
enum CONTROL_T_opcode_type
{
	CONTROL_SIGEN,
	CONTROL_SIGDIS,
	CONTROL_PRINT,
	CONTROL_PRINT_STRING,
	CONTROL_PRINT_IDENTIFIER,
	CONTROL_HALT,
	CONTROL_FIRE
};

// Referencial type instructions
enum REF_T_opcode_type
{
	REF_MATCH_SOURCE,
	REF_TRIGGER,
	REF_S_PUSH,
	REF_S_COMMIT,
	REF_S_PULL,
	REF_S_SINK
};

struct ir_instruction
{
	// address of instruction in memory
	int address;

	// used for jmp/branch destination. Can probably be resolved into proper address prior to evaluation
	int label;

	// opcode: determines which instruction family
	enum ir_opcode_type opcode;

	// sub_opcode determines type of instruction in family
	// when we add more data types, distinguishing between, e.g., Push i32 and i16 is done here
	union
	{
		enum PUSH_t_opcode_type PUSH_t_opcode;
		enum POP_T_opcode_type POP_t_opcode;
		enum JMP_T_opcode_type JMP_t_opcode;
		enum ALU_T_opcode_type ALU_t_opcode;
		enum CONTROL_T_opcode_type CONTROL_t_opcode;
		enum REF_T_opcode_type REF_t_opcode;
	} sub_opcode;

	// instruction fields
	char *identifier;
	int jmp_target; // corresponding to a label
	int constant;

	// for stream push instructions, need to keep track of more identifiers
	//"identifier" above is used for argument
	char *stream;
	char *core;

	struct ir_instruction *next;
};

struct ir_instruction *generate_code(struct ast_node *h, int match_statement_end, int stream_call_index);

enum ALU_T_opcode_type get_ALU_opcode(enum operator_type o);

int gen_label();

void free_instruction(struct ir_instruction *ins);

#endif