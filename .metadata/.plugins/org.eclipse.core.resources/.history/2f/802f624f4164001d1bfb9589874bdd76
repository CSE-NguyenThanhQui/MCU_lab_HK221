/*
 * fsm_run.c
 *
 *  Created on: 13 thg 11, 2022
 *      Author: Qui
 */

#include "time_display.h"
#include "fsm_run.h"
#include "main.h"
#include "global.h"
#include "input_reading.h"
#include "display_led.h"

void fsm_run(){
	switch(current_mode){

	case INIT:
		//TODO
		clear_all_led(); //xoa cac so xuat hien tren led 7 doan
		current_mode = MODE_1;
		traffic_state[TRAFFIC_1ST] = DISPLAY_INIT;
		traffic_state[TRAFFIC_2ND] = DISPLAY_INIT;
		setTimer(TIMER_7SEG, 250);
		break;

	//trang thai mac dinh
	case MODE_1:
		//TODO
		display_traffic(TRAFFIC_1ST);
		display_traffic(TRAFFIC_2ND);
		display_time();

		//khi nhan nut 1, chuyen sang mode 2
		if (isBtnPressed(BTN_1)){
			current_mode = MODE_2;
			change_mode_buffer(MODE_2);
			setTimer(TIMER_LED, 500);
			clear_all_led();
		}
		break;

	//mode 2: chinh den do
	case MODE_2:
		//TODO
		display_blinky_led(LED_RED);
		display_time();

		//khi nhan nut 1, chuyen sang mode 3
		if (isBtnPressed(BTN_1)){
			current_mode = MODE_3;
			change_mode_buffer(MODE_3);
			setTimer(TIMER_LED, 500);
			clear_all_led();
		}
		//khi nhan nut 2, tang gia tri
		if (isBtnPressed(BTN_2)) inc_temp_led_duration();
		//khi nhan nut 3, thiet lap gia tri
		if (isBtnPressed(BTN_3)) update_led_duration(LED_RED);
		break;

	//mode 3, den vang
	case MODE_3:
		//TODO
		display_blinky_led(LED_AMBER);
		display_time();

		if (isBtnPressed(BTN_1)){
			current_mode = MODE_4;
			change_mode_buffer(MODE_4);
			setTimer(TIMER_LED, 500);
			clear_all_led();
		}

		if (isBtnPressed(BTN_2)) inc_temp_led_duration();

		if (isBtnPressed(BTN_3)) update_led_duration(LED_AMBER);
		break;

	//mode 4, den xanh
	case MODE_4:
		//TODO
		display_blinky_led(LED_GREEN);
		display_time();

		if (isBtnPressed(BTN_1)){
			current_mode = MODE_1;
			traffic_state[TRAFFIC_1ST] = DISPLAY_INIT;
			traffic_state[TRAFFIC_2ND] = DISPLAY_INIT;
			clear_all_led();
		}

		if (isBtnPressed(BTN_2)) inc_temp_led_duration();

		if (isBtnPressed(BTN_3)) update_led_duration(LED_GREEN);
		break;

	default:
		break;
	}
}
