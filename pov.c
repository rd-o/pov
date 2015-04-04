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

//uint8_t caracteres[] = {0b11111000, 0b10101000, 0b10101000, 0b10001000};
uint8_t retardo_linea_v;

int main(void){
    retardo_linea_v = 2;

    DDRD &= ~(1 << DDD2);     //poner a 0 PD2 para que sirva de entrada
    PORTD |= (1 << PORTD2);   //activar pull-up en PD2
    EICRA |= (1 << ISC00);    // INTO sera activado en cualquier cambio logico
    EIMSK |= (1 << INT0);     // activar INT0
    sei();                    // activar interrupciones

    DDRB |= _BV(DDB0); //PB0 como salida
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
