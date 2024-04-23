#include <stdio.h>
#include <stdlib.h>

#include "../includes/errores.h"

/**
 * @brief Permite imprimir el error
 * 
 * @param codigo Codigo del error
 */
void imprimirError(int codigo){
    switch (codigo)
    {
    case ERROR_ARCHIVO:
        printf("Error: al cargar el archivo\n");
        break;

    case LEXEMA_MAL_FORMADO:
        printf("Error: Lexema mal formado\n");
        break;

    case NUM_PARAMETROS_INCORRECTO:
        printf("Error: Numero de parametros incorrecto\n");
        break;

    case PARAMETROS_INCORRECTOS_FUNC:
        printf("Error: Los parametros no son los adecuados para esta funcion\n");
        break;

    case VARIABLE_NO_DEFINIDA:
        printf("Error: Variable no definida\n");
        break;

    case SYNTAX_ERROR:
        printf("Error sintactico\n");
        break;

    case NAN_DETECTADO:
        printf("Error: NaN detectado\n");
        break;

    case ASIGNACION_NO_VARIABLE:
        printf("Error: No se le puede asignar un valor a este tipo de dato\n");
        break;
    
    default:
        break;
    }
}