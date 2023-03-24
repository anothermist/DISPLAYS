#include "main.h"

int main(void) {
	
	twi_init();
	lcd_twi_init();
	
	lcd_twi_string("LCD STRING 0 3", 0, 3);
	lcd_twi_string("LCD STRING 1 3", 1, 3);
	_delay_ms(1000);
	lcd_twi_clear();
	
	unsigned int rtc_Hrs = 12;
	unsigned int rtc_Min = 45;
	
	lcd_twi_drawBigDigits(rtc_Hrs/10, 0);
	lcd_twi_drawBigDigits(rtc_Hrs % 10, 4);
	lcd_twi_drawBigDigits(rtc_Min/10, 9);
	lcd_twi_drawBigDigits(rtc_Min % 10, 13);
	
	while (1) {
		lcd_twi_string("* ", 0, 7);
		lcd_twi_string(" *", 1, 7);
		_delay_ms(1000);
		lcd_twi_string(" *", 0, 7);
		lcd_twi_string("* ", 1, 7);
		_delay_ms(1000);
	}
}

