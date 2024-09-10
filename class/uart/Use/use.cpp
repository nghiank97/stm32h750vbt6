
#include "use.h"
#include "uart.h"

UART uart = UART(&huart1);

extern void setup(void){

}

char* data = "hello world\r\n";

extern void loop(void){
	uart.print(reinterpret_cast<u08*>(data), 13);
	HAL_Delay(500);
}
