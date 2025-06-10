#ifndef MICROPHONE_H
#define MICROPHONE_H

#include <stdint.h>
#include "hardware/dma.h"
#include "microphone.h"

// ===============================
// Definições dos pinos e canais
// ===============================
#define MIC_CHANNEL 2
#define MIC_PIN 28

// ===============================
// Parâmetros e macros do ADC
// ===============================
#define SAMPLES 110000
// ===============================
// Variáveis globais
// ===============================
extern uint dma_channel;
extern dma_channel_config dma_cfg;

extern uint16_t adc_buffer[SAMPLES];

void init_mic(float sample_rate);
void init_dma(void);
int one_sample (void);
void sample_mic(void);

#endif // MICROPHONE_H
