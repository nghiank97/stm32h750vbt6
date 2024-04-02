
#include "use.h"

uint8_t tx_data[64];
uint16_t len_tx_data;
uint8_t mystring[]="Hello World !!!\r\n";

extern void setup(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
	CDC_Transmit_FS(mystring,strlen((const char*)mystring));
}

uint16_t adc_0 = 0;
uint16_t adc_1 = 0;

extern void loop(void){
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	adc_0 = HAL_ADC_GetValue(&hadc1);

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	adc_1 = HAL_ADC_GetValue(&hadc1);

	len_tx_data = sprintf(tx_data,"adc %d %d \r\n",adc_0,adc_1);
	CDC_Transmit_FS(tx_data, len_tx_data);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
}

