/*******************************************************************************
* File Name          : sys_TempHumiPress.c
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.4.06
* Description        :  Temperature, Hudimity , Pressure Sensor (BME280)
*******************************************************************************/

#include "sys_main.h"

//static struct bme280_t *p_bme280; /**< pointer to BME280 */

Bme280_Cal_data_structure Bme280_Cal_data_str;
void bme280_get_calib_param(void);

s32 bme280_compensate_temperature_int32(s32 v_uncomp_temperature_s32);
u32 bme280_compensate_humidity_int32(s32 v_uncomp_humidity_s32);
u32 bme280_compensate_pressure_int32(s32 v_uncomp_pressure_s32);

u8 sys_GetBME280_ID(void)
{
	u8 id =0;
//			u16 temp =0;
//	u8 temp1=0,temp2=0,crc=0,crc_check=0;
	u8 reg=THP_ID_READ;
	
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,&id,1,TWI_ISSUE_STOP);
	
#if _SYS_DEBUG  > 3
	
	sys_printf("BME280 ID[0x%x]\n\r",id);
	
#endif

	return id;
}


u16 sys_GetBME280_Humi(void)
{
	u16 returnHumi =0;
	//u8 temp1=0,temp2=0;
	u8 data_buf[2];
	u8 reg=0;

	reg = THP_HUM_MSB;
	
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,data_buf,2,TWI_ISSUE_STOP);


	returnHumi = ((data_buf[0] << 8)& 0xff00 ) | (data_buf[1] & 0x00ff);

#if _SYS_DEBUG  > 0
	
	sys_printf("BME280 Humi[0x%x][%x][%x]\n\r",returnHumi,data_buf[0],data_buf[1]);
	
#endif
	return returnHumi;
	
}

u32 sys_GetBME280_Temp(void)
{
	
	u32 returnTemp =0;
	//u8 temp1=0,temp2=0,temp3=0;
	u8 data_buf[3];
	u8 reg=0;

	reg = THP_TEMP_MSB;
	
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,data_buf,3,TWI_ISSUE_STOP);
	


	returnTemp = ((data_buf[0] << 12)& 0x000ff000 ) | ((data_buf[1]  << 4)& 0x00000ff0) | ((data_buf[2]  >>4) & 0x0f);
	
#if _SYS_DEBUG  > 0
	
	sys_printf("BME280 Temp[0x%x][%x][%x][%x]\n\r",returnTemp,data_buf[0] ,data_buf[1] ,data_buf[2]);
	
#endif

	return returnTemp;
	
	
}

u32 sys_GetBME280_Press(void)
{
	u32 returnPress =0;
	
	u8 data_buf[3];
	u8 reg=0;

	reg = THP_PRESS_MSB;
	
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,data_buf,3,TWI_ISSUE_STOP);
	
	

	returnPress = ((data_buf[0] << 12)& 0x000ff000 ) | ((data_buf[1]  << 4)& 0x00000ff0) | ((data_buf[2]  >>4) & 0x0f);
	
#if _SYS_DEBUG  > 0
	
	sys_printf("BME280 Press[0x%x][%x][%x][%x]\n\r",returnPress,data_buf[0],data_buf[1],data_buf[2]);
	
#endif

	return returnPress;
	
	
}

void sys_BME280_Ctrl_Meas(void)
{
		u8 temp=0;	
	
	
	u8 data_buf[2];
	u8 reg=0;

	data_buf[0] = THP_CTRL_MEAS;
	data_buf[1] = (THP_TEMP_OVERSAMPLE_4|THP_PRESSURE_OVERSAMPLE_2|THP_NORMAL_MODE);
	
	twi_master_transfer(THP_WR_ADD,data_buf,2,TWI_ISSUE_STOP);
	
	
/*****   read  ***********/
	
	reg=THP_CTRL_MEAS;
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);

	twi_master_transfer(THP_RD_ADD,&temp,1,TWI_ISSUE_STOP);
	
	sys_printf("CTRL_MEAS [0x%x]\n",temp);
	
}
void sys_BME280_Config(void)
{
	
		u8 temp=0;	
	
	
	u8 data_buf[2];
	u8 reg=0;

	data_buf[0] = THP_CONFIG;
	data_buf[1] = (THP_T_STANDBY_005|THP_FILTER_OFF);
	
	twi_master_transfer(THP_WR_ADD,data_buf,2,TWI_ISSUE_STOP);
	
	
/*****   read  ***********/
	
	reg=THP_CONFIG;
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);

	twi_master_transfer(THP_RD_ADD,&temp,1,TWI_ISSUE_STOP);
	

	sys_printf("config [0x%x]\n",temp);
	
	
}

void sys_BME280_hum(void)
{
	
		u8 temp=0;	
	
	
	u8 data_buf[2];
	u8 reg=0;

	data_buf[0] = THP_CTRL_HUM;
	data_buf[1] = THP_HUMI_OVERSAMPLE_4;
	
	twi_master_transfer(THP_WR_ADD,data_buf,2,TWI_ISSUE_STOP);
	
	
/*****   read  ***********/
	
	reg=THP_CTRL_HUM;
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);

	twi_master_transfer(THP_RD_ADD,&temp,1,TWI_ISSUE_STOP);
	
	sys_printf("ctrol hum [0x%x]\n",temp);
	
}

u8 sys_GetBME280_Temp_Press_Hudi(u32 *temp_data,u32 *press_data, u16 *humi_data)
{
	u32 returnPress =0;
	//u8 temp1=0,temp2=0,temp3=0;
	u8 status=0;
	u8 data_buf[8];
	u8 reg=0;

	reg = THP_STATUS;
/****   status read  ****/	
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,&status,1,TWI_ISSUE_STOP);
#if _SYS_DEBUG  > 0
	
		sys_printf("status[0x%x]\n",status);
#endif
	
	/**** data read ****/
		reg = THP_PRESS_MSB;
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,data_buf,8,TWI_ISSUE_STOP);
	/****   status read  ****/	
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,&status,1,TWI_ISSUE_STOP);
#if _SYS_DEBUG  > 0
	
		sys_printf("After status[0x%x]\n",status);
#endif
	

	*press_data = ((data_buf[0] << 12)& 0x000ff000 ) | ((data_buf[1]  << 4)& 0x00000ff0) | ((data_buf[2]  >>4) & 0x0f);
	*temp_data = ((data_buf[3] << 12)& 0x000ff000 ) | ((data_buf[4]  << 4)& 0x00000ff0) | ((data_buf[5]  >>4) & 0x0f);
	*humi_data = ((data_buf[6] << 8)& 0xff00 ) | (data_buf[7] & 0x00ff);
	
	
	
#if _SYS_DEBUG  > 0
	
		sys_printf("__Temp[0x%x],press[0x%x],humi[0x%x]\n",*temp_data,*press_data ,*humi_data);
#endif

	return returnPress;
	
}
void sys_BME280_sleep(void)
{
		u8 temp=0;	
	
	
	u8 data_buf[2];
	u8 reg=0;

	data_buf[0] = THP_CTRL_MEAS;
	data_buf[1] = (THP_TEMP_OVERSAMPLE_4|THP_PRESSURE_OVERSAMPLE_2|THP_SLEEP_MODE);
	
	twi_master_transfer(THP_WR_ADD,data_buf,2,TWI_ISSUE_STOP);
	
	
/*****   read  ***********/
	
	reg=THP_CTRL_MEAS;
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);

	twi_master_transfer(THP_RD_ADD,&temp,1,TWI_ISSUE_STOP);
	

	sys_printf("CTRL_MEAS [0x%x]\n",temp);
	
	
}
void sys_BME280_force(void)
{
//		u8 temp=0;	
	
	
	u8 data_buf[2];
//	u8 reg=0;

	data_buf[0] = THP_CTRL_MEAS;
	data_buf[1] = (THP_TEMP_OVERSAMPLE_4|THP_PRESSURE_OVERSAMPLE_2|THP_FORCE_MODE);
	
	twi_master_transfer(THP_WR_ADD,data_buf,2,TWI_ISSUE_STOP);
	

	
	
}

u8 sys_GetBME280_Force_Temp_Press_Hudi(u32 *temp_data,u32 *press_data, u16 *humi_data)
{
	u32 returnPress =0;
	//u8 temp1=0,temp2=0,temp3=0;
	u8 status=0;
	u8 data_buf[8];
	u8 reg=0;
	u8 loop_cnt=0;
	
	Bme280_Cal_data_structure *pCal_data = &Bme280_Cal_data_str;
	
	reg = THP_STATUS;


	
	sys_BME280_force();
	loop: 
/****   status read  ****/	
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,&status,1,TWI_ISSUE_STOP);
#if _SYS_DEBUG  > 0
	
		sys_printf("status[0x%x]\n",status);
#endif
	  if((status & 0x08))
	  {
		//  sys_printf("11111\n");
	  }else
	  {
		  sys_printf("loop\n");
		  loop_cnt++;
		  
		  if(loop_cnt >3)
			 return 0;
		  goto loop;
		  
	  }
	/**** data read ****/
		reg = THP_PRESS_MSB;
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,data_buf,8,TWI_ISSUE_STOP);
	/****   status read  ****/	
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,&status,1,TWI_ISSUE_STOP);
#if _SYS_DEBUG  > 2
	
		sys_printf("After status[0x%x]\n",status);
#endif

	*press_data = ((data_buf[0] << 12)& 0x000ff000 ) | ((data_buf[1]  << 4)& 0x00000ff0) | ((data_buf[2]  >>4) & 0x0f);
	*temp_data = ((data_buf[3] << 12)& 0x000ff000 ) | ((data_buf[4]  << 4)& 0x00000ff0) | ((data_buf[5]  >>4) & 0x0f);
	*humi_data = ((data_buf[6] << 8)& 0xff00 ) | (data_buf[7] & 0x00ff);
	
	pCal_data->temp = bme280_compensate_temperature_int32(*temp_data);
	pCal_data->press = bme280_compensate_pressure_int32(*press_data);
	pCal_data->humi = bme280_compensate_humidity_int32(*humi_data);
	
	//	returnPress = ((temp1 << 12)& 0x000ff000 ) | ((temp2 << 4)& 0x00000ff0) | ((temp3 >>4) & 0x0f);
	
#if _SYS_DEBUG  > 0
	sys_printf("Temp[0x%x],press[0x%x],humi[0x%x]\n",*temp_data,*press_data ,*humi_data);
	sys_printf("temp =[%d],press[%d],humi[%d]\n\r",pCal_data->temp,pCal_data->press,pCal_data->humi);

		
#endif

	return returnPress;
		
	
	
}

void sys_BME280_init(void)
{
	u8 id=0;
	id= sys_GetBME280_ID();
		

	sys_BME280_Config();
	nrf_delay_ms(1);
	sys_BME280_hum();
	nrf_delay_ms(1);
	sys_BME280_Ctrl_Meas();

	bme280_get_calib_param();
	
	sys_BME280_sleep();
#if _SYS_DEBUG  > 0
	if(id == BME_280_ID)	
		sys_printf("BME280 ID intiial[0x%x]\n\r",id);
	else
		sys_printf("BME280 ID No intiial[0x%x]\n\r",id);
	
#endif
	
}

void bme280_get_calib_param(void)
{
//	u8 a_data_u8[25];
	u8 reg=0;
	// bme280_calibration_struct *pCal_data = &Bme280_cal_data_str;
	Bme280_Cal_data_structure *pCal_data = &Bme280_Cal_data_str;

	
			/* used to return the communication result*/
//	BME280_RETURN_FUNCTION_TYPE com_rslt = ERROR;
	u8 a_data_u8[26] = {0,};
//	 u16 teset=0;
	
			/**** data read ****/
	reg = BME280_TEMPERATURE_CALIB_DIG_T1_LSB_REG;
	twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
	twi_master_transfer(THP_RD_ADD,a_data_u8,25,TWI_ISSUE_STOP);
	
	
	
	pCal_data->dig_T1 = (u16)((((u16)((u8)a_data_u8[BME280_TEMPERATURE_CALIB_DIG_T1_MSB])) <<	BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_TEMPERATURE_CALIB_DIG_T1_LSB]);

	
			pCal_data->dig_T2 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_TEMPERATURE_CALIB_DIG_T2_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_TEMPERATURE_CALIB_DIG_T2_LSB]);
	
			pCal_data->dig_T3 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_TEMPERATURE_CALIB_DIG_T3_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_TEMPERATURE_CALIB_DIG_T3_LSB]);
			
			 sys_printf("get T1 \n\r");
			
			pCal_data->dig_P1 = (u16)(((
			(u16)((u8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P1_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_PRESSURE_CALIB_DIG_P1_LSB]);
			
			pCal_data->dig_P2 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P2_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_PRESSURE_CALIB_DIG_P2_LSB]);
			
			pCal_data->dig_P3 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P3_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P3_LSB]);
			
			pCal_data->dig_P4 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P4_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_PRESSURE_CALIB_DIG_P4_LSB]);
			
			pCal_data->dig_P5 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P5_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_PRESSURE_CALIB_DIG_P5_LSB]);
			
			pCal_data->dig_P6 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P6_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_PRESSURE_CALIB_DIG_P6_LSB]);
			
			pCal_data->dig_P7 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P7_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_PRESSURE_CALIB_DIG_P7_LSB]);
			pCal_data->dig_P8 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P8_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_PRESSURE_CALIB_DIG_P8_LSB]);
			pCal_data->dig_P9 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_PRESSURE_CALIB_DIG_P9_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_PRESSURE_CALIB_DIG_P9_LSB]);
			
	
			
			pCal_data->dig_H1 =a_data_u8[BME280_HUMIDITY_CALIB_DIG_H1];

			/**** data read ****/
			reg = BME280_HUMIDITY_CALIB_DIG_H2_LSB_REG;
			twi_master_transfer(THP_WR_ADD,&reg,1,TWI_DONT_ISSUE_STOP);
			twi_master_transfer(THP_RD_ADD,a_data_u8,8,TWI_ISSUE_STOP);


			sys_printf("get cal 3 \n\r");
			pCal_data->dig_H2 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_HUMIDITY_CALIB_DIG_H2_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_08_BITS)
			| a_data_u8[BME280_HUMIDITY_CALIB_DIG_H2_LSB]);
			
			pCal_data->dig_H3 =
			a_data_u8[BME280_HUMIDITY_CALIB_DIG_H3];
			
			pCal_data->dig_H4 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_HUMIDITY_CALIB_DIG_H4_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_04_BITS) |
			(((u8)BME280_MASK_DIG_H4) &
			a_data_u8[BME280_HUMIDITY_CALIB_DIG_H4_LSB]));
			
			pCal_data->dig_H5 = (s16)(((
			(s16)((s8)a_data_u8[
			BME280_HUMIDITY_CALIB_DIG_H5_MSB])) <<
			BME280_SHIFT_BIT_POSITION_BY_04_BITS) |
			(a_data_u8[BME280_HUMIDITY_CALIB_DIG_H4_LSB] >>
			BME280_SHIFT_BIT_POSITION_BY_04_BITS));
			
			pCal_data->dig_H6 =
			(s8)a_data_u8[BME280_HUMIDITY_CALIB_DIG_H6];
			
			
			
			sys_printf("dig T[%d][%d][%d]\n",pCal_data->dig_T1,pCal_data->dig_T2,pCal_data->dig_T3);
			sys_printf("dig P[%d][%d][%d][%d][%d][%d][%d][%d][%d]\n",pCal_data->dig_P1,pCal_data->dig_P2,pCal_data->dig_P3,
						pCal_data->dig_P4,pCal_data->dig_P5,pCal_data->dig_P6,pCal_data->dig_P7,pCal_data->dig_P8,pCal_data->dig_P9);
			
			sys_printf("dig H[%d][%d][%d][%d][%d][%d]\n",pCal_data->dig_H1,pCal_data->dig_H2,pCal_data->dig_H3,pCal_data->dig_H4,pCal_data->dig_H5,pCal_data->dig_H6);
				
}


// Returns temperature in DegC, resolution is 0.01 DegC. Output value of ¡°5123¡± equals 51.23 DegC.
// t_fine carries fine temperature as global value

s32 bme280_compensate_temperature_int32(s32 v_uncomp_temperature_s32)
{
	Bme280_Cal_data_structure *pCal_data = &Bme280_Cal_data_str;
	
	s32 v_x1_u32r = BME280_INIT_VALUE;
	s32 v_x2_u32r = BME280_INIT_VALUE;
	s32 temperature = BME280_INIT_VALUE;

	/* calculate x1*/
	v_x1_u32r  =
	((((v_uncomp_temperature_s32
	>> BME280_SHIFT_BIT_POSITION_BY_03_BITS) -
	((s32)pCal_data->dig_T1
	<< BME280_SHIFT_BIT_POSITION_BY_01_BIT))) *
	((s32)pCal_data->dig_T2)) >>
	BME280_SHIFT_BIT_POSITION_BY_11_BITS;
	/* calculate x2*/
	v_x2_u32r  = (((((v_uncomp_temperature_s32
	>> BME280_SHIFT_BIT_POSITION_BY_04_BITS) -
	((s32)pCal_data->dig_T1))
	* ((v_uncomp_temperature_s32 >> BME280_SHIFT_BIT_POSITION_BY_04_BITS) -
	((s32)pCal_data->dig_T1)))
	>> BME280_SHIFT_BIT_POSITION_BY_12_BITS) *
	((s32)pCal_data->dig_T3))
	>> BME280_SHIFT_BIT_POSITION_BY_14_BITS;
	/* calculate t_fine*/
	pCal_data->t_fine = v_x1_u32r + v_x2_u32r;
	/* calculate temperature*/
	temperature  = (pCal_data->t_fine * 5 + 128)
	>> BME280_SHIFT_BIT_POSITION_BY_08_BITS;
	
	sys_printf("temp = %d\n\r",temperature);
	return temperature;
}
// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of ¡°24674867¡± represents 24674867/256 = 96386.2 Pa = 963.862 hPa
u32 bme280_compensate_pressure_int32(s32 v_uncomp_pressure_s32)
{
	Bme280_Cal_data_structure *pCal_data = &Bme280_Cal_data_str;
	s32 v_x1_u32 = BME280_INIT_VALUE;
	s32 v_x2_u32 = BME280_INIT_VALUE;
	u32 v_pressure_u32 = BME280_INIT_VALUE;

	/* calculate x1*/
	v_x1_u32 = (((s32)pCal_data->t_fine)
	>> BME280_SHIFT_BIT_POSITION_BY_01_BIT) - (s32)64000;
	/* calculate x2*/
	v_x2_u32 = (((v_x1_u32 >> BME280_SHIFT_BIT_POSITION_BY_02_BITS)
	* (v_x1_u32 >> BME280_SHIFT_BIT_POSITION_BY_02_BITS)
	) >> BME280_SHIFT_BIT_POSITION_BY_11_BITS)
	* ((s32)pCal_data->dig_P6);
	/* calculate x2*/
	v_x2_u32 = v_x2_u32 + ((v_x1_u32 *
	((s32)pCal_data->dig_P5))
	<< BME280_SHIFT_BIT_POSITION_BY_01_BIT);
	/* calculate x2*/
	v_x2_u32 = (v_x2_u32 >> BME280_SHIFT_BIT_POSITION_BY_02_BITS) +
	(((s32)pCal_data->dig_P4)
	<< BME280_SHIFT_BIT_POSITION_BY_16_BITS);
	/* calculate x1*/
	v_x1_u32 = (((pCal_data->dig_P3 *
	(((v_x1_u32 >> BME280_SHIFT_BIT_POSITION_BY_02_BITS) *
	(v_x1_u32 >> BME280_SHIFT_BIT_POSITION_BY_02_BITS))
	>> BME280_SHIFT_BIT_POSITION_BY_13_BITS))
	>> BME280_SHIFT_BIT_POSITION_BY_03_BITS) +
	((((s32)pCal_data->dig_P2) *
	v_x1_u32) >> BME280_SHIFT_BIT_POSITION_BY_01_BIT))
	>> BME280_SHIFT_BIT_POSITION_BY_18_BITS;
	/* calculate x1*/
	v_x1_u32 = ((((32768 + v_x1_u32)) *
	((s32)pCal_data->dig_P1))
	>> BME280_SHIFT_BIT_POSITION_BY_15_BITS);
	/* calculate pressure*/
	v_pressure_u32 =
	(((u32)(((s32)1048576) - v_uncomp_pressure_s32)
	- (v_x2_u32 >> BME280_SHIFT_BIT_POSITION_BY_12_BITS))) * 3125;
	if (v_pressure_u32
	< 0x80000000)
		/* Avoid exception caused by division by zero */
		if (v_x1_u32 != BME280_INIT_VALUE)
			v_pressure_u32 =
			(v_pressure_u32
			<< BME280_SHIFT_BIT_POSITION_BY_01_BIT) /
			((u32)v_x1_u32);
		else
			return BME280_INVALID_DATA;
	else
		/* Avoid exception caused by division by zero */
		if (v_x1_u32 != BME280_INIT_VALUE)
			v_pressure_u32 = (v_pressure_u32
			/ (u32)v_x1_u32) * 2;
		else
			return BME280_INVALID_DATA;

		v_x1_u32 = (((s32)pCal_data->dig_P9) *
		((s32)(((v_pressure_u32 >> BME280_SHIFT_BIT_POSITION_BY_03_BITS)
		* (v_pressure_u32 >> BME280_SHIFT_BIT_POSITION_BY_03_BITS))
		>> BME280_SHIFT_BIT_POSITION_BY_13_BITS)))
		>> BME280_SHIFT_BIT_POSITION_BY_12_BITS;
		v_x2_u32 = (((s32)(v_pressure_u32
		>> BME280_SHIFT_BIT_POSITION_BY_02_BITS)) *
		((s32)pCal_data->dig_P8))
		>> BME280_SHIFT_BIT_POSITION_BY_13_BITS;
		v_pressure_u32 = (u32)((s32)v_pressure_u32 +
		((v_x1_u32 + v_x2_u32 + pCal_data->dig_P7)
		>> BME280_SHIFT_BIT_POSITION_BY_04_BITS));
		
sys_printf("v_pressure_u32 = %d\n\r",v_pressure_u32);
	return v_pressure_u32;
}

// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits).
// Output value of ¡°47445¡± represents 47445/1024 = 46.333 %RH

u32 bme280_compensate_humidity_int32(s32 v_uncomp_humidity_s32)
{
	s32 v_x1_u32 = BME280_INIT_VALUE;
	Bme280_Cal_data_structure *pCal_data = &Bme280_Cal_data_str;
	/* calculate x1*/
	v_x1_u32 = (pCal_data->t_fine - ((s32)76800));
	/* calculate x1*/
	v_x1_u32 = (((((v_uncomp_humidity_s32
	<< BME280_SHIFT_BIT_POSITION_BY_14_BITS) -
	(((s32)pCal_data->dig_H4)
	<< BME280_SHIFT_BIT_POSITION_BY_20_BITS) -
	(((s32)pCal_data->dig_H5) * v_x1_u32)) +
	((s32)16384)) >> BME280_SHIFT_BIT_POSITION_BY_15_BITS)
	* (((((((v_x1_u32 *
	((s32)pCal_data->dig_H6))
	>> BME280_SHIFT_BIT_POSITION_BY_10_BITS) *
	(((v_x1_u32 * ((s32)pCal_data->dig_H3))
	>> BME280_SHIFT_BIT_POSITION_BY_11_BITS) + ((s32)32768)))
	>> BME280_SHIFT_BIT_POSITION_BY_10_BITS) + ((s32)2097152)) *
	((s32)pCal_data->dig_H2) + 8192) >> 14));
	v_x1_u32 = (v_x1_u32 - (((((v_x1_u32
	>> BME280_SHIFT_BIT_POSITION_BY_15_BITS) *
	(v_x1_u32 >> BME280_SHIFT_BIT_POSITION_BY_15_BITS))
	>> BME280_SHIFT_BIT_POSITION_BY_07_BITS) *
	((s32)pCal_data->dig_H1))
	>> BME280_SHIFT_BIT_POSITION_BY_04_BITS));
	v_x1_u32 = (v_x1_u32 < 0 ? 0 : v_x1_u32);
	v_x1_u32 = (v_x1_u32 > 419430400 ?
	419430400 : v_x1_u32);
	sys_printf("humi = %d\n\r",v_x1_u32 >> BME280_SHIFT_BIT_POSITION_BY_12_BITS);
	return (u32)(v_x1_u32 >> BME280_SHIFT_BIT_POSITION_BY_12_BITS);
}
