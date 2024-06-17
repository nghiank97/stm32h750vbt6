/*
 * mpu6050.h
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 */

#ifndef INC_GY521_H_
#define INC_GY521_H_

#endif /* INC_GY521_H_ */

#include <stdint.h>
#include "binary.h"
#include "main.h"
// MPU6050 structure
typedef struct
{

    i16 Accel_X_RAW;
    i16 Accel_Y_RAW;
    i16 Accel_Z_RAW;
    f32 Ax;
    f32 Ay;
    f32 Az;

    i16 Gyro_X_RAW;
    i16 Gyro_Y_RAW;
    i16 Gyro_Z_RAW;
    f32 Gx;
    f32 Gy;
    f32 Gz;

    float Temperature;

    f32 KalmanAngleX;
    f32 KalmanAngleY;
} MPU6050_t;

// Kalman structure
typedef struct
{
    f32 Q_angle;
    f32 Q_bias;
    f32 R_measure;
    f32 angle;
    f32 bias;
    f32 P[2][2];
} Kalman_t;

u08 MPU6050_Init(I2C_HandleTypeDef *I2Cx);

void MPU6050_Read_Accel(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);

void MPU6050_Read_Gyro(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);

void MPU6050_Read_Temp(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);

void MPU6050_Read_All(I2C_HandleTypeDef *I2Cx, MPU6050_t *DataStruct);

f32 Kalman_getAngle(Kalman_t *Kalman, f32 newAngle, f32 newRate, f32 dt);
