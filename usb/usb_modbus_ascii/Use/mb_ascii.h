
#ifndef _MB_ASCII_H
#define _MB_ASCII_H

#ifdef __cplusplus
extern "C"{
#endif

#include "binary.h"
#include "main.h"

typedef enum{
	RX_IDLE = 0,
	RX_START = 1,
	RX_COMPLETE = 2,
	TX_IDLE = 3,
	TX_START = 4,
	TX_COMPLETE = 5
}mb_state_t;

typedef enum{
	MB_NONE = 0,
	MB_ID_ERROR = 1,
	MB_FUNC_ERROR = 2,
	MB_ADD_ERROR = 3,
	MB_CRC_ERROR = 4
}mb_error_t;

typedef enum{
	MB_FUNC_04 = 4,
	MB_FUNC_16 = 16,
	MB_FUNC_06 = 6
}mb_func_t;

u08* split_to_ascii(u08 b_hex);

void mb_gpio_init(void);

void mb_init(u08 id);

void mb_rx_call_back(u08 c);
void mb_rx_enable(void);

void mb_tx_call_back(void);
void mb_tx_enable(void);
void mb_tx_data(u08 data[], u16 lenght);

void mb_poll(void);
mb_error_t mb_execute(u08* line, u16 len);
void mb_response(mb_func_t func, u16 add, u16 len, u08* data);

extern mb_error_t mb_input_register_cb(u08* data_frame, u16 begin_add, u16 len);
extern mb_error_t mb_holding_register_cb(u08* data_frame, u16 begin_add, u16 len);

#ifdef __cplusplus
}
#endif

#endif /* _MB_ASCII_H */
