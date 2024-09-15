#include "binary.h"
#include "use.h"

#define LED_OFF() 			{GPIOA->ODR |= (1<<1);}
#define LED_ON() 			{GPIOA->ODR &=~ (1<<1);}
#define LED_TOGGLE() 		{GPIOA->ODR ^= (1<<1);}

extern void setup(void){
	// enable clock GPIO A
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
	// general purpose output mode
	GPIOA->MODER &=~ (B11<<2);
	GPIOA->MODER |= (B01<<2);
	// output push-pull
	GPIOA->OTYPER &=~ (B1<<1);
	// Medium speed
	GPIOA->OSPEEDR &=~ (B11<<2);
	GPIOA->OSPEEDR |= (B01<<2);
}

extern void loop(void){
	LED_TOGGLE();
	HAL_Delay(500);
}

