#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/include/actuators.h"
#include "libs/include/definicoes.h"
#include "libs/include/pioconfig.h"

// Função que liga e desliga os atuadores do setor A de acordo com a temperatura
void actuators_temperature_a(int temperature_a) {
    // Se a temperatura for menor que 29, ligam as lâmpadas
    if(temperature_a < 29){
        npSetLED(24,200,0,0); // Liga as lâmpadas
        npWrite();
    } else if(temperature_a > 33){ // Se a temperatura for maior que 33, ligam os ventiladores
        npSetLED(15,0,0,200); // Liga os ventiladores
        npWrite();
    } else { // Temperatura ideal, desliga tudo
        int leds[2] = {24,15};
        npSetManyLEDs(leds, 2, 0,0,0); // Mantém os ventiladores e lâmpadas desligados
        npWrite();
    }
}

// Função que liga e desliga os atuadores do setor B de acordo com a temperatura
void actuators_temperature_b(int temperature_b) {
    // Se a temperatura for maior que 23, ligam os ventiladores
    if(temperature_b > 23){
        npSetLED(20,200,0,0);  // Liga os ventiladores
        npWrite();
    } else { // Temperatura ideal, desliga tudo
        npSetLED(20,0,0,0); // Desliga os ventiladores
        npWrite();
 
    }
}

// Função que liga e desliga os atuadores do setor A de acordo com a umidade
void actuators_humidity_a(int humidity_a) {
    if(humidity_a < 50){
        npSetLED(5,200,0,0); // Liga os nebulizadores
        npWrite();
    } else if(humidity_a > 70){
        npSetLED(4,0,0,200); // Liga os exaustores
        npWrite();
    } else {
        int leds[2] = {5,4};
        npSetManyLEDs(leds, 2, 0,0,0); // Desliga os nebulizadores e exaustores
        npWrite(); 
    }
}

// Função que liga e desliga os atuadores do setor B de acordo com a umidade
void actuators_humidity_b(int humidity_b) {
    if(humidity_b < 50){
        npSetLED(9,200,0,0); // Liga os nebulizadores
        npWrite();
    } else if(humidity_b > 70){
        npSetLED(0,0,0,200); // Liga os exaustores
    } else {
        int leds[2] = {9,0};
        npSetManyLEDs(leds, 2, 0,0,0); // Desliga os nebulizadores e exaustores
        npWrite();
    }
}