#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

void pwm_init_buzzer();
void play_buffer(uint16_t *buffer, float sample_rate);


#endif // BUZZER_H
