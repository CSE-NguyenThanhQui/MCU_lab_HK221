/*
 * input_reading.c
 *
 *  Created on: 13 thg 11, 2022
 *      Author: Qui
 */


#include "input_reading.h"
#include "main.h"

//Define duration for a long pressed button
#define	LONG_PRESSED_DURATION 100

//Work for multiple buttons
#define IS_PRESSED		GPIO_PIN_RESET
#define IS_RELEASED		GPIO_PIN_SET

//Store button state in buffer after debouncing
//static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

//Store button state in 2 buffers for debouncing
int KeyReg0[NO_OF_BUTTONS] = {IS_RELEASED};
int KeyReg1[NO_OF_BUTTONS] = {IS_RELEASED};
int KeyReg2[NO_OF_BUTTONS] = {IS_RELEASED};
int KeyReg3[NO_OF_BUTTONS] = {IS_RELEASED};

int TimeOutForKeyPress[NO_OF_BUTTONS] = {500};
int flagBtn[NO_OF_BUTTONS];

void button_reading(void){
	for (int i = 0; i < NO_OF_BUTTONS; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
		switch (i){ //check which button is being read now
		case BTN_1:
			KeyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BTN_1_Pin);
			break;
		case BTN_2:
			KeyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BTN_2_Pin);
			break;
		case BTN_3:
			KeyReg0[i] = HAL_GPIO_ReadPin(GPIOA, BTN_3_Pin);
			break;
		default:
			break;
		}
		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg2[i] != KeyReg3[i]){
				KeyReg3[i] = KeyReg2[i];

				if (KeyReg3[i] == IS_PRESSED){
					TimeOutForKeyPress[i] = 500;
					subKeyProcess(i);
				}
			} else {
				TimeOutForKeyPress[i] --;
				if (TimeOutForKeyPress[i] == 0){
				  KeyReg3[i] = IS_RELEASED;
				}
			}
		}
	}
}

void subKeyProcess(int index){
	flagBtn[index] = 1;
}

int isBtnPressed(int index){
	if (flagBtn[index] == 1){
		flagBtn[index] = 0;
		return 1;
	}
	return 0;
}
