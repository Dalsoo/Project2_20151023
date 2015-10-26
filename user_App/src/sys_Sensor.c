/*******************************************************************************
* File Name          : sys_Sensor.c
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.17
* Description        : Sensor 
*******************************************************************************/

#include "sys_main.h"

sys_Sensor_Structure sys_Sensor;



bool sys_Buzzer_on(u16 freq)
{
//	float time=0;
//	time = (float)(1000/(freq));
	
//	time=time *1000;
	
//	sys_printf("buzzeri timer [%d][%d]\n",time,freq);
	bool return_flag=false;
	if((sys_i2c_busy_flag==0) &&(sys_i2c2_busy_flag==0)) 
	{
		for(u16 i =0; i<100; i++)
		{
			nrf_gpio_pin_set(BUZZER_PWM_OUT);
			nrf_delay_us(BUZZER_PERIOD);
			nrf_gpio_pin_clear(BUZZER_PWM_OUT);
			nrf_delay_us(BUZZER_PERIOD);
		}
		return_flag=true;
	}
	
	return return_flag;
}
