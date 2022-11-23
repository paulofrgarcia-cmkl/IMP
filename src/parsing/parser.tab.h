/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_PARSING_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSING_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    t_IDENTIFIER = 258,
    t_VALUE = 259,
    t_CORE = 260,
    t_MAIN = 261,
    t_SIGNAL = 262,
    t_SOURCE = 263,
    t_MATCH = 264,
    t_SIGEN = 265,
    t_SIGDIS = 266,
    t_LB = 267,
    t_RB = 268,
    t_SC = 269,
    t_COLON = 270,
    t_I32 = 271,
    t_ASSIGNMENT = 272,
    t_IF = 273,
    t_ELSE = 274,
    t_WHILE = 275,
    t_LPAR = 276,
    t_RPAR = 277,
    t_STREAM = 278,
    t_PIPELINE = 279,
    t_EXPOSE = 280,
    t_SHUNT = 281,
    t_NULL = 282,
    t_LINKS = 283,
    t_COMMA = 284,
    t_PERIOD = 285,
    t_PLUS = 286,
    t_TIMES = 287,
    t_MINUS = 288,
    t_DIVIDE = 289,
    t_AND = 290,
    t_OR = 291,
    t_LESS = 292,
    t_LESSEQUAL = 293,
    t_GREATER = 294,
    t_GREATEREQUAL = 295,
    t_EQUALS = 296,
    t_NOTEQUALS = 297,
    t_TRIGGER = 298,
    t_NOP = 299,
    t_PRINT = 300,
    t_PRINTSTRING = 301,
    t_HALT = 302,
    t_FIRE = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "src/parsing/parser.y" /* yacc.c:1909  */

        char *var;
        int val;
        struct ast_node *node;
        int op_type;

#line 110 "src/parsing/parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSING_PARSER_TAB_H_INCLUDED  */
