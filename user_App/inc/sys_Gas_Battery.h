/*******************************************************************************
* File Name          : sys_Gas_Battery.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.4.08
* Description        :  gas gage, Battery status(STC3115)
*******************************************************************************/



#ifndef  __SYS_BATTERY_H__
#define __SYS_BATTERY_H__

#include "sys_main.h"


/**************  Control registers ***************/
#define GAS_WR_ADD			0xE0
#define GAS_RD_ADD			0xE1

#define GAS_REG_MODE			0x00
#define GAS_REG_CTRL			0x01
#define GAS_REG_SOC_LH		0x02
#define GAS_REG_COUNTER_LH	0x04
#define GAS_REG_CURRENT_LH	6
#define GAS_REG_VOLTAGE_LH	8
#define GAS_REG_TEMPERATURE	10
#define GAS_REG_CC_ADJ_HIGH	11
#define GAS_REG_VM_ADJ_HIGH	12
#define GAS_REG_OCV_LH		13
#define GAS_REG_CC_CNF_LH	15
#define GAS_REG_VM_CNF_LH	17
#define GAS_REG_ALARM_SOC	19
#define GAS_REG_ALARM_VOLTAGE	20
#define GAS_REG_CURRENT_THERS	21
#define GAS_REG_RELAX_COUNT		22
#define GAS_REG_RELAX_MAX		23
#define GAS_REG_ID				24
#define GAS_REG_CC_ADJ_LOW		25
#define GAS_REG_VM_ADJ_LOW		26
#define GAS_ACC_CC_ADJ_LH			27
#define GAS_ACC_VM_ADJ_LH			29


#define GAS_ID		0x14


#define GAS_MODE_SET    0x19
#define GAS_CONFIG_SET  0x44

#define BATTERY_FULL_VALUE  		1682    //3.7V
#define BATTERY_HIGH_VALUE  		1682    //3.7V
#define BATTERY_MID_VALUE  		1591    //3..5V
#define BATTERY_LOW_VALUE  		1500   //3.3V
#define BATTERY_EXTREAME_VALUE  	1409    //3.1V
#define BATTERY_OFF_VALUE 		1363    //3V

#define SYS_CHG_BAT_EXTRIME       1800//  3.96V   
#define SYS_CHG_BAT_CHARGE_LOW    1810//
#define SYS_CHG_BAT_LOW           1810   //
#define SYS_CHG_BAT_MID           1844//
#define SYS_CHG_BAT_HIGH          1895
#define SYS_CHG_BAT_FULL  1900  


#define SYS_MAX_VOLTAGE           2100   // 4.2V 최대 전압


#define SYS_HALF_TIME            900
#define SYS_1HOUR_TIME            1800

//
#define SYS_BAT_75MA            2048              //설정저항값 : 10KR , 측정치 : 2051 , 계산치 : 2048
#define SYS_BAT_2600MA            2730              //설정저항값 : 20KR , 측정치 : 2726 , 계산치 : 2580-2730-2880
//#define SYS_BAT_1600MA            372               //설정저항값 : 1KR , 측정치 : 371 , 계산치 : 372
//#define SYS_BAT_3200MA            682               //설정저항값 : 2KR , 측정치 : 680 , 계산치 : 682

#define SYS_FULL_BATT_ST          0x01
#define SYS_HIGH_BATT_ST          0x02
#define SYS_MID_BATT_ST           0x04
#define SYS_LOW_BATT_ST           0x08
#define SYS_LOW_CHG_BATT_ST       0x10

#define SYS_MCP73837_SHUTDOWN     0x07
#define SYS_MCP73837_STANDBY    0x06
#define SYS_MCP73837_CHARGING     0x02
#define SYS_MCP73837_COMPLETE     0x04


#define SYS_BATTERY_NORMAL				0x00
#define SYS_BATTERY_CHARGING				0x01
#define SYS_BATTERY_CHARGE_COMPLETE		0x02


typedef enum 
{
	BATT_DIS_IDLE,
	BATT_DIS_EXTREAM,
	BATT_DIS_LEVEL1,
	BATT_DIS_LEVEL2,
	BATT_DIS_LEVEL3,
	BATT_DIS_LEVEL4,
	BATT_DIS_FULL	
	
}BATT_DIS_STAT;






u8 sys_GetSTC3115_ID(void);

bool sys_GetBatteryInfo(u16 *batt_current, u16 *batt_voltage);

void sys_STC3115_Init(void);

void sys_Battey_Indicate(bool ext_power,u16 batt_vol_data);
void sys_Battey_manager(bool ext_power,u16 batt_vol_data);


#endif

