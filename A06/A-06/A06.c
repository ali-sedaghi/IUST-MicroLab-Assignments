// Ali Sedaghi
// 97521378

#include <mega32.h>
#include <alcd.h>
#include <delay.h>

// Init time
unsigned int hour = 23;
unsigned int minute = 58;
unsigned int second = 0;
unsigned int ms = 0;

unsigned char int_to_char(unsigned int x) {
	return x + '0';
}

void put_on_lcd(int value, int c) {
	unsigned int r = 1;
	unsigned char tens = int_to_char(value / 10);
	unsigned char ones = int_to_char(value % 10);
	lcd_gotoxy(c, r);
	lcd_putchar(tens);
	lcd_gotoxy(c + 1, r);
	lcd_putchar(ones);
}

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void) {
    ms += 1;
	
    if (ms == 10) {
		ms = 0;
		second += 1;
        
        if (second == 60) {
            second = 0;
            minute += 1;
            
            if (minute == 60) {
                minute = 0;
                hour += 1;
                
                if (hour == 24) {
                    hour = 0;
                }
            }
       }
    }
}

void main(void) {
	PORTA=0x00;
	DDRA=0x00;
	PORTB=0x00;
	DDRB=0x00;
	PORTC=0x00;
	DDRC=0x00;
	PORTD=0x00;
	DDRD=0x00;
	
	TCCR1A = 0x00;
	TCCR1B = 0x0C;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	ICR1H = 0x00;
	ICR1L = 0x00;
	OCR1AH = 0x0C;
	OCR1AL = 0x35;
	OCR1BH = 0x00;
	OCR1BL = 0x00;
	TIMSK = 0x12;
	
	lcd_init(16);
	lcd_gotoxy(4, 0);
	lcd_puts("LCD Clock");
	
	// Global enable interrupts
	#asm("sei")
	
	while (1) {
		put_on_lcd(hour, 3);
		lcd_gotoxy(5, 1);
		lcd_puts(":");
		
		put_on_lcd(minute, 6);
		lcd_gotoxy(8, 1);
        lcd_puts(":");

        put_on_lcd(second, 9);
        lcd_gotoxy(11, 1);
        lcd_puts(":");
        
        lcd_gotoxy(12, 1);
        lcd_putchar(int_to_char(ms));
    }
}
