#!/bin/bash

lex scan.l
rm y.tab.c 
yacc -dy parser.ypp

g++ -g -O1 -w lex.yy.c  y.tab.c sql_node.cpp -ll -ly
