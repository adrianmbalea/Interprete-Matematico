#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "../includes/definiciones.h"
#include "../includes/lex.yy.h"
#include "../includes/sintactico.tab.h"
#include "../includes/comandos.h"
#include "../includes/errores.h"
#include "../includes/ts.h"

/**
 * @brief Permite imprimir o no los resultados de las próximas expresiones 
 * 
 * @param valor Valor que indica si se imprimen o no, puede ser "on" u "off"
 */
void echo(char* valor){
    if(!strcasecmp(valor, "\"on\"") || !strcasecmp(valor, "\'on\'")){
        imprimirResultados = 1;
    } else if(!strcasecmp(valor, "\"off\"") || !strcasecmp(valor, "\'off\'")){
        imprimirResultados = 0;
    } else {
        imprimirError(PARAMETROS_INCORRECTOS_FUNC);
    }
    return;
}

/**
 * @brief Permite salir del programa
 * 
 */
void quit(){
    liberarTS();
    cerrarArchivo();
    liberarLexico();
    exit(EXIT_SUCCESS);
}

/**
 * @brief Muestra el histórico de variables empleadas y sus respectivos valores
 * 
 */
void workspace(){
    printf("WORKSPACE:\n");
    imprimirWorkSpace();
}

/**
 * @brief Elimina todo el workspace actual
 * 
 */
void clear(){
    clearWS();
}

/**
 * @brief Muestra la ayuda
 * 
 */
void help() {
    printf("Bienvenido al intérprete matemático!\n\n");
    printf("El intérprete matemático es una herramienta diseñada para realizar cálculos\ny evaluaciones de expresiones matemáticas de forma interactiva. \nPermite a los usuarios ingresar expresiones matemáticas complejas y\nobtener resultados precisos de manera rápida y eficiente.\n");
    printf("\n");
    printf("Además de las expresiones y operadores esperados que \npueda soportar este intérprete, también puede ejecutar\nlas siguientes funciones matemáticas:\n");
    printf("- `sin()`, `cos()`, `tan()`, `asin()`, `acos()`, `atan()`, `pow()`,\n  `sqrt()`, `cbrt()`, `log()`, `log10()`, `log2()`, `round()`,\n  `floor()`, `ceil()`, `fabs()`, `exp()`, `exp2()`.\n");
    printf("\n");
    printf("A mayores, cuenta con las constantes `pi` y `e`.\n");
    printf("\n");
    printf("También cabe mencionar también la existencia de los siguientes comandos:\n");
    printf("- `echo(\"on\")`/`echo(\"off\")`: Permite imprimir o no los resultados de las próximas expresiones.\n");
    printf("- `quit()`: Permite salir del programa.\n");
    printf("- `workspace()`: Muestra el histórico de variables empleadas y sus respectivos valores.\n");
    printf("- `clear()`: Elimina todo el workspace actual.\n");
    printf("- `load(\"fichero\")`: Carga un fichero de código y lo ejecuta.\n");
    printf("- `help()`: Muestra la ayuda.\n\n\n");
}



/**
 * @brief Elimina las comillas (ya sean dobles o simples) de una cadena
 * 
 * @param cadena la cadena a eliminar las comillas
 */
void _eliminarComillas(char* cadena) {
    size_t longitud = strlen(cadena);

    if (longitud >= 2 && (cadena[0] == '\'' || cadena[0] == '"') && cadena[longitud - 1] == cadena[0]) {
        memmove(cadena, cadena + 1, longitud - 2);
        cadena[longitud - 2] = '\0';
    }
}

/**
 * @brief Carga un fichero de código y lo ejecuta
 * 
 * @param fichero fichero a ejecutar
 */
void load(char *fichero){
    _eliminarComillas(fichero);
    abrirArchivo(fichero);
}