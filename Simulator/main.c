#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

pthread_t threadId;
sem_t n;
sem_t s;
int greenN = 1;
int greenS = 1;
int redN;
int redS;
int COM1;
int south = 0;
int north = 0;
int bridge = 0;

void printAll(){
	printf("%c[2JNorth: Cars: %d, Green: %d, Red: %d \nBridge: Cars: %d \nSouth: Cars: %d, Green: %d, Red: %d \n",27, north, greenN, redN, bridge, south, greenS, redS);
	
}

void *fun(void *arg){
	char side = (char)arg;
	if (side == 's'){
		south +=1;
		printAll();
		sem_wait(&s);
	}
	else if(side == 'n'){
		north +=1;
		printAll();
		sem_wait(&n);
	}
	while(1){
		if (side == 's'){
			if (greenS == 1){
				
				bridge +=1;
				south -= 1;
				printAll();
				
				char buf[1] = {8};
				write(COM1, buf, 1);
				sleep(1);
				sem_post(&s);
				
				sleep(4);
				
				bridge -=1;
				printAll();
				pthread_exit(0);
			}
		}
		else if(side == 'n'){
			if (greenN == 1){
				bridge +=1;
				north -=1;
				printAll();
				
				char buf[1] = {2};
				write(COM1, buf, 1);
				sleep(1);
				sem_post(&n);
				
				sleep(4);
				
				bridge -= 1;
				printAll();
				pthread_exit(0);
			}
		}
	}
}



void testwrite(){
	int buff;
	buff = getc(stdin);
	//buff = buff - 48;
	
	if(buff == 's'){
		char buf[1] = {4};
		write(COM1, buf, 1);
		pthread_create(&threadId, NULL, fun,(void*)'s');
		threadId = threadId + 1;
	}
	else if(buff == 'n'){
		char buf[1] = {1};
		write(COM1, buf, 1);
		pthread_create(&threadId, NULL, fun,(void*)'n');
		threadId = threadId + 1;
	}
	else if(buff == 'e'){
		exit(0);
	}
	
	
}

void testrecieve(){
		
	int buf[1] = {0};
	read(COM1, buf, 1);
	
	int temp = buf[0];
	temp = 0x1 & temp;
	//Greenlight North
	if (temp == 1){
		greenN = 1;
	}
	else{
		greenN = 0;
	}
	
	temp = buf[0];
	temp = temp >> 1;
	temp = 0x1 & temp;
	//Redlight North
	if(temp == 1){
		redN = 1;
	}
	else{
		redN = 0;
	}
	
	temp = buf[0];
	temp = temp >> 2;
	temp = 0x1 & temp;
	//Greenlight South
	if(temp == 1){
		greenS = 1;
	}
	else{
		greenS = 0;
	}
	
	temp = buf[0];
	temp = temp >> 3;
	//Redlight South
	if(temp == 1){
		redS = 1;
	}
	else{
		redS = 0;
	}
	printAll();
}
struct termios term;

int main(void){
	
	
	COM1 = open("/dev/ttyS0", O_RDWR);
	
	tcgetattr(COM1, &term);
	cfsetospeed(&term, B9600);
	cfsetispeed(&term, B9600);
	
	sem_init(&n, 0, 1);
	sem_init(&s, 0, 1);
	
	fd_set rfds;
	while(1){
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		FD_SET(COM1, &rfds);
		select(4, &rfds, NULL, NULL, NULL);
		
		if(FD_ISSET(0, &rfds)){
			testwrite();
		}
		
		if(FD_ISSET(COM1, &rfds)){
			testrecieve();
		}
	}
}


