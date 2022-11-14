/*
 * software_timer.c
 *
 *  Created on: 13 thg 11, 2022
 *      Author: Qui
 */

#include "global.h"
#include "software_timer.h"

int flagTimer[MAX_TIMER] = {0};
int counterTimer[MAX_TIMER] = {0};

void setTimer(int index, int duration){
	counterTimer[index] = duration / CYCLE;
	flagTimer[index] = 0;
}

int getCurrTimer(int index){
	return counterTimer[index]*CYCLE;
}

char isTimerFlagOn(int index){
	if (flagTimer[index] == 1){
		flagTimer[index] = 0;
		return 1;
	}
	return 0;
}

void timerRun(){
	for (int i=0; i<MAX_TIMER; i++){
		if (counterTimer[i] > 0){
			counterTimer[i]--;
			if (counterTimer[i] <= 0){
				flagTimer[i] = 1;
			}
		}
	}
}
