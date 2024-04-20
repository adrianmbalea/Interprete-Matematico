#include <stdio.h>
#include <stdlib.h>
#include "../includes/ts.h"
#include "../includes/errores.h"
#include "../includes/sintactico.h"
#include "../includes/lex.yy.h"

int main(int argc, char **argv){
    char* nombreArchivo=NULL;
    if(argc==2){
        nombreArchivo=*(argv+1);
    } else if(argc>2){
        imprimirError(NUM_PARAMETROS_INCORRECTO, 1);
        return;
    }

    abrirArchivo(nombreArchivo);

    inicializarTS();
    imprimirTS();

    iniciarSintactico();

    imprimirTS();
    
    liberarTS();

    cerrarArchivo();

    exit(EXIT_SUCCESS);
    
}