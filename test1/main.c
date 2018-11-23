#include <stdint.h>

__sfr __at 0x40 IO;

#define S_A 0x10
#define S_B 0x08
#define S_C 0x40
#define S_D 0x01
#define S_E 0x02
#define S_F 0x04
#define S_G 0x20

#define LED_1 0x40
#define LED_2 0x20
#define LED_3 0x10
#define LED_4 0x08
#define LED_5 0x04
#define LED_6 0x02
#define BEEP 0x01

const uint8_t hex[16] = {
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

volatile uint8_t tab[8];
volatile uint32_t cnt = 0;
volatile uint8_t rx_cnt = 0;
volatile uint8_t key = 0xFF;

void irq_vec(void)
{
	uint8_t v;
	uint8_t idx;
	
	v = IO;
	idx = (v+1) & 0x07;
	
	if ((v & 0x40))//Timer 4MHz/4096
	{
		cnt++;
	}

	if (((v & 0x80) == 0)&&((v & 0x40)==0))//Rx interrupt
	{
		rx_cnt++;
	}

	IO = tab[idx];//LCD

	/*Key board*/
	if ((v & 0x08) == 0)
		key = (v & 0x07);

	if ((v & 0x10) == 0)
		key = 0x08 + (v & 0x07);

	if (v & 0x20)
		key = 0x0F;

}

const char hexstr[] = "0123456789ABCDEF";

void putchar(char c)
{
	uint8_t i;
	uint16_t v = c;
	v = v >> 4;
	v &= 0x0FF0;
	v |= 0xF007;

	__asm;
	di
	__endasm;

	for(i=0;i<16;i++)
	{
		uint32_t j;

		for(j=0;j<20;j++)
		{
			__asm;
			nop
			__endasm;
		}

		if (v & (1 << i))
			IO = 0x80;
		else
			IO = 0x00;
	}

	__asm;
	ei
	__endasm;

}

void putstr(char *str)
{
	while(*str)
	{
		putchar(*str);
		str++;
	}
}


void main(void)
{
	uint8_t k = 0;
	uint32_t t = 0xFFFFFFFF;
	uint32_t t1 = 0;
	uint8_t bit = 0;

	putstr("Hello world\n");

	tab[0] = 0;//hex[0];
	tab[1] = 0;//hex[1];
	tab[2] = 0;//hex[2];
	tab[3] = 0;//hex[3];
	tab[4] = 0;//hex[4];
	tab[5] = hex[5];
	tab[6] = hex[6];
	tab[7] = 0;

	while(1)
	{
		uint32_t m = cnt/100;


		if (key != 0xFF)
		{
			switch(key)
			{
				case 0x00:
					cnt = 0;
				break;
				case 0x01:
					rx_cnt = 0;
				break;
				case 0x0A:
					__asm;
					jp #0x8000
					__endasm;
				break;
			}


			if ((t == 0xFFFFFFFF)&&(k != key))
			{
				putchar(hexstr[k]);

				tab[7] |= BEEP;
				t = cnt+5;
			}

			k = key;


			key = 0xFF;
		}

		if ((t != 0xFFFFFFFF) && (cnt > t))
		{
			t = 0xFFFFFFFF;
			tab[7] &= ~BEEP;
		}

		tab[0] = hex[k & 0x000F];

		tab[2] = hex[rx_cnt & 0x000F];

		tab[5] = hex[(m/10) & 0x000F];	
		tab[6] = hex[(m%10) & 0x000F];	

		if (cnt > t1)
		{
			t1 = cnt+100;
			tab[7] &= ~(1<<(6-bit));
			bit++;
			if (bit > 5)
				bit = 0;
			tab[7] |= (1<<(6-bit));

		}

	}

}
