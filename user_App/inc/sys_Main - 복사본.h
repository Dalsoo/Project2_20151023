/*******************************************************************************
* File Name          : sys_main.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.11
* Description        : System main  header
*******************************************************************************/

#ifndef  __SYS_MAIN_H__
#define __SYS_MAIN_H__

typedef   signed          char s8;
typedef   signed short     int s16;
typedef   signed           int s32;
    /* minimum-width unsigned integer types */
typedef unsigned          char u8;
typedef unsigned short     int u16;
typedef unsigned           int u32;
 

#include <stdint.h>
#include <string.h>
#include <ble_gap.h>
#include "nordic_common.h"
#include "nrf.h"
#include "nrf51_bitfields.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_conn_params.h"
#include "softdevice_handler.h"
#include "app_timer.h"
#include "app_gpiote.h"
#include "app_button.h"
#include "ble_nus.h"
#include "simple_uart.h"
#include "app_util_platform.h"
#include "bsp.h"

#include "nrf_delay.h"

#include "nrf_gpiote.h"
/**********************************
        user include header
**********************************/
#include "sys_uart.h"
#include "sys_i2c_driver.h"
#include "sys_initialize.h"
#include "sys_ble_process.h"
//#include "sys_Sensor.h"
#include "sys_delay.h"
//#include "sys_body_temp.h"

#include "sys_TempHumiPress.h"
#include "sys_Gas_Battery.h"
#include "sys_iAQ_sensor.h"
#include "sys_dust_sensor.h"

typedef struct
{
	u8 check_time;
	bool release;
	bool push;
	bool status;
	
	
}sys_KeyCheck_struct;

typedef struct
{
	u8  char_status;
	u8 status;
	u8 battery_cnt;
	
	bool Charge_Flag;
	bool Batt_Full_Flag;
	bool Batt_High_Flag;
	bool Batt_Mid_Flag;
	bool Batt_Low_Flag;
	bool Batt_Extream_Flag;
	
	
}sys_battery_struct;

extern sys_battery_struct sys_battery_str;

extern sys_KeyCheck_struct sys_ION_KeyCheck_str;

/***********************************
	Debug Mode Define 
 ********************************/
 #define _SYS_DEBUG 1
 #define LED_TEST_DEBUG   0
 #define __NRF_DK_BOARD  0 //dk board test 시
 
 #define __I2C_DRIVER_USE   1   // I2C DRIVER 사용시
 
 

#define MAIN_TIMER_TICK   1000       // ms
#define BLE_COMM_TIMER_TICK  500   //ms
#define EEPROM_DATA_TIMER_TICK 30  //ms
#define EXT_PORT_TIMER_TICK      100   //ms

#define HRS_CHECK_TIMER_TICK	100    //ms
#define LED_TIMER_TICK			200   //ms


#define USER_APP_TIMER_NUMBER  5        // user timer number

/**********************************

    Nordic  define
*********************************/


#define IS_SRVC_CHANGED_CHARACT_PRESENT 0                                           /**< Include or not the service_changed characteristic. if not enabled, the server's database cannot be changed for the lifetime of the device*/


#define WAKEUP_BUTTON_ID              2//17                                           /**< Button used to wake up the application. */

#if __NRF_DK_BOARD >0
#define DEVICE_NAME_SELECT    2
#else

#define DEVICE_NAME_SELECT    0

#endif

#if (DEVICE_NAME_SELECT == 0)
#define DEVICE_NAME                     "Gift Air co. Project2" 
#elif (DEVICE_NAME_SELECT == 1)
#define DEVICE_NAME                     "Gift Air co JSU TEST." 
#elif (DEVICE_NAME_SELECT == 2)
#define DEVICE_NAME                     "Gift Air co DK board." 
#elif (DEVICE_NAME_SELECT == 3)
#define DEVICE_NAME                     "Gift Air co TEST." 
#endif

//#define DEVICE_NAME                     "Gift Air co TEST." 
//#define DEVICE_NAME                     "Gift Air co jsu test."                               /**< Name of device. Will be included in the advertising data. */
//#define DEVICE_NAME                     "Gift Air co DK board"                               /**< Name of device. Will be included in the advertising data. */
#define APP_ADV_INTERVAL                64                                          /**< The advertising interval (in units of 0.625 ms. This value corresponds to 40 ms). */
#define APP_ADV_TIMEOUT_IN_SECONDS    0//180                                         /**< The advertising timeout (in units of seconds). */

#define APP_TIMER_PRESCALER             0                                           /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_MAX_TIMERS             (2+ BSP_APP_TIMERS_NUMBER+USER_APP_TIMER_NUMBER)     // (2 + BSP_APP_TIMERS_NUMBER)                 /**< Maximum number of simultaneously created timers. */
#define APP_TIMER_OP_QUEUE_SIZE         4                                           /**< Size of timer operation queues. */

#define APP_GPIOTE_MAX_USERS          1                                           /**< Maximum number of simultaneously gpiote users. */

#define MIN_CONN_INTERVAL               16                                          /**< Minimum acceptable connection interval (20 ms), Connection interval uses 1.25 ms units. */
#define MAX_CONN_INTERVAL               60                                          /**< Maximum acceptable connection interval (75 ms), Connection interval uses 1.25 ms units. */
#define SLAVE_LATENCY                   0                                           /**< slave latency. */
#define CONN_SUP_TIMEOUT                400                                         /**< Connection supervisory timeout (4 seconds), Supervision Timeout uses 10 ms units. */
#define FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(5000, APP_TIMER_PRESCALER)  /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(30000, APP_TIMER_PRESCALER) /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT    3                                           /**< Number of attempts before giving up the connection parameter negotiation. */

#define BUTTON_DETECTION_DELAY          APP_TIMER_TICKS(50, APP_TIMER_PRESCALER)    /**< Delay from a GPIOTE event until a button is reported as pushed (in number of timer ticks). */

#define SEC_PARAM_TIMEOUT               30                                          /**< Timeout for Pairing Request or Security Request (in seconds). */
#define SEC_PARAM_BOND                  1                                           /**< Perform bonding. */
#define SEC_PARAM_MITM                  0                                           /**< Man In The Middle protection not required. */
#define SEC_PARAM_IO_CAPABILITIES       BLE_GAP_IO_CAPS_NONE                        /**< No I/O capabilities. */
#define SEC_PARAM_OOB                   0                                           /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE          7                                           /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE          16                                          /**< Maximum encryption key size. */

#define START_STRING                    "Start...\n"                                /**< The string that will be sent over the UART when the application starts. */

#define DEAD_BEEF                       0xDEADBEEF                                  /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */



/***********************************
	GPIO Initail Define 
 *****************************/
#define SYS_I2C_CLK   2      
#define SYS_I2C_DATA 3

#define SYS_LED1    23
#define SYS_LED2   24

#define SYS_BUTTON 6


#define SYS_SPI_SS  7
#define SYS_SPI_CLK 8
#define SYS_SPI_MOSI 9
#define SYS_SPI_MISO 10


/****************  GPIO PORT INITIAL  ************/

 #define ADIN2_IN 			2
 #define ADIN3_IN			3

#define CHARGE_IC_PG_IN	4
#define CHARGE_IC_STAT1_IN 5
#define CHARGE_IC_STAT2_IN 6
#define LOW_BATT_ALM_IN	12
#define BAT_RSTIO_OUT		13

#define SENSOR_POWER_OUT	16

#define ADAPTOR_DETECT_IN	18
#define POWER_HOLD_OUT		19


/***************   PROJECT 2 ************/

/***    led  ******/

#define BATT_LED_LEVEL1_OUT         23
#define BATT_LED_LEVEL2_OUT         22
#define BATT_LED_LEVEL3_OUT         21
//#define BATT_LED_LEVEL4_OUT          24

#define DUST_STAT_LED_BAD_OUT  29 //24
#define DUST_STAT_LED_MEDIOCRE_OUT   28 //25
#define DUST_STAT_LED_FAIR_OUT   25 //28
#define DUST_STAT_LED_EXCELLENT_OUT  24//29

#define BT_CONNECT_ON_LED                 3
#define BT_CONNECT_OFF_LED                2

#define POWER_LED_OUT			                     8

#define ION_LED_OUT       10

/**********  s w input  ***********/ 
#define ION_ON_SW_IN			15
#define DUST_SW_IN				    20
#define POWER_SW_IN		17



/**********   control port  ***********/
#define DUST_LED_OUTPUT		0   // dust control
#define DUST_LED_INPUT		1     // adc


#define ION_ON				14         // ion on/off





//#define 


/***********************************
	Model & Version Define 
 **********************************/

#define PROJECT_MODEL_NAME     " Gift Air "   // 10자리 맞출 것.
#define VER_MAJOR       0 
#define VER_MINOR       1
#define VER_PRODUCT   1

#define GREEN_LED_ON()    nrf_gpio_pin_clear(GREEN_LED_OUT);
#define GREEN_LED_OFF()    nrf_gpio_pin_set(GREEN_LED_OUT);
#define GREEN_LED_TOGGLE() 	nrf_gpio_pin_toggle(GREEN_LED_OUT);

#define RED_LED_ON()    nrf_gpio_pin_clear(RED_LED_OUT);
#define RED_LED_OFF()    nrf_gpio_pin_set(RED_LED_OUT);
#define RED_LED_TOGGLE() 	nrf_gpio_pin_toggle(RED_LED_OUT);

#define ORANGE_LED_ON()    nrf_gpio_pin_clear(ORANGE_LED_OUT);
#define ORANGE_LED_OFF()    nrf_gpio_pin_set(ORANGE_LED_OUT);
#define ORANGE_LED_TOGGLE() 	nrf_gpio_pin_toggle(ORANGE_LED_OUT);

#define POWER_ON()    nrf_gpio_pin_set(POWER_HOLD_OUT);
#define POWER_OFF()    nrf_gpio_pin_clear(POWER_HOLD_OUT);

#define SENSOR_POWER_ON()   nrf_gpio_pin_set(SENSOR_POWER_OUT);
#define SENSOR_POWER_OFF()   nrf_gpio_pin_clear(SENSOR_POWER_OUT);

#define POWER_SW_READ()   nrf_gpio_pin_read(POWER_SW_IN);

#define APDAPTOR_DETECT_READ()  nrf_gpio_pin_read(ADAPTOR_DETECT_IN);

#if __NRF_DK_BOARD >0
#define DUST_LED_OFF()	 nrf_gpio_pin_set(DUST_LED_OUTPUT);
#define DUST_LED_ON()	 nrf_gpio_pin_clear(DUST_LED_OUTPUT);

#else
#define DUST_LED_OFF()	 nrf_gpio_pin_set(DUST_LED_OUTPUT);
#define DUST_LED_ON()	 nrf_gpio_pin_clear(DUST_LED_OUTPUT);
//#define DUST_LED_ON()	 nrf_gpio_pin_set(DUST_LED_OUTPUT);
//#define DUST_LED_OFF()	 nrf_gpio_pin_clear(DUST_LED_OUTPUT);

#endif

#define ION_OUT_ON() nrf_gpio_pin_set(ION_ON);
#define ION_OUT_OFF()  nrf_gpio_pin_clear(ION_ON);




/***********************************************/

#define DUST_STAT_LED_BAD_ON()  nrf_gpio_pin_clear(DUST_STAT_LED_BAD_OUT);  
#define DUST_STAT_LED_BAD_OFF()  nrf_gpio_pin_set(DUST_STAT_LED_BAD_OUT);  

#define DUST_STAT_LED_MEDIOCRE_ON()  nrf_gpio_pin_clear(DUST_STAT_LED_MEDIOCRE_OUT);  
#define DUST_STAT_LED_MEDIOCRE_OFF()  nrf_gpio_pin_set(DUST_STAT_LED_MEDIOCRE_OUT);  

#define DUST_STAT_LED_FAIR_ON()  nrf_gpio_pin_clear(DUST_STAT_LED_FAIR_OUT);  
#define DUST_STAT_LED_FAIR_OFF()  nrf_gpio_pin_set(DUST_STAT_LED_FAIR_OUT);  

#define DUST_STAT_LED_EXCELLENT_ON()  nrf_gpio_pin_clear(DUST_STAT_LED_EXCELLENT_OUT);  
#define DUST_STAT_LED_EXCELLENT_OFF()  nrf_gpio_pin_set(DUST_STAT_LED_EXCELLENT_OUT);  


#define BATT_LED_LEVEL1_ON()  			nrf_gpio_pin_clear(BATT_LED_LEVEL1_OUT);  
#define BATT_LED_LEVEL1_OFF()  			nrf_gpio_pin_set(BATT_LED_LEVEL1_OUT);  
 #define BATT_LED_LEVEL1_TOGGLE()            nrf_gpio_pin_toggle(BATT_LED_LEVEL1_OUT)
 
#define BATT_LED_LEVEL2_ON()  			nrf_gpio_pin_clear(BATT_LED_LEVEL2_OUT);  
#define BATT_LED_LEVEL2_OFF() 			nrf_gpio_pin_set(BATT_LED_LEVEL2_OUT);  
 #define BATT_LED_LEVEL2_TOGGLE()            nrf_gpio_pin_toggle(BATT_LED_LEVEL2_OUT)

#define BATT_LED_LEVEL3_ON()  			nrf_gpio_pin_clear(BATT_LED_LEVEL3_OUT);  
#define BATT_LED_LEVEL3_OFF()  			nrf_gpio_pin_set(BATT_LED_LEVEL3_OUT);  
 #define BATT_LED_LEVEL3_TOGGLE()            nrf_gpio_pin_toggle(BATT_LED_LEVEL3_OUT)

#define POWER_LED_ON() nrf_gpio_pin_clear(POWER_LED_OUT);
#define POWER_LED_OFF() nrf_gpio_pin_set(POWER_LED_OUT);


/****  TEST LED *****/
#define ION_LED_OUT_OFF()    nrf_gpio_pin_set(ION_LED_OUT);
#define ION_LED_OUT_ON()  nrf_gpio_pin_clear(ION_LED_OUT);

#define BLE_CONNECTION_LED_ON()   nrf_gpio_pin_clear(BT_CONNECT_ON_LED);
#define BLE_CONNECTION_LED_OFF()   nrf_gpio_pin_set(BT_CONNECT_ON_LED);




//#define BATT_LED_LEVEL4_ON()  			nrf_gpio_pin_clear(BATT_LED_LEVEL4_OUT);  
//#define BATT_LED_LEVEL4_OFF()  			nrf_gpio_pin_set(BATT_LED_LEVEL4_OUT);  
 //#define BATT_LED_LEVEL4_TOGGLE()            nrf_gpio_pin_toggle(BATT_LED_LEVEL4_OUT)

//extern   void detectHeartRate( unsigned int *irBuffer , int irBuffer_length, int *heartRate , unsigned short peak_height, unsigned short peak_distance, unsigned short *HRvalid ) ;

//extern   void arterialOxygenSaturation(unsigned int *irBuffer ,  int irBuffer_length, unsigned int *redBuffer ,   int *SPO2, int *SPO2Valid );   



extern app_timer_id_t m_Main_timer_id;
extern app_timer_id_t m_Adc_timer_id;
extern app_timer_id_t m_Ble_Tx_Timer_id;
extern app_timer_id_t m_Ble_eeprom_read_timer_id;

extern app_timer_id_t	m_Ble_Led_Timer_id;
//extern app_timer_id_t m_Hrs_data_read_timer_id;

extern  u16 body_temp;

void advertising_stop(void);
void advertising_start(void);

void sys_ADC_Handler(void * p_context);
void sys_Ble_Tx_Handler(void * p_context) ;
void sys_Ble_eeprom_Handler(void * p_context);
void sys_Main_Timer_Handler(void * p_context);
void sys_Ble_Led_Timer_Handler(void * p_context);
//void sys_Hrs_data_Read_Handler(void * p_context)   ;

void sys_Ble_Tx_Handler_Start(void);
void sys_Ble_Tx_Handler_Stop(void);
void sys_Ble_eeprom_Start(void);
void sys_Ble_eeprom_Stop(void);

void sys_Ble_Led_timer_Start(void);
void sys_Ble_Led_timer_Stop(void);


 void sys_Ion_on_off(bool mode);
 
//void sys_HRS_Data_Read_Start(void);
//void sys_HRS_Data_Read_Stop(void);

#endif

