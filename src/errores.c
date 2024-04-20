#include <stdio.h>
#include <stdlib.h>

#include "../includes/errores.h"

/**
 * @brief Permite imprimir el error indicando la linea
 * 
 * @param codigo Codigo del error
 * @param linea Linea en la que se produjo el error
 */
void imprimirError(int codigo, int linea){
    switch (codigo){
        case ERROR_ARCHIVO:
            printf("Error: Archivo no encontrado\n");
            break;

        case TAM_LEXEMA_EXCEDIDO:
            printf("Error: Tamano del lexema excedido en la linea %d\n", linea);
            break;

        case LEXEMA_MAL_FORMADO:
            printf("Error: Lexema mal formado en la linea %d\n", linea);
            break;

        case NUM_PARAMETROS_INCORRECTO:
            printf("Error: Numero de parametros incorrecto\n");
            printf("Se puede pasar como parametro un fichero para ejecutar, o ninguno para la linea de comandos\n");
            break;
        
        default:
            break;
        }
}