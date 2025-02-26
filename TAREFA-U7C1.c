#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "libs/include/temperature_humidity.h"
#include "libs/include/actuators.h"
#include "libs/include/ssd1306.h"
#include "libs/include/display_draw.h"
#include "libs/include/definicoes.h"


bool button_pressed = false; 
static volatile uint32_t last_time = 0;
int temp_a, temp_b, humi_a, humi_b;
uint16_t vrx, vry;

void initialize_gpio(int pin, bool direction); // Declaração da função de inicialização do pino
static void gpio_irq_handler(uint gpio, uint32_t events); // Declaração da função de tratamento de interrupção do botão
bool repeating_timer_callback(struct repeating_timer *timer); // Declaração da função de callback do timer
int main()
{
    stdio_init_all();

    // Inicializa o joystick
    adc_init(); 
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);

    initialize_gpio(BUTTON_A, GPIO_IN); // Inicializa o botão
    initialize_gpio(LED_RED, GPIO_OUT); // Inicializa o LED
    initialize_gpio(LED_BLUE, GPIO_OUT); // Inicializa o LED
    initialize_display(); // Inicializa o display

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler); // Configura a interrupção do botão

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer); // Inicializa o timer com 3 segundos de intervalo (na prática seria 15 minutos)

    while (true) {
        
        // Lê o eixo X do joystick (sensor de temperatura)
        adc_select_input(1);
        vrx = adc_read();
        sleep_ms(50);

        // Lê o eixo Y do joystick (sensor de umidade)
        adc_select_input(0);
        vry = adc_read();
        sleep_ms(50);
        
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
        gpio_put(LED_RED, 0);
        gpio_put(LED_BLUE, 0);
    }
}

bool repeating_timer_callback(struct repeating_timer *timer){

    if(!button_pressed){
        temp_a = check_temperature_a(vrx);
        humi_a = check_humidity_a(vry);
        draw_lines("ALA A");
        draw_temperature_a(temp_a);
        draw_humidity_a(humi_a);
        actuators_temperature_a(temp_a);
        actuators_humidity_a(humi_a);
    } else{
        draw_lines("ALA B");
        temp_b = check_temperature_b(vrx);
        draw_temperature_b(temp_b);
        humi_b = check_humidity_b(vry);
        draw_humidity_b(humi_b);
        actuators_temperature_b(temp_b);
        actuators_humidity_b(humi_b);
    }
    return true;
}