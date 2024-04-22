#ifndef ERRORES_H
#define ERRORES_H

#define ERROR_ARCHIVO               1
#define LEXEMA_MAL_FORMADO          2
#define NUM_PARAMETROS_INCORRECTO   3
#define PARAMETROS_INCORRECTOS_FUNC 4 // numero incorrecto o alguno de ellos es nan
#define VARIABLE_NO_DEFINIDA        5
#define SYNTAX_ERROR                6
#define NAN_DETECTADO               7
#define ASIGNACION_NO_VARIABLE      8

/**
 * @brief Permite imprimir el error
 * 
 * @param codigo Codigo del erro
 */
void imprimirError(int codigo);

#endif	/* ERRORES_H */