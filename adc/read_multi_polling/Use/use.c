
#include "use.h"

extern void setup(void){
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
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
}

