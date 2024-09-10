#ifndef _ADS1285_H_
#define _ADS1285_H_

#ifdef __cplusplus
extern "C"{
#endif
#include "binary.h"
#include "main.h"

#ifdef STM32H750xx

#define ADS_IDENTIFICATION 0x0000

typedef enum{
	ID_SYNC	= 0x00,
	CONFIG0 = 0x01,
	CONFIG1	= 0x02,
	HPF0	= 0x03,
	HPF1 	= 0x04,
	OFFSET0 = 0x05,
	OFFSET1	= 0x06,
	OFFSET2 = 0x07,
	GAIN0 	= 0x08,
	GAIN1 	= 0x09,
	GAIN2 	= 0x0A,
	GPIO 	= 0x0B,
	SRC0 	= 0x0C,
	SRC1 	= 0x0D
}address_t;

typedef enum{
	/* control */
	_WAKEUP		= 0x00,	// Wake from standby mode or NOP
	_STANDBY 	= 0x02,	// Enter standby (software power-down mode)
	_SYNC		= 0x04,	// Synchronize
	_RESET		= 0x06,	// Reset
	/* data */
	_RDATA 		= 0x12,	// Read conversion data
	/* register */
	_RREG 		= 0x20,	// Read nnnn registers beginning at address rrrr
	_WREG		= 0x40,	// Write nnnn registers beginning at address rrrr
	/* calibration */
	_OFSCAL 	= 0x60,	// Offset calibration
	_GANCAL 	= 0x61	// Gain calibration
}command_t;

/* ID/SYNC: Device ID, SYNC Register (Address = 00h) */

typedef enum{
	PULSE_SYNC 		= B0,	// Pulse-sync mode
	CONTINUOUS_SYNC	= B1	// Continuous-sync mode
}sync_t;

/* Configuration Register 0 (Address = 01h) */

typedef enum{
	HIGH 	= B00,
	MID 	= B01,
	LOW 	= B10
}power_modes_t;

typedef enum{
	SPS_250	= B000,
	SPS_500	= B010,
	SPS_1000= B100,
	SPS_2000= B110,
	SPS_4000= B100
}data_rate_t;

/* Configuration Register 1 (Address = 02h) */

typedef enum{
	INPUT_1	= B000,
	INPUT_2 = B001,
	RES_400	= B010,
	INPUT_12= B011,
	RES_0	= B101
}input_mux_t;

typedef enum{
	_5V 	= 0,
	_4_096V = 1,
	_2_5V 	= 2,
}vref_t;

typedef enum{
	GAIN_1 	= 1,
	GAIN_2 	= 2,
	GAIN_4 	= 4,
	GAIN_8 	= 8,
	GAIN_16 = 16,
	GAIN_32 = 32,
	GAIN_64 = 64
}gain_t;

class ADS1285{

private:
	SPI_HandleTypeDef spi;

	GPIO_TypeDef* drdy_port	; u16 drdy_pin;
	GPIO_TypeDef* cs_port	; u16 cs_pin;
	GPIO_TypeDef* pwdn_port	; u16 pwdn_pin;
	GPIO_TypeDef* rs_port	; u16 rs_pin;
	GPIO_TypeDef* sync_port	; u16 sync_pin;

	f32 vref = 2.5f;
	gain_t gain = GAIN_1;
	u32 raw_data;

	inline u08 drdy_read(void);
	inline void cs_low(void);
	inline void cs_high(void);
	inline void pwdn_high(void);
	inline void pwdn_off(void);
	inline void rs_low(void);
	inline void rs_high(void);
	inline void sync_low(void);
	inline void sync_high(void);

	bool read_data_direct(u32 *data);
	void read_conversion_data_cmd(u32 *data);
	void read_reg_cmd(address_t add, u08 *rx, u08 len);
	void write_reg_cmd(address_t add, u08 *tx, u08 len);
public:
	ADS1285(
		SPI_HandleTypeDef _spi,
		GPIO_TypeDef* _drdy_port	, u16 _drdy_pin,
		GPIO_TypeDef* _cs_port		, u16 _cs_pin,
		GPIO_TypeDef* _pwdn_port	, u16 _pwdn_pin,
		GPIO_TypeDef* _rs_port		, u16 _rs_pin,
		GPIO_TypeDef* _sync_port	, u16 _sync_pin
	);

	bool init(
			sync_t syn,
			input_mux_t mux,
			vref_t v_ref,
			gain_t gain);
	u32 read_raw(void);
	i32 read_raw_int(void);

};

#endif

#ifdef __cplusplus
}
#endif
#endif /* _ADS1285_H_ */
