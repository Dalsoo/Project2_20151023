/*******************************************************************************
* File Name          : sys_initialize.c
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.11
* Description        : System initialize
*******************************************************************************/

#include "sys_main.h"





static void sys_Uart_init(void)
{
    /**@snippet [UART Initialization] */
    simple_uart_config(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, 0);
    
    NRF_UART0->INTENSET = UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos;
    
    NVIC_SetPriority(UART0_IRQn, APP_IRQ_PRIORITY_LOW);
    NVIC_EnableIRQ(UART0_IRQn);
    /**@snippet [UART Initialization] */
}

static void sys_Gpio_init(void)
{
	/* GPIO OUTPUT  ************/

  nrf_gpio_cfg_output( ION_LED3_OUT );
	nrf_gpio_cfg_output( ION_LED4_OUT );
	nrf_gpio_cfg_output( ION_LED2_OUT );
		nrf_gpio_cfg_output( ION_LED1_OUT );
//	nrf_gpio_cfg_output(BATT_LED_LEVEL4_OUT);
	
	nrf_gpio_cfg_output(DUST_STAT_LED_BAD_OUT);
	nrf_gpio_cfg_output(DUST_STAT_LED_MEDIOCRE_OUT);
	nrf_gpio_cfg_output(DUST_STAT_LED_FAIR_OUT);
	nrf_gpio_cfg_output(DUST_STAT_LED_EXCELLENT_OUT);
	
	nrf_gpio_cfg_output(DUST_LED_OUTPUT);
	nrf_gpio_cfg_output(ION_ON);
//	nrf_gpio_cfg_output(ION_LED_OUT);
	nrf_gpio_cfg_output(POWER_LED_OUT);
	nrf_gpio_cfg_output(SENSOR_POWER_OUT);
	
	nrf_gpio_cfg_output(POWER_SW_IN);
	
	nrf_gpio_cfg_output(POWER_HOLD_OUT);

		nrf_gpio_cfg_output(BT_CONNECT_ON_LED);
// 		nrf_gpio_cfg_output(BT_CONNECT_OFF_LED);   




/*  INPUT   *************/

	nrf_gpio_cfg_input(CHARGE_IC_PG_IN,NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_input(CHARGE_IC_STAT1_IN,NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_input(CHARGE_IC_STAT2_IN,NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_input(LOW_BATT_ALM_IN,NRF_GPIO_PIN_NOPULL);
	

	
#if __NRF_DK_BOARD >0
         nrf_gpio_cfg_input(POWER_SW_IN,NRF_GPIO_PIN_PULLUP);
	 nrf_gpio_cfg_input(ADAPTOR_DETECT_IN,NRF_GPIO_PIN_PULLUP);
	 nrf_gpio_cfg_input(ION_ON_SW_IN,NRF_GPIO_PIN_PULLUP);
#else
	nrf_gpio_cfg_input(POWER_SW_IN,NRF_GPIO_PIN_PULLDOWN);
	nrf_gpio_cfg_input(ADAPTOR_DETECT_IN,NRF_GPIO_PIN_NOPULL);
	 nrf_gpio_cfg_input(ION_ON_SW_IN,NRF_GPIO_PIN_NOPULL);
	  nrf_gpio_cfg_input(DUST_SW_IN,NRF_GPIO_PIN_NOPULL);
	//
#endif
	nrf_gpio_cfg_input(ADAPTOR_DETECT_IN,NRF_GPIO_PIN_NOPULL);

	
	nrf_gpio_pin_set(BAT_RSTIO_OUT);

	nrf_gpio_pin_set(POWER_HOLD_OUT);

	nrf_gpio_pin_set(SENSOR_POWER_OUT);
  
	nrf_gpio_pin_clear(DUST_LED_OUTPUT);
	nrf_gpio_pin_clear(ION_ON);
	
	nrf_gpio_pin_set(DUST_STAT_LED_BAD_OUT);
	nrf_gpio_pin_set(DUST_STAT_LED_MEDIOCRE_OUT);
	nrf_gpio_pin_set(DUST_STAT_LED_FAIR_OUT);
	nrf_gpio_pin_set(DUST_STAT_LED_EXCELLENT_OUT);

		nrf_gpio_pin_set(BT_CONNECT_ON_LED);
//	nrf_gpio_pin_set(BT_CONNECT_OFF_LED);
//	nrf_gpio_pin_set(ION_LED_OUT);
	
		nrf_gpio_pin_clear(POWER_LED_OUT);
}

///* ---------------------------------------------------------------
//    TIM2 Configuration: Output Compare Toggle Mode:
//      Ftimer = 16MHz / 2^Prescaler)
//  
//    CC0 update rate = TIM0 counter clock / 5000 = 200Hz(5msec)
//   
//-------------------------------------------------------------------*/
void sys_Timer2_init(void)
{


    NRF_TIMER2->MODE      = TIMER_MODE_MODE_Timer;
    NRF_TIMER2->BITMODE   = TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;
    NRF_TIMER2->PRESCALER = TIMER_PRESCALERS;  //16

    // Clears the timer, sets it to 0.
    NRF_TIMER2->TASKS_CLEAR = 1;


    NRF_TIMER2->CC[0] = TIMER_CC_CNT;
    // Interrupt setup.
    NRF_TIMER2->INTENSET = (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos);
		
		  //  NVIC_EnableIRQ(TIMER2_IRQn);
	  NVIC_EnableIRQ(TIMER2_IRQn);
    __enable_irq();

		NRF_TIMER2->TASKS_START = 1;
	
}

static void sys_Timer_init(void)
{
	// sys_Timer2_init();
	
	
	
}
static void sys_SPI_init(void)
{
	
	
	
}

static void sys_ADC_init(void)
{
	/* Enable interrupt on ADC sample ready event*/		
	NRF_ADC->INTENSET = ADC_INTENSET_END_Msk;   

	
	NRF_ADC->CONFIG	= (ADC_CONFIG_EXTREFSEL_None << ADC_CONFIG_EXTREFSEL_Pos) /* Bits 17..16 : ADC external reference pin selection. */
									| (ADC_CONFIG_PSEL_AnalogInput2 << ADC_CONFIG_PSEL_Pos)					/*!< Use analog input 2 as analog input. */
									| (ADC_CONFIG_REFSEL_VBG << ADC_CONFIG_REFSEL_Pos)							/*!< Use internal 1.2V bandgap voltage as reference for conversion. */
									| (ADC_CONFIG_INPSEL_AnalogInputOneThirdPrescaling << ADC_CONFIG_INPSEL_Pos) /*!< Analog input specified by PSEL with no prescaling used as input for the conversion. */
									| (ADC_CONFIG_RES_10bit << ADC_CONFIG_RES_Pos);									/*!< 8bit ADC resolution. */ 
	
	/* Enable ADC*/
	NRF_ADC->ENABLE = ADC_ENABLE_ENABLE_Enabled;
	
	
}


static void sys_Power_init(void)
{
	
	
	
}

void sys_Extern_init(void)
{

}
void sys_WDT_init(void)
{
	
	NRF_WDT->CONFIG = (WDT_CONFIG_HALT_Pause << WDT_CONFIG_HALT_Pos) | ( WDT_CONFIG_SLEEP_Run << WDT_CONFIG_SLEEP_Pos);
	NRF_WDT->CRV = (5*32768)-1;   //ca  5 sec. timout
	NRF_WDT->RREN |= WDT_RREN_RR0_Msk;  //Enable reload register 0
	NRF_WDT->TASKS_START = 1;
	
	
}
void sys_Initialize(void)
{


	sys_Power_init();
	sys_Uart_init();
	sys_Gpio_init();

	sys_Timer_init();
	sys_SPI_init();
	sys_ADC_init();
	sys_Extern_init();      
	sys_WDT_init();
	
#if __I2C_DRIVER_USE >0	
	twi_master_init();
#else
	sys_I2C_init();
#endif	
}

void sys_Sensor_Init(void)
{
	

	sys_BME280_init();
	sys_STC3115_Init();

}

void sys_Sensor_Value_Init(void)
{
	
		sys_Dust_value_structure 	*pDustValue = &sys_Dust_value_str;

		pDustValue->execellent = DUST_STANDARD_EXCELLENT;
		pDustValue->fair = DUST_STANDARD_FAIR;
		pDustValue->mediocre = DUST_STANDARD_MEDIOCRE;
		pDustValue->bad = DUST_STANDARD_BAD;
	
	
}



