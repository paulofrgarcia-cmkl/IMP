%{
#include <stdio.h>
#include "parser.tab.h"

#include <ast.h>

int yyerror(char *s);
int yylex();

//#define YYDEBUG 1


extern struct ast_node *ast_head;

int linenum = 1;
%}

// Symbols.
%union
{
        char *var;
        int val;
        struct ast_node *node;
        int op_type;
};


%token <var> t_IDENTIFIER
%token <val> t_VALUE

%token t_CORE
%token t_MAIN
%token t_SIGNAL
%token t_SOURCE
%token t_MATCH
%token t_SIGEN
%token t_SIGDIS
%token t_LB
%token t_RB
%token t_SC
%token t_COLON
%token t_I32
%token t_ASSIGNMENT
%token t_IF
%token t_ELSE
%token t_WHILE
%token t_LPAR
%token t_RPAR

%token t_STREAM
%token t_PIPELINE
%token t_EXPOSE
%token t_SHUNT
%token t_NULL
%token t_LINKS
%token t_COMMA
%token t_PERIOD

%token t_PLUS
%token t_TIMES
%token t_MINUS
%token t_DIVIDE
%token t_AND
%token t_OR
%token t_LESS
%token t_LESSEQUAL
%token t_GREATER
%token t_GREATEREQUAL
%token t_EQUALS
%token t_NOTEQUALS 
%token t_TRIGGER
%token t_NOP
%token t_PRINT
%token t_PRINTSTRING
%token t_HALT
%token t_FIRE



%start prog
%type <node> prog
%type <node> cores 
%type <node> core 
%type <node> core_body 
%type <node> core_construct 
%type <node>  construct_body
%type <node> statement
%type <node> match_statement
%type <node> match_body
%type <node> match_case
%type <node> var_decl
%type <node> var_assign
%type <node> expression
%type <node> if_statement
%type <node> stream_function
%type <node> func_header
%type <node> arg_list
%type <node> arg
%type <node> pipeline_statement
%type <node> pipeline_body
%type <node> pipeline_exp
%type <node> expose_stmt
%type <node> link_stmt
%type <node> while_statement
%type <node> terminal
%type <op_type> operator
%type <node> trigger_statement
%type <node> call_arg_list
%type <node> pull_arg_list
%type <node> stream_push
%type <node> stream_pull
%type <node> nop_statement
%type <node> print_statement
%type <node> print_string_statement
%type <node> halt_statement
%type <node> fire_statement

%%

prog: cores { ast_head = $$ = new_ast_program($1); } ;


cores: core {$$ = $1;} |  core cores { $1->side = $2; $$=$1; } ;

core: t_CORE t_IDENTIFIER t_LB core_body t_RB { $$ = new_ast_core($2,$4); } ;

core_body: core_construct { $$=$1; } | core_construct core_body { $1->side = $2; $$ = $1; } ;

core_construct: t_MAIN t_LB construct_body t_RB { $$=new_ast_main($3); }
              | t_SIGNAL t_LB construct_body t_RB { $$=new_ast_signal($3); }
              | var_decl {$$ = $1; } 
              | stream_function {$$ = $1;} ;

stream_function:  t_STREAM func_header t_LINKS func_header t_LB construct_body t_RB 
                  {
                    $$ = new_ast_stream($2->name,$4->name);
                    $$->down = $6;

                    $$->stream_in = $2;
                    $$->stream_out = $4;
                  } ;


func_header:  t_IDENTIFIER t_LPAR arg_list t_RPAR 
              { 
                $$=new_ast_func_header($1);
                $$->down = $3; 
              } ;

arg_list:  arg { $$=$1; }
         | arg t_COMMA arg_list { $1->side=$3; $$=$1; } ;


arg: t_I32 t_IDENTIFIER { $$=new_ast_i32var_decl($2); } ;


construct_body: statement { $$=$1; } 
              |  statement construct_body { $1->side=$2; $$=$1; } ;

statement:  t_SIGEN t_SC { $$=new_ast_sigen(); }
          | t_SIGDIS t_SC { $$=new_ast_sigdis(); }
          | match_statement { $$=$1; } 
          | var_decl { $$=$1; } 
          | var_assign { $$=$1; } 
          | if_statement { $$=$1; } 
          | pipeline_statement { $$=$1; } 
          | while_statement { $$=$1; } 
          | trigger_statement { $$=$1; } 
          | stream_push t_SC { $$=$1; }
          | nop_statement { $$=$1; } 
          | print_statement { $$=$1; }
          | print_string_statement { $$=$1; }
          | halt_statement { $$ = $1; } 
          | fire_statement { $$ = $1; } ;

print_statement: t_PRINT t_VALUE t_SC { $$=new_ast_print($2); }
                | t_PRINT t_IDENTIFIER t_SC { $$=new_ast_print_identifier($2); } ;

print_string_statement: t_PRINTSTRING t_IDENTIFIER t_SC { $$=new_ast_printstring($2); } ;

trigger_statement: t_TRIGGER t_IDENTIFIER t_SC { $$=new_ast_trigger($2); } ;

halt_statement: t_HALT t_SC { $$=new_ast_halt(); } ;

fire_statement: t_FIRE t_SC { $$=new_ast_fire(); } ;

nop_statement: t_NOP t_SC { $$=new_ast_nop(); } ;

if_statement: t_IF t_LPAR expression t_RPAR t_LB construct_body t_RB t_SC 
              { 
                $$ = new_ast_if((struct ast_node *)0); 
                $$->condition = $3;
                $$->down = $6; 
              }
          |   t_IF t_LPAR expression t_RPAR t_LB construct_body t_RB t_ELSE t_LB construct_body t_RB t_SC 
              {
                struct ast_node *tmp = new_ast_else($10);

                $$ = new_ast_if(tmp); 
                $$->condition = $3;
                $$->down = $6;
              } ;


while_statement: t_WHILE t_LPAR expression t_RPAR t_LB construct_body t_RB t_SC
                  {
                    $$ = new_ast_while(); 
                    $$->condition = $3;
                    $$->down = $6;
                  } ;

pipeline_statement: t_PIPELINE t_IDENTIFIER t_LB pipeline_body t_RB t_SC 
                    { 
                      $$=new_ast_pipeline($2);
                      $$->down = $4; 
                    } ;

pipeline_body:  pipeline_exp { $$=$1; } 
              | pipeline_exp pipeline_body { $1->side=$2; $$=$1; } ;


pipeline_exp: var_decl    { $$=$1; }
            | expose_stmt { $$=$1; }
            | link_stmt   { $$=$1; } ;

expose_stmt: t_EXPOSE t_IDENTIFIER t_PERIOD t_IDENTIFIER t_SC { $$ = new_ast_expose($2,$4); } ;


link_stmt: t_IDENTIFIER t_PERIOD t_IDENTIFIER t_LINKS t_IDENTIFIER t_PERIOD t_IDENTIFIER t_SC 
          {
            $$ = new_ast_link($1,$3);
            $$->link_port = new_ast_linkport($5,$7);
          } ;


match_statement: t_MATCH t_SOURCE t_LB match_body t_RB t_SC { $$=new_ast_match_source($4); } ;

match_body: match_case { $$=$1; } |  match_case match_body { $1->side=$2; $$=$1; } ;

match_case: t_IDENTIFIER t_COLON t_LB construct_body t_RB { $$=new_ast_match_case_identifier($1,$4); } ;

var_decl: t_I32 t_IDENTIFIER t_SC { $$=new_ast_i32var_decl($2); } ;

var_assign: t_IDENTIFIER t_ASSIGNMENT expression t_SC {$$ = new_ast_var_assign($1, $3); } ;


expression: terminal { $$ = $1; }
          | terminal operator expression 
          {  
            $$ = new_ast_expression($2);
            $$->left = $1;
            $$->right = $3;
          } ;

operator: t_PLUS    { $$ = PLUS;}
        | t_TIMES   { $$ = TIMES;}
        | t_MINUS   { $$ = MINUS;}
        | t_DIVIDE  { $$ = DIVIDE;}
        | t_AND     { $$ = AND;}
        | t_OR      { $$ = OR;}
        | t_LESS    { $$ = LESS;}
        | t_LESSEQUAL { $$ = LESSEQUAL;}
        | t_GREATER   { $$ = GREATER;}
        | t_GREATEREQUAL  { $$ = GREATEREQUAL;}
        | t_EQUALS    { $$ = EQUALS;}
        | t_NOTEQUALS { $$ = NOTEQUALS;} ;

terminal: t_VALUE { $$ = new_ast_const($1); }
        | t_IDENTIFIER { $$ = new_ast_identifier($1); } 
        | t_LPAR expression t_RPAR { $$=$2; } 
        | stream_pull { $$=$1; } ;



stream_push:  t_IDENTIFIER t_LPAR call_arg_list t_RPAR t_PERIOD t_IDENTIFIER 
              {
                $$ = new_ast_stream_push($1,$6);
                $$->down = $3;
                populate_stream_names($1,$6,$3);
              } ;


stream_pull:  t_IDENTIFIER t_PERIOD t_IDENTIFIER t_LPAR pull_arg_list t_RPAR  
              {
                $$ = new_ast_stream_pull($3,$1);
                $$->down = $5;
                populate_pull_stream_names($3,$1,$5);
              } ;

call_arg_list:  expression { $$=new_ast_call_arg();    $$->down=$1; }
              | t_NULL { $$=new_ast_call_arg();    $$->down=new_ast_null(); }
              | expression t_COMMA call_arg_list { $$=new_ast_call_arg(); $$->side=$3; $$->down=$1; }
              | t_NULL t_COMMA call_arg_list     { $$=new_ast_call_arg(); $$->side=$3; $$->down=new_ast_null();  } ; 


pull_arg_list:  t_IDENTIFIER { $$=new_ast_pull_arg();    $$->down=new_ast_identifier($1); }
              | t_IDENTIFIER t_COMMA call_arg_list    { $$=new_ast_pull_arg(); $$->side=$3; $$->down=new_ast_identifier($1);  } ; 



%%

int yyerror(char *s) 
{
  printf("yyerror : %s at line %d\n",s,linenum);
  return 0;
}


