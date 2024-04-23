# Interprete-Matematico
Implementación en C de un intérprete de línea de comandos para expresiones matemáticas, usando las herramientas `Flex` y `Bison`.

## Compilación

Para compilar este programa se proporciona un Makefile, por lo que basta con ejecutar el comando `make` en una terminal de Linux. Esto se debe a que los archivos `lexico.l` y `sintactico.y` ya han sido compilados con flex y bison, respectivamente. En caso de querer modificar o recompilar estos archivos, ejecutar `flex --outfile="./src/lex.yy.c" src/lexico.l`y `bison -d -Wconflicts-sr src/sintactico.y --output=./src/sintactico.tab.c --header=./includes/sintactico.tab.h`. 

Una vez compilado todo, obtendremos un archivo ejecutable a través del comando `./interpreteMatematico`. Este ejecutable permite también pasar como parámetro un archivo con algunas expresiones matemáticas, asignaciones y otros comandos, con el fin de precargarlos.

## Funciones matemáticas soportadas

Además de las expresiones y operadores esperados que pueda soportar este intérprete, también puede ejecutar las siguientes funciones matemáticas:

- `sin()`: Calcula el seno de un ángulo.
- `cos()`: Calcula el coseno de un ángulo.
- `tan()`: Calcula la tangente de un ángulo.
- `asin()`: Calcula el arcoseno de un valor.
- `acos()`: Calcula el arcocoseno de un valor.
- `atan()`: Calcula el arcotangente de un valor.
- `pow()`: Calcula la potencia de un número.
- `sqrt()`: Calcula la raíz cuadrada de un número.
- `cbrt()`: Calcula la raíz cúbica de un número.
- `log()`: Calcula el logaritmo natural de un número.
- `log10()`: Calcula el logaritmo en base 10 de un número.
- `log2()`: Calcula el logaritmo en base 2 de un número.
- `round()`: Redondea un número al entero más cercano.
- `floor()`: Redondea hacia abajo un número al entero más cercano.
- `ceil()`: Redondea hacia arriba un número al entero más cercano.
- `fabs()`: Devuelve el valor absoluto de un número.
- `exp()`: Calcula la función exponencial de un número.
- `exp2()`: Calcula 2 elevado a la potencia de un número.

A mayores, cuenta con las constantes `pi` y `e`.

## Comandos

Cabe mencionar también la existencia de los siguiente comandos:
- `echo("on")`/`echo("off")`: Permite imprimir o no los resultados de las próximas expresiones
- `quit()`: Permite salir del programa
- `workspace()`: Muestra el histórico de variables empleadas y sus respectivos valores
- `clear()`: Elimina todo el workspace actual
- `load("fichero")`: Carga un fichero de código y lo ejecuta
- `help()`: Muestra la ayuda