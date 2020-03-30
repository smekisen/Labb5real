/*
 * LightLogic.c
 *
 * Created: 2020-03-10 14:17:43
 *  Author: wille
 */ 
#include "TinyTimber.h"
#include "LightLogic.h"
#include "GUI.h"
#include "TrafficLight.h"

void northArrive(LightLogic *self){
	
	self->northQ += 1;
	
	if(self->bridgeNr == 0){
		SYNC(self->tl, redSouth, 1);
		SYNC(self->tl, greenNorth, 1);
		SYNC(self->tl, greenSouth, 0);
		SYNC(self->tl, redNorth, 0);	
		SYNC(self->tl,sendToCom,NULL);	
	}
	
	ASYNC(self->gui1, updateNorth, self->northQ);
	//AFTER(SEC(3),self,northEntry,NULL);
}

void southArrive(LightLogic *self){
	
	self->southQ += 1;
	
	if(self->bridgeNr == 0){
		SYNC(self->tl, redSouth, 0);
		SYNC(self->tl, greenNorth, 0);
		SYNC(self->tl, greenSouth, 1);
		SYNC(self->tl, redNorth, 1);
		SYNC(self->tl,sendToCom,NULL);
	}
	
	ASYNC(self->gui1, updateSouth, self->southQ);
	//AFTER(SEC(3),self,southEntry,NULL);
}

void northEntry(LightLogic *self){
	SYNC(self->tl, greenNorth, 0);
	SYNC(self->tl, redNorth, 1);
	SYNC(self->tl, greenSouth, 0);
	SYNC(self->tl, redSouth, 1);
	SYNC(self->tl,sendToCom,NULL);
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
	if (!(self->streak >= 4 && self->southQ > 0)){
		AFTER(SEC(1), self, carDelay, 0);
	}
	AFTER(SEC(5), self, bridgeExit, 0);
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
	ASYNC(self->gui1, updateNorth, self->northQ);
}

void southEntry(LightLogic *self){
	SYNC(self->tl, greenNorth, 0);
	SYNC(self->tl, redNorth, 1);
	SYNC(self->tl, greenSouth, 0);
	SYNC(self->tl, redSouth, 1);
	SYNC(self->tl,sendToCom,NULL);
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
	if (!(self->streak >= 4 && self->northQ > 0)){
		AFTER(SEC(1), self, carDelay, 0);
	}
	
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
					SYNC(self->tl, redSouth, 1);
					SYNC(self->tl, greenNorth, 1);
					SYNC(self->tl, greenSouth, 0);
					SYNC(self->tl, redNorth, 0);
					SYNC(self->tl,sendToCom,NULL);
				} else {
					SYNC(self->tl, redSouth, 0);
					SYNC(self->tl, greenNorth, 1);
					SYNC(self->tl, greenSouth, 1);
					SYNC(self->tl, redNorth, 0);
					SYNC(self->tl,sendToCom,NULL);
				}
			}
			else if(self->streak >= 4){
				if(self->northQ > 0){
					SYNC(self->tl, redSouth, 1);
					SYNC(self->tl, greenNorth, 1);
					SYNC(self->tl, greenSouth, 0);
					SYNC(self->tl, redNorth, 0);
					SYNC(self->tl,sendToCom,NULL);
				}
			}
		}
		if (self->lastSide == 1){
			if (self->northQ == 0){
				if(self->southQ > 0){
					SYNC(self->tl, redSouth, 0);
					SYNC(self->tl, greenNorth, 0);
					SYNC(self->tl, greenSouth, 1);
					SYNC(self->tl, redNorth, 1);
					SYNC(self->tl,sendToCom,NULL);
					} else {
					SYNC(self->tl, redSouth, 0);
					SYNC(self->tl, greenNorth, 1);
					SYNC(self->tl, greenSouth, 1);
					SYNC(self->tl, redNorth, 0);
					SYNC(self->tl,sendToCom,NULL);
				}
			}
			else if(self->streak >= 4){
				if(self->southQ > 0){
					SYNC(self->tl, redSouth, 0);
					SYNC(self->tl, greenNorth, 0);
					SYNC(self->tl, greenSouth, 1);
					SYNC(self->tl, redNorth, 1);
					SYNC(self->tl,sendToCom,NULL);
				}
			}
		}
	}
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
}

void carDelay(LightLogic *self){
	if(self->lastSide == 2){
		SYNC(self->tl, redSouth, 0);
		SYNC(self->tl, greenNorth, 0);
		SYNC(self->tl, greenSouth, 1);
		SYNC(self->tl, redNorth, 1);
		SYNC(self->tl,sendToCom,NULL);
	}
	else if(self->lastSide == 1){
		SYNC(self->tl, redSouth, 1);
		SYNC(self->tl, greenNorth, 1);
		SYNC(self->tl, greenSouth, 0);
		SYNC(self->tl, redNorth, 0);
		SYNC(self->tl,sendToCom,NULL);
	}
}

void lightStart(LightLogic *self){
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
	ASYNC(self->gui1, updateNorth, self->northQ);
	ASYNC(self->gui1, updateSouth, self->northQ);
	SYNC(self->tl, redSouth, 0);
	SYNC(self->tl, greenNorth, 1);
	SYNC(self->tl, greenSouth, 1);
	SYNC(self->tl, redNorth, 0);
	SYNC(self->tl,sendToCom,NULL);
}