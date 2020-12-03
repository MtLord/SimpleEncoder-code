/*
 * DefineReadSwitch.h
 *
 *  Created on: 2019/08/18
 *      Author: �T��
 */

#ifndef ENCODERSWITCH_DEFINEREADSWITCH_H_
#define ENCODERSWITCH_DEFINEREADSWITCH_H_
#include "stm32f4xx_hal.h"

#define Read_SW1 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4)
#define Read_SW2 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)
#define Read_SW3 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)
#define Read_SW4 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)
#define Read_SW5 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)
#define Read_SW6 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)
#define Read_SW7 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)
#define Read_SW8 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)





#endif /* ENCODERSWITCH_DEFINEREADSWITCH_H_ */
