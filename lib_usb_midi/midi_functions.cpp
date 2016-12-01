/*
 * midi_functions.cpp
 *
 * Created: 17.11.2016 18:55:21
 *  Author: ssc
 */ 

#include "MIDIUSB.h"

//#include "Arduino/CDC.h"	//Methode verbessern!!!!
#include <avr/interrupt.h>

void midi_usb_init(void)
{
	USBDevice.attach();
	sei();
	//while (!CDC_finished_setup());
	while (!USBDevice.configured()) {};
	//if(USBDevice.configured()) PinSet(PIN_A2);
}

void midi_send_noteOn(uint8_t channel, uint8_t pitch, uint8_t velocity) {
	channel |= 0x90;
	midiEventPacket_t noteOn = {0x09, channel, pitch, velocity};
	MidiUSB.sendMIDI(noteOn);
	/*noteOn.byte2 = 37;
	MidiUSB.sendMIDI(noteOn);
	noteOn.byte2 = 38;
	MidiUSB.sendMIDI(noteOn);
	noteOn.byte2 = 39;
	MidiUSB.sendMIDI(noteOn);*/		//can send multiple notes at once
}
void midi_send_noteOff(uint8_t channel, uint8_t pitch, uint8_t velocity) {
	channel |= 0x80;
	midiEventPacket_t noteOff = {0x08, channel, pitch, velocity};
	MidiUSB.sendMIDI(noteOff);
	/*noteOff.byte2 = 37;
	MidiUSB.sendMIDI(noteOff);
	noteOff.byte2 = 38;
	MidiUSB.sendMIDI(noteOff);
	noteOff.byte2 = 39;
	MidiUSB.sendMIDI(noteOff);*/	//can send multiple notes at once
}
void midi_send_controlChange(uint8_t channel, uint8_t control, uint8_t value) {
	channel |= 0xB0;
	midiEventPacket_t event = {0x0B, channel, control, value};
	MidiUSB.sendMIDI(event);
}

void midi_flush(){
	MidiUSB.flush();
}

//EXPAND this so you can give it an own midi handler
#if 0
void midi_read(void * event_handler/*(uint8_t x1,uint8_t x2, uint8_t x3)*/){
	midiEventPacket_t rx;
	rx = MidiUSB.read();
	if(rx.header != 0) {
		event_handler(rx.byte1,rx.byte2,rx.byte3);
	}
}
(*COOS_taskArray[index].pTask)();
COOS_taskArray[index].pTask	 	= taskName;
#endif

void midi_read(void (* taskName)(uint8_t,uint8_t,uint8_t)){
	midiEventPacket_t rx;
	rx = MidiUSB.read();
	if(rx.header != 0) {
		//PinSet(PIN_D11);
		(*taskName)(rx.byte1,rx.byte2,rx.byte3);	//run midi handler
		//PinClr(PIN_D11);
	}
	
}



void midi_read_multiple(void (* taskName)(uint8_t,uint8_t,uint8_t)){
	midiEventPacket_t rx;
	rx = MidiUSB.read();
	while (rx.header != 0)
	{
		(*taskName)(rx.byte1,rx.byte2,rx.byte3);	//run midi handler
		rx = MidiUSB.read();
	}
}