
#include "ui.h"

const uint8_t _hex[16] = {
				S_A|S_B|S_C|S_D|S_E|S_F,
				S_B|S_C,
				S_A|S_B|S_G|S_E|S_D,
				S_A|S_B|S_G|S_C|S_D,
				S_F|S_G|S_B|S_C,
				S_A|S_F|S_G|S_C|S_D,
				S_A|S_F|S_E|S_D|S_C|S_G,
				S_A|S_B|S_C,
				S_A|S_B|S_C|S_D|S_E|S_F|S_G,
				S_A|S_B|S_C|S_D|S_F|S_G,
				S_E|S_F|S_A|S_B|S_C|S_G,
				S_F|S_E|S_D|S_C|S_G,
				S_A|S_F|S_E|S_D,
				S_B|S_C|S_D|S_E|S_G,
				S_A|S_F|S_E|S_D|S_G,
				S_A|S_F|S_E|S_G,
};

volatile uint8_t _segments[8];
volatile uint8_t _key;

void ui_init()
{
	uint8_t i;
	for(i=0;i<8;i++)
		_segments[i] = 0;

	_key = 0xFF;
}

uint8_t ui_get_key()
{
	uint8_t tmp = _key;
	_key = UI_KEY_NONE;
	return tmp;
}

void ui_set_segment(uint8_t id, uint8_t segments)
{
	if (id > 6)
		return;

	_segments[id] = segments;
}

void ui_set_segment_hex(uint8_t id, uint8_t hex)
{
	ui_set_segment(id, _hex[hex & 0x0F]);
}

void ui_set_leds(uint8_t mask, uint8_t value)
{
	uint8_t tmp = _segments[7];

	tmp &= ~mask;
	tmp |= value;

	_segments[7] = tmp;
}

uint8_t ui_process(uint8_t ioport)
{
	uint8_t idx = (ioport+1) & 0x07;

		/*Key board*/
		if ((ioport & 0x08) == 0)
			_key = (ioport & 0x07);

		if ((ioport & 0x10) == 0)
			_key = 0x08 + (ioport & 0x07);

		if (ioport & 0x20)
			_key = 0x0F;

	return _segments[idx];
}