/*
 * midi_functions.h
 *
 * Created: 17.11.2016 18:55:38
 *  Author: ssc
 */ 

#ifndef MIDI_FUNCTIONS_H_
#define MIDI_FUNCTIONS_H_

void midi_usb_init(void);
void midi_send_noteOn(uint8_t channel, uint8_t pitch, uint8_t velocity);
void midi_send_noteOff(uint8_t channel, uint8_t pitch, uint8_t velocity);
void midi_send_controlChange(uint8_t channel, uint8_t control, uint8_t value);

void midi_flush();

void midi_read(void (* midi_event_handler)(uint8_t status,uint8_t cc,uint8_t val));
void midi_read_multiple(void (* midi_event_handler)(uint8_t,uint8_t,uint8_t));

#endif /* MIDI_FUNCTIONS_H_ */