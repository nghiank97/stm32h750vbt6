
#include "led.h"

LED::LED(GPIO_TypeDef * led_port, u16 led_pin){
	port = led_port;
	pin = led_pin;

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	if (port == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else if (port == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	else if (port == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else if (port == GPIOD)
		__HAL_RCC_GPIOD_CLK_ENABLE();
	else if (port == GPIOE)
		__HAL_RCC_GPIOE_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);

	/*Configure GPIO pin : LED_Pin */
	GPIO_InitStruct.Pin = led_pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void LED::write(u08 s){
	if (s == 0){
		level = 0;
		HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
	}
	else{
		level = 1;
		HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
	}
}

void LED::toggle(void){
	if (level == 0){
		HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
		level = 1;
	}
	else{
		HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
		level = 0;
	}
}
