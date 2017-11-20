#include "substituicao.h"

#define stage(N) printf("stage %d\n", N);

int main(int argc, char **argv){

	if(argc < 4){
		printf("Fltando argumentos.\n");
		return 1;
	}
	char *algoritmo = argv[1];
	char *arquivo = argv[2];
	uint size_page = atoi(argv[3]) * 1024;
	size_mem_fisica = atoi(argv[4]) * 1024;

	// flag para habilitar/desabilitar debug
	debug = 0;
	if(argc > 4){
		debug = (argv[5][0] == 'd');
	}

	size_mem_virtual = (1UL << 32) / size_page;
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
	//Inicializando as variáveis globais.
	page_faults = 0;
	n_reads = 0;
	n_writes = 0;
	n_dirty_pages = 0;
	tempo = 0;

	uint qtdeLinhas = leArquivo(arquivo);
	uint addr;
	uint page, posicao_livre = 0;
	char *temp_linha, rw;
	srand(time(NULL));
	
	
	if(debug){

		printf("size_ram: %d size_vi: %d\n", size_mem_fisica, size_mem_virtual);
	}
	do{
		
		
		// referenciando a referencia i.
		temp_linha = acessos + (LEN * tempo);
		rw = temp_linha[9];
		temp_linha[8] = '\0';
		addr = (uint)strtol(temp_linha, NULL, 16);
		page = addr / size_page;
		
		if(debug){

			printf("MEM V ANTES:\n");
			print_memoria_virtual();
			printf("Memória Física: %d/%d\n", posicao_livre, size_mem_fisica);
			printf("Endereço: %ld, página %ld\n", addr, page);
			printf("Tempo: %d # Acertos: %d # Erros: %d\n", tempo, tempo - page_faults, page_faults);
			getchar();
		}
		if(!(mem_virtual[page].controle & PRESENTE)){

			if(posicao_livre < size_mem_fisica){

				mem_virtual[page].endereco = posicao_livre;
				posicao_livre++;
			}else{
				
				if(debug){
					printf("Memória cheia: chamando o %s\n", algoritmo);
					getchar();
				}
				substituicao(page);
			}
			page_faults++;
		}else{
			//O lru precisa refazer a heap das páginas que foram acessadas.
			if(posicao_livre >= size_mem_fisica && algoritmo[0] == 'l'){
				
				if(debug){
					
					printf("oi\n");getchar();
					uint kk;
					for(kk=0; kk<size_mem_fisica; kk++){
						printf("ram[%d]: %d\n", kk, mem_fisica[kk]);
					}
				}
				mem_virtual[page].ultimo_acesso = tempo;
				mem_fisica[mem_virtual[page].endereco] = page;
				
				if(debug){/*
					printf("-----\n");
					for(kk=0; kk<size_mem_fisica; kk++){
						printf("ram[%d]: %d\n", kk, mem_fisica[kk]);
					}
					print_memoria_virtual();
					getchar();
					*/
				}
				extern construi_heap;
				if(!construi_heap){
					construi_heap = 1;
					heap_constroi();
					heap_refaz(0);
				}else{
					heap_refaz(mem_fisica[mem_virtual[page].endereco]);
				}
			}
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
		if(posicao_livre <= size_mem_fisica && algoritmo[0] == 'l'){
			mem_fisica[mem_virtual[page].endereco] = page;
		}
		
		if(debug){

			printf("MEM V DEPOIS:\n");		
			print_memoria_virtual();
			getchar();
		}
		++tempo;
	}while(tempo <= qtdeLinhas);
	printf("%d/%d\ntempo: %d\nacertp: %d\nerro: %d\ndp: %d\n", posicao_livre, size_mem_fisica, tempo, tempo - page_faults, page_faults, n_dirty_pages);
	printf("W: %d\nR: %d\n", n_writes, n_reads);
	return 0;
	saida(algoritmo[0], arquivo, size_page / 1024);
	return 0;
}
