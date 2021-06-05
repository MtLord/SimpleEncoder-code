/*
 * mpu6050.h
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 */

#ifndef INC_GY521_H_
#define INC_GY521_H_



#include <stdint.h>
#include "i2c.h"


class MPU6500
{
	 const double PI=3.14159265;
	 int16_t Gyro_X_RAW=0;
	 int16_t Gyro_Y_RAW=0;
	 int16_t Gyro_Z_RAW=0;;
	 double Gx=0;
	 double Gy=0;
	 double Gz=0;
	 double Gx_offset=0;
	 double Gy_offset=0;
	 double Gz_offset=0;

	 double stddev=0;
	 double hataverage=0;
	 double average=0;

	 int sample_num=500;
	 float cutoffmag=2.5;
	 double sample[500];
	 double deg=0;
	 double prevel=0;
	 double curvel=0;

	 int ledcount=0;
	 int error_led=0;
	 bool gyro_ok=false;
	 const float dt=0.005;
	 I2C_HandleTypeDef *I2Cx;

	 double GetGyroX();
	 double GetGyroY();

public:
	 MPU6500(I2C_HandleTypeDef *I2Cx)
	{
		 this->I2Cx=I2Cx;

	}
	 uint8_t Init();
	 int Read_Gyro();
	 double GetGyroZ();
	 void CalcOffset();
	 void SetYaw();
	 void SetRoll();
	 void SetPitch();
	 float GetYaw();
	 float GetPitch();
	 float GetRoll();
	 void SetYawVel();
	 float GetYawVel();
};


#endif /* INC_GY521_H_ */



