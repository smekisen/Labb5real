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
		SYNC(self->tl, redSouth, 0);
		SYNC(self->tl, greenNorth, 0);		
	}
	
	ASYNC(self->gui1, updateNorth, self->northQ);
}

void southArrive(LightLogic *self){
	
	self->southQ += 1;
	
	if(self->bridgeNr == 0){
		SYNC(self->tl, redNorth, 0);
		SYNC(self->tl, greenSouth, 0);
	}
	
	ASYNC(self->gui1, updateSouth, self->southQ);
}

void northEntry(LightLogic *self){
	self->northQ -= 1;
	self->bridgeNr += 1;
	if (self->lastSide == 1){
		self->streak += 1;
	}
	else{
		self->streak = 0;
	}
	self->lastSide = 1;
	
	//Byt sida när streak når 4 och kön på andra sidan inte är tom
	if (self->streak >= 4 && self->southQ > 0){
		SYNC(self->tl, redNorth, 0);
		AFTER(SEC(5),self->tl, greenSouth,0);
	}
	//Om kön är tom, byt sida
	if (self->northQ == 0){
		SYNC(self->tl, redNorth, 0);
		AFTER(SEC(5),self->tl, greenSouth,0);
	}
	AFTER(SEC(5), self, bridgeExit, 0);
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
	ASYNC(self->gui1, updateNorth, self->northQ);
}

void southEntry(LightLogic *self){
	self->southQ -= 1;
	self->bridgeNr += 1;
	if (self->lastSide == 2){
		self->streak += 1;
	}
	else{
		self->streak = 0;
	}
	self->lastSide = 2;
	
	//Byt sida när streak når 4 och kön på andra sidan inte är tom
	if (self->streak >= 4 && self->northQ > 0){
		SYNC(self->tl, redSouth, 0);
		AFTER(SEC(5),self->tl, greenNorth,0);
	}
	//Om kön är tom, byt sida
	if (self->southQ == 0){
		SYNC(self->tl, redSouth, 0);
		AFTER(SEC(5),self->tl, greenSouth,0);
	}
	
	AFTER(SEC(5), self, bridgeExit, 0);
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
	ASYNC(self->gui1, updateSouth, self->southQ);
}

void bridgeExit(LightLogic *self){
	self->bridgeNr -= 1;
	ASYNC(self->gui1, updateBridge, self->bridgeNr);
}

void lightControl(LightLogic *self){
	
}