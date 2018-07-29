#!/bin/bash

lex scan.l
yacc -dy parser.y

gcc  -w lex.yy.c y.tab.c -ll -ly
