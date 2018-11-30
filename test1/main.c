#include <stdint.h>

#include "ui.h"

__sfr __at 0x40 IO;

volatile uint32_t _ticks = 0;
volatile uint8_t _rx_cnt = 0;

void irq_vec(void)
{
	uint8_t v = IO;
	
	if ((v & 0x40))//Timer 4MHz/4096 ~ 1.024ms
	{
		IO = ui_process(v);
		_ticks++;
	}

	if (((v & 0x80) == 0)&&((v & 0x40)==0))//Rx interrupt
	{
		_rx_cnt++;
	}
}


void main(void)
{
	/* Led animation */
	const uint8_t leds[] = {
		UI_LED_1_ORANGE,
		UI_LED_2_ORANGE,
		UI_LED_3_RED,
		UI_LED_4_RED,
		UI_LED_5_GREEN,
		UI_LED_6_GREEN,
		UI_LED_5_GREEN,
		UI_LED_4_RED,
		UI_LED_3_RED,
		UI_LED_2_ORANGE,
	};
	uint8_t led = 0;


	uint32_t timer1 = 0;
	uint32_t timer2 = 0;

	ui_init();

	while(1)
	{
		uint8_t k;
	
		/* Print _ticks % 1000, in 10ms */
		uint32_t c = _ticks % 1000;
		uint8_t c100, c10;
		c100 = c / 100;
		c -= c100 * 100;
		c10 = c / 10;

		ui_set_segment_hex(5, c100);
		ui_set_segment_hex(6, c10);


		/* Print _rx_cnt counter in hexa */
		ui_set_segment_hex(2, (_rx_cnt >> 4) & 0x0F);
		ui_set_segment_hex(3, (_rx_cnt >> 0) & 0x0F);


		/* Test keys */
		k = ui_get_key();

		if (k != UI_KEY_NONE)
		{
			ui_set_segment_hex(0, k);
			ui_set_leds(UI_LED_7_BUZZER, UI_LED_7_BUZZER);
			timer2 = _ticks + 50;
		}

		if (_ticks >= timer2)
		{
			ui_set_leds(UI_LED_7_BUZZER, 0);
		}

		if (_ticks >= timer1)
		{
			timer1 = _ticks + 100;

			ui_set_leds(UI_LED_ALL, leds[led]);
			led++;
			if (led >= sizeof(leds))
				led = 0;
		}
	}
}
