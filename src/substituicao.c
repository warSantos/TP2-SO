#include "substituicao.h"

///Armazena a posição da página mais antiga na memória física.
uint fifo_indice = 0;

uint sub_fifo(uint page){
	if(fifo_indice == size_mem_fisica){
		fifo_indice = 0;
	}
	return fifo_indice++;
}


uint sub_lru(uint page){
	uint i, menor = 0;
	for(i=0; i<size_mem_fisica; i++){
		//Usa a própria memória principal como tabela inversa.
		if(mem_virtual[mem_fisica[i]].ultimo_acesso < mem_virtual[mem_fisica[menor]].ultimo_acesso){
			menor = i;
		}
	}
	
	return mem_fisica[menor];
}

uint sub_random(uint page){

	return rand() % size_mem_fisica;
}

void substituicao(uint page){
	uint sai = politica(page);

	if(debug){
		printf("Quem sai: %d\n", sai);
		getchar();
	}

	//Atualiza o endereço da página que vai entrar.
	mem_virtual[page].endereco = mem_virtual[sai].endereco;

	//Checando se a página está suja.
	if((mem_virtual[sai].controle & MODIFICADO) != 0){
		n_dirty_pages++;
	}

	//Zera os bits da página que saiu.
	mem_virtual[sai].controle = 0;
}
