
#include "use.h"

/*
 * MODBUS
 */

#define REG_INPUT_NREGS					6
#define REG_INPUT_START					1000
#define REG_HOLDING_NREGS				6
#define REG_HOLDING_START				2000

u16 RegInputBuf[REG_INPUT_NREGS] 		= {0,0,0,0,0,0};
u16 RegHoldingBuf[REG_HOLDING_NREGS] 	= {7,10,100,100,200,20};

extern void USBD_RX_CallBack(u08 *rx, u16 len){
	for(int i=0;i<len;i++){
		mb_rx_call_back(rx[i]);
	}
}

extern void USBD_TX_CallBack(void){
	mb_tx_call_back();
}

extern void setup(void){
	mb_init(86);
	HAL_TIM_Base_Start_IT(&htim2);
}

extern void upload_data(void){
	RegInputBuf[0] = RegHoldingBuf[0];
	RegInputBuf[1] = RegHoldingBuf[1];
	RegInputBuf[2] = RegHoldingBuf[2];
	RegInputBuf[3] = RegHoldingBuf[3];
	RegInputBuf[4] = RegHoldingBuf[4];
	RegInputBuf[5] = RegHoldingBuf[5];
}

extern void loop(void){
	mb_poll();

}

extern mb_error_t mb_input_register_cb(u08* data_frame, u16 begin_add, u16 len){
	if((begin_add >= REG_INPUT_START)
        && ((begin_add + len)<=(REG_INPUT_NREGS+REG_INPUT_START))){

		u16 i = begin_add-REG_INPUT_START;
        while(len>0){
            *data_frame++ = (u08)(RegInputBuf[i]>>8);
            *data_frame++ = (u08)(RegInputBuf[i]%256);
            i++;
            len--;
        }
		return MB_NONE;
	}
	return MB_ADD_ERROR;
}

extern mb_error_t mb_holding_register_cb(u08* data_frame, u16 begin_add, u16 len){
	if((begin_add >= REG_HOLDING_START)
        && ((begin_add + len)<=(REG_HOLDING_START + REG_HOLDING_NREGS)))
	{
		u16 i = begin_add-REG_HOLDING_START;
        while(len>0){

            RegHoldingBuf[i] = (u16)(*data_frame++ << 8);
            RegHoldingBuf[i] += (u16)(*data_frame++);
            i++;
            len--;
        }
		return MB_NONE;
	}
	return MB_ADD_ERROR;
}
