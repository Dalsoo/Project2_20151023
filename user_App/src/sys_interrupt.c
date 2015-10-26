/*******************************************************************************
* File Name          : sys_interrupt
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.11
* Description        : interrupt function
*******************************************************************************/



#include "sys_main.h"

u32 test_timer=0;
u32 int_test=0;


//BodyTempStutus Body_temp_status=BODY_TEMP_STATUS_NORMAL;

bool led_timer_status=false;
bool extern_power_flag=false;
 u16 body_temp=0;
 u8 adapt_timer=0;
 
 sys_DustSensor_structure sys_DustSensor_str;
 sys_KeyCheck_struct sys_ION_KeyCheck_str;
 
 
 void sys_Ion_on_off(bool mode)
 {
	 if(mode)
	 {
		 ION_OUT_ON();
		 ION_LED_OUT_ON(); 
		 
	 }else
	 {
		 ION_OUT_OFF();
		 ION_LED_OUT_OFF(); 
		 
	 }
	 
	 
 }
 
void TIMER2_IRQHandler(void)
{
	
	   // static bool cc0_turn = false; /**< Keeps track of which CC register to be used. */

    if (NRF_TIMER2->EVENTS_COMPARE[0] != 0) 
		{
			    NRF_TIMER2->EVENTS_COMPARE[0]=0;
			   
			   NRF_TIMER2->CC[0] = NRF_TIMER2->CC[0]+TIMER_CC_CNT ;
			
//			nrf_gpio_pin_toggle(SYS_LED1);  //jsu test
//			sys_printf("%d\n",++int_test);
//			//test_timer++;
			++int_test;
			
		}
}


typedef enum  
{
	
	SYS_BLE_IDLE_STATE,
	SYS_BLE_CONNECTION,
	SYS_BLE_DISCONNECTION,
	SYS_BLE_WAIT	
	
}Main_status ;

//u8 test_timer=0;
void sys_Main_Timer_Handler(void * p_context)                //1000ms
{

	
	static u8 sw_timer=0;
	
	static Main_status state = SYS_BLE_IDLE_STATE;
	static bool first_check=false;
	bool key_release_flag=false;     // dust sensor 구동
	u16 batt_curr_data=0,batt_vol_data=0;  
	u8 battery_flag=0;
	 sys_DustSensor_structure *pDustSensor = &sys_DustSensor_str;
	sys_KeyCheck_struct *pKeyCheck = &sys_ION_KeyCheck_str;
		
	
	UNUSED_PARAMETER(p_context);
	
	
	NRF_WDT->RR[0] = WDT_RR_RR_Reload;  //Reload watchdog register 0
	
        iAQ_Ready_timer++;
	
	if(!first_check )
	{
		first_check=true;
		
	       sys_Sensor_Init();
		
		sys_Sensor_Value_Init();
		pDustSensor->dust_stat_flag = true;
		pDustSensor->dust_timer = (DUST_CHECK_TIME*60);
		sys_printf("Sensor init\n");
		
	}
	

 #if _SYS_DEBUG > 2            // BME 280 TEST
	u16 Humi_data=0;
	u32 Temp_data=0,Press_data=0;
	
	sys_GetBME280_Force_Temp_Press_Hudi(&Temp_data,&Press_data,&Humi_data);
#endif	
	 
#if _SYS_DEBUG > 2               //  IAQ TEST   ,, BETTERY TEST
	u16 co2=0,Tvoc=0;
	u16 batt_curr_data=0,batt_vol_data=0;
	
	//sys_printf("systest \n");
		sys_GetiAQSensor_Data(&co2,&Tvoc);
	
	//sys_GetBatteryInfo(&batt_curr_data,&batt_vol_data);
	
#endif	
	 
	 
#if __NRF_DK_BOARD >0	 
	 if(!nrf_gpio_pin_read(ADAPTOR_DETECT_IN))
#else
	  if(nrf_gpio_pin_read(ADAPTOR_DETECT_IN))
 #endif
	 {
		
		 adapt_timer++;
		 if(adapt_timer > 1)
		 {
		//	 sys_printf("Adapt detect \n");
			 extern_power_flag= true;
			 nrf_gpio_pin_clear(POWER_HOLD_OUT);    //power off
			 
		//	  while(1);
		 }
	 }else
	 {
		 adapt_timer=0;
		 extern_power_flag= false;
		 
	 }
	 
	 if(extern_power_flag)
	 {
		 if(nrf_gpio_pin_read(CHARGE_IC_STAT1_IN))  //CHARGER COMPLETE
		 {
			// ORANGE_LED_OFF();
			// RED_LED_OFF() ;
			// GREEN_LED_ON();
			 
		 }else                                       			//CHARGING
		 {
			// ORANGE_LED_OFF();
			// GREEN_LED_OFF();
			// RED_LED_ON() ;
			 
		 }
		 
	 }else
	 {
		 
	 }
#if __NRF_DK_BOARD >0
		if(!nrf_gpio_pin_read(POWER_SW_IN))
#else
		if(nrf_gpio_pin_read(POWER_SW_IN))
#endif
		{
			sw_timer++;
			sys_printf("Power sw cnt[%d]\n",sw_timer);
			//sys_Buzzer_on(1);
			if(sw_timer > 3)
			{
				sys_printf("Main Power Off\n");
			//	RED_LED_ON();
				POWER_LED_OFF();    // 전원 oFF

				//dalsoo: BT off 				
				state = SYS_BLE_DISCONNECTION;
				sys_Ble_Tx_Handler_Stop();
				BLE_CONNECTION_LED_OFF();
	
				 sys_Ion_on_off(false);  //dalsoo: Ion off
	
      	 DUST_STAT_LED_BAD_OFF();
		     DUST_STAT_LED_MEDIOCRE_OFF();
		     DUST_STAT_LED_FAIR_OFF();
		     DUST_STAT_LED_EXCELLENT_OFF();
         DUST_LED_OFF()	;
				 pDustSensor->dust_stat_flag = false;		  // dust sensor LED off
				
	//			sys_HRS_ShutDown();
				//nrf_gpio_pin_clear(RED_LED_OUT);
				//nrf_delay_ms(1000);
				nrf_gpio_pin_clear(POWER_HOLD_OUT);
				
			} else
			{
				if (state != SYS_BLE_CONNECTION)
				{ 
					//led scenario: power led is used for charging led too			  POWER_LED_ON();    // 전원 LED on
			
				}
			}
		}else
		{
			sw_timer=0;
				
		}
		
				if(nrf_gpio_pin_read(DUST_SW_IN))
				{
					key_release_flag=true;

				}
		
		if(key_release_flag)
		{
				key_release_flag=false;
					pDustSensor->dust_stat_flag = true;
					pDustSensor->dust_timer = (DUST_CHECK_TIME*60);
					sys_printf("dust sensor On \n");
					
		}else
		{

		}

		if(pDustSensor->dust_stat_flag)
		{
			Dust_Sensor_Process();
		}else
		{
			
			
		}
		
		
#if __NRF_DK_BOARD >0
		if(!nrf_gpio_pin_read(ION_ON_SW_IN))
#else
		if(nrf_gpio_pin_read(ION_ON_SW_IN))
#endif
		{
		       pKeyCheck->push = true;
			pKeyCheck->release =false;
			pKeyCheck->check_time++;
			
		}else
		{
			if(pKeyCheck->push)
			{
				
				pKeyCheck->release =true;
			}
			 pKeyCheck->push = false;
			pKeyCheck->check_time=0;
	
		}
		
		if( pKeyCheck->push)
		{
			 pKeyCheck->push= false;
			if(pKeyCheck->status)
			{
				pKeyCheck->status= false;
				sys_Ion_on_off(false);
				//ION_OUT_OFF();
				sys_printf("ION OFF \n");
			}else
			{
				pKeyCheck->status= true;
				sys_Ion_on_off(true);
				//ION_OUT_ON();
				sys_printf("ION ON \n");
				
			}
			
		}else
		{
			/* Empty */
			
		}
		
		
		
		
	//}
		switch(state)
		{
			case SYS_BLE_IDLE_STATE:
					     
				if(sys_Ble_Status)
				{
					state = SYS_BLE_CONNECTION;
					sys_Ble_Tx_Handler_Start();
  				POWER_LED_OFF();    // dalsoo: just to turn off the green LED
					BLE_CONNECTION_LED_ON();
				}
		
			
			
			break;
			case SYS_BLE_CONNECTION:
				if(!sys_Ble_Status)
				{
					state = SYS_BLE_DISCONNECTION;
					sys_Ble_Tx_Handler_Stop();
					BLE_CONNECTION_LED_OFF();
					//changed led scenario:					POWER_LED_ON();    // dalsoo: Green LED on
				}
				
			break;
			case SYS_BLE_DISCONNECTION:
				
			//	sys_Ble_eeprom_Stop();
				 state=SYS_BLE_WAIT;
			break;
			case SYS_BLE_WAIT:
				
				if(sys_Ble_Status)
				{
					state = SYS_BLE_CONNECTION;
					sys_Ble_Tx_Handler_Start();
 	   			POWER_LED_OFF();    // dalsoo: just to turn off the green LED	
					BLE_CONNECTION_LED_ON();
				}
				
			
				
			break;
			
			default:
				
			break;
			
			
			
		}
		
		if(state ==SYS_BLE_WAIT)
		{
			
			
		}else
		{
			/*  Empty */
			
		}
		
		
		battery_flag = sys_GetBatteryInfo(&batt_curr_data,&batt_vol_data);

		//dalsoo: changed for led scenario. toggle 1sec if charging 	if(battery_flag && first_check)
		{
//				      GREEN_LED_TOGGLE();
		    	      sys_Battey_manager(extern_power_flag,batt_vol_data);
		}
				
#if LED_TEST_DEBUG > 0
			
		DUST_STAT_LED_BAD_ON();
		DUST_STAT_LED_MEDIOCRE_ON();
		DUST_STAT_LED_FAIR_ON();
		DUST_STAT_LED_EXCELLENT_ON();

		BATT_LED_LEVEL1_ON();
		BATT_LED_LEVEL2_ON();
		BATT_LED_LEVEL3_ON();
		ION_LED_OUT_ON() ;
		BLE_CONNECTION_LED_ON() ;
#endif
		
		
		
		NRF_WDT->RR[0] = WDT_RR_RR_Reload; 
	//}

}

void sys_Ble_Led_Timer_Handler(void * p_context)   
{
	
		UNUSED_PARAMETER(p_context);
	NRF_WDT->RR[0] = WDT_RR_RR_Reload;  //Reload watchdog register 0
	
}


void sys_ADC_Handler(void * p_context)   
{
	UNUSED_PARAMETER(p_context);
	
	u16 adc_data;
	NRF_ADC->TASKS_START = 1;
	
	while(NRF_ADC->BUSY);
	
	adc_data= NRF_ADC->RESULT;
#if 	_SYS_DEBUG > 0
	sys_printf("adc_data = [%d]\n",adc_data);
#endif
	
	NRF_ADC->TASKS_STOP =1;
	
	
}

void sys_Ble_Tx_Handler(void * p_context)      // 1sec
{
	UNUSED_PARAMETER(p_context);
	//nrf_gpio_pin_toggle(RED_LED_OUT);
	NRF_WDT->RR[0] = WDT_RR_RR_Reload;  //Reload watchdog register 0
	sys_ble_process();
	NRF_WDT->RR[0] = WDT_RR_RR_Reload;  //Reload watchdog register 0
	
	
}

void sys_Ble_eeprom_Handler(void * p_context)   
{
	UNUSED_PARAMETER(p_context);
	
	
	
	
	
}

void sys_Ble_Tx_Handler_Start(void)
{
	uint32_t err_code;

	err_code  =app_timer_start(m_Ble_Tx_Timer_id, APP_TIMER_TICKS(500, APP_TIMER_PRESCALER),NULL);
	APP_ERROR_CHECK(err_code);
}

void sys_Ble_Tx_Handler_Stop(void)
{
	app_timer_stop(m_Ble_Tx_Timer_id);	
	
}
void sys_Ble_eeprom_Start(void)
{
	uint32_t err_code;

	err_code  =app_timer_start(m_Ble_eeprom_read_timer_id, APP_TIMER_TICKS(30, APP_TIMER_PRESCALER),NULL);
	APP_ERROR_CHECK(err_code);
}

void sys_Ble_eeprom_Stop(void)
{
	app_timer_stop(m_Ble_eeprom_read_timer_id);	
	
}

void sys_Ble_Led_timer_Start(void)
{
	uint32_t err_code;

	err_code  =app_timer_start(m_Ble_Led_Timer_id, APP_TIMER_TICKS(LED_TIMER_TICK, APP_TIMER_PRESCALER),NULL);
	APP_ERROR_CHECK(err_code);
}

void sys_Ble_Led_timer_Stop(void)
{
	app_timer_stop(m_Ble_Led_Timer_id);	
	
}



void GPIOTE_IRQHandler(void)
{
    // Event causing the interrupt must be cleared.
    if ((NRF_GPIOTE->EVENTS_IN[0] == 1) &&
        (NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk))
    {
        NRF_GPIOTE->EVENTS_IN[0] = 0;
    }
}



