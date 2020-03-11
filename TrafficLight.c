/*
 * TrafficLight.c
 *
 * Created: 2020-03-11 14:32:16
 *  Author: wille
 */ 
#include "TrafficLight.h"
#include "TinyTimber.h"

void greenNorth(TrafficLight *self){
	self->north = 1;
}
void greenSouth(TrafficLight *self){
	self->south	= 1;
}
void redNorth(TrafficLight *self){
	self->north = 0;
}
void redSouth(TrafficLight *self){
	self->south = 0;
}