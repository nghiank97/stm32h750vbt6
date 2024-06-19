
#include "main.h"
#include "use.h"
#include "mpu6050.h"

MPU6050_t MPU6050;

void setup(void){
	while (MPU6050_Init(&hi2c1) == 1);
}

void loop(void){
	MPU6050_Read_All(&hi2c1, &MPU6050);
	delay_ms (100);
}
