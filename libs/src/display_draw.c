#include "libs/include/ssd1306.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/include/definicoes.h"


ssd1306_t ssd;

// Inicializa o display
void initialize_display(){
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA,  GPIO_FUNC_I2C); // SDA
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // SCL
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ANDRESS, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

// Desenha linhas verticais e horizontais
void draw_lines(char *text){
    ssd1306_draw_string(&ssd, text, 48, 0);
    ssd1306_hline(&ssd, 0,127, 15, true);
    ssd1306_hline(&ssd, 0,127, 26, true);
    ssd1306_vline(&ssd, 64, 15, 63, true);
    ssd1306_send_data(&ssd);
}

// Desenha a umidade da ala A
void draw_humidity_a(int humidity_a){
    char humidity_a_value[6];
    snprintf(humidity_a_value, 6, "%d", humidity_a);
    ssd1306_draw_string(&ssd, "UMIDADE", 71, 17);
    ssd1306_draw_string(&ssd, humidity_a_value, 80, 36);
    ssd1306_draw_char(&ssd, '%', 98, 36);
    ssd1306_send_data(&ssd);
}

// Desenha a umidade da ala B
void draw_humidity_b(int humidity_b){
    char humidity_b_value[6];
    snprintf(humidity_b_value, 6, "%d", humidity_b);
    ssd1306_draw_string(&ssd, "UMIDADE", 71, 17);
    ssd1306_draw_string(&ssd, humidity_b_value, 80, 36);
    ssd1306_draw_char(&ssd, '%', 98, 36);
    ssd1306_send_data(&ssd);
}

// Desenha a temperatura da ala A
void draw_temperature_a(int temperature_a){
    char temperature_a_value[6];
    snprintf(temperature_a_value, 6, "%d", temperature_a);
    ssd1306_draw_string(&ssd, "TEMPER", 8, 17);
    ssd1306_draw_string(&ssd, temperature_a_value, 20, 36);
    ssd1306_draw_char(&ssd, 'C', 37, 36);
    ssd1306_send_data(&ssd);
}

// Desenha a temperatura da ala B
void draw_temperature_b(int temperature_b){
    char temperature_b_value[6];
    snprintf(temperature_b_value, 6, "%d", temperature_b);
    ssd1306_draw_string(&ssd, "TEMPER", 8, 17);
    ssd1306_draw_string(&ssd, temperature_b_value, 20, 36);
    ssd1306_draw_char(&ssd, 'C', 37, 36);
    ssd1306_send_data(&ssd);
}

