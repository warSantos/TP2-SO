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
	for(i = 0; i < size_mem_virtual; ++i){
		mem_virtual[i].controle &= ~REFERENCIADO;
	}
}

void print_memoria_virtual(){
	int i;
	
	printf("  %11s: %11s | %11s [RMP]\n", "Indice", "Endereco", "Ult. Acesso");
	for(i=0; i<size_mem_virtual; i++){
		if(mem_virtual[i].controle & PRESENTE){
			printf("  %11d: %11d | %11d [%d%d%d]\n",
				i, mem_virtual[i].endereco, mem_virtual[i].ultimo_acesso,
				mem_virtual[i].controle & REFERENCIADO, mem_virtual[i].controle & MODIFICADO,
				mem_virtual[i].controle & PRESENTE);
		}
	}
}
