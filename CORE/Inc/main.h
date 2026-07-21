/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "eep_addr.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern RTC_DateTypeDef sdatestructure;
extern RTC_TimeTypeDef stimestructure;

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCU_MOTOR_Pin GPIO_PIN_2
#define MCU_MOTOR_GPIO_Port GPIOC
#define MCU_TRIP_Pin GPIO_PIN_3
#define MCU_TRIP_GPIO_Port GPIOC
#define CUR_LEAK_Pin GPIO_PIN_0
#define CUR_LEAK_GPIO_Port GPIOA
#define CUR_A_Pin GPIO_PIN_1
#define CUR_A_GPIO_Port GPIOA
#define CUR_B_Pin GPIO_PIN_2
#define CUR_B_GPIO_Port GPIOA
#define CUR_C_Pin GPIO_PIN_3
#define CUR_C_GPIO_Port GPIOA
#define V_A_IN_Pin GPIO_PIN_4
#define V_A_IN_GPIO_Port GPIOA
#define V_B_IN_Pin GPIO_PIN_5
#define V_B_IN_GPIO_Port GPIOA
#define V_C_IN_Pin GPIO_PIN_6
#define V_C_IN_GPIO_Port GPIOA
#define VLOSS_DET_Pin GPIO_PIN_7
#define VLOSS_DET_GPIO_Port GPIOA
#define BRK_POS_Pin GPIO_PIN_4
#define BRK_POS_GPIO_Port GPIOC
#define LCD_BL_Pin GPIO_PIN_5
#define LCD_BL_GPIO_Port GPIOC
#define LCD_RD_Pin GPIO_PIN_0
#define LCD_RD_GPIO_Port GPIOB
#define LCD_WR_Pin GPIO_PIN_1
#define LCD_WR_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_2
#define LCD_RS_GPIO_Port GPIOB
#define LCD_RESET_Pin GPIO_PIN_10
#define LCD_RESET_GPIO_Port GPIOB
#define TEST_BTN_Pin GPIO_PIN_11
#define TEST_BTN_GPIO_Port GPIOB
#define DOWN_BTN_Pin GPIO_PIN_12
#define DOWN_BTN_GPIO_Port GPIOB
#define BACK_BTN_Pin GPIO_PIN_13
#define BACK_BTN_GPIO_Port GPIOB
#define CENTER_BTN_Pin GPIO_PIN_14
#define CENTER_BTN_GPIO_Port GPIOB
#define SET_BTN_Pin GPIO_PIN_15
#define SET_BTN_GPIO_Port GPIOB
#define OPEN_BTN_Pin GPIO_PIN_6
#define OPEN_BTN_GPIO_Port GPIOC
#define CLOSE_BTN_Pin GPIO_PIN_7
#define CLOSE_BTN_GPIO_Port GPIOC
#define LK_TEST_Pin GPIO_PIN_8
#define LK_TEST_GPIO_Port GPIOC
#define UP_BTN_Pin GPIO_PIN_9
#define UP_BTN_GPIO_Port GPIOC
#define RS485_EN_Pin GPIO_PIN_8
#define RS485_EN_GPIO_Port GPIOA
#define RS485_TX_Pin GPIO_PIN_9
#define RS485_TX_GPIO_Port GPIOA
#define RS485_RX_Pin GPIO_PIN_10
#define RS485_RX_GPIO_Port GPIOA
#define EXT_TRIP_DET_Pin GPIO_PIN_11
#define EXT_TRIP_DET_GPIO_Port GPIOA
#define EXT_CLOSE_DET_Pin GPIO_PIN_12
#define EXT_CLOSE_DET_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_15
#define D7_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_10
#define D6_GPIO_Port GPIOC
#define D5_Pin GPIO_PIN_11
#define D5_GPIO_Port GPIOC
#define D4_Pin GPIO_PIN_12
#define D4_GPIO_Port GPIOC
#define D3_Pin GPIO_PIN_2
#define D3_GPIO_Port GPIOD
#define D2_Pin GPIO_PIN_3
#define D2_GPIO_Port GPIOB
#define D1_Pin GPIO_PIN_4
#define D1_GPIO_Port GPIOB
#define D0_Pin GPIO_PIN_5
#define D0_GPIO_Port GPIOB
#define I2C_SCL_Pin GPIO_PIN_8
#define I2C_SCL_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define Lenth_dev_id 6
#define Lenth_dev_addr 6
#define Lenth_dev_code 32
#define Lenth_rated_V 6
#define Lenth_rated_I 6
#define Lenth_frame_current 6
#define Lenth_equi_type 10
#define Lenth_production_date 10
#define Lenth_protocol_ver 16
#define Lenth_factory_code 24
#define Lenth_soft_ver 32
#define Lenth_hard_ver 32
#define Lenth_leak_valve 20
#define Lenth_leak_time 10
#define Lenth_break_time 10
#define Lenth_auto_closing 24
#define Lenth_leak_type 24
#define Lenth_install_phase 10
#define Lenth_0_password 4
#define Lenth_1_password 4
#define Lenth_2_password 4
#define Lenth_alarm_value 2
#define Lenth_record_value 1
#define Lenth_record_time 1
#define Lenth_timed_trip 3
#define Lenth_over_vol 2
#define Lenth_under_vol 2
#define Lenth_break_phase 2
#define Lenth_rated_current 3
#define Lenth_over_current 1
#define Lenth_remote_trip 2
#define Lenth_remote_close 2
#define Lenth_analog_trip 2
#define Lenth_clear_num 3
#define Lenth_trip_num 2
#define Lenth_close_num 2
#define Lenth_leak_num 2
#define Lenth_current_num 2
#define Lenth_vol_num 2
#define Lenth_hand_num 2
#define Lenth_zero_num 2
#define Lenth_test_num 2
#define Lenth_2D_num 2
#define Lenth_3D_num 2
#define Lenth_LD_up_num 2
#define Lenth_AJ_sy_num 2
#define Lenth_leakquit_num 2
#define Lenth_protect_time 4
#define Lenth_max_leak 9
#define Lenth_max_Avol 8
#define Lenth_max_Bvol 8
#define Lenth_max_Cvol 8
#define Lenth_max_Acur 9
#define Lenth_max_Bcur 9
#define Lenth_max_Ccur 9
#define Lenth_min_leak 9
#define Lenth_min_Avol 8
#define Lenth_min_Bvol 8
#define Lenth_min_Cvol 8
#define Lenth_min_Acur 9
#define Lenth_min_Bcur 9
#define Lenth_min_Ccur 9
#define Lenth_event_leak 15
#define Lenth_event_self 26
#define Lenth_event_trip 25
#define Lenth_event_alarm 12
#define Lenth_record_leak1 9
#define Lenth_record_leak2 9
#define Lenth_F_GJ_FUNC 1

#define H_H_V 250 + Vol_g
#define H_L_V 140 + Vol_q
#define V_UP D_UP_Array[Vol_up]
#define V_DOWN D_DOWN_Array[Vol_down]
#define F_ZTrip F_ITrip + F_Trip + F_VTrip + F_UTrip + F_STrip

// 5,6	漏电因子	L_factor
// 7,8	电压因子	V_factor
// 9,10	电流因字	I_factor

#define ERR_BAD_DATA (0x01 + 0x33)
#define ERR_NO_REQUEST (0x02 + 0x33)
#define ERR_BAD_PASSWORD (0x04 + 0x33)
#define ERR_BAD_BAUD (0x08 + 0x33)
#define ERR_NO_REMOTE (0x10 + 0x33)

// 不隔离
#define TX_E E485 = 1
#define RX_E E485 = 0
// 隔离
// #define TX_E   E485 = 0
// #define RX_E   E485 = 1

#define T_H_V T_HV_Array[D_GY_yanshi]
#define T_L_V T_LV_Array[D_QY_yanshi]
#define T_S_V T_SV_Array[D_SY_yanshi]

//#define set_bit(val, bitn)    (val |=(1<<(bitn)))
#define clr_bit(val, bitn)    (val&=~(1<<(bitn)))
//#define get_bit(val, bitn)    (val &(1<<(bitn)) )
//#define neg_bit(val, bitn)    (val^=(1<<(bitn)))
#define A_QX 0x10
#define B_QX 0x11
#define C_QX 0x12
#define A_sy 0x14
#define B_sy 0x15
#define C_sy 0x16
#define A_qy 0  
//A相欠压故障		
#define B_qy 2  
//B相欠压故障  
#define C_qy 4  
//C相欠压故障
#define A_gy 1  
//A相过压故障
#define B_gy 3  
//B相过压故障
#define C_gy 5  
//C相过压故障
#define L_hb 6 
//漏电故障
#define A_gl 7  
//A相过流故障
#define B_gl 8  
//B相过流故障
#define C_gl 9  
//C相过流故障
#define N_gl 0x0A 
//D相过流故障
#define Gz_TD 0x0B 
//停电故障
//#define FZ_SD 0x0C //手动分闸（未知）
#define FZ_UK 0x0c 
//未知分闸
#define FZ_AJ 0x0d 
//按键分闸
#define FZ_YC 0x0e 
//远程分闸
#define Gz_QL 0x13
//故障灯的定义
#define GV_LED_ON dispbit[4] = 0x01;
#define GL_LED_ON dispbit[4] = 0x02;
#define GC_LED_ON dispbit[4] = 0x04;
#define GJ_LED_ON dispbit[4] = 0x08;

#define trip_reason_normal 0 
#define trip_reason_leak 2 
#define trip_reason_zero 4 
#define trip_reason_cur 5 
#define trip_reason_short 6 
#define trip_reason_phase 7 
#define trip_reason_undervoltage 8 
#define trip_reason_overvoltage 9 
#define trip_reason_ground 0x0A 
#define trip_reason_powerdown 0x0B 
#define trip_reason_timer 0x0C 
#define trip_reason_remote 0x0D 
#define trip_reason_key 0x0E 
#define trip_reason_lock 0x0F 
#define trip_reason_sensor 0x10 
#define trip_reason_close 0x11 
#define trip_reason_hand 0x12 
#define trip_reason_change 0x13 
#define trip_reason_quit 0x1F
#define trip_reason_3D_cur 0x16
#define trip_reason_lowvoltage 0x17

#define Trip_LED PDout(2)// PB5

#define start 	   HAL_GPIO_WritePin(MCU_MOTOR_GPIO_Port, MCU_MOTOR_Pin, GPIO_PIN_SET) 
#define stop  		 HAL_GPIO_WritePin(MCU_MOTOR_GPIO_Port, MCU_MOTOR_Pin, GPIO_PIN_RESET) 

#define Trip_ON    HAL_GPIO_WritePin(MCU_TRIP_GPIO_Port, MCU_TRIP_Pin, GPIO_PIN_SET)  
#define Trip_OFF   HAL_GPIO_WritePin(MCU_TRIP_GPIO_Port, MCU_TRIP_Pin, GPIO_PIN_RESET)



  #if type_125
    #define Trip_LED_ON   // HAL_GPIO_WritePin(TRIP_LED_GPIO_Port, TRIP_LED_Pin, GPIO_PIN_RESET)
	#define Trip_LED_OFF   //HAL_GPIO_WritePin(TRIP_LED_GPIO_Port, TRIP_LED_Pin, GPIO_PIN_SET)   
  #else
    #define Trip_LED_ON    HAL_GPIO_WritePin(TRIP_LED_GPIO_Port, TRIP_LED_Pin, GPIO_PIN_RESET)
		#define Trip_LED_OFF   HAL_GPIO_WritePin(TRIP_LED_GPIO_Port, TRIP_LED_Pin, GPIO_PIN_SET)
  #endif

#define RS485_RX_EN   HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_SET)//设置为接收模式  
#define RS485_TX_EN   HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET)//设置为发送模式
//#define RS485_RX_EN   HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_RESET)//设置为接收模式  
//#define RS485_TX_EN   HAL_GPIO_WritePin(RS485_EN_GPIO_Port, RS485_EN_Pin, GPIO_PIN_SET)//设置为发送模式

#define Test_start   HAL_GPIO_WritePin(LK_TEST_GPIO_Port, LK_TEST_Pin, GPIO_PIN_RESET)//
#define Test_stop   HAL_GPIO_WritePin(LK_TEST_GPIO_Port, LK_TEST_Pin, GPIO_PIN_SET)//


extern volatile int cui;
extern volatile	unsigned char F_re_sta;
extern unsigned char  dian[16];


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
