/*
 * RotaryEncoder.hpp
 *
 *  Created on: 2018/12/22
 *      Author: �T��
 */

#ifndef ENCODER_ROTARYENCODER_HPP_
#define ENCODER_ROTARYENCODER_HPP_
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "EncoderSwitch/Switch.hpp"
class Encoder
{
protected:
	const long offset=0x80000000;
	TIM_HandleTypeDef *htim;
	short direction;
public:
	Encoder(TIM_HandleTypeDef *tim,short _direction):htim(tim),direction(_direction)
	{
		htim->Instance->CNT=offset;
		HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
	}

	 long getcount();
};

class IntEncoder
{
	const short offset=0x8000;
	TIM_HandleTypeDef *htim;
	short direction;
public:
	IntEncoder(TIM_HandleTypeDef *_tim,short _direction):htim(_tim),direction(_direction)
	{
		htim->Instance->CNT=offset;
		HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
	}

	short getcount();
};


#endif /* ENCODER_ROTARYENCODER_HPP_ */
