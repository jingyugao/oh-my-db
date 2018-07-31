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
     CHAR = 259,
     LITERAL = 260,
     INT = 261,
     FLOAT = 262,
     NONE = 263,
     CREATE = 264,
     DROP = 265,
     TABLE = 266,
     INDEX = 267,
     HELP = 268,
     VALUES = 269,
     INSERT = 270,
     DELET = 271,
     UPDATE = 272,
     INTO = 273,
     AND = 274,
     XOR = 275,
     OR = 276,
     NOT = 277,
     EQ = 278,
     NE = 279,
     LT = 280,
     LE = 281,
     GT = 282,
     GE = 283,
     SELECT = 284,
     FROM = 285,
     WHERE = 286
   };
#endif
/* Tokens.  */
#define WORD 258
#define CHAR 259
#define LITERAL 260
#define INT 261
#define FLOAT 262
#define NONE 263
#define CREATE 264
#define DROP 265
#define TABLE 266
#define INDEX 267
#define HELP 268
#define VALUES 269
#define INSERT 270
#define DELET 271
#define UPDATE 272
#define INTO 273
#define AND 274
#define XOR 275
#define OR 276
#define NOT 277
#define EQ 278
#define NE 279
#define LT 280
#define LE 281
#define GT 282
#define GE 283
#define SELECT 284
#define FROM 285
#define WHERE 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "parser.y"
{
int ival;
float fval;
char *sval;
int subtok;
}
/* Line 1529 of yacc.c.  */
#line 118 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

