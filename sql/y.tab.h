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
     CHAR = 263,
     CREATE = 264,
     DROP = 265,
     TABLE = 266,
     INDEX = 267,
     HELP = 268,
     VALUES = 269,
     INSERT = 270,
     DELET = 271,
     UPDATE = 272,
     AND = 273,
     XOR = 274,
     OR = 275,
     EQ = 276,
     NE = 277,
     LT = 278,
     LE = 279,
     GT = 280,
     GE = 281,
     SELECT = 282,
     FROM = 283,
     WHERE = 284
   };
#endif
/* Tokens.  */
#define WORD 258
#define LITERAL 259
#define INT 260
#define FLOAT 261
#define NONE 262
#define CHAR 263
#define CREATE 264
#define DROP 265
#define TABLE 266
#define INDEX 267
#define HELP 268
#define VALUES 269
#define INSERT 270
#define DELET 271
#define UPDATE 272
#define AND 273
#define XOR 274
#define OR 275
#define EQ 276
#define NE 277
#define LT 278
#define LE 279
#define GT 280
#define GE 281
#define SELECT 282
#define FROM 283
#define WHERE 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 1 "parser.y"
{
int ival;
float fval;
char *sval;
int subtok;
}
/* Line 1529 of yacc.c.  */
#line 114 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

