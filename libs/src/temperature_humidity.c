#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/include/temperature_humidity.h"


int temperature_a = 30; // Inicializa a temperatura com 30
int vrx_upper = 2300; // Define o valor do eixo X para iniciar o incremento 
int vrx_lower = 2000; // Define o valor do eixo X para iniciar o decremento 
int vry_upper = 2200; // Define o valor do eixo Y para iniciar o incremento 
int vry_lower = 1900; // Define o valor do eixo Y para iniciar o decremento

int check_temperature_a(uint16_t vrx) {
    if(vrx > vrx_upper){
        temperature_a++;
    } else if(vrx < vrx_lower){
        temperature_a--;
    }
    return temperature_a;
}

// Inicializa a temperatura com 22
int temperature = 22;
int check_temperature_b(uint16_t vry) {
    if(vry > vry_upper){
        temperature++;
    } else if(vry < vry_lower){
        temperature--;
    }
    return temperature;
}

// Inicializa a umidade em 52%
int humidity_a = 52;

int check_humidity_a(uint16_t vrx) {
    // Se o valor for maior que o limiar, aumenta a umidade
    if(vrx > vrx_upper) {
        humidity_a++;
    }
    // Se o valor for menor que o limiar, diminui a umidade
    else if(vrx < vrx_lower) {
        humidity_a--;
    }
    return humidity_a;
}


int humidity_b = 52;
int check_humidity_b(uint16_t vry) {
    // Se o valor for maior que o limiar, aumenta a umidade
    if(vry > vry_upper) {
        humidity_b++;
    }
    // Se o valor for menor que o limiar, diminui a umidade
    else if(vry < vry_lower) {
        humidity_b--;
    }
    return humidity_b;
}