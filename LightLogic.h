/*
 * LightLogic.h
 *
 * Created: 2020-03-10 14:17:58
 *  Author: wille
 */ 
#include "TinyTimber.h"
#include "GUI.h"
#include "TrafficLight.h"
#ifndef LIGHTLOGIC_H_
#define LIGHTLOGIC_H_
typedef struct{
	Object super;
	GUI *gui1;
	TrafficLight *tl;
	int northQ;
	int southQ;
	int bridgeNr;
	int streak;
	int lastSide;
} LightLogic;

#define initLightLogic(g, t) {initObject(),g,t,0,0,0,0,0}

void northArrive(LightLogic *self);
void southArrive(LightLogic *self);
void northEntry(LightLogic *self);
void southEntry(LightLogic *self);
void bridgeExit(LightLogic *self);
void carDelay(LightLogic *self);
void lightStart(LightLogic *self);

#endif /* LIGHTLOGIC_H_ */