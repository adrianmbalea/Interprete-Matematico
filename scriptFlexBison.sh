#!/bin/bash
flex --outfile="./src/lex.yy.c" src/lexico.l
bison -d -Wconflicts-sr src/sintactico.y --output=./src/sintactico.tab.c --header=./includes/sintactico.tab.h