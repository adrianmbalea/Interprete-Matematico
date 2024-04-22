# Interprete-Matematico
Implementación en C de un intérprete de línea de comandos para expresiones matemáticas, usando las herramientas flex y bison.

Para compilar flex: flex --outfile="./src/lex.yy.c" src/lexico.l 
Para compilar bison: bison -d -Wconflicts-sr src/sintactico.y --output=./src/sintactico.tab.c --header=./includes/sintactico.tab.h