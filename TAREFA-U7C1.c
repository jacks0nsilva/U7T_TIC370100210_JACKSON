#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "libs/include/temperature_humidity.h"
#include "libs/include/actuators.h"
#include "libs/include/ssd1306.h"
#include "libs/include/display_draw.h"
#include "libs/include/definicoes.h"

bool button_pressed = false;
static volatile uint32_t last_time = 0;

void initialize_gpio(int pin, bool direction); // Declaração da função de inicialização do pino
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    adc_init();
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);

    initialize_gpio(LED_RED, GPIO_OUT);
    initialize_gpio(LED_BLUE, GPIO_OUT);
    initialize_gpio(LED_GREEN, GPIO_OUT);
    initialize_gpio(BUTTON_A, GPIO_IN);

    initialize_display();

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        
        // Sensor de temperatura da ala A
        adc_select_input(1);
        uint16_t vrx = adc_read();
        sleep_ms(100);


        adc_select_input(0);
        uint16_t vry = adc_read();
        sleep_ms(100);
        

        if(!button_pressed){
            draw_lines("NIVEL TEMP");

            int temperature_a = check_temperature_a(vrx);
            // Se a temperatura for menor que 29, liga a lampada
            // Se a temperatura for maior que 33, liga o ventilador
            actuators_temperature_a(temperature_a);
            draw_temperature_a(temperature_a);


            int temperature_b = check_temperature_b(vry);
            actuators_temperature_b(temperature_b);

            draw_temperature_b(temperature_b);
        } else{
            draw_lines("NIVEL UMIDADE");

            int humidity_a = check_humidity_a(vrx);
            actuators_humidity_a(humidity_a);
            draw_humidity_a(humidity_a);
 

            int humidity_b = check_humidity_b(vry);
            actuators_humidity_b(humidity_b);
            draw_humidity_b(humidity_b);
        }
        sleep_ms(100); // Pausa para evitar sobrecarga do processador
        //printf("Temperatura A: %d | VRX: %d | \t Temperatura: B %d \n", temperature_a, vrx, temperature_b);
        //printf("Posição x: %d | Posição y: %d\n", vrx, vry);
    }
}

void initialize_gpio(int pin, bool direction) {
    gpio_init(pin);
    gpio_set_dir(pin, direction);
    if(direction == GPIO_IN){
        gpio_pull_up(pin);
    } else if(direction == GPIO_OUT){
        gpio_put(pin, 0);
    }
}

static void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if(current_time - last_time > 200000){
        last_time = current_time;
        button_pressed = !button_pressed;
        gpio_put(LED_RED, 0);
        gpio_put(LED_GREEN, 0);
        gpio_put(LED_BLUE, 0);
    }
}