#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/include/temperature_humidity.h"

// Inicializa a temperatura com 30
int temperature_a = 30;

int check_temperature_a(uint16_t vrx) {
    if(vrx > 2047){
        temperature_a++;
    } else if(vrx < 2047){
        temperature_a--;
    }
    return temperature_a;
}

// Inicializa a temperatura com 22
int temperature = 22;
int check_temperature_b(uint16_t vry) {
    if(vry > 2047){
        temperature++;
    } else if(vry < 2047){
        temperature--;
    }
    return temperature;
}

// Inicializa a umidade em 50%
int humidity_a = 50;

int check_humidity_a(uint16_t vrx) {
    // Se o valor for maior que o limiar, aumenta a umidade
    if(vrx > 2047) {
        humidity_a++;
    }
    // Se o valor for menor que o limiar, diminui a umidade
    else if(vrx < 2047) {
        humidity_a--;
    }
    return humidity_a;
}


int humidity_b = 50;
int check_humidity_b(uint16_t vry) {
    // Se o valor for maior que o limiar, aumenta a umidade
    if(vry > 2047) {
        humidity_b++;
    }
    // Se o valor for menor que o limiar, diminui a umidade
    else if(vry < 2047) {
        humidity_b--;
    }
    return humidity_b;
}