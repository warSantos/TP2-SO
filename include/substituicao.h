#ifndef SUBSTITUICAO_H
#define SUBSTITUICAO_H

#include <stdint.h>
#include <time.h>
#include "core.h"

uint sub_fifo(uint page);

uint sub_lru(uint page);

uint sub_lru_h(uint page);

uint sub_random(uint page);

///Ponteiro de função usado para chamar a função de substituição correta.
uint (*politica)(uint);

void substituicao(uint page);

#endif //SUBSTITUICAO_H
