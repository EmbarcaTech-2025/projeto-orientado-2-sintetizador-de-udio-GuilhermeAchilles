# Projetos de Sistemas Embarcados - EmbarcaTech 2025

Autor: **Guilherme Achilles de Oliveira e Aguiar**  
Curso: Residência Tecnológica em Sistemas Embarcados  
Instituição: EmbarcaTech - HBr  
Brasília, 09/05 de 2025

# 🎙️ Sintetizador de Áudio com Raspberry Pi Pico

Este projeto implementa um **sintetizador de áudio digital** utilizando o **Raspberry Pi Pico**. A partir de sinais capturados por um microfone, o sistema realiza o tratamento do sinal e gera uma resposta sonora por meio de um buzzer, com feedback visual em um display OLED. O sistema também conta com botões de controle e LEDs para interação e sinalização. 

Todo o projeto foi modularizado para facilitar o desenvolvimento, testes e manutenção do código.

## 📂 Estrutura do Projeto

.
├── app
│ └── Sintetizador_de_Audio_definitivo.c
├── driver
│ ├── button.c
│ ├── buzzer.c
│ ├── led.c
│ ├── microphone.c
│ ├── neopixel.c
│ ├── ssd1306.c
│ ├── ssd1306_i2c.c
│ └── ws2818b.pio
├── hal
│ ├── show_display.c
│ ├── signal_tratament.c
│ └── write_display.c
├── include
│ ├── button.h
│ ├── buzzer.h
│ ├── font.h
│ ├── led.h
│ ├── microphone.h
│ ├── show_display.h
│ ├── signal_tratament.h
│ ├── ssd1306.h
│ ├── ssd1306_font.h
│ ├── ssd1306_i2c.h
│ └── write_display.h
├── CMakeLists.txt
├── pico_sdk_import.cmake
└── .gitignore
