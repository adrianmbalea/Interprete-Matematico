#ifndef ABB_H
#define ABB_H

#include "../includes/definiciones.h"

/**
 * Tipo de dato abstracto para arbol binario con clave de
 * ordenacion y elemento de celda.
 */

typedef struct celda * ABB;
		

//FUNCIONES DE CREACIÓN Y DESTRUCCIÓN DEL ARBOL
/**
 * Crea el arbol vacio.
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void crearAbb(ABB *A);

/**
 * Destruye el arbol recursivamente
 * @param A El arbol que queremos destruir
 */
void destruirAbb(ABB *A);


//FUNCIONES DE INFORMACIÓN
unsigned esAbbVacio(ABB A);

void buscarNodoAbb(ABB A, char *lexema, componente* elemento);

/**
 * @brief Imprime todo el ABB, imprimiendo cada elemento con su tipo y sus valores asociados
 * 
 * @param A Arbol a imprimir
 */
void imprimirAbb(ABB A);

/**
 * @brief Imprime los elementos del ABB cuyo componente léxico sea el pasado por parametro
 * 
 * @param A arbol a imprimir
 * @param compLex componente lexico a buscar
 */
void imprimirCompLex(ABB A, int compLex);

/**
 * @brief Busca y almacena el lexema de la primera variable que encuentre
 * 
 * @param A arbol donde se busca la variable
 * @param variable cadena donde se almacena el lexema
 */
void buscarVariable(ABB A, char** variable);


// FUNCIONES DE MODIFICACION

int insertarElementoAbb(ABB *A, char* lexema, int compLex, union Valor valor);

void suprimirElementoAbb(ABB *A, char *lexema);



#endif	// ABB_H

