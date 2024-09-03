

#include "mb_ascii.h"

#define MAX_RX_LEN							128
#define MAX_TX_LEN							128

u08 mb_id 									= 0;
volatile mb_state_t mb_status 				= RX_IDLE;

volatile u08 tx_data[MAX_TX_LEN] 			= {0};
volatile u08 tx_header 						= 0;

volatile u08 rx_data[MAX_RX_LEN] 			= {0};
volatile i08 rx_header 						= -1;

volatile u16 count_transmit					= 0;

static u08 cvt_to_ascii(u08 b_hex) {
	if (b_hex < 0x0A)
		return (b_hex + 48);
	else
		return (b_hex + 55);
}

u08* split_to_ascii(u08 b_hex) {
	static u08 nibble[2];
	nibble[0] = cvt_to_ascii(b_hex & 0x0F);
	nibble[1] = cvt_to_ascii((b_hex >> 4) & 0x0F);
	return nibble;
}

static u08 cvt_to_hex(u08 d_ascii) {
	if (('0' <= d_ascii) && (d_ascii <= '9'))
		return (d_ascii - 48);
	else if (('a' <= d_ascii) && (d_ascii <= 'f'))
		return (d_ascii - 87);
	else if (('A' <= d_ascii) && (d_ascii <= 'F'))
		return (d_ascii - 55);
	return 0x00;
}

extern u08 merge_to_hex(u08 h_nibble, u08 l_nibble) {
	u08 result = (cvt_to_hex(h_nibble) << 4) & 0xF0;
	result += cvt_to_hex(l_nibble);
	return result;
}

extern bool check_lrc(u08 frame[],int len){
    u08 sum = 0x00;
    u08 lrc;
    for (int i = 0; i < len-2; i+=2) {
        sum += merge_to_hex(frame[i], frame[i+1]);
    }
    sum = 255-sum+1;
    lrc = merge_to_hex(frame[len-2], frame[len-1]);

    if (sum == lrc)
        return true;
    return false;
}

extern u08 lrc(u08 frame[],int len){
    u08 lrc = 0x00;
    for (int i = 1; i < len; i+=2) {
        lrc += merge_to_hex(frame[i], frame[i+1]);
    }
    lrc = 255-lrc+1;
    return lrc;
}

u16 copy_arr(u08* dest, u08* source, u16 len){
	for(u16 i=0;i<len;i++){
		*dest++ = *source++;
	}
	return len;
}

void mb_gpio_init(void){
	// nothing
}

void mb_init(u08 id){
	mb_id = id;
	mb_gpio_init();
	mb_status = RX_IDLE;
}

void mb_rx_enable(void){
	// nothing
}

void mb_rx_call_back(u08 c){
	if (mb_status == RX_START){
	    char data = c;
	    if ((data == ':') && (rx_header == -1)) {
	    	rx_header = 0;
	    	return;
		}
	    if ((data != (char)(13)) && (rx_header>=0)) {
			rx_data[rx_header] = data;
			rx_header += 1;
		}
	    if ((data == (char)13) && (rx_header>=0)) {
			mb_status = RX_COMPLETE;
		}
	}
}

void mb_tx_call_back(void){
	// nothing
}

void mb_tx_enable(void){
	// nothing
}

void mb_tx_data(u08 data[], u16 lenght){
	CDC_Transmit_FS(data, lenght);
}

void mb_poll(void){
	switch (mb_status){
		case RX_IDLE:{
			rx_header = -1;
			mb_status = RX_START;
			mb_rx_enable();
			break;
		}
		case RX_COMPLETE:{
			mb_status = TX_IDLE;
			tx_header = 0;
			if (mb_execute((u08*)rx_data, rx_header) != MB_NONE){
				mb_status = TX_COMPLETE;
			}
			else{
				mb_status = TX_START;
				mb_tx_enable();
				mb_tx_data((u08*)tx_data, tx_header);
			}
			break;
		}
		case TX_START:{
			count_transmit+=1;
			if (count_transmit == 200){
				mb_status = TX_COMPLETE;
				count_transmit = 0;
			}
			break;
		}
		case TX_COMPLETE:{
			for (int i=0; i<MAX_TX_LEN; i++){
				tx_data[i] = 0;
				rx_data[i] = 0;
			}
			tx_header = 0;
			rx_header = -1;

			mb_status = RX_IDLE;
			break;
		}
		default:
			break;
	}
	return mb_status;
}


mb_error_t mb_execute(u08* line, u16 len){
	u08 id = 0x00;
	u08 dest_frame[MAX_RX_LEN];
	u16 start_add = 0x00;
	u16 len_register = 0x00;
	u08 func = 0x00;

	mb_error_t error = MB_NONE;

	if (mb_status == TX_IDLE){
		if (check_lrc(line,len)){
			id = merge_to_hex(line[0],line[1]);
			if(id == mb_id){
				func = merge_to_hex(line[2],line[3]);

				switch (func){
					case MB_FUNC_04:{
						start_add 		= merge_to_hex(line[4],line[5])*256;
						start_add 		+= merge_to_hex(line[6],line[7]);
						len_register 	= merge_to_hex(line[8],line[9])*256;
						len_register 	+= merge_to_hex(line[10],line[11]);
						error 			= mb_input_register_cb(dest_frame, start_add, len_register);

						if (error != MB_NONE){
							////mb_response_error(error);
						}
						else{
							mb_response(func, start_add, len_register, dest_frame);
						}
						break;
					}
					case MB_FUNC_06:{
						start_add 		= merge_to_hex(line[4],line[5])*256;
						start_add 		+= merge_to_hex(line[6],line[7]);
						dest_frame[0] 	= merge_to_hex(line[8],line[9]);
						dest_frame[1] 	= merge_to_hex(line[10],line[11]);

						error = mb_holding_register_cb(dest_frame, start_add, 1);
						if (error != MB_NONE){
							//mb_response_error(error);
						}
						else{
							mb_response(func, start_add, 16, line);
						}
						break;
					}
					case MB_FUNC_16:{
						start_add 		= merge_to_hex(line[4],line[5])*256;
						start_add 		+= merge_to_hex(line[6],line[7]);
						len_register 	= merge_to_hex(line[8],line[9])*256;
						len_register 	+= merge_to_hex(line[10],line[11]);

						for(int i=0;i<len_register*2;i++){
							dest_frame[i] = merge_to_hex(line[14+2*i],line[15+2*i]);
						}

						error = mb_holding_register_cb(dest_frame, start_add, (u16)len_register);
						if (error != MB_NONE){
							//mb_response_error(error);
						}
						else{
							mb_response(func, start_add, 12, line);
						}
						break;
					}
					default:{
						////mb_response_error(MB_FUNC_ERROR);
						error = MB_FUNC_ERROR;
						break;
					}
				}
			}
			else{
				////mb_response_error(MB_ID_ERROR);
				error = MB_ID_ERROR;
			}
		}
		else{
			error = MB_CRC_ERROR;
			////mb_response_error(MB_CRC_ERROR);
		}
	}
	return error;
}

void mb_response(mb_func_t func, u16 add, u16 len, u08* data){
	switch (func){
		case MB_FUNC_04:{
			u08 buff;
			u08 *nibble;
			/* header */
			tx_data[0] = ':';
			tx_header = 1;
			/* id */
			nibble = split_to_ascii(mb_id);
			tx_data[1] = nibble[1];
			tx_data[2] = nibble[0];
			tx_header+=2;
			/* function */
			tx_data[3] = '0';
			tx_data[4] = '4';
			tx_header+=2;
			/* len */
			nibble = split_to_ascii(len*2);
			tx_data[5] = nibble[1];
			tx_data[6] = nibble[0];
			tx_header+=2;

			for (int i=0;i<len*2;i++){
				nibble = split_to_ascii(data[i]);
				tx_data[7+2*i] = nibble[1];
				tx_data[8+2*i] = nibble[0];
				tx_header+=2;
			}

			buff = lrc((u08*)tx_data, tx_header);
			nibble = split_to_ascii(buff);
			tx_data[tx_header] = nibble[1];
			tx_data[tx_header+1] = nibble[0];
			tx_header+=2;
			tx_data[tx_header] = '\r';
			tx_data[tx_header+1] = '\n';
			tx_header+=2;

			break;
		}
		case MB_FUNC_06:{
			tx_data[0] = ':';
			tx_header = copy_arr((u08*)&tx_data[1], data, len);
			tx_header+=1;
			tx_data[tx_header] = '\r';
			tx_data[tx_header+1] = '\n';
			tx_header+=2;
			break;
		}
		case MB_FUNC_16:{
			u08 check;
			u08 *nibble;
			tx_data[0] = ':';
			tx_header = copy_arr((u08*)&tx_data[1], data, len);
			tx_header +=1;
			check = lrc(tx_data, tx_header);
			nibble = split_to_ascii(check);
			tx_data[tx_header] = nibble[1];
			tx_data[tx_header+1] = nibble[0];
			tx_header+=2;
			tx_data[tx_header] = '\r';
			tx_data[tx_header+1] = '\n';
			tx_header+=2;
			break;
		}
		default:{
			break;
		}

	}
}

