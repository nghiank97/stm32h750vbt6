
#include <stdio.h>

#include "binary.h"
#include "ads1220.h"
#include "use.h"

#define led_toggle()		(HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin))

i32 raw;

extern void drdy_callback(){
	led_toggle();
	raw = ads1220_read_continuous();
}

extern void setup(void){
	ads1220_begin();
}

extern void loop(void){
	printf("%ld \r\n",raw);
}

