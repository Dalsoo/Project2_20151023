/*******************************************************************************
* File Name          : sys_iAQ_sensor.c
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project2(Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.5.07
* Description        : co2 ,Voc data(iAQ-core)
*******************************************************************************/

#include "sys_main.h"

u32 iAQ_Ready_timer=0;
//2015.10.06: dalsoo fix immature return_value problem:
u16 saved_co2data = 0;
u16 saved_TvocData = 0;

u8 sys_GetiAQSensor_Data(u16 *co2data,u16 *TvocData)
{
	u8 buffer[9];
	u32 iAQregister=0;
	u8 return_value=0;

	
	 u8 cnt=0;
        NRF_WDT->RR[0] = WDT_RR_RR_Reload;  //Reload watchdog register 0

	if(iAQ_Ready_timer>= 150)   // 150 = 5min
	{
		iAQ_Ready_timer = 151;
loop:	

		twi_master_transfer(IAQ_RD_ADD,buffer,9,TWI_ISSUE_STOP);

		cnt++;
		if(cnt > 10)  {
	
			*co2data = saved_co2data;   //dalsoo
		  *TvocData = saved_TvocData;  //dalsoo
				
			return return_value;
		}
		
		if(buffer[2] == 0x00)
		{
			*co2data = ((buffer[0] << 8) & 0xff00  )| (buffer[1] & 0xff);
			*TvocData =  ((buffer[7] << 8) & 0xff00  )| (buffer[8] & 0xff);

			saved_co2data = *co2data;   //dalsoo
			saved_TvocData = *TvocData ;  //dalsoo
			
			iAQregister = ((buffer[4] << 16) & 0xff0000  )| ((buffer[5] << 8) & 0xff00  )| (buffer[6] & 0xff);

			return_value=0;
			  if((*co2data >2000 ) || (*TvocData >600))
			  {
				  goto loop;
			  }
		}else if(buffer[2] == 0x01)
		{

			return_value=0x01;



		goto loop;

		}else if(buffer[2] == 0x80)
		{
			return_value=0x80;
		goto loop;
		}else  if(buffer[2] == 0x10)
		{
	
			return_value=0x10;
			
			
			*co2data = saved_co2data;   //dalsoo
		  *TvocData = saved_TvocData;  //dalsoo
		
			return return_value;
			

		}
		NRF_WDT->RR[0] = WDT_RR_RR_Reload;  //Reload watchdog register 0
		
				
			*co2data = saved_co2data;   //dalsoo
		  *TvocData = saved_TvocData;  //dalsoo
		
		return return_value;
	}else
	{
		
			*co2data = saved_co2data;   //dalsoo
		  *TvocData = saved_TvocData;  //dalsoo
		
		return_value=3;
		return return_value;
		
	}
	
}
