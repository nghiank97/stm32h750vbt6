
#include "ads1220.h"

ads1220_t ads1220;

#ifndef delay_us
void delay_us(void){
	for(int i=0;i<100;i++);
}
#endif
#ifndef delay_ms
#define delay_ ms(t)	HAL_Delay(t)
#endif

void reg_ads1220_drdy_cbfunc(u08 (*read_drdy)(void)){
	ads1220.IF.BUS._drdy = read_drdy;
}

void reg_ads1220_cs_cbfunc(void(*cs_sel)(void), void(*cs_desel)(void)){
	ads1220.CS._select = cs_sel;
	ads1220.CS._deselect = cs_desel;
}
void reg_ads1220_spi_cbfunc(u08 (*spi_rb)(void), void (*spi_wb)(u08 wb)){
	ads1220.IF.SPI._read_byte = spi_rb;
	ads1220.IF.SPI._write_byte = spi_wb;
}
void reg_ads1220_spiburst_cbfunc(void (*spi_rb)(u08* tx, u08* rx, u16 len)){
	ads1220.IF.SPI._transfer = spi_rb;
}
void ads1220_int(void){

	u08 m_config_reg0;
	u08 m_config_reg1;
	u08 m_config_reg2;
	u08 m_config_reg3;

	ads1220.CS._deselect();
	ads1220_reset();
    delay_ms(10);

    /******************** Configuration Register 0 ********************/
    m_config_reg0 =
    		(0b0000<<4)|	// AINP=AIN0, AINN=AIN1
    		(0b101<<1)|		// Gain 32
			(0b0<<0);		// PGA enabled
    /******************** Configuration Register 1 ********************/
    m_config_reg1 =
    		(0b110<<5)|		// DR= 500SPS
    		(0b00<<3)|		// Mode= Normal
			(0b1<<2)|		// Conv mode=continuous
			(0b0<<1)|		// Temp Sensor disabled
			(0b0<<0);		// Current Source off
    /******************** Configuration Register 2 ********************/
    m_config_reg2 =
    		(0b01<<6)|		// External reference selected using AIN0/REFP1 and AIN3/REFN1 inputs
    		(0b11<<4)|	  	// simultaneous 50-Hz and 60-Hz rejection, IDAC = 500 µA
			(0b0<<3)|
			(0b101<<0);
    /******************** Configuration Register 3 ********************/

    m_config_reg3 = 0x00;   // IDAC1 disabled, IDAC2 disabled, DRDY pin only

    ads1220_write_reg( CONFIG_REG0_ADDRESS , m_config_reg0);
    delay_ms(1);
    ads1220_write_reg( CONFIG_REG1_ADDRESS , m_config_reg1);
    delay_ms(1);
    ads1220_write_reg( CONFIG_REG2_ADDRESS , m_config_reg2);
    delay_ms(1);
    ads1220_write_reg( CONFIG_REG3_ADDRESS , m_config_reg3);
    delay_ms(1);
    ads1220.CS._select();
    delay_ms(1);
}
void ads1220_cmd(u08 cmd){
    ads1220.CS._select();
    //delay_us;
    ads1220.IF.SPI._write_byte(cmd);
    //delay_us;
    ads1220.CS._deselect();
}
void ads1220_write_reg(u08 add, u08 value){
	ads1220.CS._select();
    //delay_us;
	ads1220.IF.SPI._write_byte(WREG|(add<<2));
	ads1220.IF.SPI._write_byte(value);
    //delay_us;
    ads1220.CS._deselect();
}
u08 ads1220_read_reg(u08 add){
    u08 tx[1] = {RREG|(add<<2)};
    u08 rx[1] = {0};
    ads1220.CS._select();
    //delay_us;
    ads1220.IF.SPI._transfer(tx, rx, 1);
    //delay_us;
    ads1220.CS._deselect();
    return rx[0];
}
void ads1220_reset(void){
	ads1220_cmd(RESET);
}

void ads1220_start_conv(void){
	ads1220_cmd(START);
}
void ads1220_stop_conv(void){
	ads1220_cmd(STOP);
}
u08 ads1220_read_drdy(void){
	return ads1220.IF.BUS._drdy();
}
i32 ads1220_read_continuous(void){
	u08 rx[3] = {0};
	u08 tx[3] = {0};
	i32 result = 0;

	ads1220.IF.SPI._transfer(tx, rx, 3);

    result = rx[0];
    result = (result << 8) | rx[1];
    result = (result << 8) | rx[2];
    if (rx[0] & (1<<7)) {
        result |= 0xFF000000;
    }
    ads1220.VALUE.raw = result;
    ads1220.VALUE.mv = 0;
    ads1220.VALUE.v = 0;
    ads1220.VALUE.F = 0;
    return result;
}
i32 ads1220_raw(void){
	return ads1220.VALUE.raw;
}
f32 ads1220_m_vol(void){
	return ads1220.VALUE.mv;
}
f32 ads1220_vol(void){
	return ads1220.VALUE.v;
}
f32 ads1220_force(void){
	return ads1220.VALUE.F;
}


