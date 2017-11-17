#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/// quantidade de caracteres por linha.
#define LEN 11

int size_mem, size_page; 
int page_faults = 0;
int n_reads = 0;
int n_writes = 0;
int n_dirty_pages = 0;

char *acessos, *algoritmo;

int sizeArq(char *arquivo){
	
	struct stat fstats;
	if(!stat(arquivo, &fstats)){
				
		return fstats.st_size;
	}else{
	
		perror("leArquivo");
		return -1;
	}	
}

void leArquivo(char *arquivo){
	
	int size = sizeArq(arquivo), qtdeLinhas = size / LEN;
	acessos = malloc(size);
	FILE *leitor = fopen(arquivo, "r");
	fread(acessos, 1, size, leitor);
	fclose(leitor);
}

int main(int argc, char **argv){
	
	algoritmo = argv[1];
	char *arquivo = argv[2];
	size_page = atoi(argv[3]);
	size_mem = atoi(argv[4]);
	
	/*
	switch(algoritmo[0]){
		
		// FIFO
		case 'f':
		case 'F':
		
			break;
		// LRU
		case 'l':
		case 'L':
			
			break;
		// RANDOM
		case 'r':
		case 'R':
		
			break;
			
		default :
			break;
	}
	*/
	leArquivo(arquivo);
	return 0;
}
