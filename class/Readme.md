# Class 

# 1. Led

```cpp
// LED class Contruction
LED::LED(GPIO_TypeDef * led_port, u16 led_pin){
}
void LED::write(u08 s){
}
void LED::toggle(void){
}
// Instance LED class
LED led_a1 = LED(GPIOA, GPIO_PIN_1);
```
# 2. Led 1

[ref : stm32-hal-cpp](https://github.com/tomikaa87/stm32-hal-cpp)

```cpp
using pin_a1 =gpio::output_pin<gpio::pin<
		gpio::port::a,
		gpio::pins<1>,
		gpio::output_pp_mode,
		gpio::pull::up,
		gpio::speed::low>>;

static void gpio_test(void)
{
    pin_a1::init();
    pin_a1::set();
}

extern void setup(void){
	gpio_test();
}

extern void loop(void){
	pin_a1::toggle();
	HAL_Delay(1000);
}
```
