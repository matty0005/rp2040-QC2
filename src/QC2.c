#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "QC2.h"

#define DATA_PLUS 2
#define DATA_MINUS 3

static bool handshake_complete =false;

void handshake_init() {

    gpio_init(DATA_PLUS);
    gpio_init(DATA_MINUS);

    // Set high impeadance to reach 0.325v-2v crietia
    gpio_set_dir(DATA_PLUS, GPIO_IN);
    sleep_ms(1500);

    // Discharge D1
    gpio_set_dir(DATA_MINUS, GPIO_OUT);
    gpio_put(DATA_MINUS, 0);
    sleep_ms(2);

    handshake_complete = true;

}

void set_voltage(uint8_t voltage) {

    if (!handshake_complete) {
        handshake_init()
    }

    switch (voltage) {
        
        case QC_5V:
            gpio_set_dir(DATA_PLUS, GPIO_IN);
            gpio_set_dir(DATA_MINUS, GPIO_IN);

            break;

        case QC_9V:
            gpio_set_dir(DATA_PLUS, GPIO_OUT);

            gpio_set_dir(DATA_MINUS, GPIO_OUT);
            gpio_put(DATA_MINUS, 1);
            break;

        case QC_12V:

            gpio_set_dir(DATA_PLUS, GPIO_IN);

            gpio_set_dir(DATA_MINUS, GPIO_OUT);
            gpio_put(DATA_MINUS, 1);
            break;
    }
}
