#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "write_display.h"

#define TOTAL_AMOSTRAS    110000
#define DISPLAY_WIDTH     128
#define DISPLAY_HEIGHT    64
#define DISPLAY_CENTER_Y  (DISPLAY_HEIGHT/2)

void preparar_grafico_display(const int16_t *dados) {
    clear_display();

    // 1) Pico global absoluto para normalização de magnitude
    int16_t pico_global = 1;
    for (int i = 0; i < TOTAL_AMOSTRAS; i++) {
        int16_t a = abs(dados[i]);
        if (a > pico_global) pico_global = a;
    }

    // 2) Tamanho do bloco
    const int bloco = TOTAL_AMOSTRAS / DISPLAY_WIDTH;

    // 3) Para cada coluna...
    for (int col = 0; col < DISPLAY_WIDTH; col++) {
        int base = col * bloco;

        // 3.1) Soma simples para sinal médio (direção)
        int32_t soma = 0;
        // 3.2) Soma dos quadrados para RMS (magnitude)
        float soma2 = 0.0f;

        for (int j = 0; j < bloco; j++) {
            int16_t v = dados[base + j];
            soma  += v;
            soma2 += (float)v * (float)v;
        }

        // 3.3) Calcula média simples para sinal
        float media_simples = (float)soma / bloco;
        int   direcao      = (media_simples >= 0.0f) ? +1 : -1;

        // 3.4) Calcula RMS para magnitude
        float rms = sqrtf(soma2 / bloco);

        // 3.5) Normaliza RMS em ±31 pixels
        float altura_f = rms * 31.0f / (float)pico_global;
        int   altura_i = (int)roundf(altura_f);
        if (altura_i > DISPLAY_CENTER_Y) altura_i = DISPLAY_CENTER_Y;

        // 4) Decide coordenadas de desenho
        int y0 = (direcao > 0)
                 ? (DISPLAY_CENTER_Y - altura_i)  // parte para cima
                 : (DISPLAY_CENTER_Y);            // parte para baixo
        int h  = altura_i;

        // 5) Desenha com largura 1px
        draw_bar(col, y0, 1, h);

        // Debug (opcional)
        // printf("col %3d: media=%.1f  rms=%.1f  dir=%d  alt=%d\n",
        //        col, media_simples, rms, direcao, altura_i);
    }
    write_line(0,32,128,32);
    show_display();
}
