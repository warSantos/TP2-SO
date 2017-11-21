#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    FILE *leitor = fopen(argv[1], "r");
    
    int i,j = 0;
    unsigned long int soma = 0;
    unsigned long int v1, v2, v3, v4, v5, v6;
    unsigned long int *pages = calloc(sizeof(long int), 6); 
    char *arqs[3] = {"m-dirtys.txt", "l-m", "r-m"};
    FILE *escritor = fopen(arqs[0], "a");
    for(i = 0; i < 3; ++i){

        while(j < 32 && fscanf(leitor, "%lu %lu %lu %lu %lu %lu\n", &v1, &v2, &v3, &v4, &v5, &v6) != EOF){
                                    
            pages[0] += v1;
            pages[1] += v2;
            pages[2] += v3;
            pages[3] += v4;
            pages[4] += v5;
            pages[5] += v6;            
            ++j;
        }
        j = 0;
        fprintf(escritor, "%lu  %lu %lu %lu %lu %lu\n", pages[0]/32, pages[1]/32, pages[2]/32, pages[3]/32, pages[4]/32, pages[5]/32);   
        pages[0] = 0;
        pages[1] = 0;
        pages[2] = 0;
        pages[3] = 0;
        pages[4] = 0;
        pages[5] = 0;
    }
    printf("I: %d\n", i);
    fclose(escritor);
    fclose(leitor);
    return 0;
}