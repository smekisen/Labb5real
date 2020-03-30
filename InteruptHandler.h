/*
 * InteruptHandler.h
 *
 * Created: 2020-03-13 16:37:49
 *  Author: zorro
 */ 
#include "TinyTimber.h"
#include <avr/io.h>
#include "LightLogic.h"

#ifndef INTERUPTHANDLER_H_
#define INTERUPTHANDLER_H_
typedef struct{
	Object super;
	LightLogic *ll;
} InteruptHandler;

#define InitInteruptHandler(ll) {initObject(),ll}
void SerialInterupt(InteruptHandler *self);


#endif /* INTERUPTHANDLER_H_ */