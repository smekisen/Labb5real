/*
 * GUI.c
 *
 * Created: 2020-02-26 14:00:31
 *  Author: wille
 */ 
#include <avr/io.h>
#include "GUI.h"
#include "TinyTimber.h"

void writeChar(char ch, int pos){
	int SCC[4];
	switch(ch)
	{
		case '0':
		SCC[0] = 0x1;
		SCC[1] = 0x5;
		SCC[2] = 0x5;
		SCC[3] = 0x1;
		break;
		case '1':
		SCC[0] = 0x0;
		SCC[1] = 0x1;
		SCC[2] = 0x1;
		SCC[3] = 0x0;
		break;
		case '2':
		SCC[0] = 0x1;
		SCC[1] = 0x1;
		SCC[2] = 0xE;
		SCC[3] = 0x1;
		break;
		case '3':
		SCC[0] = 0x1;
		SCC[1] = 0x1;
		SCC[2] = 0xB;
		SCC[3] = 0x1;
		break;
		case '4':
		SCC[0] = 0x0;
		SCC[1] = 0x5;
		SCC[2] = 0xB;
		SCC[3] = 0x0;
		break;
		case '5':
		SCC[0] = 0x1;
		SCC[1] = 0x4;
		SCC[2] = 0xB;
		SCC[3] = 0x1;
		break;
		case '6':
		SCC[0] = 0x1;
		SCC[1] = 0x4;
		SCC[2] = 0xF;
		SCC[3] = 0x1;
		break;
		case '7':
		SCC[0] = 0x1;
		SCC[1] = 0x1;
		SCC[2] = 0x1;
		SCC[3] = 0x0;
		break;
		case '8':
		SCC[0] = 0x1;
		SCC[1] = 0x5;
		SCC[2] = 0xF;
		SCC[3] = 0x1;
		break;
		case '9':
		SCC[0] = 0x1;
		SCC[1] = 0x5;
		SCC[2] = 0xB;
		SCC[3] = 0x1;
		break;
		default:
		SCC[0] = 0xF;
		SCC[1] = 0xF;
		SCC[2] = 0xF;
		SCC[3] = 0xF;
	}
	printSCC(SCC,pos);
}

void printSCC(int SCC[]	, int pos){
	char *point;
	point = &LCDDR0;
	if(pos % 2 == 0){
		point += pos/2;
		for(int i = 0;i < 4; i++)
		{
			*point &= 0xF0;
			*point = SCC[i] | *point;
			point += 5;
		}
		} else {
		point += (pos-1)/2;
		for(int i = 0;i < 4; i++)
		{
			*point &= 0xF;
			SCC[i] <<= 4;
			*point = SCC[i] | *point;
			point += 5;
			
		}
	}
}

void printAt(long num, int pos) {
	int pp;
	pp = pos;
	//AFTER(0, &self, writeChar, ((num % 100) / 10 + '0', pp));
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}

void updateBridge(GUI *self, int i){
	printAt(i, 2);
}

void updateNorth(GUI *self, int i){
	printAt(i, 0);
}
void updateSouth(GUI *self, int i){
	printAt(i, 4);
}