/*
 * display_led.h
 *
 *  Created on: 13 thg 11, 2022
 *      Author: Qui
 */

#ifndef INC_DISPLAY_LED_H_
#define INC_DISPLAY_LED_H_

#define LED_RED		0
#define LED_AMBER	1
#define LED_GREEN	2

#define DISPLAY_INIT	22
#define DISPLAY_RED 	23
#define DISPLAY_GREEN 	24
#define DISPLAY_AMBER 	25

void clear_all_led();

//for test led in PA5
void display_test_led();
void clear_test_led();

//for normal led
void display_blinky_led(int index);

//for 7 segments led
void display_7_seg(int num);
void enable_7_seg(int index);

//for traffic light
void display_light(int index, int type);
void display_time();
void display_traffic(int index);

#endif /* INC_DISPLAY_LED_H_ */
