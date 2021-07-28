/*
 * RotaryEncoder.cpp
 *
 *  Created on: 2018/12/22
 *      Author: �T��
 */

#include "RotaryEncoder.hpp"

long Encoder::getcount()
{
	return (htim->Instance->CNT-this->offset)*direction;
}

short IntEncoder::getcount()
{
	return (htim->Instance->CNT-this->offset)*direction;
}

short IntEncoder::GetCoutDiff()
{
	b_count=n_count;
	n_count=getcount();
	return n_count-b_count;
}
