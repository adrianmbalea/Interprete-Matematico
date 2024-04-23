#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../includes/ts.h"
#include "../includes/abb.h"
#include "definiciones.h"
#include "../includes/sintactico.tab.h"

const componente palabrasReservadas[] = {
    {"echo",        CMD,        .valor.cmdptr=echo},
    {"quit",        CMD,        .valor.cmdptr=quit},
    {"workspace",   CMD,        .valor.cmdptr=workspace},
    {"clear",       CMD,        .valor.cmdptr=clear},
    {"help",        CMD,        .valor.cmdptr=help},
    {"load",        CMD,        .valor.cmdptr=load},
    {"ts",          CMD,        .valor.cmdptr=imprimirTS},

    {"sin",         FUNC,       .valor.funcptr=sin},
    {"cos",         FUNC,       .valor.funcptr=cos},
    {"tan",         FUNC,       .valor.funcptr=tan},
    {"asin",        FUNC,       .valor.funcptr=asin},
    {"acos",        FUNC,       .valor.funcptr=acos},
    {"atan",        FUNC,       .valor.funcptr=atan},
    {"pow",         FUNC,       .valor.funcptr=pow},
    {"sqrt",        FUNC,       .valor.funcptr=sqrt},
    {"cbrt",        FUNC,       .valor.funcptr=cbrt},
    {"log",         FUNC,       .valor.funcptr=log},
    {"log10",       FUNC,       .valor.funcptr=log10},
    {"log2",        FUNC,       .valor.funcptr=log2},
    {"round",       FUNC,       .valor.funcptr=round},
    {"floor",       FUNC,       .valor.funcptr=floor},
    {"ceil",        FUNC,       .valor.funcptr=ceil},
    {"fabs",        FUNC,       .valor.funcptr=fabs},
    {"exp",         FUNC,       .valor.funcptr=exp},
    {"exp2",        FUNC,       .valor.funcptr=exp2},

    {"pi",          CONST,      .valor.var=3.141592653589},
    {"e",           CONST,      .valor.var=2.718281828459}
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
 * @brief Inserta un elemento en la TS, si no existe ya. En caso de que exista y sea una variable, modifica su valor
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
 * @brief Busca un componente a partir de su lexema
 * 
 * @param lexema lexema del componente a buscar 
 */
componente buscarComponente(char* lexema){
    componente c;
    c.lexema=NULL;
    c.compLex=-2;
    buscarNodoAbb(ts, lexema, &c);
    return c;
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

/**
 * @brief Imprime el WS, esto es, las variables y su valor actual
 * 
 */
void imprimirWorkSpace(){
    printf("-------------------- WORKSPACE --------------------\n");
    imprimirCompLex(ts, VAR);
    printf("---------------------------------------------------\n");
}

/**
 * @brief Limpia (elimina) el workspace
 * 
 */
void clearWS(){
    while(1){
        char* variable = NULL;
        buscarVariable(ts, &variable);
        if(variable==NULL) return;
        suprimirElementoAbb(&ts, variable);
    }
}