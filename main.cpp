/*
 * Library include.cpp
 *
 * Created: 30.11.2016 17:42:44
 * Author : ssc
 */ 

#include <avr/io.h>
#include "midi_functions.h"

void onMidi(uint8_t state, uint8_t id, uint8_t val)
{
	switch (state)
	{
		case 0x90:
		{
			PORTD |= (1 << 7);	//set pin 11 to HIGH (Arduino Leonardo)
			break;
		}
		case 0x80:
		{
			PORTD &= ~(1 << 7);	//set pin 11 to LOW (Arduino Leonardo)
		}
	}
}

int main(void)
{
    midi_usb_init();	
    *(&PORTD - 1) |= (1 << 7);	//set pin 11 to output (Arduino Leonardo)
	while (1) 
    {
		midi_read(onMidi);
    }
}



