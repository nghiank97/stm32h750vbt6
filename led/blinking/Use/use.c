
#include "use.h"

extern void setup(void){
}

extern void loop(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
}

