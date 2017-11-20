#ifndef SUBSTITUICAO_H
#define SUBSTITUICAO_H

#include <stdint.h>
#include <time.h>
#include "core.h"

///Ponteiro de função usado para chamar a função de substituição correta.
uint (*politica)(uint);

uint sub_fifo(uint page);

uint sub_lru(uint page);

uint sub_random(uint page);

void substituicao(uint page);

#endif //SUBSTITUICAO_H
