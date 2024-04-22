#include <stdio.h>
#include <stdlib.h>
#include "../includes/ts.h"
#include "../includes/errores.h"
#include "../includes/sintactico.tab.h"
#include "../includes/lex.yy.h"

int main(int argc, char **argv){
    char* nombreArchivo=NULL;
    if(argc==2){
        nombreArchivo=*(argv+1);
    } else if(argc>2){
        imprimirError(NUM_PARAMETROS_INCORRECTO);
        exit(EXIT_FAILURE);
    }

    abrirArchivo(nombreArchivo);

    inicializarTS();
    imprimirTS();

    //iniciarSintactico();
    yyparse();

    imprimirTS();
    
    liberarTS();

    cerrarArchivo();

    exit(EXIT_SUCCESS);
    
}