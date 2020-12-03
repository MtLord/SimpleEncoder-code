/*
 * Switch.cpp
 *
 *  Created on: 2019/07/11
 *      Author: —T‘¿
 */
#include "stm32f4xx_hal.h"
#include "Switch.hpp"
#include <string>
#include "stdio.h"
#include "DefineReadSwitch.h"

void DebugPullup()
{
	std::string pull1("pullup"),pull2("pullup"),pull3("pullup"),pull4("pullup");

	 if(Read_SW1==0)
	    {
		 	 pull1="no pull";
	    }
	 if(Read_SW2==0)
	 {
		 pull2="no pull";
	 }
	 if(Read_SW3==0)
	{
		 pull3="no pull";
	}
	 if(Read_SW1==0)
	{
		 pull4="no pull";
	}
	 printf("%s %s %s %s\n\r",pull1.c_str(),pull2.c_str(),pull3.c_str(),pull4.c_str());

}

