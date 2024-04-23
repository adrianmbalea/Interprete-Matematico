#ifndef COMANDOS_H
#define COMANDOS_H

/**
 * @brief Permite imprimir o no los resultados de las próximas expresiones 
 * 
 * @param valor Valor que indica si se imprimen o no, puede ser "on" u "off"
 */
void echo(char* valor);

/**
 * @brief Permite salir del programa
 * 
 */
void quit();

/**
 * @brief Muestra el histórico de variables empleadas y sus respectivos valores
 * 
 */
void workspace();

/**
 * @brief Elimina todo el workspace actual
 * 
 */
void clear();

/**
 * @brief Muestra la ayuda
 * 
 */
void help();

/**
 * @brief Carga un fichero de código y lo ejecuta
 * 
 * @param fichero fichero a ejecutar
 */
void load(char *fichero);

#endif	/* COMANDOS_H */