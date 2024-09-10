#include "ads1285.h"
#include "use.h"

ADS1285 ads1285 = ADS1285{
	hspi1,
	ADS_DRDY_GPIO_Port, ADS_DRDY_Pin,
	ADS_CS_GPIO_Port, ADS_CS_Pin,
	ADS_PWDN_GPIO_Port, ADS_PWDN_Pin,
	ADS_RS_GPIO_Port, ADS_RS_Pin,
	ADS_SYNC_GPIO_Port, ADS_SYNC_Pin
};

extern void setup(void){
	if (!ads1285.init(CONTINUOUS_SYNC, INPUT_1, _2_5V, GAIN_32)){
		#ifdef _DEBUG
			printf("ADS1285 initialize error !\r\n");
		#endif
		return;
	}
}

i32 ads_data;

extern void loop(void){
	ads_data = ads1285.read_raw_int();
	delay_ms(1);
}

