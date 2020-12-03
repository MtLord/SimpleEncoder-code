/*
 * Localization.hpp
 *
 *  Created on: 2018/12/28
 *      Author: �T��
 */

#ifndef LOCALIZATION_LOCALIZATION_HPP_
#define LOCALIZATION_LOCALIZATION_HPP_
#include "MPU6500/mpu6500.h"
#include "CAN/CAN.hpp"
#include "encoder/RotaryEncoder.hpp"
#define Xencoder 0
#define Yencoder 1
class Localization
{
protected:

		float diameter=0.048;//�ڒn�G���R�[�_�̒��a
		uint16_t pulse=2048;//�G���R�[�_��1��]�̃p���X��
		float ShiftY=0.094;
		float ShiftX=0.094;
		double XX = 0;             //Present value(x axis)
		double YY = 0;             //Present value(y axis)
		double theta = 0;
		float initX=0.48;
		float initY=0.48;
		long count[2]={0,};
		float point[2]={0,};
		long b_count[2]={0,};
		double ENCR_velocity =0.00;            //velocity of the ENCR
		double ENCL_velocity =0.00;            //velocity of the ENCL
		double robot_velocity = 0;
		double robot_omega = 0;
		const double pi=3.14159265358979323846264338;

public:
	MPU6500 *gyro;
	Encoder *enX,*enY;
	virtual float GetX();
	virtual float GetY();
	virtual float GetYaw();
	void SetDiamater(float d);
	void SetPulse(unsigned short p);
	void SetShiftX(float x);
	void SetShiftY(float y);
	Localization(MPU6500 *g,Encoder *encoX,Encoder *encoY):gyro(g),enX(encoX),enY(encoY)
	{

	}

	virtual void countintegral();

};

class Localization_2wd:public Localization
{
	long kitaihensa=0;
	float Toled=0.293;//width wheel to wheel
	float diameter=0.10200;
	               //angular velocity of the robot

	float delta=0.005;
public:
	using Localization::Localization;
	virtual float GetX();
	virtual float GetY();
	virtual float GetYaw();
	virtual void countintegral();

};




#endif /* LOCALIZATION_LOCALIZATION_HPP_ */
