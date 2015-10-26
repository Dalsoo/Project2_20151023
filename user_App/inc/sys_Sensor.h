/*******************************************************************************
* File Name          : sys_Sensor.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.17
* Description        : Sensor 
*******************************************************************************/

#ifndef  __SYS_SENSOR_H__
#define __SYS_SENSOR_H__

#include "sys_main.h"


#define BUZZER_PERIOD   200

typedef struct
{
	u8 Oximeter[3];
	u8 HearRate[3];
	u8 BodyTemp[2];
	u32 Temperature;       //3byte
	u16 Humidity;        //2byte
	u32 Pressure;     //3byte
	u16 ForceSensor; //2
	u16 GasSensor;
	u16 BatteryInfo;
		
}sys_Sensor_Structure;


bool sys_Buzzer_on(u16 freq);

//void Heart_Rate_Sensor(u8 cmd);
//u16 sys_GetFoceSensor(void);
u16 sys_Body_Temp_Sensor_Check(void);

#endif
