/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WORD = 258,
     LITERAL = 259,
     INT = 260,
     FLOAT = 261,
     NONE = 262,
     CREATE = 263,
     DROP = 264,
     DATABASE = 265,
     TABLE = 266,
     INDEX = 267,
     HELP = 268,
     VALUES = 269,
     INSERT = 270,
     DELETE = 271,
     T_INT = 272,
     T_FLOAT = 273,
     T_VARCHAR = 274,
     UPDATE = 275,
     INTO = 276,
     AND = 277,
     OR = 278,
     NOT = 279,
     EQ = 280,
     NE = 281,
     LT = 282,
     LE = 283,
     GT = 284,
     GE = 285,
     SELECT = 286,
     FROM = 287,
     WHERE = 288
   };
#endif
/* Tokens.  */
#define WORD 258
#define LITERAL 259
#define INT 260
#define FLOAT 261
#define NONE 262
#define CREATE 263
#define DROP 264
#define DATABASE 265
#define TABLE 266
#define INDEX 267
#define HELP 268
#define VALUES 269
#define INSERT 270
#define DELETE 271
#define T_INT 272
#define T_FLOAT 273
#define T_VARCHAR 274
#define UPDATE 275
#define INTO 276
#define AND 277
#define OR 278
#define NOT 279
#define EQ 280
#define NE 281
#define LT 282
#define LE 283
#define GT 284
#define GE 285
#define SELECT 286
#define FROM 287
#define WHERE 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "parser.ypp"
{
int ival;
float fval;
char *sval;
SqlOp opval;
struct SqlNode* n;
}
/* Line 1529 of yacc.c.  */
#line 123 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

