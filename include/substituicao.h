#ifndef SUBSTITUICAO_H
#define SUBSTITUICAO_H

#include <time.h>
#include "core.h"

uint sub_fifo(uint page);

uint sub_lru(uint page);

uint sub_random(uint page);

void substituicao(uint page);

#endif //SUBSTITUICAO_H
