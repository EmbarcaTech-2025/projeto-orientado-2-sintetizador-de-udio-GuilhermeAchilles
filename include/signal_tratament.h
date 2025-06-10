#ifndef SIGNAL_TRATAMENT_H
#define SIGNAL_TRATAMENT_H


#include <stdint.h>

void fir_media_movel_inplace(uint16_t *data, int len, int window_size);
void filtro_passa_baixa_10k_2ordem_inplace(int16_t *data, int len);
void remove_offset(int16_t *data, int len);
#endif //
