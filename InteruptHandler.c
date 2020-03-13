/*
 * InteruptHandler.c
 *
 * Created: 2020-03-13 16:37:19
 *  Author: zorro
 */ 

#include "InteruptHandler.h"
#include "GUI.h"
#include <avr/io.h>
void SerialInterupt(InteruptHandler *self){
	unsigned int temp = UDR0;
	temp -= 48;
	printAt(temp, 4);
	UDR0 = temp + 48;
}