#define F_CPU 1000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>

//a 0b11111000, 0b10010000, 0b10010000, 0b11111000
//i 0b10001000, 0b11111000, 0b10001000
//n 0b11111000, 0b01000000, 0b00100000, 0b11111000
//m 0b11111000, 0b01000000, 0b00100000, 0b01000000, 0b11111000
//l 0b11111000, 0b00001000, 0b00001000, 0b00001000


uint8_t caracteres[] = {0b11111000, 0b10010000, 0b10010000, 0b11111000, 0b00000000, 0b11111000, 0b01000000, 0b00100000, 0b11111000, 0b00000000, 0b10001000, 0b11111000, 0b10001000, 0b00000000, 0b11111000, 0b01000000, 0b00100000, 0b01000000, 0b11111000, 0b00000000, 0b11111000, 0b10010000, 0b10010000, 0b11111000, 0b00000000, 0b11111000, 0b00001000, 0b00001000, 0b00001000};
/*
LED
1 PB0
...
8 PB7

9  PC0
...
14 PC5

15 PD0
16 PD1
17 PD3
18 PD4

19 PD5
20 PD6
21 PD7
*/

//uint8_t caracteres[] = {0b11111000, 0b10101000, 0b10101000, 0b10001000};
uint8_t retardo_linea_v;

int main(void){
    retardo_linea_v = 2;

    DDRD &= ~(1 << DDD2);     //poner a 0 PD2 para que sirva de entrada
    PORTD |= (1 << PORTD2);   //activar pull-up en PD2
    EICRA |= (1 << ISC00);    // INTO sera activado en cualquier cambio logico
    EIMSK |= (1 << INT0);     // activar INT0
    sei();                    // activar interrupciones

    DDRB |= _BV(DDB0);
    DDRB |= _BV(DDB1);
    DDRB |= _BV(DDB2);
    DDRB |= _BV(DDB3);
    DDRB |= _BV(DDB4);
    DDRB |= _BV(DDB5);
    DDRB |= _BV(DDB6);
    DDRB |= _BV(DDB7);

    DDRC |= _BV(DDC0);
    DDRC |= _BV(DDC1);
    DDRC |= _BV(DDC2);
    DDRC |= _BV(DDC3);
    DDRC |= _BV(DDC4);
    DDRC |= _BV(DDC5);

    DDRD |= _BV(DDD0);
    DDRD |= _BV(DDD1);
    DDRD |= _BV(DDD3);
    DDRD |= _BV(DDD4);
    DDRD |= _BV(DDD5);
    DDRD |= _BV(DDD6);
    DDRD |= _BV(DDD7);
    
    PORTB =  0b11111111;
    PORTC =  0b11111111;
    PORTD =  0b11111111;
    _delay_ms(1000);
    PORTB =  0;
    PORTC =  0;
    PORTD =  0;
    _delay_ms(1000);
    PORTB =  0b11111111;
    PORTC =  0b11111111;
    PORTD =  0b11111111;

    while(1)
    {
    }
}

ISR (INT0_vect)
{
    int i;
    for(i = 0; i < 15; i++){
        PORTB = caracteres[i]; 
        _delay_ms(retardo_linea_v); //retardo
    }
    PORTB = 0;
}
