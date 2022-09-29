// Ali Sedaghi
// 97521378

#include <mega32.h>
#include <alcd.h>
#include <delay.h>

unsigned char int_to_char(int x) {
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

// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input) {
	ADMUX = adc_input | ADC_VREF_TYPE;
	// Delay needed for the stabilization of the ADC input voltage
	delay_us(10);
	// Start the AD conversion
	ADCSRA |= (1 << ADSC);
	// Wait for the AD conversion to complete
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA |= (1 << ADIF);
	return ADCW;
}

void main(void) {
	int temprature;
	
	PORTA=0x00;
	DDRA=0x00;
	PORTB=0x00;
	DDRB=0x00;
	PORTC=0x00;
	DDRC=0x00;
	PORTD=0x00;
	DDRD=0x00;
	
	// ADC initialization
	// ADC Clock frequency: 250.000 kHz
	// ADC Voltage Reference: AVCC pin
	// ADC Auto Trigger Source: ADC Stopped
	ADMUX |= (1<<MUX0);
	//ADMUX=ADC_VREF_TYPE;
	ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
	SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
	
	lcd_init(16);
	
    lcd_gotoxy(3, 0);
    lcd_puts("LM35 Sensor");
    
    lcd_gotoxy(2, 1);
    lcd_puts("Temp :");
    
    lcd_gotoxy(12, 1);
    lcd_putchar(223);
    
    lcd_gotoxy(13, 1);
    lcd_puts("C");
    
    while (1) {
        temprature = read_adc(0);
        temprature = temprature * 0.48898;
        put_on_lcd(temprature, 9);
        delay_ms(100);
    }
}
