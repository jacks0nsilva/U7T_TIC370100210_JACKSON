#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "libs/include/temperature_humidity.h"
#include "libs/include/actuators.h"

#define VRX_PIN 27 
#define VRY_PIN 26 
#define SW_PIN 22

bool button_pressed = true;

int main()
{
    stdio_init_all();

    adc_init();
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);

    gpio_init(13); // Lampadas ala A
    gpio_set_dir(13, GPIO_OUT);
    gpio_put(13, 0);

    gpio_init(12); // Ventilador ala A
    gpio_set_dir(12, GPIO_OUT);
    gpio_put(12, 0);

    gpio_init(11); // Ventilador ala B
    gpio_set_dir(11, GPIO_OUT);
    gpio_put(11, 0);

    while (true) {
        
        // Sensor de temperatura da ala A
        adc_select_input(1);
        uint16_t vrx = adc_read();
        sleep_ms(100);


        adc_select_input(0);
        uint16_t vry = adc_read();
        sleep_ms(100);
        

        if(!button_pressed){
            int temperature_a = check_temperature_a(vrx);
            // Se a temperatura for menor que 29, liga a lampada
            // Se a temperatura for maior que 33, liga o ventilador
            actuators_temperature_a(temperature_a);

            int temperature_b = check_temperature_b(vry);
            actuators_temperature_b(temperature_b);
        } else{
            int humidity_a = check_humidity_a(vrx);
            actuators_humidity_a(humidity_a);
            printf("Umidade A: %d\n", humidity_a);

            int humidity_b = check_humidity_b(vry);
            actuators_humidity_b(humidity_b);
            printf("Umidade B: %d\n", humidity_b);
        }


        



        



        //printf("Temperatura A: %d | VRX: %d | \t Temperatura: B %d \n", temperature_a, vrx, temperature_b);
        //printf("Posição x: %d | Posição y: %d\n", vrx, vry);
    }
}

