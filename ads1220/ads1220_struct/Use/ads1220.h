
#ifndef _ADS1220_H_
#define _ADS1220_H_
#include "binary.h"
#include "main.h"

//ADS1220 SPI commands
#define SPI_MASTER_DUMMY    	0xFF
#define RESET   				0x06   		//Send the RESET command (06h) to make sure the ADS1220 is properly reset after power-up
#define START   				0x08    	//Send the START/SYNC command (08h) to start converting in continuous conversion mode
#define STOP   					0x02
#define WREG  					0x40
#define RREG  					0x20

//Config registers
#define CONFIG_REG0_ADDRESS 	0x00
#define CONFIG_REG1_ADDRESS 	0x01
#define CONFIG_REG2_ADDRESS 	0x02
#define CONFIG_REG3_ADDRESS 	0x03

typedef struct __ADS1220_CHIP{
	// The set of @ref \__ADS1220_CHIP select control callback func.
	struct _CS{
		// @ref \__ADS1220_CHIP selected
		void 		(*_select)  	(void);
		// @ref \__ADS1220_CHIP deselected
		void 		(*_deselect)	(void);
	}CS;
	// The set of interface IO callback func.
	union _IF{
		// For SPI interface IO
		struct{
			u08		(*_read_byte)	(void);
			void	(*_write_byte)	(u08 wb);
			void	(*_transfer)	(u08* tx, u08* rx, u16 len);
		}SPI;
		// For BUS interface IO
		struct{
			u08		(*_drdy)		(void);
		}BUS;
	}IF;
	struct _VALUE{
		i32 raw;
		f32 mv;
		f32 v;
		f32 F;
	}VALUE;
}ads1220_t;

void reg_ads1220_cs_cbfunc(void (*cs_sel)(void), void (*cs_desel)(void));
void reg_ads1220_drdy_cbfunc(u08 (*read_drdy)(void));
void reg_ads1220_spi_cbfunc(u08 (*spi_rb)(void), void (*spi_wb)(u08 wb));
void reg_ads1220_spiburst_cbfunc(void (*spi_rb)(u08 *tx, u08* rx, u16 len));

void ads1220_cmd(u08 cmd);
void ads1220_write_reg(u08 add, u08 value);
u08 ads1220_read_reg(u08 add);

void ads1220_int(void);

void ads1220_start_conv(void);
void ads1220_stop_conv(void);
void ads1220_reset(void);

i32 ads1220_read_continuous();

i32 ads1220_raw(void);
f32 ads1220_m_vol(void);
f32 ads1220_vol(void);
f32 ads1220_force(void);

#endif /* _ADS1220_H_ */

