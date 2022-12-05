/*
 * uart.c
 *
 *  Created on: Nov 18, 2022
 *      Author: Qui
 */

#include "uart.h"

UART_HandleTypeDef huart2;

void uart_init() {
	sprintf(tx_data, "Uart Initialized\r\n");
	HAL_UART_Transmit(&huart2, &tx_data, sizeof(tx_data), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_data, 1);
}

void Str_UART(char str[]) {
	sprintf(tx_data, "");
	rx_data = "";
	sprintf(tx_data, "%s\r\n", str);
	HAL_UART_Transmit(&huart2, tx_data, sizeof(tx_data), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_data, 1);
}

void Digit_UART(char str[], uint32_t data) {
	sprintf(tx_data, "");
	rx_data = "";
	sprintf(tx_data, "%s%d\r\n", str, data);
	HAL_UART_Transmit(&huart2, tx_data, sizeof(tx_data), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_data, 1);
}
