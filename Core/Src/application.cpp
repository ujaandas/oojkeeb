/*
 * application.cpp
 *
 *  Created on: Nov 21, 2024
 *      Author: ooj
 */

#include "main.h"
#include <cstring>

extern "C" {

extern UART_HandleTypeDef huart1;

void send_at_command(const char* command) {
	HAL_UART_Transmit(&huart1, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);
	HAL_Delay(100); // Delay to allow the command to be processed
}

void main_cpp() {
	uint8_t rx_buffer;
	send_at_command("AT+RST\r\n");

	while (1) {
		if (HAL_UART_Receive(&huart1, &rx_buffer, 1, 1000) == HAL_OK) {
			if (rx_buffer == 'o') {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			} else if (rx_buffer == 'X') {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			}
		}
	}
}


}


