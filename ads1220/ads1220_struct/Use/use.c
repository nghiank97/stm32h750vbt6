
#include <stdio.h>

#include "binary.h"
#include "ads1220.h"
#include "use.h"

u08 read_drdy(void){
	return (u08)HAL_GPIO_ReadPin(
			ADS_DRDY_GPIO_Port,
			ADS_DRDY_Pin);
}
void spi_cs_l(void){
	HAL_GPIO_WritePin(ADS_CS_GPIO_Port, ADS_CS_Pin, GPIO_PIN_RESET);
}
void spi_cs_h(void){
	HAL_GPIO_WritePin(ADS_CS_GPIO_Port, ADS_CS_Pin, GPIO_PIN_SET);
}
void spi_write(u08 data){
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
}
u08 spi_read(void){
	u08 c = 0;
	HAL_SPI_Receive(&hspi1, &c, 1, 1000);
	return c;
}
void spi_transfer(u08* tx, u08* rx, u16 len){
	HAL_SPI_TransmitReceive(&hspi1, tx, rx, len, 1000);
}

extern void drdy_callback(){
	ads1220_read_continuous();
}

extern void setup(void){
	reg_ads1220_drdy_cbfunc(read_drdy);
	reg_ads1220_cs_cbfunc(spi_cs_l,spi_cs_h);
	reg_ads1220_spi_cbfunc(spi_read,spi_write);
	reg_ads1220_spiburst_cbfunc(spi_transfer);

	ads1220_int();
}

extern void loop(void){
	u32 raw = ads1220_raw();
	printf("%ld \r\n",raw);
}

