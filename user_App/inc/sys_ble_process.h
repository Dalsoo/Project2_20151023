
/*******************************************************************************
* File Name          : sys_ble_process.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.16
* Description        : Ble Process
*******************************************************************************/


#ifndef  __SYS_BLE_PROCESS_H__
#define __SYS_BLE_PROCESS_H__

#include "sys_main.h"





#define BLE_RX_MAX 21
#define STX    0x02
#define ETX    0x03

/***** command  *******/
#define SENSOR_ON    'O'
#define SENSOR_OFF   'F'
#define SENSOR_STATUS 'S'



/*******  Sensor ID (CMD) ******/
#define HEART 	               		'A'
#define BODY_TEMP               		'B'
#define TEMP_HUMI_PRESS   		'C'
#define FORCE_SENSOR         	'D'
#define GAS_SENSOR            		'E'
#define BATT_INFO              		'F'
#define ALL_SENSOR_CTL    		'G'
#define TIME_GET				'H'
#define TIME_SET				'I'

#define BODY_TEMP_RANGE		'J'
#define EEPROM_READ			'K'
#define FORCE_SENSOR_RANGE	'L'
#define BODY_TEMP_SET		'M'
#define MODEL_NAME          	   	'N'
#define BODY_TEMP_CALCU		'O'

#define DUST_SENSOR_VALUE	'P'
#define CO2_TVOC_SENSOR_VAL	'Q'
#define ION_ON_OFF	'R'

#define DUST_VALUE_SET				'S'

#define VERSION_INFO       		'V'



typedef struct{           
	bool BleRxEndFlag;      // ble data rx end flag
	bool BleRxStxFlag;       // ble data stx check flag
	bool BleRxCompleteFlag;  // ble data checksum check flag
	bool BleRxNackFlag;        // checksum check;
	u16 BleRxLength;              // ble data length
	u8 Ble_Cmd;			// Rx command
	u8 Ble_SubCmd[2]; 		//Sub command
	
}sys_BleRxStruct;


typedef struct{
	u8 sec;
	u8 min;
	u8 hour;
	u8 day;
	u8 month;
	u16 year;
	u8 settime;
	
}sys_Time_struct;

typedef struct{
	u8 time_period;
	u16 normal_temp;
	u16 check_range;
	u16 measure_min;
	u16 measure_max;
		
}sys_Temp_Time_struct;


/**************   Protocol Structure  *************************/
typedef struct{    
	u8 head;
	u8 data_length;
	u8 cmd;
	u8 sub_cmd[2];
		
}sys_protocol_type;



typedef union{
	u8 Txbuffer[16];
	struct{
	sys_protocol_type protocol;
	u8 data[10];
	u8 checksum;
	//u8 etx;
	}str;
}sys_Model_union;

typedef union{
	u8 Txbuffer[10];
	struct{
	sys_protocol_type protocol;
	u8 data[4];
	u8 checksum;
	}str;
}sys_Vision_union;

typedef union{
	u8 Txbuffer[15];
	struct{
	sys_protocol_type protocol;
	u8 data[9];
	u8 checksum;
	//u8 etx;
	}str;
}sys_HeartRate_union;

typedef union{
	u8 Txbuffer[8];
	struct{
	sys_protocol_type protocol;
	u8 data[2];
	u8 checksum;
	//u8 etx;
	}str;
}sys_BodyTemp_union;

typedef union{
	u8 Txbuffer[14];
	struct{
	sys_protocol_type protocol;
	u8 data[8];
	u8 checksum;
	}str;
}sys_TempHumiPress_union;

typedef union{
	u8 Txbuffer[8];
	struct{
	sys_protocol_type protocol;
	u8 data[2];
	u8 checksum;
	}str;
}sys_Force_union;

typedef union{
	u8 Txbuffer[8];
	struct{
	sys_protocol_type protocol;
	u8 data[2];
	u8 checksum;
	}str;
}sys_Gas_union;

typedef union{
	u8 Txbuffer[8];
	struct{
	sys_protocol_type protocol;
	u8 data[2];
	u8 checksum;
	}str;
}sys_BattInfo_union;

typedef union{
	u8 Txbuffer[7];
	struct{
	sys_protocol_type protocol;
	u8 data;
	u8 checksum;
	}str;
}sys_SensorStatus_union;

typedef union{
	u8 Txbuffer[13];
	struct{
	sys_protocol_type protocol;
	u8 data[7];
	u8 checksum;
	}str;
}sys_TimeGet_union;

typedef union{
	u8 Txbuffer[7];
	struct{
	sys_protocol_type protocol;
	u8 data;
	u8 checksum;
	}str;
}sys_TimeSet_union;

typedef union{
	u8 Txbuffer[10];
	struct{
	sys_protocol_type protocol;
	u8 data[4];
	u8 checksum;
	}str;
}sys_BodyTempRange_union;

typedef union{
	u8 Txbuffer[19];
	struct{
	sys_protocol_type protocol;
	u8 TotalCnt[2];
	u8 status;
	u8 BodyTemp[2];
	u8 Force[2];
	u8 HeartRate[3];
	u8 Spo2[3];
	u8 checksum;
	}str;
}sys_EepromRead_union;

typedef union{
	u8 Txbuffer[8];
	struct{
	sys_protocol_type protocol;
	u8 data[2];
	u8 checksum;
	}str;
}sys_ForceLevelSet_union;

typedef union{
	u8 Txbuffer[15];
	struct{
	sys_protocol_type protocol;
	u8 time_period;
	u16 normal_temp;
	u16 check_range;
	u16 measure_min;
	u16 measure_max;	
	u8 checksum;
	}str;
}sys_Body_Temp_Set_union;

typedef union{
	u8 Txbuffer[8];
	struct{
	sys_protocol_type protocol;
	u8 data[2];
	u8 checksum;
	}str;
}sys_Body_Temp_calu_union;

typedef union{
	u8 Txbuffer[8];
	struct{
	sys_protocol_type protocol;
	u8 data[2];
	u8 checksum;
	}str;
}sys_Dust_Sensor_union;


typedef union{
	u8 Txbuffer[10];
	struct{
	sys_protocol_type protocol;
	u8 data[4];
	u8 checksum;
	}str;
}sys_Co2_Tvoc_union;


typedef union{
	u8 Txbuffer[7];
	struct{
	sys_protocol_type protocol;
	u8 data;
	u8 checksum;
	}str;
}sys_ION_On_Off_union;

typedef union{
	u8 Txbuffer[10];
	struct{
	sys_protocol_type protocol;
	u8 excellent;
		u8 fair;
		u8 mediocre;
		u8 bad;
  	u8 checksum;
	}str;
}sys_Dust_Value_Set_union;






extern sys_Model_union 				sys_Model_uni; 
extern sys_Vision_union 				sys_Vision_uni; 
extern sys_HeartRate_union 			sys_HeartRate_uni; 
extern sys_BodyTemp_union 			sys_BodyTemp_uni; 
extern sys_TempHumiPress_union 	sys_TempHumiPress_uni; 
extern sys_Force_union				 sys_Force_uni; 
extern sys_Gas_union 				sys_Gas_uni; 
extern sys_BattInfo_union 			sys_BattInfo_uni; 
extern sys_SensorStatus_union 			sys_SensorStatus_uni; 
extern sys_TimeGet_union 			sys_TimeGet_uni; 
extern sys_TimeSet_union 			sys_TimeSet_uni; 
extern sys_BodyTempRange_union 	sys_BodyTempRange_uni; 
extern sys_EepromRead_union 		sys_EepromRead_uni; 
extern sys_ForceLevelSet_union 		sys_ForceLevelSet_uni; 
extern sys_Body_Temp_Set_union	sys_Body_Temp_Set_uni;
extern sys_Body_Temp_calu_union	sys_Body_Temp_calu_uni;
extern sys_Dust_Value_Set_union	    sys_Dust_Value_Set_uni;


extern sys_Time_struct sys_Time_set;
extern sys_Temp_Time_struct sys_Temp_Time_str;


//typedef union
//{
//	
//	
//	
//}sys_BleTxUnion;


extern uint8_t sys_ble_rx_buf[BLE_RX_MAX];
extern sys_BleRxStruct sys_BleRx_str;

extern bool sys_Ble_Status;



/* function   */
void sys_ble_process(void);
void sys_Get_Body_Temp_Calcu(u8 Ackcmd);

#endif

