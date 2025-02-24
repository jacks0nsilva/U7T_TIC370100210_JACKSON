#ifndef PIOCONFIG_H
#define PIOCONFIG_H

// Função para converter cores em formato RGB para o protocolo da matriz de LEDs
uint32_t matriz_rgb(uint8_t b, uint8_t r, uint8_t g);

// Inicializa a máquina PIO
void npInit(uint pin);

// Função para atribuar uma cor a um LED
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);

// Limpa o buffer de LEDs
void npClear();
// Escreve o buffer de LEDs no controlador
void npWrite();

// Atribui uma cor a vários LEDs
void npSetManyLEDs(uint *posicaoLEDs, size_t tamanhoVetor, uint8_t r, uint8_t g, uint8_t b);
#endif