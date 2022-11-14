/*
 * display_led.c
 *
 *  Created on: 13 thg 11, 2022
 *      Author: Qui
 */

#include "display_led.h"
#include "main.h"
#include "global.h"

int led_7seg_index = 0;

//xoa toan bo led 7 doan
void clear_all_led(){
	HAL_GPIO_WritePin(GPIOA, LED_TEST_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_R1_Pin | LED_Y1_Pin | LED_G1_Pin
							| LED_R2_Pin | LED_Y2_Pin | LED_G2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin
							| SEG4_Pin | SEG5_Pin | SEG6_Pin, GPIO_PIN_SET);
}
//sang toan bo led 7 doan
void display_test_led(){
	HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_RESET);
}
//tat toan bo led 7 doan
void clear_test_led(){
	HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_SET);
}

void blink_led(int index){
	switch(index){
	case LED_RED:
		HAL_GPIO_TogglePin(GPIOA, LED_R1_Pin | LED_R2_Pin);
		break;
	case LED_AMBER:
		HAL_GPIO_TogglePin(GPIOA, LED_Y1_Pin | LED_Y2_Pin);
		break;
		break;
	case LED_GREEN:
		HAL_GPIO_TogglePin(GPIOA, LED_G1_Pin | LED_G2_Pin);
		break;
		break;
	default:
		break;
	}
}

void display_blinky_led(int index){
	if(isTimerFlagOn(TIMER_LED)){
		setTimer(TIMER_LED, 500);
		blink_led(index);
	}
}

void update_time_buffer(int index, int time){
	traffic_time_buffer[index][0] = time/10; //led 7 doan hang chuc
	traffic_time_buffer[index][1] = time%10; //led 7 doan hang don vi
}

void display_7_seg(int num){
	switch (num){
	case 0:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
								SEG3_Pin | SEG4_Pin | SEG5_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG6_Pin, 1);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG3_Pin | SEG4_Pin |
								SEG5_Pin | SEG6_Pin, 1);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG3_Pin |
								SEG4_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG2_Pin | SEG5_Pin, 1);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
								SEG3_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG4_Pin | SEG5_Pin, 1);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG2_Pin | SEG5_Pin |
								SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG3_Pin | SEG4_Pin, 1);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG2_Pin | SEG3_Pin |
								SEG5_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin | SEG4_Pin, 1);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG2_Pin | SEG3_Pin |
								SEG4_Pin | SEG5_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin, 1);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG3_Pin | SEG4_Pin | SEG5_Pin |
								SEG6_Pin, 1);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
								SEG3_Pin | SEG4_Pin | SEG5_Pin |
								SEG6_Pin, 0);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin | SEG1_Pin | SEG2_Pin |
								SEG3_Pin | SEG5_Pin | SEG6_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, SEG4_Pin, 1);
		break;
	default:
		break;
	}
}

void enable_7_seg(int index){
	switch (index){
	case 0:
		HAL_GPIO_WritePin(GPIOB, EN0_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN2_Pin | EN3_Pin, SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, EN1_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, EN0_Pin | EN2_Pin | EN3_Pin, SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, EN2_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN0_Pin | EN3_Pin, SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, EN3_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, EN1_Pin | EN2_Pin | EN0_Pin, SET);
		break;
	default:
		break;
	}
	display_7_seg(traffic_time_buffer[index/2][index%2]);
}


void display_traffic(int index){
	switch(traffic_state[index]){
	case DISPLAY_INIT: //trang thai mac dinh
		//TODO
		if (index == TRAFFIC_1ST){
			traffic_state[index] = DISPLAY_RED;
			setTimer(index, traffic_duration[LED_RED]*TIME_UNIT);
		}
		else {
			traffic_state[index] = DISPLAY_GREEN;
			setTimer(index, traffic_duration[LED_GREEN]*TIME_UNIT);
		}
		break;

	case DISPLAY_RED:
		display_light(index, LED_RED);

		if (isTimerFlagOn(index)){
			traffic_state[index] = DISPLAY_GREEN;
			setTimer(index, traffic_duration[LED_GREEN]*TIME_UNIT);
		}
		break;

	case DISPLAY_GREEN:
		display_light(index, LED_GREEN);

		if (isTimerFlagOn(index)){
			traffic_state[index] = DISPLAY_AMBER;
			setTimer(index, traffic_duration[LED_AMBER]*TIME_UNIT);
		}
		break;

	case DISPLAY_AMBER:
		display_light(index, LED_AMBER);

		if (isTimerFlagOn(index)){
			traffic_state[index] = DISPLAY_RED;
			setTimer(index, traffic_duration[LED_RED]*TIME_UNIT);
		}
		break;

	default:
		break;
	}
	cur_time[index] = (getCurrTimer(index)+1000)/TIME_UNIT;
	update_time_buffer(index, cur_time[index]);
}


void display_light(int index, int type){
	switch(index){
	case TRAFFIC_1ST: //day den giao thong thu nhat
		switch(type){
		case LED_RED:
			HAL_GPIO_WritePin(GPIOA, LED_R1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_G1_Pin | LED_Y1_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN:
			HAL_GPIO_WritePin(GPIOA, LED_G1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_Y1_Pin | LED_R1_Pin, GPIO_PIN_SET);
			break;
		case LED_AMBER:
			HAL_GPIO_WritePin(GPIOA, LED_Y1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_R1_Pin | LED_G1_Pin, GPIO_PIN_SET);
			break;
		default:
			break;
		}
		break;
	case TRAFFIC_2ND: //day den giao thong thu hai
		switch(type){
		case LED_RED:
			HAL_GPIO_WritePin(GPIOA, LED_R2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_G2_Pin | LED_Y2_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN:
			HAL_GPIO_WritePin(GPIOA, LED_G2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_Y2_Pin | LED_R2_Pin, GPIO_PIN_SET);
			break;
		case LED_AMBER:
			HAL_GPIO_WritePin(GPIOA, LED_Y2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, LED_R2_Pin | LED_G2_Pin, GPIO_PIN_SET);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void display_time(){
	if (isTimerFlagOn(TIMER_7SEG)){
		setTimer(TIMER_7SEG, 250);
		enable_7_seg(led_7seg_index);
		led_7seg_index = (led_7seg_index+1)%4;
	}
}

