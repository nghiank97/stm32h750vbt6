
#include <stdio.h>
#include <string.h>
#include "binary.h"
#include "w5500.h"
#include "socket.h"
#include "wizchip_conf.h"
#include "use.h"
#include "main.h"

void w5500_reset(void){
	HAL_Delay(1000);
	HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(W5500_RST_GPIO_Port, W5500_RST_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
}
void w5500_cs_l(void){
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);
}
void w5500_cs_h(void){
	HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
}
void w5500_spi_write(u08 data){
	HAL_SPI_Transmit(&hspi3, &data, 1, 100);
}
u08 w5500_spi_read(void){
	u08 c = 0;
	HAL_SPI_Receive(&hspi3, &c, 1, 100);
	return c;
}
void w5500_spi_write_page(u08* pBuf, u16 len){
	HAL_SPI_Transmit(&hspi3, pBuf, len, 100);
}
void w5500_spi_read_page(u08* pBuf, u16 len){
	HAL_SPI_Receive(&hspi3, pBuf, len, 100);
}

u08 txsize[8] = {4,2,2,2,2,2,2,2};
u08 rxsize[8] = {4,2,2,2,2,2,2,2};

wiz_NetInfo gWIZNETINFO = {
							.mac = {0x08,0x10,0x19,0x97,0x25,0x25},
							.ip = {192,168,1,47},
							.sn = {255, 255, 255, 0},
							.gw = {192, 168, 1, 1},
							.dns = {8, 8, 8, 8},
							.dhcp = NETINFO_STATIC
};
u16 local_port=5004;
#define W5500_DEBUG
#define ETH_MAX_BUF_SIZE	512
u08 buffer[ETH_MAX_BUF_SIZE];

/* udp info */
u08 remote_ip[4]={192,168,1,2};
u16 remote_port=5002;

u16 len=0;

u08 tx_debug[ETH_MAX_BUF_SIZE];
u16 tx_len = 0;

extern void setup(){
	w5500_reset();
	/* initialize w5500 */
	reg_wizchip_cs_cbfunc(w5500_cs_l, w5500_cs_h);
	reg_wizchip_spi_cbfunc(w5500_spi_read, w5500_spi_write);
	reg_wizchip_spiburst_cbfunc(w5500_spi_read_page, w5500_spi_write_page);
	wizchip_init(txsize, rxsize);
	wizchip_setnetinfo(&gWIZNETINFO);
#ifdef W5500_DEBUG
	u08 net_ip[4] = {0};
	u08 net_sub[4] = {0};
	u08 net_gw[4] = {0};
	u08 net_mac[6] = {0};
	
	getSIPR(net_ip);
	getSHAR(net_mac);
	getSUBR(net_sub);
	getGAR(net_gw);
	
	tx_len = sprintf((char*)tx_debug, "ip: %03d.%03d.%03d.%03d\r\n", net_ip[0], net_ip[1], net_ip[2], net_ip[3]);
	CDC_Transmit_FS(tx_debug,tx_len);
	tx_len = sprintf((char*)tx_debug, "sn: %03d.%03d.%03d.%03d\r\n", net_sub[0], net_sub[1], net_sub[2], net_sub[3]);
	CDC_Transmit_FS(tx_debug,tx_len);
	tx_len = sprintf((char*)tx_debug, "gw: %03d.%03d.%03d.%03d\r\n", net_gw[0], net_gw[1], net_gw[2], net_gw[3]);
	CDC_Transmit_FS(tx_debug,tx_len);
	tx_len = sprintf((char*)tx_debug, "mac: %02x.%02x.%02x.%02x.%02x.%02x\r\n", net_mac[0], net_mac[1], net_mac[2], net_mac[3], net_mac[4], net_mac[5]);
	CDC_Transmit_FS(tx_debug,tx_len);
#endif
}

extern void loop(){
	switch(getSn_SR(0)){
		case SOCK_UDP:

/********************* receiver *************************************/
			if(getSn_IR(0) & Sn_IR_RECV){
				setSn_IR(0, Sn_IR_RECV);
			}
			len=getSn_RX_RSR(0);
			if(len>0){
				memset(buffer,0,len+1);
				recvfrom(0,buffer, len, remote_ip, &remote_port);
				CDC_Transmit_FS(buffer,len);
				sendto(0,buffer,len, remote_ip, remote_port);
			}
/********************* transmit *************************************/
			tx_len = sprintf((char*)tx_debug, "welcome !\r\n");
			CDC_Transmit_FS(tx_debug, tx_len);
			sendto(0, tx_debug, tx_len, remote_ip, remote_port);

			break;
		case SOCK_CLOSED:
			socket(0,Sn_MR_UDP,local_port,0);
			break;
		default:
			break;
	}
}