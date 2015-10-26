/*******************************************************************************
* File Name          : sys_iAQ_sensor.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project2 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               :2015.5.07
* Description        : co2 ,Voc data(iAQ-core)
*******************************************************************************/

#ifndef  __SYS_IAQ_SENSOR_H__
#define __SYS_IAQ_SENSOR_H__


#define IAQ_WR_ADD   0xB4
#define IAQ_RD_ADD    0xB5

#define IAQ_CO2_VALUE  0x00
#define IAQ_STATUS	0x02
#define IAQ_RESISTANCE	0x03
#define IAQ_TVOC_VALUE	0x07

extern u32 iAQ_Ready_timer;

u8 sys_GetiAQSensor_Data(u16 *co2data,u16 *TvocData);
#endif

