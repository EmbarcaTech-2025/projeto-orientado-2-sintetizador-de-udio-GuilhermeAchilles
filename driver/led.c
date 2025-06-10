#include "pico/stdlib.h"

void init_led(){

    gpio_init(13);
    gpio_init(11);

}

void led_on(uint gpio) {
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 1);
}

void led_off(uint gpio) {
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 0);
}