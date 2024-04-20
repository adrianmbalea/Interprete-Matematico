%{
#include <string.h>
#include <math.h>

#include "../includes/definiciones.h"
#include "../includes/ts.h"
%}

%option noyywrap noinput nounput yylineno

/*Identificadores*/
ID [a-zA-Z_]([a-zA-Z0-9_])*

/*Numeros enteros*/
NUMERO_DECIMAL ([1-9][_0-9]*)|(0+(_?0)*)
NUMERO_BINARIO 0[bB](_?[01])+
NUMERO_OCTAL 0[oO](_?[0-7])+
NUMERO_HEXADECIMAL 0[xX](_?[[:xdigit:]])+
NUMERO_ENTERO ({NUMERO_DECIMAL}|{NUMERO_BINARIO}|{NUMERO_OCTAL}|{NUMERO_HEXADECIMAL})

/*Numeros flotantes*/
PARTE_DIGITOS [0-9](_?[0-9])*
PUNTO_FLOTANTE ({PARTE_DIGITOS}?\.{PARTE_DIGITOS})|({PARTE_DIGITOS}\.)
EXPONENCIAL ({PARTE_DIGITOS}|{PUNTO_FLOTANTE})[eE][\+-]?{PARTE_DIGITOS}
NUMERO_FLOTANTE ({PUNTO_FLOTANTE}|{EXPONENCIAL})

/*Comentarios*/
COMENTARIO //.*

/* Operadores */
OPERADOR_SIMPLE \+|-|\*|\/|%|\^|\<|\>|\(|\)|\[|\]|\{|\}|,|\.|;|=
MENOR_IGUAL \<=
MAYOR_IGUAL \>=
IGUAL_IGUAL ==
DISTINTO !=
MAS_IGUAL \+= 
MENOS_IGUAL -=
POR_IGUAL \*=
SLASH_IGUAL \/=
PORCENTAJE_IGUAL %=

%%




[[:space:]] /* ignoramos los espacios */

. { imprimirError(LEXEMA_MAL_FORMADO, yylineno); return -2; }

<<EOF>> { yyterminate(); }

%%

// Toma el valor de 1 si se ha pasado por parametros un archivo, y 0 en el caso contrario
int fichero = 0;

componente sigCompLexico(){
    componente c;
    c.compLex=yylex();
    c.lexema=strdup(yytext);

    if(!c.compLex){ // si se ha llegado al final del archivo, le mandamos EOF al sintactico
        c.compLex=EOF;
    }
    
    return c;
}

void abrirArchivo(char *filename){
    // Si no se ejecuta ningun archivo
    if(filename==NULL){
        yyin = stdin;
    } else{
        FILE *fp;
        fp=fopen(filename, "r");
        if(fp == NULL){
            imprimirError(ERROR_ARCHIVO, 1);
            yyin = stdin;
        } else{
            yyin = fp;
            fichero = 1;
        }
    }
}

void cerrarArchivo(){
    if (fichero==1 && yyin != NULL) {
        fclose(yyin);
        yyin = NULL;
    }
    yylex_destroy(); 
}
