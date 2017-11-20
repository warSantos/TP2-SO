#include "substituicao.h"

int main(int argc, char **argv){
	if(argc < 5){
		printf("Fltando argumentos.\n\n");
		printf("1. o algoritmo de substituicao a ser usado (lru, fifo ou random)\n"
				"2. o arquivo contendo a sequencia de enderecos de memoria acessados (arquivo.log, nesse exemplo)\n"
				"3. o tamanho de cada pagina/quadro de memoria, em kilobytes — faixa de valores razoaveis: de 2 a 64\n"
				"4. o tamanho total da memoria fısica disponıvel para o processo, tambem em kilobytes — faixa de"
				"valores razoaveis: de 128 a 16384 (16 MB).\n"
				"5. debug para ativar o modo depuracao. (opcional)\n");
		return 1;
	}
	char *algoritmo = argv[1];
	char *arquivo = argv[2];
	uint size_page = atoi(argv[3]) * 1024;
	size_mem_fisica = atoi(argv[4]) * 1024;

	// flag para habilitar/desabilitar debug
	debug = 0;
	if(argc > 5){
		debug = (argv[5][0] == 'd');
	}
	//Inicializando as variáveis globais.
	page_faults = 0;
	n_reads = 0;
	n_writes = 0;
	n_dirty_pages = 0;
	tempo = 0;
	
	size_mem_virtual = (1UL << 32) / size_page;
	if(size_mem_virtual > size_mem_fisica){
		
		printf("Tabela de pagina maior que a memoria dispnivel.\n");
		printf("Memoria Virtual: %d | Memoria Fisica %d.\n", size_mem_virtual, size_mem_fisica);
		return 1;
	}
	size_mem_fisica /= size_page;
	
	mem_virtual = calloc(sizeof(Moldura), size_mem_virtual);
	mem_fisica = calloc(sizeof(int), size_mem_fisica);
	
	//Definindo a política de escalonamento.
	switch(algoritmo[0]){
		// FIFO
		case 'f':
		case 'F':
			politica = sub_fifo;
			break;

		// LRU
		case 'l':
		case 'L':
			politica = sub_lru;
			break;

		// RANDOM
		case 'r':
		case 'R':
			politica = sub_random;
			break;

		default:
			break;
	}	

	uint qtdeLinhas = leArquivo(arquivo);
	uint addr;
	uint page, posicao_livre = 0;
	char *temp_linha, rw;
	srand(time(NULL));
	
	
	if(debug){

		printf("size_ram: %d size_vi: %d\n", size_mem_fisica, size_mem_virtual);
	}
	printf("Executando o simulador...\n"
			"Arquivo de entrada: %s\n"
			"Tamanho da memoria: %d KB\n"
			"Tamanho das paginas: %d KB\n"
			"Tecnica de reposicao: %s\n",
		arquivo, size_mem_fisica * size_page / 1024 , size_page / 1024, algoritmo);
	do{
		// referenciando a referencia.
		temp_linha = acessos + (LEN * tempo);
		rw = temp_linha[9];
		temp_linha[8] = '\0';
		addr = (uint)strtol(temp_linha, NULL, 16);
		page = addr / size_page;
		
		if(debug){

			printf("MEMORIA ANTES:\n");
			print_memoria_virtual();
			printf("Memória Física: %d/%d\n", posicao_livre, size_mem_fisica);
			printf("Endereço: %d, página %d\n", addr, page);
			printf("Tempo: %d # Acertos: %d # Erros: %d\n", tempo, tempo - page_faults, page_faults);
			getchar();
		}
		if(!(mem_virtual[page].controle & PRESENTE)){

			if(posicao_livre < size_mem_fisica){

				mem_virtual[page].endereco = posicao_livre;
				posicao_livre++;
			}else{
				
				if(debug){
					print_memoria_virtual();
					printf("Memória cheia: chamando o %s\n", algoritmo);
					getchar();
				}
				substituicao(page);
			}
			page_faults++;
		}
		if((tempo % ZERO_TIME) == 0){
			// verifica se é hora de zerar os bits de referência.
			zera_bit();
		}
		mem_virtual[page].ultimo_acesso = tempo;
		mem_virtual[page].controle = REFERENCIADO | PRESENTE;
		if(rw == 'W'){

			mem_virtual[page].controle |= MODIFICADO;
			n_writes++;
		}else{

			n_reads++;
		}
		
		//Armazena na memória física o índice da memória virtual.
		mem_fisica[mem_virtual[page].endereco] = page;
		
		if(debug){

			printf("MEMORIA DEPOIS:\n");		
			print_memoria_virtual();
			getchar();
		}
		++tempo;
	}while(tempo <= qtdeLinhas);
	
	printf("Paginas lidas: %d\n"
			"Paginas escritas: %d\n", n_reads, n_writes);
	
	return 0;
}
