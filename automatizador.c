#include <stdio.h>
#include <stdlib.h>

/*

Parâmetros: tamanho da memória, tamanho da página, algoritmo, arquivo de teste.
*/

int potencia(int exp){

    int i, retorno = 2;
    for(i = 1; i < exp; ++i){

        retorno *= 2; 
    }
    return retorno;
}

int main(void){

    int i,j, k, l;
    int iteracao = 0;
    char *files[4] = {"compilador.log", "compressor.log" , "matriz.log", "simulador.log"};
    char *alg = "frl";
    char comando[50], log[30];

    for(i = 0; i < 3; ++i){ // algoritmo

        for(l = 0; l < 4; ++l){ // arquivo a ser executado
            
            for(j = 7; j < 15; ++j){ // memória

                for(k = 1; k < 7; ++k){ // tamanho da página.
                                            
                    sprintf(comando ,"./main.out %c\tteste/%s\t%d %d n\n", alg[i], files[l], 1<<k, 1<<j);
                    system(comando);       
                    sprintf(log, "echo \"%d\" >> log-exec", iteracao);
                    system(log);
                    iteracao++;
                }
            }
        }
    }
    //printf("iteracões: %d i: %d\n", iteracao, i);
    return 0;
}
