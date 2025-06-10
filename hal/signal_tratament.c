
#include <stdint.h>
#include <stdlib.h>

void fir_media_movel_inplace(uint16_t *data, int len, int window_size) {
    for (int i = window_size - 1; i < len; i++) {
        uint32_t sum = 0;
        for (int j = 0; j < window_size; j++) {
            sum += data[i - j];
        }
        data[i - (window_size - 1)] = sum / window_size;
    }

    for (int i = len - window_size + 1; i < len; i++) {
        data[i] = data[len - window_size];
    }
}


void filtro_passa_baixa_10k_inplace(int16_t *data, int len) {
    if (len < 1) return;
    
    // Coeficiente para fc ≈ 10kHz @ fs = 22kHz
    // alpha = 0.35 (aproximadamente)
    // y[n] = alpha*x[n] + (1-alpha)*y[n-1]
    
    const int32_t alpha = 350;      // 0.35 * 1000
    const int32_t one_minus_alpha = 650;  // 0.65 * 1000
    
    int32_t prev_output = data[0];  // Inicializa com primeira amostra
    
    for (int i = 1; i < len; i++) {
        // Filtro RC: y[n] = alpha*x[n] + (1-alpha)*y[n-1]
        int32_t output = (alpha * data[i] + one_minus_alpha * prev_output) / 1000;
        
        // Saturação
        if (output > 32767) output = 32767;
        if (output < -32768) output = -32768;
        
        data[i] = (int16_t)output;
        prev_output = output;
    }
}

/**
 * @brief Filtro passa-baixa de 2ª ordem (mais suave)
 *        Frequência de corte: ~10kHz @ 22kHz
 *        Processa in-place (modifica o vetor original)
 * 
 * @param data    Vetor de amostras int16_t (entrada e saída)
 * @param len     Número de amostras no vetor
 */
void filtro_passa_baixa_10k_2ordem_inplace(int16_t *data, int len) {
    if (len < 1) return;

    // Coeficientes (fixed-point Q3: a0=1000 representa 1.0, b0=67 representa 0.067, etc.)
    const int32_t a0 = 1000;    // divisor
    const int32_t a1 = -1143;   // –1.143 * a0
    const int32_t a2 =  413;    //  0.413 * a0
    const int32_t b0 =   67;    //  0.067 * a0
    const int32_t b1 =  134;    //  0.134 * a0
    const int32_t b2 =   67;    //  0.067 * a0

    // Estados (amostras anteriores) iniciados em zero
    int32_t x1 = 0, x2 = 0;
    int32_t y1 = 0, y2 = 0;

    for (int i = 0; i < len; i++) {
        int32_t x0 = data[i];

        // y[n] = (b0*x0 + b1*x1 + b2*x2 - a1*y1 - a2*y2) / a0
        int32_t acc =  b0 * x0
                    + b1 * x1
                    + b2 * x2
                    - a1 * y1
                    - a2 * y2;

        int32_t y0 = acc / a0;

        // Saturação para 12 bits (–2048…+2047)
        if      (y0 >  2047) y0 =  2047;
        else if (y0 < -2048) y0 = -2048;

        // Atualiza estado e sobrescreve data[i]
        data[i] = (int16_t)y0;

        x2 = x1;
        x1 = x0;
        y2 = y1;
        y1 = y0;
    }
}

void remove_offset(int16_t *data, int len) {
    if (len < 1) return;

    // Calcula o offset (média)
    int32_t sum = 0;
    for (int i = 0; i < len; i++) {
        sum += data[i];
    }
    int16_t offset = sum / len;

    // Subtrai o offset de cada amostra
    for (int i = 0; i < len; i++) {
        data[i] = 2*(data[i]-offset);
    }
}
