/*
 * InteruptHandler.c
 *
 * Created: 2020-03-13 16:37:19
 *  Author: zorro
 */ 

#include "InteruptHandler.h"
#include "GUI.h"
#include "LightLogic.h"
#include <avr/io.h>
void SerialInterupt(InteruptHandler *self){
	unsigned int temp = UDR0;
	unsigned int temp2 = temp;
	temp2 = 0x1 & temp2;
	if(temp2 == 1){
		ASYNC(self->ll,northArrive,NULL);
	}
	temp2 = temp;
	temp2 = temp2 >> 1;
	temp2 = 0x1 & temp2;
	if (temp2 == 1){
		ASYNC(self->ll,northEntry,NULL);	
	}
	
	temp2 = temp;
	temp2 = temp2 >> 2;
	temp2 = 0x1 & temp2;
	if (temp2 == 1){
		ASYNC(self->ll,southArrive,NULL);
	}
	
	temp2 = temp;
	temp2 = temp2 >> 3;
	temp2 = 0x1 & temp2;
	if (temp2 == 1){
		ASYNC(self->ll,southEntry,NULL);
	}
}