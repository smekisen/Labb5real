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
	int send;
} TrafficLight;

#define initTrafficLight() {initObject(), 0}

void greenNorth(TrafficLight *self,int value);
void greenSouth(TrafficLight *self,int value);
void redNorth(TrafficLight *self,int value);
void redSouth(TrafficLight *self,int value);
void sendToCom(TrafficLight *self);

#endif /* TRAFFICLIGHT_H_ */