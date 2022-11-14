/*
 * software_timer.h
 *
 *  Created on: 13 thg 11, 2022
 *      Author: Qui
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define MAX_TIMER 	4
#define CYCLE 		1
#define TIME_UNIT	1000

#define TRAFFIC_1ST	0
#define TRAFFIC_2ND	1
#define TIMER_7SEG	2
#define TIMER_LED	3

void initTimer();
void setTimer(int index, int duration);
int getCurrTimer(int index);
char isTimerFlagOn(int index);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
