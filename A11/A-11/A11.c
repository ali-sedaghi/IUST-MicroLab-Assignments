// Ali Sedaghi
// 97521378

#include <mega32.h>
#include <i2c.h>
#include <ds1307.h>
#include <alcd.h>
#include <stdlib.h>
#include <delay.h>

unsigned char _hour, _min, _sec;
unsigned char week_day, _day,_month,_year;
unsigned char* s1;
unsigned char* s2;
unsigned char* s3;
unsigned char* s4;
unsigned char* s5;
unsigned char* s6;

void main(void) {	
	PORTA = 0x00;
	DDRA = 0x00;
	PORTB = 0x00;
	DDRB = 0x00;
	PORTC = 0x00;
	DDRC = 0x00;
	PORTD = 0x00;
	DDRD = 0x00;

	i2c_init();
	rtc_init(0, 0, 0);
	lcd_init(20);
	
	while (1) {
		lcd_clear();
		
		//lcd_gotoxy(0, 0);
		lcd_puts("TIME> ");
		lcd_gotoxy(0, 1);
		lcd_puts("DATE> ");
		
		rtc_get_time(&_hour, &_min, &_sec);
		rtc_get_date(&week_day, &_day, &_month, &_year);
		
		// Display Time
		lcd_gotoxy(6, 0);
		
		itoa(_hour, s1);
		lcd_puts(s1);
		lcd_putsf(" ");
		
		itoa(_min, s2);
		lcd_puts(s2);
		lcd_putsf(" ");
		
		itoa(_sec, s3);
		lcd_puts(s3);
		
		// Display Date      
		lcd_gotoxy(6, 1);
		
		itoa(_day, s4);
		lcd_puts(s4);
		lcd_putsf(" ");
		
		itoa(_month, s5);
		lcd_puts(s5);
		lcd_putsf(" ");
		
		lcd_putsf("20");
		itoa(_year, s6);
		lcd_puts(s6);
		
		// Display my name
		lcd_gotoxy(0, 2);
        lcd_putsf("Ali Sedaghi");
        
        delay_ms(1000);
    }
}
