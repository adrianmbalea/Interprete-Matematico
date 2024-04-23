#include <stdio.h>
#include <stdlib.h>
#include "../includes/ts.h"
#include "../includes/errores.h"
#include "../includes/sintactico.tab.h"
#include "../includes/lex.yy.h"
#include "../includes/comandos.h"

int main(int argc, char **argv){
    char* nombreArchivo=NULL;
    if(argc==2){
        nombreArchivo=*(argv+1);
    } else if(argc>2){
        imprimirError(NUM_PARAMETROS_INCORRECTO);
        exit(EXIT_FAILURE);
    }

    // Mostramos la ayuda del interprete
    help();

    inicializarTS();

    /* Si no se ha pasado ningun nombre de archivo,
    entonces abrirArchivo() establecerá el yyin a stdin*/
    abrirArchivo(nombreArchivo);
    
    // Analisis sintactico
    yyparse();
    
    // Salimos del programa correctamente en caso de algun error inesperado
    quit();

    exit(EXIT_SUCCESS);
    
}