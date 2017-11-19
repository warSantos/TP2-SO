#include "substituicao.h"

int main(int argc, char **argv){

	algoritmo = argv[1];
	char *arquivo = argv[2];
	uint size_page = atoi(argv[3]) * 1024;	
	size_mem_fisica = atoi(argv[4]) * 1024;

	// flag para habilitar/desabilitar debug
	char flag_debug = argv[5][0];

	size_mem_virtual = (1UL << 32) / size_page;
	size_mem_fisica /= size_page;
	
	mem_virtual = malloc(size_mem_virtual * sizeof(Moldura));
	mem_fisica = malloc(size_mem_fisica * sizeof(int));
	
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
	uint addr, nova_pagina = -1;
	uint page, posicao_livre = 0;
	char *temp_linha, rw;
	srand(time(NULL));
	
	uint32_t asd;
	if(flag_debug == 'd'){

		printf("size_ram: %d size_vi: %d\n", size_mem_fisica, size_mem_virtual);
	}
	do{
		// referenciando a referencia i.
		temp_linha = acessos + (LEN * tempo);
		sscanf(temp_linha, "%x %c\n", &addr, &rw);
		page = addr / size_page;

		if(flag_debug == 'd'){

			printf("MEM V ANTES:\n");
			print_memoria_virtual();
			printf("Memória Física: %d/%d\n", posicao_livre, size_mem_fisica);
			printf("Endereço: %ld, página %ld\n", addr, page);
			printf("Endereço: %x, página %d\n", addr, page);
			getchar();
		}
		if(!(mem_virtual[page].controle & PRESENTE)){

			if(posicao_livre < size_mem_fisica){

				mem_virtual[page].endereco = posicao_livre;
				posicao_livre++;
				
			}else{
				
				if(flag_debug == 'd'){
					printf("Memória cheia: chamando o %s\n", algoritmo);
				}
				substituicao(page);
			}
			page_faults++;
		}
		if(!(tempo % ZERO_TIME)){
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
		
		if(flag_debug == 'd'){

			printf("MEM V DEPOIS:\n");		
			print_memoria_virtual();
			getchar();
		}
		++tempo;
	}while(tempo <= qtdeLinhas);	
	saida(algoritmo[0], arquivo, size_page / 1024);
	return 0;
}
