/*******************************************************************************
* File Name          : sys_delay.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.11
* Description        : delay
*******************************************************************************/


#ifndef  __SYS_I2C_DRIVER_H__
#define __SYS_I2C_DRIVER_H__

#include "sys_main.h"





void delay_time(u32 i)
{
     while(--i);
}


#endif



