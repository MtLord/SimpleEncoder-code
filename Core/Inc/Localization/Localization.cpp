/*
 * Localization.cpp
 *
 *  Created on: 2018/12/28
 *      Author: �T��
 */


#include "Localization.hpp"
#include "LowlayerHandel.hpp"
#include "DefineOrder.h"
#include "DefineLED.h"
#include <math.h>
extern CAN_RxHeaderTypeDef RXmsg;
extern unsigned char RxFIFO_Data[8];




void Localization::countintegral()
{
	 long hensa[2]={0,0};
	 count[0]=enX->getcount();
	 count[1]=enY->getcount();
	 hensa[Xencoder]=count[0]-b_count[0];
	 hensa[Yencoder]=count[1]-b_count[1];

	 point[Xencoder]+=(hensa[Xencoder]*cos(gyro->GetYaw())-hensa[Yencoder]*sin(gyro->GetYaw()));
	 point[Yencoder]+=(hensa[Yencoder]*cos(gyro->GetYaw()))+hensa[Xencoder]*sin(gyro->GetYaw());
	 b_count[0]=count[0];
	 b_count[1]=count[1];
	 XX=((float)point[Xencoder]*pi*diameter)/((float)pulse*4)+ShiftX*cos(gyro->GetYaw()) - ShiftY*sin(gyro->GetYaw())-ShiftX+initX;
	 YY=((float)point[Yencoder]*pi*diameter)/((float)pulse*4)+ShiftY*cos(gyro->GetYaw()) + ShiftX*sin(gyro->GetYaw())-ShiftY+initY;
	 theta=gyro->GetYaw();

}

void Localization::CalcVel()
{
	long hensa[2]={0,0};
	count[0]=enX->getcount();
	count[1]=enY->getcount();
	hensa[Xencoder]=count[0]-b_count[0];
	hensa[Yencoder]=count[1]-b_count[1];
	XX=(((float)hensa[Xencoder]/(pulse*4))*pi*diameter)/delta;//get x velocity
	YY=(((float)hensa[Yencoder]/(pulse*4))*pi*diameter)/delta;
	theta=gyro->GetYawVel();//get yaw velocity
}


float Localization::GetX()
{
	return XX;
}

float Localization::GetY()
{
	return YY;
}

float Localization::GetYaw()
{
	return theta;
}

void Localization::SetShiftX(float x)
{
	ShiftX=x;
}

void Localization::SetShiftY(float y)
{
	ShiftY=y;
}

void Localization::SetDiamater(float d)
{
	diameter=d;
}

void Localization::SetPulse(unsigned short p)
{
	pulse=p;
}


void Localization_2wd::countintegral()
{
	 long hensa[2]={0,0};
	 count[0]=-enX->getcount();
	 count[1]=enY->getcount();
	 hensa[0]=count[0]-b_count[0];//�E�ւ̕΍�
	 hensa[1]=count[1]-b_count[1];//���ւ̕΍�
	 ENCR_velocity = (hensa[0]* this->diameter*pi * 200) /(pulse*4);  //encoder(24X12V) count 400 per 1 rotation
	 ENCL_velocity = (hensa[1]* this->diameter *pi* 200) /(pulse*4);
	 robot_omega = (ENCR_velocity - ENCL_velocity)/Toled;
	 theta += robot_omega * delta;
	 robot_velocity = (ENCR_velocity + ENCL_velocity)/2;
	 XX += robot_velocity * sin(theta)*delta;
	 YY += robot_velocity * cos(theta)*delta;
	 b_count[0]=count[0];
	 b_count[1]=count[1];
}

float Localization_2wd::GetX()
{
	return XX;
}

float Localization_2wd::GetY()
{
	return YY;
}
float Localization_2wd::GetYaw()
{
	return theta;
}


