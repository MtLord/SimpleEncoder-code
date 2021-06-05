

#include <math.h>
#include <MPU6500/mpu6500.h>
#include "DefineLED.h"
#define RAD_TO_DEG 57.295779513082320876798154814105

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43

#define FS_250DPS 0x00
#define FS_500DPS 0x01
#define FS_1000DPS 0x02
#define FS_2000DPS 0x03

#define CONVDEG_250DPS 131
#define CONVDEG_500DPS 65.5
#define CONVDEG_1000DPS 32.8
#define CONVDEG_2000PS 16.4

#define CH_DEG_VAL CONVDEG_250DPS
// Setup MPU6050
#define MPU6050_ADDR 0xD0
const uint16_t i2c_timeout = 10;

uint32_t timer;



uint8_t MPU6500::Init()
{
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I

    if(HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1,i2c_timeout)!=0)
    {
    	return -1;
    	ERROR_LED;
    }

    if (check == 0x71) // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1,i2c_timeout);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x00;//1000hz
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1,i2c_timeout);


        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 500 dps
        Data = FS_500DPS<<3;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1,i2c_timeout);
        CalcOffset();
        return 0;
    }

    return -2;
}


int MPU6500::Read_Gyro()
{
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    if(HAL_I2C_Mem_Read_IT(I2Cx, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6)!=0)
    {
    	return 1;
    }

    Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into dps (�/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/

    Gx = Gyro_X_RAW / CH_DEG_VAL;
    Gy = Gyro_Y_RAW / CH_DEG_VAL;
    Gz = Gyro_Z_RAW / CH_DEG_VAL;
    return 0;
}

double MPU6500::GetGyroZ()
{
	return Gz-Gz_offset;
}

double MPU6500::GetGyroX()
{
	return Gx-Gx_offset;
}

double MPU6500::GetGyroY()
{
	return Gy-Gy_offset;
}

void MPU6500::CalcOffset()
{

	for(int i=0;i<sample_num;i++)
	{
		Read_Gyro();
		sample[i]=GetGyroZ();
		HAL_Delay(1);//ms
	}
	for(int i=0;i<sample_num;i++)
	{
		hataverage+=sample[i]*sample[i]/sample_num;
		average+=(sample[i]/sample_num);
	}
		stddev=sqrt(hataverage-average*average);
		this->Gz_offset=average;
}

void MPU6500::SetYaw()
{

		if(Read_Gyro()==0)
			{
				if(ledcount>85)
				{
					TOGGLE_GYRO_LED;
					ledcount=0;
				}
				ledcount++;
				gyro_ok=true;
			}
			else
			{
				if(error_led>70)
				{
					ERROR_LED;
					error_led=0;
				}
				error_led++;
			}


	curvel=GetGyroZ();

	if((Gz<(average-stddev*cutoffmag))||Gz>(average+stddev*cutoffmag))//cutoff noises
	{
		deg+=((curvel+prevel)*dt)/2;
		prevel=curvel;
	}
}

void MPU6500::SetYawVel()
{
	if(Read_Gyro()==0)
	{
		if(ledcount>85)
		{
			TOGGLE_GYRO_LED;
			ledcount=0;
		}
		ledcount++;
	}
	else
	{
			if(error_led>70)
			{
				ERROR_LED;
				error_led=0;
			}
			error_led++;
	}
	if((Gz<(average-stddev*cutoffmag))||Gz>(average+stddev*cutoffmag))//cutoff noises
	{
		curvel=GetGyroZ();
	}
	else
	{
		curvel=0;
	}
}
float MPU6500::GetYawVel()
{
	return curvel*PI/180;
}

float MPU6500::GetYaw()
{
	return deg*PI/180;
}
