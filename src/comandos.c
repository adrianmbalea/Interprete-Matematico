#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "../includes/definiciones.h"
#include "../includes/comandos.h"
#include "../includes/errores.h"

int imprimirResultados = 1;

/**
 * @brief Procesa los parametros de los diferentes comandos que puede haber
 * 
 * @param parametros parametro de entrada, es la cadena de caracteres en la que el usuario pasa los parametros separados por comas
 * @param argc parametro de salida, es el numero de parametros que hay
 * @param argv parametro de salida, es el array de parametros que el usuario ha pasado
 */
void _procesarParametros(char *parametros, int *argc, char ***argv) {
    // Contar el número de parámetros
    *argc = 0;
    char *copia = strdup(parametros);
    char *token = strtok(copia, ",");
    while (token != NULL) {
        (*argc)++;
        token = strtok(NULL, ",");
    }
    free(copia);

    *argv = (char**)malloc((*argc) * sizeof(char*));
    copia = strdup(parametros);
    int i = 0;
    token = strtok(copia, ",");
    while (token != NULL) {
        (*argv)[i] = strdup(token);
        i++;
        token = strtok(NULL, ",");
    }
    free(copia);
}

/**
 * @brief Libera la memoria de los parametros que pasa el usuario
 * 
 * @param argc numero de parametros
 * @param argv array de parametros
 */
void _liberarParametros(int argc, char ***argv) {
    for (int i = 0; i < argc; i++) {
        free((*argv)[i]);
    }

    free(*argv);
    *argv = NULL;
}

void echo(char* parametro){
    if(!strcasecmp(parametro, "on")){
        imprimirResultados=1;
    } else if(!strcasecmp(parametro, "off")){
        imprimirResultados=0;
    } else {
        imprimirError(PARAMETROS_INCORRECTOS_FUNC);
    }

    return;
}

void quit(char* parametros){
    int argc;
    char **argv;
    _procesarParametros(parametros, &argc, &argv);

    if(argc!=0){
        imprimirError(PARAMETROS_INCORRECTOS_FUNC);
        _liberarParametros(argc, &argv);
        return;
    }

    _liberarParametros(argc, &argv);
    // todo: liberar toda la memoria y salir del programa
}

void workspace(char* parametros){
    int argc;
    char **argv;
    _procesarParametros(parametros, &argc, &argv);

    if(argc!=0){
        imprimirError(PARAMETROS_INCORRECTOS_FUNC);
        _liberarParametros(argc, &argv);
        return;
    }

    // todo: imprimir workspace

    _liberarParametros(argc, &argv);
    return;
}

void clear(char* parametros){
    int argc;
    char **argv;
    _procesarParametros(parametros, &argc, &argv);

    if(argc!=0){
        imprimirError(PARAMETROS_INCORRECTOS_FUNC);
        _liberarParametros(argc, &argv);
        return;
    }

    // todo: borrar workspace

    _liberarParametros(argc, &argv);
    return;
}

void help(char* parametros){
    int argc;
    char **argv;
    _procesarParametros(parametros, &argc, &argv);

    if(argc!=0){
        imprimirError(PARAMETROS_INCORRECTOS_FUNC);
        _liberarParametros(argc, &argv);
        return;
    }

    // todo: imprimir ayuda

    _liberarParametros(argc, &argv);
    return;
}

void load(char* parametros){
    int argc;
    char **argv;
    _procesarParametros(parametros, &argc, &argv);

    if(argc!=0){
        imprimirError(PARAMETROS_INCORRECTOS_FUNC);
        _liberarParametros(argc, &argv);
        return;
    }

    // todo: cargar fichero

    _liberarParametros(argc, &argv);
    return;
}