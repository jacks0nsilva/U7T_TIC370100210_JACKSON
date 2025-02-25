#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "libs/include/temperature_humidity.h"
#include "libs/include/actuators.h"
#include "libs/include/ssd1306.h"
#include "libs/include/display_draw.h"
#include "libs/include/definicoes.h"
#include "libs/include/pioconfig.h"

bool button_pressed = true; 
static volatile uint32_t last_time = 0;

void initialize_gpio(int pin, bool direction); // Declaração da função de inicialização do pino
static void gpio_irq_handler(uint gpio, uint32_t events); // Declaração da função de tratamento de interrupção do botão

int main()
{
    stdio_init_all();

    // Inicializa o joystick
    adc_init(); 
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);

    initialize_gpio(BUTTON_A, GPIO_IN); // Inicializa o botão

    initialize_display(); // Inicializa o display

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Configura a interrupção do botão
    npInit(MATRIZ_LEDS); // Inicializa o pino da matriz de LEDs

    while (true) {
        
        // Lê o eixo X do joystick
        adc_select_input(1);
        uint16_t vrx = adc_read();
        sleep_ms(50);

        // Lê o eixo Y do joystick
        adc_select_input(0);
        uint16_t vry = adc_read();
        sleep_ms(50);
        
        if(!button_pressed){
            draw_lines("ALA A");
            int temperature_a = check_temperature_a(vrx);
            actuators_temperature_a(temperature_a);
            draw_temperature_a(temperature_a);

            int humidity_a = check_humidity_a(vry);
            actuators_humidity_a(humidity_a);
            draw_humidity_a(humidity_a);
        } else{
            draw_lines("ALA B");
            int temperature_b = check_temperature_b(vrx);
            actuators_temperature_b(temperature_b);
            draw_temperature_b(temperature_b);

            int humidity_b = check_humidity_b(vry);
            actuators_humidity_b(humidity_b);
            draw_humidity_b(humidity_b);
        }
        sleep_ms(100); // Pausa para evitar sobrecarga do processador
    }
}

// Função de inicialização do gpio
void initialize_gpio(int pin, bool direction) {
    gpio_init(pin);
    gpio_set_dir(pin, direction);
    if(direction == GPIO_IN){
        gpio_pull_up(pin);
    } else if(direction == GPIO_OUT){
        gpio_put(pin, 0);
    }
}

// Função de tratamento de interrupção do botão
static void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if(current_time - last_time > 200000){
        last_time = current_time;
        button_pressed = !button_pressed;
    }
}