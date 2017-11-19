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
	char format[25];
	
	sprintf(format, "  %%0%dd: %%11d | %%11d [%%d]\n", size_mem_virtual);
	
	printf("  %11s: %11s | %11s [RMP]\n", "Indice", "Endereco", "Ult. Acesso");
	for(i=0; i<size_mem_virtual; i++){
		printf("  %11d: %11d | %11d [%d%d%d]\n",
			i, mem_virtual[i].endereco, mem_virtual[i].ultimo_acesso,
			mem_virtual[i].controle & REFERENCIADO, mem_virtual[i].controle & MODIFICADO,
			mem_virtual[i].controle & PRESENTE);
	}
}

char detecta_teste(char *arquivo){

	if(!strcmp(arquivo, "compilador.log")){
		return 'c';
	}else if(!strcmp(arquivo, "compressor.log")){
		return 'p';
	}else if(!strcmp(arquivo, "matriz.log")){
		return 'm';
	}else if(!strcmp(arquivo, "simulador.log")){
		return 's';
	}
	return '0';
}
void saida(char f, char *arquivo, uint size_page){
	
	// f, algoritmo a ser executado. 
	// *arquivo, arquivo em execução
	char t = detecta_teste(arquivo);

	// Geração de tabelas
	char arq_saida[20];
	
	// leituras
	sprintf(arq_saida, "logs/%c-%c-r", f, t);
	FILE *escritor = fopen(arq_saida, "a");		
	if(size_page == 64){	
		fprintf(escritor, "%d\n", n_reads);
	}else{
		fprintf(escritor, "%d;", n_reads);
	}
	fclose(escritor);
	
	// escrita
	sprintf(arq_saida, "logs/%c-%c-w", f, t);
	escritor = fopen(arq_saida, "a");		
	if(size_page == 64){	
		fprintf(escritor, "%d\n", n_writes);
	}else{
		fprintf(escritor, "%d;", n_writes);
	}	
	fclose(escritor);
	
	// acertos
	sprintf(arq_saida, "logs/%c-%c-a", f, t);
	escritor = fopen(arq_saida, "a");		
	if(size_page == 64){	
		fprintf(escritor, "%d\n", (tempo - page_faults));
	}else{
		fprintf(escritor, "%d;", (tempo - page_faults));
	}	
	fclose(escritor);
	
	// erros	
	sprintf(arq_saida, "logs/%c-%c-e", f, t);		
	escritor = fopen(arq_saida, "a");		
	if(size_page == 64){	
		fprintf(escritor, "%d\n", page_faults);
	}else{
		fprintf(escritor, "%d;", page_faults);
	}	
	fclose(escritor);
	
}

/*
 A cada chamada da Função quatro arquivos devem ser editados.
 Nomeclatura do arquivo algoritmo - teste - escrita/leitura. Ex.: r-c-r 
 IDs: para os arquivos de teste:
	compilador.log..: c
	compressor.log..: p
	matriz.log......: m
	simulador.log...: s		
 Saida: 2 arquivos de log de saida, um para fifo e outro para o r.
 tabela qtde de memoria x tamanho da pagina.
 
 Parâmetros: qtde Memoria, tamanho da pagina, arquivo, algoritmo.

 Dados a serem minerados: qtde de escritas, leituras, acertos e erros.
*/