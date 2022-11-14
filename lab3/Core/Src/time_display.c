/*
 * time_display.c
 *
 *  Created on: 13 thg 11, 2022
 *      Author: Qui
 */

#include "time_display.h"
#include "global.h"
#include "fsm_run.h"
#include "main.h"
#include "display_led.h"

int curr_mode = 0;
int temp_duration = 0;

void modify_traffic_buffer(int mode, int duration){
	traffic_time_buffer[0][0] = duration/10;
	traffic_time_buffer[0][1] = duration%10;
	traffic_time_buffer[1][0] = mode/10;
	traffic_time_buffer[1][1] = mode%10;
}

void change_mode_buffer(int mode){
	switch (mode){
	case MODE_2:
		temp_duration = traffic_duration[LED_RED];
		curr_mode = 2;
		break;

	case MODE_3:
		temp_duration = traffic_duration[LED_AMBER];
		curr_mode = 3;
		break;

	case MODE_4:
		temp_duration = traffic_duration[LED_GREEN];
		curr_mode = 4;
		break;

	default:
		break;
	}
	modify_traffic_buffer(curr_mode, temp_duration);
}

void inc_temp_led_duration(){
	temp_duration++;
	if (temp_duration >= 100) temp_duration = 1;
	modify_traffic_buffer(curr_mode, temp_duration);
}

void update_led_duration(int led){
	traffic_duration[led] = temp_duration;
	modify_traffic_buffer(curr_mode, temp_duration);
}
