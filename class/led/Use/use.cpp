
#include "use.h"
#include "led.h"

LED led_1 = LED(GPIOA, GPIO_PIN_1);

extern void setup(void){

}

extern void loop(void){
	led_1.toggle();
	HAL_Delay(500);
}






