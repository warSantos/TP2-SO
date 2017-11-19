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
    char *alg = "fr";
    char comando[50], log[30];

    for(i = 0; i < 1; ++i){ // algoritmo

        for(l = 0; l < 4; ++l){ // arquivo a ser executado
            
            for(j = 7; j < 15; ++j){ // memória

                for(k = 1; k < 7; ++k){ // tamanho da página.
                                            
                    sprintf(comando ,"./main.out %c\tteste/%s\t%d %d n\n", alg[i], files[l], potencia(k), potencia(j));
                    //printf("comando: %s", comando);
                    iteracao++;                  
                    //printf("k: %d\n", k);
                    // Aqui chama o algoritmo.
                    //system(comando);
                    sprintf(log, "echo \"%d\" >> log-exec", iteracao);                        
                    system(log);
                }
            }
            break;
        }
    }
    //printf("iteracões: %d i: %d\n", iteracao, i);
    return 0;
}
