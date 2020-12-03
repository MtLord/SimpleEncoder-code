/*
 * DefineOrder.h
 *
 *  Created on: 2019/05/04
 *      Author: —T‘¿
 */

#ifndef DEFINEORDER_H_
#define DEFINEORDER_H_

#define ORDER_BIT_Pos 8U//extid sift bit
#define ORDER_BIT_Pos_S 4U//stdid sift bit
#define NODE_ID_Pos 4U

#define CON_ADDRESEE 0x74<<1
enum{
	MOTORE_SET_DUTY=0x2,
	SERVO_SET_DUTY=0x42,
	SERVO_SET_FREAQENCY=0x40,
	AIR_OPEN=0x21,
	AIR_CLOSE=0x22,
	Get_SENSOR=0x31,
	GET_MICROSWITCH=0x32,
	SETPPER_SET_PULSE=0x51,
	GET_LOCA=0x11,
	SET_INIT_POSE=0x10,
	SET_ENCO_POSE=0x12,
	SET_ENCO_PULSE=0x13,
	GRT_ENCODER_COUNT=0x14,
	SET_ENC_DIAMTER=0x15,
	SET_ENC_DIRECTION=0x16,
	GET_SWITCH=0xA1

};




#endif /* DEFINEORDER_H_ */
