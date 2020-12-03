/*
 * Robot.hpp
 *
 *  Created on: 2018/06/25
 *      Author: �T��
 */

#ifndef ROBOT_HPP_
#define ROBOT_HPP_
/*******include heders*******************/
#include "tim.h"
#include "stm32f4xx.h"
#include <encoder/RotaryEncoder.hpp>
#include "CAN/CAN.hpp"
#include "Localization/Localization.hpp"
#include "MPU6500/mpu6500.h"
#include "i2c.h"
#include "stdio.h"

/****************************************/
struct LowlayerHandleTypdef{
private:


public:
		IntEncoder int_enco1;
		IntEncoder int_enco2;
		IntEncoder int_enco3;
		IntEncoder int_enco4;
		Encoder enX;//(timhandle,direction);
		Encoder enY;
		CanBus extcan_d, extcan_r,stdcan_d;


		MPU6500 gyro;
		Localization loca;

	LowlayerHandleTypdef():int_enco1(&htim3),int_enco2(&htim8),int_enco3(&htim1),int_enco4(&htim4),
			enX(&htim2),enY(&htim5),gyro(&hi2c2),extcan_d(CAN_ID_EXT,CAN_RTR_DATA),extcan_r(CAN_ID_EXT,CAN_RTR_REMOTE),stdcan_d(CAN_ID_STD,CAN_RTR_DATA),
			loca(&gyro,&enX,&enY)
	{

	}
	void PutDebugLocalization()
	{
		  printf("x:%f y:%f yaw:%f count1:%d count2:%d count3:%d count4:%d\n\r",loca.GetX(),loca.GetY(),loca.GetYaw(),int_enco1.getcount(),
				  int_enco2.getcount(), int_enco3.getcount(), int_enco4.getcount() );
	}
	void LEDChek()
	{
		  HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8);
		  HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9);
		  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_8);
		  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_10);
		  HAL_Delay(500);
	}
};
extern void FilterConfig();
extern LowlayerHandleTypdef *plow;
extern bool IntFlag;



#endif /* ROBOT_HPP_ */
