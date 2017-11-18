#include "substituicao.h"

///Armazena a posição da página mais antiga na memória física.
uint fifo_indice = 0;

uint sub_fifo(uint page){
	fifo_indice++;
	if(fifo_indice == size_mem_fisica){
		fifo_indice = 0;
	}
	return fifo_indice;
}


///Vetor usado para heap binária no lru.
uint *heap;

uint sub_lru(uint page){

	return 0;
}


uint sub_random(uint page){

	return rand() % size_mem_fisica;
}


void substituicao(uint page){
	uint sai = politica(page);
	
	//Atualiza o endereço da página que vai entrar.
	mem_virtual[page].endereco = mem_virtual[sai].endereco;
	
	//Checando se a página está suja.
	if((mem_virtual[sai].controle & ALTERADO) != 0){
		n_dirty_pages++;
	}
	
	//Zera os bits da página que saiu.
	mem_virtual[sai].controle = 0;
}
