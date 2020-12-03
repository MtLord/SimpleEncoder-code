
#ifndef __TIMERINTERRUPTCALLBACK__
#define __TIMERINTERRUPTCALLBACK__
#include "stm32f4xx_hal.h"
#include "tim.h"
//if you use different interrupt cycle,you set interrupt cycle  each other

class Timer1
{
private:
	 float period;
	 unsigned short counterperiod;
	 unsigned short Prescaler;
	 float ajustperiod;

	TIM_HandleTypeDef *htim;
public:
	Timer1(TIM_HandleTypeDef *timhandle):htim(timhandle),period(0),counterperiod(0),Prescaler(0),ajustperiod(0)
	{

	}
	void SetLoopTime(float p)
	{
		period=p/1000;
	 				/**************initialization******************/
	 	while(ajustperiod!=period)
	 	{
	 							Prescaler++;
	 		for(counterperiod=0;counterperiod<65535;counterperiod++)
	 		{
	 			ajustperiod=((float)Prescaler*((float)counterperiod+1))/HAL_RCC_GetPCLK1Freq();
	 			if(ajustperiod==period)
	 			{
	 				break;
	 			}
	 		}
	 	}
	 	htim->Init.Prescaler=(unsigned short)Prescaler-1;
	 	htim->Init.Period=(unsigned short)counterperiod;

				/***********************************************/

	}
	void Start()
	{
		HAL_TIM_Base_Init(htim);
		HAL_TIM_Base_Start_IT(htim);
	}

};


class Timer2
{
private:
		float period=0;//���荞�ݎ���
		unsigned short counterperiod;
		unsigned short Prescaler;
		float ajustperiod;
public:
	Timer2(TIM_HandleTypeDef *timhandle,float p):period(p)
		{
			/**************initialization******************/
			while(ajustperiod!=period)
			{
				Prescaler++;
			for(counterperiod=0;counterperiod<65535;counterperiod++)
			{
				ajustperiod=((float)Prescaler*(float)(counterperiod+1))/HAL_RCC_GetPCLK1Freq();
				if(ajustperiod==period)
				{
					break;
				}
			}
			}
			timhandle->Init.Prescaler=Prescaler-1;
			timhandle->Init.Period=counterperiod;
			HAL_TIM_Base_Start_IT(timhandle);
			/***********************************************/
		}

};







#endif
