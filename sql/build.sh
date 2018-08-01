#!/bin/bash

lex scan.l
rm y.tab.c 
yacc -dy parser.y

gcc -g -O1 -w lex.yy.c  y.tab.c -ll -ly
