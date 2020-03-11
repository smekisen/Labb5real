/*
 * labb5.c
 *
 * Created: 2020-03-10 14:03:22
 * Author : wille
 */ 

#include <avr/io.h>
#include "TinyTimber.h"
#include "LightLogic.h"
#include "GUI.h"
TrafficLight tl = initTrafficLight();
GUI gui1 = initGUI();
LightLogic ll = initLightLogic(&gui1, &tl);


int main(void)
{
	//initializera lcd skärm
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1)| (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
	LCDFRR = (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
	LCDCCR = (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);
	LCDCRA = (1<<LCDEN) | (1<<LCDAB);
	
	return TINYTIMBER(&ll, northArrive, 0);
    /* Replace with your application code */
    while (1)
    {
    }
}

