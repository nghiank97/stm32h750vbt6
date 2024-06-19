#include <stdio.h>
#include "main.h"
#include "use.h"
#include "mpu6050.h"
#include <math.h>

MPU6050_t MPU6050;

void setup(void){
	HAL_Delay(500);
	while (MPU6050_Init(&hi2c1) == 1);
	CDC_Transmit_FS("Finish !\r\n", 10);
}

f32 roll, pitch, yaw;

u08 tx_data[128] = {0};
u16 tx_len = 0;

void CalculateAccAngle(f32 *roll, f32 *pitch, f32 *yaw, f32 acc_x, f32 acc_y, f32 acc_z)
{
	*roll  = atan(-acc_x / sqrt(acc_y*acc_y + acc_z*acc_z)) * RAD_TO_DEG;
	*pitch = atan(acc_y / sqrt(acc_x*acc_x + acc_z*acc_z)) * RAD_TO_DEG;
	*yaw = atan(sqrt(acc_x*acc_x + acc_y*acc_y) / acc_z) * RAD_TO_DEG;
}

void loop(void){

	MPU6050_Read_All(&hi2c1, &MPU6050);

	CalculateAccAngle(&roll, &pitch, &yaw, MPU6050.Ax, MPU6050.Ay, MPU6050.Az);

//	tx_len = sprintf((char*)tx_data, "%0.2f\t%0.2f\t%0.2f\r\n", MPU6050.Ax, MPU6050.Ay, MPU6050.Az);
//	CDC_Transmit_FS(tx_data, tx_len);
	tx_len = sprintf((char*)tx_data, "%0.2f\t%0.2f\t%0.2f\r\n", roll, pitch, yaw);
	CDC_Transmit_FS(tx_data, tx_len);

//	tx_len = sprintf((char*)tx_data, "%0.2f\t%0.2f\t%0.2f\r\n", Gx, Gy, Gz);
//	CDC_Transmit_FS(tx_data, tx_len);
	HAL_Delay (100);
}
