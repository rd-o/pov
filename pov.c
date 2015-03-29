#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>

int main(void){
    DDRD &= ~(1 << DDD2); //poner a 0 PD2 para que sirva de entrada

    PORTD |= (1 << PORTD2);  //activar pull-up en PD2

    EICRA |= (1 << ISC00);    // INTO sera activado en cualquier cambio logico
    EIMSK |= (1 << INT0);     // activar INT0

    sei();                    // activar interrupciones

    DDRB |= _BV(DDB0); //PB0 como salida
    
    while(1)
    {
        //PORTB ^= _BV(PB0); //cambiar estado de PB0
        //_delay_ms(500); //retardo de 500ms
    }
}



ISR (INT0_vect)
{
    PORTB ^= _BV(PB0); //cambiar estado de PB0
    _delay_ms(500); //retardo de 500ms
}
