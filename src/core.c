#include "core.h"

int sizeArq(char *arquivo){
	
	struct stat fstats;
	if(!stat(arquivo, &fstats)){
				
		return fstats.st_size;
	}else{
	
		perror("leArquivo");
		return -1;
	}	
}

uint leArquivo(char *arquivo){
	
	uint size = sizeArq(arquivo), qtdeLinhas = size / LEN;
	acessos = malloc(size + 1);
	FILE *leitor = fopen(arquivo, "r");
	fread(acessos, 1, size, leitor);
	fclose(leitor);	
	return qtdeLinhas;
}

void zera_bit(void){

	uint i;
	for(i = 0; i < size_mem; ++i){

		mem_virtual[i].controle &= ~REFERENCIADO;
	}
}
