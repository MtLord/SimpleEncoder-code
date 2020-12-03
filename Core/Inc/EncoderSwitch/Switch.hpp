/*
 * Switch.hpp
 *
 *  Created on: 2019/07/11
 *      Author: �T��
 */

#ifndef ENCODERSWITCH_SWITCH_HPP_
#define ENCODERSWITCH_SWITCH_HPP_
#include "DefineReadSwitch.h"

struct SwitchMode
{
	int enc1_dir,enc2_dir,enc3_dir,enc4_dir;
	int encX_dir,encY_dir;
	SwitchMode()
	{
		if(Read_SW1==1)
		{
			enc1_dir=-1;
		}
		else
		{
			enc1_dir=1;
		}
		if(Read_SW2==1)
		{
			enc2_dir=-1;
		}
		else
		{
			enc2_dir=1;
		}
		if(Read_SW3==1)
		{
			enc3_dir=-1;
		}
		else
		{
			enc3_dir=1;
		}
		if(Read_SW4==1)
		{
			enc4_dir=-1;
		}
		else
		{
			enc4_dir=1;
		}
		if(Read_SW5==1)
		{
			encX_dir=-1;
		}
		else
		{
			encX_dir=1;
		}
		if(Read_SW6==1)
		{
				encY_dir=-1;
		}
		else
		{
			encY_dir=1;
		}
	}
};


#endif /* ENCODERSWITCH_SWITCH_HPP_ */
