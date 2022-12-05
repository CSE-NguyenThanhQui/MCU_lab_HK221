/*
 * uart.h
 *
 *  Created on: Nov 18, 2022
 *      Author: Qui
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdio.h>
#include <stdint.h>
#include "main.h"

extern UART_HandleTypeDef huart2;

uint32_t rx_data;
uint32_t tx_data[10];

void uart_init();
void Str_UART(char str[]);
void Digit_UART(char str[], uint32_t data);

#endif /* INC_UART_H_ */
