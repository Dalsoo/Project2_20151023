/*******************************************************************************
* File Name          : sys_Gas_Battery.c
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.4.08
* Description        :  gas gage, Battery status(STC3115)
*******************************************************************************/



#include "sys_main.h"


static BATT_DIS_STAT batt_dis_stat = BATT_DIS_IDLE;
sys_battery_struct sys_battery_str;

u8 sys_GetSTC3115_ID(void)
{
	
	
	u8 id=0;

	u8 reg =GAS_REG_ID;
	
	twi_master_transfer(GAS_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	
	twi_master_transfer(GAS_RD_ADD,&id,1,TWI_ISSUE_STOP);
	

	return id;
	
	
}
void sys_SetSTC3115_Mode(void)
{
	u8 write_data[2];
	
	write_data[0] = GAS_REG_MODE;
	write_data[1] = GAS_MODE_SET;
	
	twi_master_transfer(GAS_WR_ADD, write_data, 2, TWI_ISSUE_STOP);
	
}

void sys_SetSTC3115_Config(void)
{
	
	
	
}
u32 batt_test=0;
extern bool extern_power_flag;
bool sys_GetBatteryInfo(u16 *batt_current, u16 *batt_voltage)
{
	u8 batt_temp=0;

	u8 buffer[5];
	
	u8 reg=GAS_REG_CURRENT_LH;
	u8 loop_cnt =0;
	
	bool return_val=false;
	
	do
	{
		twi_master_transfer(GAS_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);

		twi_master_transfer(GAS_RD_ADD,buffer,5,TWI_ISSUE_STOP);

		
			
		*batt_current = (buffer[0]& 0x00ff) | ((buffer[1]<< 8) & 0xff00);
		*batt_voltage = (buffer[2]& 0x00ff) | ((buffer[3]<< 8) & 0xff00);
		
		batt_temp = buffer[4];
		
		if( (*batt_voltage >1136 ) && (*batt_voltage < 2045 ) )   //2.5v ~ 4.5v
		{
			return_val = true;
			break;
			
		}else
		{
			
			loop_cnt++;

			if(loop_cnt > 5)
			{
				return_val = false;
				return return_val;
				
			}
		
		}
	}while(loop_cnt < 5);
	
#if _SYS_DEBUG > 0	
	float vol=0.0,curr=0.0;
	vol=*batt_voltage*0.0022;
	curr= *batt_current * 5.88;
	sys_battery_struct *pBattery = &sys_battery_str;
	sys_printf("%d %d %d %d %d %d %f %d %f \n",batt_test++,extern_power_flag,pBattery->Charge_Flag, batt_dis_stat,batt_temp,*batt_voltage,vol,*batt_current,curr);
	
#endif
	return return_val;
}

void sys_STC3115_Init(void)
{
     u8 id=0;
	u8 cnt=0;
	do
	{
		id= sys_GetSTC3115_ID();
		
		sys_printf("Gas ID = [0x%x] \n",id);
		if(id == GAS_ID)
		{
			sys_printf("STC 3115 INITIALIZE  OK \n",id);
			break;
			
		}
	}while(cnt++ <3);
	
	
	
	sys_SetSTC3115_Mode();
	sys_SetSTC3115_Config();



}

void sys_Battey_Indicate(bool ext_power,u16 batt_vol_data)
{





}
void sys_Battey_manager(bool ext_power,u16 batt_vol_data)
{
	
	
	sys_battery_struct *pBattery = &sys_battery_str;
	
	
	pBattery->char_status = nrf_gpio_pin_read(CHARGE_IC_PG_IN) | (nrf_gpio_pin_read(CHARGE_IC_STAT2_IN)<<1)
	                               |( nrf_gpio_pin_read(CHARGE_IC_STAT1_IN)<<2) ;

	switch(pBattery->char_status)
	{
		case SYS_MCP73837_SHUTDOWN:
			pBattery->Charge_Flag = false;
		pBattery->status = SYS_BATTERY_NORMAL;
		break;
		case SYS_MCP73837_STANDBY:
			pBattery->status = SYS_BATTERY_NORMAL;
			pBattery->Charge_Flag = false;
		break;
		case SYS_MCP73837_CHARGING:
			pBattery->Charge_Flag = true;
			pBattery->status = SYS_BATTERY_CHARGING;
		break;
		case SYS_MCP73837_COMPLETE:
			pBattery->Charge_Flag = false;
			pBattery->status = SYS_BATTERY_CHARGE_COMPLETE;
		break;
		default:
			pBattery->status = SYS_BATTERY_NORMAL;
			pBattery->Charge_Flag = false;
		break;

		
	}
	

	
	if(ext_power && pBattery->Charge_Flag )                     // 충전중
	{ 
		switch(batt_dis_stat)
		{
			case BATT_DIS_IDLE:
				
				if(batt_vol_data < SYS_CHG_BAT_EXTRIME)    // 3v
				{
					batt_dis_stat=BATT_DIS_EXTREAM;
          GREEN_LED_TOGGLE();
					/*					BATT_LED_LEVEL1_ON();
					BATT_LED_LEVEL2_OFF();
					BATT_LED_LEVEL3_OFF();
*/
					
					
				}else if((batt_vol_data >= SYS_CHG_BAT_EXTRIME) && (batt_vol_data < SYS_CHG_BAT_MID))
				{
					batt_dis_stat=BATT_DIS_LEVEL1;
          GREEN_LED_TOGGLE();
					/*					BATT_LED_LEVEL1_ON();
					BATT_LED_LEVEL2_OFF();
					BATT_LED_LEVEL3_OFF();
*/
					}

	      	else if((batt_vol_data >= SYS_CHG_BAT_MID) && (batt_vol_data < SYS_CHG_BAT_HIGH))
				{
					batt_dis_stat=BATT_DIS_LEVEL2;
          GREEN_LED_ON();
					/*					BATT_LED_LEVEL1_ON();
					BATT_LED_LEVEL2_ON();
					BATT_LED_LEVEL3_ON();
*/
					
//2015.10.22				}else if((batt_vol_data >= SYS_CHG_BAT_HIGH)&& (batt_vol_data < BATTERY_FULL_VALUE))
				}else if((batt_vol_data >= SYS_CHG_BAT_HIGH)&& (batt_vol_data < SYS_CHG_BAT_FULL))
				{
					batt_dis_stat=BATT_DIS_LEVEL3;
         GREEN_LED_ON();
					/*					BATT_LED_LEVEL1_ON();
					BATT_LED_LEVEL2_ON();
					BATT_LED_LEVEL3_ON();
*/					
//2015.10.22				}else if(batt_vol_data >= BATTERY_FULL_VALUE)
				}else if(batt_vol_data >= SYS_CHG_BAT_FULL)
				{
					batt_dis_stat=BATT_DIS_FULL;
          GREEN_LED_ON();
					/*					BATT_LED_LEVEL1_ON();
					BATT_LED_LEVEL2_ON();
					BATT_LED_LEVEL3_ON();
*/					
				}
			
			
			break;
			case BATT_DIS_EXTREAM:
				  GREEN_LED_TOGGLE();
/*				BATT_LED_LEVEL1_TOGGLE();
				BATT_LED_LEVEL2_OFF();
				BATT_LED_LEVEL3_OFF();
*/
			if((batt_vol_data >= SYS_CHG_BAT_EXTRIME))
				{
					batt_dis_stat = BATT_DIS_LEVEL1;
				}
			      
			break;
			case BATT_DIS_LEVEL1:
          GREEN_LED_TOGGLE();
			/*				BATT_LED_LEVEL1_TOGGLE();
				BATT_LED_LEVEL2_OFF();
				BATT_LED_LEVEL3_OFF();
*/
				if((batt_vol_data >= SYS_CHG_BAT_MID) )
				{
					batt_dis_stat = BATT_DIS_LEVEL2;
				}
			break;
			case BATT_DIS_LEVEL2:
				  GREEN_LED_TOGGLE();
/*				BATT_LED_LEVEL1_ON();
				BATT_LED_LEVEL2_TOGGLE();
				BATT_LED_LEVEL3_OFF();
*/
				if((batt_vol_data >= SYS_CHG_BAT_HIGH))
				{
					batt_dis_stat = BATT_DIS_LEVEL3;
				}
			break;
			case BATT_DIS_LEVEL3:
				 GREEN_LED_TOGGLE();
/*				BATT_LED_LEVEL1_ON();
				BATT_LED_LEVEL2_ON();
				BATT_LED_LEVEL3_TOGGLE();
*/
					if(batt_vol_data >= SYS_CHG_BAT_FULL)
				{
					batt_dis_stat = BATT_DIS_LEVEL4;
				}
			break;
			case BATT_DIS_LEVEL4:
         GREEN_LED_ON();
			/*				BATT_LED_LEVEL1_ON();
				BATT_LED_LEVEL2_ON();
				BATT_LED_LEVEL3_ON();
*/
				if((batt_vol_data >= SYS_CHG_BAT_FULL) && (pBattery->status == SYS_BATTERY_CHARGE_COMPLETE))
				{
					batt_dis_stat = BATT_DIS_FULL;
				}
			break;
			case BATT_DIS_FULL:
         GREEN_LED_ON();
			/*				BATT_LED_LEVEL1_ON();
				BATT_LED_LEVEL2_ON();
				BATT_LED_LEVEL3_ON();
*/
				
			break;
			default:
/*					BATT_LED_LEVEL1_OFF();
					BATT_LED_LEVEL2_OFF();
					BATT_LED_LEVEL3_OFF();
*/
			break;
			
			
			
			
			
		}
		
	}else     // 사용중
	{
		
		switch(batt_dis_stat)
		{
			case BATT_DIS_IDLE:
				
			if(batt_vol_data < BATTERY_EXTREAME_VALUE)    // 3.1v
			{
				batt_dis_stat=BATT_DIS_EXTREAM;
/*				BATT_LED_LEVEL1_ON();
				BATT_LED_LEVEL2_OFF();
				BATT_LED_LEVEL3_OFF();
*/
				
				
			}else if((batt_vol_data >= BATTERY_EXTREAME_VALUE) && (batt_vol_data < BATTERY_MID_VALUE))
			{
				batt_dis_stat=BATT_DIS_LEVEL1;
/*				BATT_LED_LEVEL1_ON();
				BATT_LED_LEVEL2_OFF();
				BATT_LED_LEVEL3_OFF();
*/
		}
				
     	else if((batt_vol_data >= BATTERY_MID_VALUE) && (batt_vol_data < BATTERY_HIGH_VALUE))
			{
				batt_dis_stat=BATT_DIS_LEVEL2;
/*				BATT_LED_LEVEL1_ON();
				BATT_LED_LEVEL2_ON();
				BATT_LED_LEVEL3_OFF();
*/
				
			}else if((batt_vol_data >= BATTERY_HIGH_VALUE))
			{
				batt_dis_stat=BATT_DIS_LEVEL3;
/*				BATT_LED_LEVEL1_ON();
				BATT_LED_LEVEL2_ON();
				BATT_LED_LEVEL3_ON();
*/
				
			}
			
			
			break;
			case BATT_DIS_EXTREAM:
/*				BATT_LED_LEVEL1_TOGGLE();
				BATT_LED_LEVEL2_OFF();
				BATT_LED_LEVEL3_OFF();
*/
			        if(batt_vol_data < BATTERY_OFF_VALUE)    // 
				{
					POWER_OFF() ;
					
				}
			break;
			case BATT_DIS_LEVEL1:
	
				if(batt_vol_data < BATTERY_EXTREAME_VALUE)    // 3v
				{
					batt_dis_stat=BATT_DIS_EXTREAM;
				
	/*				BATT_LED_LEVEL1_ON();
					BATT_LED_LEVEL2_OFF();
					BATT_LED_LEVEL3_OFF();
					*/
					//					BATT_LED_LEVEL4_OFF();
				}
			break;
			case BATT_DIS_LEVEL2:
							if( (batt_vol_data < BATTERY_LOW_VALUE))
				{
					batt_dis_stat=BATT_DIS_LEVEL1;
//					BATT_LED_LEVEL1_ON();
//					BATT_LED_LEVEL2_OFF();
//					BATT_LED_LEVEL3_OFF();
//					BATT_LED_LEVEL4_OFF();
				}
			break;
			case BATT_DIS_LEVEL3:
					if((batt_vol_data < BATTERY_MID_VALUE))
				{
					batt_dis_stat=BATT_DIS_LEVEL2;
//					BATT_LED_LEVEL1_ON();
//					BATT_LED_LEVEL2_ON();
//					BATT_LED_LEVEL3_OFF();
//					BATT_LED_LEVEL4_OFF();
				
				}
			break;
			case BATT_DIS_LEVEL4:
				if((batt_vol_data < BATTERY_HIGH_VALUE))
				{
					batt_dis_stat=BATT_DIS_LEVEL3;
//					BATT_LED_LEVEL1_ON();
//					BATT_LED_LEVEL2_ON();
//					BATT_LED_LEVEL3_ON();

				
				}
			break;
			case BATT_DIS_FULL:
				sys_printf("BATT_DIS_FULL \n");
		
				batt_dis_stat=BATT_DIS_LEVEL4;
			break;	
			default:
					batt_dis_stat=BATT_DIS_LEVEL4;
//					BATT_LED_LEVEL1_OFF();
//					BATT_LED_LEVEL2_OFF();
//					BATT_LED_LEVEL3_OFF();
			break;
				
		}
//batt_dis_stat=BATT_DIS_EXTREAM;  // for test
	
		if ( batt_dis_stat == BATT_DIS_EXTREAM) {
		    GREEN_LED_TOGGLE();
		} else {
		    GREEN_LED_ON();
		}

		
	}
	
	
	
}



