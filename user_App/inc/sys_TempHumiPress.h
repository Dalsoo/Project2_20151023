
/*******************************************************************************
* File Name          : sys_TempHumiPress_process.h
* Author             :    SU. Jang
* Company        : Chamsolution  INC
* Project            :  Project1 (Gift Air)
* PART               : nRF51822(Nordic)
* Version            : V0.0
* Date               : 2015.4.06
* Description        :  Temperature, Hudimity , Pressure Sensor (BME280)
*******************************************************************************/


#ifndef  __SYS_TEMP_HUMI_PRESS_H__
#define __SYS_TEMP_HUMI_PRESS_H__

#include "sys_main.h"

#define THP_WR_ADD		0xEE
#define  THP_RD_ADD		0xEF

#define BME_280_ID			0x60
/***********   memory map  ************/
#define THP_ID_READ		0xD0
#define THP_RESET			0xE0
#define  THP_CTRL_HUM		0xF2
#define  THP_STATUS		0xF3
#define  THP_CTRL_MEAS	0xF4
#define  THP_CONFIG		0xF5
#define  THP_PRESS_MSB	0xF7
#define  THP_PRESS_LSB	0xF8
#define  THP_PRESS_XLSB	0xF9
#define  THP_TEMP_MSB	0xFA
#define  THP_TEMP_LSB		0xFB
#define  THP_TEMP_XLSB	0xFC
#define  THP_HUM_MSB		0xFD
#define  THP_HUM_LSB		0xFE

/***********   Ctrl Meas Register  ************/

#define  THP_PRESSURE_OVERSAMPLE_SKIPE	0x00
#define  THP_PRESSURE_OVERSAMPLE_1		0x04
#define  THP_PRESSURE_OVERSAMPLE_2		0x08
#define  THP_PRESSURE_OVERSAMPLE_4		0x0C
#define  THP_PRESSURE_OVERSAMPLE_8		0x10
#define  THP_PRESSURE_OVERSAMPLE_16		0x14

#define  THP_TEMP_OVERSAMPLE_SKIPE	0x00
#define  THP_TEMP_OVERSAMPLE_1		0x20
#define  THP_TEMP_OVERSAMPLE_2		0x40
#define  THP_TEMP_OVERSAMPLE_4		0x60
#define  THP_TEMP_OVERSAMPLE_8		0x80
#define  THP_TEMP_OVERSAMPLE_16		0xA0

#define    THP_SLEEP_MODE				0x00
#define	THP_FORCE_MODE				0x01
#define	THP_NORMAL_MODE			0x03

/***********   config Register  ************/
#define 	THP_T_STANDBY_005			0x00   // 0.5ms
#define 	THP_T_STANDBY_065			0x20   // 62.5ms
#define 	THP_T_STANDBY_125			0x40   // 125ms
#define 	THP_T_STANDBY_250			0x60   // 250ms
#define 	THP_T_STANDBY_500			0x80   // 500ms
#define 	THP_T_STANDBY_1000			0xA0   // 1000ms
#define 	THP_T_STANDBY_010			0xc0   // 10ms
#define 	THP_T_STANDBY_020			0xE0   // 20ms

#define 	THP_FILTER_OFF				0x00   // FILTER OFF
#define 	THP_FILTER_2					0x04   // FILTER 2
#define 	THP_FILTER_4					0x08   // FILTER 4
#define 	THP_FILTER_8					0x0C   // FILTER 8
#define 	THP_FILTER_16				0x10   // FILTER 16


/**********  control Humi   *******************/

#define  THP_HUMI_OVERSAMPLE_SKIPE	0x00
#define  THP_HUMI_OVERSAMPLE_1		0x01
#define  THP_HUMI_OVERSAMPLE_2		0x02
#define  THP_HUMI_OVERSAMPLE_4		0X03
#define  THP_HUMI_OVERSAMPLE_8		0x04
#define  THP_HUMI_OVERSAMPLE_16		0x05 


/***************************************************************/
/**\name	COMMON USED CONSTANTS      */
/***************************************************************/
/* Constants */
#define BME280_NULL                          (0)
#define BME280_RETURN_FUNCTION_TYPE          s8
/* shift definitions*/
#define BME280_SHIFT_BIT_POSITION_BY_01_BIT				(1)
#define BME280_SHIFT_BIT_POSITION_BY_02_BITS			(2)
#define BME280_SHIFT_BIT_POSITION_BY_03_BITS			(3)
#define BME280_SHIFT_BIT_POSITION_BY_04_BITS			(4)
#define BME280_SHIFT_BIT_POSITION_BY_07_BITS			(7)
#define BME280_SHIFT_BIT_POSITION_BY_08_BITS			(8)
#define BME280_SHIFT_BIT_POSITION_BY_10_BITS			(10)
#define BME280_SHIFT_BIT_POSITION_BY_11_BITS			(11)
#define BME280_SHIFT_BIT_POSITION_BY_12_BITS			(12)
#define BME280_SHIFT_BIT_POSITION_BY_13_BITS			(13)
#define BME280_SHIFT_BIT_POSITION_BY_14_BITS			(14)
#define BME280_SHIFT_BIT_POSITION_BY_15_BITS			(15)
#define BME280_SHIFT_BIT_POSITION_BY_16_BITS			(16)
#define BME280_SHIFT_BIT_POSITION_BY_17_BITS			(17)
#define BME280_SHIFT_BIT_POSITION_BY_18_BITS			(18)
#define BME280_SHIFT_BIT_POSITION_BY_19_BITS			(19)
#define BME280_SHIFT_BIT_POSITION_BY_20_BITS			(20)
#define BME280_SHIFT_BIT_POSITION_BY_25_BITS			(25)
#define BME280_SHIFT_BIT_POSITION_BY_31_BITS			(31)
#define BME280_SHIFT_BIT_POSITION_BY_33_BITS			(33)
#define BME280_SHIFT_BIT_POSITION_BY_35_BITS			(35)
#define BME280_SHIFT_BIT_POSITION_BY_47_BITS			(47)

/* numeric definitions */
#define	BME280_PRESSURE_TEMPERATURE_CALIB_DATA_LENGTH	    (26)
#define	BME280_HUMIDITY_CALIB_DATA_LENGTH	    (7)
#define	BME280_GEN_READ_WRITE_DATA_LENGTH		(1)
#define	BME280_HUMIDITY_DATA_LENGTH				(2)
#define	BME280_TEMPERATURE_DATA_LENGTH			(3)
#define	BME280_PRESSURE_DATA_LENGTH				(3)
#define	BME280_ALL_DATA_FRAME_LENGTH			(8)
#define	BME280_INIT_VALUE						(0)
#define	BME280_INVALID_DATA						(0)

/****************************************************/
/**\name	ERROR CODE DEFINITIONS  */
/***************************************************/
#define	SUCCESS					((u8)0)
#define E_BME280_NULL_PTR       ((s8)-127)
#define E_BME280_COMM_RES       ((s8)-1)
#define E_BME280_OUT_OF_RANGE   ((s8)-2)
#define ERROR					((s8)-1)
/****************************************************/
/**\name	I2C ADDRESS DEFINITIONS  */
/***************************************************/
#define BME280_I2C_ADDRESS1                  (0x76)
#define BME280_I2C_ADDRESS2                  (0x77)
/****************************************************/
/**\name	POWER MODE DEFINITIONS  */
/***************************************************/
/* Sensor Specific constants */
#define BME280_SLEEP_MODE                    (0x00)
#define BME280_FORCED_MODE                   (0x01)
#define BME280_NORMAL_MODE                   (0x03)
#define BME280_SOFT_RESET_CODE               (0xB6)
/****************************************************/
/**\name	STANDBY DEFINITIONS  */
/***************************************************/
#define BME280_STANDBY_TIME_1_MS              (0x00)
#define BME280_STANDBY_TIME_63_MS             (0x01)
#define BME280_STANDBY_TIME_125_MS			  (0x02)
#define BME280_STANDBY_TIME_250_MS            (0x03)
#define BME280_STANDBY_TIME_500_MS            (0x04)
#define BME280_STANDBY_TIME_1000_MS           (0x05)
#define BME280_STANDBY_TIME_10_MS             (0x06)
#define BME280_STANDBY_TIME_20_MS             (0x07)
/****************************************************/
/**\name	OVER SAMPLING DEFINITIONS  */
/***************************************************/
#define BME280_OVERSAMP_SKIPPED          (0x00)
#define BME280_OVERSAMP_1X               (0x01)
#define BME280_OVERSAMP_2X               (0x02)
#define BME280_OVERSAMP_4X               (0x03)
#define BME280_OVERSAMP_8X               (0x04)
#define BME280_OVERSAMP_16X              (0x05)
/****************************************************/
/**\name	WORK MODE DEFINITIONS  */
/***************************************************/
/*#define BME280_ULTRALOWPOWER_MODE          (0x00)
#define BME280_LOWPOWER_MODE                 (0x01)
#define BME280_STANDARDRESOLUTION_MODE       (0x02)
#define BME280_HIGHRESOLUTION_MODE           (0x03)
#define BME280_ULTRAHIGHRESOLUTION_MODE      (0x04)

#define BME280_ULTRALOWPOWER_OSRS_P          BME280_OVERSAMP_1X
#define BME280_ULTRALOWPOWER_OSRS_T          BME280_OVERSAMP_1X

#define BME280_LOWPOWER_OSRS_P               BME280_OVERSAMP_2X
#define BME280_LOWPOWER_OSRS_T               BME280_OVERSAMP_1X

#define BME280_STANDARDRESOLUTION_OSRS_P     BME280_OVERSAMP_4X
#define BME280_STANDARDRESOLUTION_OSRS_T     BME280_OVERSAMP_1X

#define BME280_HIGHRESOLUTION_OSRS_P         BME280_OVERSAMP_8X
#define BME280_HIGHRESOLUTION_OSRS_T         BME280_OVERSAMP_1X

#define BME280_ULTRAHIGHRESOLUTION_OSRS_P    BME280_OVERSAMP_16X
#define BME280_ULTRAHIGHRESOLUTION_OSRS_T    BME280_OVERSAMP_2X */

#define BME280_STANDARD_OVERSAMP_HUMIDITY	BME280_OVERSAMP_1X
/****************************************************/
/**\name	FILTER DEFINITIONS  */
/***************************************************/
#define BME280_FILTER_COEFF_OFF               (0x00)
#define BME280_FILTER_COEFF_2                 (0x01)
#define BME280_FILTER_COEFF_4                 (0x02)
#define BME280_FILTER_COEFF_8                 (0x03)
#define BME280_FILTER_COEFF_16                (0x04)
/****************************************************/
/**\name	DELAY DEFINITIONS  */
/***************************************************/
#define T_INIT_MAX                             (20)
		/* 20/16 = 1.25 ms */
#define T_MEASURE_PER_OSRS_MAX                 (37)
		/* 37/16 = 2.3125 ms*/

#define T_SETUP_PRESSURE_MAX                   (10)
		/* 10/16 = 0.625 ms */

#define T_SETUP_HUMIDITY_MAX                   (10)
		/* 10/16 = 0.625 ms */
/****************************************************/
/**\name	DEFINITIONS FOR ARRAY SIZE OF DATA   */
/***************************************************/
#define	BME280_HUMIDITY_DATA_SIZE		(2)
#define	BME280_TEMPERATURE_DATA_SIZE	(3)
#define	BME280_PRESSURE_DATA_SIZE		(3)
#define	BME280_DATA_FRAME_SIZE			(8)
/**< data frames includes temperature,
pressure and humidity*/
#define	BME280_CALIB_DATA_SIZE			(26)

#define	BME280_TEMPERATURE_MSB_DATA		(0)
#define	BME280_TEMPERATURE_LSB_DATA		(1)
#define	BME280_TEMPERATURE_XLSB_DATA	(2)
#define	BME280_PRESSURE_MSB_DATA		(0)
#define	BME280_PRESSURE_LSB_DATA		(1)
#define	BME280_PRESSURE_XLSB_DATA	    (2)
#define	BME280_HUMIDITY_MSB_DATA		(0)
#define	BME280_HUMIDITY_LSB_DATA		(1)

#define	BME280_DATA_FRAME_PRESSURE_MSB_BYTE	    (0)
#define	BME280_DATA_FRAME_PRESSURE_LSB_BYTE		(1)
#define	BME280_DATA_FRAME_PRESSURE_XLSB_BYTE	(2)
#define	BME280_DATA_FRAME_TEMPERATURE_MSB_BYTE	(3)
#define	BME280_DATA_FRAME_TEMPERATURE_LSB_BYTE	(4)
#define	BME280_DATA_FRAME_TEMPERATURE_XLSB_BYTE	(5)
#define	BME280_DATA_FRAME_HUMIDITY_MSB_BYTE		(6)
#define	BME280_DATA_FRAME_HUMIDITY_LSB_BYTE		(7)
/****************************************************/
/**\name	ARRAY PARAMETER FOR CALIBRATION     */
/***************************************************/
#define	BME280_TEMPERATURE_CALIB_DIG_T1_LSB		(0)
#define	BME280_TEMPERATURE_CALIB_DIG_T1_MSB		(1)
#define	BME280_TEMPERATURE_CALIB_DIG_T2_LSB		(2)
#define	BME280_TEMPERATURE_CALIB_DIG_T2_MSB		(3)
#define	BME280_TEMPERATURE_CALIB_DIG_T3_LSB		(4)
#define	BME280_TEMPERATURE_CALIB_DIG_T3_MSB		(5)
#define	BME280_PRESSURE_CALIB_DIG_P1_LSB       (6)
#define	BME280_PRESSURE_CALIB_DIG_P1_MSB       (7)
#define	BME280_PRESSURE_CALIB_DIG_P2_LSB       (8)
#define	BME280_PRESSURE_CALIB_DIG_P2_MSB       (9)
#define	BME280_PRESSURE_CALIB_DIG_P3_LSB       (10)
#define	BME280_PRESSURE_CALIB_DIG_P3_MSB       (11)
#define	BME280_PRESSURE_CALIB_DIG_P4_LSB       (12)
#define	BME280_PRESSURE_CALIB_DIG_P4_MSB       (13)
#define	BME280_PRESSURE_CALIB_DIG_P5_LSB       (14)
#define	BME280_PRESSURE_CALIB_DIG_P5_MSB       (15)
#define	BME280_PRESSURE_CALIB_DIG_P6_LSB       (16)
#define	BME280_PRESSURE_CALIB_DIG_P6_MSB       (17)
#define	BME280_PRESSURE_CALIB_DIG_P7_LSB       (18)
#define	BME280_PRESSURE_CALIB_DIG_P7_MSB       (19)
#define	BME280_PRESSURE_CALIB_DIG_P8_LSB       (20)
#define	BME280_PRESSURE_CALIB_DIG_P8_MSB       (21)
#define	BME280_PRESSURE_CALIB_DIG_P9_LSB       (22)
#define	BME280_PRESSURE_CALIB_DIG_P9_MSB       (23)
#define	BME280_HUMIDITY_CALIB_DIG_H1           (25)
#define	BME280_HUMIDITY_CALIB_DIG_H2_LSB		(0)
#define	BME280_HUMIDITY_CALIB_DIG_H2_MSB		(1)
#define	BME280_HUMIDITY_CALIB_DIG_H3			(2)
#define	BME280_HUMIDITY_CALIB_DIG_H4_MSB		(3)
#define	BME280_HUMIDITY_CALIB_DIG_H4_LSB		(4)
#define	BME280_HUMIDITY_CALIB_DIG_H5_MSB		(5)
#define	BME280_HUMIDITY_CALIB_DIG_H6			(6)
#define	BME280_MASK_DIG_H4		(0x0F)
/****************************************************/
/**\name	CALIBRATION REGISTER ADDRESS DEFINITIONS  */
/***************************************************/
/*calibration parameters */
#define BME280_TEMPERATURE_CALIB_DIG_T1_LSB_REG             (0x88)
#define BME280_TEMPERATURE_CALIB_DIG_T1_MSB_REG             (0x89)
#define BME280_TEMPERATURE_CALIB_DIG_T2_LSB_REG             (0x8A)
#define BME280_TEMPERATURE_CALIB_DIG_T2_MSB_REG             (0x8B)
#define BME280_TEMPERATURE_CALIB_DIG_T3_LSB_REG             (0x8C)
#define BME280_TEMPERATURE_CALIB_DIG_T3_MSB_REG             (0x8D)
#define BME280_PRESSURE_CALIB_DIG_P1_LSB_REG                (0x8E)
#define BME280_PRESSURE_CALIB_DIG_P1_MSB_REG                (0x8F)
#define BME280_PRESSURE_CALIB_DIG_P2_LSB_REG                (0x90)
#define BME280_PRESSURE_CALIB_DIG_P2_MSB_REG                (0x91)
#define BME280_PRESSURE_CALIB_DIG_P3_LSB_REG                (0x92)
#define BME280_PRESSURE_CALIB_DIG_P3_MSB_REG                (0x93)
#define BME280_PRESSURE_CALIB_DIG_P4_LSB_REG                (0x94)
#define BME280_PRESSURE_CALIB_DIG_P4_MSB_REG                (0x95)
#define BME280_PRESSURE_CALIB_DIG_P5_LSB_REG                (0x96)
#define BME280_PRESSURE_CALIB_DIG_P5_MSB_REG                (0x97)
#define BME280_PRESSURE_CALIB_DIG_P6_LSB_REG                (0x98)
#define BME280_PRESSURE_CALIB_DIG_P6_MSB_REG                (0x99)
#define BME280_PRESSURE_CALIB_DIG_P7_LSB_REG                (0x9A)
#define BME280_PRESSURE_CALIB_DIG_P7_MSB_REG                (0x9B)
#define BME280_PRESSURE_CALIB_DIG_P8_LSB_REG                (0x9C)
#define BME280_PRESSURE_CALIB_DIG_P8_MSB_REG                (0x9D)
#define BME280_PRESSURE_CALIB_DIG_P9_LSB_REG                (0x9E)
#define BME280_PRESSURE_CALIB_DIG_P9_MSB_REG                (0x9F)

#define BME280_HUMIDITY_CALIB_DIG_H1_REG                    (0xA1)

#define BME280_HUMIDITY_CALIB_DIG_H2_LSB_REG                (0xE1)
#define BME280_HUMIDITY_CALIB_DIG_H2_MSB_REG                (0xE2)
#define BME280_HUMIDITY_CALIB_DIG_H3_REG                    (0xE3)
#define BME280_HUMIDITY_CALIB_DIG_H4_MSB_REG                (0xE4)
#define BME280_HUMIDITY_CALIB_DIG_H4_LSB_REG                (0xE5)
#define BME280_HUMIDITY_CALIB_DIG_H5_MSB_REG                (0xE6)
#define BME280_HUMIDITY_CALIB_DIG_H6_REG                    (0xE7)
/****************************************************/
/**\name	REGISTER ADDRESS DEFINITIONS  */
/***************************************************/
#define BME280_CHIP_ID_REG                   (0xD0)  /*Chip ID Register */
#define BME280_RST_REG                       (0xE0)  /*Softreset Register */
#define BME280_STAT_REG                      (0xF3)  /*Status Register */
#define BME280_CTRL_MEAS_REG                 (0xF4)  /*Ctrl Measure Register */
#define BME280_CTRL_HUMIDITY_REG             (0xF2)  /*Ctrl Humidity Register*/
#define BME280_CONFIG_REG                    (0xF5)  /*Configuration Register */
#define BME280_PRESSURE_MSB_REG              (0xF7)  /*Pressure MSB Register */
#define BME280_PRESSURE_LSB_REG              (0xF8)  /*Pressure LSB Register */
#define BME280_PRESSURE_XLSB_REG             (0xF9)  /*Pressure XLSB Register */
#define BME280_TEMPERATURE_MSB_REG           (0xFA)  /*Temperature MSB Reg */
#define BME280_TEMPERATURE_LSB_REG           (0xFB)  /*Temperature LSB Reg */
#define BME280_TEMPERATURE_XLSB_REG          (0xFC)  /*Temperature XLSB Reg */
#define BME280_HUMIDITY_MSB_REG              (0xFD)  /*Humidity MSB Reg */
#define BME280_HUMIDITY_LSB_REG              (0xFE)  /*Humidity LSB Reg */
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS  */
/***************************************************/
/* Status Register */
#define BME280_STAT_REG_MEASURING__POS           (3)
#define BME280_STAT_REG_MEASURING__MSK           (0x08)
#define BME280_STAT_REG_MEASURING__LEN           (1)
#define BME280_STAT_REG_MEASURING__REG           (BME280_STAT_REG)

#define BME280_STAT_REG_IM_UPDATE__POS            (0)
#define BME280_STAT_REG_IM_UPDATE__MSK            (0x01)
#define BME280_STAT_REG_IM_UPDATE__LEN            (1)
#define BME280_STAT_REG_IM_UPDATE__REG            (BME280_STAT_REG)
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS
FOR TEMPERATURE OVERSAMPLING  */
/***************************************************/
/* Control Measurement Register */
#define BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__POS             (5)
#define BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__MSK             (0xE0)
#define BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__LEN             (3)
#define BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__REG             \
(BME280_CTRL_MEAS_REG)
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS
FOR PRESSURE OVERSAMPLING  */
/***************************************************/
#define BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__POS             (2)
#define BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__MSK             (0x1C)
#define BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__LEN             (3)
#define BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__REG             \
(BME280_CTRL_MEAS_REG)
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS
FOR POWER MODE  */
/***************************************************/
#define BME280_CTRL_MEAS_REG_POWER_MODE__POS              (0)
#define BME280_CTRL_MEAS_REG_POWER_MODE__MSK              (0x03)
#define BME280_CTRL_MEAS_REG_POWER_MODE__LEN              (2)
#define BME280_CTRL_MEAS_REG_POWER_MODE__REG              \
(BME280_CTRL_MEAS_REG)
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS
FOR HUMIDITY OVERSAMPLING  */
/***************************************************/
#define BME280_CTRL_HUMIDITY_REG_OVERSAMP_HUMIDITY__POS             (0)
#define BME280_CTRL_HUMIDITY_REG_OVERSAMP_HUMIDITY__MSK             (0x07)
#define BME280_CTRL_HUMIDITY_REG_OVERSAMP_HUMIDITY__LEN             (3)
#define BME280_CTRL_HUMIDITY_REG_OVERSAMP_HUMIDITY__REG            \
(BME280_CTRL_HUMIDITY_REG)
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS
FOR STANDBY TIME  */
/***************************************************/
/* Configuration Register */
#define BME280_CONFIG_REG_TSB__POS                 (5)
#define BME280_CONFIG_REG_TSB__MSK                 (0xE0)
#define BME280_CONFIG_REG_TSB__LEN                 (3)
#define BME280_CONFIG_REG_TSB__REG                 (BME280_CONFIG_REG)
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS
FOR FILTER */
/***************************************************/
#define BME280_CONFIG_REG_FILTER__POS              (2)
#define BME280_CONFIG_REG_FILTER__MSK              (0x1C)
#define BME280_CONFIG_REG_FILTER__LEN              (3)
#define BME280_CONFIG_REG_FILTER__REG              (BME280_CONFIG_REG)
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS
FOR SPI ENABLE  */
/***************************************************/
#define BME280_CONFIG_REG_SPI3_ENABLE__POS             (0)
#define BME280_CONFIG_REG_SPI3_ENABLE__MSK             (0x01)
#define BME280_CONFIG_REG_SPI3_ENABLE__LEN             (1)
#define BME280_CONFIG_REG_SPI3_ENABLE__REG            (BME280_CONFIG_REG)
/****************************************************/
/**\name	BIT MASK, LENGTH AND POSITION DEFINITIONS
FOR PRESSURE AND TEMPERATURE DATA  */
/***************************************************/
/* Data Register */
#define BME280_PRESSURE_XLSB_REG_DATA__POS         (4)
#define BME280_PRESSURE_XLSB_REG_DATA__MSK         (0xF0)
#define BME280_PRESSURE_XLSB_REG_DATA__LEN         (4)
#define BME280_PRESSURE_XLSB_REG_DATA__REG         (BME280_PRESSURE_XLSB_REG)

#define BME280_TEMPERATURE_XLSB_REG_DATA__POS      (4)
#define BME280_TEMPERATURE_XLSB_REG_DATA__MSK      (0xF0)
#define BME280_TEMPERATURE_XLSB_REG_DATA__LEN      (4)
#define BME280_TEMPERATURE_XLSB_REG_DATA__REG      (BME280_TEMPERATURE_XLSB_REG)

typedef struct
{
	
	u16 dig_T1;/**<calibration T1 data*/
	s16 dig_T2;/**<calibration T2 data*/
	s16 dig_T3;/**<calibration T3 data*/
	u16 dig_P1;/**<calibration P1 data*/
	s16 dig_P2;/**<calibration P2 data*/
	s16 dig_P3;/**<calibration P3 data*/
	s16 dig_P4;/**<calibration P4 data*/
	s16 dig_P5;/**<calibration P5 data*/
	s16 dig_P6;/**<calibration P6 data*/
	s16 dig_P7;/**<calibration P7 data*/
	s16 dig_P8;/**<calibration P8 data*/
	s16 dig_P9;/**<calibration P9 data*/

	u8  dig_H1;/**<calibration H1 data*/
	s16 dig_H2;/**<calibration H2 data*/
	u8  dig_H3;/**<calibration H3 data*/
	s16 dig_H4;/**<calibration H4 data*/
	s16 dig_H5;/**<calibration H5 data*/
	s8  dig_H6;/**<calibration H6 data*/

	s32 t_fine;/**<calibration T_FINE data*/
	
	s32 temp;
	u32 press;
	u32 humi;
	
	
}Bme280_Cal_data_structure;

extern Bme280_Cal_data_structure Bme280_Cal_data_str;

struct bme280_calibration_param_t {
	u16 dig_T1;/**<calibration T1 data*/
	s16 dig_T2;/**<calibration T2 data*/
	s16 dig_T3;/**<calibration T3 data*/
	u16 dig_P1;/**<calibration P1 data*/
	s16 dig_P2;/**<calibration P2 data*/
	s16 dig_P3;/**<calibration P3 data*/
	s16 dig_P4;/**<calibration P4 data*/
	s16 dig_P5;/**<calibration P5 data*/
	s16 dig_P6;/**<calibration P6 data*/
	s16 dig_P7;/**<calibration P7 data*/
	s16 dig_P8;/**<calibration P8 data*/
	s16 dig_P9;/**<calibration P9 data*/

	u8  dig_H1;/**<calibration H1 data*/
	s16 dig_H2;/**<calibration H2 data*/
	u8  dig_H3;/**<calibration H3 data*/
	s16 dig_H4;/**<calibration H4 data*/
	s16 dig_H5;/**<calibration H5 data*/
	s8  dig_H6;/**<calibration H6 data*/

	s32 t_fine;/**<calibration T_FINE data*/
};
/*!
 * @brief This structure holds BME280 initialization parameters
 */
struct bme280_t {
	struct bme280_calibration_param_t cal_param;
	/**< calibration parameters*/

	u8 chip_id;/**< chip id of the sensor*/
	u8 dev_addr;/**< device address of the sensor*/

	u8 oversamp_temperature;/**< temperature over sampling*/
	u8 oversamp_pressure;/**< pressure over sampling*/
	u8 oversamp_humidity;/**< humidity over sampling*/
	u8 ctrl_hum_reg;/**< status of control humidity register*/
	u8 ctrl_meas_reg;/**< status of control measurement register*/
	u8 config_reg;/**< status of configuration register*/
};



u8 sys_GetBME280_ID(void);
void sys_BME280_init(void);
u32 sys_GetBME280_Press(void);
u32 sys_GetBME280_Temp(void);
u16 sys_GetBME280_Humi(void);

u8 sys_GetBME280_Temp_Press_Hudi(u32 *temp_data,u32 *press_data, u16 *humi_data);
u8 sys_GetBME280_Force_Temp_Press_Hudi(u32 *temp_data,u32 *press_data, u16 *humi_data);
#endif



