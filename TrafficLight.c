/*
 * TrafficLight.c
 *
 * Created: 2020-03-11 14:32:16
 *  Author: wille
 */ 
#include "TrafficLight.h"
#include "TinyTimber.h"
#include <avr/io.h>
void greenNorth(TrafficLight *self, int value){
	if (value == 1){
		self->send = 0x1 | self->send;
	}
	else{
		self->send = ~0x1 & self->send;
	}
}
void greenSouth(TrafficLight *self,int value){
	if (value == 1){
		self->send = 0x4 | self->send;
	}
	else{
		self->send = ~0x4 & self->send;
	}
}
void redNorth(TrafficLight *self, int value){
	if (value == 1){
		self->send = 0x2 | self->send;
	}
	else{
		self->send = ~0x2 & self->send;
	}
}
void redSouth(TrafficLight *self, int value){
	if (value == 1){
		self->send = 0x8 | self->send;
	}
	else{
		self->send = ~0x8 & self->send;
	}
}

void sendToCom(TrafficLight *self){
	UDR0 = self->send;
}