
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdlib.h>
#include <stdio.h>
#include "hardware/clocks.h"
#include "microphone.h"

// Configuração do pino do buzzer
#define BUZZER_PIN 21

void pwm_init_buzzer() {
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_wrap(slice, 4096);

    // Vamos gerar PWM em ≈ 20 kHz
    float clkdiv = (float)clock_get_hz(clk_sys) / (30000 *4096);
    pwm_set_clkdiv(slice,clkdiv);
    pwm_set_enabled(slice, true); // Habilita o PWM no slice
    pwm_set_gpio_level(BUZZER_PIN, 0);
}

void play_buffer(uint16_t *buffer, float sample_rate) {
    const uint32_t period_us = (uint32_t)(1e6 / sample_rate);

    for (size_t i = 0; i < 110000; i++) {
        // passo 1: remove offset e centraliza em –128..+127
        int16_t pwm_value = abs(buffer[i]);

        // passo 4: ajusta no PWM (8 bits)
        pwm_set_gpio_level(BUZZER_PIN, pwm_value);

        // passo 5: espera o tempo da amostra (8 kHz, 16 kHz etc.)
        sleep_us(30); // 62.5 us para 16 kHz
        pwm_set_gpio_level(BUZZER_PIN, 0);
    }
    // ao fim, zera a saída
    pwm_set_gpio_level(BUZZER_PIN, 0);
}


