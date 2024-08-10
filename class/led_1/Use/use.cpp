
#include "use.h"
#include "gpio.hpp"

using pin_a1 =gpio::output_pin<gpio::pin<
		gpio::port::a,
		gpio::pins<1>,
		gpio::output_pp_mode,
		gpio::pull::up,
		gpio::speed::low>>;

/** @brief 	gpio test init
  * @note
  * @param	void
  * @return void
  */
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






