%{
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "parser.tab.h"

extern int linenum ;

%}

alpha       [a-zA-Z_][a-zA-Z0-9_]*
value       ([0-9])+  
comment		"//".*

%%


{comment}		{}

"\n"			{linenum++;}

"+"		 		{return t_PLUS;}
"*" 			{return t_TIMES;}
"->"			{return t_LINKS;}
"-"				{return t_MINUS;}
"/"				{return t_DIVIDE;}
"&" 			{return t_AND;}
"|" 			{return t_OR;}
"<=" 			{return t_LESSEQUAL;}
"<"				{return t_LESS;}
">=" 			{return t_GREATEREQUAL;}
">" 			{return t_GREATER;}
"=="			{return t_EQUALS;}
"!=" 			{return t_NOTEQUALS;} 


"core"			{return t_CORE;}
"main"			{return t_MAIN;}
"signal"		{return t_SIGNAL;}
"source"		{return t_SOURCE;}
"match"			{return t_MATCH;}
"sigen"			{return t_SIGEN;}
"sigdis"		{return t_SIGDIS;}
"i32"			{return t_I32;}
"="				{return t_ASSIGNMENT;}
"if"			{return t_IF;}
"else"			{return t_ELSE;}
"while"			{return t_WHILE;}
"stream"		{return t_STREAM;}
"pipeline"		{return t_PIPELINE;}
"expose"		{return t_EXPOSE;}
"shunt"			{return t_SHUNT;}
"null"			{return t_NULL;}
"trigger"		{return t_TRIGGER;}
"nop"			{return t_NOP;}
"print"			{return t_PRINT;}
"prints"		{return t_PRINTSTRING;}
"halt"			{return t_HALT;}
"catchfire"		{return t_FIRE;}

","				{return t_COMMA;}

"{"				{return t_LB;}
"}"				{return t_RB;}
";"				{return t_SC;}
":"				{return t_COLON;}
"("				{return t_LPAR;}
")"				{return t_RPAR;}
"."				{return t_PERIOD;}


{value}         {
					yylval.val = atoi(yytext); 
					return t_VALUE;
				}
{alpha}         {
                	yylval.var = (char *)malloc(strlen(yytext)+1);
					strncpy(yylval.var, yytext, strlen(yytext));
					return t_IDENTIFIER;
				}

.				{/*ignore whitespace*/}

%%

int yywrap()
{
	return 1;
}