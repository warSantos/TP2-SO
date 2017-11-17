#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/// quantidade de caracteres por linha.
#define LEN 11
/// intervalo de tempo para zerar os bits de referenciado.
#define ZERO_TIME 1000

typedef enum CONTROLE {
	
	REFERENCIADO = 1,
	ALTERADO = 2,
	PRESENTE = 4
} CONTROLE;

typedef struct Moldura {
	
	int endereco;
	int ultimo_acesso;
	char controle;
}Moldura;

unsigned int size_mem, size_page; 
unsigned int page_faults = 0;
unsigned int n_reads = 0;
unsigned int n_writes = 0;
unsigned int n_dirty_pages = 0;
unsigned int *mem_fisica;
Moldura *mem_virtual;
unsigned int tempo = 0;

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

unsigned int leArquivo(char *arquivo){
	
	unsigned int size = sizeArq(arquivo), qtdeLinhas = size / LEN;
	acessos = malloc(size + 1);
	FILE *leitor = fopen(arquivo, "r");
	fread(acessos, 1, size, leitor);
	fclose(leitor);	
	return qtdeLinhas;
}

void zera_bit(void){

	unsigned int i;
	for(i = 0; i < size_mem; ++i){

		mem_virtual[i].controle &= ~REFERENCIADO;
	}
}

int main(int argc, char **argv){
	
	algoritmo = argv[1];
	char *arquivo = argv[2];
	size_page = atoi(argv[3]) * 1024;
	size_mem = atoi(argv[4]) * 1024;
	
	mem_virtual = malloc((((1 << 32) / size_page) * sizeof(Moldura)));	
	size_mem /= size_page;
	mem_fisica = malloc(size_mem * sizeof(int));
	
	unsigned int qtdeLinhas = leArquivo(arquivo);
	unsigned int addr;		
	unsigned int page, posicao_livre = 0;
	char *temp_linha, rw;
		
	do {
		// referenciando a referencia i.
		temp_linha = acessos + (LEN * tempo);
		sscanf(temp_linha , "%x %c\n", &addr, &rw);
		page = addr / (size_page);
		
		if(!(mem_virtual[page].controle & PRESENTE)){
			
			if(posicao_livre < size_mem){
				
				mem_virtual[page].endereco = posicao_livre;
				posicao_livre++;
			}else{
				
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
			}			
		}
		if(!(tempo % ZERO_TIME)){
			// verifica se é hora de zerar os bits de referência.
			zera_bit();
		}
		mem_virtual[page].ultimo_acesso = tempo;
		mem_virtual[page].controle = REFERENCIADO;
		if(rw == 'W'){
			
			mem_virtual[page].controle |= ALTERADO;
			n_writes++;
		}else{

			n_reads++;
		}		
		++tempo;
	}while(tempo < qtdeLinhas);		
	return 0;
}