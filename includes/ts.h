#ifndef TS_H
#define TS_H

#include "../includes/definiciones.h"

/**
 * @brief Inicializa la TS con todas las palabras reservadas
 * 
 */
void inicializarTS();

/**
 * @brief Inserta un elemento en la TS, si no existe ya
 * 
 * @param lexema Lexema del elemento
 * @param compLex Componente lexico del elemento
 * @return int Componente lexico del elemento
 */
int insertarLex(char* lexema, int compLex, union Valor valor);

/**
 * @brief Elimina un elemento de la TS en caso de que exista
 * 
 * @param lexema Lexema del elemento a eliminar
 */
void eliminarLex(char* lexema);

/**
 * @brief Imprime la TS siguiendo un recorrido inorden, lo cual implica que se impriman en orden alfabetico
 * 
 */
void imprimirTS();

/**
 * @brief Comprueba si un identificador esta asociado a una funcion
 * 
 * @param id identificador a comprobar
 * @return int 1 si es una función, 0 en caso contrario
 */
int esFuncion(char* id);

/**
 * @brief Libera la memoria de la TS
 * 
 */
void liberarTS();

#endif	/* TS_H */