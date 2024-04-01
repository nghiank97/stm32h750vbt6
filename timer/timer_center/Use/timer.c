
#include "main.h"

extern void timer_init(void){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
}
extern void timer_call_back(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

extern void timer_start(void){
	HAL_TIM_Base_Start_IT(&htim1);
}

extern void timer_stop(void){

}

extern void timer_compare(u16 a){
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, a);
}
