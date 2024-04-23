#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/abb.h"
#include "../includes/sintactico.tab.h"

//ESTRUCTURAS DE DATOS

struct celda {
	componente info;
	struct celda *izq, *der;
};



void crearAbb(ABB *A) {
    *A = NULL;
}

void destruirAbb(ABB *A) {
    if (*A != NULL) {
        destruirAbb(&(*A)->izq);
        destruirAbb(&(*A)->der);
        if((*A)->info.lexema != NULL){
            free((*A)->info.lexema);
            (*A)->info.lexema=NULL;
        }
        free(*A);
        *A = NULL;
    }
}

int insertarElementoAbb(ABB *A, char* lexema, int compLex, union Valor valor) {
    if (esAbbVacio(*A)) {
        *A = (ABB) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*)malloc(strlen(lexema)+1);
		strcpy((*A)->info.lexema, lexema);
		(*A)->info.lexema[strlen(lexema)] = '\0';
        (*A)->info.compLex=compLex;
        (*A)->info.valor=valor;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return compLex;
    }
    int comp = strcmp(lexema, (*A)->info.lexema);

    if (comp == 0) { //lexema == (*A)->info.lexema
        if((*A)->info.compLex==VAR) (*A)->info.valor=valor;
        return (*A)->info.compLex;
    }
    if (comp > 0) { //lexema > (*A)->info.lexema
        return insertarElementoAbb(&((*A)->der), lexema, compLex, valor);
    }

    //lexema < ( *A)->info.lexema 
    return insertarElementoAbb(&((*A)->izq), lexema, compLex, valor);
}

/* Funcion privada que devuelve mínimo de subárbol dcho */
componente _suprimir_min(ABB * A) {//Se devuelve el elemento más a la izquierda
    ABB aux;
    componente ele;
    if (esAbbVacio((*A)->izq)) {//Si izquierda vacía, se devuelve valor nodo actual A
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq); //se vuelve a buscar mínimo rama izquierda
    }
}

void suprimirElementoAbb(ABB *A, char *lexema) {
    ABB aux;
    if (esAbbVacio(*A)) {
        return;
    }

    int comp = strcmp(lexema, (*A)->info.lexema);
    if (comp < 0) { // lexema < (*A)->info.lexema
        suprimirElementoAbb(&(*A)->izq, lexema);
    } else if (comp > 0) { // lexema > (*A)->info.lexema
        suprimirElementoAbb(&(*A)->der, lexema);
    } else if (esAbbVacio((*A)->izq) && esAbbVacio((*A)->der)) {
        free((*A)->info.lexema);
        free(*A);
        *A = NULL;
    } else if (esAbbVacio((*A)->izq)) { // pero no es vacio derecha
        aux = *A;
        *A = (*A)->der;
        free(aux->info.lexema);
        free(aux);
    } else if (esAbbVacio((*A)->der)) { //pero no es vacio izquierda
        aux = *A;
        *A = (*A)->izq;
        free(aux->info.lexema);
        free(aux);
    } else { //ni derecha ni izquierda esta vacio, busco mínimo subárbol derecho
        free((*A)->info.lexema); //elimino la info pero no libero el nodo,
        //pues en su sitio voy a poner el mínimo del subárbol derecho
        (*A)->info = _suprimir_min(&(*A)->der);
    }
}


//OPERACIONES DE INFORMACIÓN

unsigned esAbbVacio(ABB A) {
    return A == NULL;
}

void buscarNodoAbb(ABB A, char *lexema, componente* componente) {
    if (esAbbVacio(A)) {
        return;
    }

    int comp = strcmp(lexema, A->info.lexema);
    if (comp == 0) { // lexema == A->info.lexema
        *componente = A->info;
        return;
    } else if (comp < 0) { // lexema < A->info.lexema
        buscarNodoAbb(A->izq, lexema, componente);
    } else { // lexema > A->info.lexema
        buscarNodoAbb(A->der, lexema, componente);
    }
}

/**
 * @brief Imprime todo el ABB, imprimiendo cada elemento con su tipo y sus valores asociados
 * 
 * @param A Arbol a imprimir
 */
void imprimirAbb(ABB A){
    if(!esAbbVacio(A)){
		imprimirAbb(A->izq);
        switch(A->info.compLex){
            case VAR:
                printf("<VAR, %s, %g>\n", A->info.lexema, A->info.valor.var);
                break;
            case CONST:
                printf("<CONST, %s, %g>\n", A->info.lexema, A->info.valor.var);
                break;
            case FUNC:
                printf("<FUNC, %s>\n", A->info.lexema);
                break;
            case CMD:
                printf("<CMD, %s>\n", A->info.lexema);
                break;
            default:
                return;
        }
		imprimirAbb(A->der);
    }
}

/**
 * @brief Imprime los elementos del ABB cuyo componente léxico sea el pasado por parametro
 * 
 * @param A arbol a imprimir
 * @param compLex componente lexico a buscar
 */
void imprimirCompLex(ABB A, int compLex){
    if(!esAbbVacio(A)){
		imprimirCompLex(A->izq, compLex);
        if(A->info.compLex==compLex) {
            switch(compLex){
                case VAR:
                    printf("<%s, %g>\n", A->info.lexema, A->info.valor.var);
                    break;
                case CONST:
                    printf("<%s, %g>\n", A->info.lexema, A->info.valor.var);
                    break;
                case FUNC:
                    printf("<%s>\n", A->info.lexema);
                    break;
                case CMD:
                    printf("<%s>\n", A->info.lexema);
                    break;
                default:
                    return;
            }
            
        }
		imprimirCompLex(A->der, compLex);
    }
}

/**
 * @brief Busca y almacena el lexema de la primera variable que encuentre
 * 
 * @param A arbol donde se busca la variable
 * @param variable cadena donde se almacena el lexema
 */
void buscarVariable(ABB A, char** variable){
    if(!esAbbVacio(A) && *variable==NULL){
		buscarVariable(A->izq, variable);
        if(A->info.compLex==VAR) {
            *variable=A->info.lexema;
            return;
        }
		buscarVariable(A->der, variable);
    }
}

