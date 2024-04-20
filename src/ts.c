#include <stdlib.h>
#include <stdio.h>
#include "../includes/ts.h"
#include "../includes/abb.h"
#include "definiciones.h"

const componente palabrasReservadas[] = {
    {"echo",        FUNC,    .valor.cmdptr=echo},
    {"quit",        FUNC,    .valor.cmdptr=quit},
    {"workspace",   FUNC,    .valor.cmdptr=workspace},
    {"clear",       FUNC,    .valor.cmdptr=clear},
    {"help",        FUNC,    .valor.cmdptr=help},
    {"load",        FUNC,    .valor.cmdptr=load},
    {"pi",          CONST,    .valor.var=3.141592653589},
    {"e",           CONST,    .valor.var=2.718281828459},
};

/** Estructura para la tabla de simbolos => ABB **/
ABB ts;

/**
 * @brief Inicializa la TS con todas las palabras reservadas
 * 
 */
void inicializarTS(){
    int nPalabrasReservadas = sizeof(palabrasReservadas)/sizeof(palabrasReservadas[0]);
    for(int i=0; i<nPalabrasReservadas; i++){
        insertarLex(palabrasReservadas[i].lexema, palabrasReservadas[i].compLex, palabrasReservadas[i].valor);
    }
}

/**
 * @brief Libera la memoria de la TS
 * 
 */
void liberarTS(){
    destruirAbb(&ts);
}

/**
 * @brief Inserta un elemento en la TS, si no existe ya
 * 
 * @param lexema Lexema del elemento
 * @param compLex Componente lexico del elemento
 * @return int Componente lexico del elemento
 */
int insertarLex(char* lexema, int compLex, union Valor valor){
    if(compLex){
        return insertarElementoAbb(&ts, lexema, compLex, valor);
    } else{
        return -1;
    }
}

/**
 * @brief Elimina un elemento de la TS en caso de que exista
 * 
 * @param lexema Lexema del elemento a eliminar
 */
void eliminarLex(char* lexema){
    suprimirElementoAbb(&ts, lexema);
}

/**
 * @brief Comprueba si un identificador esta asociado a una funcion
 * 
 * @param id identificador a comprobar
 * @return int 1 si es una función, 0 en caso contrario
 */
int esFuncion(char* id){
    componente comp;
    buscarNodoAbb(ts, id, &comp);
    return comp.lexema!=NULL && comp.compLex==FUNC;
}

/**
 * @brief Imprime la TS siguiendo un recorrido inorden, lo cual implica que se impriman en orden alfabetico
 * 
 */
void imprimirTS(){
    printf("-------------------- TABLA DE SIMBOLOS --------------------\n");
    imprimirAbb(ts);
    printf("-----------------------------------------------------------\n");
}