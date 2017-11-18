#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

///Quantidade de caracteres por linha.
#define LEN 11
///Intervalo de tempo para zerar os bits de referenciado.
#define ZERO_TIME 1000

typedef enum CONTROLE {
	PRESENTE = 1,
	ALTERADO = 2,
	REFERENCIADO = 4
} CONTROLE;

typedef struct Moldura {
	int endereco;
	int ultimo_acesso;
	char controle;
}Moldura;

///Quantidade de páginas da memória virtual.
uint size_mem;

///Quantidade de páginas da memória física.
uint size_page;

///Memória virtual.
Moldura *mem_virtual;

///Memória física.
uint *mem_fisica;


/**
 * Estatística
 */

uint page_faults; ///Quantidade de page faults.
uint n_reads; ///Quantidades de leituras.
uint n_writes; ///Quantidade de escritas.
uint n_dirty_pages; ///Quantidade de páginas sujas.

///Tempo de relógio.
uint tempo;

//uint *lista;

///String para fazer o cache do arquivo.
char *acessos;

//TO-DO: não precisa ser global se usar ponteiro de função.
char *algoritmo;


/**
 * FUNÇÕES ÚTEIS
 */

///Retorna o tamano em bytes do arquivo.
int sizeArq(char *arquivo);

/**
 * Carrega o arquivo para a string acessos e retorna a quantidade de
 * linhas presentes no arquivo.
 */
uint leArquivo(char *arquivo);

///Percorre a memória zerando o bit R de cada página.
void zera_bit(void);

#endif //CORE_H