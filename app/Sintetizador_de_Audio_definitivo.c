#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/dma.h"
#include "driver/neopixel.c"
#include "signal_tratament.h"
#include "led.h"
#include "write_display.h"
#include "microphone.h"
#include "buzzer.h"
#include "button.h"
#include "show_display.h"

void mostrar_menu(void);
void iniciando_gravacao(void);

int main()
{

  stdio_init_all();
  pwm_init_buzzer();
  init_display();
  init_buttons();
  init_mic(22000.0f);
  init_dma();
  init_led();

  init_button_interrupts();
  clear_display();
  

  while (true) {
    
    led_on(13);
    mostrar_menu();
    printf("Estado do Botão A: %d\n", gpio_get(BUTTON_A));

    if(button_a_nivel == 1){
      button_a_nivel = 0;
      deinit_button_interrupts();
      led_off(13);
      contagem_regressiva(5);
      led_on(11);
      inicando_gravacao();
      led_off(11);
      remove_offset(adc_buffer, 110000);
      filtro_passa_baixa_10k_2ordem_inplace(adc_buffer, 110000);
      init_button_interrupts();
    }
    if(button_b_nivel == 1){
      button_b_nivel = 0;
      deinit_button_interrupts();
      led_off(13);
      clear_display();
      char *text_reproduzindo[] = {"Reproduzindo..."}; 
      write_string(text_reproduzindo, 0, 0, 1);
      show_display();
      preparar_grafico_display(adc_buffer);
      play_buffer(adc_buffer, 8000.0f);
      init_button_interrupts();
    }

  }

  return 0;
}


void mostrar_menu(void){
    char *text_menu_1[] = {"Gravar - Aperkte A"};
    char *text_menu_2[] = {"Reproduzir - Aperte B"};

    clear_display();
    write_string(text_menu_1, 0, 0, 1);
    write_string(text_menu_2,0,10,1);
    show_display();
}

void contagem_regressiva(int segundos) {
    for (int i = segundos; i > 0; i--) {  
    printf("Contagem regressiva: %d segundos\n", i);
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Iniciando em : %d", i);
        char *text_contagem[] = {buffer};
        clear_display();
        write_string(text_contagem,15,32, 1);
        show_display();
        led_on(11);
        sleep_ms(500);
        led_off(11);
        sleep_ms(500);
    }
    clear_display();
}

void inicando_gravacao(void) {
    char *text_gravando[] = {"Gravando..."};
    clear_display();
    write_string(text_gravando, 0, 0, 1);
    show_display();
    sample_mic();
}