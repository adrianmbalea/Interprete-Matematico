#ifndef TS_H
#define TS_H

#include "../includes/definiciones.h"

/**
 * @brief Inicializa la TS con todas las palabras reservadas
 * 
 */
void inicializarTS();

/**
 * @brief Inserta un elemento en la TS, si no existe ya. En caso de que exista y sea una variable, modifica su valor
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
 * @brief Busca un componente a partir de su lexema
 * 
 * @param lexema lexema del componente a buscar 
 */
componente buscarComponente(char* lexema);

/**
 * @brief Libera la memoria de la TS
 * 
 */
void liberarTS();

/**
 * @brief Imprime el WS, esto es, las variables y su valor actual
 * 
 */
void imprimirWorkSpace();

/**
 * @brief Limpia (elimina) el workspace
 * 
 */
void clearWS();

#endif	/* TS_H */