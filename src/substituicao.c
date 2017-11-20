#include "substituicao.h"

///Armazena a posição da página mais antiga na memória física.
uint fifo_indice = 0;

uint sub_fifo(uint page){
	if(fifo_indice == size_mem_fisica){
		fifo_indice = 0;
	}
	return fifo_indice++;
}


///Vetor usado para heap binária no lru.
int construi_heap = 0;
uint *heap;

void heap_refaz(uint inicio){
	uint i = inicio, j = 2 * i + 1;

	uint troca = heap[i];
	while(j < size_mem_fisica){
		if(debug){
			printf("Pai[%d]: %d # E[%d](%d)", i, mem_virtual[troca].ultimo_acesso, j, mem_virtual[heap[j]].ultimo_acesso);

		}
		if((j + 1 < size_mem_fisica) && (mem_virtual[heap[j]].ultimo_acesso > mem_virtual[heap[j + 1]].ultimo_acesso)){
			j++;
			if(debug){
				printf(" D[%d](%d)", j, mem_virtual[heap[j]].ultimo_acesso);
			}
		}
		if(debug){
			printf("\n");	
		}

		if(mem_virtual[heap[j]].ultimo_acesso < mem_virtual[troca].ultimo_acesso){
			heap[i] = heap[j];
			mem_fisica[j] = i;
			
			i = j;
			j = 2 * i + 1;

			if(debug){
				printf("Trocado");getchar();
			}
		}else{
			if(debug){
				getchar();
			}
			break;
		}
	}
	heap[i] = troca;
	mem_fisica[inicio] = i;
	
}

void heap_constroi(){
	uint i;

	heap = malloc(size_mem_fisica * sizeof(uint));

	//memcpy(heap, mem_fisica, size_mem_fisica * sizeof(uint));
	if(debug){
		printf("CONTROI HEAP\nRAM:\n");
		for(i=0; i<size_mem_fisica; i++){
			printf("%2d: %d\n", i, mem_fisica[i]);
		}
		getchar();
	}
	
	for(i=0; i<size_mem_fisica; i++){
		heap[i] = mem_fisica[i];
		mem_fisica[i] = i;
	}
	
	if(debug){
		printf("constroi\n");
		for(i = 0; i < size_mem_fisica; i++){
			printf("%2d: %d, %d\n", i, heap[i], mem_virtual[heap[i]].ultimo_acesso);
		}
		getchar();
	}

	for(i = (size_mem_fisica - 1) / 2; i > 0; i--){
		heap_refaz(i);
	}
	//heap_refaz(0);
}

uint sub_lru(uint page){
	if(!construi_heap){
		heap_constroi();
		construi_heap = 1;
	}

	heap_refaz(0);

	if(debug){
		printf("lru:\n");
		uint i;
		for(i = 0; i < size_mem_fisica; i++){
			printf("%2d: %d, %d\n", i, heap[i], mem_virtual[heap[i]].ultimo_acesso);
		}
		getchar();
	}

	uint sai = heap[0];

	heap[0] = page;

	return sai;
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
