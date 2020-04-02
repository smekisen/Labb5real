/*
 * LightLogic.c
 *
 * Created: 2020-03-10 14:17:43
 *  Author: wille
 */ 
#define STREAKNUMBER 6
#include "TinyTimber.h"
#include "LightLogic.h"
#include "GUI.h"
#include "TrafficLight.h"

void northArrive(LightLogic *self){
	
	self->northQ += 1;
	
	
	
	ASYNC(self->gui1, updateNorth, self->northQ);
	//AFTER(SEC(3),self,northEntry,NULL);
}

void southArrive(LightLogic *self){
	
	self->southQ += 1;
	
	
	ASYNC(self->gui1, updateSouth, self->southQ);
	//AFTER(SEC(3),self,southEntry,NULL);
}

void northEntry(LightLogic *self){
	ASYNC(self->tl, greenSouth, 0);
	ASYNC(self->tl, redSouth, 1);
	self->northQ -= 1;
	self->bridgeNr += 1;
	if (self->lastSide == 1){
		self->streak += 1;
	}
	else{
		self->streak = 0;
	}
	self->lastSide = 1;
	//Sägg alla ljus röda efter att en bil kört in på bron.
	
	
	//Om en streak inte är nådd, sätt grönt ljus efter 1 sekund
	if (self->streak >= STREAKNUMBER && self->southQ > 0){
		//AFTER(SEC(1), self, carDelay, NULL);
		ASYNC(self->tl, greenNorth, 0);
		ASYNC(self->tl, redNorth, 1);
		ASYNC(self->tl, greenSouth, 0);
		SYNC(self->tl, redSouth, 1);
		
	}
	ASYNC(self->tl,sendToCom,NULL);
	AFTER(SEC(5), self, bridgeExit, 0);
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
	ASYNC(self->gui1, updateNorth, self->northQ);
}

void southEntry(LightLogic *self){
	ASYNC(self->tl, greenNorth, 0);
	ASYNC(self->tl, redNorth, 1);
	
	self->southQ -= 1;
	self->bridgeNr += 1;
	if (self->lastSide == 2){
		self->streak += 1;
	}
	else{
		self->streak = 0;
	}
	self->lastSide = 2;
	//Sägg alla ljus röda efter att en bil kört in på bron.
	
	
	//Om en streak inte är nådd, sätt grönt ljus efter 1 sekund
	if (self->streak >= STREAKNUMBER && self->northQ > 0){
		//AFTER(SEC(1), self, carDelay, NULL);
		ASYNC(self->tl, greenNorth, 0);
		ASYNC(self->tl, redNorth, 1);
		ASYNC(self->tl, greenSouth, 0);
		ASYNC(self->tl, redSouth, 1);
	}
	ASYNC(self->tl,sendToCom,NULL);
	AFTER(SEC(5), self, bridgeExit, 0);
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
	ASYNC(self->gui1, updateSouth, self->southQ);
}

void bridgeExit(LightLogic *self){
	self->bridgeNr -= 1;
	if (self->bridgeNr == 0){
		if (self->lastSide == 2){
			if (self->southQ == 0){
				if(self->northQ > 0){
					ASYNC(self->tl, redSouth, 1);
					ASYNC(self->tl, greenNorth, 1);
					ASYNC(self->tl, greenSouth, 0);
					ASYNC(self->tl, redNorth, 0);
					ASYNC(self->tl,sendToCom,NULL);
				} else {
					ASYNC(self->tl, redSouth, 0);
					ASYNC(self->tl, greenNorth, 1);
					ASYNC(self->tl, greenSouth, 1);
					ASYNC(self->tl, redNorth, 0);
					ASYNC(self->tl,sendToCom,NULL);
				}
			}
			else if(self->streak >= STREAKNUMBER){
				if(self->northQ > 0){
					ASYNC(self->tl, redSouth, 1);
					ASYNC(self->tl, greenNorth, 1);
					ASYNC(self->tl, greenSouth, 0);
					ASYNC(self->tl, redNorth, 0);
					ASYNC(self->tl,sendToCom,NULL);
				}
			}
		}
		if (self->lastSide == 1){
			if (self->northQ == 0){
				if(self->southQ > 0){
					ASYNC(self->tl, redSouth, 0);
					ASYNC(self->tl, greenNorth, 0);
					ASYNC(self->tl, greenSouth, 1);
					ASYNC(self->tl, redNorth, 1);
					ASYNC(self->tl,sendToCom,NULL);
					} else {
					ASYNC(self->tl, redSouth, 0);
					ASYNC(self->tl, greenNorth, 1);
					ASYNC(self->tl, greenSouth, 1);
					ASYNC(self->tl, redNorth, 0);
					ASYNC(self->tl,sendToCom,NULL);
				}
			}
			else if(self->streak >= STREAKNUMBER){
				if(self->southQ > 0){
					ASYNC(self->tl, redSouth, 0);
					ASYNC(self->tl, greenNorth, 0);
					ASYNC(self->tl, greenSouth, 1);
					ASYNC(self->tl, redNorth, 1);
					ASYNC(self->tl,sendToCom,NULL);
				}
			}
		}
	}
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
}


void lightStart(LightLogic *self){
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
	ASYNC(self->gui1, updateNorth, self->northQ);
	ASYNC(self->gui1, updateSouth, self->northQ);
	ASYNC(self->tl, redSouth, 0);
	ASYNC(self->tl, greenNorth, 1);
	ASYNC(self->tl, greenSouth, 1);
	ASYNC(self->tl, redNorth, 0);
	ASYNC(self->tl,sendToCom,NULL);
}