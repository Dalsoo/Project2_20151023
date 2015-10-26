
/*******************************************************************************
* File Name          : sys_TempHumiPress_process.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.4.06
* Description        :  Temperature, Hudimity , Pressure Sensor (BME280)
*******************************************************************************/


#ifndef  __SYS_TEMP_HUMI_PRESS_H__
#define __SYS_TEMP_HUMI_PRESS_H__

#include "sys_main.h"

#define THP_WR_ADD		0xEC
#define  THP_RD_ADD		0xED

#define THP_ID_READ		0xD0
#define THP_RESET			0xE0
#define  THP_TRL_HUM		0xF2
#define  THP_STATUS		0xF3
#define  THP_CTRL_MEAS	0xF4
#define  THP_CONFIG		0xF5
#define  THP_PRESS_MSB	0xF7
#define  THP_PRESS_LSB	0xF8
#define  THP_PRESS_XLSB	0xF9
#define  THP_TEMP_MSB	0xFA
#define  THP_TEMP_LSB		0xFB
#define  THP_TEMP_XLSB	0xFC
#define  THP_HUM_MSB		0xFD
#define  THP_HUM_LSB		0xFE


u8 sys_BME280_init(void);
u32 sys_GetBME280_Press(void);
u32 sys_GetBME280_Temp(void);
u16 sys_GetBME280_Humi(void);



#endif



