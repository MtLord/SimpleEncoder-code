/*
 * Application.hpp
 *
 *  Created on: 2019/08/12
 *      Author: �T��
 */

#ifndef APPLICATION_APPLICATION_HPP_
#define APPLICATION_APPLICATION_HPP_
#include "LowlayerHandel.hpp"
class Application
{
	LowlayerHandleTypdef *plow;
	int gyro_state=0;
	int ledstack=0;
	unsigned char tx_buff[8]={0,};
	short count_buff[4]={0,};
	unsigned char msg[8]={0,};
	unsigned char msg2[8]={0,};
	void SetCountBuff();
	void SendCount();
	void SendLoca();

	void SetEncPose();
	void SetEncPulse();
	void SetEncDiamater();
	int tx_led=0;
	bool TXok=false;

	bool sendloca=false;
	bool sendcout=false;
	bool change_encpos=false;
	bool change_encpulse=false;
	bool change_encdia=false;

	float diameter=0;
		short pulse=0;
		float ShiftY=0;
		float ShiftX=0;
		void UnitData(int start,int end,float *d,unsigned char *fifodata);
		void UnitData(int start,int end, short *d,unsigned char *fifodata);
		void Convfloat(int selct,float data);
public:
	Application(LowlayerHandleTypdef *_plow):plow(_plow){

	}



	void TaskShift();
	void SetRequred();
};



#endif /* APPLICATION_APPLICATION_HPP_ */
