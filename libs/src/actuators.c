#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/include/actuators.h"
#include "libs/include/definicoes.h"

// Função que liga e desliga os atuadores do setor A de acordo com a temperatura
void actuators_temperature_a(int temperature_a) {
    // Se a temperatura for menor que 29, ligam as lâmpadas
    if(temperature_a < 29){
        gpio_put(LED_RED, 1); // Liga a lampada
    } else if(temperature_a > 33){ // Se a temperatura for maior que 33, ligam os ventiladores
        gpio_put(LED_BLUE, 1); // Liga o ventilador
    } else { // Temperatura ideal, desliga tudo
        gpio_put(LED_RED, 0); // Desliga a lampada
        gpio_put(LED_BLUE, 0);   // Desliga o ventilador
    }
}

// Função que liga e desliga os atuadores do setor B de acordo com a temperatura
void actuators_temperature_b(int temperature_b) {
    // Se a temperatura for maior que 23, ligam os ventiladores
    if(temperature_b > 23){
        gpio_put(LED_GREEN, 1); // Liga o ventilador
    } else { // Temperatura ideal, desliga tudo
        gpio_put(LED_GREEN, 0); // Desliga o ventilador
    }
}

void actuators_humidity_a(int humidity_a) {
    if(humidity_a < 50){
        gpio_put(LED_RED, 1); // Liga os nebulizadores
    } else if(humidity_a > 70){
        gpio_put(LED_BLUE, 1); // Liga os exaustores
    } else {
        gpio_put(LED_RED, 0); // Desliga os nebulizadores
        gpio_put(LED_BLUE, 0); // Desliga os exaustores
    }
}

void actuators_humidity_b(int humidity_b) {
    if(humidity_b < 50){
        gpio_put(LED_GREEN, 1); // Liga os nebulizadores
    } else if(humidity_b > 70){
        gpio_put(LED_GREEN, 1); // Liga os exaustores
    } else {
        gpio_put(LED_GREEN, 0); // Desliga os nebulizadores
        gpio_put(LED_GREEN, 0); // Desliga os exaustores
    }
}