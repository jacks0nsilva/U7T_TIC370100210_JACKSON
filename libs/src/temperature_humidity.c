#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/include/temperature_humidity.h"



int vrx_upper = 4000; // Define o valor do eixo X para iniciar o incremento 
int vrx_lower = 100; // Define o valor do eixo X para iniciar o decremento 
int vry_upper = 4000; // Define o valor do eixo Y para iniciar o incremento 
int vry_lower = 100; // Define o valor do eixo Y para iniciar o decremento


int temperature_a = 30; // Inicializa a temperatura com 30C
// Função para definir a temperatura do setor A
int check_temperature_a(uint16_t vrx) {
    if(vrx > vrx_upper){
        temperature_a += 4;
    } else if(vrx < vrx_lower){
        temperature_a -= 4;
    }
    return temperature_a;
}


int temperature = 24; // Inicializa a temperatura com 24C
// Função para definir a temperatura do setor B
int check_temperature_b(uint16_t vry) {
    if(vry > vry_upper){
        temperature+= 6;
    } else if(vry < vry_lower){
        temperature-= 6;
    }
    return temperature;
}


int humidity_a = 60; // Inicializa a umidade em 60%
// Função para definir a umidade do setor A
int check_humidity_a(uint16_t vrx) {
    // Se o valor for maior que o limiar, aumenta a umidade
    if(vrx > vrx_upper) {
        humidity_a += 10;
    }
    // Se o valor for menor que o limiar, diminui a umidade
    else if(vrx < vrx_lower) {
        humidity_a -= 10;
    }
    return humidity_a;
}


int humidity_b = 60; // Inicializa a umidade em 60%
// Função para definir a umidade do setor B
int check_humidity_b(uint16_t vry) {
    // Se o valor for maior que o limiar, aumenta a umidade
    if(vry > vry_upper) {
        humidity_b += 10;
    }
    // Se o valor for menor que o limiar, diminui a umidade
    else if(vry < vry_lower) {
        humidity_b -= 10;
    }
    return humidity_b;
}