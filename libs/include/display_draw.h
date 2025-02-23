#ifndef DISPLAY_DRAW_H
#define DISPLAY_DRAW_H

void draw_humidity_a(int humidity_a);
void draw_humidity_b(int humidity_b);
void draw_temperature_a(int temperature_a);
void draw_temperature_b(int temperature_b);


void initialize_display();
void draw_lines(char *text);
#endif