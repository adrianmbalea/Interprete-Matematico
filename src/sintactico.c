#include <stdlib.h>
#include <stdio.h>
#include "../includes/sintactico.h"
#include "../includes/lex.yy.h"
#include "../includes/definiciones.h"

void iniciarSintactico(){
    componente c;

    printf("\n\n***** INICIO DEL ANALISIS *****\n\n\n");
    while(1){
        c = sigCompLexico();
        if(c.compLex==EOF){
            printf("\n\n***** FIN DEL ANALISIS *****\n\n\n");
            free(c.lexema);
            return;
        } 
        if(c.compLex!=-2){
            printf("< %d, %s >\n", c.compLex, c.lexema);
        }
        free(c.lexema);
    }
}