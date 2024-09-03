#ifndef _GC9A01_H_
#define _GC9A01_H_

#include "binary.h"

#ifdef __cplusplus
extern "C" {
#endif

struct GC9A01_point {
    u16 X, Y;
};

struct GC9A01_frame {
    struct GC9A01_point start, end;
};

typedef enum{
	COL_ADDR_SET        = 0x2A,
	ROW_ADDR_SET        = 0x2B,
	MEM_WR              = 0x2C,
	COLOR_MODE          = 0x3A,
	COLOR_MODE__12_BIT  = 0x03,
	COLOR_MODE__16_BIT  = 0x05,
	COLOR_MODE__18_BIT  = 0x06,
	MEM_WR_CONT         = 0x3C
}GC9A01_code_t;

class GC9A01{
	private:
		SPI_HandleTypeDef spi;
		GPIO_TypeDef* cs_port;u16 cs_pin;
		GPIO_TypeDef* dc_port;u16 dc_pin;
		GPIO_TypeDef* rs_port;u16 rs_pin;

		inline void reset(void);
		inline void choose_data(void);
		inline void choose_cmd(void);
		inline void chip_select(void);
		inline void chip_unselect(void);
		void spi_tx(u08 *data, size_t len);

		void write_cmd(u08 cmd);
		void write_data(u08 val);

	public:
		GC9A01(
			SPI_HandleTypeDef _spi,
			GPIO_TypeDef* _cs_port, u16 _cs_pin,
			GPIO_TypeDef* _dc_port, u16 _dc_pin,
			GPIO_TypeDef* _rs_port, u16 _rs_pin);

		void init(void);
		void set_frame(struct GC9A01_frame frame);
		void write_datas(u08 *data, size_t len);
};

#ifdef __cplusplus
}
#endif

#endif /* _GC9A01_H_ */
