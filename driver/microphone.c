#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"

// Pino e canal do microfone no ADC.
#define MIC_CHANNEL 2
#define MIC_PIN 28

// Parâmetros e macros do ADC.

#define SAMPLES 110000

// Calanal e Configurações do DMA
uint dma_channel;
dma_channel_config dma_cfg;

// Buffer de amostras do ADC.
uint16_t adc_buffer[SAMPLES];

void init_mic(float sample_rate)
{
    adc_gpio_init(MIC_PIN);
    adc_init();
    adc_select_input(MIC_CHANNEL);

    adc_fifo_setup(
        true,  // habilitar FIFO
        true,  // habilitar request de dados do DMA
        1,     // trigger DMA a cada 1 amostra
        false, // sem bit de erro
        false  // manter 12 bits
    );

    // Clock interno atual (clk_adc = clk_sys / clkdiv_atual)
    float adc_clock = (float)clock_get_hz(clk_adc); 
    // Novo divisor: inclui o fator 96 ciclos/conv
    float div = adc_clock / (sample_rate);

    printf("Clock do ADC: %.0f Hz\n", adc_clock);
    printf("Divisor calculado: %f\n", div);
    adc_set_clkdiv(div);

    printf("ADC configurado para %.0f amostras/s\n\n", sample_rate);
}


void init_dma(void)
{
    printf("Preparando DMA...");

    dma_channel = dma_claim_unused_channel(true);
    dma_cfg = dma_channel_get_default_config(dma_channel);

    channel_config_set_transfer_data_size(&dma_cfg,DMA_SIZE_16);
    channel_config_set_read_increment(&dma_cfg, false);
    channel_config_set_write_increment(&dma_cfg, true);
    channel_config_set_dreq(&dma_cfg, DREQ_ADC);

    printf("DMA Configurado!\n");

}

int one_sample (void){
    adc_select_input(MIC_CHANNEL); // Seleciona o canal do microfone
    return adc_read(); // Lê o valor do ADC
}

void sample_mic(void)
{
    adc_fifo_drain(); // Limpa o FIFO do ADC
    adc_run(false); // Desliga o ADC (se estiver ligado) para configurar o DMA);
    dma_channel_configure(dma_channel, &dma_cfg,
                          adc_buffer, // Escreve no buffer
                          &(adc_hw->fifo), // Lê do ADC
                          SAMPLES, // Faz SAMPLES amostras
                          true // Liga o DMA
    );
    adc_run(true);
    dma_channel_wait_for_finish_blocking(dma_channel);
    adc_run(false);
}






