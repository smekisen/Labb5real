/*
 * TrafficLight.h
 *
 * Created: 2020-03-11 14:32:26
 *  Author: wille
 */ 
#include "TinyTimber.h"

#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

typedef struct {
	Object super;
	int north;
	int south;
} TrafficLight;

#define initTrafficLight() {initObject(), 0, 0}

void greenNorth(TrafficLight *self);
void greenSouth(TrafficLight *self);
void redNorth(TrafficLight *self);
void redSouth(TrafficLight *self);

#endif /* TRAFFICLIGHT_H_ */