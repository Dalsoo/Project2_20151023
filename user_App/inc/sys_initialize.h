/*******************************************************************************
* File Name          : sys_initialize.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.11
* Description        : System initialize
*******************************************************************************/



#ifndef  __SYS_INITIALIZE_H__
#define __SYS_INITIALIZE_H__


#define MAX_SAMPLE_LEVELS        (65535)               /**< Maximum number of sample levels. */
#define INCREMENT_VALUE          (16)                /**< Value by which the pulse_width is incremented/decremented for each event. */
#define TIMER_PRESCALERS         (9U)                /**< Prescaler setting for timer. */
#define TIMER_CC_CNT  (31250-1)
#define MAIN_CLK    16000000         //16MHz
#define TIMER_CLK (MAIN_CLK/(2^TIMER_PRESCALERS))








void sys_Initialize(void);

void sys_Sensor_Init(void);
void sys_Sensor_Value_Init(void);


#endif
