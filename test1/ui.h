#ifndef _UI_H_
#define _UI_H_

#include <stdint.h>

#define S_A 0x10
#define S_B 0x08
#define S_C 0x40
#define S_D 0x01
#define S_E 0x02
#define S_F 0x04
#define S_G 0x20

#define UI_LED_1_ORANGE 0x40
#define UI_LED_2_ORANGE 0x20
#define UI_LED_3_RED 0x10
#define UI_LED_4_RED 0x08
#define UI_LED_5_GREEN 0x04
#define UI_LED_6_GREEN 0x02
#define UI_LED_7_BUZZER 0x01
#define UI_LED_ALL 0x7F

#define UI_KEY_NONE 0xFF

void ui_init();
uint8_t ui_process(uint8_t ioport);
void ui_set_segment(uint8_t id, uint8_t segments);
void ui_set_segment_hex(uint8_t id, uint8_t hex);
uint8_t ui_get_key();
void ui_set_leds(uint8_t mask, uint8_t value);

#endif//_UI_H_