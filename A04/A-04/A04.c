// Ali Sedaghi
// 97521378

#include <mega32.h>
#include <delay.h>

// Init time
unsigned int HOUR_TENS = 2;
unsigned int HOUR_ONES = 3;
unsigned int MINUTE_TENS = 5;
unsigned int MINUTE_ONES = 8;
unsigned int SECOND_TENS = 0;
unsigned int SECOND_ONES = 0;
char DP = 0x80;

char convert[] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F};

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void) {
    DP = 0x00;
    SECOND_ONES += 1;
    
    if (SECOND_ONES % 2 == 0)
        DP = 0x80;
            
    if (SECOND_ONES == 10) {
        SECOND_ONES = 0;
        SECOND_TENS += 1;
        
        if (SECOND_TENS == 6) { 
            SECOND_TENS = 0;
            MINUTE_ONES += 1;
            
            if (MINUTE_ONES == 10) {
                MINUTE_ONES = 0;
                MINUTE_TENS += 1;
                
                if (MINUTE_TENS == 6) {
                    MINUTE_TENS = 0;
                    HOUR_ONES += 1;
                    
                    if (HOUR_ONES == 4 && HOUR_TENS == 2) {
                        HOUR_ONES = 0;
                        HOUR_TENS = 0;
                    }
                    
                    else if (HOUR_ONES == 10 && HOUR_TENS == 0) {
                        HOUR_ONES = 0;
                        HOUR_TENS += 1;
                    }
                }
            }
       } 
    }
}

void main(void) {
// Port C and D as out
PORTC = 0x00;
DDRC = 0xFF;
PORTD = 0x00;
DDRD = 0xFF;

// Timer 1 config
TCCR1A = 0x00;
TCCR1B = 0x0C;
TCNT1H = 0x00;
TCNT1L = 0x00;
ICR1H = 0x00;
ICR1L = 0x00;
OCR1AH = 0x7A;
OCR1AL = 0x12;
OCR1BH = 0x00;
OCR1BL = 0x00;

TIMSK = 0x12;

// Global enable interrupts
#asm("sei")

while (1)
{
    // Digit [*-----]
    PORTD = 0b11111110;
    PORTC = convert[HOUR_TENS];
    delay_ms(5);
    
    // Digit [-*----]
    PORTD = 0b11111101;
    PORTC = convert[HOUR_ONES] | DP;
    delay_ms(5);

    // Digit [--*---]
    PORTD = 0b11111011;
    PORTC = convert[MINUTE_TENS];
    delay_ms(5);

    // Digit [---*--]
    PORTD = 0b11110111;
    PORTC = convert[MINUTE_ONES] | DP;
    delay_ms(5);
    
    // Digit [----*-]
    PORTD = 0b11101111;
    PORTC = convert[SECOND_TENS];
    delay_ms(5);
    
    // Digit [-----*]
    PORTD = 0b11011111;
    PORTC = convert[SECOND_ONES] | DP;
    delay_ms(5);
}
}
