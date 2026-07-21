/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "delay.h"
#include "rtc.h"
#include "tool.h"
#include "disp.h"
#include "24cxx.h"





extern volatile unsigned char Type_Cur,D2_Cur,D3_Cur;        //过流保护规格,档位长度,档位指针
extern  unsigned char R_SD[8];
extern	volatile unsigned long Delta_Cur,DLD_Cur,DLS_Cur;
extern	u8 at[3];
extern volatile unsigned char TH_hezha_delay;
extern volatile unsigned char hezha_delay;
extern volatile unsigned char hezha_delay_arry[10];//
int Vol_g_decimal;
int Vol_q_decimal;
extern void Cur_Switch(unsigned char tmp);
extern void ctrlword1_analyze(void);
extern void ctrlword2_analyze(void);
extern void ctrlword3_analyze(void);
extern void ctrlword4_analyze(void);
extern void ctrlword5_analyze(void);
void Read_fenzha_tim(unsigned char fact_tmp);

extern volatile unsigned char tim_disp[7],tim_m,tim_d,tim_h,tim_f,tim_s,sssj_N;
extern volatile unsigned char tim_m1,tim_d1,tim_h1,tim_f1,tim_s1;
extern volatile unsigned int  tim_y;
extern volatile unsigned int  tim_y1;
extern volatile unsigned int  Vol_g,Vol_q;

extern volatile unsigned char tim_m2,tim_d2,tim_h2,tim_f2,tim_s2;
extern volatile unsigned int  tim_y2;


extern volatile unsigned int DLS_Cur_IV_AD_value[5],DLS_Cur_IV_slope[5],DLS_Cur_IV_Value[5];
extern volatile unsigned int DLS_Cur_I_AD_value[5],DLS_Cur_I_slope[5],DLS_Cur_I_Value[5];
extern volatile unsigned int DLS_Cur_II_AD_value[5],DLS_Cur_II_slope[5],DLS_Cur_II_Value[5];
extern volatile unsigned int DLS_Cur_III_AD_value[5],DLS_Cur_III_slope[5],DLS_Cur_III_Value[5];


void hongwai_SendData(unsigned char Data);
unsigned char hard_ver_code[Lenth_hard_ver] = "hard ver1.0 2013-11-28          ";
unsigned char soft_ver_code[Lenth_soft_ver] = "soft ver1.0 2013-11-28          ";

//南京鼎牌的是"1LJM4L    "
//另外一家是  "1GRM1L    "
unsigned int UART_N1=0,UART_N2=0;
extern void Cur_Switch_F(unsigned char tmp);
extern void copy_array(unsigned char *obj_tmp,unsigned char *sours_tmp,unsigned char lenth_tmp);
extern unsigned char dev_id_code[];
extern      unsigned char dev_code_code[];
extern      unsigned char frame_current_code[];
extern      unsigned char rated_V_code[];
extern      unsigned char equi_type_code[];
extern      unsigned char production_date_code[];
extern      unsigned char protocol_ver_code[];
extern      unsigned char factory_code_code[];
//extern      unsigned char soft_ver_code[];
//extern      unsigned char hard_ver_code[];
extern      unsigned char leak_valve_code[];
extern      unsigned char leak_time_code[];
extern      unsigned char break_time_code[];
extern      unsigned char auto_closing_code[];
extern      unsigned char leak_type_code[],install_phase_type_code[];
extern   volatile    unsigned int Leak_limit_time_class[];
extern  unsigned int Leak_Class[];
extern volatile  unsigned long T_yc_hezha ,T_yc_fenzha,T_yc_fenzha_js,T_yc_hezha_js,T_an_fenzha,T_an_fenzha_js;
extern volatile unsigned int  Leak_Cur_disp;

extern unsigned char alarm_value_code[];
extern unsigned char record_value_code[];
extern unsigned char record_time_code[];
extern unsigned char timed_trip_code[];
extern unsigned char over_vol_code[];
extern unsigned char under_vol_code[];
extern unsigned char break_phase_code[];
extern unsigned char rated_current_code[];
extern unsigned char over_current_code[],F_GJ_FUNC ;
extern  const unsigned int D_HV_Array[],D_LV_Array[];
//extern  const unsigned long D_C1_Array[];//20~100各档位1.15倍电流值
//extern  const unsigned long D_C15_Array[];//00,100663894,180000000,280272589,405000000,549881285,720000000,909489981,1125000000};//20~100各档位1.5倍电流值
//extern  const unsigned long D_C19_Array[];//={200,300,400,500,600,700,800,900,950};
//extern  const unsigned int  D_C1H_Array[];//
extern volatile unsigned long H_Cur,H5_Cur,I2,I3;
extern volatile unsigned  long Num_clearall;

extern volatile unsigned long Num_leak_record;
//void hongwai_Send_Data(u8 *buf,u8 len);
extern volatile int Num_leakquit,H_D_V;
extern volatile unsigned int  Leak_Alarm_Value;
extern volatile unsigned int Leak_Cur_disp_temp;
extern  unsigned char ctrlword[5],stateword[5];
extern volatile unsigned char F_Trip,F_Trip1;
extern  unsigned char password_0class[4],password_1class[4],password_2class[4];
extern volatile unsigned char point_trip,F_set_state;
extern volatile unsigned char 	F_trip_dl, F_analog_trip, F_trip_ld,F_trip_sy,F_trip_qy,F_trip_gy ,F_dataalarm_xq,F_trip_xq ,F_trip_gl ,	F_trip_xl,F_data_clear,F_Corr,F_auto_ld;
extern volatile unsigned char  	F_hezha_js,F_fenzha_js,F_an_js;

volatile unsigned char F_re_sta,F_re_sta1,Addr_len,Addr_len1,F_guangbo,F_benji,F_addr;
volatile unsigned char DI0,DI1,DI2,DI3;
volatile unsigned char ctrl_code,cs_data1,ctrl_code1,data_len_temp,cs_data,guozhitao,Addr_array[6],Addr_array1[6], Addr_len,data_len,data_len1,data_len_temp1;
extern unsigned char UART_T_Buf[60],UART_S_Buf[60],F_Dataval1,self_addr_code[6],F_Dataval;
extern volatile signed int I_Array[4],I_Array_xianshi[20],I1_cal_tmp[3],I2_cal_tmp[3];
extern volatile unsigned char tmp_uart_rx[50];
unsigned char  data_array[70];
unsigned char  data_array1[70];


extern unsigned short int V_A_slope[3],V_B_slope[3],V_C_slope[3],L_slope[3],I_A_slope[5],I_B_slope[5],I_C_slope[5],Vol_C_disp[3],Vol_B_disp[3],Vol_A_disp[3],Cur_A_disp[5],Cur_B_disp[5],Cur_C_disp[5],Leak_disp[3];
extern unsigned int Vol_A_temp[3],Vol_B_temp[3],Vol_C_temp[3];
extern volatile unsigned int  Cur_A_temp[7],Cur_B_temp[7],Cur_C_temp[7],Leak_temp[3];


volatile unsigned int Vol_uart_q,Vol_uart_g,UART_Cur_Value;

extern unsigned char F_day_updata,F_yc_hezha,F_yc_fenzha,F_yc;
extern unsigned char  	F_disp_h,F_yc_hezha,F_yc_fenzha,F_an_fenzha;
extern volatile unsigned int  L_Cur,A_Vol,B_Vol,C_Vol,A_Cur,B_Cur,C_Cur,Z_Cur,I_VAL,V_Array[3],V_Array_record[3],V_sample[3];
extern volatile unsigned char max_phase;
extern  volatile unsigned char F_disp_jg;
extern volatile unsigned int Leak_Cur;
extern unsigned int vol_handle(unsigned int value);
extern unsigned int vol_handle_A(unsigned int value);
extern unsigned int vol_handle_B(unsigned int value);
extern unsigned int vol_handle_C(unsigned int value);

extern  unsigned int cur_handle(unsigned int x);
extern unsigned int cur_handle_A(unsigned int x);
extern unsigned int cur_handle_B(unsigned int x);
extern unsigned int cur_handle_C(unsigned int x);
extern  unsigned int cur_cal_handle(unsigned int x);
extern volatile unsigned char D_LCur,TH_LCur,T_run_time_array[5],F_gz,TH_Long_Cur;
extern volatile unsigned char Type_Cur;
extern volatile unsigned int D_Cur;
extern unsigned int leak_handle(unsigned int x);
extern volatile unsigned char point_leak_max,point_leak_min;
extern volatile unsigned char  point_Avol_max,point_Bvol_max,point_Cvol_max;
extern volatile unsigned char  point_Acur_max,point_Bcur_max,point_Ccur_max;
extern volatile unsigned char  point_Avol_min,point_Bvol_min,point_Cvol_min;
extern volatile unsigned char  point_Acur_min,point_Bcur_min,point_Ccur_min;
extern volatile unsigned char point_event_leak,point_event_alarm;
extern volatile unsigned  int point_Leak_record;
extern volatile unsigned char point_event_trip,point_event_trip_24C256,point_event_leak,F_hezha_sta,point_event_self;
extern  unsigned char baud,baud_uart;
extern  unsigned char timed_trip_code[3];
extern  unsigned char Vol_s_T,over_vol_code[2];
extern  unsigned int Vol_g_T,Vol_q_T;
extern  unsigned int Vol_g_T,Vol_q_T;
extern  unsigned char under_vol_code[2];
extern  unsigned char break_phase_code[2];
extern unsigned char remote_trip_time[2],remote_close_time[2],analog_trip_time[2];
extern  unsigned char rated_current_code[3] ;
extern  unsigned char over_current_code[2];
extern volatile unsigned char Leak_record_value,Leak_record_time;
extern volatile signed int Leak_Cur_uart;
extern volatile signed long I_I_Array_xianshi[20],CurA_cal_tmp[5],CurA_cal_tmp_nv[5],CurB_cal_tmp[5],CurB_cal_tmp_nv[5],CurC_cal_tmp[5],CurC_cal_tmp_nv[5],Leak1_temp,Vol1_A_temp,Vol1_B_temp,Vol1_C_temp;

extern volatile signed long CurA400_cal_tmp[5],CurB400_cal_tmp[5],CurC400_cal_tmp[5];
extern volatile signed long CurA630_cal_tmp[5],CurB630_cal_tmp[5],CurC630_cal_tmp[5];
extern volatile signed long CurA800_cal_tmp[5],CurB800_cal_tmp[5],CurC800_cal_tmp[5];
volatile unsigned int rated_cur;
void vol_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned int value);
void cur_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned int value);
void leak_uart_cal_handle(void);
void SD_uart_cal_handle(unsigned char tmp,unsigned char temp,unsigned int value);

extern float Power_factor[3],Active_Pow[3],Total_power[3];

extern void xianshishuju1(unsigned int dat);


 unsigned char TXJZ_start=0;//通讯校准开始标志位0结束，1开始
unsigned char TXJZ_SJ=0;//通讯时间
//unsigned char TXJZ_DY=0;//通讯电压
unsigned char TXJZ_LD=0;//通讯漏电

unsigned char TXJZ_DL_A=0;//通讯电流A
unsigned char TXJZ_DL_B=0;//通讯电流B
unsigned char TXJZ_DL_C=0;//通讯电流C

unsigned char TXJZ_DY_A=0;//通讯电压A
unsigned char TXJZ_DY_B=0;//通讯电压B
unsigned char TXJZ_DY_C=0;//通讯电压C

extern volatile unsigned char F_initial_lcd,F_ld_change_stateword,LEDA_FLAG,Fun_Power_Flag,Fun_Power_Flag1;

extern volatile unsigned char duandian,TH_Long_Cur,F_TB_trip,N_anolog_trip,F_ia,F_ip_3,F_sssj,F_ip,F_anolog_trip,LC_N,F_al1,D_LCur,TH_LCur,Vol_ch ,F_trip_QL;

extern volatile unsigned char F_sssj;
extern void factor_first_init(unsigned char tmp);
extern void factors_init(void);
extern volatile unsigned short int I1_A_slope[2],I1_A_slope_nv[2],I1_B_slope[2],I1_B_slope_nv[2],I1_C_slope[2],I1_C_slope_nv[2];	
extern volatile unsigned int Leak_Cur_disp_temp,V_Array_disp[3];
extern volatile signed int I_A_factor,V_A_factor,I_B_factor,V_B_factor,I_C_factor,V_C_factor,V1_slope[3],Power_Add[3],Power_Add_flag[3];
extern volatile unsigned char F_sssj,F_shishichaxun;

extern unsigned char shangdian,LD_hezha,DY_hezha,DL_hezha;
extern volatile unsigned	char F_trip_QX;
extern volatile unsigned short int L1_slope;




  
//#ifdef EN_USART3_RX   	//如果使能了接收
	

//接收缓存区 	
u8 RS485_RX_BUF[64];  	//接收缓冲,最大64个字节.
//接收到的数据长度
u8 RS485_RX_CNT=0;   		
UART_HandleTypeDef huart1;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 2400;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_EVEN;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = RS485_TX_Pin|RS485_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, RS485_TX_Pin|RS485_RX_Pin);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart == &huart1)
    {
        u8 tmp = tmp_uart_rx[0];
        if (F_re_sta == 0) // 无开始标志，等待帧头
        {
            if (tmp != 0x68)
            {
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return; // 若非帧头且未置接收标志则不接收
            }
            if (tmp == 0x68) // 帧头且无开始标志，则开始接收并置标志
            {
                data_len_temp = 0;
                F_re_sta = 2;
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return;
            }
        }
        else if (F_re_sta == 2) // 开始接收地址数据
        {

            if (Addr_len == 6)
            {
                if (tmp == 0x68)
                {
                    Addr_len = 0;
                    F_re_sta = 3;
                    HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                    return;
                }
                else
                {
                    F_re_sta = 0;
                    Addr_len = 0;
                    HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                    return;
                }
            }
            else
            {
                Addr_array[Addr_len] = tmp;
                Addr_len++;
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return;
            }
        }
        else if (F_re_sta == 3) // 接收控制码
        {
            ctrl_code = tmp;
            if (ctrl_code <= 0x80) // 主站发出的命令帧  80 为保留
            {
                F_re_sta = 4;
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return;
            }
            else
            {
                F_re_sta = 0;
                // ctrl_code = 0;
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return;
            }
        }
        else if (F_re_sta == 4) // 接收数据长度
        {
            data_len = tmp;
            if (data_len <= 208)
            {
                if (data_len == 0)
                {
                    F_re_sta = 6;
                    HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                    return;
                }
                else
                {
                    F_re_sta = 5;
                    HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                    return;
                }
            }
            else
            {
                F_re_sta = 0;
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return;
            }
        }
        else if (F_re_sta == 5) // 开始接收数据
        {
            if (data_len > 0)
            {
                data_array[data_len_temp] = tmp;
                data_len_temp++;

                if (data_len_temp == data_len)
                {
                    F_re_sta = 6;
                }
                if (data_len_temp > data_len) // 什么意思呢
                {
                    // clear_uart_sta();
                    F_re_sta = 0;
                    HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                    return;
                }
                //				if(data_len_temp>50)
                //				{
                //					clear_uart_sta();
                //					HAL_UART_Receive_IT(&huart1,(uint8_t*)tmp_uart_rx,1);
                //					return;
                //				}
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return;
            }
        }
        else if (F_re_sta == 6) // 接收校验码
        {
            cs_data = tmp;
            F_re_sta = 7;
            HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
            return;
        }
        else if (F_re_sta == 7) // 接收帧尾
        {
            if (tmp == 0x16)
            {
                // F_re_sta = 8;
                F_re_sta = 0;
                F_Dataval = 1;
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return;
            }
            else
            {
                F_re_sta = 0;
                HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
                return;
            }
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) // 2022.5.9新增
{
    HAL_StatusTypeDef ERR;
    int i = 0;
    if (huart->Instance == USART3)
    {
        __HAL_UNLOCK(&huart1);
        ERR = HAL_UART_Receive_IT(&huart1, (uint8_t *)&tmp_uart_rx, 1); // 再开启接收中断
        if (ERR != HAL_OK)
        { // 测试
            while (i < 1000000)
            {
                i++;
                ;
            }
        }
    }
}

// #endif

#ifdef EN_USART2_RX // 如果使能了接收

////接收缓存区
// u8 hongwai_RX_BUF[64];  	//接收缓冲,最大64个字节.
////接收到的数据长度
// u8 hongwai_RX_CNT=0;
//  void USART2_IRQHandler(void)
//{
//	u8 tmp;
//
//  	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收到数据
//	{
//
//		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//		tmp =USART_ReceiveData(USART2);	//读取接收到的数据
//
//		if(F_re_sta==0)  // 无开始标志，等待帧头
//		{
//			if(tmp!=0x68) return;//若非帧头且未置接收标志则不接收
//			if(tmp==0x68)		  //帧头且无开始标志，则开始接收并置标志
//			{
//				data_len_temp = 0;
//				F_re_sta = 2;
//				//F_Dataval = 1;
//				return;
//			}
//		}
//		else if(F_re_sta==2) //开始接收地址数据
//		{
//
//			if(Addr_len==6)
//			{
//				if(tmp==0x68)
//				{
//					Addr_len = 0;
//					F_re_sta=3;
//					return;
//				}
//				else
//				{
//					F_re_sta =0;
//					Addr_len =0 ;
//					return;
//				}
//			}
//			else
//			{
//				Addr_array[Addr_len] = tmp;
//				Addr_len++;
//				return;
//			}
//		}
//		else if(F_re_sta==3) //接收控制码
//		{
//			ctrl_code = tmp;
//			if(ctrl_code<=0x80)  //主站发出的命令帧  80 为保留
//			{
//				F_re_sta=4;
//				return;
//			}
//			else
//			{
//				F_re_sta= 0;
//				//ctrl_code = 0;
//				return;
//			}
//		}
//		else if(F_re_sta==4)//接收数据长度
//		{
//			data_len = 	tmp;
//			if(data_len<=200)
//			{
//				if(data_len==0)
//				{
//					F_re_sta = 6;
//					return;
//				}
//				else
//				{
//					F_re_sta = 5;
//					return;
//				}
//			}
//			else
//			{
//				F_re_sta = 0;
//				return;
//			}
//		}
//		else if(F_re_sta==5)	  //开始接收数据
//		{
//			if(data_len>0)
//			{
//				data_array[data_len_temp] = tmp;
//				data_len_temp++;
//
//				if(data_len_temp==data_len)
//				{
//					F_re_sta = 6;
//				}
//				if(data_len_temp>data_len)  //什么意思呢
//				{
//					clear_uart_sta();
//					return;
//				}
//				if(data_len_temp>50)
//				{
//					clear_uart_sta();
//					return;
//				}
//				return;
//			}
//		}
//		else if(F_re_sta==6)//接收校验码
//		{
//			cs_data = tmp;
//			F_re_sta = 7;
//			return;
//		}
//		else if(F_re_sta ==7)//接收帧尾
//		{
//			if(tmp == 0x16)
//			{
//				//F_re_sta1 = 8;
//				F_re_sta = 0;
//				F_Dataval1 = 1;
//				return;
//			}
//		}
//	}
// }
//	}
#endif

unsigned char frame_check(void) // 是帧检查不是框架检查
{
    unsigned char i, Addr_err, CHECK;
    Addr_err = 0;
    CHECK = 0;
    for (i = 0; i < 6; i++)
    {
        if (Addr_array[i] != 0x99) // 广播不要求从站应答   地址域传输低字节在前高字节在后
            Addr_err++;
    }
    if (Addr_err == 0)
        F_guangbo = 1; // 如果都是99则广播
    else
    {
        Addr_err = 0;
        for (i = 0; i < 6; i++)
        {
            if (Addr_array[i] != self_addr_code[i]) // 如果对不上本机地址就ADDR_ERR++
                Addr_err++;
        }
        if (Addr_err == 0)
            F_benji = 1; // 如果都对上了就F_BENJI置一
        else
        {
            Addr_err = 0;
            for (i = 0; i < 6; i++)
            {
                if (Addr_array[i] != 0xAA)
                    Addr_err++;
            }
            if (Addr_err == 0)
                F_addr = 1; // 读通信地址
            else
            {
                return 0x01;
            }
        }
    }
    CHECK = 0;
    for (i = 0; i < 6; i++)
    {
        CHECK = Addr_array[i] + CHECK;
    }
    CHECK = CHECK + 0x68 + 0x68 + data_len + ctrl_code; // 从第一个起始符开始到校验码之前所有数据的模256和
    for (i = 0; i < data_len; i++)
        CHECK = CHECK + data_array[i];
    // mrnow_tmp1 = CHECK;
    // put2char(CHECK);
    // put2char(cs_data);

    if (CHECK != cs_data) // 如果对不上则返回  02  校验错误
        return 0x02;
    else
    {
        for (i = 0; i < data_len; i++)
        {
            data_array[i] = data_array[i] - 0x33; // 数据进行减0x33处理
        }
        return 0;
    }
}

void format_uart_t_buf(void) // 数据排版？？？
{
    unsigned char i;
    for (i = 0; i < 60; i++)
    {
        UART_T_Buf[i] = 0;
    }
}

void clear_uart_sta1(void)
{
    unsigned char i;
    for (i = 0; i < 6; i++)
        Addr_array1[i] = 0;         // 地址
    Addr_len1 = 0;                  // 地址长度
    data_len1 = data_len_temp1 = 0; // 数据长度
    cs_data1 = 0;                   // 校验码
    ctrl_code1 = 0;                 // 控制码
    F_re_sta1 = 0;                  // 从头开始接收
}
void clear_uart_sta(void)
{
    unsigned char i;
    for (i = 0; i < 6; i++)
        Addr_array[i] = 0;        // 地址
    Addr_len = 0;                 // 地址长度
    data_len = data_len_temp = 0; // 数据长度
    cs_data = 0;                  // 校验码
    ctrl_code = 0;                // 控制码
    F_re_sta = 0;                 // 从头开始接收
    HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
}

void Uart_prepare(unsigned char tmp)
{
    unsigned char i;
    format_uart_t_buf();                  // 清除要写的东西
    UART_T_Buf[0] = UART_T_Buf[7] = 0x68; // 1 2 3 4 5 6 都是地址码
    for (i = 0; i < 6; i++)
    {
        UART_T_Buf[i + 1] = self_addr_code[i]; // 写地址的六位
    }
    if (tmp == 0)
    {
        UART_T_Buf[8] = ctrl_code + 0x80; // 控制码80 从站发出应答帧    要写的东西   把接收到的控制码加上0x80再传送回去
        for (i = 0; i < 4; i++)
            UART_T_Buf[10 + i] = data_array[i] + 0x33;
    }
    if (tmp == 1)
    {
        UART_T_Buf[8] = ctrl_code + 0xC0; // C0从站异常应答帧
    }
}
void Uart_prepare1(unsigned char tmp)
{
    unsigned char i;
    format_uart_t_buf();                  // 清除要写的东西
    UART_T_Buf[0] = UART_T_Buf[7] = 0x68; // 1 2 3 4 5 6 都是地址码
    for (i = 0; i < 6; i++)
    {
        UART_T_Buf[i + 1] = self_addr_code[i]; // 写地址的六位
    }
    if (tmp == 0)
    {
        UART_T_Buf[8] = ctrl_code + 0x80; // 控制码80 从站发出应答帧
    }
    if (tmp == 1)
    {
        UART_T_Buf[8] = ctrl_code + 0xC0; // C0从站异常应答帧
    }
}

void Read_response(unsigned char len, unsigned char *array_tmp)
{

    unsigned char i, cs_temp;
    cs_temp = 0;
    Uart_prepare(0); // 从站正常应答帧
    UART_T_Buf[9] = 4 + len;

    for (i = 0; i < len; i++)
    {
        UART_T_Buf[14 + i] = array_tmp[i] + 0x33; // 真正的数据部分加33处理
    }

    for (i = 0; i < (14 + len); i++) // 校验码处理
    {
        cs_temp = UART_T_Buf[i] + cs_temp;
    }
    UART_T_Buf[14 + len] = cs_temp;
    UART_T_Buf[15 + len] = 0x16;
    // 20150202北京测试修改
    //	for(i=0;i<4;i++)
    //	put2char(0xFE);

    //	for(i=0;i<(16+len);i++)
    //	put2char(UART_T_Buf[i]);
    for (i = 0; i < 4; i++)
    {
        UART_S_Buf[i] = 0xFE;
    }
    if (F_Dataval == 1)
    {
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_S_Buf, 4, 0xffff);
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_T_Buf, 16 + len, 0xffff);
        // RS485_Send_Data(UART_S_Buf,4);
        // RS485_Send_Data(UART_T_Buf,16+len);
        //		UART_T_Buf[0]=0X00
        //
        //		//RS485_Send_Data(UART_T_Buf,3);
    }
    if (F_Dataval1 == 1)
    {
        // hongwai_Send_Data(UART_T_Buf,16+len);
    }
}
void Read_response1(unsigned char len, unsigned char *array_tmp)
{

    unsigned char i, cs_temp;
    cs_temp = 0;
    Uart_prepare1(0); // 从站正常应答帧
    UART_T_Buf[9] = len;

    for (i = 0; i < len; i++)
    {
        UART_T_Buf[10 + i] = array_tmp[i] + 0x33; // 真正的数据部分加33处理
    }

    for (i = 0; i < 16; i++) // 校验码处理
    {
        cs_temp = UART_T_Buf[i] + cs_temp;
    }
    UART_T_Buf[16] = cs_temp;
    UART_T_Buf[17] = 0x16;
    // 20150202北京测试修改
    //	for(i=0;i<4;i++)
    //	put2char(0xFE);

    //	for(i=0;i<(16+len);i++)
    //	put2char(UART_T_Buf[i]);
    for (i = 0; i < 4; i++)
    {
        UART_S_Buf[i] = 0xFE;
    }
    if (F_Dataval == 1)
    {
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_S_Buf, 4, 0xffff);
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_T_Buf, 18, 0xffff);
        // RS485_Send_Data(UART_S_Buf,4);
        // RS485_Send_Data(UART_T_Buf,18);
        //		UART_T_Buf[0]=0X00
        //
        //		//RS485_Send_Data(UART_T_Buf,3);
    }
    if (F_Dataval1 == 1)
    {
        // hongwai_Send_Data(UART_T_Buf,18);
    }
}

/***************************************
    广播校时
***************************************/
void Broadcasting_time(void)
{
    unsigned char i, array_temp[6];

    for (i = 0; i < 6; i++)
    {
        array_temp[i] = data_array[5 - i];
        // putchar(array_temp[i]);
    }
    //	array_temp[0]=17;
    sdatestructure.Year = array_temp[0];
    sdatestructure.Month = array_temp[1];
    sdatestructure.Date = array_temp[2];
    stimestructure.Hours = array_temp[3];
    stimestructure.Minutes = array_temp[4];
    stimestructure.Seconds = array_temp[5];
    RTC_Set_Time(array_temp[3], array_temp[4], array_temp[5]);
    RTC_Set_Date(array_temp[0], array_temp[1], array_temp[2]);
    // ds1302_write_time_uart(array_temp2[0],array_temp[1],array_temp[2],array_temp[3],array_temp[4],array_temp[5]);   //写时间？？？？？？？？
    F_day_updata = 1;
}

unsigned char Password_verification(unsigned char tmp) // 密码验证
{

    if (tmp == 0)
    {
        if ((password_0class[0] == data_array[4]) && (password_0class[1] == data_array[5]) && (password_0class[2] == data_array[6]) && (password_0class[3] == data_array[7]))
        {
            return 0;
        }
        else if ((password_1class[0] == data_array[4]) && (password_1class[1] == data_array[5]) && (password_1class[2] == data_array[6]) && (password_1class[3] == data_array[7]))
        {
            return 1;
        }
        else if ((password_2class[0] == data_array[4]) && (password_2class[1] == data_array[5]) && (password_2class[2] == data_array[6]) && (password_2class[3] == data_array[7]))
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }
    if (tmp == 1)
    {
        if ((password_0class[0] == data_array[0]) && (password_0class[1] == data_array[1]) && (password_0class[2] == data_array[2]) && (password_0class[3] == data_array[3]))
        {
            return 0;
        }
        else if ((password_1class[0] == data_array[0]) && (password_1class[1] == data_array[1]) && (password_1class[2] == data_array[2]) && (password_1class[3] == data_array[3]))
        {
            return 1;
        }
        else if ((password_2class[0] == data_array[0]) && (password_2class[1] == data_array[1]) && (password_2class[2] == data_array[2]) && (password_2class[3] == data_array[3]))
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }
    return 3;
}

void WRITE_DATA_NOMAL(void)
{
    unsigned char i, cs_temp;
    Uart_prepare(0);      // 写到控制码部分
    UART_T_Buf[9] = 0x00; // 数据长度  正常应答帧  正常应答帧为什么长度为00  数据长度结束之后直接就是结束符
    cs_temp = 0;
    for (i = 0; i < 9; i++)
    {
        cs_temp = UART_T_Buf[i] + cs_temp;
    }
    UART_T_Buf[10] = cs_temp;
    UART_T_Buf[11] = 0x16;
    // 20150202北京测试修改
    //	for(i=0;i<4;i++)
    //	put2char(0xFE);
    //	for(i=0;i<12;i++)
    //	put2char(UART_T_Buf[i]);
    for (i = 0; i < 4; i++)
    {
        UART_S_Buf[i] = 0xFE;
    }
    if (F_Dataval == 1)
    {
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_S_Buf, 4, 0xffff);
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_T_Buf, 12, 0xffff);
        // RS485_Send_Data(UART_S_Buf,4);
        // RS485_Send_Data(UART_T_Buf,12);
    }
    if (F_Dataval1 == 1)
    {
        // hongwai_Send_Data(UART_T_Buf,12);
    }

    //	  //RS485_Send_Data(UART_T_Buf,12);
}

void ERR_data_sent(unsigned char reason)
{
    unsigned char i, cs_temp;
    cs_temp = 0;
    Uart_prepare(1);         // 从站异常应答帧准备
    UART_T_Buf[9] = 0x01;    // 数据长度
    UART_T_Buf[10] = reason; // 第十位为原因
    for (i = 0; i < 11; i++)
    {
        cs_temp = UART_T_Buf[i] + cs_temp; // 是一位为校验码
    }
    UART_T_Buf[11] = cs_temp;
    UART_T_Buf[12] = 0x16;
    // 20150202北京测试修改
    //	for(i=0;i<4;i++)
    //	put2char(0xFE);

    //	for(i=0;i<13;i++)
    //	put2char(UART_T_Buf[i]);
    //	//RS485_Send_Data(UART_T_Buf,13);
    for (i = 0; i < 4; i++)
    {
        UART_S_Buf[i] = 0xFE;
    }
    if (F_Dataval == 1)
    {
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_S_Buf, 4, 0xffff);
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_T_Buf, 13, 0xffff);
        // RS485_Send_Data(UART_S_Buf,4);
        // RS485_Send_Data(UART_T_Buf,13);
    }
    if (F_Dataval1 == 1)
    {
        // hongwai_Send_Data(UART_T_Buf,13);
    }
}

/************************************校准读取2022.4.28新加***********************/
// 电流AD值读取
unsigned char Read_DL_AD_Value(unsigned char xiangwei_tmp, unsigned char dian_tmp) // xiangwei_tmp=DI2；dian_tmp=DI0
{
    //	if(((vol_handle_A(V_Array[0]))<100)||((vol_handle_B(V_Array[1]))<100)||((vol_handle_C(V_Array[2]))<100))  //没电压
    //{
    //	unsigned char array_temp[8];
    //	  unsigned char lenth;
    //
    //	if(xiangwei_tmp==1)//A相位
    //	{
    //		if(dian_tmp==0)//0点
    //		{
    //		      DectoBCD(array_temp, CurA_cal_tmp_nv[0],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}
    //		else if(dian_tmp==1)
    //		{
    //		      DectoBCD(array_temp, CurA_cal_tmp_nv[1],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}

    //	}
    //	else if(xiangwei_tmp==2)//B相位
    //	{
    //		if(dian_tmp==0)//0点
    //		{
    //		      DectoBCD(array_temp, CurB_cal_tmp_nv[0],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}
    //		else if(dian_tmp==1)
    //		{
    //		      DectoBCD(array_temp, CurB_cal_tmp_nv[1],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}

    //	}
    //	else if(xiangwei_tmp==3)//C相位
    //	{
    //		if(dian_tmp==0)//0点
    //		{
    //		      DectoBCD(array_temp, CurC_cal_tmp_nv[0],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}
    //		else if(dian_tmp==1)
    //		{
    //		      DectoBCD(array_temp, CurC_cal_tmp_nv[1],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}

    //	}

    //	else
    //	{
    //		ERR_data_sent(ERR_NO_REQUEST);  //没回应
    //		return 1;
    //	}
    //	Read_response(lenth,array_temp);    //加上数据长度再加上数据
    //	return 0;
    //}
    //	else
    //	{
    unsigned char array_temp[8];
    unsigned char lenth;

    if (xiangwei_tmp == 1) // A相位
    {
        if (dian_tmp == 0) // 0点
        {
            DectoBCD(array_temp, CurA_cal_tmp[0], 3); // 十进制转换成二进制转换成值
            lenth = 3;                                // 数据长达
        }
        else if (dian_tmp == 1)
        {
            DectoBCD(array_temp, CurA_cal_tmp[1], 3); // 十进制转换成二进制转换成值
            lenth = 3;                                // 数据长达
        }
    }
    else if (xiangwei_tmp == 2) // B相位
    {
        if (dian_tmp == 0) // 0点
        {
            DectoBCD(array_temp, CurB_cal_tmp[0], 3); // 十进制转换成二进制转换成值
            lenth = 3;                                // 数据长达
        }
        else if (dian_tmp == 1)
        {
            DectoBCD(array_temp, CurB_cal_tmp[1], 3); // 十进制转换成二进制转换成值
            lenth = 3;                                // 数据长达
        }
    }
    else if (xiangwei_tmp == 3) // C相位
    {
        if (dian_tmp == 0) // 0点
        {
            DectoBCD(array_temp, CurC_cal_tmp[0], 3); // 十进制转换成二进制转换成值
            lenth = 3;                                // 数据长达
        }
        else if (dian_tmp == 1)
        {
            DectoBCD(array_temp, CurC_cal_tmp[1], 3); // 十进制转换成二进制转换成值
            lenth = 3;                                // 数据长达
        }
    }

    else
    {
        ERR_data_sent(ERR_NO_REQUEST); // 没回应
        return 1;
    }
    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
    //}
}

// 电流斜率值读取
unsigned char Read_DL_XL_Value(unsigned char xiangwei_tmp, unsigned char dian_tmp) // xiangwei_tmp=DI2；dian_tmp=DI0
{
    //	if(((vol_handle_A(V_Array[0]))<100)||((vol_handle_B(V_Array[1]))<100)||((vol_handle_C(V_Array[2]))<100))  //没电压
    //{
    //	unsigned char array_temp[8];
    //	  unsigned char lenth;
    //
    //	if(xiangwei_tmp==1)//A相位
    //	{

    //		if(dian_tmp==0)//0点
    //		{
    //		      DectoBCD(array_temp, I1_A_slope_nv[0],3);  //十进制转换成二进制转换成值

    //					lenth = 3;  //数据长达
    //		}
    //		else if(dian_tmp==1)
    //		{
    //		      DectoBCD(array_temp, I1_A_slope_nv[1],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}

    //	}
    //	else if(xiangwei_tmp==2)//B相位
    //	{
    //		if(dian_tmp==0)//0点
    //		{
    //		      DectoBCD(array_temp, I1_B_slope_nv[0],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}
    //		else if(dian_tmp==1)
    //		{
    //		      DectoBCD(array_temp, I1_B_slope_nv[1],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}

    //	}
    //	else if(xiangwei_tmp==3)//C相位
    //	{
    //		if(dian_tmp==0)//0点
    //		{
    //		      DectoBCD(array_temp, I1_C_slope_nv[0],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}
    //		else if(dian_tmp==1)
    //		{
    //		      DectoBCD(array_temp, I1_C_slope_nv[1],3);  //十进制转换成二进制转换成值
    //					lenth = 3;  //数据长达
    //		}

    //	}

    //	else
    //	{
    //		ERR_data_sent(ERR_NO_REQUEST);  //没回应
    //		return 1;
    //	}
    //	Read_response(lenth,array_temp);    //加上数据长度再加上数据
    //	return 0;
    //}
    //
    //
    //	else
    //	{
    unsigned char array_temp[8];
    unsigned char lenth;

    if (xiangwei_tmp == 1) // A相位
    {

        if (dian_tmp == 0) // 0点
        {
            DectoBCD(array_temp, I1_A_slope[0], 3); // 十进制转换成二进制转换成值

            lenth = 3; // 数据长达
        }
        else if (dian_tmp == 1)
        {
            DectoBCD(array_temp, I1_A_slope[1], 3); // 十进制转换成二进制转换成值
            lenth = 3;                              // 数据长达
        }
    }
    else if (xiangwei_tmp == 2) // B相位
    {
        if (dian_tmp == 0) // 0点
        {
            DectoBCD(array_temp, I1_B_slope[0], 3); // 十进制转换成二进制转换成值
            lenth = 3;                              // 数据长达
        }
        else if (dian_tmp == 1)
        {
            DectoBCD(array_temp, I1_B_slope[1], 3); // 十进制转换成二进制转换成值
            lenth = 3;                              // 数据长达
        }
    }
    else if (xiangwei_tmp == 3) // C相位
    {
        if (dian_tmp == 0) // 0点
        {
            DectoBCD(array_temp, I1_C_slope[0], 3); // 十进制转换成二进制转换成值
            lenth = 3;                              // 数据长达
        }
        else if (dian_tmp == 1)
        {
            DectoBCD(array_temp, I1_C_slope[1], 3); // 十进制转换成二进制转换成值
            lenth = 3;                              // 数据长达
        }
    }

    else
    {
        ERR_data_sent(ERR_NO_REQUEST); // 没回应
        return 1;
    }
    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
    //}
}
// 读电压斜率
unsigned char Read_DY_XL_Value(unsigned char xiangwei_tmp) // xiangwei_tmp=DI2
{
    unsigned char array_temp[8];
    unsigned char lenth;

    if (xiangwei_tmp == 1) // A相位
    {

        DectoBCD(array_temp, V1_slope[0], 3); // 十进制转换成二进制转换成值
        lenth = 3;                            // 数据长达
    }
    else if (xiangwei_tmp == 2) // B相位
    {

        DectoBCD(array_temp, V1_slope[1], 3); // 十进制转换成二进制转换成值
        lenth = 3;                            // 数据长达
    }
    else if (xiangwei_tmp == 3) // C相位
    {

        DectoBCD(array_temp, V1_slope[2], 3); // 十进制转换成二进制转换成值
        lenth = 3;                            // 数据长达
    }

    else
    {
        ERR_data_sent(ERR_NO_REQUEST); // 没回应
        return 1;
    }
    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
}

// 读漏电斜率
unsigned char Read_LD_XL_Value() //
{
    unsigned char array_temp[8];
    unsigned char lenth;

    DectoBCD(array_temp, L1_slope, 3); // 十进制转换成二进制转换成值
    lenth = 3;                         // 数据长达

    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
}

/************************************瞬动校准读取***********************/
// 瞬动AD值读取
unsigned char Read_SD_AD_Value(unsigned char fact_tmp, unsigned char lenth) // fact_tmp为DI0：表示第几个点
{
    unsigned char array_temp[8];
    if ((fact_tmp >= 0) && (fact_tmp <= 4))
    {
        if (Type_Cur == 0)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_IV_AD_value[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_IV_AD_value[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_IV_AD_value[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_IV_AD_value[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_IV_AD_value[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
        }
        if (Type_Cur == 1)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_I_AD_value[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                      // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_I_AD_value[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                      // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_I_AD_value[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                      // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_I_AD_value[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                      // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_I_AD_value[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                      // 数据长达
            }
        }
        if (Type_Cur == 2)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_II_AD_value[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_II_AD_value[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_II_AD_value[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_II_AD_value[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_II_AD_value[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                       // 数据长达
            }
        }
        if (Type_Cur == 3)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_III_AD_value[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                        // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_III_AD_value[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                        // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_III_AD_value[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                        // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_III_AD_value[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                        // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_III_AD_value[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                        // 数据长达
            }
        }
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST); // 没回应
        return 1;
    }
    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
}

// 瞬动斜率值读取
unsigned char Read_SD_Slope_Value(unsigned char fact_tmp, unsigned char lenth) // fact_tmp为DI0：表示第几个点
{
    unsigned char array_temp[8];
    if ((fact_tmp >= 0) && (fact_tmp <= 4))
    {
        if (Type_Cur == 0)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_IV_slope[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_IV_slope[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_IV_slope[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_IV_slope[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_IV_slope[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
        }
        if (Type_Cur == 1)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_I_slope[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_I_slope[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_I_slope[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_I_slope[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_I_slope[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
        }
        if (Type_Cur == 2)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_II_slope[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_II_slope[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_II_slope[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_II_slope[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_II_slope[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
        }
        if (Type_Cur == 3)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_III_slope[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_III_slope[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_III_slope[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_III_slope[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_III_slope[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
        }
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST); // 没回应
        return 1;
    }
    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
}

// 瞬动电流值读取
unsigned char Read_SD_Value(unsigned char fact_tmp, unsigned char lenth) // fact_tmp为DI0：表示第几个点
{
    unsigned char array_temp[8];
    if ((fact_tmp >= 0) && (fact_tmp <= 4))
    {
        if (Type_Cur == 0)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
        }
        if (Type_Cur == 1)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_I_Value[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_I_Value[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_I_Value[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_I_Value[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_I_Value[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                   // 数据长达
            }
        }
        if (Type_Cur == 2)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_II_Value[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_II_Value[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_II_Value[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_II_Value[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_II_Value[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                    // 数据长达
            }
        }
        if (Type_Cur == 3)
        {
            if (fact_tmp == 0)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[0], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 1)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[1], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 2)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[2], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 3)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[3], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
            if (fact_tmp == 4)
            {
                DectoBCD(array_temp, DLS_Cur_III_Value[4], 3); // 十进制转换成二进制转换成值
                lenth = 3;                                     // 数据长达
            }
        }
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST); // 没回应
        return 1;
    }
    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
}

/***************************************
    读电压  XXX.X  2  BCD
***************************************/
unsigned char Read_variable_vol(unsigned char fact_tmp, unsigned char lenth) // fact_tmp为DI1
{
    unsigned char array_temp[8];
    if ((fact_tmp >= 1) && (fact_tmp <= 3)) // 读ABC三相某一项电压值
    {
        if (fact_tmp == 1)
        {
            DectoBCD(array_temp, (vol_handle_A(V_Array[0]) * 10), 2); // 十进制转换成二进制转换成电压值
            lenth = 2;                                                // 数据长达
        }
        if (fact_tmp == 2)
        {
            DectoBCD(array_temp, (vol_handle_B(V_Array[1]) * 10), 2); // 十进制转换成二进制转换成电压值
            lenth = 2;                                                // 数据长达
        }
        if (fact_tmp == 3)
        {
            DectoBCD(array_temp, (vol_handle_C(V_Array[2]) * 10), 2); // 十进制转换成二进制转换成电压值
            lenth = 2;                                                // 数据长达
        }
    }
    else if (fact_tmp == 0xFF) // 读三个电压值
    {
        DectoBCD(&array_temp[0], (vol_handle_A(V_Array[0]) * 10), 2);
        DectoBCD(&array_temp[2], (vol_handle_B(V_Array[1]) * 10), 2);
        DectoBCD(&array_temp[4], (vol_handle_C(V_Array[2]) * 10), 2);
        lenth = 6;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST); // 没回应
        return 1;
    }
    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
}

/***************************************
    读电流  XXXXX.X  3  BCD
***************************************/
unsigned char Read_variable_cur(unsigned char fact_tmp, unsigned char lenth) // fact_tmp为DI1
{
    unsigned char array_temp[12];
    if ((fact_tmp >= 1) && (fact_tmp <= 3))
    {
        if (fact_tmp == 1)
        {
            DectoBCD(array_temp, (cur_handle_A(I_Array_xianshi[fact_tmp - 1]) * 10), 3);
            lenth = 3;
        }
        else if (fact_tmp == 2)
        {
            DectoBCD(array_temp, (cur_handle_B(I_Array_xianshi[fact_tmp - 1]) * 10), 3);
            lenth = 3;
        }
        else if (fact_tmp == 3)
        {
            DectoBCD(array_temp, (cur_handle_C(I_Array_xianshi[fact_tmp - 1]) * 10), 3);
            lenth = 3;
        }
    }
    else if (fact_tmp == 0xFF)
    {
        DectoBCD(&array_temp[0], (cur_handle_A(I_Array_xianshi[0]) * 10), 3);
        DectoBCD(&array_temp[3], (cur_handle_B(I_Array_xianshi[1]) * 10), 3);
        DectoBCD(&array_temp[6], (cur_handle_C(I_Array_xianshi[2]) * 10), 3);
        lenth = 9;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp); // 加上数据长度再加上数据
    return 0;
}
void Uart_data_propare(void)
{
    if (isfenzha == 0)
    {
        Leak_Cur_uart = 0;
    }
    else
    {
        Leak_Cur_uart = Leak_Cur_disp;
    }
}
/***************************************
    读剩余电流  XX  1  BIN  /  XXXX  2  BCD
***************************************/
unsigned char Read_variable_leak(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[5];
    // max_phase = 0x01;
    if (fact_tmp == 0x00) // 00 就是剩余电流最大相
    {
        array_temp[0] = max_phase;
        lenth = 1;
    }
    else if (fact_tmp == 0x01) // 当前剩余电流值
    {
        //		Uart_data_propare();
        //		DectoBCD(&array_temp[0],Leak_Cur_uart,2);
        DectoBCD(&array_temp[0], (leak_handle(Leak_Cur_disp_temp)), 2);
        lenth = 2;
    }
    else if (fact_tmp == 0xFF) //   //当前剩余电流值及最大相
    {
        //		Uart_data_propare();
        array_temp[0] = max_phase;
        // array_temp[0] = 0x01;
        //		DectoBCD(&array_temp[1],Leak_Cur_uart,2);
        DectoBCD(&array_temp[0], (leak_handle(Leak_Cur_disp_temp)), 2);
        lenth = 3;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp);
    return 0;
}

/***************************************
    读剩余电流档位    XXXX  2  BCD
***************************************/
unsigned char Read_variable_leak_class(unsigned char fact_tmp, unsigned char lenth)
{
    unsigned char array_temp[5];
    if (fact_tmp == 1)
    {
        DectoBCD(&array_temp[0], Leak_Class[D_LCur], 2);
        lenth = 2;
    }
    else if (fact_tmp == 2)
    {
        DectoBCD(&array_temp[0], Leak_limit_time_class[TH_LCur], 2);
        lenth = 2;
    }

    else if (fact_tmp == 0xff)
    {
        DectoBCD(&array_temp[0], Leak_Class[D_LCur], 2);
        DectoBCD(&array_temp[2], Leak_limit_time_class[TH_LCur], 2);
        lenth = 4;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp);
    return 0;
}

/***************************************
    读数据清零总次数   XXXXXX  3  BCD
***************************************/
unsigned char Read_num_dataclear(void)
{
    unsigned char lenth, array_temp[8];
    int Addr_factor;
    lenth = Lenth_clear_num;
    Addr_factor = Addr_clear_num;
    // EEPROM_R(array_temp,Addr_factor,lenth,0);
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
    return 0;
}

/***************************************
    读跳闸次数   XXXX  2  BCD
    00 总跳闸次数 01 闭锁性跳闸次数 02 剩余电流保护跳闸次数  03 电流保护跳闸次数
    04 电压保护跳闸次数 05 手动闭锁跳闸次数  06 缺零保护跳闸次数 07 试验跳闸次数（定时、远程、按键）
    FF 以上所有

***************************************/
unsigned char Read_num_trip(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[20];
    int Addr_factor;
    Addr_factor = 0;
    if (fact_tmp == 0)
    {
        lenth = Lenth_trip_num; // 总跳闸次数
        Addr_factor = Addr_trip_num;
    }
    else if (fact_tmp == 1) // 剩余电流闭锁跳闸
    {
        lenth = Lenth_close_num;
        Addr_factor = Addr_close_num;
    }
    else if (fact_tmp == 2) // 剩余电流保护跳闸
    {
        lenth = Lenth_leak_num;
        Addr_factor = Addr_leak_num;
    }
    else if (fact_tmp == 3) // 过载保护跳闸
    {
        lenth = Lenth_current_num;
        Addr_factor = Addr_current_num;
    }
    else if (fact_tmp == 4)
    {
        lenth = Lenth_vol_num;
        Addr_factor = Addr_vol_num; // 过压保护跳闸次数
    }
    else if (fact_tmp == 5)
    {
        lenth = Lenth_hand_num;
        Addr_factor = Addr_hand_num; // 手动闭锁跳闸
    }
    else if (fact_tmp == 6)
    {
        lenth = Lenth_zero_num;
        Addr_factor = Addr_zero_num; // 缺零保护
    }
    else if (fact_tmp == 7)
    {
        lenth = Lenth_test_num;
        Addr_factor = Addr_test_num; // 试验跳闸
    }

    else if (fact_tmp == 8)
    {
        lenth = Lenth_2D_num;
        Addr_factor = Addr_2D_num; // 短路短延时
    }
    else if (fact_tmp == 9)
    {
        lenth = Lenth_3D_num;
        Addr_factor = Addr_3D_num; // 短路瞬时
    }
    else if (fact_tmp == 0x0A)
    {
        lenth = Lenth_LD_up_num;
        Addr_factor = Addr_leakover_num; // 欠压保护跳闸次数
    }
    else if (fact_tmp == 0x0B)
    {
        lenth = Lenth_AJ_sy_num;
        Addr_factor = Addr_leakprotect_num; // 缺相保护跳闸次数
    }
    else if (fact_tmp == 0xFF)
    {
        lenth = 16;
        Addr_factor = Addr_trip_num; // 跳闸总次数
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    array_temp[0] = 0;
    array_temp[1] = 0;
    // EEPROM_R(array_temp,Addr_factor,lenth,0);
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
    return 0;
}

/***************************************
    读退出剩余电流保护次数   XXXX  2  BCD
***************************************/
unsigned char Read_num_protectoff(void)
{
    unsigned char lenth, array_temp[8];
    int Addr_factor;
    Addr_factor = Addr_leakquit_num;
    lenth = 2;
    // EEPROM_R(array_temp,Addr_factor,lenth,0);
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
    return 0;
}

/***************************************
    读保护器运行时间   XXXXXXXX  4  BCD
***************************************/
unsigned char Read_time_run(void)
{
    unsigned char i, lenth, array_temp[8];
    int Addr_factor;
    Addr_factor = Addr_protect_time;
    lenth = Lenth_protect_time;
    for (i = 0; i < 4; i++)
    {
        array_temp[i] = T_run_time_array[i];
    }
    // AT24C64_R(array_temp,Addr_factor,lenth);
    Read_response(lenth, array_temp);
    return 0;
}

void point_just(unsigned char fact, unsigned char *array_tmp)
{
    unsigned char month, day, array_temp_time[15], day_tmp, month_tmp;
    unsigned mon_daya_array[13] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 1 3 5 7 8 10 12

    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;

    month_tmp = tim_m;
    month = ((month_tmp >> 4) & 0x0F) * 10 + month_tmp & 0x0F; // 十进制
    day_tmp = tim_d;                                           // 假如是0x31
    array_tmp[0] = tim_m;
    day = (((day_tmp >> 4) & 0x03) * 10) + (day_tmp & 0x0F); // 十进制
    day = day - 1;                                           // 十进制减1
    fact = fact - 1;                                         // fact为DI0，进行减1处理
    if (day >= fact)
    {
        array_tmp[1] = day - fact; // array_tmp[0]存月   array_tmp[1]存日
    }
    else
    {
        if ((month - 1 == 0) || (month - 1 == 2) || (month - 1 == 4) || (month - 1 == 6) || (month - 1 == 9) || (month - 1 == 11))
        {
            array_tmp[1] = mon_daya_array[month] - (fact - day) - 1;
        }
        else
        {
            array_tmp[1] = mon_daya_array[month] - (fact - day);
        }
    }
    //	month_tmp = array_temp_time[1];
    //	month = ((month_tmp>>4)&0x0F)*10 + month_tmp&0x0F;   //十进制
    //	day_tmp = array_temp_time[2];   //假如是0x31
    //	array_tmp[0] = array_temp_time[1];
    //	day = (((day_tmp>>4)&0x03)*10) + (day_tmp&0x0F);   //十进制
    //	day = day - 1;           //十进制减1
    //	fact = fact - 1;         //fact为DI0，进行减1处理
    //	if(day>=fact)
    //	{
    //		array_tmp[1] = day-fact;   //array_tmp[0]存月   array_tmp[1]存日
    //	}
    //	else
    //	{
    //		array_tmp[1] =  mon_daya_array[month] - (fact-day) - 1;
    //	}
}

/****************************************************
//读剩余电流最大相 01--08   8 X 9 = 72
格式： 剩余电流最大相 剩余电流值      出现的时刻
            XX（1）     XXXX（2）  YYMMDDhhmmss（6）
            BIN          BCD
******************************************************/
void Read_max_leak(unsigned char fact_tmp) // fact_tmp为上几日的参数
{
    unsigned char lenth, array_tmp[3], array_temp[15];
    unsigned int Addr_factor;
    point_just(fact_tmp, array_tmp); // fact_tmp为上几日的参数
    Addr_factor = Addr_max_leak + array_tmp[1] * Lenth_max_leak;
    lenth = Lenth_max_leak;
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}
/****************************************************
////读电压最大值 01--30   30X 8 = 240
格式： 电压值	     出现的时刻
    XXX.X(2)	2    YYMMDDhhmmss（6）
        BCD
******************************************************/
void Read_max_vol(unsigned char tmp_fact, unsigned char fact_tmp)
{
    unsigned char lenth, array_tmp[3], array_temp[15];
    unsigned int Addr_factor;
    point_just(fact_tmp, array_tmp);
    Addr_factor = 0;
    if (tmp_fact == 1)
        Addr_factor = Addr_max_Avol;
    if (tmp_fact == 2)
        Addr_factor = Addr_max_Bvol;
    if (tmp_fact == 3)
        Addr_factor = Addr_max_Cvol; // 确定读哪一相

    lenth = Lenth_max_Avol;
    Addr_factor += (array_tmp[1] << 3);
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}

/****************************************************
//读电流最大值 01--08   8 X 9 = 72
格式： 电流值	     出现的时刻
    XXXXX.X（3）   YYMMDDhhmmss（6）
        BCD
******************************************************/
void Read_max_cur(unsigned char tmp_fact, unsigned char fact_tmp)
{
    unsigned char lenth, array_tmp[3], array_temp[15];
    unsigned int Addr_factor;
    point_just(fact_tmp, array_tmp); // 是第几日
    Addr_factor = 0;
    if (tmp_fact == 4)
        Addr_factor = Addr_max_Acur;
    if (tmp_fact == 5)
        Addr_factor = Addr_max_Bcur;
    if (tmp_fact == 6)
        Addr_factor = Addr_max_Ccur;
    lenth = Lenth_max_Acur;
    Addr_factor += (array_tmp[1] * 9); // array_tmp1为上几日的参数
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}
// 读剩余电流最大值最小值
/****************************************************
//读剩余电流最大相 01--30  30X 9 = 270
格式： 剩余电流最大相 剩余电流值      出现的时刻
            XX（1）     XXXX（2）  YYMMDDhhmmss（6）
            BIN          BCD
******************************************************/
void Read_max_min_leak(unsigned char fact_tmp)
{
    unsigned char lenth, array_tmp[3], array_temp[15];
    unsigned int Addr_factor;
    point_just(fact_tmp, array_tmp);
    Addr_factor = 0;
    Addr_factor = Addr_min_leak + array_tmp[1] * Lenth_min_leak;
    lenth = Lenth_min_leak;
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}

// 读电压最小值，最小值 Addr_min_Avol
/****************************************************
////读电压最小值 01--30   30 X 8 = 240
格式： 电压值	     出现的时刻
    XXX.X(2)	2    YYMMDDhhmmss（6）
        BCD
******************************************************/
void Read_max_min_vol(unsigned char tmp_fact, unsigned char fact_tmp)
{
    unsigned char lenth, array_tmp[3], array_temp[15];
    unsigned int Addr_factor;
    point_just(fact_tmp, array_tmp);
    Addr_factor = 0;
    if (tmp_fact == 1)
        Addr_factor = Addr_min_Avol;
    if (tmp_fact == 2)
        Addr_factor = Addr_min_Bvol;
    if (tmp_fact == 3)
        Addr_factor = Addr_min_Cvol;
    lenth = Lenth_min_Avol;
    Addr_factor += (array_tmp[1] << 3);
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}

// 读电流最小值  Addr_min_Acur
/****************************************************
//读电流最小值 01--30   30 X 9 = 270
格式： 电流值	     出现的时刻
    XXXXX.X（3）   YYMMDDhhmmss（6）
        BCD
******************************************************/
void Read_max_min_cur(unsigned char tmp_fact, unsigned char fact_tmp)
{
    unsigned char lenth, array_tmp[3], array_temp[15];
    unsigned int Addr_factor;
    point_just(fact_tmp, array_tmp);
    Addr_factor = 0;
    if (tmp_fact == 4)
        Addr_factor = Addr_min_Acur;
    if (tmp_fact == 5)
        Addr_factor = Addr_min_Bcur;
    if (tmp_fact == 6)
        Addr_factor = Addr_min_Ccur;
    fact_tmp = fact_tmp - 1;
    lenth = Lenth_min_Acur;
    Addr_factor += (array_tmp[1] * 9);
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}

// 剩余电流超限 Addr_event_leak
/***********************************************
剩余电流超限 10X15 =150
剩余电流最大相	XX	1	BIN
剩余电流值	XXXX	2	BCD
开始时刻	YYMMDDhhmmss	6
结束时刻	YYMMDDhhmmss	6
************************************************/
void Read_event_leakover(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[20], point_event_leak_tmp, event_point;
    int Addr_factor;

    if (point_event_leak == 0)
    {
        point_event_leak_tmp = 9;
    }
    else
    {
        point_event_leak_tmp = point_event_leak - 1;
    }
    fact_tmp = fact_tmp - 1; // 次数减1处理
    if (point_event_leak_tmp >= fact_tmp)
    {
        event_point = (point_event_leak_tmp - fact_tmp);
    }
    else
    {
        event_point = point_event_leak_tmp + 10 - fact_tmp;
    }
    Addr_factor = Addr_event_leak + ((event_point) * 15);
    lenth = Lenth_event_leak;
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}

// 保护器自检 Addr_event_self
void Read_event_leakself(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[30], event_point, point_event_self_tmp;
    int Addr_factor;
    if (point_event_self == 0)
    {
        point_event_self_tmp = 9;
    }
    else
    {
        point_event_self_tmp = point_event_self - 1;
    }
    fact_tmp = fact_tmp - 1;
    if (point_event_self_tmp >= fact_tmp)
    {
        event_point = (point_event_self_tmp - fact_tmp);
    }
    else
    {
        event_point = point_event_self_tmp + 10 - fact_tmp;
    }
    Addr_factor = Addr_event_self + ((event_point) * 26);
    lenth = Lenth_event_self;
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}

// 保护器跳闸 Addr_event_trip
void Read_event_leaktrip(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[30], event_point, point_event_trip_tmp;
    int Addr_factor;
    if (point_event_trip_24C256 == 0)
    {
        point_event_trip_tmp = 9;
    }
    else
    {
        point_event_trip_tmp = point_event_trip_24C256 - 1;
    }
    fact_tmp = fact_tmp - 1;
    if (point_event_trip_tmp >= fact_tmp)
    {
        event_point = (point_event_trip_tmp - fact_tmp);
    }
    else
    {
        event_point = point_event_trip_tmp + 10 - fact_tmp;
    }
    Addr_factor = Addr_event_trip + ((event_point) * 25);
    lenth = Lenth_event_trip;
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}
// 剩余电流报警 Addr_event_alarm
void Read_event_leakalarm(unsigned char fact_tmp)
{
    // unsigned char i,cs_temp,lenth,array_temp[20],point_event_alarm_tmp,event_point;
    // int Addr_factor;

    /*	if(point_event_alarm==0)
    {
        point_event_alarm_tmp = 9;
    }
    else
    {
        point_event_alarm_tmp = point_event_alarm-1;
    }
    fact_tmp = fact_tmp - 1;
    if(point_event_alarm_tmp>=fact_tmp)
    {
        event_point = (point_event_alarm_tmp-fact_tmp);
    }
    else
    {
        event_point = point_event_alarm_tmp+10-fact_tmp;
    }
    Addr_factor = Addr_event_alarm+((event_point)*15);
    lenth = Lenth_event_alarm;
    AT24C64_R(array_temp,Addr_factor,lenth);
    Addr_factor = Addr_event_alarm+(fact_tmp-1)*Lenth_event_alarm;
    lenth = Lenth_event_alarm;
    AT24C64_R(array_temp,Addr_factor,lenth);
    Read_response(lenth,array_temp);*/
    unsigned char lenth, array_temp[20], point_event_leak_tmp, event_point;
    int Addr_factor;

    if (point_event_leak == 0)
    {
        point_event_leak_tmp = 9;
    }
    else
    {
        point_event_leak_tmp = point_event_leak - 1;
    }
    fact_tmp = fact_tmp - 1;
    if (point_event_leak_tmp >= fact_tmp)
    {
        event_point = (point_event_leak_tmp - fact_tmp);
    }
    else
    {
        event_point = point_event_leak_tmp + 10 - fact_tmp;
    }
    Addr_factor = Addr_event_leak + ((event_point) * 15);
    lenth = Lenth_event_leak;
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth - 3, &array_temp[3]);
}
// 剩余电流记录 Addr_record_leak1
void Read_event_leakrecord(unsigned char tmp_fact, unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[30], event_point;
    int Addr_factor, point_leak_record_tmp;
    if (point_Leak_record == 0)
    {
        point_leak_record_tmp = 256;
    }
    else
    {
        point_leak_record_tmp = point_Leak_record - 1;
    }
    fact_tmp = fact_tmp - 1;
    if (point_leak_record_tmp >= fact_tmp)
    {
        event_point = (point_leak_record_tmp - fact_tmp);
    }
    else
    {
        event_point = point_leak_record_tmp + 256 - fact_tmp;
    }
    Addr_factor = Addr_record_leak1 + (tmp_fact - 1) * 256 + (event_point * 9);
    lenth = Lenth_record_leak1;
    EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    Read_response(lenth, array_temp);
}

// 获取当前时间
unsigned char Read_time(unsigned char fact_tmp)
{
    unsigned char i, lenth, array_temp[20], tim_array[10];
    tim_array[0] = 0;
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    tim_array[0] = tim_y;
    tim_array[1] = tim_m;
    tim_array[2] = tim_d;
    tim_array[3] = tim_h;
    tim_array[4] = tim_f;
    tim_array[5] = tim_s;
    if (fact_tmp == 1)
    {
        lenth = 4;
        for (i = 1; i < 4; i++)
        {
            array_temp[4 - i] = tim_array[i - 1];
        }
        array_temp[0] = 0x00;
    }
    else if (fact_tmp == 2)
    {
        lenth = 3;
        for (i = 0; i < 3; i++)
        {
            array_temp[2 - i] = tim_array[i + 3];
        }
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp);
    /* while(1)
    {
        ds1302_read_time_uart(tim_array);
        for(i=0;i<200;i++)
        {
            delay_5ms();
        }
        //20150202北京测试修改
        for(i=0;i<4;i++)
        putchar(0xFE);
        for(i=0;i<7;i++)
        {
            putchar(tim_array[i]);
        }
    }  */
    return 0;
}

// 获取当前参数
unsigned char Read_factors(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp_U[40];
    if (fact_tmp == 0x01) // 通信地址
    {
        lenth = Lenth_dev_addr;
        copy_array(array_temp_U, self_addr_code, lenth);
    }
    else if (fact_tmp == 0x02) // 设备号
    {
        lenth = Lenth_dev_id;
        EEPROM_R(Addr_dev_id, array_temp_U, lenth, 0xA0); // 设备号跟地址一样
    }
    else if (fact_tmp == 0x03) // 资产管理编码
    {
        unsigned int cs_sum;
        // Addr_factor = Addr_dev_code;
        lenth = Lenth_dev_code;
        // AT24C64_R(array_temp,Addr_factor,lenth);
        // copy_array(dev_code_code,dev_code_code_head,10);
        /* for(i=0;i<6;i++)
        {
            self_addr_code_str[2*i] = (self_addr_code[5-i]>>4)+0x30;
            self_addr_code_str[2*i+1] = (self_addr_code[5-i]&0x0F)+0x30;
        }
        copy_array(&dev_code_code[9],self_addr_code_str,12);
        for(i=0;i<10;i++)
        {
            cs_sum = 3*(dev_code_code[2*i]-0x30)+(dev_code_code[2*i+1]-0x30);
        }
        cs_tmp = cs_sum%10;
        dev_code_code[21] = cs_tmp+0x30;
        //dev_code_code[21] = 0x35;

        for(i=0;i<10;i++)
        {
            dev_code_code[22+i] = 0x20;
        } */
        // EEPROM_R(dev_code_code,Addr_dev_code,32,0);
        EEPROM_R(Addr_dev_code, dev_code_code, 32, 0xA0);
        copy_array(array_temp_U, dev_code_code, lenth);
    }
    else if (fact_tmp == 0x04) // 额定电压
    {
        // Addr_factor = Addr_rated_V;
        lenth = Lenth_rated_V;
        copy_array(array_temp_U, rated_V_code, lenth);
    }
    else if (fact_tmp == 0x05) // 额定电流
    {
        // Addr_factor = Addr_rated_I;
        lenth = Lenth_rated_I;
        Cur_Switch_F(Type_Cur);
        copy_array(array_temp_U, frame_current_code, lenth);
    }

    else if (fact_tmp == 0x06) // 最大（壳架）电流(Inm)
    {
        // Addr_factor = Addr_frame_current;
        lenth = Lenth_frame_current;
        Cur_Switch_F(Type_Cur);
        copy_array(array_temp_U, frame_current_code, lenth);
    }
    else if (fact_tmp == 0x0B) // 设备型号
    {
        // Addr_factor = Addr_equi_type;
        // EEPROM_R(equi_type_code,Addr_equi_type,10,0);

        EEPROM_R(Addr_equi_type, equi_type_code, 10, 0xA0);
        lenth = Lenth_equi_type;
        copy_array(array_temp_U, equi_type_code, lenth);
    }
    else if (fact_tmp == 0x0C) // 生产日期
    {
        // Addr_factor = Addr_production_date;
        lenth = Lenth_production_date;
        copy_array(array_temp_U, production_date_code, lenth);
    }
    else if (fact_tmp == 0x0D) // 协议版本号
    {
        // Addr_factor = Addr_protocol_ver;
        lenth = Lenth_protocol_ver;
        copy_array(array_temp_U, protocol_ver_code, lenth);
    }
    else if (fact_tmp == 0x0E) // 工厂代码
    {
        // Addr_factor = Addr_factory_code;
        // EEPROM_R(factory_code_code,Addr_factory_code,24,0);
        EEPROM_R(Addr_factory_code, factory_code_code, 24, 0xA0);
        lenth = Lenth_factory_code;
        copy_array(array_temp_U, factory_code_code, lenth);
    }
    else if (fact_tmp == 0x0F) // 固件版本号
    {
        // Addr_factor = Addr_soft_ver;
        lenth = Lenth_soft_ver;
        copy_array(array_temp_U, soft_ver_code, lenth);
    }
    else if (fact_tmp == 0x10) // 硬件版本号32
    {
        // Addr_factor = Addr_hard_ver;
        lenth = Lenth_hard_ver;
        copy_array(array_temp_U, hard_ver_code, lenth);
    }
    else if (fact_tmp == 0x11) // 额定剩余电流动作值参数组 20
    {
        // Addr_factor = Addr_leak_valve;
        lenth = Lenth_leak_valve;
        copy_array(array_temp_U, leak_valve_code, lenth);
    }
    else if (fact_tmp == 0x12) // 额定极限不驱动时间参数组10
    {
        // Addr_factor = Addr_leak_time;
        lenth = Lenth_leak_time;
        copy_array(array_temp_U, leak_time_code, lenth);
    }
    else if (fact_tmp == 0x13) // 额定分断时间参数组10
    {
        // Addr_factor = Addr_break_time;
        lenth = Lenth_break_time;
        // AT24C64_R(array_temp,Addr_factor,lenth);
        copy_array(array_temp_U, break_time_code, lenth);
    }
    else if (fact_tmp == 0x14) // 自动分合闸时间24
    {
        // Addr_factor = Addr_auto_closing;
        lenth = Lenth_auto_closing;
        copy_array(array_temp_U, auto_closing_code, lenth);
    }
    else if (fact_tmp == 0x15) // 剩余电流动作特性（A型或AC型）
    {
        // Addr_factor = Addr_leak_type;
        lenth = Lenth_leak_type;
        copy_array(array_temp_U, leak_type_code, lenth);
    }
    else if (fact_tmp == 0x16) // 安装相位别（只适用单相式保护器）10
    {
        // Addr_factor = Addr_install_phase;
        lenth = Lenth_install_phase;
        copy_array(array_temp_U, install_phase_type_code, lenth);
        // AT24C64_R(array_temp_U,Addr_factor,lenth);
    }

    //	else if(fact_tmp==0x17)//长延时动作电流参数组 20	BCD  long_delay_action
    //	{
    //		//Addr_factor = Addr_install_phase;
    //		lenth = 20;
    //		copy_array(array_temp_U,long_delay_action,lenth);
    //	}
    //	else if(fact_tmp==0x18)//长延时动作时间参数组 10	BCD  long_delay_time
    //	{
    //		//Addr_factor = Addr_install_phase;
    //		lenth = 10;
    //		copy_array(array_temp_U,long_delay_time,lenth);
    //	}
    //	else if(fact_tmp==0x19)//短路短延时动作电流参数组 10	BCD  short_delay_action
    //	{
    //		//Addr_factor = Addr_install_phase;
    //		lenth = 10;
    //		copy_array(array_temp_U,short_delay_action,lenth);
    //	}
    //	else if(fact_tmp==0x1A)//短路短延时动作时间参数组 20	BCD  short_delay_time
    //	{
    //		//Addr_factor = Addr_install_phase;
    //		lenth = 20;
    //		copy_array(array_temp_U,short_delay_time,lenth);
    //	}
    //	else if(fact_tmp==0x1B)//短路瞬时动作电流参数组 10	BCD   instant_action
    //	{
    //		//Addr_factor = Addr_install_phase;
    //		lenth = 10;
    //		copy_array(array_temp_U,instant_action,lenth);
    //	}
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp_U);
    return 0;
}

// 获取当前状态
/* 说明有告警的几种状态
1、剩余电流退运（按键告警与串口设置）
2、执行跳闸动作失败（D7+故障）
3、现场按键设置93，有告警
*/

unsigned char Read_state(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[10];
    stateword[0] = stateword[1] = 0;
    if (isfenzha != 0) // 合闸状态
    {
        F_analog_trip = 0;
        if (F_trip_ld == 1)
        {
            stateword[0] = 0x80 + F_gz; // 0x80为漏电告警开启的意思
        }
        else
        {
            stateword[0] = F_gz; // 后面的5位为故障状态
        }
        if (F_set_state == 1)
        {
            stateword[0] = 0x93; // 1001 0111
        }
    }
    else // 分闸状态
    {
        if (F_gz == 0)
        {
            stateword[0] = 0x40; // 重合闸
        }
        else if (F_gz == 2) // 漏电
        {
            if (F_Trip != 0x03)
                stateword[0] = (0x40 | F_gz);
            else
                stateword[0] = (0x60 | F_gz);
        }
        else if ((F_gz == 4) || (F_gz == 5) || (F_gz == 6) || (F_gz == 7) || (F_gz == 8) || (F_gz == 9) || (F_gz == 0x0A) || (F_gz == 0x0B) || (F_gz == 0x0D) || (F_gz == 0x0F) || (F_gz == 0x12))
        {
            if (F_hezha_sta == 1)
            {
                stateword[0] = (0x40 | F_gz);
            }
            else
            {
                stateword[0] = (0x60 | F_gz);
            }
            if ((F_analog_trip == 1) && (F_gz == 0x0D))
            {

                stateword[0] = 0x4D;
            }
        }
        else if ((F_gz == 0x0C) || (F_gz == 0x0B) || (F_gz == 0x0E))
        {
            stateword[0] = (0x40 | F_gz);
        }
        else
        {
            stateword[0] = (0x60 | F_gz);
        }
        if (F_set_state == 1)
        {
            stateword[0] = 0xF3;
        }
        if (F_disp_jg == 0x55)
        {
            stateword[0] = 0x71;
        }
    }

    stateword[1] = point_trip;
    point_trip = 0;
    if ((fact_tmp == 1) || (fact_tmp == 2)) // 读状态字1还是2
    {
        array_temp[0] = stateword[fact_tmp - 1];
        lenth = 1;
    }
    else if (fact_tmp == 0xff)
    {
        array_temp[0] = stateword[0];
        array_temp[1] = stateword[1]; // 都读
        lenth = 2;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp);
    return 0;
}

// 获取当前波特率
unsigned char Read_baud(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[4];
    if (baud == 0)
        baud_uart = 0x04;
    else if (baud == 1)
        baud_uart = 0x08;
    else if (baud == 2)
        baud_uart = 0x10;
    else if (baud == 3)
        baud_uart = 0x20; // 波特率代表 9600 依次除2
    else
        baud_uart = 0x08;
    if (fact_tmp == 0x03)
    {
        array_temp[0] = baud_uart;
        lenth = 1;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp);
    return 0;
}

// 获取当前控制字
unsigned char Read_ctrlword(unsigned char fact_tmp)
{
    unsigned char i, lenth, array_temp[10];

    if ((fact_tmp > 0) && (fact_tmp < 6))
    {
        array_temp[0] = ctrlword[fact_tmp - 1];
        lenth = 1;
    }
    else if (fact_tmp == 0xff)
    {
        for (i = 0; i < 6; i++)
        {
            array_temp[i] = ctrlword[i];
        }
        lenth = 5;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp);
    return 0;
}

// 获取漏电控制参数
unsigned char Read_leakctrl(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[20];
    int Addr_factor;
    if (fact_tmp == 0x01) // 剩余电流超限报警整定值 2
    {
        Addr_factor = Addr_alarm_value;
        lenth = Lenth_alarm_value;
        EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    }
    else if (fact_tmp == 0x02) // 剩余电流记录变化差值整定值(10-99) 1

    {
        Addr_factor = Addr_record_value;
        lenth = Lenth_record_value;
        EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    }
    else if (fact_tmp == 0x03) // 剩余电流记录间隔时间整定值(01-99)

    {
        Addr_factor = Addr_record_time;
        lenth = Lenth_record_time;
        EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    }
    else if (fact_tmp == 0xFF)
    {
        Addr_factor = Addr_alarm_value;
        lenth = Lenth_alarm_value + Lenth_record_value + Lenth_record_time;
        EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
        EEPROM_R(Addr_record_time, &array_temp[3], 1, 0xA0);
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    // AT24C64_R(array_temp,Addr_factor,lenth);
    Read_response(lenth, array_temp);
    return 0;
}

// 获取定时试跳时间
unsigned char Read_timing(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[20], Addr_factor;
    if (fact_tmp == 0x01) // 定时试跳整定时间 3
    {
        Addr_factor = Addr_timed_trip; // record_time_code;
        lenth = Lenth_timed_trip;
    }
    else if (fact_tmp == 0xFF)
    {
        Addr_factor = Addr_timed_trip;
        lenth = Lenth_timed_trip;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    // AT24C64_R(array_temp,Addr_factor,lenth);
    // if(F_time_compare==0)
    {
        array_temp[0] = timed_trip_code[0];
        array_temp[1] = timed_trip_code[1];
        array_temp[2] = timed_trip_code[2];
    }
    Read_response(lenth, array_temp);
    return 0;
}
// 获取电压相关整定值
unsigned char Read_vol_setpoint(unsigned char fact_tmp)
{
    Vol_g_decimal = (int)Vol_g;
    Vol_q_decimal = (int)Vol_q;
    unsigned char lenth, array_temp[20];
    if (fact_tmp == 0x01) // 过电压整定值 2
    {

        over_vol_code[0] = (Vol_g_decimal % 10) << 4;
        over_vol_code[1] = 0x25 + (Vol_g_decimal / 10) % 10;
        lenth = Lenth_over_vol;
        copy_array(array_temp, over_vol_code, lenth);
    }
    else if (fact_tmp == 0x02) // 欠电压整定值 2
    {

        under_vol_code[0] = (Vol_q_decimal % 10) << 4;
        under_vol_code[1] = 0x14 + (Vol_q_decimal / 10) % 10;
        if (under_vol_code[1] == 0x1A)
            under_vol_code[1] = 0x20;
        lenth = Lenth_under_vol;
        copy_array(array_temp, under_vol_code, lenth);
    }
    else if (fact_tmp == 0x03) // 断相电压整定值 2
    {
        // Addr_factor = Addr_break_phase;
        lenth = Lenth_break_phase;
        copy_array(array_temp, break_phase_code, lenth);
    }
    else if (fact_tmp == 0xFF)
    {
        // Addr_factor = Addr_over_vol;
        lenth = Lenth_over_vol + Lenth_break_phase + Lenth_under_vol;
        over_vol_code[0] = (Vol_g_decimal % 10) << 4;
        over_vol_code[1] = 0x25 + (Vol_g_decimal / 10) % 10;
        under_vol_code[0] = (Vol_q_decimal % 10) << 4;
        under_vol_code[1] = 0x14 + (Vol_q_decimal / 10) % 10;
        copy_array(array_temp, over_vol_code, 2);
        copy_array(&array_temp[2], under_vol_code, 2);
        copy_array(&array_temp[4], break_phase_code, 2);
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp);
    return 0;
}

void Cur_uart_get(void)
{

    unsigned char i;
    unsigned int tmp;
    for (i = 0; i < 3; i++)
    {
        rated_current_code[i] = 0x00;
    }

    if (Type_Cur == 0) // 100 20~100
    {

        tmp = 50 + D_Cur * 10; // 10为1档位
        DectoBCD(rated_current_code, tmp, 3);
    }
    if (Type_Cur == 1) // 250 60-250
    {
        tmp = 630 + D_Cur * 10;
        DectoBCD(rated_current_code, tmp, 3);
    }
    if (Type_Cur == 2) // 400 200-400
    {
        tmp = 1600 + D_Cur * 10; // 20为1档位
        DectoBCD(rated_current_code, tmp, 3);
    }
    if (Type_Cur == 3) // 630 210 -630
    {
        tmp = 2520 + D_Cur * 10; // 30为1档位
        DectoBCD(rated_current_code, tmp, 3);
    }
    if (Type_Cur == 4) // 100 20~100
    {

        tmp = 3200 + D_Cur * 10; // 10为1档位
        DectoBCD(rated_current_code, tmp, 3);
    }
}

// 获取电流相关整定值
unsigned char Read_cur_setpoint(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[20];
    int Addr_factor;
    if (fact_tmp == 0x01) // 额定电流整定值 3
    {
        // Addr_factor = Addr_rated_current;
        lenth = Lenth_rated_current;
        Cur_uart_get();
        copy_array(array_temp, rated_current_code, lenth);
    }
    else if (fact_tmp == 0x02) // 电流超限报警整定值
    {
        Addr_factor = Addr_over_current;
        lenth = Lenth_over_current;
        EEPROM_R(Addr_factor, array_temp, lenth, 0xA0);
    }
    else if (fact_tmp == 0xFF)
    {
        // Addr_factor = Addr_rated_current;
        lenth = Lenth_rated_current + Lenth_over_current;
        Cur_uart_get();
        copy_array(array_temp, rated_current_code, Lenth_rated_current);
        Addr_factor = Addr_over_current;
        EEPROM_R(Addr_factor, &array_temp[Lenth_rated_current], Lenth_over_current, 0xA0);
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 1;
    }
    Read_response(lenth, array_temp);
    return 0;
}

// 获取预分闸时间
void Read_fenzha_tim(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[20];
    fact_tmp = fact_tmp + 1;
    // Addr_factor = Addr_remote_trip;
    lenth = 2;
    fact_tmp = fact_tmp - 1;
    // EEPROM_R(array_temp,Addr_factor,lenth,2);
    copy_array(array_temp, remote_trip_time, 2);
    Read_response(lenth, array_temp);
}
// 获取预合闸时间
void Read_hezha_tim(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[20];
    //	Addr_factor = Addr_remote_close;
    fact_tmp = fact_tmp + 1;
    lenth = Lenth_remote_close;
    fact_tmp = fact_tmp - 1;
    // AT24C64_R(array_temp,Addr_factor,lenth);
    copy_array(array_temp, remote_close_time, 2);
    Read_response(lenth, array_temp);
}

// 获取模拟脱扣时间
void Read_trip_tim(unsigned char fact_tmp)
{
    unsigned char lenth, array_temp[20];
    //	Addr_factor = Addr_analog_trip;
    fact_tmp = fact_tmp + 1;
    lenth = Lenth_analog_trip;
    fact_tmp = fact_tmp - 1;
    // AT24C64_R(array_temp,Addr_factor,lenth);
    copy_array(array_temp, analog_trip_time, 2);
    Read_response(lenth, array_temp);
}
void Read_addr(void)
{
    unsigned char lenth, array_temp_U[40];
    lenth = Lenth_dev_addr;
    copy_array(array_temp_U, self_addr_code, lenth);
    Read_response1(lenth, array_temp_U);
}

void Write_addr(void) // 写地址
{
    unsigned char i, cs_temp, lenth;
    int Addr_factor;
    for (i = 0; i < 6; i++)
    {
        self_addr_code[i] = data_array[i];
    }
    format_uart_t_buf(); // 清0
    UART_T_Buf[0] = UART_T_Buf[7] = 0x68;
    for (i = 0; i < 6; i++)
    {
        UART_T_Buf[i + 1] = 0xAA; // 写读地址前面都是这
    }
    UART_T_Buf[8] = ctrl_code + 0x80;
    UART_T_Buf[9] = 0x00; // 第九位是数据长度
    cs_temp = 0;
    for (i = 0; i < 10; i++)
    {
        cs_temp = UART_T_Buf[i] + cs_temp;
    }
    UART_T_Buf[10] = cs_temp;
    UART_T_Buf[11] = 0x16;
    // 20150202??????
    //	for(i=0;i<4;i++)
    //	put2char(0xFE);
    //	for(i=0;i<12;i++)
    //	put2char(UART_T_Buf[i]);
    //	//RS485_Send_Data(UART_T_Buf,12);
    for (i = 0; i < 4; i++)
    {
        UART_S_Buf[i] = 0xFE;
    }
    if (F_Dataval == 1)
    {
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_S_Buf, 4, 0xffff);
        HAL_UART_Transmit(&huart1, (uint8_t *)UART_T_Buf, 12, 0xffff);
        //		 RS485_Send_Data(UART_S_Buf,4);
        //		 RS485_Send_Data(UART_T_Buf,12);
    }
    if (F_Dataval1 == 1)
    {
        // hongwai_Send_Data(UART_T_Buf,12);
    }

    delay_ms(5);
    delay_ms(5);
    Addr_factor = Addr_dev_addr;
    lenth = Lenth_dev_addr;
    MODIFY_EEP_W(Addr_factor, self_addr_code, lenth, 0xA0);
}

// 写当前时间
unsigned char Write_time(unsigned char fact_tmp)
{
    unsigned char i, array_temp[10];

    if (fact_tmp == 1) // 年月日周
    {
        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        tim_y1 = sdatestructure.Year; // tim_y为十进制，要转换二进制
        tim_m1 = sdatestructure.Month;
        tim_d1 = sdatestructure.Date;
        tim_h1 = stimestructure.Hours;
        tim_f1 = stimestructure.Minutes;
        tim_s1 = stimestructure.Seconds;
        //	tim_y=tim_y%2000;  //time_tmp[0]=17   十进制转换为二进制存入24C64中
        //	array_temp[0]=(tim_y/10)<<4;
        //	array_temp[0]+=(tim_y%10);
        //	array_temp2[0]=((array_temp[0]>>4)*10)+(array_temp[0]&0x0F)+2000;
        //	array_temp[1]=(tim_m/10)<<4;
        //	array_temp[1]+=(tim_m%10);
        //	array_temp[2]=(tim_d/10)<<4;
        //	array_temp[2]+=(tim_d%10);
        //	array_temp[3]=(tim_h/10)<<4;
        //	array_temp[3]+=(tim_h%10);
        //	array_temp[4]=(tim_f/10)<<4;
        //	array_temp[4]+=(tim_f%10);
        //	array_temp[5]=(tim_s/10)<<4;
        //	array_temp[5]+=(tim_s%10);
        array_temp[0] = tim_y1;
        array_temp[1] = tim_m1;
        array_temp[2] = tim_d1;
        array_temp[3] = tim_h1;
        array_temp[4] = tim_f1;
        array_temp[5] = tim_s1;
        for (i = 0; i < 3; i++)
        {
            array_temp[2 - i] = data_array[12 + 1 + i];
        }
        //    array_temp[6]=((array_temp[0]>>4)*10)+(array_temp[0]&0x0F);
        //		tim_y1=((array_temp[6]/10)<<4)+(array_temp[6]%10);
        //		tim_m1=array_temp[1];
        //		tim_d1=array_temp[2];
        //		sdatestructure.Year=tim_y1;
        //	 RTC_Set_Date(tim_y1,tim_m1,tim_d1);
        RTC_Set_Date(array_temp[0], array_temp[1], array_temp[2]);
        RTC_Set_Time(tim_h1, tim_f1, tim_s1);

        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        // ds1302_write_time_uart(array_temp2[0],array_temp[1],array_temp[2],array_temp[3],array_temp[4],array_temp[5]);
        return 0;
    }
    else if (fact_tmp == 2) // 时分秒
    {
        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
        tim_m = sdatestructure.Month;
        tim_d = sdatestructure.Date;
        tim_h = stimestructure.Hours;
        tim_f = stimestructure.Minutes;
        tim_s = stimestructure.Seconds;
        //	tim_y=tim_y%2000;  //time_tmp[0]=17   十进制转换为二进制存入24C64中
        //	array_temp[0]=(tim_y/10)<<4;
        //	array_temp[0]+=(tim_y%10);
        //	array_temp2[0]=((array_temp[0]>>4)*10)+(array_temp[0]&0x0F)+2000;
        //	array_temp[1]=(tim_m/10)<<4;
        //	array_temp[1]+=(tim_m%10);
        //	array_temp[2]=(tim_d/10)<<4;
        //	array_temp[2]+=(tim_d%10);
        //	array_temp[3]=(tim_h/10)<<4;
        //	array_temp[3]+=(tim_h%10);
        //	array_temp[4]=(tim_f/10)<<4;
        //	array_temp[4]+=(tim_f%10);
        //	array_temp[5]=(tim_s/10)<<4;
        //	array_temp[5]+=(tim_s%10);
        array_temp[0] = tim_y;
        array_temp[1] = tim_m;
        array_temp[2] = tim_d;
        array_temp[3] = tim_h;
        array_temp[4] = tim_f;
        array_temp[5] = tim_s;
        for (i = 0; i < 3; i++)
        {
            array_temp[3 + 2 - i] = data_array[12 + i];
        }
        RTC_Set_Time(array_temp[3], array_temp[4], array_temp[5]);
        RTC_Set_Date(array_temp[0], array_temp[1], array_temp[2]);

        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        // ds1302_write_time_uart(array_temp2[0],array_temp[1],array_temp[2],array_temp[3],array_temp[4],array_temp[5]);
        return 0;
    }
    else if (fact_tmp == 0xFF) // 时分秒
    {
        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
        tim_m = sdatestructure.Month;
        tim_d = sdatestructure.Date;
        tim_h = stimestructure.Hours;
        tim_f = stimestructure.Minutes;
        tim_s = stimestructure.Seconds;

        array_temp[0] = tim_y;
        array_temp[1] = tim_m;
        array_temp[2] = tim_d;
        array_temp[3] = tim_h;
        array_temp[4] = tim_f;
        array_temp[5] = tim_s;
        for (i = 0; i < 6; i++)
        {
            array_temp[5 - i] = data_array[12 + i];
        }
        RTC_Set_Time(array_temp[3], array_temp[4], array_temp[5]);
        RTC_Set_Date(array_temp[0], array_temp[1], array_temp[2]);

        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        // ds1302_write_time_uart(array_temp2[0],array_temp[1],array_temp[2],array_temp[3],array_temp[4],array_temp[5]);
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}

// 写当前参数
unsigned char Write_factors(unsigned char fact_tmp)
{
    unsigned char i, array_temp[32], array_tmp[1];
    if (fact_tmp == 1) // 写通信地址 6 BCD
    {
        for (i = 0; i < 6; i++)
        {
            self_addr_code[i] = data_array[12 + i];
            if (array_temp[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        MODIFY_EEP_W(Addr_dev_addr, self_addr_code, 6, 0xA0);
        return 0;
    }
    else if (fact_tmp == 2) // 写设备号 6 BCD
    {
        for (i = 0; i < 6; i++)
        {
            dev_id_code[i] = data_array[12 + i];
            if (dev_id_code[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        MODIFY_EEP_W(Addr_dev_id, dev_id_code, 6, 0xA0);
        return 0;
    }
    else if (fact_tmp == 3) // 写资产管理编码 32 ASCII
    {
        for (i = 0; i < 32; i++)
        {
            dev_code_code[i] = data_array[12 + i];
        }
        WRITE_DATA_NOMAL();
        MODIFY_EEP_W(Addr_dev_code, dev_code_code, 32, 0xA0);
        return 1;
    }
    else if (fact_tmp == 6) // 写壳架电流 2 BCD
    {
        array_temp[0] = data_array[12];
        array_temp[1] = data_array[13];
        UART_Cur_Value = BCDtoDec(array_temp, 2);
        if (UART_Cur_Value == 2500)
        {
            Type_Cur = 1;
        }
        else if (UART_Cur_Value == 4000)
        {
            Type_Cur = 2;
        }
        else if (UART_Cur_Value == 6300)
        {
            Type_Cur = 3;
        }
        else
        {
            Type_Cur = 0;
        }
        array_tmp[0] = Type_Cur;
        Cur_Switch(Type_Cur);
        //		WRITE_DATA_NOMAL();
        MODIFY_EEP_W(Addr_Type_Cur, array_tmp, 1, 0xA0);
        return 0;
    }
    else if (fact_tmp == 0x0E) // 写厂家代码 24 ASCII
    {
        for (i = 0; i < 24; i++)
        {
            factory_code_code[i] = data_array[12 + i];
        }
        WRITE_DATA_NOMAL();
        MODIFY_EEP_W(Addr_factory_code, factory_code_code, 24, 0xA0);
        return 1;
    }
    else if (fact_tmp == 0x0B) // 写设备代码 10 ASCII
    {
        for (i = 0; i < 10; i++)
        {
            equi_type_code[i] = data_array[12 + i];
        }
        WRITE_DATA_NOMAL();
        MODIFY_EEP_W(Addr_equi_type, equi_type_code, 10, 0xA0);
        return 1;
    }

    else if (fact_tmp == 0x11) // 写额定剩余电流动作值参数组 20 BCD
    {
        for (i = 0; i < 20; i++)
        {
            leak_valve_code[i] = data_array[12 + i];
        }
        MODIFY_EEP_W(Addr_leak_valve, leak_valve_code, Lenth_leak_valve, 0xA0);
        return 0;
    }
    else if (fact_tmp == 0x12) // 写额定极限不驱动时间参数组 10 BCD
    {
        for (i = 0; i < Lenth_leak_time; i++)
        {
            leak_time_code[i] = data_array[12 + i];
        }
        MODIFY_EEP_W(Addr_leak_time, leak_time_code, Lenth_leak_time, 0xA0);
        return 0;
    }
    else if (fact_tmp == 0x13) // 写额定分断时间参数数组 10 BCD
    {
        for (i = 0; i < Lenth_break_time; i++)
        {
            break_time_code[i] = data_array[12 + i];
        }
        MODIFY_EEP_W(Addr_leak_time, leak_time_code, Lenth_leak_time, 0xA0);
        return 0;
    }

    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}
// 写当前波特率
unsigned char Write_baud(unsigned char fact_tmp)
{
    // baud = data_array[12];
    baud_uart = data_array[12];
    if ((baud_uart == 0x02) || (baud_uart == 0x04) || (baud_uart == 0x08) || (baud_uart == 0x10) || (baud_uart == 0x20) || (baud_uart == 0x40))
    {
        if (baud_uart == 0x20)
            baud = 3;
        else if (baud_uart == 0x10)
            baud = 2;
        else if (baud_uart == 0x08)
            baud = 1;
        else if (baud_uart == 0x04)
            baud = 0;
        else
            baud = 1;
        data_array[0] = baud;
        MODIFY_EEP_W(Addr_baud, data_array, 1, 0xA0);
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_BAD_DATA);
        //	//RS485_Send_Data(data_array,1);
        return 1;
    }
}
// 写当前密码
unsigned char Write_password(unsigned char fact_tmp)
{
    unsigned char i, array_temp[6];
    if (fact_tmp == 1)
    {
        for (i = 0; i < 4; i++)
        {
            array_temp[i] = data_array[12 + i];
            password_0class[i] = data_array[12 + i];
            if (array_temp[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        MODIFY_EEP_W(Addr_0_password, array_temp, 4, 0xA0);
        return 0;
    }
    else if (fact_tmp == 2)
    {
        for (i = 0; i < 4; i++)
        {
            array_temp[i] = data_array[12 + i];
            password_1class[i] = data_array[12 + i];
            if (array_temp[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        MODIFY_EEP_W(Addr_1_password, array_temp, 4, 0xA0);
        return 0;
    }
    else if (fact_tmp == 3)
    {
        for (i = 0; i < 4; i++)
        {
            array_temp[i] = data_array[12 + i];
            password_2class[i] = data_array[12 + i];
            if (array_temp[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        MODIFY_EEP_W(Addr_2_password, array_temp, 4, 0xA0);
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
    // for(i=0;i<4;i++)
    // {
    // putchar(password_0class[i]);
    // }
    // for(i=0;i<4;i++)
    // {
    // putchar(password_1class[i]);
    // }
    // for(i=0;i<4;i++)
    // {
    // putchar(password_2class[i]);
    // }
}

// 写当前控制字
unsigned char Write_ctrlword(unsigned char fact_tmp)
{
    unsigned char i, array_temp[6];
    if ((fact_tmp >= 1) && (fact_tmp <= 5))
    {
        array_temp[fact_tmp - 1] = data_array[12 + 0];
        ctrlword[fact_tmp - 1] = array_temp[fact_tmp - 1];
        // AT24C64_W(ctrlword,Addr_crtl_word1,5);
        //  putchar(0x55);
        //  putchar(ctrlword[fact_tmp-1]);
        if (fact_tmp == 1)
        {
            ctrlword1_analyze();
            // AT24C64_W(&ctrlword[0],Addr_crtl_word1,1);
            MODIFY_EEP_W(Addr_crtl_word1, &ctrlword[0], 1, 0xA0);
        }
        else if (fact_tmp == 2)
        {
            ctrlword2_analyze();
            // AT24C64_W(&ctrlword[1],Addr_crtl_word2,1);
            MODIFY_EEP_W(Addr_crtl_word2, &ctrlword[1], 1, 0xA0);
        }
        else if (fact_tmp == 3)
        {
            ctrlword3_analyze();
            // AT24C64_W(&ctrlword[2],Addr_crtl_word3,1);
            MODIFY_EEP_W(Addr_crtl_word3, &ctrlword[2], 1, 0xA0);
        }
        else if (fact_tmp == 4)
        {
            ctrlword4_analyze();
            // AT24C64_W(&ctrlword[3],Addr_crtl_word4,1);
            MODIFY_EEP_W(Addr_crtl_word4, &ctrlword[3], 1, 0xA0);
        }
        else if (fact_tmp == 5)
        {
            ctrlword5_analyze();
        }
        else
        {
            ERR_data_sent(ERR_NO_REQUEST);
            return 2;
        }
        return 0;
    }

    else if (fact_tmp == 0xff)
    {
        for (i = 0; i < 5; i++)
        {
            ctrlword[i] = data_array[12 + i];
        }
        ctrlword1_analyze();
        // AT24C64_W(&ctrlword[0],Addr_crtl_word1,1);
        MODIFY_EEP_W(Addr_crtl_word1, &ctrlword[0], 1, 0xA0);
        ctrlword2_analyze();
        // AT24C64_W(&ctrlword[1],Addr_crtl_word2,1);
        MODIFY_EEP_W(Addr_crtl_word2, &ctrlword[1], 1, 0xA0);
        ctrlword3_analyze();
        // AT24C64_W(&ctrlword[2],Addr_crtl_word3,1);
        MODIFY_EEP_W(Addr_crtl_word3, &ctrlword[2], 1, 0xA0);
        ctrlword4_analyze();
        // AT24C64_W(&ctrlword[3],Addr_crtl_word4,1);
        MODIFY_EEP_W(Addr_crtl_word4, &ctrlword[3], 1, 0xA0);
        ctrlword5_analyze();
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}

// 写漏电控制参数
unsigned char Write_leakctrl(unsigned char fact_tmp)
{
    unsigned char array_temp[6];
    if (fact_tmp == 1) // 剩余电流超限整定值 2 BCD
    {
        array_temp[0] = data_array[12];
        array_temp[1] = data_array[12 + 1];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        copy_array(alarm_value_code, array_temp, Lenth_alarm_value);
        Leak_Alarm_Value = BCDtoDec(array_temp, 2);
        MODIFY_EEP_W(Addr_alarm_value, alarm_value_code, 2, 0xA0);
        return 0;
    }
    else if (fact_tmp == 2) // 剩余电流记录差值整定值 1 BCD
    {
        array_temp[0] = data_array[12];

        if ((array_temp[0] > 0x99) || (array_temp[0] < 0x10))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        record_value_code[0] = array_temp[0];
        Leak_record_value = BCDtoDec(record_value_code, 1);
        MODIFY_EEP_W(Addr_record_value, record_value_code, 1, 0xA0);
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_record_value, array_temp, 1, 0xA0);
        return 0;
    }
    else if (fact_tmp == 3) // 剩余电流记录时间整定值 1 BCD
    {
        array_temp[0] = data_array[12];
        if ((array_temp[0] > 0x99) || (array_temp[0] < 0x01))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        record_time_code[0] = array_temp[0];
        Leak_record_time = BCDtoDec(record_time_code, 1);
        Num_leak_record = Leak_record_time * 30 * 1000 + 1;
        MODIFY_EEP_W(Addr_record_time, record_time_code, 1, 0xA0);
        return 0;
    }
    else if (fact_tmp == 0xff)
    {
        array_temp[0] = data_array[12 + 0];
        array_temp[1] = data_array[12 + 1];
        array_temp[2] = data_array[12 + 2];
        array_temp[3] = data_array[12 + 3];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99) || (array_temp[2] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        alarm_value_code[0] = array_temp[0];
        alarm_value_code[1] = array_temp[1];
        record_value_code[0] = array_temp[2];
        record_time_code[0] = array_temp[3];
        Leak_Alarm_Value = BCDtoDec(alarm_value_code, 2);
        Leak_record_value = BCDtoDec(alarm_value_code, 1);
        Leak_record_time = BCDtoDec(record_time_code, 1);
        Num_leak_record = Leak_record_time * 30 * 1000 + 1;
        MODIFY_EEP_W(Addr_alarm_value, array_temp, 4, 0xA0);
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}

// 写定时试跳时间
unsigned char Write_timing(unsigned char fact_tmp)
{
    unsigned char array_temp[6];
    if ((fact_tmp == 0x01) || (fact_tmp == 0xff))
    {
        timed_trip_code[0] = array_temp[0] = data_array[12 + 0];
        timed_trip_code[1] = array_temp[1] = data_array[12 + 1];
        timed_trip_code[2] = array_temp[2] = data_array[12 + 2];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99) || (array_temp[2] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        MODIFY_EEP_W(Addr_timed_trip, array_temp, 3, 0xA0);
        // MODIFY_EEP_W(array_temp,Addr_timed_trip,3,2);

        // if(F_timealarm==1)
        // {
        // F_time_compare = 1;
        // AT24C64_W(array_temp,Addr_timed_trip,3);
        // }
        /* 		else
        {
            ERR_data_sent(ERR_NO_REQUEST);
            return 2;
        }
        */
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}

//****写电机合闸延时时间*********by lsj 23-09-19***********//
unsigned char Write_hezha_delay(unsigned char fact_tmp)
{
    unsigned char array_temp[6];
    array_temp[0] = fact_tmp;

    if ((array_temp[0] <= 0x09) && (array_temp[0] >= 0x00))
    {
        MODIFY_EEP_W(Addr_hezha_delay, array_temp, 1, 0xA0);
        TH_hezha_delay = array_temp[0];
        hezha_delay = hezha_delay_arry[TH_hezha_delay];
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_BAD_DATA);
        return 2;
    }
}

// 写电压相关整定值
unsigned char Write_vol_setpoint(unsigned char fact_tmp)
{
    unsigned char i, array_temp[6], array_tmp[3];
    unsigned char tmp1, tmp2, tmp3;
    if (fact_tmp == 1)
    {
        over_vol_code[0] = array_temp[0] = data_array[12 + 0];
        over_vol_code[1] = array_temp[1] = data_array[12 + 1];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        Vol_uart_g = 0;
        tmp1 = ((over_vol_code[1] >> 4) & 0x0F);
        tmp2 = ((over_vol_code[1] & 0x0F));
        tmp3 = (over_vol_code[0] >> 4);
        Vol_uart_g = tmp1 * 100 + tmp2 * 10 + tmp3;
        Vol_uart_g = Vol_uart_g - 250;
        Vol_g = (unsigned char)Vol_uart_g;
        //		if(Vol_uart_g>=295)       Vol_g = 5;
        //		else if(Vol_uart_g>=285)  Vol_g = 4;
        //		else if (Vol_uart_g>=275) Vol_g = 3;
        //		else if (Vol_uart_g>=265) Vol_g = 2;
        //		else if (Vol_uart_g>=255) Vol_g = 1;
        //		else if (Vol_uart_g>=245) Vol_g = 0;
        //		else                    Vol_g = 0;
        // W_EEP(45,Vol_g);//将新的过压动作值写入E2
        //		H_H_V = D_HV_Array[Vol_g];//更新主程序中相关数值
        array_tmp[0] = Vol_g;
        MODIFY_EEP_W(Addr_Vol_g, array_tmp, 1, 0xA0);

        //	    while(Vol_g!=R_EEP(45))
        // W_EEP(45,Vol_g);
        MODIFY_EEP_W(Addr_over_vol, array_temp, 2, 0xA0);
        return 0;
    }
    else if (fact_tmp == 2)
    {
        under_vol_code[0] = array_temp[0] = data_array[12 + 0];
        under_vol_code[1] = array_temp[1] = data_array[12 + 1];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        Vol_uart_q = 0;
        tmp1 = ((under_vol_code[1] >> 4) & 0x0F);
        tmp2 = ((under_vol_code[1] & 0x0F));
        tmp3 = (under_vol_code[0] >> 4);
        Vol_uart_q = tmp1 * 100 + tmp2 * 10 + tmp3;
        Vol_uart_q = Vol_uart_q - 140;
        Vol_q = (unsigned char)Vol_uart_q;
        //		if(Vol_uart_q<=144) Vol_q = 0;
        //		else if (Vol_uart_q<=154) Vol_q = 1;
        //		else if (Vol_uart_q<=164) Vol_q = 2;
        //		else if (Vol_uart_q<=174) Vol_q = 3;
        //		else if (Vol_uart_q<=184) Vol_q = 4;
        //		else if (Vol_uart_q<=194) Vol_q = 5;
        //		else if (Vol_uart_q<=204) Vol_q = 6;
        //		else                    Vol_q = 6;
        // W_EEP(46,Vol_q);//将新的欠压动作值写入E2
        //		H_L_V = D_LV_Array[Vol_q];//更新主程序中相关数值
        array_tmp[0] = Vol_q;
        MODIFY_EEP_W(Addr_Vol_q, array_tmp, 1, 0xA0);
        //  while(Vol_q!=R_EEP(46))
        // W_EEP(46,Vol_q);
        //	AT24C64_W(array_temp,Addr_under_vol,1);
        MODIFY_EEP_W(Addr_under_vol, array_temp, 2, 0xA0);
        return 0;
    }
    else if (fact_tmp == 3)
    {
        break_phase_code[0] = array_temp[0] = data_array[12 + 0];
        break_phase_code[1] = array_temp[1] = data_array[12 + 1];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }

        H_D_V = BCDtoDec(break_phase_code, 2) / 10;
        H_D_V = ((H_D_V * 7) >> 1) - 109;
        MODIFY_EEP_W(Addr_break_phase, array_temp, 2, 0xA0);
        // MODIFY_EEP_W(array_temp,Addr_break_phase,2,2);
        return 0;
    }
    else if ((fact_tmp == 0xff) || (fact_tmp == 0x04))
    {
        over_vol_code[0] = array_temp[0] = data_array[12 + 0];
        over_vol_code[1] = array_temp[1] = data_array[12 + 1];
        under_vol_code[0] = array_temp[2] = data_array[12 + 2];
        under_vol_code[1] = array_temp[3] = data_array[12 + 3];
        break_phase_code[0] = array_temp[4] = data_array[12 + 4];
        break_phase_code[1] = array_temp[5] = data_array[12 + 5];
        for (i = 0; i < 6; i++)
        {
            if (array_temp[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        Vol_uart_g = 0;
        tmp1 = ((over_vol_code[1] >> 4) & 0x0F);
        tmp2 = ((over_vol_code[1] & 0x0F));
        tmp3 = (over_vol_code[0] >> 4);
        Vol_uart_g = tmp1 * 100 + tmp2 * 10 + tmp3;
        Vol_uart_g = Vol_uart_g - 250;
        Vol_g = (unsigned char)Vol_uart_g;
        //		if(Vol_uart_g>=295)      Vol_g = 5;
        //	  else if(Vol_uart_g>=285) Vol_g = 4;
        //		else if (Vol_uart_g>=275) Vol_g = 3;
        //		else if (Vol_uart_g>=265) Vol_g = 2;
        //		else if (Vol_uart_g>=255) Vol_g = 1;
        //		else if (Vol_uart_g>=245) Vol_g = 0;
        //		else                    Vol_g = 0;
        // W_EEP(45,Vol_g);//将新的过压动作值写入E2
        //		H_H_V = D_HV_Array[Vol_g];//更新主程序中相关数值
        //  while(Vol_g!=R_EEP(45))
        // W_EEP(45,Vol_g);
        array_tmp[0] = Vol_g;
        MODIFY_EEP_W(Addr_Vol_g, array_tmp, 1, 0xA0);

        Vol_uart_q = 0;
        tmp1 = ((under_vol_code[1] >> 4) & 0x0F);
        tmp2 = ((under_vol_code[1] & 0x0F));
        tmp3 = (under_vol_code[0] >> 4);
        Vol_uart_q = tmp1 * 100 + tmp2 * 10 + tmp3;
        Vol_uart_q = Vol_uart_q - 140;
        Vol_q = (unsigned char)Vol_uart_q;
        //		if(Vol_uart_q<=144) Vol_q = 0;
        //		else if (Vol_uart_q<=154) Vol_q = 1;
        //		else if (Vol_uart_q<=164) Vol_q = 2;
        //		else if (Vol_uart_q<=174) Vol_q = 3;
        //		else if (Vol_uart_q<=184) Vol_q = 4;
        //		else                    Vol_q = 4;
        // W_EEP(46,Vol_q);//将新的欠压动作值写入E2
        //		H_L_V = D_LV_Array[Vol_q];//更新主程序中相关数值
        array_tmp[0] = Vol_q;
        MODIFY_EEP_W(Addr_Vol_q, array_tmp, 1, 0xA0);
        //  while(Vol_q!=R_EEP(46))
        // W_EEP(46,Vol_q);
        MODIFY_EEP_W(Addr_over_vol, array_tmp, 6, 0xA0);
        // MODIFY_EEP_W(array_temp,Addr_over_vol,6,2);
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}

void Cur_uart_change(unsigned long tmp)
{

    unsigned char i, array_tmp[3];
    unsigned int fact1, fact2;
    if (Type_Cur == 0) // 100 20~100
    {

        D_Cur = tmp - 50;
        if (tmp < 50)
        {
            D_Cur = 0;
        }
        if (tmp > 125)
        {
            D_Cur = 75;
        }

        array_tmp[0] = D_Cur >> 8;
        array_tmp[1] = D_Cur & 0xFF;
        // W_EEP(0x08,D_Cur);//将新的额定负载电流写入E2
        MODIFY_EEP_W(Addr_D_Cur, array_tmp, 2, 0xA0);
        // Cur_Switch(Type_Cur);
        // while(D_Cur!=R_EEP(0x08))
        // W_EEP(0x08,D_Cur);
        Cur_Switch(Type_Cur);
        //		  Delta_Cur=D_Cur+50 ;
        //		H_Cur=1.21*Delta_Cur*Delta_Cur;
        //		H5_Cur=((260*Delta_Cur*Delta_Cur)*(R_SD[TH_Long_Cur]+3));
        //		DLD_Cur   =  (Delta_Cur*(2*D2_Cur+2));   //短延倍数之后数值
        //		I2=DLD_Cur;

        //		H_Cur=D_C1_Array[D_Cur];
        //		H5_Cur=D_C15_Array[D_Cur];
        //		I2=D_C19_Array[D_Cur];
    }
    if (Type_Cur == 1) // 250
    {
        D_Cur = tmp - 63;
        if (tmp < 63)
        {
            D_Cur = 0;
        }
        if (tmp > 250)
        {
            D_Cur = 187;
        }

        //		W_EEP(0x08,D_Cur);//将新的额定负载电流写入E2
        array_tmp[0] = D_Cur >> 8;
        array_tmp[1] = D_Cur & 0xFF;
        MODIFY_EEP_W(Addr_D_Cur, array_tmp, 2, 0xA0);
        Cur_Switch(Type_Cur);
        //	while(D_Cur!=R_EEP(0x08))
        //	W_EEP(0x08,D_Cur);
        //		H_Cur=D_C1_Array[D_Cur];
        //		H5_Cur=D_C15_Array[D_Cur];
        //		I2=D_C19_Array[D_Cur];
    }
    if (Type_Cur == 2) // 400
    {
        D_Cur = tmp - 160;
        if (tmp < 160)
        {
            D_Cur = 0; //
        }
        if (tmp > 400)
        {
            D_Cur = 240;
        }

        // W_EEP(0x08,D_Cur);//将新的额定负载电流写入E2
        array_tmp[0] = D_Cur >> 8;
        array_tmp[1] = D_Cur & 0xFF;
        MODIFY_EEP_W(Addr_D_Cur, array_tmp, 2, 0xA0);
        Cur_Switch(Type_Cur);
        // while(D_Cur!=R_EEP(0x08))
        // W_EEP(0x08,D_Cur);
        //		H_Cur=D_C1_Array[D_Cur];
        //		H5_Cur=D_C15_Array[D_Cur];
        //		I2=D_C19_Array[D_Cur];
    }
    if (Type_Cur == 3) // 750
    {

        D_Cur = tmp - 252;
        if (tmp < 252)
        {
            D_Cur = 0;
        }
        if (tmp > 630)
        {
            D_Cur = 378;
        }

        // putchar(D_Cur);
        // W_EEP(0x08,D_Cur);//将新的额定负载电流写入E2
        array_tmp[0] = D_Cur >> 8;
        array_tmp[1] = D_Cur & 0xFF;
        MODIFY_EEP_W(Addr_D_Cur, array_tmp, 2, 0xA0);
        Cur_Switch(Type_Cur);
        // while(D_Cur!=R_EEP(0x08))
        // W_EEP(0x08,D_Cur);
        //		H_Cur=D_C1_Array[D_Cur];
        //		H5_Cur=D_C15_Array[D_Cur];
        //		I2=D_C19_Array[D_Cur];
    }
}

// 写电流相关整定值
unsigned char Write_cur_setpoint(unsigned char fact_tmp)
{
    unsigned char i, array_temp[6], tmp1, tmp2, tmp3, tmp4, tmp5;
    if (fact_tmp == 1)
    {
        rated_current_code[0] = array_temp[0] = data_array[12 + 0];
        rated_current_code[1] = array_temp[1] = data_array[12 + 1];
        rated_current_code[2] = array_temp[2] = data_array[12 + 2];
        for (i = 0; i < 3; i++)
        {
            if (array_temp[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        tmp1 = (rated_current_code[0] >> 4); // 个
        // putchar(tmp1);
        tmp2 = (rated_current_code[1] & 0x0F); // 十
        // putchar(tmp2);
        tmp3 = (rated_current_code[1] >> 4); // 百
        // putchar(tmp3);
        tmp4 = (rated_current_code[2] & 0x0F); // 千
        // putchar(tmp4);
        tmp5 = (rated_current_code[2] >> 4); // 万
        // putchar(tmp5);
        rated_cur = tmp5 * 10000 + tmp4 * 1000 + tmp3 * 100 + tmp2 * 10 + tmp1;
        Cur_uart_change(rated_cur);
        MODIFY_EEP_W(Addr_rated_current, array_temp, 3, 0xA0);
        // MODIFY_EEP_W(array_temp,Addr_rated_current,3,2);
        return 0;
    }
    else if (fact_tmp == 2)
    {
        over_current_code[0] = array_temp[0] = data_array[12 + 0];
        if (array_temp[0] > 0x99)
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        MODIFY_EEP_W(Addr_over_current, over_current_code, 1, 0xA0);
        return 0;
    }
    else if (fact_tmp == 0xff)
    {
        for (i = 0; i < 4; i++)
        {
            if (array_temp[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        rated_current_code[0] = array_temp[0] = data_array[12 + 0];
        rated_current_code[1] = array_temp[1] = data_array[12 + 1];
        rated_current_code[2] = array_temp[2] = data_array[12 + 2];
        over_current_code[0] = array_temp[3] = data_array[12 + 3];
        for (i = 0; i < 3; i++)
        {
            if (array_temp[i] > 0x99)
            {
                ERR_data_sent(ERR_BAD_DATA);
                return 1;
            }
        }
        tmp1 = (rated_current_code[0] >> 4);   // 个
        tmp2 = (rated_current_code[1] & 0x0F); // 十
        tmp3 = (rated_current_code[1] >> 4);   // 百
        tmp4 = (rated_current_code[2] & 0x0F); // 千
        tmp5 = (rated_current_code[2] >> 4);   // 万
        rated_cur = tmp5 * 10000 + tmp4 * 1000 + tmp3 * 100 + tmp2 * 10 + tmp1;
        Cur_uart_change(rated_cur);
        MODIFY_EEP_W(Addr_over_current, over_current_code, 1, 0xA0);
        // MODIFY_EEP_W(over_current_code,Addr_over_current,1,2);
        // AT24C64_W(array_temp,Addr_over_current,4);
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}

// 写预分闸时间
unsigned char Write_fenzha_tim(unsigned char fact_tmp)
{
    unsigned char array_temp[6];
    if (fact_tmp == 1)
    {
        remote_trip_time[0] = array_temp[0] = data_array[12];
        remote_trip_time[1] = array_temp[1] = data_array[13];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        MODIFY_EEP_W(Addr_remote_trip, array_temp, 2, 0xA0);
        if (remote_trip_time[0] == 0)
        {
            if (isfenzha != 0)
            {
                F_yc_fenzha = 1;
            }
            // Trip_Action();
            // F_gz_disp = FZ_YC;
            // Write_Record(trip_reason_remote,1);
        }
        else
        {
            if (remote_trip_time[1] == 0x02) // 02为分  60S 1S有50MS  50*60
            {
                T_yc_fenzha = 3000 * remote_trip_time[0];
            }
            if (remote_trip_time[1] == 0x03) // 03表示小时
            {
                T_yc_fenzha = 60 * 3000 * remote_trip_time[0];
            }
            F_fenzha_js = 1;
        }
        return 0;
    }
    else if (fact_tmp == 2)
    {
        // 预分闸取消
        F_fenzha_js = 0;
        remote_trip_time[0] = remote_trip_time[1] = 0;
        T_yc_fenzha_js = 0;
        T_yc_fenzha = 0;

        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}
// 写预合闸时间
unsigned char Write_hezha_tim(unsigned char fact_tmp)
{
    unsigned char array_temp[6];
    if (fact_tmp == 1)
    {
        remote_close_time[0] = array_temp[0] = data_array[12];
        remote_close_time[1] = array_temp[1] = data_array[13];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        MODIFY_EEP_W(Addr_remote_close, array_temp, 2, 0xA0);
        if (remote_close_time[0] == 0)
        {
            if (isfenzha == 0)
            {
                F_yc_hezha = 1;
            }
            ctrl_code = 0x1C;
        }
        else
        {
            if (remote_close_time[1] == 0x02)
            {
                T_yc_hezha = 3000 * remote_close_time[0];
            }
            if (remote_close_time[1] == 0x03)
            {
                T_yc_hezha = 60 * 3000 * remote_close_time[0];
            }
            F_hezha_js = 1;
        }
        return 0;
    }
    else if (fact_tmp == 2)
    {
        // 预合闸取消
        F_hezha_js = 0;
        remote_close_time[0] = remote_close_time[1] = 0;
        T_yc_fenzha_js = 0;
        T_yc_fenzha = 0;
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}
// 写模拟脱扣时间
unsigned char Write_trip_tim(unsigned char fact_tmp)
{
    unsigned char array_temp[6];
    if (fact_tmp == 1)
    {
        analog_trip_time[0] = array_temp[0] = data_array[12];
        analog_trip_time[1] = array_temp[1] = data_array[13];
        if ((array_temp[0] > 0x99) || (array_temp[1] > 0x99))
        {
            ERR_data_sent(ERR_BAD_DATA);
            return 1;
        }
        MODIFY_EEP_W(Addr_analog_trip, array_temp, 2, 0xA0);
        // MODIFY_EEP_W(array_temp,Addr_analog_trip,2,2);
        if (analog_trip_time[0] == 0)
        {
            F_an_fenzha = 1;
        }
        else
        {

            if (analog_trip_time[1] == 0x02)
            {
                T_an_fenzha = 3000 * analog_trip_time[0];
            }
            if (analog_trip_time[1] == 0x03)
            {
                T_an_fenzha = 60 * 3000 * analog_trip_time[0];
            }
            F_an_js = 1;
        }
        return 0;
    }
    else if (fact_tmp == 2)
    {
        // 预分闸取消
        F_an_js = 0;
        analog_trip_time[0] = analog_trip_time[1] = 0;
        T_an_fenzha = 0;
        return 0;
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST);
        return 2;
    }
}

unsigned char Event_clear(void)
{
    unsigned char array_temp[20], F_clear_all;
    int Addr_factor, lenth;
    F_clear_all = 0;
    if ((DI3 == 0xFF) && (DI2 == 0xff) && (DI1 == 0xFF) && (DI0 == 0xFF))
    {
        F_clear_all = 1;
        Num_clearall = Num_clearall + 1;
        DectoBCD(array_temp, Num_clearall, 3);
        MODIFY_EEP_W(Addr_clear_num, array_temp, 3, 0xA0);
        return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x81) && (DI1 == 00) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        // 脱扣次数
        array_temp[0] = array_temp[1] = 0;
        MODIFY_EEP_W(Addr_trip_num, array_temp, 2, 0xA0);
        // close 次数
        array_temp[0] = array_temp[1] = 0;
        MODIFY_EEP_W(Addr_close_num, array_temp, 2, 0xA0);
        // 漏电脱扣次数
        array_temp[0] = array_temp[1] = 0;
        MODIFY_EEP_W(Addr_leak_num, array_temp, 2, 0xA0);
        // 电流脱扣次数
        array_temp[0] = array_temp[1] = 0;
        MODIFY_EEP_W(Addr_current_num, array_temp, 2, 0xA0);
        // 电压脱扣次数
        array_temp[0] = array_temp[1] = 0;
        MODIFY_EEP_W(Addr_vol_num, array_temp, 2, 0xA0);
        // 手动脱扣次数
        array_temp[0] = array_temp[1] = 0;
        MODIFY_EEP_W(Addr_hand_num, array_temp, 2, 0xA0);
        // 零相脱扣次数
        array_temp[0] = array_temp[1] = 0;
        MODIFY_EEP_W(Addr_zero_num, array_temp, 2, 0xA0);
        // 测试脱扣次数
        array_temp[0] = array_temp[1] = 0;
        MODIFY_EEP_W(Addr_test_num, array_temp, 2, 0xA0);
        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x82) && (DI1 == 00) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_max_leak;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x82) && (DI1 == 01) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_max_Avol;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x82) && (DI1 == 02) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_max_Bvol;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x82) && (DI1 == 03) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_max_Cvol;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x82) && (DI1 == 04) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_max_Acur;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x82) && (DI1 == 05) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_max_Bcur;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x82) && (DI1 == 06) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_max_Ccur;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);
        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x83) && (DI1 == 00) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_min_leak;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);
        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x83) && (DI1 == 01) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_min_Avol;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);
        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x83) && (DI1 == 02) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_min_Bvol;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x83) && (DI1 == 03) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_min_Cvol;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x83) && (DI1 == 04) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_min_Acur;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x83) && (DI1 == 05) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_min_Bcur;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x83) && (DI1 == 06) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_min_Ccur;
        lenth = 288;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }

    if (((DI3 == 0x03) && (DI2 == 0x88) && (DI1 == 00) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_event_leak;
        lenth = 150;
        //		EEPROM_C(Addr_factor,lenth);
        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x8D) && (DI1 == 00) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_event_self;
        lenth = 260;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x8E) && (DI1 == 00) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_event_trip;
        lenth = 250;
        //		EEPROM_C(Addr_factor,lenth);

        if (F_clear_all == 0)
            return 0;
    }
    if (((DI3 == 0x03) && (DI2 == 0x8F) && (DI1 == 00) && (DI0 == 0xFF)) || (F_clear_all == 1))
    {
        Addr_factor = Addr_event_alarm;
        lenth = 120;
        //		EEPROM_C(Addr_factor,lenth);

        // if(F_clear_all == 0)
        return 0;
    }
    return 1;
}
void UART_process(void)
{

    // unsigned char tmp_test[30];//根据指令处理
    // unsigned int i;
    // unsigned char pre_I_class,pre_L_class,pre_HV_class,pre_LV_class,pre_state,cs_temp;
    // cs_temp = 0;
    // delay();  //猜测发送过快而加上的延时2011.1.24晚
    // E485 = 1;
    // for(i=0;i<10000;i++);
    // COM_type = GETDATA;   //11 主站命令读数据 12读后续数据 14写数据 18修改密码 1C设备控制 请求动作
    if ((ctrl_code == 0x11) || (ctrl_code == 0x12) || (ctrl_code == 0x14) || (ctrl_code == 0x12) || (ctrl_code == 0x18) || (ctrl_code == 0x1C) || (ctrl_code == 0x1F) || (ctrl_code == 0x1E))
    {
        DI0 = data_array[0];
        DI1 = data_array[1];
        DI2 = data_array[2];
        DI3 = data_array[3];
    }
    else if (ctrl_code == 0x1B) //  请求清零
    {
        DI0 = data_array[8];
        DI1 = data_array[9];
        DI2 = data_array[10];
        DI3 = data_array[11];
    }
    /****************************
        广播
*****************************/

    if (ctrl_code == 0x08) // 0x08广播校时
    {
        DI0 = data_array[0];
        if (F_guangbo == 1)
        {

            F_guangbo = 0;
            Broadcasting_time();

            TXJZ_SJ = 1;
        }
    }

    else if (ctrl_code == 0x09) // 0x09  广播校准进退
    {
        DI0 = data_array[0];
        if (DI0 == 0x01) // 广播进入校准
        {
            unsigned char array_temp[5];

            TXJZ_start = 1;
            F_sssj = 10;

            nomal_disp();

            F_guangbo = 0;
            factor_first_init(0);

            Type_Cur = data_array[1];
            array_temp[0] = data_array[1];
            MODIFY_EEP_W(Addr_Type_Cur, array_temp, 1, 0xA0); // 电流壳架等级
            delay_ms(10);

            factors_init();
            delay_ms(50);

            //					  ctrlword[1]=0;
            //						ctrlword[2]=0;
            //					  ctrlword[3]=0;
            //						ctrlword2_analyze();
            //						ctrlword3_analyze();
            //					  ctrlword4_analyze();

            F_trip_ld = 1; // 漏电
            F_TB_trip = 0; // 突变
            F_trip_sy = 0; // 失压
            F_trip_xq = 0; // 缺相
            F_trip_gy = 0; // 过压
            F_trip_qy = 0; // 欠压
            F_trip_QL = 0; // 断零
            F_trip_gl = 0; // 过流
            F_ip = 0;      // 短延
            F_ip_3 = 0;    // 瞬时
            duandian = 0;  // 停电跳闸
        }

        else if (DI0 == 0x02) // 广播退出校准
        {
            unsigned char array_temp[30];

            //
            //				array_temp[0]=0x3C ;
            //				MODIFY_EEP_W(Addr_crtl_word1,array_temp,1,0xA0);
            //				 array_temp[0]=0xAA ;
            //				MODIFY_EEP_W(Addr_crtl_word2,array_temp,1,0xA0);
            //				array_temp[0]=0x00;
            //				MODIFY_EEP_W(Addr_crtl_word3,array_temp,1,0xA0);
            //				array_temp[0]=0x26 ;
            //				MODIFY_EEP_W(Addr_crtl_word4,array_temp,1,0xA0);
            //				array_temp[0]=0x60 ;
            //				MODIFY_EEP_W(Addr_crtl_word5,array_temp,1,0xA0);
            //
            //

            TXJZ_start = 0;
            F_sssj = 0;
            LEDA_FLAG = 1; // 背光灭开始计时

            TXJZ_SJ = 0;   // 通讯时间
            TXJZ_DY_A = 0; // 通讯电压
            TXJZ_DY_B = 0; // 通讯电压
            TXJZ_DY_C = 0; // 通讯电压
            TXJZ_LD = 0;   // 通讯漏电
            TXJZ_DL_A = 0; // 通讯电流
            TXJZ_DL_B = 0; // 通讯电流
            TXJZ_DL_C = 0; // 通讯电流

            //
            //					ctrlword[0]=0x3C ;   //开启定时试跳
            //					ctrlword[1]=0xAA ;
            //					ctrlword[2]=0x00;
            //					ctrlword[3]=0x26 ;	//漏电档位修改为1000//时间档位改成500ms
            //					ctrlword[4]=0x60 ;
            //
            //				ctrlword1_analyze();
            //				ctrlword2_analyze();
            //				ctrlword3_analyze();
            //				ctrlword4_analyze();

            EEPROM_R(Addr_crtl_word1, array_temp, 1, 0xA0);
            ctrlword[0] = array_temp[0];

            EEPROM_R(Addr_crtl_word2, array_temp, 1, 0xA0);
            ctrlword[1] = array_temp[0];
            EEPROM_R(Addr_crtl_word3, array_temp, 1, 0xA0);
            ctrlword[2] = array_temp[0];
            EEPROM_R(Addr_crtl_word4, array_temp, 1, 0xA0);
            ctrlword[3] = array_temp[0];
            EEPROM_R(Addr_crtl_word5, array_temp, 1, 0xA0);
            ctrlword[4] = array_temp[0];

            ctrlword1_analyze();
            ctrlword2_analyze();
            ctrlword3_analyze();
            ctrlword4_analyze();

            delay_ms(1000);
        }
    }
    /****************************
        功能码：0x11  读数据
*****************************/

    else if (ctrl_code == 0x11) // 读数据
    {
        if (DI3 == 0x02) // 当前变量
        {
            delay_uart();
            if (DI2 == 0x01)
            {
                Read_variable_vol(DI1, 2); // 读电压变量
            }
            else if (DI2 == 0x02)
            {
                Read_variable_cur(DI1, 3); // 读电流变量
            }
            else if (DI2 == 0x90)
            {
                Read_variable_leak(DI1); // 读剩余电流
            }
            else if (DI2 == 0x91)
            {
                Read_variable_leak_class(DI1, 2); // 读剩余电流档位  额定剩余电流动作值
            }
            else
            {
                ERR_data_sent(ERR_NO_REQUEST);
            }
        }
        else if (DI3 == 0x03) // 累计记录、最大值、事件记录
        {
            delay_uart();
            if ((DI2 == 0x30) && (DI1 == 0x01))
            {
                Read_num_dataclear(); // 数据清零次数
            }
            else if ((DI2 == 0x81) && (DI1 == 0x00))
            {
                Read_num_trip(DI0); // 读分闸次数
            }
            else if ((DI2 == 0x81) && (DI1 == 0x01) && (DI0 == 0x01))
            {
                // delay_uart();
                Read_num_protectoff(); // 读退出漏电保护次数
            }
            else if ((DI2 == 0x81) && (DI1 == 0x02) && (DI0 == 0x01))
            {
                // delay_uart();
                Read_time_run(); // 读保护器运行总时间
            }
            else if (DI2 == 0x82)
            {
                if (DI1 == 0x00)
                {
                    Read_max_leak(DI0); // 读剩余电流最大相
                }
                else if ((DI1 >= 0x01) && (DI1 <= 0x03))
                {
                    Read_max_vol(DI1, DI0); // 读电压最大值
                }
                else if ((DI1 >= 0x04) && (DI1 <= 0x06))
                {
                    Read_max_cur(DI1, DI0); // 读电流最大值
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (DI2 == 0x83)
            {

                if (DI1 == 0x00)
                {
                    Read_max_min_leak(DI0); // 读剩余电流最大值最小值
                }
                else if ((DI1 >= 0x01) && (DI1 <= 0x03))
                {
                    Read_max_min_vol(DI1, DI0); //  A B C读电压最大值，最小值
                }
                else if ((DI1 >= 0x04) && (DI1 <= 0x06))
                {
                    Read_max_min_cur(DI1, DI0); // A B C读电流最大值，最小值
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (DI2 == 0x88)
            {
                Read_event_leakover(DI0); // 剩余电流超限  DI0次数
            }
            else if (DI2 == 0x8D)
            {
                Read_event_leakself(DI0); // 保护器自检  DI0次数
            }
            else if (DI2 == 0x8E)
            {
                Read_event_leaktrip(DI0); // 保护器跳闸  DI0次数
            }
            else if (DI2 == 0x8F)
            {
                Read_event_leakalarm(DI0); // 剩余电流报警   DI0次数
            }
            else if (DI2 == 0x90)
            {
                Read_event_leakrecord(DI1, DI0); // 剩余电流记录   DI0次数
            }
            else
            {
                ERR_data_sent(ERR_NO_REQUEST);
            }
        }
        else if (DI3 == 0x04) // 参数变量
        {
            delay_uart();
            if (DI1 == 0x01)
            {
                Read_time(DI0); // 获取当前时间
            }
            else if (DI1 == 0x04)
            {
                Read_factors(DI0); // 获取当前参数
            }
            else if (DI1 == 0x05)
            {
                Read_state(DI0); // 获取当前运行状态字
            }
            else if (DI1 == 0x07)
            {
                Read_baud(DI0); // 获取当前波特率
            }
            else if (DI1 == 0x0C)
            {
                // Read_password(DI0);//获取当前密码
            }
            else if (DI1 == 0x10)
            {
                Read_ctrlword(DI0); // 获取当前控制字
            }
            else if (DI1 == 0x11)
            {
                Read_leakctrl(DI0); // 获取漏电控制参数
            }
            else if (DI1 == 0x12)
            {
                Read_timing(DI0); // 获取定时试跳时间
            }
            else if (DI1 == 0x13)
            {
                Read_vol_setpoint(DI0); // 获取电压相关整定值
            }
            else if (DI1 == 0x14)
            {
                Read_cur_setpoint(DI0); // 获取电流相关整定值
            }
            else
            {
                ERR_data_sent(ERR_NO_REQUEST);
            }
        }
        else if (DI3 == 0x06) // 分合闸时间
        {
            delay_uart();
            if (DI2 == 0x01)
            {
                if (DI1 == 0x01)
                {
                    Read_fenzha_tim(DI0);
                }
                else if (DI1 == 0x02)
                {
                    Read_hezha_tim(DI0);
                }
                else if (DI1 == 0x03)
                {
                    Read_trip_tim(DI0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
        }
        else
        {
            ERR_data_sent(ERR_NO_REQUEST);
        }
    }

    /****************************
        功能码：0x1E   读瞬动、电压、电流、漏电校准数据
*****************************/
    else if (ctrl_code == 0x1E) // 读瞬动数据
    {
        if (DI3 == 0x03) // 读瞬动校准数据
        {
            delay_uart();
            if (DI2 == 0x01)
            {
                if (DI1 == 0x01)
                {
                    Read_SD_AD_Value(DI0, 3); // 读瞬动AD值
                }
                else if (DI1 == 0x02)
                {
                    Read_SD_Slope_Value(DI0, 3); // 读瞬动斜率值
                }
                else if (DI1 == 0x03)
                {
                    Read_SD_Value(DI0, 3); // 读瞬动电流值
                }
                //				Read_variable_vol(DI1,2);//读变量
            }
            else if (DI2 == 0x02)
            {
            }
        }

        else if (DI3 == 0x04) // 读电流校准数据
        {
            if (DI1 == 0x01)
            {
                Read_DL_AD_Value(DI2, DI0); // 读电流AD值
            }
            else if (DI1 == 0x02)
            {
                Read_DL_XL_Value(DI2, DI0); // 读电流斜率值
            }
        }

        else if (DI3 == 0x05) // 读电压
        {

            Read_DY_XL_Value(DI2); // 读漏电斜率值
        }

        else if (DI3 == 0x06) // 读漏电校准数据
        {

            Read_LD_XL_Value(); // 读漏电斜率值
        }
    }

    /****************************
        功能码：0x12  读后续数据
*****************************/
    else if (ctrl_code == 0x12) // 读后续数据
    {
    }
    /****************************
        功能码：0x13  读通信地址
*****************************/
    else if (ctrl_code == 0x13) // 读通信地址
    {
        delay_uart();
        if (F_addr == 1)
        {
            F_addr = 0;
            Read_addr();
        }
    }
    /****************************
        功能码：0x14  写数据
*****************************/
    else if (ctrl_code == 0x14) // 写数据
    {
        if ((Password_verification(0) == 0) || (Password_verification(0) == 1) || (Password_verification(0) == 2)) // 密码验证通过
        {
            if (DI3 == 0x04) // 参数变量
            {
                delay_uart();
                if (DI1 == 0x01)
                {
                    if (Write_time(DI0) == 0) // 写当前时间
                    {
                        WRITE_DATA_NOMAL();
                    }
                }
                else if (DI1 == 0x04)
                {
                    if (Write_factors(DI0) == 0) // 写当前参数
                    {
                        WRITE_DATA_NOMAL();
                    }
                }
                /* else if(DI1==0x07)
            {
                Write_baud(DI0);//写当前波特率
            }*/
                else if (DI1 == 0x0C)
                {
                    if (Write_password(DI0) == 0) // 写当前密码
                    {
                        WRITE_DATA_NOMAL();
                    }
                }
                else if (DI1 == 0x10)
                {
                    if (Write_ctrlword(DI0) == 0) // 写当前控制字
                    {
                        WRITE_DATA_NOMAL();
                    }
                }
                else if (DI1 == 0x11)
                {
                    if (Write_leakctrl(DI0) == 0) // 写漏电控制参数
                    {
                        WRITE_DATA_NOMAL();
                    }
                }
                else if (DI1 == 0x12)
                {
                    if (Write_timing(DI0) == 0) // 写定时试跳时间
                    {
                        WRITE_DATA_NOMAL();
                    }
                }
                else if (DI1 == 0x13)
                {
                    if (Write_vol_setpoint(DI0) == 0) // 写电压相关整定值
                    {
                        WRITE_DATA_NOMAL();
                    }
                }
                else if (DI1 == 0x14)
                {
                    if (Write_cur_setpoint(DI0) == 0) // 写电流相关整定值
                    {
                        WRITE_DATA_NOMAL();
                    }
                }
                else if (DI1 == 0x15)
                {
                    if (Write_hezha_delay(DI0) == 0) // 写合闸延时时间
                    {
                        WRITE_DATA_NOMAL();
                    }
                }

                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else
            {
                ERR_data_sent(ERR_NO_REQUEST);
            }
        }
        else
        {
            ERR_data_sent(ERR_BAD_PASSWORD);
        }
    }

    /****************************
        功能码:0x15  写通信地址
*****************************/
    else if (ctrl_code == 0x15) // 写通信地址
    {
        // if(get_bit(PINC,0)==0)
        {
            delay_uart();
            if (F_addr == 1)
            {
                F_addr = 0;
                Write_addr();
            }
        }
    }

    /****************************
        功能码：0x17  更改通信速率
*****************************/
    else if (ctrl_code == 0x17) // 更改通信速率
    {
        unsigned char i, cs_temp = 0;
        delay_uart();
        if (Write_baud(0) == 0)
        {
            format_uart_t_buf();
            UART_T_Buf[0] = UART_T_Buf[7] = 0x68;
            for (i = 0; i < 6; i++)
            {
                UART_T_Buf[i + 1] = self_addr_code[i];
            }
            UART_T_Buf[8] = ctrl_code + 0x80;
            UART_T_Buf[9] = 0x01;
            UART_T_Buf[10] = baud + 0x33;
            for (i = 0; i < 11; i++)
            {
                cs_temp = UART_T_Buf[i] + cs_temp;
            }
            UART_T_Buf[11] = cs_temp;
            UART_T_Buf[12] = 0x16;
            // 20150202北京测试修改
            //			for(i=0;i<(13);i++)
            for (i = 0; i < 4; i++)
            {
                UART_S_Buf[i] = 0xFE;
            }
            if (F_Dataval == 1)
            {
                // RS485_Send_Data(UART_S_Buf,4);
                // RS485_Send_Data(UART_T_Buf,14);
            }
            if (F_Dataval1 == 1)
            {
                // hongwai_Send_Data(UART_T_Buf,14);
            }
            //			//RS485_Send_Data(UART_T_Buf,14);
            //			put2char(UART_T_Buf[i]);

            delay_ms(25);
            if (baud == 3)
            {
                RS485_Init(9600);
            }
            else if (baud == 2)
            {
                RS485_Init(4800);
            }
            else if (baud == 1)
            {
                RS485_Init(2400);
            }
            else if (baud == 0)
            {
                RS485_Init(1200);
            }
        }
    }
    /****************************
        功能码：0x18  修改密码
*****************************/
    else if (ctrl_code == 0x18) // 修改密码
    {
        unsigned char i, cs_temp = 0, array_temp[10], F_err;
        //		delay_uart();
        //		for(i=0;i<4;i++)
        //		{
        //			put2char(password_0class[i]);
        //		}
        //		for(i=0;i<4;i++)
        //		{
        //			put2char(password_1class[i]);
        //		}
        //		for(i=0;i<4;i++)
        //		{
        //			put2char(password_2class[i]);
        //		}
        //
        if (DI0 == 0x01)
        {
            if ((Password_verification(0) == 0))
            {
                for (i = 0; i < 4; i++)
                {
                    array_temp[i] = data_array[8 + i];
                    password_0class[i] = data_array[8 + i];
                    if (array_temp[i] > 0x99)
                    {
                        ERR_data_sent(ERR_BAD_DATA);
                    }
                }

                format_uart_t_buf();
                UART_T_Buf[0] = UART_T_Buf[7] = 0x68;
                for (i = 0; i < 6; i++)
                {
                    UART_T_Buf[i + 1] = self_addr_code[i];
                }
                UART_T_Buf[8] = ctrl_code + 0x80;
                UART_T_Buf[9] = 0x04;
                UART_T_Buf[10] = password_0class[0] + 0x33;
                UART_T_Buf[11] = password_0class[1] + 0x33;
                UART_T_Buf[12] = password_0class[2] + 0x33;
                UART_T_Buf[13] = password_0class[3] + 0x33;
                for (i = 0; i < 14; i++)
                {
                    cs_temp = UART_T_Buf[i] + cs_temp;
                }
                UART_T_Buf[14] = cs_temp;
                UART_T_Buf[15] = 0x16;
                // 20150202北京测试修改
                for (i = 0; i < 4; i++)
                {
                    UART_S_Buf[i] = 0xFE;
                }
                if (F_Dataval == 1)
                {
                    // RS485_Send_Data(UART_S_Buf,4);
                    // RS485_Send_Data(UART_T_Buf,14);
                }
                if (F_Dataval1 == 1)
                {
                    // hongwai_Send_Data(UART_T_Buf,14);
                }
                MODIFY_EEP_W(Addr_0_password, password_0class, 4, 0xA0);
            }
            else
            {
                ERR_data_sent(ERR_BAD_PASSWORD);
            }
        }
        else if (DI0 == 0x02)
        {
            if ((Password_verification(0) == 0) || (Password_verification(0) == 1))
            {
                for (i = 0; i < 4; i++)
                {
                    array_temp[i] = data_array[8 + i];
                    password_1class[i] = data_array[8 + i];
                    if (array_temp[i] > 0x99)
                    {
                        ERR_data_sent(ERR_BAD_DATA);
                    }
                }

                format_uart_t_buf();
                UART_T_Buf[0] = UART_T_Buf[7] = 0x68;
                for (i = 0; i < 6; i++)
                {
                    UART_T_Buf[i + 1] = self_addr_code[i];
                }
                UART_T_Buf[8] = ctrl_code + 0x80;
                UART_T_Buf[9] = 0x04;
                UART_T_Buf[10] = password_1class[0] + 0x33;
                UART_T_Buf[11] = password_1class[1] + 0x33;
                UART_T_Buf[12] = password_1class[2] + 0x33;
                UART_T_Buf[13] = password_1class[3] + 0x33;
                for (i = 0; i < 14; i++)
                {
                    cs_temp = UART_T_Buf[i] + cs_temp;
                }
                UART_T_Buf[14] = cs_temp;
                UART_T_Buf[15] = 0x16;
                // 20150202北京测试修改
                for (i = 0; i < 4; i++)
                {
                    UART_S_Buf[i] = 0xFE;
                }
                if (F_Dataval == 1)
                {
                    // RS485_Send_Data(UART_S_Buf,4);
                    // RS485_Send_Data(UART_T_Buf,14);
                }
                if (F_Dataval1 == 1)
                {
                    // hongwai_Send_Data(UART_T_Buf,14);
                }
                MODIFY_EEP_W(Addr_1_password, password_1class, 4, 0xA0);
            }
            else
            {
                ERR_data_sent(ERR_BAD_PASSWORD);
            }
        }
        else if (DI0 == 0x03)
        {
            if ((Password_verification(0) == 0) || (Password_verification(0) == 1) || (Password_verification(0) == 2))
            {
                for (i = 0; i < 4; i++)
                {
                    array_temp[i] = data_array[8 + i];
                    password_2class[i] = data_array[8 + i];
                    if (array_temp[i] > 0x99)
                    {
                        ERR_data_sent(ERR_BAD_DATA);
                    }
                }

                format_uart_t_buf();
                UART_T_Buf[0] = UART_T_Buf[7] = 0x68;
                for (i = 0; i < 6; i++)
                {
                    UART_T_Buf[i + 1] = self_addr_code[i];
                }
                UART_T_Buf[8] = ctrl_code + 0x80;
                UART_T_Buf[9] = 0x04;
                UART_T_Buf[10] = password_2class[0] + 0x33;
                UART_T_Buf[11] = password_2class[1] + 0x33;
                UART_T_Buf[12] = password_2class[2] + 0x33;
                UART_T_Buf[13] = password_2class[3] + 0x33;
                for (i = 0; i < 14; i++)
                {
                    cs_temp = UART_T_Buf[i] + cs_temp;
                }
                UART_T_Buf[14] = cs_temp;
                UART_T_Buf[15] = 0x16;
                // 20150202北京测试修改
                for (i = 0; i < 4; i++)
                {
                    UART_S_Buf[i] = 0xFE;
                }
                if (F_Dataval == 1)
                {
                    // RS485_Send_Data(UART_S_Buf,4);
                    // RS485_Send_Data(UART_T_Buf,14);
                }
                if (F_Dataval1 == 1)
                {
                    // hongwai_Send_Data(UART_T_Buf,14);
                }
                MODIFY_EEP_W(Addr_2_password, password_2class, 4, 0xA0);
            }
            else
            {
                ERR_data_sent(ERR_BAD_PASSWORD);
            }
        }
        else
        {
            ERR_data_sent(ERR_BAD_PASSWORD);
        }
        delay_uart();
        F_err = 0;
        if (DI0 == 0x01) // 修改0级密码，必须是0级密码与原密码相同
        {
            for (i = 0; i < 4; i++)
            {
                if (data_array[8 + i] > 0x99)
                {
                    F_err = 1;
                }
            }
            if (F_err == 1)
            {
                ERR_data_sent(ERR_BAD_PASSWORD);
            }
            else
            {
                if ((Password_verification(0) == 0))
                {
                    for (i = 0; i < 4; i++)
                    {
                        password_0class[i] = data_array[8 + i];
                    }
                    format_uart_t_buf();
                    UART_T_Buf[0] = UART_T_Buf[7] = 0x68;
                    for (i = 0; i < 6; i++)
                    {
                        UART_T_Buf[i + 1] = self_addr_code[i];
                    }
                    UART_T_Buf[8] = ctrl_code + 0x80;
                    UART_T_Buf[9] = 0x04;
                    UART_T_Buf[10] = password_0class[0] + 0x33;
                    UART_T_Buf[11] = password_0class[1] + 0x33;
                    UART_T_Buf[12] = password_0class[2] + 0x33;
                    UART_T_Buf[13] = password_0class[3] + 0x33;
                    for (i = 0; i < 14; i++)
                    {
                        cs_temp = UART_T_Buf[i] + cs_temp;
                    }
                    UART_T_Buf[14] = cs_temp;
                    UART_T_Buf[15] = 0x16;
                    // 20150202北京测试修改
                    for (i = 0; i < 4; i++)
                    {
                        UART_S_Buf[i] = 0xFE;
                    }
                    if (F_Dataval == 1)
                    {
                        // RS485_Send_Data(UART_S_Buf,4);
                        // RS485_Send_Data(UART_T_Buf,14);
                    }
                    if (F_Dataval1 == 1)
                    {
                        // hongwai_Send_Data(UART_T_Buf,14);
                    }
                    MODIFY_EEP_W(Addr_0_password, password_0class, 4, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_BAD_PASSWORD);
                }
            }
        }
        else if (DI0 == 0x02) // 修改1级密码，0级密码和1级密码有效
        {
            for (i = 0; i < 4; i++)
            {
                if (data_array[8 + i] > 0x99)
                {
                    F_err = 1;
                }
            }
            if (F_err == 1)
            {
                ERR_data_sent(ERR_BAD_PASSWORD);
            }
            else
            {
                if ((Password_verification(0) == 0) || (Password_verification(0) == 1))
                {
                    for (i = 0; i < 4; i++)
                    {
                        password_1class[i] = data_array[8 + i];
                    }

                    format_uart_t_buf();
                    UART_T_Buf[0] = UART_T_Buf[7] = 0x68;
                    for (i = 0; i < 6; i++)
                    {
                        UART_T_Buf[i + 1] = self_addr_code[i];
                    }
                    UART_T_Buf[8] = ctrl_code + 0x80;
                    UART_T_Buf[9] = 0x04;
                    UART_T_Buf[10] = password_1class[0] + 0x33;
                    UART_T_Buf[11] = password_1class[1] + 0x33;
                    UART_T_Buf[12] = password_1class[2] + 0x33;
                    UART_T_Buf[13] = password_1class[3] + 0x33;
                    for (i = 0; i < 14; i++)
                    {
                        cs_temp = UART_T_Buf[i] + cs_temp;
                    }
                    UART_T_Buf[14] = cs_temp;
                    UART_T_Buf[15] = 0x16;
                    // 20150202北京测试修改
                    for (i = 0; i < 4; i++)
                    {
                        UART_S_Buf[i] = 0xFE;
                    }
                    if (F_Dataval == 1)
                    {
                        // RS485_Send_Data(UART_S_Buf,4);
                        // RS485_Send_Data(UART_T_Buf,14);
                    }
                    if (F_Dataval1 == 1)
                    {
                        // hongwai_Send_Data(UART_T_Buf,14);
                    }
                    MODIFY_EEP_W(Addr_1_password, password_1class, 4, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_BAD_PASSWORD);
                }
            }
        }
        else if (DI0 == 0x03) // 修改2级密码，0级密码和1级密码和2级密码有效
        {
            for (i = 0; i < 4; i++)
            {
                if (data_array[8 + i] > 0x99)
                {
                    F_err = 1;
                }
            }
            if (F_err == 1)
            {
                ERR_data_sent(ERR_BAD_PASSWORD);
            }
            else
            {
                if ((Password_verification(0) == 0) || (Password_verification(0) == 1) || (Password_verification(0) == 2))
                {
                    for (i = 0; i < 4; i++)
                    {
                        password_2class[i] = data_array[8 + i];
                    }

                    format_uart_t_buf();
                    UART_T_Buf[0] = UART_T_Buf[7] = 0x68;
                    for (i = 0; i < 6; i++)
                    {
                        UART_T_Buf[i + 1] = self_addr_code[i];
                    }
                    UART_T_Buf[8] = ctrl_code + 0x80;
                    UART_T_Buf[9] = 0x04;
                    UART_T_Buf[10] = password_2class[0] + 0x33;
                    UART_T_Buf[11] = password_2class[1] + 0x33;
                    UART_T_Buf[12] = password_2class[2] + 0x33;
                    UART_T_Buf[13] = password_2class[3] + 0x33;
                    for (i = 0; i < 14; i++)
                    {
                        cs_temp = UART_T_Buf[i] + cs_temp;
                    }
                    UART_T_Buf[14] = cs_temp;
                    UART_T_Buf[15] = 0x16;
                    // 20150202北京测试修改
                    for (i = 0; i < 4; i++)
                    {
                        UART_S_Buf[i] = 0xFE;
                    }
                    if (F_Dataval == 1)
                    {
                        // RS485_Send_Data(UART_S_Buf,4);
                        // RS485_Send_Data(UART_T_Buf,14);
                    }
                    if (F_Dataval1 == 1)
                    {
                        // hongwai_Send_Data(UART_T_Buf,14);
                    }
                    MODIFY_EEP_W(Addr_2_password, password_2class, 4, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_BAD_PASSWORD);
                }
            }
        }
        else
        {
            ERR_data_sent(ERR_BAD_PASSWORD);
        }
    }
    /****************************
        功能码：0x19  设备告警
*****************************/
    else if (ctrl_code == 0x19) // 设备告警
    {
    }
    /****************************
        功能码：0x1A  设备告警应答
*****************************/
    else if (ctrl_code == 0x1A) // 设备告警应答
    {
    }
    /****************************
        功能码：0x1B  事件清零
*****************************/
    else if (ctrl_code == 0x1B) // 事件清零
    {
        if (Password_verification(1) == 0)
        {
            if (Event_clear() == 0)
            {
                WRITE_DATA_NOMAL();
            }
        }
        else
        {
            ERR_data_sent(ERR_BAD_PASSWORD);
        }
    }

    /****************************
        功能码:0x1C  设备控制
*****************************/
    else if (ctrl_code == 0x1C) // 设备控制
    {
        F_yc = 1;
        delay_uart();
        if (F_yc == 1)
        {
            if ((Password_verification(0) == 0) || (Password_verification(0) == 1) || (Password_verification(0) == 2))
            {
                if (DI3 == 0x06)
                {
                    if (DI2 == 0x01)
                    {
                        if (DI1 == 0x01)
                        {
                            if (Write_fenzha_tim(DI0) == 0)
                            {
                                WRITE_DATA_NOMAL();
                            }
                        }
                        else if (DI1 == 0x02)
                        {
                            if (Write_hezha_tim(DI0) == 0)
                            {
                                WRITE_DATA_NOMAL();
                            }
                        }
                        else if (DI1 == 0x03)
                        {
                            if (Write_trip_tim(DI0) == 0)
                            {
                                WRITE_DATA_NOMAL();
                            }
                        }
                        else
                        {
                            ERR_data_sent(ERR_NO_REQUEST);
                        }
                    }
                    else
                    {
                        ERR_data_sent(ERR_NO_REQUEST);
                    }
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else
            {
                ERR_data_sent(ERR_BAD_PASSWORD); // 密码错误
            }
        }
        else
        {
            ERR_data_sent(ERR_NO_REMOTE); //  远程控制失败
        }
    }
    else if (ctrl_code == 0x1F) // 内部规约
    {
        //                                   控制码 L  D3 D2 D1 D0
        // 剩余电流系数1  50mA  frame：68 addr 68 1F 04 01 00 00 50 校验 16
        // 剩余电流系数2 100mA  frame：68 addr 68 1F 04 01 01 01 00 校验 16
        // 剩余电流系数3 300mA  frame：68 addr 68 1F 04 01 02 03 00 校验 16

        // 电压ABC 系数1  150V  frame：68 addr 68 1F 04 02 01 01 70 校验 16
        // 电压ABC 系数2  220V  frame：68 addr 68 1F 04 02 02 02 20 校验 16
        // 电压ABC 系数3  280V  frame：68 addr 68 1F 04 02 03 02 80 校验 16

        // 电流ABC 系数1   50A  frame：68 addr 68 1F 04 03 01 00 50 校验 16
        // 电流ABC 系数2  100A  frame：68 addr 68 1F 04 03 02 01 00 校验 16
        // 电流ABC 系数3  300A  frame：68 addr 68 1F 04 03 03 03 00 校验 16
        // 电流ABC 系数4  500A  frame：68 addr 68 1F 04 03 04 05 00 校验 16
        // 电流ABC 系数5  800A  frame：68 addr 68 1F 04 03 05 08 00 校验 16

        if (DI3 == 0x02) //
        {
            unsigned int cal_factor;
            unsigned char array_temp[3], i;
            for (i = 0; i < 3; i++)
            {
                array_temp[i] = data_array[12 + i];
            }
            cal_factor = BCDtoDec(array_temp, 3);
            if (DI2 == 0x01) // 电压
            {
                vol_uart_cal_handle(DI1, DI0, cal_factor);
            }
            else if (DI2 == 0x02) // 电流
            {

                cur_uart_cal_handle(DI1, DI0, cal_factor);
            }
            else if (DI2 == 0x03) // 200mA漏电
            {

                leak_uart_cal_handle();

                TXJZ_LD = 1;
            }
            else if (DI2 == 0x04) // 瞬动校准
            {

                SD_uart_cal_handle(DI1, DI0, cal_factor); // 瞬动：DI1：AD/斜率；DI0第几个点；
                //				WRITE_DATA_NOMAL();
            }
            //			else
            //			{
            //				ERR_data_sent(ERR_NO_REQUEST);
            //			}
            //
        }
    }
    else
    {
        ERR_data_sent(ERR_NO_REQUEST); // 无请求
    }
}
void vol_uart_cal_handle(unsigned char tmp, unsigned char temp, unsigned value)
{
    // tmp相位     temp点数(没用）    value要校准的值

    unsigned char array_temp[2], array_tmp[2];

    unsigned char array_temp_1[2];
    unsigned short int Vol_cal_tmp, L_cal_tmp = 200;
    signed int L_factor_tmp1, I_A_factor_tmp, V_A_factor_tmp, I_B_factor_tmp, V_B_factor_tmp, I_C_factor_tmp, V_C_factor_tmp;
    Vol_cal_tmp = 220;

    if (tmp == 1)
    {
        //	            Vol_cal_tmp=value;
        Vol1_A_temp = V_Array_disp[0];                                // V_Array_disp/V_Array
        V_A_factor_tmp = vol_handle_A(V_Array_disp[0]) - Vol_cal_tmp; // A电压校准
        V1_slope[0] = (Vol_cal_tmp << 20) / (Vol1_A_temp);
        HexToChar(array_temp, V1_slope[0], 2);
        MODIFY_EEP_W(Addr_V1_A_slope, array_temp, 2, 0xA0);
        delay_ms(5);

        /*****************2022.5.4怕写错新增************************/
        EEPROM_R(Addr_V1_A_slope, array_temp_1, 2, 0xA0);
        if ((array_temp_1[0] != array_temp[0]) || (array_temp_1[1] != array_temp[1]))
        {

            V1_slope[0] = (Vol_cal_tmp << 20) / (Vol1_A_temp);
            HexToChar(array_temp, V1_slope[0], 2);
            MODIFY_EEP_W(Addr_V1_A_slope, array_temp, 2, 0xA0);
            delay_ms(5);
            // 读出
            EEPROM_R(Addr_V1_A_slope, array_temp, 2, 0xA0);
            V1_slope[0] = (array_temp[1] << 8) + array_temp[0];
        }
        else
        {
            V1_slope[0] = (array_temp_1[1] << 8) + array_temp_1[0];
        }

        /**********************************************************/

        HexToChar(array_tmp, Vol1_A_temp, 2);
        MODIFY_EEP_W(Addr_Vol1_A_temp, array_tmp, 2, 0xA0);
        delay_ms(5);
        TXJZ_DY_A = 1;
    }

    else if (tmp == 2)
    {
        //					  Vol_cal_tmp=value;
        Vol1_B_temp = V_Array_disp[1];
        V_B_factor_tmp = vol_handle_B(V_Array_disp[1]) - Vol_cal_tmp; // B电压校准
        V1_slope[1] = (Vol_cal_tmp << 20) / (Vol1_B_temp);
        HexToChar(array_temp, V1_slope[1], 2);
        MODIFY_EEP_W(Addr_V1_B_slope, array_temp, 2, 0xA0);
        delay_ms(5);

        /*****************2022.5.4怕写错新增************************/
        EEPROM_R(Addr_V1_B_slope, array_temp_1, 2, 0xA0);
        if ((array_temp_1[0] != array_temp[0]) || (array_temp_1[1] != array_temp[1]))
        {

            V1_slope[1] = (Vol_cal_tmp << 20) / (Vol1_B_temp);
            HexToChar(array_temp, V1_slope[1], 2);
            MODIFY_EEP_W(Addr_V1_B_slope, array_temp, 2, 0xA0);
            delay_ms(5);

            EEPROM_R(Addr_V1_B_slope, array_temp, 2, 0xA0);
            V1_slope[1] = (array_temp[1] << 8) + array_temp[0];
        }
        else
        {
            V1_slope[1] = (array_temp_1[1] << 8) + array_temp_1[0];
        }

        /**********************************************************/

        HexToChar(array_tmp, Vol1_B_temp, 2);
        MODIFY_EEP_W(Addr_Vol1_B_temp, array_tmp, 2, 0xA0);
        delay_ms(5);
        TXJZ_DY_B = 1;
    }

    else if (tmp == 3)
    {
        //					 Vol_cal_tmp=value;
        Vol1_C_temp = V_Array_disp[2];
        V_C_factor_tmp = vol_handle_C(V_Array_disp[2]) - Vol_cal_tmp; // C电压校准

        V1_slope[2] = (Vol_cal_tmp << 20) / (Vol1_C_temp);
        HexToChar(array_temp, V1_slope[2], 2);
        MODIFY_EEP_W(Addr_V1_C_slope, array_temp, 2, 0xA0);
        delay_ms(5);

        /*****************2022.5.4怕写错新增************************/
        EEPROM_R(Addr_V1_C_slope, array_temp_1, 2, 0xA0);
        if ((array_temp_1[0] != array_temp[0]) || (array_temp_1[1] != array_temp[1]))
        {

            V1_slope[2] = (Vol_cal_tmp << 20) / (Vol1_C_temp);
            HexToChar(array_temp, V1_slope[2], 2);
            MODIFY_EEP_W(Addr_V1_C_slope, array_temp, 2, 0xA0);
            delay_ms(5);

            EEPROM_R(Addr_V1_C_slope, array_temp, 2, 0xA0);
            V1_slope[2] = (array_temp[1] << 8) + array_temp[0];
        }
        else
        {
            V1_slope[2] = (array_temp_1[1] << 8) + array_temp_1[0];
        }
        /**********************************************************/

        HexToChar(array_tmp, Vol1_C_temp, 2);
        MODIFY_EEP_W(Addr_Vol1_C_temp, array_tmp, 2, 0xA0);
        delay_ms(5);
        TXJZ_DY_C = 1;
    }
}

void cur_uart_cal_handle(unsigned char tmp, unsigned char temp, unsigned value)
{

    unsigned long Cur_cal_tmp[2] = {100, 250}; // 500
    // tmp相位,temp校准点，value校准点的值

    unsigned char array_temp[2], array_tmp[2];
    unsigned short int Vol_cal_tmp, L_cal_tmp = 200;
    signed int L_factor_tmp1, I_A_factor_tmp, V_A_factor_tmp, I_B_factor_tmp, V_B_factor_tmp, I_C_factor_tmp, V_C_factor_tmp;

    if (Type_Cur == 0)
    {
        Cur_cal_tmp[0] = 50;
        Cur_cal_tmp[1] = 125;
    }

    if (Type_Cur == 1)
    {
        Cur_cal_tmp[0] = 100;
        Cur_cal_tmp[1] = 250;
    }
    else if (Type_Cur == 2)
    {
        Cur_cal_tmp[0] = 160;
        Cur_cal_tmp[1] = 400;
    }
    else if (Type_Cur == 3)
    {
        Cur_cal_tmp[0] = 252;
        Cur_cal_tmp[1] = 630;
    }
    else if (Type_Cur == 4)
    {
        Cur_cal_tmp[0] = 320;
        Cur_cal_tmp[1] = 800;
    }

    if (temp == 1) // 电流校准100A
    {
        if (tmp == 1)
        {
            CurA_cal_tmp[0] = I_I_Array_xianshi[0]; // I_I_Array_xianshi//I_Array_xianshi
            I_A_factor_tmp = cur_handle_A(I_I_Array_xianshi[0]) - Cur_cal_tmp[0];
            I1_A_slope[0] = (Cur_cal_tmp[0] << 20) / (CurA_cal_tmp[0]); // A电流校准点1
            HexToChar(array_temp, I1_A_slope[0], 2);
            HexToChar(array_tmp, CurA_cal_tmp[0], 2);
            if (Type_Cur == 0)
            {
                MODIFY_EEP_W(Addr100_I1_A_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr100_CurA_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 1)
            {
                MODIFY_EEP_W(Addr_I1_A_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr_CurA_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 2)
            {
                MODIFY_EEP_W(Addr400_I1_A_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr400_CurA_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 3)
            {
                MODIFY_EEP_W(Addr630_I1_A_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr630_CurA_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 4)
            {
                MODIFY_EEP_W(Addr800_I1_A_slope, array_temp, 2, 0xA0);
                MODIFY_EEP_W(Addr800_CurA_cal_tmp, array_tmp, 2, 0xA0);
            }
            TXJZ_DL_A = 1;
        }

        else if (tmp == 2)
        {
            CurB_cal_tmp[0] = I_I_Array_xianshi[1];
            I_B_factor_tmp = cur_handle_B(I_I_Array_xianshi[1]) - Cur_cal_tmp[0];
            I1_B_slope[0] = (Cur_cal_tmp[0] << 20) / (CurB_cal_tmp[0]); // B电流校准点1
            HexToChar(array_temp, I1_B_slope[0], 2);
            HexToChar(array_tmp, CurB_cal_tmp[0], 2);
            if (Type_Cur == 0)
            {
                MODIFY_EEP_W(Addr100_I1_B_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr100_CurB_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 1)
            {
                MODIFY_EEP_W(Addr_I1_B_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr_CurB_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 2)
            {
                MODIFY_EEP_W(Addr400_I1_B_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr400_CurB_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 3)
            {
                MODIFY_EEP_W(Addr630_I1_B_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr630_CurB_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 4)
            {
                MODIFY_EEP_W(Addr800_I1_B_slope, array_temp, 2, 0xA0);
                MODIFY_EEP_W(Addr800_CurB_cal_tmp, array_tmp, 2, 0xA0);
            }

            TXJZ_DL_B = 1;
        }

        else if (tmp == 3)
        {

            CurC_cal_tmp[0] = I_I_Array_xianshi[2];
            I_C_factor_tmp = cur_handle_C(I_I_Array_xianshi[2]) - Cur_cal_tmp[0];
            I1_C_slope[0] = (Cur_cal_tmp[0] << 20) / (CurC_cal_tmp[0]); // C电流校准点1
            HexToChar(array_temp, I1_C_slope[0], 2);
            HexToChar(array_tmp, CurC_cal_tmp[0], 2);
            if (Type_Cur == 0)
            {
                MODIFY_EEP_W(Addr100_I1_C_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr100_CurC_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 1)
            {
                MODIFY_EEP_W(Addr_I1_C_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr_CurC_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 2)
            {
                MODIFY_EEP_W(Addr400_I1_C_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr400_CurC_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 3)
            {
                MODIFY_EEP_W(Addr630_I1_C_slope, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr630_CurC_cal_tmp, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 4)
            {
                MODIFY_EEP_W(Addr800_I1_C_slope, array_temp, 2, 0xA0);
                MODIFY_EEP_W(Addr800_CurC_cal_tmp, array_tmp, 2, 0xA0);
            }
            TXJZ_DL_C = 1;
        }
    }

    /***	****************************abc电流校准点2****************/ //	250A
    else if (temp == 2)
    {
        if (tmp == 1)
        {
            CurA_cal_tmp[1] = I_I_Array_xianshi[0];
            I_A_factor_tmp = cur_handle_A(I_I_Array_xianshi[0]) - Cur_cal_tmp[1];
            I1_A_slope[1] = ((Cur_cal_tmp[1] - Cur_cal_tmp[0]) << 20) / (CurA_cal_tmp[1] - CurA_cal_tmp[0]); // a电流校准点2
            HexToChar(array_temp, I1_A_slope[1], 2);
            HexToChar(array_tmp, CurA_cal_tmp[1], 2);
            if (Type_Cur == 0)
            {
                MODIFY_EEP_W(Addr100_I1_A_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr100_CurA_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 1)
            {
                MODIFY_EEP_W(Addr_I1_A_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr_CurA_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 2)
            {
                MODIFY_EEP_W(Addr400_I1_A_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr400_CurA_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 3)
            {
                MODIFY_EEP_W(Addr630_I1_A_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr630_CurA_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 4)
            {
                MODIFY_EEP_W(Addr800_I1_A_slope1, array_temp, 2, 0xA0);
                MODIFY_EEP_W(Addr800_CurA_cal_tmp1, array_tmp, 2, 0xA0);
            }
            TXJZ_DL_A = 1;
        }

        else if (tmp == 2)
        {

            CurB_cal_tmp[1] = I_I_Array_xianshi[1];
            I_B_factor_tmp = cur_handle_B(I_I_Array_xianshi[1]) - Cur_cal_tmp[1];
            I1_B_slope[1] = ((Cur_cal_tmp[1] - Cur_cal_tmp[0]) << 20) / (CurB_cal_tmp[1] - CurB_cal_tmp[0]); // b电流校准点2
            HexToChar(array_temp, I1_B_slope[1], 2);
            HexToChar(array_tmp, CurB_cal_tmp[1], 2);
            if (Type_Cur == 0)
            {
                MODIFY_EEP_W(Addr100_I1_B_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr100_CurB_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 1)
            {
                MODIFY_EEP_W(Addr_I1_B_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr_CurB_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 2)
            {
                MODIFY_EEP_W(Addr400_I1_B_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr400_CurB_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 3)
            {
                MODIFY_EEP_W(Addr630_I1_B_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr630_CurB_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 4)
            {
                MODIFY_EEP_W(Addr800_I1_B_slope1, array_temp, 2, 0xA0);
                MODIFY_EEP_W(Addr800_CurB_cal_tmp1, array_tmp, 2, 0xA0);
            }
            TXJZ_DL_B = 1;
        }

        else if (tmp == 3)
        {

            CurC_cal_tmp[1] = I_I_Array_xianshi[2];
            I_C_factor_tmp = cur_handle_C(I_I_Array_xianshi[2]) - Cur_cal_tmp[1];
            I1_C_slope[1] = ((Cur_cal_tmp[1] - Cur_cal_tmp[0]) << 20) / (CurC_cal_tmp[1] - CurC_cal_tmp[0]); // c电流校准点2
            HexToChar(array_temp, I1_C_slope[1], 2);
            HexToChar(array_tmp, CurC_cal_tmp[1], 2);
            if (Type_Cur == 0)
            {
                MODIFY_EEP_W(Addr100_I1_C_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr100_CurC_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 1)
            {
                MODIFY_EEP_W(Addr_I1_C_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr_CurC_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 2)
            {
                MODIFY_EEP_W(Addr400_I1_C_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr400_CurC_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 3)
            {
                MODIFY_EEP_W(Addr630_I1_C_slope1, array_temp, 2, 0xA0);
                delay_ms(5);
                MODIFY_EEP_W(Addr630_CurC_cal_tmp1, array_tmp, 2, 0xA0);
                delay_ms(5);
            }
            else if (Type_Cur == 4)
            {
                MODIFY_EEP_W(Addr800_I1_C_slope1, array_temp, 2, 0xA0);
                MODIFY_EEP_W(Addr800_CurC_cal_tmp1, array_tmp, 2, 0xA0);
            }
            TXJZ_DL_C = 1;
        }
    }
}
void leak_uart_cal_handle() // 漏电通信校准
{

    unsigned char array_temp[2], array_tmp[2];
    unsigned short int Vol_cal_tmp = 220, L_cal_tmp = 200;
    signed int L_factor_tmp1, I_A_factor_tmp, V_A_factor_tmp, I_B_factor_tmp, V_B_factor_tmp, I_C_factor_tmp, V_C_factor_tmp;
    volatile unsigned short int L1_slope;

    L_cal_tmp = 200;

    Leak1_temp = Leak_Cur_disp_temp;
    L_factor_tmp1 = Leak_Cur_disp - L_cal_tmp;

    L1_slope = (L_cal_tmp << 20) / (Leak1_temp);
    HexToChar(array_temp, L1_slope, 2);
    HexToChar(array_tmp, Leak1_temp, 2);
    if ((Type_Cur == 0) || (Type_Cur == 1))
    {
        MODIFY_EEP_W(Addr_L1_slope, array_temp, 2, 0xA0);
        MODIFY_EEP_W(Addr_Leak1_temp, array_tmp, 2, 0xA0);
    }

    else if (Type_Cur == 2)
    {
        MODIFY_EEP_W(Addr400_L1_slope, array_temp, 2, 0xA0);
        MODIFY_EEP_W(Addr400_Leak1_temp, array_tmp, 2, 0xA0);
    }
    else if (Type_Cur == 3)
    {
        MODIFY_EEP_W(Addr630_L1_slope, array_temp, 2, 0xA0);
        MODIFY_EEP_W(Addr630_Leak1_temp, array_tmp, 2, 0xA0);
    }
    else if (Type_Cur == 4)
    {
        MODIFY_EEP_W(Addr800_L1_slope, array_temp, 2, 0xA0);
        MODIFY_EEP_W(Addr800_Leak1_temp, array_tmp, 2, 0xA0);
    }
}

void SD_uart_cal_handle(unsigned char tmp, unsigned char temp, unsigned int value) // temp:第几个点
{
    //	if(F_Corr==1)
    {
        float cal_temp;
        unsigned char array_temp[10], Buf_temp[10], array_tmp[10];
        if (Type_Cur == 0)
        {
            if (temp == 0)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_IV_AD_value[0] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_AD_value[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_IV_slope[0] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_slope[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_slope, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_IV_Value[0] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_Value[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_Value, array_tmp, 3, 0xA0);
                }

                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 1)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_IV_AD_value[1] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_AD_value[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value + 3, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_IV_slope[1] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_slope[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_slope + 3, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_IV_Value[1] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_Value[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_Value + 3, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 2)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_IV_AD_value[2] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_AD_value[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value + 6, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_IV_slope[2] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_slope[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_slope + 6, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_IV_Value[2] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_Value[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_Value + 6, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 3)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_IV_AD_value[3] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_AD_value[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value + 9, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_IV_slope[3] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_slope[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_slope + 9, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_IV_Value[3] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_Value[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_Value + 9, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 4)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_IV_AD_value[4] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_AD_value[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value + 12, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_IV_slope[4] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_slope[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_slope + 12, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_IV_Value[4] = value;
                    HexToChar(array_tmp, DLS_Cur_IV_Value[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_IV_Value + 12, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
        }
        if (Type_Cur == 1)
        {
            if (temp == 0)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_I_AD_value[0] = value;
                    HexToChar(array_tmp, DLS_Cur_I_AD_value[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_I_slope[0] = value;
                    HexToChar(array_tmp, DLS_Cur_I_slope[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_slope, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_I_Value[0] = value;
                    HexToChar(array_tmp, DLS_Cur_I_Value[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_Value, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 1)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_I_AD_value[1] = value;
                    HexToChar(array_tmp, DLS_Cur_I_AD_value[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value + 3, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_I_slope[1] = value;
                    HexToChar(array_tmp, DLS_Cur_I_slope[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_slope + 3, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_I_Value[1] = value;
                    HexToChar(array_tmp, DLS_Cur_I_Value[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_Value + 3, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 2)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_I_AD_value[2] = value;
                    HexToChar(array_tmp, DLS_Cur_I_AD_value[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value + 6, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_I_slope[2] = value;
                    HexToChar(array_tmp, DLS_Cur_I_slope[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_slope + 6, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_I_Value[2] = value;
                    HexToChar(array_tmp, DLS_Cur_I_Value[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_Value + 6, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 3)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_I_AD_value[3] = value;
                    HexToChar(array_tmp, DLS_Cur_I_AD_value[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value + 9, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_I_slope[3] = value;
                    HexToChar(array_tmp, DLS_Cur_I_slope[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_slope + 9, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_I_Value[3] = value;
                    HexToChar(array_tmp, DLS_Cur_I_Value[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_Value + 9, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 4)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_I_AD_value[4] = value;
                    HexToChar(array_tmp, DLS_Cur_I_AD_value[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value + 12, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_I_slope[4] = value;
                    HexToChar(array_tmp, DLS_Cur_I_slope[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_slope + 12, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_I_Value[4] = value;
                    HexToChar(array_tmp, DLS_Cur_I_Value[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_I_Value + 12, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
        }
        if (Type_Cur == 2)
        {
            if (temp == 0)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_II_AD_value[0] = value;
                    HexToChar(array_tmp, DLS_Cur_II_AD_value[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_II_slope[0] = value;
                    HexToChar(array_tmp, DLS_Cur_II_slope[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_slope, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_II_Value[0] = value;
                    HexToChar(array_tmp, DLS_Cur_II_Value[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_Value, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 1)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_II_AD_value[1] = value;
                    HexToChar(array_tmp, DLS_Cur_II_AD_value[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value + 3, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_II_slope[1] = value;
                    HexToChar(array_tmp, DLS_Cur_II_slope[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_slope + 3, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_II_Value[1] = value;
                    HexToChar(array_tmp, DLS_Cur_II_Value[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_Value + 3, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 2)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_II_AD_value[2] = value;
                    HexToChar(array_tmp, DLS_Cur_II_AD_value[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value + 6, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_II_slope[2] = value;
                    HexToChar(array_tmp, DLS_Cur_II_slope[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_slope + 6, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_II_Value[2] = value;
                    HexToChar(array_tmp, DLS_Cur_II_Value[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_Value + 6, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 3)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_II_AD_value[3] = value;
                    HexToChar(array_tmp, DLS_Cur_II_AD_value[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value + 9, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_II_slope[3] = value;
                    HexToChar(array_tmp, DLS_Cur_II_slope[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_slope + 9, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_II_Value[3] = value;
                    HexToChar(array_tmp, DLS_Cur_II_Value[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_Value + 9, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 4)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_II_AD_value[4] = value;
                    HexToChar(array_tmp, DLS_Cur_II_AD_value[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value + 12, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_II_slope[4] = value;
                    HexToChar(array_tmp, DLS_Cur_II_slope[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_slope + 12, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_II_Value[4] = value;
                    HexToChar(array_tmp, DLS_Cur_II_Value[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_II_Value + 12, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
        }
        if (Type_Cur == 3)
        {
            if (temp == 0)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_III_AD_value[0] = value;
                    HexToChar(array_tmp, DLS_Cur_III_AD_value[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_III_slope[0] = value;
                    HexToChar(array_tmp, DLS_Cur_III_slope[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_slope, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_III_Value[0] = value;
                    HexToChar(array_tmp, DLS_Cur_III_Value[0], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_Value, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 1)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_III_AD_value[1] = value;
                    HexToChar(array_tmp, DLS_Cur_III_AD_value[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value + 3, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_III_slope[1] = value;
                    HexToChar(array_tmp, DLS_Cur_III_slope[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_slope + 3, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_III_Value[1] = value;
                    HexToChar(array_tmp, DLS_Cur_III_Value[1], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_Value + 3, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 2)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_III_AD_value[2] = value;
                    HexToChar(array_tmp, DLS_Cur_III_AD_value[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value + 6, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_III_slope[2] = value;
                    HexToChar(array_tmp, DLS_Cur_III_slope[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_slope + 6, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_III_Value[2] = value;
                    HexToChar(array_tmp, DLS_Cur_III_Value[2], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_Value + 6, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 3)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_III_AD_value[3] = value;
                    HexToChar(array_tmp, DLS_Cur_III_AD_value[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value + 9, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_III_slope[3] = value;
                    HexToChar(array_tmp, DLS_Cur_III_slope[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_slope + 9, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_III_Value[3] = value;
                    HexToChar(array_tmp, DLS_Cur_III_Value[3], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_Value + 9, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
            else if (temp == 4)
            {
                if (tmp == 1) // 瞬动AD值
                {
                    DLS_Cur_III_AD_value[4] = value;
                    HexToChar(array_tmp, DLS_Cur_III_AD_value[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value + 12, array_tmp, 3, 0xA0);
                }
                else if (tmp == 2) // 瞬动斜率值
                {
                    DLS_Cur_III_slope[4] = value;
                    HexToChar(array_tmp, DLS_Cur_III_slope[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_slope + 12, array_tmp, 3, 0xA0);
                }
                else if (tmp == 3) // 瞬动电流值
                {
                    DLS_Cur_III_Value[4] = value;
                    HexToChar(array_tmp, DLS_Cur_III_Value[4], 3);
                    MODIFY_EEP_W(Addr_DLS_Cur_III_Value + 12, array_tmp, 3, 0xA0);
                }
                else
                {
                    ERR_data_sent(ERR_NO_REQUEST);
                }
            }
        }
    }
}

// 初始化IO 串口2
// pclk1:PCLK1时钟频率(Mhz)
// bound:波特率
void RS485_Init(u32 bound)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = bound;
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_EVEN;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
    HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
}



/* USER CODE END 1 */
