
#include <stdio.h>

#include "binary.h"
#include "ads1220.h"
#include "use.h"

#define led_toggle()		(HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin))
#define led_on()			(HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET))
#define led_off()			(HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET))

i32 raw;

extern void tim_callback(){
	led_on();
	raw = ads1220_read_rdata();
	led_off();
}

extern void setup(void){
	ads1220_begin();
}

extern void loop(void){
	printf("%ld \r\n",raw);
}

