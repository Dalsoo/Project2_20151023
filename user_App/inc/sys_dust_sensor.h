/*******************************************************************************
* File Name          : sys_dust_sensor.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project2(Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.5.07
* Description        : dust data(gp2y1010au)
*******************************************************************************/

#ifndef  __SYS_DUST_SENSOR_H__
#define __SYS_DUST_SENSOR_H__

typedef struct
{
	u32 dust_timer;
	bool dust_stat_flag;
	float dust_sensor_data;
	
	
}sys_DustSensor_structure;

typedef struct
{
		u8 execellent;
	  u8 fair;
	  u8 mediocre;
	   u8 bad;
}sys_Dust_value_structure;


extern sys_Dust_value_structure 	sys_Dust_value_str;
extern sys_DustSensor_structure sys_DustSensor_str;

#define DUST_VOLTAGE     5.0

#define DUST_CHECK_TIME  60  // 60min

#define DUST_STANDARD_BAD    101    //151   //101
#define DUST_STANDARD_MEDIOCRE    100        //150  //100
#define DUST_STANDARD_FAIR    50      //80  //50
#define DUST_STANDARD_EXCELLENT    15      //30    //15

#define SAMPLE_ADC			10



float sys_GetDustSensorCalcu(u16 adc_raw);
float sys_GetDustSensorValue(void);

void Dust_Sensor_Process(void);
#endif



