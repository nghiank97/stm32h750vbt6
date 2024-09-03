#ifndef USE_H
#define USE_H

#ifdef __cplusplus
extern "C"{
#endif

#include "binary.h"
#include "mb_ascii.h"
#include "main.h"

extern void setup(void);
extern void loop(void);

extern void upload_data(void);

extern void USBD_RX_CallBack(u08 *rx, u16 len);
extern void USBD_TX_CallBack(void);

extern mb_error_t mb_input_register_cb(u08* data_frame, u16 begin_add, u16 len);
extern mb_error_t mb_holding_register_cb(u08* data_frame, u16 begin_add, u16 len);

#ifdef __cplusplus
}
#endif

#endif
