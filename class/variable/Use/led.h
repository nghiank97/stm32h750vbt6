#ifndef _LED_H
#define _LED_H

#ifdef __cplusplus
extern "C"{
#endif
#include "binary.h"
#include "main.h"

class LED{

public:
	LED(GPIO_TypeDef * led_port, u16 led_pin);
	void write(u08 s);
	void toggle(void);
private:
	GPIO_TypeDef * port;
	u16 pin;
	u08 level = 0;
};

#ifdef __cplusplus
}
#endif

#endif /* _LED_H */
