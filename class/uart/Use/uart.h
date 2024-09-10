#ifndef _UART_H
#define _UART_H

#ifdef __cplusplus
extern "C"{
#endif
#include "binary.h"
#include "main.h"

class UART{

public:
	UART(UART_HandleTypeDef * uart);
	HAL_StatusTypeDef write(u08 s);
	HAL_StatusTypeDef print(u08* data, u16 len);
	u08 read(void);
private:
	UART_HandleTypeDef * uart;
};

#ifdef __cplusplus
}
#endif

#endif /* _LED_H */
