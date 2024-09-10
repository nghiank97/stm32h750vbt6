
#include "uart.h"

UART::UART(UART_HandleTypeDef * uart){
	this->uart = uart;
}

HAL_StatusTypeDef UART::write(u08 s){
	return HAL_UART_Transmit(uart, &s, 1, 100);
}

HAL_StatusTypeDef UART::print(u08* data, u16 len){
	return HAL_UART_Transmit(uart, data, len, 100);
}

u08 UART::read(void){
	u08* data = {0};
	HAL_UART_Receive(uart, data, 1, 100);
	return data[0];
}
