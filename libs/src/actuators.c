#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/include/actuators.h"
#include "libs/include/definicoes.h"


// Função que liga e desliga os atuadores do setor A de acordo com a temperatura
void actuators_temperature_a(int temperature_a) {
    // Se a temperatura for menor que 29, ligam as campânulas 
    if(temperature_a < 29){
        gpio_put(LED_RED, 1); // Liga as campânulas
    } else if(temperature_a > 33){ // Se a temperatura for maior que 33, ligam os ventiladores
        gpio_put(LED_RED, 1); // Liga os ventiladores
    } else { // Temperatura ideal, desliga tudo
        gpio_put(LED_RED, 0); 
    }
}

// Função que liga e desliga os atuadores do setor B de acordo com a temperatura
void actuators_temperature_b(int temperature_b) {
    // Se a temperatura for maior que 28, ligam os ventiladores
    if(temperature_b > 28){
        gpio_put(LED_RED, 1); // Liga os ventiladores
    } else { // Temperatura ideal, desliga tudo
        gpio_put(LED_RED, 0); // Desliga os ventiladores
    }
}

// Função que liga e desliga os atuadores do setor A de acordo com a umidade
void actuators_humidity_a(int humidity_a) {
    if(humidity_a < 50){
        gpio_put(LED_BLUE, 1); // Liga os nebulizadores
    } else if(humidity_a > 70){
        gpio_put(LED_BLUE, 1); // Liga os exaustores
    } else {
        gpio_put(LED_BLUE, 0); // Desliga os nebulizadores e exaustores
    }
}

// Função que liga e desliga os atuadores do setor B de acordo com a umidade
void actuators_humidity_b(int humidity_b) {
    if(humidity_b < 50){
        gpio_put(LED_BLUE, 1); // Liga os nebulizadores
    } else if(humidity_b > 70){
        gpio_put(LED_BLUE, 1); // Liga os exaustores
    } else {
        gpio_put(LED_BLUE, 0); // Desliga os nebulizadores e exaustores
    }
}