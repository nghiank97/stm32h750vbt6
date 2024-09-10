
#include "ads1285.h"

#ifdef STM32H750xx

#ifndef delay_ms
#define delay_ms(t) HAL_Delay(t)
#endif

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..K) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be GPIO_PIN_x where x can be (0..15).
  * @retval The input port pin value.
  */
ADS1285::ADS1285(
	SPI_HandleTypeDef _spi,
	GPIO_TypeDef* _drdy_port	, u16 _drdy_pin,
	GPIO_TypeDef* _cs_port		, u16 _cs_pin,
	GPIO_TypeDef* _pwdn_port	, u16 _pwdn_pin,
	GPIO_TypeDef* _rs_port		, u16 _rs_pin,
	GPIO_TypeDef* _sync_port	, u16 _sync_pin
){
	spi = _spi;

	drdy_port 	= _drdy_port;
	cs_port 	= _cs_port;
	pwdn_port 	= _pwdn_port;
	rs_port 	= _rs_port;
	sync_port 	= _sync_port;

	drdy_pin 	= _drdy_pin;
	cs_pin 		= _cs_pin;
	pwdn_pin 	= _pwdn_pin;
	rs_pin 		= _rs_pin;
	sync_pin 	= _sync_pin;
}

inline u08 ADS1285::drdy_read(void){
	return (u08)HAL_GPIO_ReadPin(drdy_port, drdy_pin);
}
inline void ADS1285::cs_low(void){
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET);
}
inline void ADS1285::cs_high(void){
	HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET);
}
inline void ADS1285::pwdn_high(void){
	HAL_GPIO_WritePin(pwdn_port, pwdn_pin, GPIO_PIN_SET);
}
inline void ADS1285::pwdn_off(void){
	HAL_GPIO_WritePin(pwdn_port, pwdn_pin, GPIO_PIN_RESET);
}
inline void ADS1285::rs_low(void){
	HAL_GPIO_WritePin(rs_port, rs_pin, GPIO_PIN_RESET);
}
inline void ADS1285::rs_high(void){
	HAL_GPIO_WritePin(rs_port, rs_pin, GPIO_PIN_SET);
}
inline void ADS1285::sync_low(void){
	HAL_GPIO_WritePin(sync_port, sync_pin, GPIO_PIN_RESET);
}
inline void ADS1285::sync_high(void){
	HAL_GPIO_WritePin(sync_port, sync_pin, GPIO_PIN_SET);
}

void ADS1285::read_reg_cmd(address_t add, u08 *rx, u08 len){
	u08 tx[20] = {0};
	u08 rrrr,nnnn;
	// get start register address
	rrrr = static_cast<u08>(add)&B00001111;
	nnnn = (static_cast<u08>(len)-1)&B00001111;
	tx[0] = _RREG|rrrr;
	cs_low();
	HAL_SPI_TransmitReceive(&spi, tx, rx, nnnn+1, 100);
	while (HAL_SPI_GetState(&spi) != HAL_SPI_STATE_READY) {}
	cs_high();
}

void ADS1285::write_reg_cmd(address_t add, u08 *tx, u08 len){
	u08 buff[2] = {0};
	u08 rrrr,nnnn;
	rrrr = static_cast<u08>(add)&B00001111;
	nnnn = (static_cast<u08>(len)-1)&B00001111;

	buff[0] = _WREG|nnnn;
	buff[1] = rrrr;

	cs_low();
	HAL_SPI_Transmit(&spi, buff, 2, 100);
	HAL_SPI_Transmit(&spi, tx, nnnn+1, 100);
	while (HAL_SPI_GetState(&spi) != HAL_SPI_STATE_READY) {}
	cs_high();
}

bool ADS1285::read_data_direct(u32 *data){
	if (!drdy_read()){
		u08 tx[4] = {0};
		u08 rx[4] = {0};
		cs_low();
		HAL_SPI_TransmitReceive(&spi, tx, rx, 4, 100);
		while (HAL_SPI_GetState(&spi) != HAL_SPI_STATE_READY) {}
		cs_high();
		*data = (rx[0]<<24) + (rx[1]<<16) + (rx[2]<<8) + rx[3];
		return true;
	}
	else{
		return false;
	}
}

void ADS1285::read_conversion_data_cmd(u32 *data){
	u08 tx[5] = {_RDATA, 0, 0, 0, 0};
	u08 rx[5] = {0};
	cs_low();
	HAL_SPI_TransmitReceive(&spi, tx, rx, 5, 100);
	while (HAL_SPI_GetState(&spi) != HAL_SPI_STATE_READY) {}
	cs_high();
	*data = (rx[1]<<24) + (rx[2]<<16) + (rx[3]<<8) + rx[4];
}

/**
  * @brief  Initialize ADS1285.
  * @param  v_ref: Vref of ADS1285.
  * @param  gain: gain of ADS1285.
  * @retval void.
  */
bool ADS1285::init(
		sync_t syn,
		input_mux_t mux,
		vref_t v_ref,
		gain_t gain){

	u08 reg = 0;
	u08 iden = 0;
	// reset by RST pin (hardware)
	rs_low();
	delay_ms(10);
	rs_high();

	read_reg_cmd(ID_SYNC, &iden, 1);
	if (!(iden&0x1C)){
		return false;
	}

	reg = 0;
    reg = syn;   			// Continuouse-sys
    write_reg_cmd(ID_SYNC, &reg, 1);delay_ms(10);

	reg = 0;
    reg = (MID<<6)|   		// Power mode selection: mid
    	  (SPS_1000<<3);   	// Datarate selection
    write_reg_cmd(CONFIG0, &reg, 1);delay_ms(10);

    reg = 0;
    reg = (mux<<5)|   		// Input 1
    	  (v_ref<<4)|   	// Vref 2.5f
		  (gain<<0);   		// Gain 32
    write_reg_cmd(CONFIG1, &reg, 1);delay_ms(10);
    return true;
}
/**
  * @brief  read the raw data
  * @retval data (u32).
  */
u32 ADS1285::read_raw(void){
	return 0;
}
/**
  * @brief  read the raw data
  * @retval data (i32).
  */
i32 ADS1285::read_raw_int(void){
	return 0;
}

#endif

