#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	int i = 0, j = 0, loop = 1;		
	char *arq[4] = {"compilador.log", "matriz.log", "compressor.log", "simulador.log"}, str[100];
	FILE *leitor = fopen(argv[1], "r"), *escritor = fopen("tabela.txt", "a");
	fprintf(escritor, "%s\n", arq[0]);				
	fprintf(escritor, "Qtde Mem/Tam Página	2	4	8	16	32	64\n");
	while(i < 96 && fscanf(leitor, "%[^\n]\n", str)!= EOF){
						
		fprintf(escritor, "%d	%s\n", 1<<(j+7), str);
		if(j == 7){			
			j = -1;
			fprintf(escritor, "%s\n", arq[loop]);
			fprintf(escritor, "Qtde Mem/Tam Página	2	4	8	16	32	64\n");
			if(loop == 3){

				loop = -1;
			}
			loop++;
			//fprintf(escritor, "\n");
		}		
		j++;
		i++;
	}
	fclose(leitor);
	fclose(escritor);
	return 0;
}