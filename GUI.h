/*
 * IncFile1.h
 *
 * Created: 2020-02-26 14:00:39
 *  Author: wille
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#include "TinyTimber.h"

typedef struct {
	Object super;
	
} GUI;

#define initGUI() {initObject()}

void writeChar(char ch, int pos);
void printSCC(int SCC[]	, int pos);
void printAt(long num, int pos);
void updateNorth(GUI *self, int i);
void updateSouth(GUI *self, int i);
void updateBridge(GUI *self, int i);

#endif /* INCFILE1_H_ */