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
     SET = 265,
     DATABASE = 266,
     TABLE = 267,
     INDEX = 268,
     HELP = 269,
     VALUES = 270,
     INSERT = 271,
     DELETE = 272,
     PRIMARY = 273,
     T_INT = 274,
     T_FLOAT = 275,
     T_VARCHAR = 276,
     UPDATE = 277,
     INTO = 278,
     AND = 279,
     OR = 280,
     NOT = 281,
     EQ = 282,
     NE = 283,
     LT = 284,
     LE = 285,
     GT = 286,
     GE = 287,
     SELECT = 288,
     FROM = 289,
     WHERE = 290
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
#define SET 265
#define DATABASE 266
#define TABLE 267
#define INDEX 268
#define HELP 269
#define VALUES 270
#define INSERT 271
#define DELETE 272
#define PRIMARY 273
#define T_INT 274
#define T_FLOAT 275
#define T_VARCHAR 276
#define UPDATE 277
#define INTO 278
#define AND 279
#define OR 280
#define NOT 281
#define EQ 282
#define NE 283
#define LT 284
#define LE 285
#define GT 286
#define GE 287
#define SELECT 288
#define FROM 289
#define WHERE 290




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
#line 127 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

