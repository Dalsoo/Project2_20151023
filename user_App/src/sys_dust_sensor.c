/*******************************************************************************
* File Name          : sys_dust_sensor.c
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project2(Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.5.07
* Description        : dust data(gp2y1010au)
*******************************************************************************/


/*
  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);
  
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.172 * calcVoltage - 0.0999;
*/
/*
3000 +     = VERY POOR
1050-3000  = POOR
300-1050   = FAIR
150-300    = GOOD
75-150     = VERY GOOD
0-75       = EXCELLENT

*/
#include "sys_main.h"

sys_Dust_value_structure 	sys_Dust_value_str;


u16 sys_GetADC_Value(void)
{
	u16 adc_data=0;
		NRF_ADC->TASKS_START = 1;
	
	while(NRF_ADC->BUSY);
	
	adc_data = NRF_ADC->RESULT;

	
	NRF_ADC->TASKS_STOP =1;
	
	return adc_data;
	
}
void sys_dust_led_mode_change(u8 mode)
{
			if(mode)     // output
			{
					nrf_gpio_cfg_output(DUST_LED_OUTPUT);
			}else             //input
			{
				
					nrf_gpio_cfg_input(DUST_LED_OUTPUT,NRF_GPIO_PIN_NOPULL);
			}
	
	
}

float V0c = 0.12;   //dalsoo:  needs to be optimized  before mass production at factory

float sys_GetDustSensorValue(void)
{
//	u16 return_value=0;
	u32 adc_value=0;
	float calcVoltage=0.0;
	float dustDensity=0;
	

	for(u8 i=0;i<SAMPLE_ADC;i++)
	{
		
		DUST_LED_ON();

		
		nrf_delay_us(250);	
		adc_value += sys_GetADC_Value();   //70us
		nrf_delay_us(152);
		
		DUST_LED_OFF();

		nrf_delay_ms(9);
	}

	
	adc_value = adc_value /SAMPLE_ADC;
	

	
	  calcVoltage = adc_value * (DUST_VOLTAGE/ 1024.0);
	  
	
	  dustDensity = 0.2 * calcVoltage - V0c;
	//	20151005:dalsoo	  dustDensity = 0.17 * calcVoltage - 0.1;
	
	if(dustDensity<0) { 
//		V0c = V0c + dustDensity;  // dalsoo: Note V0c is not stable value
		dustDensity=0;
	}	
#if 	_SYS_DEBUG > 0
	sys_printf("adc_data = [%d][%f]\n",adc_value,dustDensity);
#endif	
	//for test:dalsoo		dustDensity=10/1024.0;
	return dustDensity;
}

float sys_GetDustSensorCalcu(u16 adc_raw)
{
	  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
	float calcVoltage=0.0;
	float dustDensity=0;
	
	  calcVoltage = adc_raw * (DUST_VOLTAGE/ 1024.0);
	  	
	  dustDensity = 0.17 * calcVoltage - 0.1;
	
	sys_printf("dustDensity = [%f]\n",dustDensity);
	
	return dustDensity;
}

void Dust_Sensor_Process(void)
{
//	float dust_seonsor_data=0;
	 sys_DustSensor_structure *pDustSensor = &sys_DustSensor_str;
	 sys_Dust_value_structure 	*pDustValue = &sys_Dust_value_str;
	
	if(pDustSensor->dust_timer >= (DUST_CHECK_TIME*60))    // 60min
	{
		pDustSensor->dust_timer=0;
		pDustSensor->dust_sensor_data= sys_GetDustSensorValue()*1024;
		//20151005:dalsoo				pDustSensor->dust_sensor_data= sys_GetDustSensorValue()*1000;

#if	_SYS_DEBUG > 0
		sys_printf("dust_sensor_data [%f] \n",pDustSensor->dust_sensor_data);
#endif
	}else
	{
		pDustSensor->dust_timer++;
		
	}
	
#if	_SYS_DEBUG > 2
		sys_printf("dust_timer [%d] \n",pDustSensor->dust_timer);
#endif
	


	
//	if(pDustSensor->dust_sensor_data > DUST_STANDARD_MEDIOCRE)
//	if(pDustSensor->dust_sensor_data >= pDustValue->bad)
	if(pDustSensor->dust_sensor_data > pDustValue->mediocre)
	{
		DUST_STAT_LED_BAD_ON();
		DUST_STAT_LED_MEDIOCRE_OFF();
		DUST_STAT_LED_FAIR_OFF();
		DUST_STAT_LED_EXCELLENT_OFF();
		
//	}else if( pDustSensor->dust_sensor_data > DUST_STANDARD_FAIR &&  pDustSensor->dust_sensor_data <=DUST_STANDARD_MEDIOCRE)
	}else if( pDustSensor->dust_sensor_data > pDustValue->fair &&  pDustSensor->dust_sensor_data <=pDustValue->mediocre)
		{
		DUST_STAT_LED_BAD_OFF();
		DUST_STAT_LED_MEDIOCRE_ON();
		DUST_STAT_LED_FAIR_OFF();
		DUST_STAT_LED_EXCELLENT_OFF();
		
		
//   }else if( pDustSensor->dust_sensor_data > DUST_STANDARD_EXCELLENT &&  pDustSensor->dust_sensor_data <=DUST_STANDARD_FAIR)
	}else if( pDustSensor->dust_sensor_data > pDustValue->execellent &&  pDustSensor->dust_sensor_data <=pDustValue->fair)
	{
		DUST_STAT_LED_BAD_OFF();
		DUST_STAT_LED_MEDIOCRE_OFF();
		DUST_STAT_LED_FAIR_ON();
		DUST_STAT_LED_EXCELLENT_OFF();
		
//	}else if( pDustSensor->dust_sensor_data <=DUST_STANDARD_EXCELLENT)
	}else if( pDustSensor->dust_sensor_data <= pDustValue->execellent)
	{
		DUST_STAT_LED_BAD_OFF();
		DUST_STAT_LED_MEDIOCRE_OFF();
		DUST_STAT_LED_FAIR_OFF();
		DUST_STAT_LED_EXCELLENT_ON();
		
	}
	
		// for test: dalsoo
//	  DUST_STAT_LED_BAD_ON();
//		DUST_STAT_LED_MEDIOCRE_ON();

//DUST_STAT_LED_FAIR_ON();
//		DUST_STAT_LED_EXCELLENT_ON();	
}
