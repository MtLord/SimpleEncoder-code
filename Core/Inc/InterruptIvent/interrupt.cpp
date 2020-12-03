/*
 * interrupt.c
 *
 *  Created on: 2018/09/23
 *      Author: 鬮ｯ�ｽｬ陟�髮｣�ｽｽ�ｽｱ�ｿｽ�ｽｽ�ｽｰ
 */



#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "LowlayerHandel.hpp"
bool IntFlag=false;

 void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM6)
	{
 		IntFlag=true;
 		plow->gyro.SetYaw();
 		plow->loca.countintegral();
 	}

}

