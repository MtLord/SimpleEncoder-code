/*
 * Application.cpp
 *
 *  Created on: 2019/08/12
 *      Author: �T��
 */
#include "Application.hpp"
#include "stm32f4xx_hal.h"
#include "DefineOrder.h"
#include "DefineLED.h"
#include "i2c.h"
extern unsigned char RxFIFO_Data[8];
extern CAN_RxHeaderTypeDef RXmsg;

void Application::SendCount()
{
	SetCountBuff();
	while(TXok==false)
	{
		if(plow->extcan_d.Send(GRT_ENCODER_COUNT<<ORDER_BIT_Pos|1, 8, tx_buff)!=0)
		{
			 ERROR_LED;
		}
		else
		{
			if(tx_led>10)
			{
				TOGGLE_TX_LED;
				tx_led=0;
			}
			else
			{
				tx_led++;
			}
			TXok=true;
		}
	}
		TXok=false;


}

void Application::SendLoca()
{
	Convfloat(0,plow->loca->GetX());
	Convfloat(1,plow->loca->GetY());
	Convfloat(2,plow->loca->GetYaw());
	while(TXok==false)
	{
		if(plow->extcan_d.Send(GET_LOCA<<ORDER_BIT_Pos|0x1<<NODE_ID_Pos,8,this->msg)!=0)
		{
			TXok=false;
		}
		else
		{
			TXok=true;
		}
	}
	TXok=false;

	while(TXok==false)
	{
		if(plow->extcan_d.Send(GET_LOCA<<ORDER_BIT_Pos|0x2<<NODE_ID_Pos,4,this->msg2)!=0)
		{
			ERROR_LED;
		}
		else
		{
			if(tx_led>10)
			{
				TOGGLE_TX_LED;
				tx_led=0;
			}
			else
			{
				tx_led++;
			}
			TXok=true;
		}
	}
	TXok=false;

}

void Application::SetEncPose()
{
	UnitData(0,3,&ShiftX,RxFIFO_Data);
	UnitData(4, 7, &ShiftY, RxFIFO_Data);
	plow->loca->SetShiftX(ShiftX);
	plow->loca->SetShiftY(ShiftY);
	plow->extcan_r.Send(SET_ENCO_POSE<<ORDER_BIT_Pos|0x1<<NODE_ID_Pos,0,0);//return set ok
}

void Application::SetEncPulse()
{
	UnitData(0,1,&pulse,RxFIFO_Data);
	plow->loca->SetPulse(pulse);
}
void Application::SetEncDiamater()
{
	UnitData(0, 3, &diameter, RxFIFO_Data);
	plow->loca->SetDiamater(diameter);
}

void Application::SetCountBuff()//set encoder count
{
		count_buff[0]=plow->int_enco1.getcount();
		count_buff[1]=plow->int_enco2.getcount();
		count_buff[2]=plow->int_enco3.getcount();
		count_buff[3]=plow->int_enco4.getcount();
		tx_buff[0]=((unsigned char*)&count_buff[0])[0];
		tx_buff[1]=((unsigned char*)&count_buff[0])[1];
		tx_buff[2]=((unsigned char*)&count_buff[1])[0];
		tx_buff[3]=((unsigned char*)&count_buff[1])[1];
		tx_buff[4]=((unsigned char*)&count_buff[2])[0];
		tx_buff[5]=((unsigned char*)&count_buff[2])[1];
		tx_buff[6]=((unsigned char*)&count_buff[3])[0];
		tx_buff[7]=((unsigned char*)&count_buff[3])[1];
}
void Application::TaskShift()
{
	if(sendloca)
	{
		SendLoca();
		sendloca=false;
	}
	if(sendcout)
	{
		SendCount();
		sendcout=false;
	}
	if(change_encpos)
	{
		SetEncPose();
		change_encpos=false;
	}
	if(change_encpulse)
	{
		SetEncPulse();
		change_encpulse=false;
	}
	if(change_encdia)
	{
		SetEncDiamater();
		change_encdia=false;
	}

}

void Application::Convfloat(int select,float data)
{
	switch(select)
	{
	case 0:
		msg[0]=((unsigned char*)&data)[0];
		msg[1]=((unsigned char*)&data)[1];
		msg[2]=((unsigned char*)&data)[2];
		msg[3]=((unsigned char*)&data)[3];
		break;
	case 1:
		msg[4]=((unsigned char*)&data)[0];
		msg[5]=((unsigned char*)&data)[1];
		msg[6]=((unsigned char*)&data)[2];
		msg[7]=((unsigned char*)&data)[3];
		break;
	case 2:
		msg2[0]=((unsigned char*)&data)[0];
		msg2[1]=((unsigned char*)&data)[1];
		msg2[2]=((unsigned char*)&data)[2];
		msg2[3]=((unsigned char*)&data)[3];
		break;
	}
}
void Application::UnitData(int start,int end,float *d,unsigned char *fifodata)
{
	for(int i=start;i>end;i++)
	{
		((unsigned char *)d)[i]=fifodata[i];
	}
}

void Application::UnitData(int start,int end, short *d,unsigned char *fifodata)
{
	for(int i=start;i>end;i++)
	{
		((unsigned char *)d)[i]=fifodata[i];
	}
}
void Application::SetRequred()
{
	long task=(RXmsg.ExtId);
	switch(task)
	{
		case GET_LOCA<<ORDER_BIT_Pos:
				this->sendloca=true;
			break;
		case SET_ENCO_POSE<<ORDER_BIT_Pos:
				this->change_encpos=true;
			break;
		case SET_ENCO_PULSE<<ORDER_BIT_Pos:
				this->change_encpulse=true;
			break;
		case SET_ENC_DIAMTER<<ORDER_BIT_Pos:
				this->change_encdia=true;
			break;
		case GRT_ENCODER_COUNT<<ORDER_BIT_Pos|1:
				this->sendcout=true;
				break;
	}
}
