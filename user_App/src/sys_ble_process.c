/*******************************************************************************
* File Name          : sys_ble_process.c
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.3.16
* Description        : Ble Process
*******************************************************************************/

#include "sys_main.h"

sys_BleRxStruct sys_BleRx_str;


/****    Ble TX    ***************/

sys_Model_union 			sys_Model_uni;  
sys_Vision_union 			sys_Vision_uni; 
sys_HeartRate_union 		sys_HeartRate_uni; 
sys_BodyTemp_union 		sys_BodyTemp_uni; 
sys_TempHumiPress_union 	sys_TempHumiPress_uni; 
sys_Force_union 			sys_Force_uni; 
sys_Gas_union 			sys_Gas_uni; 
sys_BattInfo_union 			sys_BattInfo_uni; 
sys_SensorStatus_union		sys_SensorStatus_uni; 
sys_TimeGet_union 		sys_TimeGet_uni; 
sys_TimeSet_union 		sys_TimeSet_uni; 
sys_BodyTempRange_union 	sys_BodyTempRange_uni; 
sys_EepromRead_union 		sys_EepromRead_uni; 
sys_ForceLevelSet_union 	sys_ForceLevelSet_uni; 
sys_Body_Temp_Set_union	sys_Body_Temp_Set_uni;
sys_Body_Temp_calu_union	sys_Body_Temp_calu_uni;
sys_Dust_Sensor_union		sys_Dust_Sensor_uni;
sys_Co2_Tvoc_union		sys_Co2_Tvoc_uni;
sys_ION_On_Off_union		sys_ION_On_Off_uni;
sys_Dust_Value_Set_union	    sys_Dust_Value_Set_uni;

bool sys_Ble_Status=false;    // ble 상태 true면 connection, false면  disconnection

sys_Time_struct sys_Time_set;
sys_Temp_Time_struct sys_Temp_Time_str;


uint8_t sys_ble_rx_buf[BLE_RX_MAX];

extern ble_nus_t                        m_nus;

u8 GetCheckSum_Sum_Carry(u8* buffer , u8 byStartIndex, u16 byEndIndex)
{
    u8 j, cs=0;
	  u16 temp=0;;

    for(j=byStartIndex, cs=0; j<= byEndIndex; j++)
    {
        temp += buffer[j];     //sum연산.
    }
      cs = (u8)(((temp >>8)&0x00ff) + (temp & 0x00ff));   // sum carry
		
    return cs;
}

void sys_Ble_Rx_Init(void)
{
	     sys_BleRxStruct *pBleRx = &sys_BleRx_str;
	
	pBleRx->BleRxEndFlag = false;
	pBleRx->BleRxCompleteFlag =false;
	pBleRx->BleRxLength =0;
	pBleRx->BleRxStxFlag=false;
	pBleRx->BleRxNackFlag = true;  
	memset(sys_ble_rx_buf,0,BLE_RX_MAX);
	
	
}

void sys_Ble_Version(u8 Ackcmd)
{
	
	sys_Vision_uni.str.protocol.head = STX;
	sys_Vision_uni.str.protocol.data_length =0x09;
	sys_Vision_uni.str.protocol.cmd= Ackcmd;
	sys_Vision_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_Vision_uni.str.protocol.sub_cmd[1] = 0x00;
	sys_Vision_uni.str.data[0] = VER_MAJOR;
	sys_Vision_uni.str.data[1] = VER_MINOR;
	sys_Vision_uni.str.data[2] = VER_PRODUCT;
	sys_Vision_uni.str.data[3] = 0x00;
	
	
	sys_Vision_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Vision_uni.Txbuffer,1,sys_Vision_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Vision_uni.Txbuffer,sys_Vision_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("[%s]\n",sys_Vision_uni.Txbuffer);

#endif	
	
}
void sys_Ble_Model(u8 Ackcmd)
{
	
	
	sys_Model_uni.str.protocol.head = STX;
	sys_Model_uni.str.protocol.data_length =0x0f;
	sys_Model_uni.str.protocol.cmd= Ackcmd;
	sys_Model_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_Model_uni.str.protocol.sub_cmd[1] = 0x00;
	
	memcpy(sys_Model_uni.str.data,PROJECT_MODEL_NAME,10);
	
	sys_Model_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Model_uni.Txbuffer,1,sys_Model_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Model_uni.Txbuffer,sys_Model_uni.str.protocol.data_length + 1);  //jsu test  +1
	
	
#if _SYS_DEBUG >0
	
	for(u8 i=0;i<sys_Model_uni.str.protocol.data_length ;i++)
	{
		if(sys_Model_uni.Txbuffer[i] == 0x00)
		{
			sys_Model_uni.Txbuffer[i]=0xff;
			
		}
		
	}
	sys_printf("%s",sys_Model_uni.Txbuffer);

#endif	
}
 u8 Tx_data[BLE_RX_MAX]={0,};
void sys_Bt_Nack_Cmd(u8 Ackcmd)
{
	u8 nackcmd=0;
	u8 cs=0;

	sys_BleRxStruct *pBleRx = &sys_BleRx_str;
	
	nackcmd = Ackcmd | 0x80;

	 memcpy(Tx_data,sys_ble_rx_buf,pBleRx->BleRxLength);
	 
	 Tx_data[2] = nackcmd;
	

	
       cs = GetCheckSum_Sum_Carry(Tx_data,1,Tx_data[1]-1);
	
       Tx_data[sys_ble_rx_buf[1]]=cs;

        ble_nus_send_string(&m_nus, Tx_data,pBleRx->BleRxLength); 
		
  #if _SYS_DEBUG >3
        sys_printf("NACK\n\r");
       	for(u8 i=0;i<pBleRx->BleRxLength ;i++)
	{
		if(Tx_data == 0x00)
		{
			Tx_data=0xff;
			
		}
		
	}
	sys_printf("%s",Tx_data);

 #endif
	
	
}

void sys_Froce_Sensor_check(u8 Ackcmd)
{
	u16 force_data=0;
	

	sys_Force_uni.str.protocol.head = STX;
	sys_Force_uni.str.protocol.data_length =0x07;
	sys_Force_uni.str.protocol.cmd= Ackcmd;
	sys_Force_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_Force_uni.str.protocol.sub_cmd[1] = 0x00;
	
	sys_Force_uni.str.data[1] = (force_data >> 8) & 0x00ff;
	sys_Force_uni.str.data[0] = (force_data ) & 0x00ff;
	
	
	sys_Force_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Force_uni.Txbuffer,1,sys_Force_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Force_uni.Txbuffer,sys_Force_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("Force data[%d]\n",force_data);

#endif	
	
	
}
void sys_Heart_Rate_Sensor(u8 Ackcmd)
{
	
	sys_HeartRate_uni.str.protocol.head = STX;
	sys_HeartRate_uni.str.protocol.data_length =0x0e;
	sys_HeartRate_uni.str.protocol.cmd= Ackcmd;
	sys_HeartRate_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_HeartRate_uni.str.protocol.sub_cmd[1] = 0x00;

	
	for(u8 i=0; i<9;i++)
	{
		sys_HeartRate_uni.str.data[i]=0x00;
	}

	
	sys_HeartRate_uni.str.checksum = GetCheckSum_Sum_Carry(sys_HeartRate_uni.Txbuffer,1,sys_HeartRate_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_HeartRate_uni.Txbuffer,sys_HeartRate_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	for(u8 i=0;i<sys_HeartRate_uni.str.protocol.data_length ;i++)
	{
		if(sys_HeartRate_uni.Txbuffer[i] == 0x00)
		{
			sys_HeartRate_uni.Txbuffer[i]=0xff;
			
		}
		
	}
	sys_printf("[%s]\n",sys_HeartRate_uni.Txbuffer);

#endif	
	
}
void sys_Body_Temp_Sensor(u8 Ackcmd)
{
	
	
	u16 body_temp_data=0;

	
	sys_BodyTemp_uni.str.protocol.head = STX;
	sys_BodyTemp_uni.str.protocol.data_length =0x07;
	sys_BodyTemp_uni.str.protocol.cmd= Ackcmd;
	sys_BodyTemp_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_BodyTemp_uni.str.protocol.sub_cmd[1] = 0x00;

	
  sys_BodyTemp_uni.str.data[1] = (body_temp_data >> 8) & 0x00ff;
	sys_BodyTemp_uni.str.data[0] = (body_temp_data ) & 0x00ff;
	
	
	sys_BodyTemp_uni.str.checksum = GetCheckSum_Sum_Carry(sys_BodyTemp_uni.Txbuffer,1,sys_BodyTemp_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_BodyTemp_uni.Txbuffer,sys_BodyTemp_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0

#endif	
	

}
void sys_Temp_Humi_Press(u8 Ackcmd)
{


	 u32 temp_data=0,press_data=0;
	u16 humi_data=0;
	Bme280_Cal_data_structure *pCal_data = &Bme280_Cal_data_str;
	
	sys_TempHumiPress_uni.str.protocol.head = STX;
	sys_TempHumiPress_uni.str.protocol.data_length =0x0d;
	sys_TempHumiPress_uni.str.protocol.cmd= Ackcmd;
	sys_TempHumiPress_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_TempHumiPress_uni.str.protocol.sub_cmd[1] = 0x00;

	sys_GetBME280_Force_Temp_Press_Hudi(&temp_data,&press_data,&humi_data);
		
	
	sys_TempHumiPress_uni.str.data[0] = (pCal_data->temp >>8 )& 0x000000ff;
	sys_TempHumiPress_uni.str.data[1] = (pCal_data->temp )& 0x000000ff;
	
	sys_TempHumiPress_uni.str.data[2] = (pCal_data->humi >>16 ) & 0x000000ff;

	sys_TempHumiPress_uni.str.data[3] = (pCal_data->humi >>8)& 0x000000ff;
	sys_TempHumiPress_uni.str.data[4] = (pCal_data->humi ) & 0x000000ff;
	
	sys_TempHumiPress_uni.str.data[5] = (pCal_data->press >>16) & 0x000000ff;
	sys_TempHumiPress_uni.str.data[6] = (pCal_data->press >>8) & 0x000000ff;
	sys_TempHumiPress_uni.str.data[7] = (pCal_data->press ) & 0x000000ff;
	

	
	
	sys_TempHumiPress_uni.str.checksum = GetCheckSum_Sum_Carry(sys_TempHumiPress_uni.Txbuffer,1,sys_TempHumiPress_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_TempHumiPress_uni.Txbuffer,sys_TempHumiPress_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >3
	sys_printf("[%s]\n",sys_TempHumiPress_uni.Txbuffer);

#endif	
	
	
	
	
}

void sys_Gas_Sensor(u8 Ackcmd)
{
		
	u16 gas_data;

	
	sys_Gas_uni.str.protocol.head = STX;
	sys_Gas_uni.str.protocol.data_length =0x07;
	sys_Gas_uni.str.protocol.cmd= Ackcmd;
	sys_Gas_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_Gas_uni.str.protocol.sub_cmd[1] = 0x00;
	
	
		
        sys_Gas_uni.str.data[1] = (gas_data >> 8) & 0x00ff;
	sys_Gas_uni.str.data[0] = (gas_data ) & 0x00ff;
	
	sys_Gas_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Gas_uni.Txbuffer,1,sys_Gas_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Gas_uni.Txbuffer,sys_Gas_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("[%s]\n",sys_Gas_uni.Txbuffer);

#endif	
	
}

void sys_Batt_Info(u8 Ackcmd)
{
	
	u16 batt_vol_data=0,batt_curr_data=0;
         bool stat=false;
	u8 cnt=0;
	sys_battery_struct *pBattery = &sys_battery_str;
	
	do
	{
		stat = sys_GetBatteryInfo(&batt_curr_data,&batt_vol_data);
		if(stat==true)
		{
			break;
		}
	}while(cnt++ > 3);
	
	sys_BattInfo_uni.str.protocol.head = STX;
	sys_BattInfo_uni.str.protocol.data_length =0x07;
	sys_BattInfo_uni.str.protocol.cmd= Ackcmd;
	
	sys_BattInfo_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_BattInfo_uni.str.protocol.sub_cmd[1] = pBattery->status;
	
	
		
        sys_BattInfo_uni.str.data[1] = (batt_vol_data >> 8) & 0x00ff;
	sys_BattInfo_uni.str.data[0] = (batt_vol_data ) & 0x00ff;
	
	sys_BattInfo_uni.str.checksum = GetCheckSum_Sum_Carry(sys_BattInfo_uni.Txbuffer,1,sys_BattInfo_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_BattInfo_uni.Txbuffer,sys_BattInfo_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("[%s]\n",sys_BattInfo_uni.Txbuffer);

#endif	
	
	
	
}
void sys_All_Sensor_Control(u8 Ackcmd)
{
	

         u8 sensor_status=0;
	
	sys_SensorStatus_uni.str.protocol.head = STX;
	sys_SensorStatus_uni.str.protocol.data_length =0x06;
	sys_SensorStatus_uni.str.protocol.cmd= Ackcmd;
	sys_SensorStatus_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_SensorStatus_uni.str.protocol.sub_cmd[1] = 0x00;
	
	
	sys_SensorStatus_uni.str.data = sensor_status ;	

	sys_SensorStatus_uni.str.checksum = GetCheckSum_Sum_Carry(sys_SensorStatus_uni.Txbuffer,1,sys_SensorStatus_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_SensorStatus_uni.Txbuffer,sys_SensorStatus_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("[%s]\n",sys_SensorStatus_uni.Txbuffer);

#endif	
	
	
	
	
}

void sys_Time_Get(u8 Ackcmd)
{
	

         u8 time_data[7];

	
	////////////////////////////
	sys_TimeGet_uni.str.protocol.head = STX;
	sys_TimeGet_uni.str.protocol.data_length =0x0c;
	sys_TimeGet_uni.str.protocol.cmd= Ackcmd;
	sys_TimeGet_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_TimeGet_uni.str.protocol.sub_cmd[1] = 0x00;
	
	for(u8 i=0; i<7;i++)
	{
		sys_TimeGet_uni.str.data[i] = time_data[i] ;	
	}
	sys_TimeGet_uni.str.checksum = GetCheckSum_Sum_Carry(sys_TimeGet_uni.Txbuffer,1,sys_TimeGet_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_TimeGet_uni.Txbuffer,sys_TimeGet_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("[%s]\n",sys_TimeGet_uni.Txbuffer);

#endif	
	
	
	
	
}

void sys_Time_Set(u8 Ackcmd)
{
		
	////////////////////////////
	sys_TimeSet_uni.str.protocol.head = STX;
	sys_TimeSet_uni.str.protocol.data_length =0x06;
	sys_TimeSet_uni.str.protocol.cmd= Ackcmd;
	sys_TimeSet_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_TimeSet_uni.str.protocol.sub_cmd[1] = 0x00;
	
	
	sys_TimeSet_uni.str.data = 0x00 ;	
	
	sys_TimeSet_uni.str.checksum = GetCheckSum_Sum_Carry(sys_TimeSet_uni.Txbuffer,1,sys_TimeSet_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_TimeSet_uni.Txbuffer,sys_TimeSet_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("[%s]\n",sys_TimeSet_uni.Txbuffer);

#endif	
	
	
	
	
}

void sys_Body_Temp_Range_Set(u8 Ackcmd)
{
	

         u8 BTRS_data[4];

	sys_BodyTempRange_uni.str.protocol.head = STX;
	sys_BodyTempRange_uni.str.protocol.data_length =0x09;
	sys_BodyTempRange_uni.str.protocol.cmd= Ackcmd;
	sys_BodyTempRange_uni.str.protocol.sub_cmd[0] = 0x00;
	sys_BodyTempRange_uni.str.protocol.sub_cmd[1] = 0x00;
	
	
	for(u8 i=0; i<4;i++)
	{
		sys_BodyTempRange_uni.str.data[i] = BTRS_data[i] ;	
	}
	
	
	sys_BodyTempRange_uni.str.checksum = GetCheckSum_Sum_Carry(sys_BodyTempRange_uni.Txbuffer,1,sys_BodyTempRange_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_BodyTempRange_uni.Txbuffer,sys_BodyTempRange_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("[%s]\n",sys_BodyTempRange_uni.Txbuffer);

#endif	
	
	
	
	
}
void sys_Eeprom_read(u8 Ackcmd)
{
	
	
}
void sys_Force_Sensor_Range_Set(u8 Ackcmd)
{
	
         sys_BleRxStruct *pBleRx = &sys_BleRx_str;
         u8 force_data[2];
/*   data 획득  */
	if(pBleRx->Ble_SubCmd[0])    // data read
	{
		
		
	}else                                      // data save
	{
		
		
		
		
	}
		
	////////////////////////////
	sys_ForceLevelSet_uni.str.protocol.head = STX;
	sys_ForceLevelSet_uni.str.protocol.data_length =0x07;
	sys_ForceLevelSet_uni.str.protocol.cmd= Ackcmd;
	sys_ForceLevelSet_uni.str.protocol.sub_cmd[0] = pBleRx->Ble_SubCmd[0];
	sys_ForceLevelSet_uni.str.protocol.sub_cmd[1] = pBleRx->Ble_SubCmd[1];
	
	
	for(u8 i=0; i<2;i++)
	{
		sys_ForceLevelSet_uni.str.data[i] = force_data[i] ;	
	}
	
	
	sys_ForceLevelSet_uni.str.checksum = GetCheckSum_Sum_Carry(sys_ForceLevelSet_uni.Txbuffer,1,sys_ForceLevelSet_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_ForceLevelSet_uni.Txbuffer,sys_ForceLevelSet_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("[%s]\n",sys_ForceLevelSet_uni.Txbuffer);

#endif	
	
	
	
	
}

void sys_Body_Temp_Set(u8 Ackcmd)
{
	
         sys_BleRxStruct *pBleRx = &sys_BleRx_str;
    
	sys_Temp_Time_struct *pTempTimer = &sys_Temp_Time_str;
	
	////////////////////////////
	sys_Body_Temp_Set_uni.str.protocol.head = STX;
	sys_Body_Temp_Set_uni.str.protocol.data_length =0x0e;
	sys_Body_Temp_Set_uni.str.protocol.cmd= Ackcmd;
	sys_Body_Temp_Set_uni.str.protocol.sub_cmd[0] = pBleRx->Ble_SubCmd[0];
	sys_Body_Temp_Set_uni.str.protocol.sub_cmd[1] = pBleRx->Ble_SubCmd[1];
	
	
	
	sys_Body_Temp_Set_uni.str.time_period = pTempTimer->time_period = sys_ble_rx_buf[5];
	sys_Body_Temp_Set_uni.str.normal_temp = pTempTimer->normal_temp = ((sys_ble_rx_buf[6] << 8) &0xff00) |(sys_ble_rx_buf[7] &0x00ff );
        sys_Body_Temp_Set_uni.str.check_range =  pTempTimer->check_range = ((sys_ble_rx_buf[8] << 8) &0xff00) |(sys_ble_rx_buf[9] &0x00ff );
	sys_Body_Temp_Set_uni.str.measure_min = pTempTimer->measure_min = ((sys_ble_rx_buf[10] << 8) &0xff00) |(sys_ble_rx_buf[11] &0x00ff );
	sys_Body_Temp_Set_uni.str.measure_max = pTempTimer->measure_max = ((sys_ble_rx_buf[12] << 8) &0xff00) |(sys_ble_rx_buf[13] &0x00ff );
	
	sys_Body_Temp_Set_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Body_Temp_Set_uni.Txbuffer,1,sys_Body_Temp_Set_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Body_Temp_Set_uni.Txbuffer,sys_Body_Temp_Set_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("time period set[%d][%d][%d][%d][%d]\n",pTempTimer->time_period,pTempTimer->normal_temp,
												pTempTimer->check_range,pTempTimer->measure_min,pTempTimer->measure_max);

#endif	
	
	
	
	
}


void sys_Get_Body_Temp_Calcu(u8 Ackcmd)
{
	
         sys_BleRxStruct *pBleRx = &sys_BleRx_str;
        
         u16 body_temp_calu=0;
	
	nrf_delay_ms(500);
	
//	body_temp = body_temp_calu=sys_Get_Body_Temp_Calculate();
	
	
	
	////////////////////////////
	sys_Body_Temp_calu_uni.str.protocol.head = STX;
	sys_Body_Temp_calu_uni.str.protocol.data_length =0x07;
	sys_Body_Temp_calu_uni.str.protocol.cmd= Ackcmd;
	sys_Body_Temp_calu_uni.str.protocol.sub_cmd[0] = pBleRx->Ble_SubCmd[0];
	sys_Body_Temp_calu_uni.str.protocol.sub_cmd[1] = pBleRx->Ble_SubCmd[1];
	
	sys_Body_Temp_calu_uni.str.data[1] = (body_temp_calu >> 8) & 0x00ff;
	sys_Body_Temp_calu_uni.str.data[0] = (body_temp_calu ) & 0x00ff;
	

	
	sys_Body_Temp_calu_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Body_Temp_calu_uni.Txbuffer,1,sys_Body_Temp_calu_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Body_Temp_calu_uni.Txbuffer,sys_Body_Temp_calu_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("Ble_Body_Temp[%d]\n",body_temp);

#endif	
	
	
	
	
}


void sys_Get_Dust_sensor(u8 Ackcmd)
{
	
         sys_BleRxStruct *pBleRx = &sys_BleRx_str;
        sys_DustSensor_structure *pDustSensor = &sys_DustSensor_str;
         float dust_data=0;
	 u16  tx_data=0;
	
//	nrf_delay_ms(500);
	
//	body_temp = body_temp_calu=sys_Get_Body_Temp_Calculate();
	
	dust_data = sys_GetDustSensorValue();

	pDustSensor->dust_sensor_data = tx_data = dust_data *1024;	
		//20151005:dalsoo				pDustSensor->dust_sensor_data = tx_data = dust_data *1000;
	
	////////////////////////////
	sys_Dust_Sensor_uni.str.protocol.head = STX;
	sys_Dust_Sensor_uni.str.protocol.data_length =0x07;
	sys_Dust_Sensor_uni.str.protocol.cmd= Ackcmd;
	sys_Dust_Sensor_uni.str.protocol.sub_cmd[0] = pBleRx->Ble_SubCmd[0];
	sys_Dust_Sensor_uni.str.protocol.sub_cmd[1] = pBleRx->Ble_SubCmd[1];
	
	
	sys_Dust_Sensor_uni.str.data[1] = (u8)((tx_data >> 8) & 0x00ff);
	sys_Dust_Sensor_uni.str.data[0] = (tx_data ) & 0x00ff;
	
	sys_printf("Dust data [%f][%d] \n\r",dust_data,tx_data);
	
	sys_Dust_Sensor_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Dust_Sensor_uni.Txbuffer,1,sys_Dust_Sensor_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Dust_Sensor_uni.Txbuffer,sys_Dust_Sensor_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("Dust sensor[%f]\n",pDustSensor->dust_sensor_data);

#endif	
	
	
	
	
}
void sys_Get_Co2_Sensor(u8 Ackcmd)
{
	
         sys_BleRxStruct *pBleRx = &sys_BleRx_str;
        
         u16 co2_data=0,Tvoc_data=0;
	 u8 Co2_sensor_stat=0;
//	nrf_delay_ms(500);
	
//	body_temp = body_temp_calu=sys_Get_Body_Temp_Calculate();
	
	Co2_sensor_stat = sys_GetiAQSensor_Data(&co2_data,&Tvoc_data);
	
	////////////////////////////
	sys_Co2_Tvoc_uni.str.protocol.head = STX;
	sys_Co2_Tvoc_uni.str.protocol.data_length =0x09;
	sys_Co2_Tvoc_uni.str.protocol.cmd= Ackcmd;
	sys_Co2_Tvoc_uni.str.protocol.sub_cmd[0] = pBleRx->Ble_SubCmd[0];
	sys_Co2_Tvoc_uni.str.protocol.sub_cmd[1] = pBleRx->Ble_SubCmd[1];
	
	sys_Co2_Tvoc_uni.str.data[1] = (co2_data >> 8) & 0x00ff;
	sys_Co2_Tvoc_uni.str.data[0] = (co2_data ) & 0x00ff;
	sys_Co2_Tvoc_uni.str.data[3] = (Tvoc_data >> 8) & 0x00ff;
	sys_Co2_Tvoc_uni.str.data[2] = (Tvoc_data ) & 0x00ff;

	
	sys_Co2_Tvoc_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Co2_Tvoc_uni.Txbuffer,1,sys_Co2_Tvoc_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Co2_Tvoc_uni.Txbuffer,sys_Co2_Tvoc_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("stat[0x%x] sys_Get_Co2_Sensor[%d][%d]\n",Co2_sensor_stat,co2_data,Tvoc_data);

#endif	
	
	
	
	
}
void sys_ION_ON_OFF(u8 Ackcmd)
{
	
         sys_BleRxStruct *pBleRx = &sys_BleRx_str;
        
//         u16 dust_data=0;
	

	
	////////////////////////////
	sys_ION_On_Off_uni.str.protocol.head = STX;
	sys_ION_On_Off_uni.str.protocol.data_length =0x06;
	sys_ION_On_Off_uni.str.protocol.cmd= Ackcmd;
	sys_ION_On_Off_uni.str.protocol.sub_cmd[0] = pBleRx->Ble_SubCmd[0];
	sys_ION_On_Off_uni.str.protocol.sub_cmd[1] = pBleRx->Ble_SubCmd[1];
	
        if(sys_ION_On_Off_uni.str.protocol.sub_cmd[0] == 0x01)
	{
		sys_Ion_on_off(true);
		//ION_OUT_ON() ;
	}else  if(sys_ION_On_Off_uni.str.protocol.sub_cmd[0] == 0x00)
	{
		sys_Ion_on_off(false);
		//ION_OUT_OFF() ;
	}
	sys_ION_On_Off_uni.str.data = 0;
	

	
	sys_ION_On_Off_uni.str.checksum = GetCheckSum_Sum_Carry(sys_ION_On_Off_uni.Txbuffer,1,sys_ION_On_Off_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_ION_On_Off_uni.Txbuffer,sys_ION_On_Off_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("sys_ION_ON[%d]\n",sys_ION_On_Off_uni.str.protocol.sub_cmd[0]);

#endif	
	
	
	
	
}

void sys_Dust_Value_set(u8 Ackcmd)
{

         sys_BleRxStruct *pBleRx = &sys_BleRx_str;
         sys_Dust_value_structure 	*pDustValue = &sys_Dust_value_str;
//         u16 dust_data=0;
	

	
	////////////////////////////
	sys_Dust_Value_Set_uni.str.protocol.head = STX;
	sys_Dust_Value_Set_uni.str.protocol.data_length =0x09;
	sys_Dust_Value_Set_uni.str.protocol.cmd= Ackcmd;
	sys_Dust_Value_Set_uni.str.protocol.sub_cmd[0] = pBleRx->Ble_SubCmd[0];
	sys_Dust_Value_Set_uni.str.protocol.sub_cmd[1] = pBleRx->Ble_SubCmd[1];
	

	sys_Dust_Value_Set_uni.str.excellent = pDustValue->execellent = sys_ble_rx_buf[5];
	sys_Dust_Value_Set_uni.str.fair = pDustValue->fair = sys_ble_rx_buf[6];
	sys_Dust_Value_Set_uni.str.mediocre = pDustValue->mediocre = sys_ble_rx_buf[7];
	sys_Dust_Value_Set_uni.str.bad = pDustValue->bad = sys_ble_rx_buf[8];
	

	
	sys_Dust_Value_Set_uni.str.checksum = GetCheckSum_Sum_Carry(sys_Dust_Value_Set_uni.Txbuffer,1,sys_Dust_Value_Set_uni.str.protocol.data_length-1);
	
	ble_nus_send_string(&m_nus, sys_Dust_Value_Set_uni.Txbuffer,sys_Dust_Value_Set_uni.str.protocol.data_length + 1); 
	
#if _SYS_DEBUG >0
	sys_printf("excell[%d],fair[%d]medi[%d],bad[%d]\n", pDustValue->execellent, pDustValue->fair, pDustValue->mediocre, pDustValue->bad);

#endif	
	
}

void sys_ble_process(void)
{
     	 sys_BleRxStruct *pBleRx = &sys_BleRx_str;
	     u8 cs=0;
	
	if(pBleRx->BleRxEndFlag)
	{
		
		pBleRx->BleRxEndFlag = false;
		if(sys_ble_rx_buf[0] == STX)
		{
			pBleRx->BleRxStxFlag=true;

			cs = GetCheckSum_Sum_Carry(sys_ble_rx_buf,1,(sys_ble_rx_buf[1]-1));
			
			//sys_printf("cs =%x tx_cs = %x\n",cs,sys_ble_rx_buf[sys_ble_rx_buf[1]]);
			if(cs == sys_ble_rx_buf[sys_ble_rx_buf[1]])
			{

				pBleRx->BleRxCompleteFlag = true;
				pBleRx->BleRxNackFlag = false;
				
				pBleRx->Ble_Cmd = sys_ble_rx_buf[2];
				pBleRx->Ble_SubCmd[0] = sys_ble_rx_buf[3];
				pBleRx->Ble_SubCmd[1] = sys_ble_rx_buf[4];

			}else
			{
			
				pBleRx->BleRxNackFlag = true;    // checksum not match
				pBleRx->BleRxStxFlag=false;
				pBleRx->BleRxCompleteFlag = false;
			}


		}else
		{
			
				pBleRx->BleRxCompleteFlag  = false;
				pBleRx->BleRxStxFlag =false;
				pBleRx->BleRxNackFlag=false;
#if  _SYS_DEBUG > 2 
			sys_printf("%c\n\r",sys_ble_rx_buf[0]);
			switch(sys_ble_rx_buf[0])
			{
			
				case 'a':
				case 'A':
					sys_Ble_Model(pBleRx->Ble_Cmd);

				break;
				
				case 'b':
				case 'B':
					sys_Heart_Rate_Sensor(pBleRx->Ble_Cmd);

				break;
				
				case 'c':
				case 'C':
					sys_Body_Temp_Sensor(pBleRx->Ble_Cmd);

				break;
				
				case 'd':
				case 'D':
					sys_Froce_Sensor_check(pBleRx->Ble_Cmd);

				break;
				
				
				
			}
	
#endif			


		} 



	}else
	{
	/* Empty */
	}
        if(pBleRx->BleRxNackFlag)
	{
			sys_printf("1\n\r");
		pBleRx->BleRxCompleteFlag  = false;
		pBleRx->BleRxStxFlag =false;
		pBleRx->BleRxNackFlag=false;
		sys_Bt_Nack_Cmd(sys_ble_rx_buf[2]);
		
	}
	else if(pBleRx->BleRxStxFlag && pBleRx->BleRxCompleteFlag)
	{
		pBleRx->BleRxCompleteFlag  = false;
		pBleRx->BleRxStxFlag =false;
		
                switch(pBleRx->Ble_Cmd )
		{
			case HEART:                     // 심장 박동수, 산소포화도
		        sys_Heart_Rate_Sensor(pBleRx->Ble_Cmd);
			break;
			case BODY_TEMP:
				sys_Body_Temp_Sensor(pBleRx->Ble_Cmd);
			
			break;
			case TEMP_HUMI_PRESS:
				sys_Temp_Humi_Press(pBleRx->Ble_Cmd);
			
			break;
			case FORCE_SENSOR:
				sys_Froce_Sensor_check(pBleRx->Ble_Cmd);
			
			break;
			case GAS_SENSOR:
				sys_Gas_Sensor(pBleRx->Ble_Cmd);
			
			break;
			case BATT_INFO:
				sys_Batt_Info(pBleRx->Ble_Cmd);
			
			break;
			case ALL_SENSOR_CTL:
				sys_All_Sensor_Control(pBleRx->Ble_Cmd);
			
			break;
			case TIME_GET:
				sys_Time_Get(pBleRx->Ble_Cmd);
			
			break;
			case TIME_SET:
				sys_Time_Set(pBleRx->Ble_Cmd);
			
			break;
			case BODY_TEMP_RANGE:
				sys_Body_Temp_Range_Set(pBleRx->Ble_Cmd);
			
			break;
			case EEPROM_READ:
				sys_Eeprom_read(pBleRx->Ble_Cmd);
			
			break;
			case FORCE_SENSOR_RANGE:
			        sys_Force_Sensor_Range_Set(pBleRx->Ble_Cmd);
			
			break;
			case BODY_TEMP_SET:
				sys_Body_Temp_Set(pBleRx->Ble_Cmd);
			
			break;
			case BODY_TEMP_CALCU:
				sys_Get_Body_Temp_Calcu(pBleRx->Ble_Cmd);
			
			break;
			case DUST_SENSOR_VALUE:
				sys_Get_Dust_sensor(pBleRx->Ble_Cmd);
			
			break;
			case CO2_TVOC_SENSOR_VAL:
				sys_Get_Co2_Sensor(pBleRx->Ble_Cmd);
			
			break;
			case ION_ON_OFF:
				sys_ION_ON_OFF(pBleRx->Ble_Cmd);
			
			break;
			case DUST_VALUE_SET:
								sys_Dust_Value_set(pBleRx->Ble_Cmd);
			break;
			
			case MODEL_NAME:
				sys_Ble_Model(pBleRx->Ble_Cmd);
			break;
			case VERSION_INFO:
				sys_Ble_Version(pBleRx->Ble_Cmd);
			
			break;

			default :
				
			
			break;
			
		}




	}
}

