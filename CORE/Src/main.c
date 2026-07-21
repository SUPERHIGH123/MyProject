/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "iwdg.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#include "debug.h"      //壳架区分在这里，如果是125的壳架宏为1，其他的壳架宏为0
#include "factor.h"
#include "delay.h"
#include "24cxx.h"
#include "tool.h"
#include "disp.h"
#include "24cxx.h"
#include "tool.h"
#include "lcd.h"
#include "state.h"
#include "display_ziku.h"
#include "stdint.h"

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
RTC_DateTypeDef sdatestructure;
RTC_TimeTypeDef stimestructure;


uint8_t External_Gate_Control_Flag=2;       //外部分合闸功能切换 三个状态 	0. 保留此前功能，短接分闸，短接合闸
																																				//1. 只有短接的情况下，各个分合闸指令正常，若未短接，则一直保持分闸状态
																																				//2. 只有短接的时候，各个分合闸指令正常，短接合闸的点如果断开，就必须一直保持合闸状态
																																				
																																				
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

extern unsigned int dianliu11[9];
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//static void MX_DMA_Init(void);
//static void MX_ADC1_Init(void);

//static void MX_RTC_Init(void);
//static void MX_TIM6_Init(void);
//static void MX_USART3_UART_Init(void);
 extern unsigned char  temp_frame[32];
	extern unsigned char  frame1[32];
extern	unsigned char  frame2[32];
	u8 at[3];
unsigned int cur_handle_A(unsigned int x);
unsigned int cur_handle_B(unsigned int x);
unsigned int cur_handle_C(unsigned int x);
unsigned int leak_handle(unsigned int x);
unsigned char TEM;
//unsigned 	F_turn_need=0;
unsigned char buff_tap[15]={0};
unsigned char test_shuju[15]={0};
extern unsigned char shangdian,duandian,jiaozhun,LD_hezha,DY_hezha,DL_hezha;
unsigned char F_Sample,F_sy_sucess,F_leak_disp=0,F_2d_trip,F_3d_trip;
unsigned char  F_record_write=0; 
void num_handle(unsigned int x);
extern unsigned char tim_disp[7],tim_m,tim_d,tim_h,tim_f,tim_s,sssj_N,sssj_N_xunhuan;
extern  unsigned char display_graphic_8x16(unsigned char page,unsigned char column,unsigned char *dp);
extern  unsigned char display_graphic_6x12(unsigned char page,unsigned char column,unsigned char *dp);
extern volatile unsigned char tim_m2,tim_d2,tim_h2,tim_f2,tim_s2;
extern volatile unsigned int  tim_y2;
//extern volatile unsigned long int Leak_Cur_Sum1 ;
extern unsigned int   tim_y;
extern unsigned int key_connter ;
 unsigned int Lcd_Count=0;
extern  unsigned char zifu_dian[4];
void data_clear(void);	
void hongwai_SendData(unsigned char Data);
void TIM2_PWM_Init(u16 arr,u16 psc);
//void hongwai_Send_Data(u8 *buf,u8 len);
extern unsigned char  zuokuohao[4];
extern unsigned char  youkuohao[4];
extern volatile unsigned long int A_C_Sum,B_C_Sum,C_C_Sum;
volatile unsigned long int cnt_array4[128],kk=0,kkk=0,cnt_array5[64],cnt_array6[64],lll=0,F_C;
//extern void MenuOperate(unsigned char key);
unsigned char F_shishi=0;
 void write_tingdian(void);
extern  unsigned char disp_status1;
signed int V_temp[3],V_temp_tmp[3],V_Diferent,V_tmp_MAX,V_tmp_MIN;
unsigned int T_wave;//按键试跳波形计数
volatile unsigned	char F_V_Array_Flag;

extern  unsigned char   mima[4];//2022.2.21温州加密码功能，杨济恺定义的数组，用于存放按键输入的密码
extern  unsigned char   mima_set[4];//用户设定的密码，用于与输入的密码比对


extern unsigned char TXJZ_start;//通讯校准开始标志位0结束，1开始
extern unsigned char TXJZ_SJ;//通讯时间
//unsigned char TXJZ_DY=0;//通讯电压
extern unsigned char TXJZ_LD;//通讯漏电

extern unsigned char TXJZ_DL_A;//通讯电流A
extern unsigned char TXJZ_DL_B;//通讯电流B
extern unsigned char TXJZ_DL_C;//通讯电流C
extern void draw_horizontal_line(uint8_t y, uint8_t start_x, uint8_t end_x);
extern unsigned char TXJZ_DY_A;//通讯电压A
extern unsigned char TXJZ_DY_B;//通讯电压B
extern unsigned char TXJZ_DY_C;//通讯电压C

unsigned int Point_i,Point_j,Point_k;
unsigned char First_menu=0,lenth_piont=5,Cross_Zero_A[2]={0},Cross_Zero_B[2]={0},Cross_Zero_C[2]={0},Samp_first_flag=1;
extern volatile unsigned long int A_C_Sum,B_C_Sum,C_C_Sum,I_A_Sum,I_B_Sum,I_C_Sum;
extern unsigned char Type_Cur_change;
unsigned char fenzha_chenggong;//按键分闸成功标志0x11为成功
extern unsigned char F_queren;

void IWDG_Init(u8 prer,u16 rlr);
void initial_lcd(void);
void initial_lcd1(void);
void initial_lcd_guanjiao(void);
void D3_A_BH_Process(void);
void D3_B_BH_Process(void);
void D3_C_BH_Process(void);
void DW_3D_init(void);
void DW_3D_E2_read(void);
void IWDG_Feed(void);
void Get_A_C(void);
	void Get_B_C(void);
		void Get_C_C(void);		
		 void D3_BH_Process(void);
void long_process(void);
void institution_init(void);
void My_USART1_Init(void);
void init_devices(void);
void	EXTIX_Init(void);
void Wait_selftest(void);
void At24cxxWriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);
void Nomal_Process(void);
void Power_Process(void);
void short_process(void);
void state_init(void);
void clear_flags(void);
void factors_init(void);
void external_E2_read(void);
void factor_first_init(unsigned char tmp);
void ctrlword1_analyze(void);
void ctrlword2_analyze(void);
void ctrlword3_analyze(void);
void ctrlword4_analyze(void);
void ctrlword5_analyze(void);
void Cur_Switch(unsigned char Type_Cur);
void TIM3_Int_Init(u16 arr,u16 psc);
void Flag_Updata(void);
void Conter_Updata(void);
void Get_L(void);
void Leak_process(void);
void Lackzero_judge(void);
void V_Sample(unsigned char tmp) ;
void Cur_sample_process(void);
void Vol_sample_process(void);
void Cur_Sample(unsigned char tmp);
unsigned char loss_phase_trip(unsigned char phase_tmp);
void Record_data_propare(void);
void V_max_process(unsigned char tmp);
void V_min_process(unsigned char tmp);
void Write_V(unsigned char tmp,unsigned int factor1,unsigned char factor2);
void Leak_max_process(void);
void Leak_min_process(void);
void I_max_process(unsigned char tmp);
void I_min_process(unsigned char tmp);
void Write_I(unsigned char tmp,unsigned int factor1,unsigned char factor2);
void Auto_Leak_process(void);
void Normal_Leak_process(void);
void zha_position_init(void);
void c_hezha(void);
 unsigned char  Trip_Action  (void) ;
 void Trip_Process_time(unsigned char tmp);
 void rms_make(unsigned char i);
 void V_Sample_C(unsigned char tmp);
 void Cur_Sample_C(unsigned char tmp);
 void Leak_Over_process(void);
void V_Sample_A(void);
void V_Sample_B(void);
void V_Sample_CC(void);
unsigned int vol_handle_A(unsigned int value);
unsigned int vol_handle_B(unsigned int value);
unsigned int vol_handle_C(unsigned int value);
unsigned int vol_handle(unsigned int value);

unsigned int cur_actionhandle_A(unsigned int x);
unsigned int cur_actionhandle_B(unsigned int x);
unsigned int cur_actionhandle_C(unsigned int x);

unsigned int L_adjust_slope;//2021.12.26修正漏电值的斜率，250与400不同

void D3_A_Quick_Process(void);
void D3_B_Quick_Process(void);
void D3_C_Quick_Process(void);

//volatile signed int AD_tmp_V=0;
void hongwai_com_process(void);
void low_vol_SD_process(void);
void Day_updata_process(void);
void hand_short_process(void);
void Record_V(unsigned char tmp,unsigned int factor1,unsigned char factor2);

void mima_input();
void mima_check();
void mima_change();
void Event_clear();
void EEPROM_C(unsigned int AT24C64_address,unsigned int count,unsigned char SelectAddr);
void data_clear();
void vol_abnormal_check(void);

void Time_Hezha_delay(void);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void Delay(u32 count)
{
    u32 i = 0;
    for (; i < count; i++)
        ;
}

void ctrlword1_analyze(void)
{
    F_dataalarm_all = (ctrlword[0] & 0x40) >> 6; // 数据告警
    F_lightalarm = (ctrlword[0] & 0x20) >> 5;    // 灯光告警
    F_voicealarm = (ctrlword[0] & 0x10) >> 4;    // 报警声音
    F_timealarm = (ctrlword[0] & 0x08) >> 3;     // 定时试跳
    F_classreturn = (ctrlword[0] & 0x04) >> 2;   // 档位返回
    F_chonghezha = (ctrlword[0] & 0x02) >> 1;    // 重合闸
    // 如果定时试跳功能打开
    if (F_timealarm == 1)
    {
        F_time_compare = 1;
    }
    else
    {
        F_time_compare = 0;
    }
}
void ctrlword2_analyze(void)
{
    F_dataalarm_qy = (ctrlword[1] & 0x80) >> 7; // 欠压保护及跳闸控制
    F_trip_qy = (ctrlword[1] & 0x40) >> 6;
    F_dataalarm_gy = (ctrlword[1] & 0x20) >> 5;
    F_trip_gy = (ctrlword[1] & 0x10) >> 4;
    F_dataalarm_xq = (ctrlword[1] & 0x08) >> 3;
    F_trip_QX = (ctrlword[1] & 0x04) >> 2;
    F_trip_gl = (ctrlword[1] & 0x01) >> 0;
}
void ctrlword3_analyze(void)
{
    F_trip_QL = (ctrlword[2] & 0x01) >> 0; // 缺零保护及跳闸控制
}
void ctrlword4_analyze(void) // 用于确定漏电相关参数
{
    unsigned char F_GJ_FUNC_tmp, E2_arraymrnow_tmp[5];
    unsigned char array_temp[1];
    D_LCur = (ctrlword[3] >> 4); // 剩余电流档位，取出高四位
    //	TH_LCur=((ctrlword[3]&0x0C)>>2);//取出低两位  额定极限不驱动时间
    F_GJ_FUNC_tmp = (ctrlword[3] & 0x03); // 剩余电流报警时间

    EEPROM_R(Addr_TH_LCur, array_temp, 1, 0xA0);
    TH_LCur = array_temp[0];

    if (D_LCur >= 8)
    {
        D_LCur = 0x08;
        ctrlword[3] &= 0x0F;
        ctrlword[3] += (D_LCur << 4);

        MODIFY_EEP_W(Addr_crtl_word4, &ctrlword[3], 1, 0xA0);
    }
    if (D_LCur == 8)
    {
        D_A_LCur = 11;
        // D_A_LCur漏电自动跟踪档位  //设定成最高档位
        Id1_A = D_ACur_Array[D_A_LCur];
        // 更新比较值
        Id1_L = H_A_L[D_A_LCur];
        // 自适应下限值，用于向下切换档位
        Id1_H = H_A_H[D_A_LCur];
        // 自适应上限值，用于向上切换档位
    }
    else
    {
        Id1 = D_LCur1_Array[D_LCur];
        // 根据漏电动作档位，确定三个动作比较门限
        Id2 = D_LCur2_Array[D_LCur];
        Id3 = D_LCur3_Array[D_LCur];
    }
    if (TH_LCur > 4) // 额定极限不驱动时间
    {
        unsigned char array_tmp[1];
        TH_LCur = 4;
        //		ctrlword[3]&=0xF3 ;
        //		ctrlword[3]+=(TH_LCur<<4);
        //
        //		MODIFY_EEP_W(Addr_crtl_word4,&ctrlword[3],1,0xA0);

        array_tmp[0] = TH_LCur;
        MODIFY_EEP_W(Addr_TH_LCur, array_tmp, 1, 0xA0);
    }
    N_TH = TD_LCur1_Array[TH_LCur];
    // 根据漏电动作时间档位，确定三个时间比较门限
    N_TH2 = TD_LCur2_Array[TH_LCur];
    N_TH3 = TD_LCur3_Array[TH_LCur];

    // 告警关闭，可以脱扣
    if (F_GJ_FUNC_tmp == 0x00)
    {
        F_GJ_FUNC = F_GJ_FUNC_tmp;
        F_trip_ld = 0;
    }
    // 告警开启24小时，后关闭，退运
    else if (F_GJ_FUNC_tmp == 0x01)
    {
        if (F_GJ_FUNC == 0x00)
        {
            F_GJ_FUNC = F_GJ_FUNC_tmp;
            Num_leakquit = Num_leakquit + 1;
            if (Num_leakquit > 10000)
                Num_leakquit = 0;
            DectoBCD(E2_arraymrnow_tmp, Num_leakquit, 2);

            MODIFY_EEP_W(Addr_leakquit_num, E2_arraymrnow_tmp, 2, 0xA0); // 漏电退运次数写入E2内
            //			AT24C64_W(E2_arraymrnow_tmp,Addr_leakquit_num+200,2);
        }
        F_trip_ld = 1;
    }
    // 告警长期启用，退运
    else if (F_GJ_FUNC_tmp == 0x02)
    {
        if (F_GJ_FUNC == 0x00)
        {
            F_GJ_FUNC = F_GJ_FUNC_tmp;
            Num_leakquit = Num_leakquit + 1;
            if (Num_leakquit > 10000)
                Num_leakquit = 0;
            DectoBCD(E2_arraymrnow_tmp, Num_leakquit, 2);

            MODIFY_EEP_W(Addr_leakquit_num, E2_arraymrnow_tmp, 2, 0xA0);
            //			AT24C64_W(E2_arraymrnow_tmp,Addr_leakquit_num+200,1);
        }
        F_trip_ld = 1;
    }
    // 保留
    else
    {
        F_GJ_FUNC = F_GJ_FUNC_tmp;
    }
}

void ctrlword5_analyze(void)
{
    // EEPROM_W(&ctrlword[4],Addr_crtl_word5,1);
    LC_N = ctrlword[4] & 0x03;
    if (LC_N > 3)
    {
        LC_N = 3;
        ctrlword[4] &= 0xFC;
        ctrlword[4] += LC_N;
        MODIFY_EEP_W(Addr_crtl_word5, &ctrlword[4], 1, 0xA0);
    }
    if (LC_N == 0) // 不重合闸
    {
        F_la = 0;
        F_la2 = 0;
        F_la1 = 0;
    }
    else if (LC_N == 1) // 一次重合闸
    {
        F_la = 1;
        F_la2 = 0;
        F_la1 = 0;
    }
    else if (LC_N == 2) // 三次重合闸
    {
        F_la = F_la2 = 1;
        F_la1 = 0;
    }
    else // 无数次重合闸
    {
        F_la = 1;
        F_la2 = 0;
        F_la1 = 1;
    }
}

void vol_abnormal_check(void)
{

    //		unsigned char array_temp[2];
    //
    ////	  EEPROM_R(Addr_V1_A_slope,array_temp,2,0xA0);
    ////	  if((array_temp[1]>0x59)||(array_temp[1]<0x45))
    ////		{
    //

    //					array_temp[0]=0x78;
    //					array_temp[1]=0x50;
    //				 	MODIFY_EEP_W(Addr_V1_A_slope,array_temp,2,0xA0);
    //				 	delay_ms(5);
    //					EEPROM_R(Addr_V1_A_slope,array_temp,2,0xA0);
    //					delay_ms(5);
    ////		}
    //	     	V1_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //
    //
    ////	  EEPROM_R(Addr_V1_B_slope,array_temp,2,0xA0);
    ////	  if((array_temp[1]>0x59)||(array_temp[1]<0x45))
    ////		{
    //

    //					array_temp[0]=0x78;
    //					array_temp[1]=0x50;
    //
    //				 	MODIFY_EEP_W(Addr_V1_B_slope,array_temp,2,0xA0);
    //				 	delay_ms(5);
    //					EEPROM_R(Addr_V1_B_slope,array_temp,2,0xA0);
    //					delay_ms(5);

    ////		}
    //
    //		V1_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //
    ////    EEPROM_R(Addr_V1_C_slope,array_temp,2,0xA0);
    ////	  if((array_temp[1]>0x59)||(array_temp[1]<0x45))
    ////		{
    ////
    //
    //					array_temp[0]=0x78;
    //					array_temp[1]=0x50;
    //				 	MODIFY_EEP_W(Addr_V1_C_slope,array_temp,2,0xA0);
    //				 	delay_ms(5);
    //					EEPROM_R(Addr_V1_C_slope,array_temp,2,0xA0);
    //					delay_ms(5);
    ////		}
    //	  V1_slope[2]=(array_temp[1]<<8)+array_temp[0];
    //
    //
}

void factors_init(void)
{
    IWDG_Feed(); // 喂狗
    unsigned char array_temp[10];
    /*****************基本信息部分****************************/
    EEPROM_R(Addr_FACTORINIT_value, &array_temp[0], 2, 0xA0); // 读外部标志主区
    if ((array_temp[0] == 0x55) && (array_temp[1] == 0xAA))   // 如果读主区成功
    {
        IWDG_Feed(); // 喂狗
        external_E2_read();
    }
    else // 如果主区读取不成功则执行下面成簇
    {
        IWDG_Feed();
        clear_screen();
        Lcd12864_Write12CnCHAR(0, 16, 2, "初始化设置...\r");
        factor_first_init(0);
        IWDG_Feed();
        external_E2_read();
    }
}
void Read_Cur_calibrae_data(void)
{
    unsigned char i;
    unsigned char array_temp[30];
    /**************************读电流AD值************************/
    AT24CXX_ReadLongByte(Addr_Cur_250, 24, array_temp, 0xA0);
    delay_ms(5);
    for (char i = 0; i < 4; i++)
    {
        unsigned char j;
        j = i << 1;
        Cur_A_temp[i] = (array_temp[j + 1] << 8) + array_temp[j];
        Cur_B_temp[i] = (array_temp[j + 9] << 8) + array_temp[j + 8];
        Cur_C_temp[i] = (array_temp[j + 17] << 8) + array_temp[j + 16];
    }
    /*******************************读电流斜率******************************/

    AT24CXX_ReadLongByte(Addr_Cur_slope_250, 24, array_temp, 0xA0);
    delay_ms(5);

    for (char i = 0; i < 4; i++)
    {
        unsigned char j;
        j = i << 1;
        I_A_slope[i] = (array_temp[j + 1] << 8) + array_temp[j];
        I_B_slope[i] = (array_temp[j + 9] << 8) + array_temp[j + 8];
        I_C_slope[i] = (array_temp[j + 17] << 8) + array_temp[j + 16];
    }
    /****************************读电流校准点值*************************/

    AT24CXX_ReadLongByte(Addr_Cur_Disp_250, 24, array_temp, 0xA0);
    delay_ms(5);
    for (char i = 0; i < 4; i++)
    {
        unsigned char j;
        j = i << 1;
        Cur_A_disp[i] = (array_temp[j + 1] << 8) + array_temp[j];
        Cur_B_disp[i] = (array_temp[j + 9] << 8) + array_temp[j + 8];
        Cur_C_disp[i] = (array_temp[j + 17] << 8) + array_temp[j + 16];
    }
    AT24CXX_ReadLongByte(Addr_Leak_ad, 4, array_temp, 0xA0);
    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        Leak_temp[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }

    AT24CXX_ReadLongByte(Addr_Leak_slope, 4, array_temp, 0xA0);
    delay_ms(5);
    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        L_slope[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }
}

void Read_SD_Cur_calibrae_data(void)
{
    IWDG_Feed();
    unsigned char array_temp[30];
    if (Type_Cur == 0)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_AD_value, 15, array_temp, 0xA0); // 800壳架瞬动

        DLS_Cur_IV_AD_value[0] = ChartoHex(&array_temp[0], 3); // AD值
        DLS_Cur_IV_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_slope, 15, array_temp, 0xA0);

        DLS_Cur_IV_slope[0] = ChartoHex(&array_temp[0], 3); // 斜率值
        DLS_Cur_IV_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_Value, 15, array_temp, 0xA0);

        DLS_Cur_IV_Value[0] = ChartoHex(&array_temp[0], 3); // 电流值
        DLS_Cur_IV_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    if (Type_Cur == 1)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_AD_value, 15, array_temp, 0xA0); // 250壳架瞬动

        DLS_Cur_I_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_slope, 15, array_temp, 0xA0);

        DLS_Cur_I_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_Value, 15, array_temp, 0xA0);

        DLS_Cur_I_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    if (Type_Cur == 2)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_AD_value, 15, array_temp, 0xA0); // 400壳架瞬动

        DLS_Cur_II_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_slope, 15, array_temp, 0xA0);

        DLS_Cur_II_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_Value, 15, array_temp, 0xA0);

        DLS_Cur_II_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    if (Type_Cur == 3)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_AD_value, 15, array_temp, 0xA0); // 630壳架瞬动

        DLS_Cur_III_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_slope, 15, array_temp, 0xA0);

        DLS_Cur_III_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_Value, 15, array_temp, 0xA0);

        DLS_Cur_III_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_Value[4] = ChartoHex(&array_temp[12], 3);
    }
}
void Read_SD_Cur_calibrae_data1(void)
{
    unsigned char array_temp[30];
    //	if(Type_Cur==0)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_AD_value, 15, array_temp, 0xA0); // 800壳架瞬动

        DLS_Cur_IV_AD_value[0] = ChartoHex(&array_temp[0], 3); // AD值
        DLS_Cur_IV_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_slope, 15, array_temp, 0xA0);

        DLS_Cur_IV_slope[0] = ChartoHex(&array_temp[0], 3); // 斜率值
        DLS_Cur_IV_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_IV_Value, 15, array_temp, 0xA0);

        DLS_Cur_IV_Value[0] = ChartoHex(&array_temp[0], 3); // 电流值
        DLS_Cur_IV_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_IV_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_IV_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_IV_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    //		if(Type_Cur==1)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_AD_value, 15, array_temp, 0xA0); // 250壳架瞬动

        DLS_Cur_I_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_slope, 15, array_temp, 0xA0);

        DLS_Cur_I_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_I_Value, 15, array_temp, 0xA0);

        DLS_Cur_I_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_I_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_I_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_I_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_I_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    //		if(Type_Cur==2)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_AD_value, 15, array_temp, 0xA0); // 400壳架瞬动

        DLS_Cur_II_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_slope, 15, array_temp, 0xA0);

        DLS_Cur_II_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_II_Value, 15, array_temp, 0xA0);

        DLS_Cur_II_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_II_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_II_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_II_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_II_Value[4] = ChartoHex(&array_temp[12], 3);
    }

    //		if(Type_Cur==3)
    {
        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_AD_value, 15, array_temp, 0xA0); // 630壳架瞬动

        DLS_Cur_III_AD_value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_AD_value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_AD_value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_AD_value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_AD_value[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_slope, 15, array_temp, 0xA0);

        DLS_Cur_III_slope[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_slope[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_slope[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_slope[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_slope[4] = ChartoHex(&array_temp[12], 3);

        AT24CXX_ReadLongByte(Addr_DLS_Cur_III_Value, 15, array_temp, 0xA0);

        DLS_Cur_III_Value[0] = ChartoHex(&array_temp[0], 3);
        DLS_Cur_III_Value[1] = ChartoHex(&array_temp[3], 3);
        DLS_Cur_III_Value[2] = ChartoHex(&array_temp[6], 3);
        DLS_Cur_III_Value[3] = ChartoHex(&array_temp[9], 3);
        DLS_Cur_III_Value[4] = ChartoHex(&array_temp[12], 3);
    }
}

void external_E2_read(void)
{
    unsigned char i;
    unsigned char array_temp[26];
    IWDG_Feed();
    /*******************校准系数*********************/
    EEPROM_R(Addr_L_factor, array_temp, 2, 0xA0);
    L_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(L_factor>15) L_factor = 15;
    //	if(L_factor<-15) L_factor = -15;
    EEPROM_R(Addr_L_F, array_temp, 1, 0xA0);
    F_cal_L = array_temp[0];

    EEPROM_R(Addr_AV_factor, array_temp, 2, 0xA0);
    V_A_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(V_A_factor>15) V_factor = 15;
    //	if(V_A_factor<-15) V_factor = -15;
    EEPROM_R(Addr_AV_F, array_temp, 1, 0xA0);
    F_cal_V_A = array_temp[0];

    EEPROM_R(Addr_BV_factor, array_temp, 2, 0xA0);
    V_B_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(V_A_factor>15) V_factor = 15;
    //	if(V_A_factor<-15) V_factor = -15;
    EEPROM_R(Addr_BV_F, array_temp, 1, 0xA0);
    F_cal_V_B = array_temp[0];

    EEPROM_R(Addr_CV_factor, array_temp, 2, 0xA0);
    V_C_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(V_A_factor>15) V_factor = 15;
    //	if(V_A_factor<-15) V_factor = -15;
    EEPROM_R(Addr_CV_F, array_temp, 1, 0xA0);
    F_cal_V_C = array_temp[0];

    EEPROM_R(Addr_AI_factor, array_temp, 2, 0xA0);
    I_A_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(I_factor>30) I_factor = 30;
    //	if(I_factor<-30) I_factor = -30;
    EEPROM_R(Addr_AI_F, array_temp, 1, 0xA0);
    F_cal_I_A = array_temp[0];

    EEPROM_R(Addr_BI_factor, array_temp, 2, 0xA0);
    I_B_factor = (array_temp[0] << 8) + array_temp[1];
    //	if(I_factor>30) I_factor = 30;
    //	if(I_factor<-30) I_factor = -30;
    EEPROM_R(Addr_BI_F, array_temp, 1, 0xA0);
    F_cal_I_B = array_temp[0];

    EEPROM_R(Addr_CI_factor, array_temp, 2, 0xA0);
    I_C_factor = (array_temp[0] << 8) + array_temp[1];
    /******************************按键校准系数********************************/
    //	  EEPROM_R(Addr_L1_slope,array_temp,2,0xA0);
    //		L1_slope=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_Leak1_temp,array_temp,2,0xA0);
    //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr400_L1_slope,array_temp,2,0xA0);
    //		L1_slope=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_Leak1_temp,array_temp,2,0xA0);
    //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr630_L1_slope,array_temp,2,0xA0);
    //		L1_slope=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_Leak1_temp,array_temp,2,0xA0);
    //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr800_L1_slope,array_temp,2,0xA0);
    //		L1_slope=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_Leak1_temp,array_temp,2,0xA0);
    //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];

    EEPROM_R(Addr_V1_A_slope, array_temp, 2, 0xA0);
    V1_slope[0] = (array_temp[1] << 8) + array_temp[0];

    EEPROM_R(Addr_V1_B_slope, array_temp, 2, 0xA0);
    V1_slope[1] = (array_temp[1] << 8) + array_temp[0];

    EEPROM_R(Addr_V1_C_slope, array_temp, 2, 0xA0);
    V1_slope[2] = (array_temp[1] << 8) + array_temp[0];

    ///*************250壳架*****************/
    //		EEPROM_R(Addr_I1_A_slope,array_temp,2,0xA0);
    //		I1_A_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_I1_B_slope,array_temp,2,0xA0);
    //		I1_B_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_I1_C_slope,array_temp,2,0xA0);
    //		I1_C_slope[0]=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr_I1_A_slope1,array_temp,2,0xA0);
    //		I1_A_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_I1_B_slope1,array_temp,2,0xA0);
    //		I1_B_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_I1_C_slope1,array_temp,2,0xA0);
    //		I1_C_slope[1]=(array_temp[1]<<8)+array_temp[0];

    //
    //		EEPROM_R(Addr_CurA_cal_tmp,array_temp,2,0xA0);
    //		CurA_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr_CurB_cal_tmp,array_temp,2,0xA0);
    //		CurB_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr_CurC_cal_tmp,array_temp,2,0xA0);
    //		CurC_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

    //    EEPROM_R(Addr_CurA_cal_tmp1,array_temp,2,0xA0);
    //		CurA_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_CurB_cal_tmp1,array_temp,2,0xA0);
    //		CurB_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr_CurC_cal_tmp1,array_temp,2,0xA0);
    //		CurC_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    EEPROM_R(Addr_Vol1_A_temp, array_temp, 2, 0xA0);
    Vol1_A_temp = (array_temp[1] << 8) + array_temp[0];
    EEPROM_R(Addr_Vol1_B_temp, array_temp, 2, 0xA0);
    Vol1_B_temp = (array_temp[1] << 8) + array_temp[0];
    EEPROM_R(Addr_Vol1_C_temp, array_temp, 2, 0xA0);
    Vol1_C_temp = (array_temp[1] << 8) + array_temp[0];
    ///*************400壳架*****************/
    //		EEPROM_R(Addr400_I1_A_slope,array_temp,2,0xA0);
    //		I1_400A_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_I1_B_slope,array_temp,2,0xA0);
    //		I1_400B_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_I1_C_slope,array_temp,2,0xA0);
    //		I1_400C_slope[0]=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr400_I1_A_slope1,array_temp,2,0xA0);
    //		I1_400A_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_I1_B_slope1,array_temp,2,0xA0);
    //		I1_400B_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_I1_C_slope1,array_temp,2,0xA0);
    //		I1_400C_slope[1]=(array_temp[1]<<8)+array_temp[0];

    //
    //		EEPROM_R(Addr400_CurA_cal_tmp,array_temp,2,0xA0);
    //		CurA400_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr400_CurB_cal_tmp,array_temp,2,0xA0);
    //		CurB400_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr400_CurC_cal_tmp,array_temp,2,0xA0);
    //		CurC400_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

    //    EEPROM_R(Addr400_CurA_cal_tmp1,array_temp,2,0xA0);
    //		CurA400_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_CurB_cal_tmp1,array_temp,2,0xA0);
    //		CurB400_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr400_CurC_cal_tmp1,array_temp,2,0xA0);
    //		CurC400_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    ///*************630壳架*****************/
    //		EEPROM_R(Addr630_I1_A_slope,array_temp,2,0xA0);
    //		I1_630A_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_I1_B_slope,array_temp,2,0xA0);
    //		I1_630B_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_I1_C_slope,array_temp,2,0xA0);
    //		I1_630C_slope[0]=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr630_I1_A_slope1,array_temp,2,0xA0);
    //		I1_630A_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_I1_B_slope1,array_temp,2,0xA0);
    //		I1_630B_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_I1_C_slope1,array_temp,2,0xA0);
    //		I1_630C_slope[1]=(array_temp[1]<<8)+array_temp[0];

    //
    //		EEPROM_R(Addr630_CurA_cal_tmp,array_temp,2,0xA0);
    //		CurA630_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr630_CurB_cal_tmp,array_temp,2,0xA0);
    //		CurB630_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr630_CurC_cal_tmp,array_temp,2,0xA0);
    //		CurC630_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

    //    EEPROM_R(Addr630_CurA_cal_tmp1,array_temp,2,0xA0);
    //		CurA630_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_CurB_cal_tmp1,array_temp,2,0xA0);
    //		CurB630_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr630_CurC_cal_tmp1,array_temp,2,0xA0);
    //		CurC630_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    ///*************800壳架*****************/
    //		EEPROM_R(Addr800_I1_A_slope,array_temp,2,0xA0);
    //		I1_800A_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_I1_B_slope,array_temp,2,0xA0);
    //		I1_800B_slope[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_I1_C_slope,array_temp,2,0xA0);
    //		I1_800C_slope[0]=(array_temp[1]<<8)+array_temp[0];

    //		EEPROM_R(Addr800_I1_A_slope1,array_temp,2,0xA0);
    //		I1_800A_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_I1_B_slope1,array_temp,2,0xA0);
    //		I1_800B_slope[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_I1_C_slope1,array_temp,2,0xA0);
    //		I1_800C_slope[1]=(array_temp[1]<<8)+array_temp[0];

    //
    //		EEPROM_R(Addr800_CurA_cal_tmp,array_temp,2,0xA0);
    //		CurA800_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr800_CurB_cal_tmp,array_temp,2,0xA0);
    //		CurB800_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
    //
    //    EEPROM_R(Addr800_CurC_cal_tmp,array_temp,2,0xA0);
    //		CurC800_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

    //    EEPROM_R(Addr800_CurA_cal_tmp1,array_temp,2,0xA0);
    //		CurA800_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_CurB_cal_tmp1,array_temp,2,0xA0);
    //		CurB800_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //
    //		EEPROM_R(Addr800_CurC_cal_tmp1,array_temp,2,0xA0);
    //		CurC800_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
    //	if(I_factor>30) I_factor = 30;
    //	if(I_factor<-30) I_factor = -30;
    EEPROM_R(Addr_CI_F, array_temp, 1, 0xA0);
    F_cal_I_C = array_temp[0];

    EEPROM_R(Addr_hezha_delay, array_temp, 1, 0xA0);
    TH_hezha_delay = array_temp[0];
    hezha_delay = hezha_delay_arry[TH_hezha_delay];
    // 保护功能*********************/
    EEPROM_R(Addr_I_ia, array_temp, 1, 0xA0);
    F_ia = array_temp[0];
    EEPROM_R(Addr_L_TB, array_temp, 1, 0xA0);
    F_TB_trip = array_temp[0];
    EEPROM_R(Addr_L_specialwave, array_temp, 1, 0xA0);
    F_Special_wave = array_temp[0];
    EEPROM_R(Addr_C_IP, array_temp, 1, 0xA0);
    F_C_IP = array_temp[0];
    EEPROM_R(Addr_L_JC, array_temp, 1, 0xA0);
    F_jiance = array_temp[0];
    EEPROM_R(Addr_F_gc, array_temp, 1, 0xA0);
    F_gc = array_temp[0];

    EEPROM_R(Addr_I_2d, array_temp, 1, 0xA0);
    F_ip = array_temp[0];
    EEPROM_R(Addr_I_3d, array_temp, 1, 0xA0); // 17.6.21改
    F_ip_3 = array_temp[0];

    EEPROM_R(Addr_D_Cur, array_temp, 2, 0xA0);
    D_Cur = (array_temp[0] << 8) + (array_temp[1]);
    EEPROM_R(Addr_D2_Cur, array_temp, 1, 0xA0);
    D2_Cur = array_temp[0];
    EEPROM_R(Addr_D3_Cur, array_temp, 1, 0xA0);
    D3_Cur = array_temp[0];
    IWDG_Feed();
    EEPROM_R(Addr_D2_Time, array_temp, 1, 0xA0);
    TH_DL = array_temp[0];
    EEPROM_R(Addr_CurLong_Time, array_temp, 1, 0xA0);
    TH_Long_Cur = array_temp[0];
    if (TH_Long_Cur > 7)
    {
        TH_Long_Cur = 0;
    }
    // putchar(D_Cur);
    EEPROM_R(Addr_Type_Cur, array_temp, 1, 0xA0);
    Type_Cur = array_temp[0];
    if (Type_Cur > 4)
    {
        Type_Cur = 1;
    }
    if ((Type_Cur == 0) && (D_Cur >= 76))
    {
        D_Cur = 76;
    }
    if ((Type_Cur == 1) && (D_Cur >= 187))
    {
        D_Cur = 187;
    }
    if ((Type_Cur == 2) && (D_Cur >= 240))
    {
        D_Cur = 240;
    }
    if ((Type_Cur == 3) && (D_Cur >= 378))
    {
        D_Cur = 378;
    }
    if ((Type_Cur == 4) && (D_Cur >= 480))
    {
        D_Cur = 480;
    }
    Cur_Switch(Type_Cur);
    IWDG_Feed();
    /*******************控制字，电流档位，壳架等级，过欠压档位*********************/
    EEPROM_R(Addr_crtl_word1, ctrlword, 5, 0xA0); // 读5个控制字
    delay_ms(5);
    ctrlword1_analyze();
    ctrlword2_analyze();
    ctrlword3_analyze();
    ctrlword4_analyze();
    ctrlword5_analyze();
    IWDG_Feed();
    EEPROM_R(Addr_Vol_g, array_temp, 1, 0xA0);
    Vol_g = array_temp[0];
    if (Vol_g > 51)
    {
        array_temp[0] = 0x05;
        MODIFY_EEP_W(Addr_Vol_g, array_temp, 1, 0xA0);
        Vol_g = 0x04;
    }
    EEPROM_R(Addr_Vol_q, array_temp, 1, 0xA0);
    Vol_q = array_temp[0];
    if (Vol_q > 51)
    {
        array_temp[0] = 0x05;
        MODIFY_EEP_W(Addr_Vol_q, array_temp, 1, 0xA0);
        Vol_q = 0x04;
    }
    EEPROM_R(Addr_Vol_ch, array_temp, 1, 0xA0);
    Vol_ch = array_temp[0];
    over_vol_code[0] = 0x00;
    over_vol_code[1] = 0x25 + Vol_g;
    IWDG_Feed();
    EEPROM_R(Addr_data_clear, array_temp, 1, 0xA0);
    F_data_clear = array_temp[0];

    EEPROM_R(Addr_SY_F, array_temp, 1, 0xA0);
    F_trip_sy = array_temp[0];

    EEPROM_R(Addr_SY_yanshi, array_temp, 1, 0xA0);
    D_SY_yanshi = array_temp[0];
    if (D_SY_yanshi > 9)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_SY_yanshi, array_temp, 1, 0xA0);
        D_SY_yanshi = 0;
    }

    EEPROM_R(Addr_QY_yanshi, array_temp, 1, 0xA0);
    D_QY_yanshi = array_temp[0]; // 0000 01111
    if (D_QY_yanshi > 9)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_QY_yanshi, array_temp, 1, 0xA0);
        D_QY_yanshi = 0;
    }

    EEPROM_R(Addr_GY_yanshi, array_temp, 1, 0xA0);
    D_GY_yanshi = array_temp[0]; // 0000 01111
    if (D_GY_yanshi > 9)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_GY_yanshi, array_temp, 1, 0xA0);
        D_GY_yanshi = 0;
    }
    IWDG_Feed();
    EEPROM_R(Addr_QX_BAOHU, array_temp, 1, 0xA0);
    Vol_down = array_temp[0];
    if (Vol_down > 6)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_QX_BAOHU, array_temp, 1, 0xA0);
        Vol_down = 0;
    }
    EEPROM_R(Addr_QL_BAOHU, array_temp, 1, 0xA0);
    Vol_up = array_temp[0];
    if (Vol_up > 5)
    {
        array_temp[0] = 0;
        MODIFY_EEP_W(Addr_QL_BAOHU, array_temp, 1, 0xA0);
        Vol_up = 0;
    }
    IWDG_Feed();
    EEPROM_R(Addr_shangdian, array_temp, 1, 0xA0);
    shangdian = array_temp[0];
    EEPROM_R(Addr_dianya, array_temp, 1, 0xA0);
    DY_hezha = array_temp[0];
    EEPROM_R(Addr_dianliu, array_temp, 1, 0xA0);
    DL_hezha = array_temp[0];
    EEPROM_R(Addr_loudian, array_temp, 1, 0xA0);
    LD_hezha = array_temp[0];

    EEPROM_R(Addr_jiaozhun, array_temp, 1, 0xA0);
    F_Corr = jiaozhun = array_temp[0];
    EEPROM_R(Addr_DIANYA_chonghe, array_temp, 1, 0xA0);
    F_dianya_chonghe = array_temp[0];
    EEPROM_R(Addr_duandian, array_temp, 1, 0xA0);
    duandian = array_temp[0];
    IWDG_Feed();
    EEPROM_R(Addr_Vol_q, array_temp, 1, 0xA0);
    Vol_q = array_temp[0];
    //	under_vol_code[0]=0x00 ;
    //	under_vol_code[1]=0x14+Vol_q ;
    //	if(under_vol_code[1]==0x1A)
    //		under_vol_code[1] = 0x20;
    /*******************波特率，设备地址*********************/
    EEPROM_R(Addr_baud, array_temp, 1, 0xA0);
    baud = array_temp[0];
    if (baud == 0)
    {
        RS485_Init(1200);
    }
    else if (baud == 1)
    {
        RS485_Init(2400);
    }
    else if (baud == 2)
    {
        RS485_Init(4800);
    }
    else if (baud == 3)
    {
        RS485_Init(9600);
    }
    //	Uart2_Init();
    EEPROM_R(Addr_dev_addr, self_addr_code, 6, 0xA0);
    if ((self_addr_code[0] > 0x99) || (self_addr_code[1] > 0x99) || (self_addr_code[2] > 0x99) || (self_addr_code[3] > 0x99) || (self_addr_code[4] > 0x99) || (self_addr_code[5] > 0x99))
    {

        self_addr_code[0] = 0x00;
        self_addr_code[1] = 0x00;
        self_addr_code[2] = 0x00;
        self_addr_code[3] = 0x00;
        self_addr_code[4] = 0x00;
        self_addr_code[5] = 0x00;
        // Rewrite_buffer(0);
        MODIFY_EEP_W(Addr_dev_addr, self_addr_code, 6, 0xA0);
    }
    /*******************密码+次数*********************/
    EEPROM_R(Addr_0_password, array_temp, 12, 0xA0);
    for (i = 0; i < 4; i++)
    {
        password_0class[i] = array_temp[i];
        password_1class[i] = array_temp[i + 4];
        password_2class[i] = array_temp[i + 8];
    }

    /********************读次数************************/
    EEPROM_R(Addr_clear_num, array_temp, 3, 0xA0);
    Num_clearall = BCDtoDec(array_temp, 3);

    EEPROM_R(Addr_trip_num, array_temp, 2, 0xA0);
    Num_tripall = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_close_num, array_temp, 2, 0xA0);
    Num_triplock = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_leak_num, array_temp, 2, 0xA0);
    Num_tripleak = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_current_num, array_temp, 2, 0xA0);
    Num_tripcur = BCDtoDec(array_temp, 2);
    IWDG_Feed();
    EEPROM_R(Addr_vol_num, array_temp, 2, 0xA0);
    Num_tripvol = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_hand_num, array_temp, 2, 0xA0);
    Num_triphand = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_zero_num, array_temp, 2, 0xA0);
    Num_tripzero = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_test_num, array_temp, 2, 0xA0);
    Num_triptest = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_2D_num, array_temp, 2, 0xA0);
    Num_tripdelay = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_3D_num, array_temp, 2, 0xA0);
    Num_tripinstant = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_leakover_num, array_temp, 2, 0xA0);
    Num_leakover = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_leakprotect_num, array_temp, 2, 0xA0);
    Num_leakprotect = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_leakquit_num, array_temp, 2, 0xA0);
    /*退运次数*/
    Num_leakquit = BCDtoDec(array_temp, 2);
    EEPROM_R(Addr_protect_time, T_run_time_array, 4, 0xA0);
    // 运行时间
    Sum_run_time = BCDtoDec(T_run_time_array, 4); // 参数变量
    // 设备号
    EEPROM_R(Addr_dev_id, dev_id_code, 6, 0xA0); // 资产管理代码
    EEPROM_R(Addr_dev_code, dev_code_code, 32, 0xA0);
    EEPROM_R(Addr_equi_type, equi_type_code, 10, 0xA0);
    // 公认代码
    EEPROM_R(Addr_factory_code, factory_code_code, 24, 0xA0);
    /**********************事件记录*****************************/
    // 跳闸事件指针
    EEPROM_R(Addr_point_event_trip, &array_temp[1], 1, 0xA0);
    point_event_trip = array_temp[1];
    EEPROM_R(Addr_point_event_trip_24C256, &array_temp[1], 1, 0xA0);
    point_event_trip_24C256 = array_temp[1];
    // 自检时间
    EEPROM_R(Addr_point_event_self, &array_temp[1], 1, 0xA0);
    point_event_self = array_temp[1];

    // 漏电超限事件指针
    EEPROM_R(Addr_point_event_leak, array_temp, 1, 0xA0);
    point_event_leak = array_temp[0];
    IWDG_Feed();
    /**********************最值记录*****************************/
    //	EEPROM_R(Addr_max_Avol_TD,array_temp,4,0xA0);
    //	V_MAX[0]=BCDtoDec(array_temp,2);
    //
    //	EEPROM_R(Addr_max_Bvol_TD,array_temp,4,0xA0);
    //	V_MAX[1]=BCDtoDec(array_temp,2);
    //
    //	EEPROM_R(Addr_max_Cvol_TD,array_temp,4,0xA0);
    //	V_MAX[2]=BCDtoDec(array_temp,2);
    EEPROM_R(Addr_record_time, array_temp, 1, 0xA0);
    Leak_record_time = BCDtoDec(array_temp, 1);
    Num_leak_record = Leak_record_time * 3000;

    EEPROM_R(Addr_point_leakrecord, array_temp, 2, 0xA0);
    point_Leak_record = BCDtoDec(array_temp, 2);

    EEPROM_R(Addr_point_leak_max, array_temp, 1, 0xA0);
    point_leak_max = array_temp[0];

    EEPROM_R((Addr_max_leak + point_leak_max * 9), array_temp, 1, 0xA0);
    old_year = array_temp[8];
    old_month = array_temp[7];
    old_day = array_temp[6];
    IWDG_Feed();
    EEPROM_R(Addr_point_Avol_max, array_temp, 1, 0xA0);
    point_Avol_max = array_temp[0];

    EEPROM_R(Addr_point_Bvol_max, array_temp, 1, 0xA0);
    point_Bvol_max = array_temp[0];
    EEPROM_R(Addr_point_Cvol_max, array_temp, 1, 0xA0);
    point_Cvol_max = array_temp[0];
    EEPROM_R(Addr_point_Acur_max, array_temp, 1, 0xA0);
    point_Acur_max = array_temp[0];
    EEPROM_R(Addr_point_Bcur_max, array_temp, 1, 0xA0);
    point_Bcur_max = array_temp[0];
    EEPROM_R(Addr_point_Ccur_max, array_temp, 1, 0xA0);
    point_Ccur_max = array_temp[0];

    EEPROM_R(Addr_point_leak_min, array_temp, 1, 0xA0);
    point_leak_min = array_temp[0];
    EEPROM_R(Addr_point_Avol_min, array_temp, 1, 0xA0);
    point_Avol_min = array_temp[0];
    EEPROM_R(Addr_point_Bvol_min, array_temp, 1, 0xA0);
    point_Bvol_min = array_temp[0];
    EEPROM_R(Addr_point_Cvol_min, array_temp, 1, 0xA0);
    point_Cvol_min = array_temp[0];
    EEPROM_R(Addr_point_Acur_min, array_temp, 1, 0xA0);
    point_Acur_min = array_temp[0];
    EEPROM_R(Addr_point_Bcur_min, array_temp, 1, 0xA0);
    point_Bcur_min = array_temp[0];
    EEPROM_R(Addr_point_Ccur_min, array_temp, 1, 0xA0);
    point_Ccur_min = array_temp[0];
    IWDG_Feed();
    EEPROM_R(Addr_alarm_value, alarm_value_code, 2, 0xA0);
    Leak_Alarm_Value = BCDtoDec(alarm_value_code, 2);
    // 剩余电流记录变化差值整定值(10-99)
    EEPROM_R(Addr_record_value, record_value_code, 1, 0xA0);
    // 剩余电流记录间隔时间整定值(01-99)
    EEPROM_R(Addr_record_time, record_time_code, 1, 0xA0);
    // 定时试跳整定时间 3
    EEPROM_R(Addr_timed_trip, timed_trip_code, 3, 0xA0);
    // 断相电压整定值 2
    EEPROM_R(Addr_break_phase, break_phase_code, 2, 0xA0);
    // 电流超限报警
    EEPROM_R(Addr_over_current, over_current_code, 1, 0xA0);

    // 读密码2022.2.21杨济恺温州加
    EEPROM_R(Addr_mima_set, array_temp, 4, 0xA0);
    mima_set[0] = array_temp[0];
    mima_set[1] = array_temp[1];
    mima_set[2] = array_temp[2];
    mima_set[3] = array_temp[3];

    // putchar(0xCC);
    /*******江苏版本校准新加系数***********/
    Read_Cur_calibrae_data(); // 读电流相关校准参数

    Read_SD_Cur_calibrae_data(); // 读瞬动相关参数
    Read_SD_Cur_calibrae_data1();

    AT24CXX_ReadLongByte(Addr_Vol_ad, 9, array_temp, 0xA0);

    Vol_A_temp[0] = ChartoHex(&array_temp[0], 3);
    Vol_B_temp[0] = ChartoHex(&array_temp[3], 3);
    Vol_C_temp[0] = ChartoHex(&array_temp[6], 3);

    AT24CXX_ReadLongByte(Addr_Vol_slope, 6, array_temp, 0xA0);

    V_A_slope[0] = ChartoHex(&array_temp[0], 2);
    V_B_slope[0] = ChartoHex(&array_temp[2], 2);
    V_C_slope[0] = ChartoHex(&array_temp[4], 2);
    AT24CXX_ReadLongByte(Addr_Vol_Disp, 6, array_temp, 0xA0);

    Vol_A_disp[0] = ChartoHex(&array_temp[0], 2);
    Vol_B_disp[0] = ChartoHex(&array_temp[2], 2);
    Vol_C_disp[0] = ChartoHex(&array_temp[4], 2);

    AT24CXX_ReadLongByte(Addr_Leak_ad, 6, array_temp, 0xA0);
    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        Leak_temp[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }

    AT24CXX_ReadLongByte(Addr_Leak_slope, 6, array_temp, 0xA0);

    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        L_slope[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }

    AT24CXX_ReadLongByte(Addr_Leak_Disp, 6, array_temp, 0xA0);

    for (char i = 0; i < 3; i++)
    {
        unsigned char j;
        j = i << 1;
        Leak_disp[i] = (array_temp[j + 1] << 8) + array_temp[j];
    }

    // 读短接分合闸模式
    EEPROM_R(External_Gate_Control_Flag_Addr, array_temp, 1, 0xA0);
    External_Gate_Control_Flag = array_temp[0];
}

void factor_first_init(unsigned char tmp)
{
    int Addr_factor;
    unsigned char array_temp[30], array_tmp[150];
    unsigned int lenth;
    // 事件清零
    Addr_factor = Addr_max_leak;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Avol;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Bvol;
    lenth = 288;
    IWDG_Feed();
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Cvol;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Acur;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Bcur;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Ccur;
    lenth = 288;
    IWDG_Feed();
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    //
    //
    array_temp[0] = 2;
    MODIFY_EEP_W(Addr_hezha_delay, array_temp, 1, 0xA0);
    /**********功能档位恢复出厂设置*******************/
    /***********电压校准参数**************/
    array_temp[0] = 0x06;
    array_temp[1] = 0x1D;
    array_temp[2] = 0x00;
    array_temp[3] = 0x20;
    array_temp[4] = 0x1D;
    array_temp[5] = 0x00;
    array_temp[6] = 0x29;
    array_temp[7] = 0x1D;
    array_temp[8] = 0x00;
    MODIFY_EEP_W(Addr_Vol_ad, array_temp, 9, 0xA0); //
    array_temp[0] = 0x22;
    array_temp[1] = 0x08;
    array_temp[2] = 0x22;
    array_temp[3] = 0x08;
    array_temp[4] = 0x35;
    array_temp[5] = 0x08;
    MODIFY_EEP_W(Addr_Vol_slope, array_temp, 6, 0xA0); //
    array_temp[0] = 0x20;
    array_temp[1] = 0x4E;
    array_temp[2] = 0x20;
    array_temp[3] = 0x4E;
    array_temp[4] = 0x20;
    array_temp[5] = 0x4E;
    MODIFY_EEP_W(Addr_Vol_Disp, array_temp, 6, 0xA0); //
                                                      /***********电流校准参数**************/
    array_temp[0] = 0xE8;
    array_temp[1] = 0x03; // 03E8=1000
    array_temp[2] = 0x88;
    array_temp[3] = 0x13; // 1388=5000
    array_temp[4] = 0x10;
    array_temp[5] = 0x27; // 2710=10000
    array_temp[6] = 0x60;
    array_temp[7] = 0xEA; // EA60=60000

    array_temp[8] = 0xE8;
    array_temp[9] = 0x03;
    array_temp[10] = 0x88;
    array_temp[11] = 0x13;
    array_temp[12] = 0x10;
    array_temp[13] = 0x27;
    array_temp[14] = 0x60;
    array_temp[15] = 0xEA;

    array_temp[16] = 0xE8;
    array_temp[17] = 0x03;
    array_temp[18] = 0x88;
    array_temp[19] = 0x13;
    array_temp[20] = 0x10;
    array_temp[21] = 0x27;
    array_temp[22] = 0x60;
    array_temp[23] = 0xEA;
    MODIFY_EEP_W(Addr_Cur_Disp_250, array_temp, 24, 0xA0);
    IWDG_Feed();
    delay_ms(5);
    array_temp[0] = 0xAB;
    array_temp[1] = 0x01;
    array_temp[2] = 0x2C;
    array_temp[3] = 0x0A;
    array_temp[4] = 0xF3;
    array_temp[5] = 0x14;
    array_temp[6] = 0x48;
    array_temp[7] = 0x7D;

    array_temp[8] = 0x5D;
    array_temp[9] = 0x03;
    array_temp[10] = 0xF6;
    array_temp[11] = 0x0B;
    array_temp[12] = 0x73;
    array_temp[13] = 0x16;
    array_temp[14] = 0x11;
    array_temp[15] = 0x7F;

    array_temp[16] = 0x6A;
    array_temp[17] = 0x02;
    array_temp[18] = 0xE7;
    array_temp[19] = 0x0A;
    array_temp[20] = 0x61;
    array_temp[21] = 0x15;
    array_temp[22] = 0x96;
    array_temp[23] = 0x7D;
    MODIFY_EEP_W(Addr_Cur_250, array_temp, 24, 0xA0);
    IWDG_Feed();
    delay_ms(5);
    array_temp[0] = 0x5E;
    array_temp[1] = 0x09;
    array_temp[2] = 0x8D;
    array_temp[3] = 0x07;
    array_temp[4] = 0x3F;
    array_temp[5] = 0x07;
    array_temp[6] = 0x7C;
    array_temp[7] = 0x07;

    array_temp[8] = 0xA5;
    array_temp[9] = 0x04;
    array_temp[10] = 0x54;
    array_temp[11] = 0x07;
    array_temp[12] = 0x72;
    array_temp[13] = 0x07;
    array_temp[14] = 0x77;
    array_temp[15] = 0x07;

    array_temp[16] = 0x78;
    array_temp[17] = 0x06;
    array_temp[18] = 0x67;
    array_temp[19] = 0x07;
    array_temp[20] = 0x75;
    array_temp[21] = 0x07;
    array_temp[22] = 0x7F;
    array_temp[23] = 0x07;
    MODIFY_EEP_W(Addr_Cur_slope_250, array_temp, 24, 0xA0);
    delay_ms(5);
    /***********漏电校准参数**************/
    array_temp[0] = 0x5F;
    array_temp[1] = 0x08;
    array_temp[2] = 0xF8;
    array_temp[3] = 0x5A;
    MODIFY_EEP_W(Addr_Leak_ad, array_temp, 4, 0xA0);
    array_temp[0] = 0x72; // 5000/////////////////////
    array_temp[1] = 0x94;
    array_temp[2] = 0x30; // 60000
    array_temp[3] = 0x75;
    MODIFY_EEP_W(Addr_Leak_Disp, array_temp, 4, 0xA0);
    array_temp[0] = 0x16;
    array_temp[1] = 0x03;
    array_temp[2] = 0x33;
    array_temp[3] = 0x05;
    MODIFY_EEP_W(Addr_Leak_slope, array_temp, 4, 0xA0);
    delay_ms(5);
    /***********************************************************/
    /**********************800壳架瞬动校准******************/
    array_temp[0] = 0x20; // 84000
    array_temp[1] = 0x48;
    array_temp[2] = 0x01;

    array_temp[3] = 0xA0; // 100000
    array_temp[4] = 0x86;
    array_temp[5] = 0x01;

    array_temp[6] = 0xA0; // 100000
    array_temp[7] = 0x86;
    array_temp[8] = 0x01;

    array_temp[9] = 0xA0;
    array_temp[10] = 0x86;
    array_temp[11] = 0x01;

    array_temp[12] = 0xA0;
    array_temp[13] = 0x86;
    array_temp[14] = 0x01;
    MODIFY_EEP_W(Addr_DLS_Cur_IV_AD_value, array_temp, 15, 0xA0); // 800壳架瞬动电流AD值
    delay_ms(5);
    array_temp[0] = 0x17; // 23
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x0A; // 10
    array_temp[4] = 0x00;
    array_temp[5] = 0x00;

    array_temp[6] = 0x08; // 8
    array_temp[7] = 0x00;
    array_temp[8] = 0x00;

    array_temp[9] = 0x06; // 6
    array_temp[10] = 0x00;
    array_temp[11] = 0x00;

    array_temp[12] = 0x04; // 4
    array_temp[13] = 0x00;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_IV_slope, array_temp, 15, 0xA0); // 800壳架瞬动电流斜率值
    delay_ms(5);
    array_temp[0] = 0x00; // 0
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x74; // 3700
    array_temp[4] = 0x0E;
    array_temp[5] = 0x00;

    array_temp[6] = 0x74; // 3700
    array_temp[7] = 0x0E;
    array_temp[8] = 0x00;

    array_temp[9] = 0x74; // 3700
    array_temp[10] = 0x0E;
    array_temp[11] = 0x00;

    array_temp[12] = 0x74; // 3700
    array_temp[13] = 0x0E;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_IV_Value, array_temp, 15, 0xA0); // 800壳架瞬动电流值
    delay_ms(5);
    /**********************250壳架瞬动校准******************/
    array_temp[0] = 0xD0; // 66000
    array_temp[1] = 0x01;
    array_temp[2] = 0x01;

    array_temp[3] = 0x00; // 76800
    array_temp[4] = 0x2C;
    array_temp[5] = 0x01;

    array_temp[6] = 0x90; // 90000
    array_temp[7] = 0x5F;
    array_temp[8] = 0x01;

    array_temp[9] = 0x90; // 90000
    array_temp[10] = 0x5F;
    array_temp[11] = 0x01;

    array_temp[12] = 0x90; // 90000
    array_temp[13] = 0x5F;
    array_temp[14] = 0x01;
    MODIFY_EEP_W(Addr_DLS_Cur_I_AD_value, array_temp, 15, 0xA0); // 250壳架瞬动电流AD值
    delay_ms(5);
    array_temp[0] = 0x3C; // 60
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x0C; // 12
    array_temp[4] = 0x00;
    array_temp[5] = 0x00;

    array_temp[6] = 0x08; // 8
    array_temp[7] = 0x00;
    array_temp[8] = 0x00;

    array_temp[9] = 0x04; // 4
    array_temp[10] = 0x00;
    array_temp[11] = 0x00;

    array_temp[12] = 0x04; // 4
    array_temp[13] = 0x00;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_I_slope, array_temp, 15, 0xA0); // 250壳架瞬动电流斜率值
    delay_ms(5);
    array_temp[0] = 0x00; // 0
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x4C; // 1100
    array_temp[4] = 0x04;
    array_temp[5] = 0x00;

    array_temp[6] = 0xD0; // 20000
    array_temp[7] = 0x07;
    array_temp[8] = 0x00;

    array_temp[9] = 0xB8; // 30000
    array_temp[10] = 0x0B;
    array_temp[11] = 0x00;

    array_temp[12] = 0xB8; // 30000
    array_temp[13] = 0x0B;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_I_Value, array_temp, 15, 0xA0); // 250壳架瞬动电流值
    delay_ms(5);
    /**********************400壳架瞬动校准******************/
    array_temp[0] = 0xE8;
    array_temp[1] = 0x80;
    array_temp[2] = 0x00;

    array_temp[3] = 0xA8;
    array_temp[4] = 0x93;
    array_temp[5] = 0x00;

    array_temp[6] = 0x18;
    array_temp[7] = 0xAB;
    array_temp[8] = 0x00;

    array_temp[9] = 0x90;
    array_temp[10] = 0x5F;
    array_temp[11] = 0x01;

    array_temp[12] = 0x90;
    array_temp[13] = 0x5F;
    array_temp[14] = 0x01;
    MODIFY_EEP_W(Addr_DLS_Cur_II_AD_value, array_temp, 15, 0xA0); // 400壳架瞬动电流AD值
    delay_ms(5);
    array_temp[0] = 0x1E;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x06;
    array_temp[4] = 0x00;
    array_temp[5] = 0x00;

    array_temp[6] = 0x06;
    array_temp[7] = 0x00;
    array_temp[8] = 0x00;

    array_temp[9] = 0x03;
    array_temp[10] = 0x00;
    array_temp[11] = 0x00;

    array_temp[12] = 0x03;
    array_temp[13] = 0x00;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_II_slope, array_temp, 15, 0xA0); // 400壳架瞬动电流斜率值
    delay_ms(5);
    array_temp[0] = 0x00;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x4C;
    array_temp[4] = 0x04;
    array_temp[5] = 0x00;

    array_temp[6] = 0x6C;
    array_temp[7] = 0x07;
    array_temp[8] = 0x00;

    array_temp[9] = 0x54;
    array_temp[10] = 0x0B;
    array_temp[11] = 0x00;

    array_temp[12] = 0xB8;
    array_temp[13] = 0x0B;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_II_Value, array_temp, 15, 0xA0); // 400壳架瞬动电流值
    delay_ms(5);
    /**********************630壳架瞬动校准******************/
    array_temp[0] = 0x38;
    array_temp[1] = 0xF9;
    array_temp[2] = 0x00;

    array_temp[3] = 0x78;
    array_temp[4] = 0x31;
    array_temp[5] = 0x01;

    array_temp[6] = 0xA0;
    array_temp[7] = 0x54;
    array_temp[8] = 0x01;

    array_temp[9] = 0x44;
    array_temp[10] = 0x74;
    array_temp[11] = 0x01;

    array_temp[12] = 0xF0;
    array_temp[13] = 0x49;
    array_temp[14] = 0x02;
    MODIFY_EEP_W(Addr_DLS_Cur_III_AD_value, array_temp, 15, 0xA0); // 630壳架瞬动电流AD值
    delay_ms(5);
    array_temp[0] = 0x1D;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x12;
    array_temp[4] = 0x00;
    array_temp[5] = 0x00;

    array_temp[6] = 0x0A;
    array_temp[7] = 0x00;
    array_temp[8] = 0x00;

    array_temp[9] = 0x09;
    array_temp[10] = 0x00;
    array_temp[11] = 0x00;

    array_temp[12] = 0x04;
    array_temp[13] = 0x00;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_III_slope, array_temp, 15, 0xA0); // 630壳架瞬动电流斜率值
    delay_ms(5);
    array_temp[0] = 0x00;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;

    array_temp[3] = 0x98;
    array_temp[4] = 0x08;
    array_temp[5] = 0x00;

    array_temp[6] = 0xB8;
    array_temp[7] = 0x0B;
    array_temp[8] = 0x00;

    array_temp[9] = 0x3C;
    array_temp[10] = 0x0F;
    array_temp[11] = 0x00;

    array_temp[12] = 0xC0;
    array_temp[13] = 0x12;
    array_temp[14] = 0x00;
    MODIFY_EEP_W(Addr_DLS_Cur_III_Value, array_temp, 15, 0xA0); // 630壳架瞬动电流值
    delay_ms(5);
    /********************************************************************/

    IWDG_Feed();
    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_I_2d, array_temp, 1, 0xA0); // 功能保护是否开启初始化  二段

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_I_3d, array_temp, 1, 0xA0); // 功能保护是否开启初始化  三段

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_I_ia, array_temp, 1, 0xA0); // 电流重合闸

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_L_TB, array_temp, 1, 0xA0); // 突变

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_L_specialwave, array_temp, 1, 0xA0); // 特波2022.2.24

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_shangdian, array_temp, 1, 0xA0); // 上电合闸2022.2.24
    MODIFY_EEP_W(Addr_dianya, array_temp, 1, 0xA0);    // 上电合闸2022.2.24
    MODIFY_EEP_W(Addr_loudian, array_temp, 1, 0xA0);   // 上电合闸2022.2.24
    MODIFY_EEP_W(Addr_dianliu, array_temp, 1, 0xA0);   // 上电合闸2022.2.24

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_C_IP, array_temp, 1, 0xA0); // 短路延时

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_L_JC, array_temp, 1, 0xA0);

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_F_gc, array_temp, 1, 0xA0);
    IWDG_Feed();
    ctrlword[0] = 0x74;
    ctrlword[1] = 0x01; // 电压保护//51
    ctrlword[2] = 0x00;
    ctrlword[3] = 0x5A; // 漏电档位修改为500//时间档位改成500ms
    ctrlword[4] = 0x61;
    MODIFY_EEP_W(Addr_crtl_word1, ctrlword, 5, 0xA0); // 把控制字写进去
    delay_ms(5);
    array_temp[0] = 0x02;
    MODIFY_EEP_W(Addr_TH_LCur, array_temp, 1, 0xA0);
    ctrlword1_analyze();
    ctrlword2_analyze();
    ctrlword3_analyze();
    ctrlword4_analyze();
    delay_ms(5);
    IWDG_Feed();

#if type_125
    array_temp[0] = 0x00;
#else
    array_temp[0] = 0x02;
#endif

    Type_Cur = array_temp[0];
    MODIFY_EEP_W(Addr_Type_Cur, array_temp, 1, 0xA0); // 电流壳架等级

    array_temp[0] = 0x19;
    MODIFY_EEP_W(Addr_Vol_g, array_temp, 1, 0xA0); // 过压档位

    array_temp[0] = 0x19;
    MODIFY_EEP_W(Addr_Vol_q, array_temp, 1, 0xA0); // 欠压档位

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_Vol_ch, array_temp, 1, 0xA0); // 过欠压重合闸

    IWDG_Feed();
    //  D_QY_yanshi=((key_state)&0x07);//0000 01111
    array_tmp[0] = 0x02;
    MODIFY_EEP_W(Addr_QY_yanshi, array_tmp, 1, 0xA0);

    array_tmp[0] = 0x02;
    MODIFY_EEP_W(Addr_GY_yanshi, array_tmp, 1, 0xA0);

    IWDG_Feed();
    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_data_clear, array_temp, 1, 0xA0);

    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_SY_F, array_temp, 1, 0xA0);

    array_tmp[0] = 0x03;
    MODIFY_EEP_W(Addr_QX_BAOHU, array_tmp, 1, 0xA0);
    array_tmp[0] = 0x03;
    MODIFY_EEP_W(Addr_QL_BAOHU, array_tmp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_D_A_Lcur, array_temp, 1, 0xA0); // 漏电自动档位

    array_temp[0] = 19;                            // 0x00;
    MODIFY_EEP_W(Addr_D_Cur, array_temp, 1, 0xA0); // 电流档位

    array_temp[0] = 0x02;                           // 0x00;
    MODIFY_EEP_W(Addr_D2_Cur, array_temp, 1, 0xA0); // 二段档位

    array_temp[0] = 0x03;                           // 0x00;
    MODIFY_EEP_W(Addr_D3_Cur, array_temp, 1, 0xA0); // 三段档位

    array_temp[0] = 0;                               // 0x00;
    MODIFY_EEP_W(Addr_D2_Time, array_temp, 1, 0xA0); // 短路短延时档位

    array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_CurLong_Time, array_tmp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_SY_yanshi, array_temp, 1, 0xA0);

    IWDG_Feed();
    array_temp[0] = 0x55;
    array_temp[1] = 0xAA;
    MODIFY_EEP_W(Addr_FACTORINIT_value, array_temp, 2, 0xA0);

    IWDG_Feed();
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_L_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_AV_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_BV_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_CV_factor, array_temp, 2, 0xA0);
    IWDG_Feed();
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_AI_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_BI_factor, array_temp, 2, 0xA0);
    array_temp[0] = 0;
    array_temp[1] = 0;
    MODIFY_EEP_W(Addr_CI_factor, array_temp, 2, 0xA0);
    /********************************按键校准斜率*********************/

    if (Type_Cur == 0) // 125壳架
    {

        IWDG_Feed();
        array_temp[0] = 0xF8;
        array_temp[1] = 0x45;
        MODIFY_EEP_W(Addr_L1_slope, array_temp, 2, 0xA0); // 125壳架的漏电斜率

        array_temp[0] = 0xB7;
        array_temp[1] = 0x29;
        MODIFY_EEP_W(Addr_Leak1_temp, array_temp, 2, 0xA0);
    }
    else
    {

        IWDG_Feed();
        array_temp[0] = 0xA9;
        array_temp[1] = 0x41;
        MODIFY_EEP_W(Addr_L1_slope, array_temp, 2, 0xA0); // 250壳架的漏电斜率

        array_temp[0] = 0xBA;
        array_temp[1] = 0x43;
        MODIFY_EEP_W(Addr_Leak1_temp, array_temp, 2, 0xA0);
    }

    array_temp[1] = 17016 >> 8;
    array_temp[0] = 17016 & 0xff;
    MODIFY_EEP_W(Addr_V1_A_slope, array_temp, 2, 0xA0);

    array_temp[1] = 17096 >> 8;
    array_temp[0] = 17096 & 0xff;
    MODIFY_EEP_W(Addr_V1_B_slope, array_temp, 2, 0xA0);

    array_temp[1] = 17246 >> 8;
    array_temp[0] = 17246 & 0xff;
    MODIFY_EEP_W(Addr_V1_C_slope, array_temp, 2, 0xA0);
    /***********250壳架******************/
    array_temp[0] = 0x9E;
    array_temp[1] = 0x41;
    MODIFY_EEP_W(Addr_I1_A_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x66;
    array_temp[1] = 0x41;
    MODIFY_EEP_W(Addr_I1_B_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xB2;
    array_temp[1] = 0x40;
    MODIFY_EEP_W(Addr_I1_C_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0xA7;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr_I1_A_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x9D;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr_I1_B_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x7F;
    array_temp[1] = 0x3E;
    MODIFY_EEP_W(Addr_I1_C_slope1, array_temp, 2, 0xA0);

    array_temp[0] = 0x7A;
    array_temp[1] = 0x15;
    MODIFY_EEP_W(Addr_CurA_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0xCC;
    array_temp[1] = 0x15;
    MODIFY_EEP_W(Addr_CurB_cal_tmp, array_temp, 2, 0xA0);
    array_temp[0] = 0xCF;
    array_temp[1] = 0x15;
    MODIFY_EEP_W(Addr_CurC_cal_tmp, array_temp, 2, 0xA0);

    array_temp[0] = 0x42;
    array_temp[1] = 0x36;
    MODIFY_EEP_W(Addr_CurA_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0x58;
    array_temp[1] = 0x36;
    MODIFY_EEP_W(Addr_CurB_cal_tmp1, array_temp, 2, 0xA0);
    array_temp[0] = 0xFF;
    array_temp[1] = 0x36;
    MODIFY_EEP_W(Addr_CurC_cal_tmp1, array_temp, 2, 0xA0);

    array_temp[0] = 0x48;
    array_temp[1] = 0x45;
    MODIFY_EEP_W(Addr_I1_A_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x48;
    array_temp[1] = 0x45;
    MODIFY_EEP_W(Addr_I1_B_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x8D;
    array_temp[1] = 0x3E;
    MODIFY_EEP_W(Addr_I1_C_slope_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0xB5;
    array_temp[1] = 0x40;
    MODIFY_EEP_W(Addr_I1_A_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xB5;
    array_temp[1] = 0x40;
    MODIFY_EEP_W(Addr_I1_B_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xEB;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr_I1_C_slope1_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0x7A;
    array_temp[1] = 0x15;
    MODIFY_EEP_W(Addr_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xCC;
    array_temp[1] = 0x15;
    MODIFY_EEP_W(Addr_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xCF;
    array_temp[1] = 0x15;
    MODIFY_EEP_W(Addr_CurC_cal_tmp_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0x42;
    array_temp[1] = 0x36;
    MODIFY_EEP_W(Addr_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x58;
    array_temp[1] = 0x36;
    MODIFY_EEP_W(Addr_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xFF;
    array_temp[1] = 0x36;
    MODIFY_EEP_W(Addr_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
    //				array_temp[0]=0x5D;
    //		array_temp[1]=0x52;
    //		MODIFY_EEP_W(Addr_I1_A_slope,array_temp,2,0xA0);
    //
    //		array_temp[0]=0xB1;
    //		array_temp[1]=0x50;
    //		MODIFY_EEP_W(Addr_I1_B_slope,array_temp,2,0xA0);
    //
    //		array_temp[0]=0x8F;
    //		array_temp[1]=0x51;
    //		MODIFY_EEP_W(Addr_I1_C_slope,array_temp,2,0xA0);
    //
    //	  array_temp[0]=0xBF;
    //		array_temp[1]=0x52;
    //		MODIFY_EEP_W(Addr_I1_A_slope1,array_temp,2,0xA0);
    //
    //		array_temp[0]=0x94;
    //		array_temp[1]=0x52;
    //		MODIFY_EEP_W(Addr_I1_B_slope1,array_temp,2,0xA0);
    //
    //		array_temp[0]=0xF8;
    //		array_temp[1]=0x52;
    //		MODIFY_EEP_W(Addr_I1_C_slope1,array_temp,2,0xA0);
    //
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurA_cal_tmp,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurB_cal_tmp,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurC_cal_tmp,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurA_cal_tmp1,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurB_cal_tmp1,array_temp,2,0xA0);
    //		array_temp[0]=0xAF;
    //		array_temp[1]=0x13;
    //		MODIFY_EEP_W(Addr_CurC_cal_tmp1,array_temp,2,0xA0);
    array_temp[0] = 0xE8; // 0xD1;
    array_temp[1] = 0x4E; // 0x10;
    MODIFY_EEP_W(Addr_Vol1_A_temp, array_temp, 2, 0xA0);
    array_temp[0] = 0xE8;
    array_temp[1] = 0x4E;
    MODIFY_EEP_W(Addr_Vol1_B_temp, array_temp, 2, 0xA0);
    array_temp[0] = 0xE8;
    array_temp[1] = 0x4E;
    MODIFY_EEP_W(Addr_Vol1_C_temp, array_temp, 2, 0xA0);

    /**************100壳架*******************/
    IWDG_Feed();
    array_temp[0] = 0x2A;
    array_temp[1] = 0x5D;
    MODIFY_EEP_W(Addr100_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr100_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0x90;
    array_temp[1] = 0x1A;
    MODIFY_EEP_W(Addr100_I1_A_slope, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_I1_A_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x90;
    array_temp[1] = 0x1A;
    MODIFY_EEP_W(Addr100_I1_B_slope, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_I1_B_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x90;
    array_temp[1] = 0x1A;
    MODIFY_EEP_W(Addr100_I1_C_slope, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_I1_C_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xFA;
    array_temp[1] = 0x19;
    MODIFY_EEP_W(Addr100_I1_A_slope1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_I1_A_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xFA;
    array_temp[1] = 0x19;
    MODIFY_EEP_W(Addr100_I1_B_slope1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_I1_B_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xFA;
    array_temp[1] = 0x19;
    MODIFY_EEP_W(Addr100_I1_C_slope1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_I1_C_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x12;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr100_CurA_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xBC;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr100_CurB_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x74;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr100_CurC_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_CurC_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xB6;
    array_temp[1] = 0x1D;
    MODIFY_EEP_W(Addr100_CurA_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x7C;
    array_temp[1] = 0x1E;
    MODIFY_EEP_W(Addr100_CurB_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x11;
    array_temp[1] = 0x1E;
    MODIFY_EEP_W(Addr100_CurC_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr100_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
    /**************400壳架*******************/
    IWDG_Feed();
    array_temp[0] = 0x19;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr400_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr400_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0x90;
    array_temp[1] = 0x65;
    MODIFY_EEP_W(Addr400_I1_A_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x1C;
    array_temp[1] = 0x66;
    MODIFY_EEP_W(Addr400_I1_A_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x90;
    array_temp[1] = 0x65;
    MODIFY_EEP_W(Addr400_I1_B_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x66;
    array_temp[1] = 0x66;
    MODIFY_EEP_W(Addr400_I1_B_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x90;
    array_temp[1] = 0x65;
    MODIFY_EEP_W(Addr400_I1_C_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0x4A;
    array_temp[1] = 0x65;
    MODIFY_EEP_W(Addr400_I1_C_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x97;
    array_temp[1] = 0x61;
    MODIFY_EEP_W(Addr400_I1_A_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x97;
    array_temp[1] = 0x61;
    MODIFY_EEP_W(Addr400_I1_A_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x97;
    array_temp[1] = 0x62;
    MODIFY_EEP_W(Addr400_I1_B_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x97;
    array_temp[1] = 0x62;
    MODIFY_EEP_W(Addr400_I1_B_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x01;
    array_temp[1] = 0x61;
    MODIFY_EEP_W(Addr400_I1_C_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x01;
    array_temp[1] = 0x61;
    MODIFY_EEP_W(Addr400_I1_C_slope1_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0xC9;
    array_temp[1] = 0x17;
    MODIFY_EEP_W(Addr400_CurA_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr400_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x20;
    array_temp[1] = 0x18;
    MODIFY_EEP_W(Addr400_CurB_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr400_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x29;
    array_temp[1] = 0x18;
    MODIFY_EEP_W(Addr400_CurC_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr400_CurC_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x83;
    array_temp[1] = 0x3B;
    MODIFY_EEP_W(Addr400_CurA_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr400_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x84;
    array_temp[1] = 0x3B;
    MODIFY_EEP_W(Addr400_CurB_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr400_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x58;
    array_temp[1] = 0x3C;
    MODIFY_EEP_W(Addr400_CurC_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr400_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
    /**************630壳架*******************/
    IWDG_Feed();
    array_temp[0] = 0x0E;
    array_temp[1] = 0x57;
    MODIFY_EEP_W(Addr630_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr630_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0x51;
    array_temp[1] = 0x91;
    MODIFY_EEP_W(Addr630_I1_A_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xCF;
    array_temp[1] = 0x95;
    MODIFY_EEP_W(Addr630_I1_A_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xF6;
    array_temp[1] = 0x93;
    MODIFY_EEP_W(Addr630_I1_B_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xBA;
    array_temp[1] = 0x96;
    MODIFY_EEP_W(Addr630_I1_B_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xB9;
    array_temp[1] = 0x8E;
    MODIFY_EEP_W(Addr630_I1_C_slope, array_temp, 2, 0xA0);
    array_temp[0] = 0xEC;
    array_temp[1] = 0x94;
    MODIFY_EEP_W(Addr630_I1_C_slope_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0xA7;
    array_temp[1] = 0x96;
    MODIFY_EEP_W(Addr630_I1_A_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0xBC;
    array_temp[1] = 0x95;
    MODIFY_EEP_W(Addr630_I1_A_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x0F;
    array_temp[1] = 0x98;
    MODIFY_EEP_W(Addr630_I1_B_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x7E;
    array_temp[1] = 0x96;
    MODIFY_EEP_W(Addr630_I1_B_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x46;
    array_temp[1] = 0x95;
    MODIFY_EEP_W(Addr630_I1_C_slope1, array_temp, 2, 0xA0);
    array_temp[0] = 0x46;
    array_temp[1] = 0x94;
    MODIFY_EEP_W(Addr630_I1_C_slope1_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0xCC;
    array_temp[1] = 0x18;
    MODIFY_EEP_W(Addr630_CurA_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr630_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x12;
    array_temp[1] = 0x19;
    MODIFY_EEP_W(Addr630_CurB_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr630_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x2A;
    array_temp[1] = 0x19;
    MODIFY_EEP_W(Addr630_CurC_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr630_CurC_cal_tmp_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0x74;
    array_temp[1] = 0x3C;
    MODIFY_EEP_W(Addr630_CurA_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr630_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x82;
    array_temp[1] = 0x3C;
    MODIFY_EEP_W(Addr630_CurB_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr630_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x4E;
    array_temp[1] = 0x3D;
    MODIFY_EEP_W(Addr630_CurC_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr630_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
    /**************800壳架*******************/
    IWDG_Feed();
    array_temp[0] = 0xEA;
    array_temp[1] = 0x60;
    MODIFY_EEP_W(Addr800_L1_slope, array_temp, 2, 0xA0);

    array_temp[0] = 0x84;
    array_temp[1] = 0x3F;
    MODIFY_EEP_W(Addr800_Leak1_temp, array_temp, 2, 0xA0);

    array_temp[0] = 0xDC;
    array_temp[1] = 0x5A;
    MODIFY_EEP_W(Addr800_I1_A_slope, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_I1_A_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xDC;
    array_temp[1] = 0x5A;
    MODIFY_EEP_W(Addr800_I1_B_slope, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_I1_B_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xDC;
    array_temp[1] = 0x5A;
    MODIFY_EEP_W(Addr800_I1_C_slope, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_I1_C_slope_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x9D;
    array_temp[1] = 0x64;
    MODIFY_EEP_W(Addr800_I1_A_slope1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_I1_A_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x9D;
    array_temp[1] = 0x64;
    MODIFY_EEP_W(Addr800_I1_B_slope1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_I1_B_slope1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x9D;
    array_temp[1] = 0x64;
    MODIFY_EEP_W(Addr800_I1_C_slope1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_I1_C_slope1_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0x4F;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr800_CurA_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x4F;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr800_CurB_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0x4F;
    array_temp[1] = 0x0C;
    MODIFY_EEP_W(Addr800_CurC_cal_tmp, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_CurC_cal_tmp_nv, array_temp, 2, 0xA0);

    array_temp[0] = 0xEB;
    array_temp[1] = 0x4B;
    MODIFY_EEP_W(Addr800_CurA_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xEB;
    array_temp[1] = 0x4B;
    MODIFY_EEP_W(Addr800_CurB_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
    array_temp[0] = 0xEB;
    array_temp[1] = 0x4B;
    MODIFY_EEP_W(Addr800_CurC_cal_tmp1, array_temp, 2, 0xA0);
    MODIFY_EEP_W(Addr800_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
    /******************************************************************************************/
    IWDG_Feed();
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_AV_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_BV_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_CV_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_AI_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_BI_F, array_temp, 1, 0xA0);
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_CI_F, array_temp, 1, 0xA0);
    // AT24C64_W(array_temp,16,1);
    array_temp[0] = 0xAA;
    // AT24C64_W(array_temp,17,1)
    //    array_tmp[0] = 0x01;
    //    MODIFY_EEP_W(Addr_shangdian,array_tmp,1,0xA0);
    array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_jiaozhun, array_tmp, 1, 0xA0);
    array_tmp[0] = 0x01;
    MODIFY_EEP_W(Addr_DIANYA_chonghe, array_tmp, 1, 0xA0);
    array_tmp[0] = 0x00;
    MODIFY_EEP_W(Addr_duandian, array_tmp, 1, 0xA0);
    /*          累计记录清零          */
    // 数据清零总次数 000000
    IWDG_Feed();
    array_temp[0] = array_temp[1] = array_temp[2] = 0;
    lenth = Lenth_clear_num;
    Addr_factor = Addr_clear_num;
    MODIFY_EEP_W(Addr_factor, array_temp, lenth, 0xA0);
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
    // 退出漏电保护次数
    IWDG_Feed();
    // 运行时间
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_leakquit_num, array_temp, 2, 0xA0);

    // 短路短延次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_2D_num, array_temp, 2, 0xA0);
    // 剩余电流保护退出报警次数
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_leakprotect_num, array_temp, 2, 0xA0);
    // 剩余电流超限次数
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_leakover_num, array_temp, 2, 0xA0);
    // 剩余电流变化次数
    //	array_temp[0] = 0;
    //	MODIFY_EEP_W(Addr_leakchange_num,array_temp,1);
    // 自检次数
    //	array_temp[0] = 0;
    //	MODIFY_EEP_W(Addr_tripkey_num,array_temp,1);
    // 短路短瞬次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_3D_num, array_temp, 2, 0xA0);
    Sum_run_time = 0;
    DectoBCD(array_temp, Sum_run_time, 4);
    MODIFY_EEP_W(Addr_protect_time, array_temp, 4, 0xA0);

    if (tmp == 0x01)
    {
        tim_y = 2017;
        tim_m = 6;
        ;
        tim_d = 11;
        tim_h = 1;
        tim_f = 1;
        tim_s = 0;
    }
    else
    {
        tim_y = 2017;
        tim_m = 6;
        ;
        tim_d = 11;
        tim_h = 1;
        tim_f = 1;
        tim_s = 0;
    }
    IWDG_Feed();
    RTC_Set_Time(array_temp[3], array_temp[4], array_temp[5]);
    RTC_Set_Date(array_temp[0], array_temp[1], array_temp[2]);
    // 设备地址

    Addr_factor = Addr_dev_addr;
    lenth = Lenth_dev_addr;
    self_addr_code[0] = 0x00;
    self_addr_code[1] = 0x00;
    self_addr_code[2] = 0x00;
    self_addr_code[3] = 0x00;
    self_addr_code[4] = 0x00;
    self_addr_code[5] = 0x00; // lpb,设备断电自动回复初始地址
    MODIFY_EEP_W(Addr_factor, self_addr_code, lenth, 0xA0);
    // 设备ID
    Addr_factor = Addr_dev_id;
    lenth = Lenth_dev_id;
    MODIFY_EEP_W(Addr_factor, dev_id_code, lenth, 0xA0);
    // 资产管理代码
    Addr_factor = Addr_dev_code;
    lenth = Lenth_dev_code;
    MODIFY_EEP_W(Addr_factor, dev_code_code, lenth, 0xA0);
    // 设备型号
    Addr_factor = Addr_equi_type;
    lenth = Lenth_equi_type;
    MODIFY_EEP_W(Addr_factor, equi_type_code, lenth, 0xA0);
    IWDG_Feed();

    IWDG_Feed();
    Addr_factor = Addr_factory_code;
    lenth = Lenth_factory_code;
    MODIFY_EEP_W(Addr_factor, factory_code_code, lenth, 0xA0);
    // 剩余电流超限报警整定值 2
    Addr_factor = Addr_alarm_value;
    lenth = Lenth_alarm_value;
    MODIFY_EEP_W(Addr_factor, alarm_value_code, lenth, 0xA0);
    // 剩余电流记录变化差值整定值(10-99)
    Addr_factor = Addr_record_value;
    lenth = Lenth_record_value;
    MODIFY_EEP_W(Addr_factor, record_value_code, lenth, 0xA0);
    // 剩余电流记录间隔时间整定值(01-99)
    Addr_factor = Addr_record_time;
    lenth = Lenth_record_time;
    MODIFY_EEP_W(Addr_factor, record_time_code, lenth, 0xA0);
    // 定时试跳整定时间 3
    Addr_factor = Addr_timed_trip;
    lenth = Lenth_timed_trip;
    MODIFY_EEP_W(Addr_factor, timed_trip_code, lenth, 0xA0);
    IWDG_Feed();
    // 过电压整定值 2
    Addr_factor = Addr_over_vol;
    lenth = Lenth_over_vol;
    MODIFY_EEP_W(Addr_factor, over_vol_code, lenth, 0xA0);
    // 欠电压整定值 2
    Addr_factor = Addr_under_vol;
    lenth = Lenth_under_vol;
    MODIFY_EEP_W(Addr_factor, under_vol_code, lenth, 0xA0);

    IWDG_Feed();
    // 断相电压整定值 2
    Addr_factor = Addr_break_phase;
    lenth = Lenth_break_phase;
    MODIFY_EEP_W(Addr_factor, break_phase_code, lenth, 0xA0);
    // 额定电流整定值 3
    Addr_factor = Addr_rated_current;
    lenth = Lenth_rated_current;
    MODIFY_EEP_W(Addr_factor, rated_current_code, lenth, 0xA0);
    // 电流超限报警
    Addr_factor = Addr_over_current;
    lenth = Lenth_over_current;
    MODIFY_EEP_W(Addr_factor, over_current_code, lenth, 0xA0);

    // 密码
    array_temp[0] = 0x00;
    array_temp[1] = 0x00;
    array_temp[2] = 0x00;
    array_temp[3] = 0x00;
    MODIFY_EEP_W(Addr_0_password, array_temp, 4, 0xA0);
    array_temp[0] = 0x01;
    array_temp[1] = 0x11;
    array_temp[2] = 0x11;
    array_temp[3] = 0x11;
    MODIFY_EEP_W(Addr_1_password, array_temp, 4, 0xA0);
    array_temp[0] = 0x02;
    array_temp[1] = 0x22;
    array_temp[2] = 0x22;
    array_temp[3] = 0x22;
    MODIFY_EEP_W(Addr_2_password, array_temp, 4, 0xA0);
    // 波特率
    array_temp[0] = 0x01;
    MODIFY_EEP_W(Addr_baud, array_temp, 1, 0xA0);

    IWDG_Feed();
    /*      事件记录指针清零            */
    //  漏电记录的地址指针
    array_temp[0] = 0x00;
    array_temp[1] = 0x00;
    MODIFY_EEP_W(Addr_point_leakrecord, array_temp, 2, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_leak_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Avol_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Bvol_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Cvol_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Acur_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Bcur_max, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Ccur_max, array_temp, 1, 0xA0);
    IWDG_Feed();
    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_leak_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Avol_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Bvol_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Cvol_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Acur_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Bcur_min, array_temp, 1, 0xA0);

    array_temp[0] = 0x00;
    MODIFY_EEP_W(Addr_point_Ccur_min, array_temp, 1, 0xA0);

    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_trip, array_temp, 1, 0xA0);

    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_trip_24C256, array_temp, 1, 0xA0);
    IWDG_Feed();
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_self, array_temp, 1, 0xA0);

    array_temp[0] = 0;
    array_temp[1] = 0;
    array_temp[2] = 0;
    array_temp[3] = 0;
    MODIFY_EEP_W(Addr_mima_set, array_temp, 4, 0xA0);

    // 短接分合闸模式初始化
    array_temp[0] = 0;
    MODIFY_EEP_W(External_Gate_Control_Flag_Addr, array_temp, 1, 0xA0);

    // Rewrite_buffer(0);
    // pw1 = 0x12;pw2 = 0x34;pw3 = 0x56;pw4 = 0x78;
    // IapEraseSector(512);
    // IapEraseSector(1024);
    Addr_factor = 10500;
    lenth = 1000;
    //	EEPROM_C(Addr_factor,lenth);
    //	EEPROM_R(Addr_FACTORINIT_value,array_tmp,150);
    //	MODIFY_EEP_W(Addr_FACTORINIT_value,array_tmp,150);
}

void clear_flags(void)
{
    // 保持重合闸前的漏电故障记录状态
    if ((F_Trip == 1) || (F_Trip == 2))
    {
        F_Trip = 2;
    }
    else
    {
        F_Trip = 0;
    }
    // F_gz = 0;
    GZ_ph = 0;
    GZ_ph_disp = 0;
    F_TB_start = 0;
    F_TB_gz = 0;
    F_gz_clear = 1;
    F_L_Lock = 0;
    // F_fenzha_G_Array[0]=F_fenzha_G_Array[1]=F_fenzha_G_Array[2]=0 ;
    // F_fenzha_Q_Array[0]=F_fenzha_Q_Array[1]=F_fenzha_Q_Array[2]=0 ;
    F_qxTrip = F_qyTrip = F_gyTrip = F_syTrip = 0; // 缺相 过压 欠压 跳闸
    F_I_Lock = 0;
    F_GTrip = F_QTrip = 0;
    F_ITrip = F_VTrip = F_UTrip = F_STrip = 0;
    // 保持重合闸前的过电流故障记录状态
    if (F_I_STA == 1)
        F_I_STA = 2;
    else
    {
        F_I_STA = 0;
        F_I_Array[0] = F_I_Array[1] = F_I_Array[2] = F_I_Array[3] = 0;
    }
    T_64_xs = T_64_6s = 0;
    T_64_31s = 0;
    T_64_11s = 0;
    F_L_hezha = F_I_hezha = F_V_hezha = F_UP_hezha = 0;
    T_64_40s = 0;
    F_fz = 0;
    //	if(isfenzha!=0)
    //	//机构故障标志清零
    //	F_ks=0 ;
    // 快速动作标志
    //	F_disp_jg = 0;
    F_disp_tr = 0;
    F_gz_disp = 0x0F;
    F_analog_trip = 0;
    F_tim_gz = 0;
}
/*************************************************
                写记录部分

Record_data_propare()
Write_Record(unsigned char gz_r,unsigned char gz_p)
**************************************************/
unsigned char time_disp[5];
void Write_Leak_Record(void)
{
    unsigned char i;
    unsigned char array_temp_R[14], time_tmp[7];
    unsigned int addr_tmp;
    IWDG_Feed(); // 喂狗
    //	ds1302_read_time_uart(time_tmp);
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    //	tim_y=tim_y%2000;  //time_tmp[0]=17   十进制转换为二进制存入24C64中
    //	time_tmp[0]=(tim_y/10)<<4;
    //	time_tmp[0]+=(tim_y%10);
    //	time_tmp[1]=(tim_m/10)<<4;
    //	time_tmp[1]+=(tim_m%10);
    //	time_tmp[2]=(tim_d/10)<<4;
    //	time_tmp[2]+=(tim_d%10);
    //	time_tmp[3]=(tim_h/10)<<4;
    //	time_tmp[3]+=(tim_h%10);
    //	time_tmp[4]=(tim_f/10)<<4;
    //	time_tmp[4]+=(tim_f%10);
    //	time_tmp[5]=(tim_s/10)<<4;
    //	time_tmp[5]+=(tim_s%10);
    time_tmp[0] = tim_y;
    time_tmp[1] = tim_m;
    time_tmp[2] = tim_d;
    time_tmp[3] = tim_h;
    time_tmp[4] = tim_f;
    time_tmp[5] = tim_s;

    for (i = 0; i < 6; i++)
    {
        array_temp_R[3 + i] = time_tmp[5 - i]; // array_temp_R[3]=time_tmp[5]    array_temp_R[4]=time_tmp[4]
    }
    array_temp_R[0] = max_phase;                  // 0x01;
    DectoBCD(&array_temp_R[1], Leak_Cur_disp, 2); // Leak_Cur_disp  为十进制
    point_Leak_record = point_Leak_record + 1;
    if (point_Leak_record == 512)
        point_Leak_record = 0;
    addr_tmp = Addr_record_leak1 + (point_Leak_record * 9);
    MODIFY_EEP_W(addr_tmp, array_temp_R, 9, 0xA0); // 起始地址  写记录   先写秒再写年
    DectoBCD(array_temp_R, point_Leak_record, 2);
    MODIFY_EEP_W(Addr_point_leakrecord, array_temp_R, 2, 0xA0);
}

void Write_Selftest_Record(unsigned char self_method)
{
    unsigned char Buf_temp[30], time_tmp[7], i, E2_temp[2];
    Buf_temp[0] = fenzha_chenggong;
    //	ds1302_read_time_uart(time_tmp);
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    //	tim_y=tim_y%2000;  //time_tmp[0]=17   十进制转换为二进制存入24C64中
    time_tmp[0] = tim_y;
    time_tmp[1] = tim_m;
    time_tmp[2] = tim_d;
    time_tmp[3] = tim_h;
    time_tmp[4] = tim_f;
    time_tmp[5] = tim_s;
    for (i = 0; i < 6; i++)
    {
        Buf_temp[1 + i] = time_tmp[5 - i];
    }
    Buf_temp[7] = self_method;
    Buf_temp[8] = max_phase;                         // 0x01;
    DectoBCD(&Buf_temp[9], Leak_Cur_disp_record, 2); // 漏电
    DectoBCD(&Buf_temp[11], ((vol_handle_A(V_Array_record[0])) * 10), 2);
    DectoBCD(&Buf_temp[13], ((vol_handle_B(V_Array_record[1])) * 10), 2);
    DectoBCD(&Buf_temp[15], ((vol_handle_C(V_Array_record[2])) * 10), 2);
    DectoBCD(&Buf_temp[17], ((cur_handle_A(I_Array_record[0])) * 10), 3);
    DectoBCD(&Buf_temp[20], ((cur_handle_B(I_Array_record[1])) * 10), 3);
    DectoBCD(&Buf_temp[23], ((cur_handle_C(I_Array_record[2])) * 10), 3);
    MODIFY_EEP_W((Addr_event_self + 26 * point_event_self), Buf_temp, 25, 0xA0);

    point_event_self = point_event_self + 1;
    if (point_event_self >= 10)
    {
        point_event_self = 0x00;
    }
    E2_temp[0] = point_event_self;
    MODIFY_EEP_W(Addr_point_event_self, E2_temp, 1, 0xA0);
}

void Record_data_propare(void)
{
    // unsigned int tmp_A1,tmp_A2;
    //  tmp_A1 = vol_handle_A(Vol_A_aver)
    //  tmp_A2 = (tmp_A1<<2)-(tmp_A1>>1);
    //  V_Array[0] = tmp_A2-109;
    Leak_Cur_disp_record = Leak_Cur_disp;
    V_Array_record[0] = V_Array[0];
    V_Array_record[1] = V_Array[1];
    V_Array_record[2] = V_Array[2];
    I_Array_record[0] = I_Array_xianshi[0];
    I_Array_record[1] = I_Array_xianshi[1];
    I_Array_record[2] = I_Array_xianshi[2];
}

// STC修改
void Write_Record(unsigned char gz_r, unsigned char gz_p)
{
    unsigned char Buf_temp[30];
    unsigned char i, E2_temp[2], time_tmp[8], F_norecord;
    IWDG_Feed(); // 喂狗
    /***********总跳闸次数***********/
    F_norecord = 0;
    F_gz = gz_r;
    if (F_gz == 0x0B)
        F_gz = 0;
    point_trip = point_trip + 1;
    if (point_trip == 0x08)
        point_trip = 0x07;

    if (1)
    {
        Num_tripall = Num_tripall + 1;
        DectoBCD(Buf_temp, Num_tripall, 2);
        MODIFY_EEP_W(Addr_trip_num, Buf_temp, 2, 0xA0);
    }
    if (gz_r == trip_reason_leak)
    {

        if (F_gc == 1)
        {
            Num_tripleak = Num_tripleak + 1;
            DectoBCD(BCD_temp, Num_tripleak, 2);
            MODIFY_EEP_W(Addr_leak_num, BCD_temp, 2, 0xA0);
        }
        else
        {
            F_norecord = 1;
            Num_tripall = Num_tripall - 1;
            DectoBCD(Buf_temp, Num_tripall, 2);
            MODIFY_EEP_W(Addr_trip_num, Buf_temp, 2, 0xA0);
        }
    }
    /***********闭锁性跳闸次数***********即不会重合闸的跳闸*/
    if (gz_r == trip_reason_lock)
    {
        if (F_L_Lock == 1)
        {
            Num_triplock = Num_triplock + 1;
            DectoBCD(Buf_temp, Num_triplock, 2);
            MODIFY_EEP_W(Addr_close_num, Buf_temp, 2, 0xA0);
            Num_tripleak = Num_tripleak + 1;
            DectoBCD(BCD_temp, Num_tripleak, 2);
            MODIFY_EEP_W(Addr_leak_num, BCD_temp, 2, 0xA0);
        }
    }
    /***********剩余电流跳闸次数*********/

    /***************电流保护跳闸次数*********/
    if (gz_r == trip_reason_cur)
    {
        if (F_gc == 1)
        {
            Num_tripcur = Num_tripcur + 1;
            DectoBCD(Buf_temp, Num_tripcur, 2);
            MODIFY_EEP_W(Addr_current_num, Buf_temp, 2, 0xA0);
        }
        else
        {
            F_norecord = 1;
            Num_tripall = Num_tripall - 1;
            DectoBCD(Buf_temp, Num_tripall, 2);
            MODIFY_EEP_W(Addr_trip_num, Buf_temp, 2, 0xA0);
        }
    }
    /***************电压保护跳闸次数*********/
    if (gz_r == trip_reason_overvoltage)
    {

        //		if(F_gc==1)
        //		{
        Num_tripvol = Num_tripvol + 1;
        DectoBCD(Buf_temp, Num_tripvol, 2);
        MODIFY_EEP_W(Addr_vol_num, Buf_temp, 2, 0xA0);
        //		}
        //		else
        //		{
        //			F_norecord = 1;
        //			Num_tripall=Num_tripall-1 ;
        //			DectoBCD(Buf_temp,Num_tripall,2);
        //			MODIFY_EEP_W(Addr_trip_num,Buf_temp,2);
        //		}
    }
    if (gz_r == trip_reason_undervoltage)
    {
        Num_leakover = Num_leakover + 1;
        DectoBCD(Buf_temp, Num_leakover, 2);
        MODIFY_EEP_W(Addr_leakover_num, Buf_temp, 2, 0xA0);
    }
    if (gz_r == trip_reason_phase)
    {
        Num_leakprotect = Num_leakprotect + 1;
        DectoBCD(Buf_temp, Num_leakprotect, 2);
        MODIFY_EEP_W(Addr_leakprotect_num, Buf_temp, 2, 0xA0);
    }
    /***************手动次数*********/
    if (gz_r == trip_reason_hand)
    {
        Num_triphand = Num_triphand + 1;
        DectoBCD(Buf_temp, Num_triphand, 2);
        MODIFY_EEP_W(Addr_hand_num, Buf_temp, 2, 0xA0);
    }
    /***************缺零次数*********/
    if (gz_r == trip_reason_zero)
    {
        Num_tripzero = Num_tripzero + 1;
        DectoBCD(Buf_temp, Num_tripzero, 2);
        MODIFY_EEP_W(Addr_zero_num, Buf_temp, 2, 0xA0);
    }
    /***************试验跳闸次数*********/
    if ((gz_r == trip_reason_timer) || (gz_r == trip_reason_key) || (gz_r == trip_reason_remote))
    {
        Num_triptest = Num_triptest + 1;
        DectoBCD(Buf_temp, Num_triptest, 2);
        MODIFY_EEP_W(Addr_test_num, Buf_temp, 2, 0xA0);
    }
    //	if(gz_r==trip_reason_key)
    //	{
    //	Num_tripkey=Num_tripkey+1;
    //	DectoBCD(Buf_temp,Num_tripkey,2);
    //	MODIFY_EEP_W(Addr_tripkey_num,Buf_temp,2);
    //	}
    /***************退出保护次数*********/
    if (gz_r == trip_reason_quit)
    {
        Num_quitleak = Num_quitleak + 1;
        DectoBCD(Buf_temp, Num_quitleak, 2);
        MODIFY_EEP_W(Addr_leakquit_num, Buf_temp, 2, 0xA0);
    }
    if (gz_r == trip_reason_short)
    {
        Num_tripdelay = Num_tripdelay + 1;
        DectoBCD(Buf_temp, Num_tripdelay, 2);
        MODIFY_EEP_W(Addr_2D_num, Buf_temp, 2, 0xA0);
    }
    if (gz_r == trip_reason_3D_cur)
    {
        Num_tripinstant = Num_tripinstant + 1;
        DectoBCD(Buf_temp, Num_tripinstant, 2);
        MODIFY_EEP_W(Addr_3D_num, Buf_temp, 2, 0xA0);
    }
    /************漏电跳闸,记录***********/
    Buf_temp[0] = gz_r;

    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    time_disp[0] = time_tmp[0] = tim_y;
    time_disp[1] = time_tmp[1] = tim_m;
    time_disp[2] = time_tmp[2] = tim_d;
    time_disp[3] = time_tmp[3] = tim_h;
    time_disp[4] = time_tmp[4] = tim_f;
    time_disp[5] = time_tmp[5] = tim_s;

    for (i = 0; i < 6; i++)
    {
        Buf_temp[1 + i] = time_tmp[5 - i];
    }

    Buf_temp[9] = gz_p;
    DectoBCD(&Buf_temp[7], gz_disp, 2); // 故障值
    // gz_disp = 0;

    MODIFY_EEP_W((10 * point_event_trip), Buf_temp, 10, 0xA0); // 地址问题

    if (point_event_trip <= 9)
    {
        MODIFY_EEP_W((10 * point_event_trip), Buf_temp, 10, 0xA0);
        // AT24C64_W(Buf_temp,(10*point_event_trip+10500),10);
        // //			EEPROM_R(Buf_temp,(10*point_event_trip),10,1);
    }

    if (point_event_trip > 9)
    {
        MODIFY_EEP_W((10 * (point_event_trip - 10)), Buf_temp, 10, 0xA0);
        // AT24C64_W(Buf_temp,(10*point_event_trip+11000),10);
        // //			EEPROM_R(Buf_temp,(10*(point_event_trip-10)),10,2);
    }
    point_event_trip = point_event_trip + 1;
    if (point_event_trip >= 20)
    {
        point_event_trip = 0x00;
    }
    E2_temp[0] = point_event_trip;
    // MODIFY_EEP_W(E2_temp,Addr_point_event_trip,1,0);

    MODIFY_EEP_W(Addr_point_event_trip, E2_temp, 1, 0xA0);

    EEPROM_R(Addr_point_event_trip, Buf_temp, 1, 0xA0); // 2017 6 10 浙江修改过

    /*以下是记录到24C256中的记录*******************/
    if (F_norecord == 0)
    {
        Buf_temp[0] = gz_r; // 故障原因
        Buf_temp[1] = gz_p; // 故障相位,此处待修改

        //		ds1302_read_time_uart(&Buf_temp[2]);  // [1][0]   从[2]开始读

        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
        tim_m = sdatestructure.Month;
        tim_d = sdatestructure.Date;
        tim_h = stimestructure.Hours;
        tim_f = stimestructure.Minutes;
        tim_s = stimestructure.Seconds;
        Buf_temp[2] = tim_y;
        Buf_temp[3] = tim_m;
        Buf_temp[4] = tim_d;
        Buf_temp[5] = tim_h;
        Buf_temp[6] = tim_f;
        Buf_temp[7] = tim_s;
        //	  tim_y=tim_y%2000;  //time_tmp[0]=17   十进制转换为二进制存入24C64中
        //	  Buf_temp[2]=(tim_y/10)<<4;
        //	  Buf_temp[2]+=(tim_y%10);
        //	  Buf_temp[3]=(tim_m/10)<<4;
        //	  Buf_temp[3]+=(tim_m%10);
        //  	Buf_temp[4]=(tim_d/10)<<4;
        //  	Buf_temp[4]+=(tim_d%10);
        //  	Buf_temp[5]=(tim_h/10)<<4;
        //  	Buf_temp[5]+=(tim_h%10);
        //  	Buf_temp[6]=(tim_f/10)<<4;
        //  	Buf_temp[6]+=(tim_f%10);
        //  	Buf_temp[7]=(tim_s/10)<<4;
        //  	Buf_temp[7]+=(tim_s%10);

        copy_array(time_tmp, &Buf_temp[2], 6);
        for (i = 0; i < 6; i++)
        {
            Buf_temp[2 + i] = time_tmp[5 - i];
        }
        if (gz_r == 0x0B)
        {
            Leak_Cur_disp_record = 0;
            V_Array_record[0] = V_Array_record[1] = V_Array_record[2] = 0;
            I_Array_record[0] = I_Array_record[1] = I_Array_record[2] = 0;
        }
        DectoBCD(&Buf_temp[8], Leak_Cur_disp_record, 2); // 漏电
        DectoBCD(&Buf_temp[10], ((vol_handle_A(V_Array_record[0])) * 10), 2);
        DectoBCD(&Buf_temp[12], ((vol_handle_B(V_Array_record[1])) * 10), 2);
        DectoBCD(&Buf_temp[14], ((vol_handle_C(V_Array_record[2])) * 10), 2);
        DectoBCD(&Buf_temp[16], ((cur_handle_A(I_Array_record[0])) * 10), 3);
        DectoBCD(&Buf_temp[19], ((cur_handle_B(I_Array_record[1])) * 10), 3);
        DectoBCD(&Buf_temp[22], ((cur_handle_C(I_Array_record[2])) * 10), 3);
        MODIFY_EEP_W((Addr_event_trip + 25 * point_event_trip_24C256), Buf_temp, 25, 0xA0);
        point_event_trip_24C256 = point_event_trip_24C256 + 1;
        if (point_event_trip_24C256 >= 10)
        {
            point_event_trip_24C256 = 0x00;
        }
        E2_temp[0] = point_event_trip_24C256;
        MODIFY_EEP_W(Addr_point_event_trip_24C256, E2_temp, 1, 0xA0);
    }
}

// 外部中断0服务程序
// void EXTI0_IRQHandler(void)
//{
////	delay_ms(1);//消抖
//	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位
//	if(F_Vsam_begin==1)
//	{
////		Adc_Init();
////	  V_Array[0]=Get_Adc(ADC_Channel_7);
//		if(vol_handle_A(V_Array[0])>=79)
//		{
//			T = 0;
//			Leak_Cur_Sum=0;
//			A_C_Sum=0;
//			B_C_Sum=0;
//			C_C_Sum=0;
//			F_qingling=0;
//		}
//		else
//		{
//			F_qingling=1;
//		}
//	}
//	F_Sample = 1;
//	N_Tingdian = 0;
//}

void Flag_Updata(void)
{
    //	if((T==7)&&(T_64_2min==1500))
    //		{
    ////			F_sssj = 0;
    //			F_initial_lcd=1;
    //		}
    if ((T == 7) && (T_64_1min == 2999))
    {
        F_sssj = 0;
        //			F_initial_lcd=1;
    }
    if ((T == 7) && (T_64_6 == 20)) // 一个简单的上电延时
    {
        F_Delay = 1;
        F_L_Delay = 1;
    }

    //	if((T==9)&&(T_64_2min==2999))
    //		{
    //			F_sssj = 0;
    //		}
    /************ 显示更新*************/
    // 每隔1000ms更新一次显示
    if ((T == 16) && (T_64_25 == 50))
    {
        F_Disp = 1;
    }
    /************ 键值判断并处理*************/
    // 每隔40ms判断一次按键
    if ((T == 8) && (T_64_1 == 1))
    {
        F_Buttom = 1;
        //		F_initial_lcd=1;
    }
    /************ 电流采样及判断*************/

    if ((T == 35) && (T_64_4 == 4))
    {
        F_Vol = 10;
    }
    if ((T == 35) && (T_64_4_Re == 200)) // 2020/11/5
    {
        F_Vol_Re = 10;
    }
    if ((T == 39) && (T_64_500ms == 100))
    {
        F_Vsam_begin = 1;
    }
    if ((T == 40) && (T_64_200ms == 200) && (isfenzha != 0))
    {
        F_Leak_Delay = 1;
        F_Leak_Delay1++;
    }
    /************ 自适应调整标志*************/
    // 6000))//每隔120进行自适应档位调整
    if ((T == 4) && (T_64_2m == 60))
    {
        F_Compare = 1;
    }
    /************ 10s 无按键*************修改为6s*/
    // 每隔10s无按键处理
    if ((T == 5) && (T_64_10s == 1000)) // 之前250（和10s按键漏电告警有关系）   无按键返回主菜单调试暂时关闭
    {
#if debug

#else
        F_nokey = 1;
#endif
    }
    /************漏电脱扣后20s合闸*********/
    if ((T == 6) && (T_64_xs == N_Trip_Array[N_Trip]))
    {
        // putchar(0xDD);
        // putchar(N_Trip);
        F_Trip = 2;

        T_64_xs = 0;
        F_L_hezha = 1;
    }
    /**********漏电重合闸后6s无异常,取消死锁****/
    // 重合闸后6s无异常取消触发标志
    if ((T == 7) && (T_64_6s == 300)) //
    {
        F_Trip = 0;
        F_Trip1 = 0;
        N_Trip = 0;
        T_64_6s = 0;
    }
    // 20s 合闸
    if ((T == 9) && (T_64_31s == 1000))
    {
        F_I_STA = 2;
        T_64_31s = 0;
        F_I_hezha = 1;
    }

    if ((T == 10) && (T_64_11s == 45000))
    {
        T_64_11s = 0;
        F_I_STA = 0;
    }
    if ((T == 12) && (T_leak_record == Num_leak_record))
    {
        T_leak_record = 0;
        F_leak_record = 1;
    }
    if ((T == 13) && (T_day_updata == 250)) // 5min 15000  调试改为1min 3000 修改为5s检测一次 50
    {
        T_day_updata = 0;
        F_day_updata = 1;
    }
    if ((T == 14) && (T_run_time == 3000))
    {
        T_run_time = 0;
        F_run_time = 1;
    }

    if ((T == 15) && (T_yc_fenzha_js == T_yc_fenzha) && (F_fenzha_js == 1))
    {
        F_fenzha_js = 0;
        T_yc_fenzha_js = 0;
        if (isfenzha != 0)
        {
            F_yc_fenzha = 1;
        }
    }
    if ((T == 16) && (T_yc_hezha_js == T_yc_hezha) && (F_hezha_js == 1))
    {
        F_hezha_js = 0;
        T_yc_hezha_js = 0;
        if (isfenzha == 0)
        {
            F_yc_hezha = 1;
        }
    }
    if ((T == 17) && (T_an_fenzha_js == T_an_fenzha) && (F_an_js == 1))
    {
        F_an_js = 0;
        T_an_fenzha_js = 0;
        F_an_fenzha = 1;
    }

    if ((T == 18) && (T_set_state == 500))
    {
        F_set_state = 0;
        F_trip_ld = 0;
        F_clear_al = 1;
    }
    if ((T == 19) && (T_time_trip == 750)) // 15s检测是否定时试跳
    {
        F_time_trip = 1;
    }
    //		if((T==20)&&(T_64_100ms==200)) //15s检测是否定时试跳
    //	{
    //		F_hezha_set = 1;
    //	}
}

void Conter_Updata(void)
{
    if (F_hezha_state == 1)
    {
        N_hezha_time++;
        if (N_hezha_time >= 6000) // 超时合闸失败，停止
        {
            stop;
            F_disp_jg = 0x55;
            N_hezha_time = 0;
            F_hezha_state = 0;
        }
    }
    if (F_hezha_delay == 1)
    {
        T_64_hezha_delay = T_64_hezha_delay + 1;
        if (T_64_hezha_delay >= 50 * hezha_delay)
        {
            // put2char(0x33);
            stop;
            T_64_hezha_delay = 0;
            F_hezha_delay = 0;
            F_initial_lcd = 1;
        }
    }
    if (F_fenzha_state == 1) // 超时分闸失败，停止
    {
        N_fenzha_time++;
        if (N_fenzha_time >= 6000)
        {
            stop;
            F_disp_tr = 1;
            N_fenzha_time = 0;
            F_fenzha_state = 0;

            fenzha_chenggong = 0x00;
            Write_Selftest_Record(0x0E);
        }
    }
    if (F_display == 0)
    {
        N_display_time++;
        if (N_display_time >= 30000)
        {
            F_display = 1;
            N_display_time = 0;
        }
    }
    if (F_display == 1) // 每隔30*2*5*2秒刷屏mrnow
    {
        clear_screen();
        initial_lcd();
        F_display = 0;
    }
    if ((F_sssj == 0) || (F_key == 1))
    {
        T_64_1min = T_64_1min + 1; // 20MS一次  20*150=300MS 太短
        if (T_64_1min >= 3000)
            T_64_1min = 0;
    }
    T_64_2min = T_64_2min + 1; // 20MS一次  20*150=300MS 太短
    if (T_64_2min >= 1501)
        T_64_2min = 0;
    if (F_sssj == 0)
    {
        T_sssj_N = T_sssj_N + 1;
        if (T_sssj_N >= 150)
        {
            T_sssj_N = 0;
            sssj_N_xunhuan++;
            //			F_initial_lcd=0;
            if (sssj_N_xunhuan > 2) // 循环两屏
            {
                sssj_N_xunhuan = 1;
            }
        }
    }
    if (F_Vsam_begin == 0)
    {
        T_64_500ms = T_64_500ms + 1;
        if (T_64_500ms >= 101)
        {
            T_64_500ms = 0;
        }
    }
    if ((F_Leak_Delay == 0) && (isfenzha != 0))
    {
        T_64_200ms = T_64_200ms + 1;
        if (T_64_200ms >= 201)
        {
            T_64_200ms = 0;
        }
    }
    //	if(F_shangdian_hezha==1)
    //	{
    //	T_64_100ms=T_64_100ms+1;
    //		if(T_64_100ms>=201) {T_64_100ms = 0;}
    //	}
    T_64_6 = T_64_6 + 1;
    if (T_64_6 == 30)
        T_64_6 = 0;

    T_64_1 = T_64_1 + 1;
    if (T_64_1 == 2)
        T_64_1 = 0;

    T_64_2 = T_64_2 + 1;
    if (T_64_2 == 3)
        T_64_2 = 0;

    T_64_3 = T_64_3 + 1;
    if (T_64_3 == 4)
        T_64_3 = 0;

    T_64_4 = T_64_4 + 1;
    if (T_64_4 >= 5)
        T_64_4 = 0; // 5T_64_4_Re

    T_64_4_Re = T_64_4_Re + 1;
    if (T_64_4_Re >= 201)
        T_64_4_Re = 0;

    T_64_25 = T_64_25 + 1;
    if (T_64_25 == 51)
        T_64_25 = 0; // 1000ms

    if (T_64_15m == 45001)
        T_64_15m = 0;
    if (F_Updata == 0)
        T_64_20m = T_64_20m + 1;

    if (T_64_20m == 4001)
        T_64_20m = 0;
    T_64_2m = T_64_2m + 1;
    if (T_64_2m == 61)
        T_64_2m = 0;

    if (F_key != 0)
        T_64_10s = T_64_10s + 1;
    if (F_Trip == 1)
    {
        T_64_xs = T_64_xs + 1;
    }
    if (T_64_xs == N_Trip_Array[N_Trip] + 1)
        T_64_xs = 0;

    if ((F_Trip == 2) && (F_ZW == 1))
        T_64_6s = T_64_6s + 1;
    if (T_64_6s == 301)
        T_64_6s = 0;

    //		if(F_key==1)  T_64_6s=T_64_6s+1 ;
    //	  if(T_64_6s>=301)T_64_6s=0 ;

    if ((F_I_STA == 1) && (isfenzha == 0))
    {
        T_64_31s = T_64_31s + 1;
        if (T_64_31s >= 1501)
            T_64_31s = 0;
    }

    if ((F_I_STA == 2) && (isfenzha != 0))
    {
        T_64_11s = T_64_11s + 1;
        if (T_64_11s == 45001)
            T_64_11s = 0;
    }

    T_leak_record = T_leak_record + 1;
    T_day_updata = T_day_updata + 1;
    T_run_time = T_run_time + 1;

    if (F_fenzha_js == 1)
        T_yc_fenzha_js = T_yc_fenzha_js + 1;
    if (F_hezha_js == 1)
        T_yc_hezha_js = T_yc_hezha_js + 1;
    if (F_an_js == 1)
        T_an_fenzha_js = T_an_fenzha_js + 1;
    if (F_set_state == 1)
        T_set_state = T_set_state + 1;
    if (F_time_compare == 1)
        T_time_trip = T_time_trip + 1;
    if (F_gz_clear == 1)
    {
        if (isfenzha != 0)
        {
            F_gz_clear = 0;
            F_gz = 0x00;
        }
    }
    //			if(F_hezha_sta==1)
    //		{
    //			if(isfenzha!=0)
    //			{
    //
    //				stop ;
    //				hezha_num = 0;
    //				ci_shu = 0;
    //				F_ZW=1 ;
    //				F_gz=0x00 ;
    //				F_gz_disp = 0x0F;
    //				//F_disp_jg=0 ;
    //				//机构故障标志清零
    //				//status=isfenzha ;
    //				F_disp_h=0 ;
    //				F_Dataval=0 ;
    //				F_guocheng = 0;
    //				F_hezha_sta = 0;
    //				F_Disp=1 ;
    //				back_button();
    //			}
    //		}
    T_delay = T_delay + 1;
    if (T_delay >= 200)
        T_delay = 200;
}

void Nomal_Process(void)
{

    IWDG_Feed();
    if (isfenzha != 0)
    {
        if (F_disp_jg != 0)
        {
            F_disp_jg = 0x00;
        }
    }
    if (F_trip_ld)
    {
        if (F_al1)
        {
            if (LouD_GaoJing < 10)
            {
                clear_screen();
                Lcd12864_Write12CnCHAR(0, 32, 0, "漏电告警");
                LouD_GaoJing++;
            }
        }
        else
            LouD_GaoJing = 0;
    }
    if (F_nokey == 1)
    {
        F_nokey = 0;
        F_key = 0;
        T_64_10s = 0;
        F_queren = 1;
    }
    if ((F_Disp == 1) && ((F_key == 0) || (F_key == 9)))
    {
        IWDG_Feed();
        F_Disp = 0;
        if (Leak_Cur_disp <= 15)
            Leak_Cur_disp = 0;
        L_Cur = Leak_Cur_disp;
        nomal_disp();

        if ((vol_handle_A(V_Array[0]) >= 550) || (vol_handle_B(V_Array[1]) >= 550) || (vol_handle_C(V_Array[2]) >= 550) || (vol_handle_A(V_Array[0]) <= 10) || (vol_handle_B(V_Array[1]) <= 10) || (vol_handle_C(V_Array[2]) <= 10))
        {

            vol_abnormal_check(); // 解决电压校准后丢失问题，感觉有问题
        }
    }

    if (F_Buttom == 1)
    {
        F_Buttom = 0;
        short_process();
        long_process();
    }

    if (F_gz_disp != 0x0F)
    {
        // key_state=0x0000 ;
        // F_key=0 ;
    }
}

void Power_Process(void)
{
    //	printf("A=%d    B=%d    C=%d\r\n",Phase_Differ[0],Phase_Differ[1],Phase_Differ[2]);
    //	printf("*************************************\r\n");
    if ((Power_A_Value >= 8) && (Power_B_Value >= 8) && (Power_C_Value >= 8))
    {
        if (Samp_start_end_flag == 1) // 64点采集标志位置位1，采样结束，开始过零点判断
        {
            /*************************电流波形毛刺滤波20210808***********************/
            for (int Poin_k = 0; Poin_k < 69; Poin_k++)
            {
                if (Zhou_bo_IA[Poin_k + 1] > 2 * Zhou_bo_IA[Poin_k]) // A电流
                {
                    if (Zhou_bo_IA[Poin_k] == 0)
                    {
                        Zhou_bo_IA[Poin_k + 1] = Zhou_bo_IA[Poin_k + 1];
                    }
                    else
                    {
                        Zhou_bo_IA[Poin_k + 1] = Zhou_bo_IA[Poin_k];
                    }
                }
                else
                {
                    Zhou_bo_IA[Poin_k + 1] = Zhou_bo_IA[Poin_k + 1];
                }
                if (Zhou_bo_IB[Poin_k + 1] > 2 * Zhou_bo_IB[Poin_k]) // B电流
                {
                    if (Zhou_bo_IB[Poin_k] == 0)
                    {
                        Zhou_bo_IB[Poin_k + 1] = Zhou_bo_IB[Poin_k + 1];
                    }
                    else
                    {
                        Zhou_bo_IB[Poin_k + 1] = Zhou_bo_IB[Poin_k];
                    }
                }
                else
                {
                    Zhou_bo_IB[Poin_k + 1] = Zhou_bo_IB[Poin_k + 1];
                }
                if (Zhou_bo_IC[Poin_k + 1] > 2 * Zhou_bo_IC[Poin_k]) // C电流
                {
                    if (Zhou_bo_IC[Poin_k] == 0)
                    {
                        Zhou_bo_IC[Poin_k + 1] = Zhou_bo_IC[Poin_k + 1];
                    }
                    else
                    {
                        Zhou_bo_IC[Poin_k + 1] = Zhou_bo_IC[Poin_k];
                    }
                }
                else
                {
                    Zhou_bo_IC[Poin_k + 1] = Zhou_bo_IC[Poin_k + 1];
                }
            }
            /********************************************************************/
            for (Point_i = 0; Point_i < 70; Point_i++) // 200
            {
                if (Point_i <= 63)
                {
                    // 第二步  找电压过零点
                    if ((Zhou_bo_UA[Point_i] <= 0) && (Zhou_bo_UA[Point_i + 1] >= 0) && (Cross_Zero_A[0] == 0))
                    {
                        Re_dot_U[0] = Point_i + 1; // A电压零点
                        if (Point_i < 63)
                            Cross_Zero_A[0] = 1; // 检测到过零点置位70
                        else
                        {
                            Cross_Zero_A[0] = 0; // 检测到过零点置0,继续判断过零点
                        }
                    }
                    if ((Zhou_bo_UB[Point_i] <= 0) && (Zhou_bo_UB[Point_i + 1] >= 0) && (Cross_Zero_B[0] == 0))
                    {
                        Re_dot_U[1] = Point_i + 1; // B电压零点
                        if (Point_i < 63)
                            Cross_Zero_B[0] = 1; // 检测到过零点置位
                        else
                        {
                            Cross_Zero_B[0] = 0; // 检测到过零点置0,继续判断过零点
                        }
                    }
                    if ((Zhou_bo_UC[Point_i] <= 0) && (Zhou_bo_UC[Point_i + 1] >= 0) && (Cross_Zero_C[0] == 0))
                    {
                        Re_dot_U[2] = Point_i + 1; // C电压零点
                        if (Point_i < 63)
                            Cross_Zero_C[0] = 1; // 检测到过零点置位
                        else
                        {
                            Cross_Zero_C[0] = 0; // 检测到过零点置0,继续判断过零点
                        }
                    }

                    /*************************第三步 电流过零点寻找*********************/
                    if ((Zhou_bo_IA[Point_i] > Zhou_bo_IA[Point_i + 1]) && (Zhou_bo_IA[Point_i + 1] > Zhou_bo_IA[Point_i + 2]) && (Zhou_bo_IA[Point_i + 2] < Zhou_bo_IA[Point_i + 3]) && (Zhou_bo_IA[Point_i + 3] < Zhou_bo_IA[Point_i + 4]) && (Cross_Zero_A[1] == 0))
                    {
                        if (Zhou_bo_IA[Point_i + 2] < 20)
                        {
                            Re_dot_I[0] = Point_i + 2;
                            Cross_Zero_A[1] = 1;
                        }
                        else
                        {
                            Cross_Zero_A[1] = 0;
                        }
                    }
                    if ((Zhou_bo_IB[Point_i] > Zhou_bo_IB[Point_i + 1]) && (Zhou_bo_IB[Point_i + 1] > Zhou_bo_IB[Point_i + 2]) && (Zhou_bo_IB[Point_i + 2] < Zhou_bo_IB[Point_i + 3]) && (Zhou_bo_IB[Point_i + 3] < Zhou_bo_IB[Point_i + 4]) && (Cross_Zero_B[1] == 0))
                    {
                        if (Zhou_bo_IB[Point_i + 2] < 20)
                        {
                            Re_dot_I[1] = Point_i + 2;
                            Cross_Zero_B[1] = 1;
                        }
                        else
                        {
                            Cross_Zero_B[1] = 0;
                        }
                    }
                    if ((Zhou_bo_IC[Point_i] > Zhou_bo_IC[Point_i + 1]) && (Zhou_bo_IC[Point_i + 1] > Zhou_bo_IC[Point_i + 2]) && (Zhou_bo_IC[Point_i + 2] < Zhou_bo_IC[Point_i + 3]) && (Zhou_bo_IC[Point_i + 3] < Zhou_bo_IC[Point_i + 4]) && (Cross_Zero_C[1] == 0))
                    {
                        if (Zhou_bo_IC[Point_i + 2] < 20)
                        {
                            Re_dot_I[2] = Point_i + 2;
                            Cross_Zero_C[1] = 1;
                        }
                        else
                        {
                            Cross_Zero_C[1] = 0;
                        }
                    }
                }
            }

            /*	***********************第四步 电流电压相位差*************/
            if ((Cross_Zero_A[0] == 1) && (Cross_Zero_B[0] == 1) && (Cross_Zero_C[0] == 1) && (Cross_Zero_A[1] == 1) && (Cross_Zero_B[1] == 1) && (Cross_Zero_C[1] == 1))
            {
                for (int PH = 0; PH < 3; PH++)
                {
                    Phase_Differ[PH] = Re_dot_U[PH] - Re_dot_I[PH] - 5; // 电压电流相差点数 /-5
                    if (Phase_Differ[PH] < 0)
                        Phase_Differ[PH] = -Phase_Differ[PH];
                    else
                        Phase_Differ[PH] = Phase_Differ[PH];
                    if (Phase_Differ[PH] <= 16) // 16
                    {
                        Phase_Differ[PH] = Phase_Differ[PH];
                        Cross_Zero[PH] = 1;
                    }
                    else
                    {
                        Cross_Zero[PH] = 0;
                        Phase_Differ[PH] = 0;
                    }
                }
                // 第五步 通过相位差点数，查表转换余弦值（功率因子）Power_factor[PH]=
                // 余弦值*1000 ：1000  995   981   957   924    882   831   773  707   634   556    471   383   290   195    98    0
                // 相差点数      0    1     2     3     4      5     6     7    8     9     10    11    12    13    14    15    16
                // 相差角度      0  5.625/11.25/16.875/22.5/28.125/33.75/39.375/45/50.625/56.25/61.875/67.5/73.125/78.75/84.375/90
                if ((Cross_Zero[0] == 1) && (Cross_Zero[1] == 1) && (Cross_Zero[2] == 1))
                {
                    //					HAL_UART_Transmit(&huart1,(uint8_t*)UART_S_Bu1f,4,0xffff);

                    Phase_Differ_buffer[0] += Phase_Differ[0];
                    Phase_Differ_buffer[1] += Phase_Differ[1];
                    Phase_Differ_buffer[2] += Phase_Differ[2];

                    Phase_Differ_A[Fun_Power] = Phase_Differ[0]; // 实现16次相差赋值，为去掉异常点作比较提供数据
                    Phase_Differ_B[Fun_Power] = Phase_Differ[1]; // 20210815去异常点
                    Phase_Differ_C[Fun_Power] = Phase_Differ[2];

                    Fun_Power++;
                    //					printf("A=%d B=%d C=%d\r\n",Phase_Differ[0],Phase_Differ[1],Phase_Differ[2]);
                    if (Fun_Power == 4) // 16
                    {
                        //						printf("*************************************\r\n");
                        Fun_Power = 0;
                        Phase_Differ_average[0] = ((Phase_Differ_buffer[0] / 4)) * 10; // 16周波取平均值
                        Phase_Differ_average[1] = ((Phase_Differ_buffer[1] / 4)) * 10;
                        Phase_Differ_average[2] = ((Phase_Differ_buffer[2] / 4)) * 10;

                        //						printf("AV1=%d   BV1=%d   CV1=%d\r\n",Phase_Differ_average[0],Phase_Differ_average[1],Phase_Differ_average[2]);

                        /**********************平均值与16点作比较去异常点****************/
                        for (int YiChang = 0; YiChang < 4; YiChang++) // 16  20210824修改
                        {
                            Phase_Differ_A_one[YiChang] = Phase_Differ_average[0] - Phase_Differ_A[YiChang] * 10;
                            Phase_Differ_B_one[YiChang] = Phase_Differ_average[1] - Phase_Differ_B[YiChang] * 10;
                            Phase_Differ_C_one[YiChang] = Phase_Differ_average[2] - Phase_Differ_C[YiChang] * 10;
                            /********************************************************************/
                            if ((Phase_Differ_A_one[YiChang] < -20) || (Phase_Differ_A_one[YiChang] > 20)) // A相
                            {
                                Phase_Differ_A_one[YiChang] = 0;
                                Phase_Differ_A[YiChang] = 0;
                            }
                            else
                            {
                                Phase_Differ_A_Two += Phase_Differ_A[YiChang];
                                Phase_Differ_A[YiChang] = 0;
                                Phase_Differ_A_one[YiChang] = 0;
                                YiChang_A_Flag++;
                            }
                            /**************************************************************************/
                            if ((Phase_Differ_B_one[YiChang] < -20) || (Phase_Differ_B_one[YiChang] > 20)) // B相
                            {
                                Phase_Differ_B_one[YiChang] = 0;
                                Phase_Differ_B[YiChang] = 0;
                            }
                            else
                            {
                                Phase_Differ_B_Two += Phase_Differ_B[YiChang];
                                Phase_Differ_B[YiChang] = 0;
                                Phase_Differ_B_one[YiChang] = 0;
                                YiChang_B_Flag++;
                            }
                            /**************************************************************************/
                            if ((Phase_Differ_C_one[YiChang] < -20) || (Phase_Differ_C_one[YiChang] > 20)) // C相
                            {
                                Phase_Differ_C_one[YiChang] = 0;
                                Phase_Differ_C[YiChang] = 0;
                            }
                            else
                            {
                                Phase_Differ_C_Two += Phase_Differ_C[YiChang];
                                Phase_Differ_C[YiChang] = 0;
                                Phase_Differ_C_one[YiChang] = 0;
                                YiChang_C_Flag++;
                            }
                        }
                        /******************求去除异常点的平均值*******************/
                        Phase_Differ_A_Two_Av = (Phase_Differ_A_Two / YiChang_A_Flag) * 10 + 5;
                        Phase_Differ_B_Two_Av = (Phase_Differ_B_Two / YiChang_B_Flag) * 10 + 5;
                        Phase_Differ_C_Two_Av = (Phase_Differ_C_Two / YiChang_C_Flag) * 10 + 5;

                        //						printf("av2=%d   bv2=%d   cv2=%d\r\n",Phase_Differ_A_Two_Av,Phase_Differ_B_Two_Av,Phase_Differ_C_Two_Av);
                        //						printf("*************************************\r\n");

                        Phase_Differ_A_Two = 0;
                        Phase_Differ_B_Two = 0;
                        Phase_Differ_C_Two = 0;

                        YiChang_A_Flag = 0;
                        YiChang_B_Flag = 0;
                        YiChang_C_Flag = 0;

                        //						Phase_Differ_average[0]=((Phase_Differ_buffer[0]/16))*10-(Power_Add[0]);
                        //						Phase_Differ_average[1]=((Phase_Differ_buffer[1]/16))*10-(Power_Add[1]);
                        //						Phase_Differ_average[2]=((Phase_Differ_buffer[2]/16))*10-(Power_Add[2]);

                        Power_factor[0] = Power_pool[Phase_Differ_A_Two_Av];
                        Power_factor[1] = Power_pool[Phase_Differ_B_Two_Av];
                        Power_factor[2] = Power_pool[Phase_Differ_C_Two_Av];
                        //						Power_factor[0]=Power_pool[Phase_Differ_average[0]];
                        //						Power_factor[1]=Power_pool[Phase_Differ_average[1]];
                        //						Power_factor[2]=Power_pool[Phase_Differ_average[2]];

                        Phase_Differ_buffer[0] = 0;
                        Phase_Differ_buffer[1] = 0;
                        Phase_Differ_buffer[2] = 0;
                    }
                    //					Power_factor_test[0]+=Power_factor[0];//测试计量20210807
                    //					Power_factor_test[1]+=Power_factor[1];
                    //					Power_factor_test[2]+=Power_factor[2];

                    //						Power_factor_testA[Fun_Power_test]=Power_factor[0];
                    //						Power_factor_testB[Fun_Power_test]=Power_factor[1];
                    //						Power_factor_testC[Fun_Power_test]=Power_factor[2];

                    //					Fun_Power_test++;
                    //					if(Fun_Power_test==1)//4
                    //					{
                    //						Fun_Power_test=0;

                    //						Power_factor_test_Ave[0]=(Power_factor_testA[0]+Power_factor_testA[1]+Power_factor_testA[2]+Power_factor_testA[3]);
                    //						Power_factor_test_Ave[1]=(Power_factor_testB[0]+Power_factor_testB[1]+Power_factor_testB[2]+Power_factor_testB[3]);
                    //						Power_factor_test_Ave[2]=(Power_factor_testC[0]+Power_factor_testC[1]+Power_factor_testC[2]+Power_factor_testC[3]);
                    //
                    //					}
                }
            }
            Cross_Zero[0] = 0;
            Cross_Zero[1] = 0;
            Cross_Zero[2] = 0;

            Cross_Zero_A[0] = 0;
            Cross_Zero_B[0] = 0;
            Cross_Zero_C[0] = 0;

            Cross_Zero_A[1] = 0;
            Cross_Zero_B[1] = 0;
            Cross_Zero_C[1] = 0;

            Re_dot_I[0] = 0;
            Re_dot_I[1] = 0;
            Re_dot_I[2] = 0;

            Re_dot_U[0] = 0;
            Re_dot_U[1] = 0;
            Re_dot_U[2] = 0;

            Phase_Differ[0] = 0;
            Phase_Differ[1] = 0;
            Phase_Differ[2] = 0;
        }
        Samp_start_end_flag = 0; // 200采样点标志位置零，开始采样
    }
    else
    {
        Power_factor[0] = 0;
        Power_factor[1] = 0;
        Power_factor[2] = 0;

        //		Power_factor_test_Ave[0]=0;
        //		Power_factor_test_Ave[1]=0;
        //		Power_factor_test_Ave[2]=0;
    }
}

void short_process(void)
{
    unsigned char tmp;
    IWDG_Feed();
    tmp = Read_key();
    //	F_sssj=1;
    if (tmp != 0)
    {
        key_process(tmp);

        if (F_key == 2)
        {

            Fun_Record_CX();
        }
        if (F_key == 3)
        {

            if (key_state == 0x42100)
                Trip_Num_LOCK();
            if (key_state == 0x42101)
                Trip_Num_LD();
            if (key_state == 0x42102)
                Trip_Num_DY();
            //			if (key_state==0x42103)
            //		   Trip_Num_TEST();
            //			if (key_state==0x42104)
            //		   Trip_Num_Instant();
            //			if (key_state==0x42105)
            //		   Trip_Num_Check();
        }

        if (F_key == 4)
        {
            Fun_Shiyan_CX();
        }

        if (F_key == 5)
        {
            if (D_LCur == 8)
            {
                F_auto_ld = 1;
            }
            else
            {
                F_auto_ld = 0;
            }
            if (key_state == 0x11100)
                Fun_GJ(); // 漏电告警
            if (key_state == 0x11101)
                Fun_auto_LD(); // 自动档位
            if (key_state == 0x11102)
                Fun_SC(); // 突变保护
            if (key_state == 0x11103)
                Fun_SW(); // 特波保护
            if (key_state == 0x11104)
                Fun_DZ();
            // Fun_SD_hezha();          //上电合闸
            if (key_state == 0x11105)
                Fun_GY(); // 过压保护
            if (key_state == 0x11106)
                Fun_QY(); // 欠压保护
            if (key_state == 0x11107)
                Fun_QX(); // 缺相保护
            if (key_state == 0x11108)
                Fun_SY(); // 失压保护
            if (key_state == 0x11109)
                Fun_OP(); // 过流保护
            if (key_state == 0x1110A)
                Fun_S_Delay(); // 短延保护
            if (key_state == 0x1110B)
                Fun_Instant(); // 瞬时保护
            //			if (key_state==0x1110C)
            //			 Fun_Corr_Slec();         //校准设置
            //			if (key_state==0x1110D)
            //			 Fun_TD_fenzha();         //停电跳闸
            //			if (key_state==0x1110E)
            //			 Fun_DZ();                //断零保护
            if (key_state == 0x1110C)
                Fun_SD_hezha();
            if (key_state == 0x1110D)
                Fun_LD_hezha();
            if (key_state == 0x1110E)
                Fun_DY_hezha();
            if (key_state == 0x1110F)
                Fun_DL_hezha();
            //					if (key_state==0x1110E)
            //				 Fun_LD_hezha();
            //					if (key_state==0x1110F)
            //				 Fun_DY_hezha();
            //					if (key_state==0x11110)
            //				 Fun_DL_hezha();
            //				if (key_state==0x1110D)
            //				// Fun_DZ();
            //				Fun_SD_hezha();
            //				////2023-10-16 zzz
            //					if (key_state==0x1110E)
            //				 Fun_LD_hezha();
            //					if (key_state==0x1110F)
            //				 Fun_DY_hezha();
            //					if (key_state==0x11110)
            //				 Fun_DL_hezha();
        }

        if (F_key == 6)
        {
            clear_screen();
            mima_input();
        }

        if (F_key == 7)
        {

            if ((key_state >= 0x21100) && (key_state <= 0x211FF))
                Fun_FZ();
            if ((key_state >= 0x22100) && (key_state <= 0x221FF))
                Fun_YS();
            if ((key_state >= 0x23100) && (key_state <= 0x231FF))
                Fun_GY_Val();
            if ((key_state >= 0x24100) && (key_state <= 0x241FF))
                Fun_QY_Val();
            if ((key_state >= 0x3D100) && (key_state <= 0x3D1FF))
                Fun_ST(); // 失压时间 设置
            if ((key_state >= 0x3E100) && (key_state <= 0x3E1FF))
                Fun_GT(); // 过压时间 设置
            if ((key_state >= 0x3F100) && (key_state <= 0x3F1FF))
                Fun_QT(); // 欠压时间 设置
            if ((key_state >= 0x40100) && (key_state <= 0x401FF))
                Fun_Instant_Val(); // 电流瞬时保护档位 设置
            if ((key_state >= 0x25100) && (key_state <= 0x25FFF))
                Fun_OP_Val(); // 过流档位
            if ((key_state >= 0x26100) && (key_state <= 0x261FF))
                Fun_OP_T(); // 过流时间
            if ((key_state >= 0x27100) && (key_state <= 0x271FF))
                Fun_Delay_Val(); // 短延档位
            if ((key_state >= 0x28100) && (key_state <= 0x281FF))
                Fun_Delay_T(); // 短延时间
            if ((key_state >= 0x29100) && (key_state <= 0x291FF))
                Fun_Com_S(); // 通信速率
            if ((key_state >= 0x2A100) && (key_state <= 0x2A1FF))
                Fun_Type_Cur(); // 壳架设置
            if ((key_state >= 0x2B100) && (key_state <= 0x2B1FF))
                Fun_Time_Y(); // 时间 年 设置
            if ((key_state >= 0x2C100) && (key_state <= 0x2C1FF))
                Fun_Time_M(); // 时间 月 设置
            if ((key_state >= 0x2D101) && (key_state <= 0x2D1FF))
                Fun_Time_D(); // 时间 日 设置
            if ((key_state >= 0x2E100) && (key_state <= 0x2E1FF))
                Fun_Time_H(); // 时间 时 设置
            if ((key_state >= 0x2F100) && (key_state <= 0x2F1FF))
                Fun_Time_F(); // 时间 分 设置
            if ((key_state >= 0x30100) && (key_state <= 0x301FF))
                Fun_Time_S(); // 时间 秒 设置
            if ((key_state >= 0x31100) && (key_state <= 0x311FF))
                Fun_Com_D_1(); // 地址 第1位 设置
            if ((key_state >= 0x32100) && (key_state <= 0x321FF))
                Fun_Com_D_2(); // 地址 第2位 设置
            if ((key_state >= 0x33100) && (key_state <= 0x331FF))
                Fun_Com_D_3(); // 地址 第3位 设置
            if ((key_state >= 0x34100) && (key_state <= 0x341FF))
                Fun_Com_D_4(); // 地址 第4位 设置
            if ((key_state >= 0x35100) && (key_state <= 0x351FF))
                Fun_Com_D_5(); // 地址 第5位 设置
            if ((key_state >= 0x36100) && (key_state <= 0x361FF))
                Fun_Com_D_6(); // 地址 第6位 设置
            if ((key_state >= 0x37100) && (key_state <= 0x371FF))
                Fun_Com_D_7(); // 地址 第7位 设置
            if ((key_state >= 0x38100) && (key_state <= 0x381FF))
                Fun_Com_D_8(); // 地址 第8位 设置
            if ((key_state >= 0x39100) && (key_state <= 0x391FF))
                Fun_Com_D_9(); // 地址 第9位 设置
            if ((key_state >= 0x3A100) && (key_state <= 0x3A1FF))
                Fun_Com_D_10(); // 地址 第10位 设置
            if ((key_state >= 0x3B100) && (key_state <= 0x3B1FF))
                Fun_Com_D_11(); // 地址 第11位 设置
            if ((key_state >= 0x3C100) && (key_state <= 0x3C1FF))
                Fun_Com_D_12(); // 地址 第12位 设置
            if ((key_state >= 0x50100) && (key_state <= 0x501FF))
                Time_Hezha_delay(); // 温度上限			电机延时
            if ((key_state >= 0x80100) && (key_state <= 0x801FF))
                Fun_External_GateMode();
            if (key_state >= 0x20000000)
            {
                if (key_state == 0x20000000)
                {
                    key_state = (unsigned int)(((key_state >> 12) | (mima[0])) << 12);
                    key_state = (unsigned int)(((key_state >> 8) | (mima[1])) << 8);
                    key_state = (unsigned int)(((key_state >> 4) | (mima[2])) << 4);
                    key_state = (unsigned int)(key_state) | (mima[3]);
                }

                mima_change();
            }
        }

        if (F_key == 8)
        {
            data_clear();
            clear_screen();
            Lcd12864_Write12CnCHAR(0, 16, 2, "数据清零完成");
            HAL_Delay(1000);
            F_key = 0;
        }
    }
}

unsigned char fenzha(void)
{
    if (isfenzha != 0)
    {
        start;
        F_disp_tr = 0;
        F_fenzha_state = 1;
        N_fenzha_time = 0;
        //		F_initial_lcd_hezha=1;
    }
    return 0;
}

/* 合闸程序程序,合闸时间约为120s,停顿时间为10s, 往复3次,
合闸成功返回1,合闸不成功返回0                         */
unsigned char hezha(void)
{
    if (isfenzha == 0)
    {
        start;
        F_hezha_state = 1;
        N_hezha_time = 0;
        //		F_initial_lcd_hezha=1;
    }
    return 0;
}

void V_max_process(unsigned char tmp)
{
    if (tmp >= 4)
        tmp = 1;
    if (V_MAX_tmp[tmp - 1] > V_MAX[tmp - 1])
    {
        V_MAX[tmp - 1] = V_MAX_tmp[tmp - 1];
        Write_V(tmp, V_MAX[tmp - 1], 0);
        Record_V(tmp, V_MAX[tmp - 1], 0);
    }
}

void V_min_process(unsigned char tmp)
{
    if (tmp >= 4)
        tmp = 1;
    if (V_MIN_tmp[tmp - 1] < V_MIN[tmp - 1])
    {
        V_MIN[tmp - 1] = V_MIN_tmp[tmp - 1];
        Write_V(tmp, V_MIN[tmp - 1], 1);
        Record_V(tmp, V_MIN[tmp - 1], 1);
    }
}

void Write_V(unsigned char tmp, unsigned int factor1, unsigned char factor2)
{
    unsigned char day, array_temp_V[15], array_temp_time[10], i, day_tmp;
    unsigned int addr_tmp;

    //	ds1302_read_time_uart(array_temp_time);

    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    array_temp_time[0] = tim_y;

    array_temp_time[1] = tim_m;

    array_temp_time[2] = tim_d;

    array_temp_time[3] = tim_h;

    array_temp_time[4] = tim_f;

    array_temp_time[5] = tim_s;

    day_tmp = array_temp_time[2];
    day = (((day_tmp >> 4) & 0x03) * 10) + (day_tmp & 0x0F);
    day = day - 1;
    if ((day >= 0) && (day < 32))
    {
        if (factor2 == 0)
        {
            if (tmp == 1)
                addr_tmp = Addr_max_Avol + (day << 3);
            else if (tmp == 2)
                addr_tmp = Addr_max_Bvol + (day << 3);
            else if (tmp == 3)
                addr_tmp = Addr_max_Cvol + (day << 3);
            else
                addr_tmp = Addr_max_Avol + (day << 3);
        }
        if (factor2 == 1)
        {
            if (tmp == 1)
                addr_tmp = Addr_min_Avol + (day << 3);
            else if (tmp == 2)
                addr_tmp = Addr_min_Bvol + (day << 3);
            else if (tmp == 3)
                addr_tmp = Addr_min_Cvol + (day << 3);
            else
                addr_tmp = Addr_min_Avol + (day << 3);
        }
        DectoBCD(array_temp_V, (vol_handle(factor1) * 10), 2);
        for (i = 0; i < 6; i++)
        {
            array_temp_V[2 + i] = array_temp_time[5 - i];
        }
        MODIFY_EEP_W(addr_tmp, array_temp_V, 8, 0xA0);
    }
}
void Record_V(unsigned char tmp, unsigned int factor1, unsigned char factor2)
{
    unsigned char array_temp_V[15], i, array_temp_time[10];
    unsigned int addr_tmp;
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);

    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;

    array_temp_time[1] = tim_m;
    array_temp_time[2] = tim_d;
    if (factor2 == 0)
    {
        if (tmp == 1)
            addr_tmp = Addr_max_Avol_TD;
        else if (tmp == 2)
            addr_tmp = Addr_max_Bvol_TD;
        else if (tmp == 3)
            addr_tmp = Addr_max_Cvol_TD;
        else
            addr_tmp = Addr_max_Avol_TD;
    }
    if (factor2 == 1)
    {
        if (tmp == 1)
            addr_tmp = Addr_min_Avol_TD;
        else if (tmp == 2)
            addr_tmp = Addr_min_Bvol_TD;
        else if (tmp == 3)
            addr_tmp = Addr_min_Cvol_TD;
        else
            addr_tmp = Addr_min_Avol_TD;
    }
    DectoBCD(array_temp_V, factor1, 2);
    for (i = 0; i < 2; i++)
    {
        array_temp_V[2 + i] = array_temp_time[2 - i];
    }
    MODIFY_EEP_W(addr_tmp, array_temp_V, 4, 0xA0);
}

void Write_leak(unsigned int factor1, unsigned char factor2)
{
    unsigned char day, array_temp_L[15], array_temp_time[10], i, day_tmp;
    unsigned int addr_tmp;
    //	ds1302_read_time_uart(array_temp_time);
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    array_temp_time[0] = tim_y;

    array_temp_time[1] = tim_m;

    array_temp_time[2] = tim_d;

    array_temp_time[3] = tim_h;

    array_temp_time[4] = tim_f;

    array_temp_time[5] = tim_s;
    day_tmp = array_temp_time[2];
    day = (((day_tmp >> 4) & 0x03) * 10) + (day_tmp & 0x0F);
    day = day - 1;
    if ((day >= 0) && (day < 32))
    {
        if (factor2 == 0)
        {
            addr_tmp = Addr_max_leak + day * 9;
        }
        if (factor2 == 1)
        {
            addr_tmp = Addr_min_leak + day * 9;
        }

        array_temp_L[0] = max_phase;
        DectoBCD(&array_temp_L[1], factor1, 2);
        for (i = 0; i < 6; i++)
        {
            array_temp_L[3 + i] = array_temp_time[5 - i];
        }
        MODIFY_EEP_W(addr_tmp, array_temp_L, 9, 0xA0);
    }
}

void Leak_max_process(void)
{
    if (Leak_MAX_tmp > Leak_MAX + 1)
    {
        Leak_MAX = Leak_MAX_tmp;
        Write_leak(Leak_MAX, 0);
    }
}

void Leak_min_process(void)
{
    if (Leak_MIN_tmp < Leak_MIN)
    {
        Leak_MIN = Leak_MIN_tmp;
        Write_leak(Leak_MIN, 1);
    }
}

void I_max_process(unsigned char tmp)
{
    if (tmp >= 4)
        tmp = 1;
    if (I_MAX_tmp[tmp - 1] > I_MAX[tmp - 1])
    {
        I_MAX[tmp - 1] = I_MAX_tmp[tmp - 1];
        Write_I(tmp, I_MAX[tmp - 1], 0);
    }
}

void I_min_process(unsigned char tmp)
{
    if (tmp >= 4)
        tmp = 1;
    if (I_MIN_tmp[tmp - 1] < I_MIN[tmp - 1])
    {
        I_MIN[tmp - 1] = I_MIN_tmp[tmp - 1];
        Write_I(tmp, I_MIN[tmp - 1], 1);
    }
}

void Write_I(unsigned char tmp, unsigned int factor1, unsigned char factor2)
{
    unsigned char day, array_temp_I[20], array_temp_time[10], i, day_tmp;
    unsigned int addr_tmp;
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
    tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
    tim_m = sdatestructure.Month;
    tim_d = sdatestructure.Date;
    tim_h = stimestructure.Hours;
    tim_f = stimestructure.Minutes;
    tim_s = stimestructure.Seconds;
    array_temp_time[0] = tim_y;

    array_temp_time[1] = tim_m;

    array_temp_time[2] = tim_d;

    array_temp_time[3] = tim_h;

    array_temp_time[4] = tim_f;

    array_temp_time[5] = tim_s;
    day_tmp = array_temp_time[2];
    day = (((day_tmp >> 4) & 0x03) * 10) + (day_tmp & 0x0F);
    day = day - 1;
    if ((day >= 0) && (day < 32))
    {
        if (factor2 == 0)
        {
            if (tmp == 1)
                addr_tmp = Addr_max_Acur + day * 9;
            else if (tmp == 2)
                addr_tmp = Addr_max_Bcur + day * 9;
            else if (tmp == 3)
                addr_tmp = Addr_max_Ccur + day * 9;
            else
                addr_tmp = Addr_max_Acur + (day * 9);
        }
        if (factor2 == 1)
        {
            if (tmp == 1)
                addr_tmp = Addr_min_Acur + (day * 9);
            else if (tmp == 2)
                addr_tmp = Addr_min_Bcur + (day * 9);
            else if (tmp == 3)
                addr_tmp = Addr_min_Ccur + (day * 9);
            else
                addr_tmp = Addr_min_Acur + (day * 9);
        }
        if (tmp == 1)
        {
            DectoBCD(array_temp_I, (cur_handle_A(factor1) * 10), 3); // 此处什么意思？？？？？？
        }
        if (tmp == 2)
        {
            DectoBCD(array_temp_I, (cur_handle_B(factor1) * 10), 3); // 此处什么意思？？？？？？
        }
        if (tmp == 3)
        {
            DectoBCD(array_temp_I, (cur_handle_C(factor1) * 10), 3); // 此处什么意思？？？？？？
        }

        for (i = 0; i < 6; i++)
        {
            array_temp_I[3 + i] = array_temp_time[5 - i];
        }
        MODIFY_EEP_W(addr_tmp, array_temp_I, 9, 0xA0);
        //		delay_ms(5);
        //		  for(int i;i<15;i++)
        //		{
        //			EEPROM_R(addr_tmp,buff_tap,9,0xA0);
        //		  test_shuju[i]=buff_tap[i];
        //		}
    }
}
void hezha_process(void)
{
    IWDG_Feed(); // 喂狗

    // 上电合闸
    if (F_shangdian_hezha == 1)
    {
        // putchar(0xAE);
        if (F_Vsam_begin == 1)
        {
            delay_ms(500);
            //		delay_ms(500);
            //		delay_ms(500);
            //	  delay_ms(500);
            F_sssj = 0;
            if (F_tim_gz == 1)
            {
                F_gz = 0x0B; // 停电故障
            }
            c_hezha();
            F_shangdian_hezha = 0;
            F_Leak_Delay = 0;
        }
    }
    // 缺相合闸
    if ((F_QX_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_qxTrip = 0;
        F_QX_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;

        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_QX_hezha=0 ;
                }
            }
        }
        F_Leak_Delay = 0;
    }
    // 欠压合闸
    if ((F_QY_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_qyTrip = 0;
        F_QY_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_QY_hezha=0 ;
                }
            }
        }
    }
    // 失压合闸
    if ((F_SY_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_syTrip = 0;
        F_SY_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_SY_hezha=0 ;
                }
            }
        }
        F_Leak_Delay = 0;
    }
    // 过压合闸
    if ((F_GY_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_gyTrip = 0;
        F_GY_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_GY_hezha=0 ;
                }
            }
        }
        F_Leak_Delay = 0;
    }
    if ((F_QL_hezha == 1) && (DY_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        //		F_tingdian_fenzha=0;
        F_lzTrip = 0;
        F_QL_hezha = 0;
        F_TB_start = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    hezha();
                    //			  F_QL_hezha=0 ;
                }
            }
        }
        F_Leak_Delay = 0;
    }
    // 远程合闸
    if (F_yc_hezha == 1)
    {
        F_wait_DY_Normal = 0;
        F_yc_fenzha = 0;
        F_yc_hezha = 0;
        // clear_uart_sta();
        F_Dataval = 0;
        F_sssj = 0;
        if (isfenzha == 0)
        {
            delay_ms(5);
            if (isfenzha == 0)
            {
                delay_ms(5);
                if (isfenzha == 0)
                {
                    c_hezha();
                    //			  F_yc_hezha=0 ;
                }
            }
        }
        //		c_hezha();
    }
    // 正常状态,按钮合闸
    if (F_hz == 1)
    {
        F_wait_DY_Normal = 0;
        delay_ms(5);
        if ((F_hz == 1) && (isfenzha == 0))
        {
            //			if(isfenzha==0)
            {
                //				delay_ms(2);
                //				if(isfenzha==0)
                {
                    c_hezha();
                }
            }
            //			c_hezha();
            F_Leak_Delay = 0;
            // hezha();
            F_hz = 0;
        }
    }
    // 漏电处理当中的重合闸
    if ((F_L_hezha == 1) && (LD_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        F_L_hezha = 0;
        if ((isfenzha == 0) && (F_L_Lock == 0))
        {
            F_TB_start = 0;
            F_sssj = 0;
            hezha();
            F_Leak_Delay = 0;
        }
    }
    if (F_wait_DY_Normal == 2)
    {
        delay_ms(5);
        if (isfenzha == 0)
        {
            F_wait_DY_Normal = 0;
            F_tingdian_fenzha = 0;
            c_hezha();
            F_Leak_Delay = 0;
            // hezha();//调试中注意修改回去20150510
            F_hz = 0;
        }
    }
    // 过电流处理当中的重合闸
    if ((F_I_hezha == 1) && (DL_hezha == 1))
    {
        F_wait_DY_Normal = 0;
        // 在分闸且不死锁的情况下重合闸
        F_I_hezha = 0;
        F_sssj = 0;
        // if((isfenzha==0)&&(F_I_Lock==0))
        {
            F_TB_start = 0;
            hezha();
            F_I_hezha = 0;
            T_64_31s = 0;
        }
    }
}
void fenzha_process(void)
{
    //
    //	if(F_tingdian_fenzha==1)
    //	{
    //		F_tingdian_fenzha = 0;
    //		if(isfenzha!=0)
    //		{
    //			Trip_Action();
    //		}
    //	}
    // 手动按键分闸
    IWDG_Feed(); // 喂狗
    if (F_fz == 1)
    {
        delay_ms(5);
        if ((F_fz == 1) && (isfenzha != 0))
        {
            F_ch = 0;
            F_gz_disp = FZ_AJ;
            Record_data_propare();
            Trip_Action();
            fenzha_chenggong = 0x11;
            Write_Selftest_Record(0x0E);
            gz_disp = 0;
            F_record_write = 1;
            gz_reason = trip_reason_key;
            // putchar(gz_reason);
            GZ_ph = 1;
            // Write_Record(trip_reason_lock,1);
            F_STrip = 1;
            // 写按键跳闸记录
            F_fz = 0;
            // 手动分闸死锁标志
        }
    }
    // 预约远程分闸
    if (F_yc_fenzha == 1)
    {
        F_yc_hezha = 0;
        F_yc_fenzha = 0;
        Record_data_propare();
        Trip_Action();
        fenzha_chenggong = 0x11;
        Write_Selftest_Record(0x0D);
        F_gz_disp = FZ_YC;
        // gz_reason = trip_reason_lock;
        gz_reason = trip_reason_remote;
        GZ_ph = 1;
        F_record_write = 1;
        // Write_Record(trip_reason_remote,1);
    }
    // 预约模拟分闸
    if (F_an_fenzha == 1)
    {
        F_analog_trip = 1;
        F_an_fenzha = 0;
        Trip_Process_time(1);
    }
    // 15s定时检测查看是否时间到——定时试跳分闸
    if (F_time_trip == 1)
    {
        unsigned char tim_array[8];
        F_time_trip = 0;
        T_time_trip = 0;
        //		ds1302_read_time_uart(tim_array);
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
        //	tim_y=tim_y%2000;  //time_tmp[0]=17   十进制转换为二进制存入24C64中
        //	tim_array[0]=(tim_y/10)<<4;
        //	tim_array[0]+=(tim_y%10);
        //	tim_array[1]=(tim_m/10)<<4;
        //	tim_array[1]+=(tim_m%10);
        //	tim_array[2]=(tim_d/10)<<4;
        //	tim_array[2]+=(tim_d%10);
        //	tim_array[3]=(tim_h/10)<<4;
        //	tim_array[3]+=(tim_h%10);
        //	tim_array[4]=(tim_f/10)<<4;
        //	tim_array[4]+=(tim_f%10);
        //	tim_array[5]=(tim_s/10)<<4;
        //	tim_array[5]+=(tim_s%10);

        if ((F_timer_triped == 0) && (timed_trip_code[0] == tim_array[4]) && (timed_trip_code[1] == tim_array[3]) && (timed_trip_code[2] == tim_array[2]))
        {
            Trip_Process_time(0);
            F_timer_triped = 1;
        }
        if ((F_timer_triped == 1) && (timed_trip_code[0] != tim_array[4]))
        {
            F_timer_triped = 0;
        }
    }
}

void Trip_Process_time(unsigned char tmp)
{

    // 若开报警,则不脱扣

    // if((F_al_key==1)||(F_al_temp==1)||(F_al_uart==1))
    if (F_trip_ld)
    {
        // F_al1为告警功能相关标志位,有漏时告警灯闪烁（牛峰7.15修改）
        F_al1 = 5;
        // 报警灯闪烁
    }
    else
    {
        // 第一次脱扣
        if (F_Trip == 0)
        {
            Leak_Cur_disp = 989;
            gz_disp = Leak_Cur_disp;
            Record_data_propare();
            Leak_Cur_disp = 989;
            Trip_Action();
            Leak_Cur_disp = 0;
            F_gz_disp = L_hb;
            F_ch = 0;
            //			fenzha_chenggong = 0x11;
            //			Write_Selftest_Record(0x0C);
            if (tmp == 0)
            {
                // Write_Record(trip_reason_timer,1);
                gz_reason = trip_reason_timer;
                GZ_ph = 1;
                F_record_write = 1;
            }
            if (tmp == 1)
            {
                // Write_Record(trip_reason_remote,1);
                gz_reason = trip_reason_remote;
                GZ_ph = 1;
                F_record_write = 1;
            }
            if (F_la == 1)
            {
                F_Trip = 1;
                // 否则不再重合闸
            }
            else
            {
                F_Trip = 3;
                F_ch = 3;
                F_L_Lock = 1;
            }
        }
        // 连续第二次脱扣
        if (F_Trip == 2)
        {
            if (F_la2 == 1)
            {
                gz_disp = Leak_Cur_disp;
                Record_data_propare();
                Trip_Action();
                N_Trip = N_Trip + 1;
                rms_make(N_Trip);

                F_Trip = 1;
                T_64_xs = 0;
                if (N_Trip == 3)
                {
                    F_Trip = 3;
                    F_L_Lock = 1;
                    N_Trip = 0;
                }
            }
            else
            {
                F_Trip = 3;
                F_L_Lock = 1;
                gz_disp = Leak_Cur_disp;
                Record_data_propare();
                Trip_Action();
                rms_make(3);
                F_ch = 3;
            }
        }
    }
}

void rms_make(unsigned char i)
{
    // rms=sqrtf((float)rms_last)*4.242 ;
    // if(rms<0)rms=0 ;
    // L_Cur=((int)(rms));

    F_gz_disp = L_hb;
    F_ch = i;
    if (F_TB_gz == 1)
    {
        F_record_write = 1;
        gz_reason = trip_reason_leak;
        // putchar(gz_reason);
        GZ_ph = 1;
        // Write_Record(trip_reason_leak,GZ_ph);
    }
    else
    {
        // putchar(0xB1);
        F_record_write = 1;
        gz_reason = trip_reason_leak;
        // putchar(gz_reason);
        GZ_ph = 1;
        // Write_Record(trip_reason_leak,1);
    }
    // Write_Record(trip_reason_leak,1);
}

unsigned char Trip_Action(void)
{
    unsigned int ci_shu1;
    // 脱扣时间控制
    //	if(F_anolog_trip == 1)
    //	{
    ////		RELAY1 = 0;
    //		F_anolog_trip = 0;
    //	}
    if (isfenzha != 0) // 合闸状态
    {
        ci_shu1 = 0;
        F_guocheng = 1;
        F_ZW = 0;
        // //Trip_LED_ON ;
        while ((isfenzha != 0) && (ci_shu1 < 100))
        {
            Trip_ON;
            delay_ms(5);
            ci_shu1++;
            IWDG_Feed();
            //			initial_lcd();
        }
        Trip_OFF;
        // //Trip_LED_OFF ;
        F_disp_tr = 0;
        // 脱扣故障标志清零0923
        if (ci_shu1 >= 100)
        {
            fenzha();
            F_guocheng = 0;
        }
        ci_shu1 = 0;
        F_initial_lcd_hezha = 1;
    }
    if (isfenzha == 0)
    {
        F_guocheng = 0;
        return 1;
        // 分闸成功
    }
    if (isfenzha != 0)
    {
        F_disp_tr = 1;
        F_ZW = 1;
        F_guocheng = 0;
        return 0;
        // 警告位D7
        // 分闸失败
    }
    return 0;
}
void c_hezha(void)
{
    // //Trip_LED_OFF ;
    F_sssj = 0;
    //	F_V_Nomal=0 ;
    //	F_VL=0 ;
    //	F_VH=0 ;
    F_anolog_trip = 0;
    F_Leak_Delay = 0;
    delay_ms(5);
    delay_ms(5);
    delay_ms(5);
    delay_ms(5);
    delay_ms(5);
    delay_ms(5);
    V_Sample_C(1);
    V_Sample_C(2);
    V_Sample_C(3);
    delay_ms(5);

    // asm("wdr");
    // 保护全开
    if ((F_trip_qy == 1) && (F_trip_gy == 1)) //&&(F_dianya_chonghe==1)
    {
        // 电压正常
        if (F_V_Nomal == 1)
        {
            hezha();
            clear_flags();
        }
        else
        {
            //			dispbit[0]=0x5e ;
            //			dispbit[1]=0x6e ;
            //			dispbit[2]=0x40 ;
            //			dispbit[3]=0x40 ;
            //			display();
            if (F_shangdian_hezha == 1)
            {
                F_wait_DY_Normal = 1;
            }
            clear_screen();
            Lcd12864_Write12CnCHAR(0, 32, 1, "电压异常");
            Lcd12864_Write12CnCHAR(0, 32, 3, "不可合闸");
            if ((F_shangdian_hezha == 1) && (F_N_shangdian == 0))
            {
                F_shangdian_2 = 1;
                F_N_shangdian = 2;
            }
            delay_ms(1000);
            F_QUIT = 1;
        }
    }
    else if ((F_trip_qy == 1) && (F_trip_gy == 0))
    {
        // 电压不低于门限值
        if (F_VL == 1)
        {
            hezha();
            clear_flags();
        }
        else
        {
            //			if(F_shangdian_hezha==1)
            //			{
            //
            //			}
            if (F_shangdian_hezha == 1)
            {
                F_wait_DY_Normal = 1;
            }
            clear_screen();
            Lcd12864_Write12CnCHAR(0, 32, 1, "电压异常");
            Lcd12864_Write12CnCHAR(0, 32, 3, "不可合闸");
            if ((F_shangdian_hezha == 1) && (F_N_shangdian == 0))
            {
                F_shangdian_2 = 1;
                F_N_shangdian = 2;
            }
            delay_ms(1000);
            F_QUIT = 1;
        }
    }
    else if ((F_trip_qy == 0) && (F_trip_gy == 1))
    {
        delay_ms(5);
        // 电压不高于门限值
        if (F_VH == 1)
        {
            hezha();
            clear_flags();
        }
        else
        {
            //			if(F_shangdian_hezha==1)
            //			{
            //
            //			}

            if (F_shangdian_hezha == 1)
            {
                F_wait_DY_Normal = 1;
            }
            clear_screen();
            Lcd12864_Write12CnCHAR(0, 32, 1, "电压异常");
            Lcd12864_Write12CnCHAR(0, 32, 3, "不可合闸");
            if ((F_shangdian_hezha == 1) && (F_N_shangdian == 0))
            {
                F_shangdian_2 = 1;
                F_N_shangdian = 2;
            }
            delay_ms(1000);
            F_QUIT = 1;
        }
    }
    else if ((F_trip_qy == 0) && (F_trip_gy == 0))
    {
        hezha();
        clear_flags();
    }
}

void Trip_Process(void)
{

    // 若开报警,则不脱扣
    // F_al_uart 已经修改为F_trip_ld
    // if((F_al_key==1)||(F_al_temp==1)||(F_al_uart==1))

    if (F_trip_ld)
    {
        F_al1 = 50;
        if (F_anolog_trip == 1)
        {
            //			RELAY1 = 0;
        }
    }
    else
    {
        T_64_xs = 0;
        // 第一次脱扣
        if ((F_Trip == 3) || (F_Trip == 1))
        {
            F_Trip = 0;
            N_Trip = 0;
        }
        if (F_Trip == 0)
        {
            gz_disp = Leak_Cur_disp;
            Record_data_propare();
            //			Leak_Over_process();//漏电超限记录20201201Y
            Trip_Action();
            F_gz_disp = L_hb;
            F_ch = 0;
            if (F_TB_gz == 1)
            {
                if (F_anolog_trip == 1)
                {
                    gz_reason = trip_reason_leak;
                    F_anolog_trip = 0;
                }
                else
                    gz_reason = trip_reason_leak;
                GZ_ph = 1;
                F_record_write = 1;
                // putchar(gz_reason);
            }
            else
            {
                if (F_anolog_trip == 1)
                {
                    gz_reason = trip_reason_leak;
                    F_anolog_trip = 0;
                }
                else
                    gz_reason = trip_reason_leak; // cui修改
                GZ_ph = 1;
                F_record_write = 1;
                // putchar(gz_reason);
            }
            ctrlword5_analyze();
            if (F_la == 1)
            {
                F_Trip = 1;
                // 否则不再重合闸
            }
            else
            {
                F_Trip = 3;
                F_ch = 0;
                F_L_Lock = 1;
            }
        }
        // 连续第二次脱扣
        if (F_Trip == 2)
        {
            ctrlword5_analyze();
            if (F_la1 == 0)
            {
                if (F_la2 == 1)
                {
                    gz_disp = Leak_Cur_disp;
                    F_gz_disp = L_hb;
                    Record_data_propare();
                    Trip_Action();
                    N_Trip = N_Trip + 1;
                    rms_make(N_Trip);
                    F_Trip = 1;
                    T_64_xs = 0;
                    if (N_Trip >= 3)
                    {
                        F_Trip = 3;
                        F_L_Lock = 1;
                        N_Trip = 0;
                    }
                }
                else
                {
                    F_Trip = 3;
                    F_L_Lock = 1;
                    F_gz_disp = L_hb;
                    gz_disp = Leak_Cur_disp;
                    Record_data_propare();
                    Trip_Action();
                    gz_reason = trip_reason_lock;
                    //				rms_make(3);
                    F_ch = 1;
                    F_record_write = 1; // cui修改
                }
            }
            else if (F_la1 == 1)
            {
                F_gz_disp = L_hb;
                gz_disp = Leak_Cur_disp;
                Record_data_propare();
                Trip_Action();
                N_Trip = 0;
                rms_make(N_Trip);
                F_Trip = 1;
                T_64_xs = 0;
            }
        }
    }
}

void Switch_pos_judge(void)
{
    N_BASE = N_BASE - 1;
    if (N_BASE <= 0)
        N_BASE = 0;
    // 程序认为应在合闸位置,而闸位置处于分闸,则判断为未知分闸,写记录写成短路故障

    if (F_ZW == 1)
    {
        //Trip_LED_OFF;
        if ((F_guocheng == 0) && (isfenzha == 0))
        {
            //Trip_LED_ON;
            N_BASE = N_BASE + 2;
            if (N_BASE >= 500) // old code 500
            {
                N_BASE = 0;
                F_UTrip = 1;
                // 未知脱扣标志
                F_ZW = 0;
                F_disp_tr = 0;
                // PutStr("\nduan_lu_bao_hu");
                //				if(F_trip_gl==1)  //做采点处理后屏蔽
                //				{
                //					Cur_Sample_C(1);
                //					Cur_Sample_C(2);
                //					Cur_Sample_C(3);
                //					Cur_Sample_C(4);
                //
                //				}
                F_ch = 0;
                F_gz_disp = FZ_UK; // 未知分闸
                gz_disp = 0;
                Record_data_propare();
                gz_reason = trip_reason_hand;
                GZ_ph = 1;
                F_record_write = 1;
                // Write_Record(trip_reason_hand,1);
                // 写短路跳闸记录
            }
            // Trip_Action();
        }
    }
    // 程序认为应在分闸位置,人为手动合闸,清除以往所有标志

    if (F_ZW == 0)
    {
        //Trip_LED_ON;
        if ((F_guocheng == 0) && (isfenzha != 0))
        {
            //Trip_LED_OFF;
            N_BASE = N_BASE + 2;
            if (N_BASE >= 500)
            {
                N_BASE = 0;
                F_ZW = 1;
                clear_flags();
                F_gz_disp = 0X0F;
                F_gz = 0x00;
            }
        }
    }
}

void Leak_Over_process(void)
{
    unsigned char time_tmp[8], i;
    if (F_Leak_Alarm == 0)
    {
        if (Leak_Cur_disp >= Leak_Alarm_Value)
        //				if(200>=Leak_Alarm_Value)
        {

            F_Leak_Alarm = 1;               // 告警置1
            Leak_Over_array[0] = max_phase; // 0x01;
            DectoBCD(&Leak_Over_array[1], Leak_Cur_disp, 2);
            //			ds1302_read_time_uart(time_tmp);
            HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
            HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
            tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
            tim_m = sdatestructure.Month;
            tim_d = sdatestructure.Date;
            tim_h = stimestructure.Hours;
            tim_f = stimestructure.Minutes;
            tim_s = stimestructure.Seconds;
            time_tmp[0] = tim_y;

            time_tmp[1] = tim_m;

            time_tmp[2] = tim_d;

            time_tmp[3] = tim_h;

            time_tmp[4] = tim_f;

            time_tmp[5] = tim_s;
            for (i = 0; i < 6; i++)
            {
                Leak_Over_array[3 + i] = time_tmp[5 - i];
            }
        }
    }
    else
    {
        if (Leak_Cur_disp < Leak_Alarm_Value)
        //		if(0<Leak_Alarm_Value)
        {
            F_Leak_Alarm = 0;
            //			ds1302_read_time_uart(time_tmp);
            HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
            HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
            tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
            tim_m = sdatestructure.Month;
            tim_d = sdatestructure.Date;
            tim_h = stimestructure.Hours;
            tim_f = stimestructure.Minutes;
            tim_s = stimestructure.Seconds;
            time_tmp[0] = tim_y;

            time_tmp[1] = tim_m;

            time_tmp[2] = tim_d;

            time_tmp[3] = tim_h;

            time_tmp[4] = tim_f;

            time_tmp[5] = tim_s;
            for (i = 0; i < 6; i++)
            {
                Leak_Over_array[9 + i] = time_tmp[5 - i];
            }
            MODIFY_EEP_W((Addr_event_leak + 15 * point_event_leak), Leak_Over_array, 15, 0xA0);
            point_event_leak = point_event_leak + 1;
            if (point_event_leak >= 10)
                point_event_leak = 0x00;
            time_tmp[0] = point_event_leak;
            MODIFY_EEP_W(Addr_point_event_leak, time_tmp, 1, 0xA0);
        }
    }
}
/*********************************************
                电压处理部分
vol_handle(unsigned int value)
V_Sample(unsigned char tmp)
loss_phase_trip(unsigned char phase_tmp)
under_vol_trip(unsigned char phase_tmp)
up_vol_trip(unsigned char phase_tmp)
loss_phase_process(int upset_value,int downset_value)
under_vol_prcoess(int upset_value,int downset_value)
up_vol_prcoess(int upset_value)
-Vol_Process(void)
Vol_sample_process(void)
**********************************************/
unsigned int vol_handle(unsigned int value)
{
    unsigned int V_t;
    V_t = value;
    if (F_Corr == 0)
    {
        V_t = (V_t * V1_slope[0]) >> 20;
    }
    else
    {
        V_t = (V_t * V_A_slope[0]) >> 10;
        V_t = V_t / 100;
    }

    return (V_t);
}

void V_Sample_C(unsigned char tmp) // 220ms采样一次
{
    // 采集A\B\C相电压
    // asm("wdr");
    //	signed int tmp_A1,tmp_A2;
    //   if((tmp+4)==5)
    //	{
    //	  AD_result=Get_Adc(ADC_Channel_7);
    //	}
    //	else if((tmp+4)==6)
    //	{
    //		AD_result=Get_Adc(ADC_Channel_14);
    //	}
    //  else
    //	{
    //		AD_result=Get_Adc(ADC_Channel_15);
    //	}
    if ((tmp - 1) < 3)
    {
        //		V_Array[tmp-1]=AD_result ;
        // if(tmp==1)
        // {
        // tmp_A1 = (Vol_A_aver>>1)+(Vol_A_aver>>4);
        // tmp_A2 = (tmp_A1<<2)-(tmp_A1>>1)-109;
        // if(tmp_A2>0)
        // V_Array[0] = tmp_A2;
        // }
        if (V_MAX_tmp[tmp - 1] < V_Array[tmp - 1])
        {
            V_MAX_tmp[tmp - 1] = V_Array[tmp - 1];
        }
        if (V_MIN_tmp[tmp - 1] > V_Array[tmp - 1])
        {
            V_MIN_tmp[tmp - 1] = V_Array[tmp - 1];
        }
    }
    //	Get_Advalue(4);//是否需要？需要看多通道切换采样是否有影响。
    if (tmp == 3)
    {
        //		if((vol_handle_A(V_Array[0])<H_H_V)&&(vol_handle_A(V_Array[0])>H_L_V)&&(vol_handle_B(V_Array[1])<H_H_V)&&(V_Array[1]>H_L_V)&&(V_Array[2]<H_H_V)&&(V_Array[2]>H_L_V))
        //		F_V_Nomal=1 ;
        //		else
        //		F_V_Nomal=0 ;
        // 当前电压值不超限标志
        if ((vol_handle_A(V_Array[0]) < H_H_V) && (vol_handle_B(V_Array[1]) < H_H_V) && (vol_handle_C(V_Array[2]) < H_H_V))
            F_VH = 1;
        else
            F_VH = 0;
        // 当前电压值不超高
        if ((vol_handle_A(V_Array[0]) > H_L_V) && (vol_handle_B(V_Array[1]) > H_L_V) && (vol_handle_C(V_Array[2]) > H_L_V))
            F_VL = 1;
        else
            F_VL = 0;
        // 当前电压值不超低
        if ((F_VL == 1) && (F_VH == 1))
        {
            F_V_Nomal = 1;
        }
        else
        {
            F_V_Nomal = 0;
        }
    }
}

void V_Sample(unsigned char tmp) // 220ms采样一次
{
    //	signed int tmp_A1,tmp_A2;
    // 采集A\B\C相电压
    // asm("wdr");

    if (F_Vol_Re == 10)
    {
        //		F_Vol_Re=0;
        if ((tmp - 1) < 3)
        {
            //			V_Array[tmp-1]=AD_result ;
            if (V_MAX_tmp[tmp - 1] < V_Array[tmp - 1]) // 取最大记录值
            {
                V_MAX_tmp[tmp - 1] = V_Array[tmp - 1];
            }
            if (V_MIN_tmp[tmp - 1] > V_Array[tmp - 1])
            {
                V_MIN_tmp[tmp - 1] = V_Array[tmp - 1];
            }
        }
    }

    //	Get_Advalue(4);//是否需要？需要看多通道切换采样是否有影响。
    //	AD_result=Get_Adc(ADC_Channel_0);   // 漏电通道

    if (tmp == 3)
    {
        //		if((vol_handle_A(V_Array[0])<H_H_V)&&(vol_handle_A(V_Array[0])>H_L_V)&&(vol_handle_B(V_Array[1])<H_H_V)&&(V_Array[1]>H_L_V)&&(V_Array[2]<H_H_V)&&(V_Array[2]>H_L_V))
        //		F_V_Nomal=1 ;
        //		else
        //		F_V_Nomal=0 ;
        // 当前电压值不超限标志
        if ((vol_handle_A(V_Array[0]) < H_H_V) && (vol_handle_B(V_Array[1]) < H_H_V) && (vol_handle_C(V_Array[2]) < H_H_V))
            F_VH = 1;
        else
            F_VH = 0;
        // 当前电压值不超高
        if ((vol_handle_A(V_Array[0]) > H_L_V) && (vol_handle_B(V_Array[1]) > H_L_V) && (vol_handle_C(V_Array[2]) > H_L_V))
            F_VL = 1;
        else
            F_VL = 0;
        // 当前电压值不超低
        if ((F_VL == 1) && (F_VH == 1))
        {
            F_V_Nomal = 1;
        }
        else
        {
            F_V_Nomal = 0;
        }
    }
}

// phase_tmp取值范围1,2,3
unsigned char loss_phase_trip(unsigned char phase_tmp) // 缺相
{
    N_qx_hezha = 0;
    Record_data_propare();
    gz_disp = vol_handle(V_Array[phase_tmp - 1]);
    // if(F_trip_xq==1)
    {
        Trip_Action();
    }
    F_qxTrip = 1;
    if (phase_tmp == 1)
    {
        F_gz_disp = 0x10;
    }
    else if (phase_tmp == 2)
    {
        F_gz_disp = 0x11;
    }
    else if (phase_tmp == 3)
    {
        F_gz_disp = 0x12;
    }
    //	F_gz_disp=2*(phase_tmp-1);
    F_record_write = 1;
    gz_reason = trip_reason_phase; // 缺相
    // putchar(gz_reason);
    GZ_ph = phase_tmp;
    // Write_Record(trip_reason_phase,phase_tmp);
    return 0;
}
unsigned char low_vol_trip(unsigned char phase_tmp)
{
    N_sy_hezha = 0;
    //	if(phase_tmp==1)
    //	{
    //		F_gz_disp=0x14;
    //	}
    //	else if(phase_tmp==2)
    //	{
    //		F_gz_disp=0x15;
    //	}
    //	else if(phase_tmp==3)
    //	{
    //		F_gz_disp=0x16;
    //	}
    Record_data_propare();
    //	gz_disp=vol_handle(V_Array[phase_tmp-1]);
    // if(F_qy==1)
    {
        Trip_Action();
    }
    //	F_sy_sucess=1;

    write_tingdian();

    F_syTrip = 1;
    //	F_gz_disp=2*(phase_tmp-1);
    F_record_write = 1;
    gz_reason = trip_reason_undervoltage;
    GZ_ph = phase_tmp;
    return 0;
}

// phase_tmp取值范围1,2,3
unsigned char under_vol_trip(unsigned char phase_tmp)
{
    N_qy_hezha = 0;
    Record_data_propare();
    gz_disp = vol_handle(V_Array[phase_tmp - 1]);
    // if(F_qy==1)
    {
        Trip_Action();
    }
    F_qyTrip = 1;
    F_gz_disp = 2 * (phase_tmp - 1);
    F_record_write = 1;
    gz_reason = trip_reason_undervoltage;
    GZ_ph = phase_tmp;
    return 0;
}

// phase_tmp取值范围1,2,3
unsigned char up_vol_trip(unsigned char phase_tmp)
{
    N_gy_hezha = 0;
    Record_data_propare();
    gz_disp = vol_handle(V_Array[phase_tmp - 1]);
    // if(F_trip_gy==1)
    {
        Trip_Action();
    };
    F_gyTrip = 1;
    F_gz_disp = 2 * (phase_tmp - 1) + 1;
    F_record_write = 1;
    gz_reason = trip_reason_overvoltage;
    // putchar(gz_reason);
    GZ_ph = phase_tmp;
    // Write_Record(trip_reason_overvoltage,phase_tmp);
    return 0;
}
unsigned char lack_vol_trip(unsigned char phase_tmp)
{
    Record_data_propare();

    Trip_Action();
    F_lzTrip = 1;
    F_gz_disp = Gz_QL;
    F_record_write = 1;
    gz_reason = trip_reason_zero;
    // putchar(gz_reason);
    GZ_ph = 1;
    // Write_Record(trip_reason_overvoltage,phase_tmp);
    return 0;
}

/*说明：返回值1,2,3代表哪一下断相,0表示无断相*/
unsigned char loss_phase_process(int upset_value, int downset_value) // 缺相
{
    //	if((V_Array[0]<=10)||(V_Array[1]<=10)||(V_Array[2]<=10))//电压误跳原因未找到，当采集出来电压为0时不执行缺相跳闸函数
    //	{
    //		return 0 ;
    //	}
    if ((vol_handle_A(V_Array[0]) >= upset_value))
    {
        if ((V_Array[0] == 0) && (V_Array[1] == 0) && (V_Array[2] == 0)) // 电压误跳原因未找到，当采集出来电压为0时不执行缺相跳闸函数
        {
            return 0;
        }
        if (vol_handle_B(V_Array[1]) < downset_value)
        {
            N_a_bqx_trip = N_a_bqx_trip + 2;
            if (N_a_bqx_trip >= 20)
            {
                N_a_bqx_trip = 0;
                loss_phase_trip(2);
                return 2;
            }
        }
        else if (vol_handle_C(V_Array[2]) < downset_value)
        {
            N_a_cqx_trip = N_a_cqx_trip + 2;
            if (N_a_bqx_trip >= 20)
            {
                N_a_cqx_trip = 0;
                loss_phase_trip(3);
                return 3;
            }
        }
        else
        {
            if (N_a_bqx_trip >= 1)
            {
                N_a_bqx_trip--;
            }
            if (N_a_cqx_trip >= 1)
            {
                N_a_cqx_trip--;
            }
            return 0;
        }
    }
    if ((vol_handle_B(V_Array[1]) >= upset_value))
    {
        if ((V_Array[0] == 0) && (V_Array[1] == 0) && (V_Array[2] == 0)) // 电压误跳原因未找到，当采集出来电压为0时不执行缺相跳闸函数
        {
            return 0;
        }
        if (vol_handle_A(V_Array[0]) < downset_value)
        {
            N_b_aqx_trip = N_b_aqx_trip + 2;
            if (N_b_aqx_trip >= 20)
            {
                N_b_aqx_trip = 0;
                loss_phase_trip(1);
                return 1;
            }
        }
        else if (vol_handle_C(V_Array[2]) < downset_value)
        {
            N_b_cqx_trip = N_b_cqx_trip + 2;
            if (N_b_cqx_trip >= 20)
            {
                N_b_cqx_trip = 0;
                loss_phase_trip(3);
                return 3;
            }
        }
        else
        {
            if (N_b_aqx_trip >= 1)
            {
                N_b_aqx_trip--;
            }
            if (N_b_cqx_trip >= 1)
            {
                N_b_cqx_trip--;
            }
            return 0;
        }
    }
    if (vol_handle_C(V_Array[2]) >= upset_value)
    {
        if ((V_Array[0] == 0) && (V_Array[1] == 0) && (V_Array[2] == 0)) // 电压误跳原因未找到，当采集出来电压为0时不执行缺相跳闸函数
        {
            return 0;
        }
        if (vol_handle_A(V_Array[0]) < downset_value)
        {
            N_c_aqx_trip = N_c_aqx_trip + 2;
            if (N_c_aqx_trip >= 20)
            {
                N_c_aqx_trip = 0;
                loss_phase_trip(1);
                return 1;
            }
        }
        else if (vol_handle_B(V_Array[1]) < downset_value)
        {
            N_c_bqx_trip = N_c_bqx_trip + 2;
            if (N_c_bqx_trip >= 20)
            {
                N_c_bqx_trip = 0;
                loss_phase_trip(2);
                return 2;
            }
        }
        else
        {
            if (N_c_aqx_trip >= 1)
            {
                N_c_aqx_trip--;
            }
            if (N_c_bqx_trip >= 1)
            {
                N_c_bqx_trip--;
            }
            return 0;
        }
    }
    return 0;
}

unsigned char under_vol_prcoess(int upset_value, int downset_value) // 欠压
{
    if ((V_Array[0] <= 10) || (V_Array[1] <= 10) || (V_Array[2] <= 10)) // 电压误跳原因未找到，当采集出来电压为0时不执行缺相跳闸函数
    {
        return 0;
    }
    if ((vol_handle_A(V_Array[0]) > upset_value))
    {
        N_aqy_trip = N_aqy_trip - 1;
        if (N_aqy_trip <= 0)
            N_aqy_trip = 0;
    }
    if ((vol_handle_A(V_Array[0]) > downset_value) && (vol_handle_A(V_Array[0]) < upset_value))
    {
        N_aqy_trip = N_aqy_trip + 2;
        if (N_aqy_trip >= T_L_V)
        {
            N_aqy_trip = 0;
            under_vol_trip(1);
            return 1;
        }
    }

    if ((vol_handle_B(V_Array[1]) > upset_value))
    {
        N_bqy_trip = N_bqy_trip - 1;
        if (N_bqy_trip <= 0)
            N_bqy_trip = 0;
    }
    if ((vol_handle_B(V_Array[1]) > downset_value) && (vol_handle_B(V_Array[1]) < upset_value))
    {
        N_bqy_trip = N_bqy_trip + 2;
        if (N_bqy_trip >= T_L_V)
        {
            N_bqy_trip = 0;
            under_vol_trip(2);
            return 2;
        }
    }

    if ((vol_handle_C(V_Array[2]) > upset_value))
    {
        N_cqy_trip = N_cqy_trip - 1;
        if (N_cqy_trip <= 0)
            N_cqy_trip = 0;
    }
    if ((vol_handle_C(V_Array[2]) > downset_value) && (vol_handle_C(V_Array[2]) < upset_value))
    {
        N_cqy_trip = N_cqy_trip + 2;
        if (N_cqy_trip >= T_L_V)
        {
            N_cqy_trip = 0;
            under_vol_trip(3);
            return 3;
        }
    }

    return 0;
}
unsigned char low_vol_prcoess(void) // 失压
{
    if ((vol_handle_A(V_Array[0]) <= 44) && (vol_handle_B(V_Array[1]) <= 44) && (vol_handle_C(V_Array[2]) <= 44))
    {
        N_asy_trip = N_asy_trip + 2;
        if (N_asy_trip >= T_S_V)
        {
            N_asy_trip = 0;
            low_vol_trip(2);
        }
    }
    else
    {
        N_asy_trip = N_asy_trip - 1;
        if (N_asy_trip <= 0)
        {
            N_asy_trip = 0;
        }
    }
    //	if((vol_handle_A(V_Array[0])>low_value))
    //	{
    //		N_asy_trip=N_asy_trip-1 ;
    //	if(N_asy_trip<=0)N_asy_trip=0 ;
    //	}
    //  else
    //	{
    //		N_asy_trip=N_asy_trip+2 ;
    //		if(N_asy_trip>=T_S_V)
    //		{
    //			N_asy_trip=0 ;
    //			low_vol_trip();
    //			return 1 ;
    //		}
    //	}

    //	if((vol_handle_B(V_Array[1])>low_value))
    //	{
    //		N_bsy_trip=N_bsy_trip-1 ;
    //		if(N_bsy_trip<=0)	N_bsy_trip=0 ;
    //	}
    // else
    //	{
    //		N_bsy_trip=N_bsy_trip+2 ;
    //		if(N_bsy_trip>=T_S_V)
    //		{
    //			N_bsy_trip=0 ;
    //			low_vol_trip();
    //			return 2 ;
    //		}
    //	}
    //
    //	if((vol_handle_C(V_Array[2])>low_value))
    //	{
    //		N_csy_trip=N_csy_trip-1 ;
    //		if(N_csy_trip<=0)N_csy_trip=0 ;
    //	}
    //  else
    //	{
    //		N_csy_trip=N_csy_trip+2 ;
    //		if(N_csy_trip>=T_S_V)
    //		{
    //			N_csy_trip=0 ;
    //			low_vol_trip();
    //			return 3 ;
    //		}
    //	}
    return 0;
}

unsigned char up_vol_prcoess(int upset_value)
{
    if ((vol_handle_A(V_Array[0]) < upset_value))
    {
        N_agy_trip = N_agy_trip - 1;
        if (N_agy_trip <= 0)
            N_agy_trip = 0;
    }
    else
    {
        N_agy_trip = N_agy_trip + 2;
        if (N_agy_trip >= T_H_V)
        {
            N_agy_trip = 0;
            up_vol_trip(1);
            return 1;
        }
    }

    if (vol_handle_B(V_Array[1]) < upset_value)
    {
        N_bgy_trip = N_bgy_trip - 1;
        if (N_bgy_trip <= 0)
            N_bgy_trip = 0;
    }
    else
    {
        N_bgy_trip = N_bgy_trip + 2;
        if (N_bgy_trip >= T_H_V)
        {
            N_bgy_trip = 0;
            up_vol_trip(2);
            return 2;
        }
    }

    if (vol_handle_C(V_Array[2]) < upset_value)
    {
        N_cgy_trip = N_cgy_trip - 1;
        if (N_cgy_trip <= 0)
            N_cgy_trip = 0;
    }
    else
    {
        N_cgy_trip = N_cgy_trip + 2;
        if (N_cgy_trip >= T_H_V)
        {
            N_cgy_trip = 0;
            up_vol_trip(3);
            return 3;
        }
    }

    return 0;
}
void lack_vol_process(void)
{
    //		if(N_QL>=10)
    //		{
    //			N_QL=0 ;
    //			lack_vol_trip(2);
    //		}
    if (F_QL_TRIP == 1)
    {
        //			delay_ms(5);
        //			delay_ms(5);
        //			delay_ms(5);
        //	  	delay_ms(5);
        delay_ms(5);
        if (F_QL_TRIP == 1)
        {
            F_QL_TRIP = 0;
            lack_vol_trip(2);
        }
    }
}

void lackzero_vol_process(void)
{
    Lackzero_judge(); // 第二种判定峰面比值
    if ((F_QLA_TRIP == 1) && (F_QLB_TRIP == 1) && (F_QLC_TRIP == 1))
    {
        //		if(isfenzha!=0)
        //		{
        F_QL_TRIP = 1;
        //		}
        //		else
        //		{
        //			F_QL_TRIP=0;
        //		}
    }
    else
    {
        F_QL_TRIP = 0;
    }
    if (F_QL_TRIP == 1)
    {
        delay_ms(5);
        delay_ms(5);
        F_QLA_TRIP = 0;
        F_QLB_TRIP = 0;
        F_QLC_TRIP = 0;

        if (F_QL_TRIP == 1)
        {
            F_QL_TRIP = 0;
            lack_vol_trip(2);
        }
    }
}
void Vol_Process(void)
{
    // 合闸状态判断缺相、欠压、过压
    if (F_VLH == 0)
    {
        if ((V_Array[0] <= 450) && (V_Array[1] <= 450) && (V_Array[2] <= 450)) //
            F_VLH = 1;
    }
    if (F_VLH == 1)
    {
        if ((V_Array[0] >= 900) || (V_Array[1] >= 900) || (V_Array[2] >= 900)) //
            F_VLH = 2;
        F_shiya_hezha = 1;
    }
    // 缺零判决
    if (F_V_Array_Flag == 1)
    {
        V_tmp_MAX = 0;
        V_tmp_MIN = 10000;
        V_temp[0] = (vol_handle_A(V_Array[0]));
        V_temp[1] = (vol_handle_B(V_Array[1]));
        V_temp[2] = (vol_handle_C(V_Array[2]));

        if (V_temp[0] > V_tmp_MAX)
            V_tmp_MAX = V_temp[0]; // 求最大值
        if (V_temp[1] > V_tmp_MAX)
            V_tmp_MAX = V_temp[1];
        if (V_temp[2] > V_tmp_MAX)
            V_tmp_MAX = V_temp[2];

        if (V_temp[0] < V_tmp_MIN)
            V_tmp_MIN = V_temp[0]; // 求最小值
        if (V_temp[1] < V_tmp_MIN)
            V_tmp_MIN = V_temp[1];
        if (V_temp[2] < V_tmp_MIN)
            V_tmp_MIN = V_temp[2];

        V_Diferent = V_tmp_MAX - V_tmp_MIN;
        if (V_Diferent < 0)
            V_Diferent = -V_Diferent;

        //		V_temp[0]=V_temp[1]=V_temp[2]=0;

        F_V_Array_Flag = 0;
    }
    V_temp[0] = (vol_handle_A(V_Array[0]));
    V_temp[1] = (vol_handle_B(V_Array[1]));
    V_temp[2] = (vol_handle_C(V_Array[2]));
    V_temp_tmp[0] = (V_temp[0] - V_temp[1]) / 10;
    if (V_temp_tmp[0] < 0)
        V_temp_tmp[0] = -V_temp_tmp[0];
    V_temp_tmp[1] = (V_temp[0] - V_temp[2]) / 10;
    if (V_temp_tmp[1] < 0)
        V_temp_tmp[1] = -V_temp_tmp[1];
    V_temp_tmp[2] = (V_temp[1] - V_temp[2]) / 10;
    if (V_temp_tmp[2] < 0)
        V_temp_tmp[2] = -V_temp_tmp[2];

    if (isfenzha != 0)
    {
        // 断相保护
        F_trip_xq = 1; // 浙江改过
        //		if((F_trip_qy==1)&&(F_qxallTrip==0)&&(F_trip_xq==1))
        //				if((F_trip_qy==1)&&(F_trip_xq==1)&&(F_trip_QX==1))
        if ((F_trip_xq == 1) && (F_trip_QX == 1))
        {
            loss_phase_process(130, 100);
            // 175V
        }
        if ((F_trip_sy == 1) && (T_delay >= 150))
        {
            low_vol_prcoess();
        }

        // 欠压保护
        if ((F_trip_qy == 1) && (F_hezha_delay == 0))
        {
            under_vol_prcoess(H_L_V, 44); // 110改为44
        }
        // 过压保护
        if ((F_trip_gy == 1) && (F_hezha_delay == 0))
        {
            up_vol_prcoess(H_H_V);
        }
        if (F_trip_QL == 1) // 缺零判断
        {
            if (((vol_handle_A(V_Array[0])) < 130) || ((vol_handle_B(V_Array[1])) < 130) || ((vol_handle_C(V_Array[2])) < 130)) // 先判决是否满足缺相跳闸
            {
                loss_phase_process(130, 100);
            }
            else if (((vol_handle_A(V_Array[0])) < H_L_V) || ((vol_handle_B(V_Array[1])) < H_L_V) || ((vol_handle_C(V_Array[2])) < H_L_V)) // 先判决是否满足欠压跳闸
            {
                under_vol_prcoess(H_L_V, 44); ////110改为44
            }
            else if (((vol_handle_A(V_Array[0])) > H_H_V) || ((vol_handle_B(V_Array[1])) > H_H_V) || ((vol_handle_C(V_Array[2])) > H_H_V)) // 再判决是否满足过压跳闸
            {
                up_vol_prcoess(H_H_V);
            }
            else
            {
                lackzero_vol_process();
            }

            //			lack_vol_process();
        }
        //		if(F_trip_QL==1)
        //		{
        //			lose_vol_process(V_UP,V_DOWN);
        //		}
    }
    // 分闸状态判断重合闸
    else
    {
        if (F_wait_DY_Normal == 1)
        {
            if (F_V_Nomal == 1)
            {
                N_shangdian_hezha = N_shangdian_hezha + 2;
            }
            else
            {
                N_shangdian_hezha = N_shangdian_hezha - 1;
                if (N_shangdian_hezha <= 0)
                    N_shangdian_hezha = 0;
            }
            if (N_shangdian_hezha >= 50)
            {
                F_wait_DY_Normal = 2;
                N_shangdian_hezha = 0;
                //				F_qxTrip=0 ;
            }
        }
        // 断相重合闸
        if ((F_dianya_chonghe == 1) && (F_qxTrip != 0))
        {
            if (F_V_Nomal == 1)
            {
                N_qx_hezha = N_qx_hezha + 2;
            }
            else
            {
                N_qx_hezha = N_qx_hezha - 1;
                if (N_qx_hezha <= 0)
                    N_qx_hezha = 0;
            }
            if (N_qx_hezha >= 250)
            {
                F_QX_hezha = 1;
                N_qx_hezha = 0;
                F_qxTrip = 0;
            }
        }
        // 欠压重合闸
        if ((F_dianya_chonghe == 1) && (F_qyTrip == 1))
        {
            if (F_V_Nomal == 1)
            {
                N_qy_hezha = N_qy_hezha + 2;
            }
            else
            {
                N_qy_hezha = N_qy_hezha - 1;
                if (N_qy_hezha <= 0)
                    N_qy_hezha = 0;
            }
            if (N_qy_hezha >= 250)
            {
                F_QY_hezha = 1;
                N_qy_hezha = 0;
                F_qyTrip = 0;
            }
        }
        // 过压重合闸
        if ((F_dianya_chonghe == 1) && (F_gyTrip == 1))
        {
            if (F_V_Nomal == 1)
            {
                N_gy_hezha = N_gy_hezha + 2;
            }
            else
            {
                N_gy_hezha = N_gy_hezha - 1;
                if (N_gy_hezha <= 0)
                    N_gy_hezha = 0;
            }
            if (N_gy_hezha >= 250)
            {
                F_GY_hezha = 1;
                N_gy_hezha = 0;
                F_gyTrip = 0;
            }
        }
        // 缺零重合闸
        if ((F_dianya_chonghe == 1) && (F_lzTrip == 1)) // 缺零重合闸
        {
            if (((BQL_Judge_tmp > 1900) && (BQL_Judge_tmp < 2100)) && ((AQL_Judge_tmp > 1900) && (AQL_Judge_tmp < 2100)) && ((CQL_Judge_tmp > 1900) && (CQL_Judge_tmp < 2100))) // 判峰值
            {
                if (F_V_Nomal == 1)
                {
                    N_lz_hezha = N_lz_hezha + 2;
                }
                else
                {
                    N_lz_hezha = N_lz_hezha - 1;
                    if (N_lz_hezha <= 0)
                        N_lz_hezha = 0;
                }
                if (N_lz_hezha >= 30)
                {
                    F_QL_hezha = 1;
                    N_lz_hezha = 0;
                    F_lzTrip = 0;
                }
            }
        }

        // if((F_dianya_chonghe==1)&&(F_syTrip==1)&&(F_shiya_hezha==1))
        if ((F_dianya_chonghe == 1) && (F_syTrip == 1))
        {
            if (F_V_Nomal == 1)
            {
                N_sy_hezha = N_sy_hezha + 2;
            }
            else
            {
                N_sy_hezha = N_sy_hezha - 1;
                if (N_sy_hezha <= 0)
                    N_sy_hezha = 0;
            }
            if (N_sy_hezha >= 200)
            {
                F_shiya_hezha = 0;
                F_SY_hezha = 1;
                N_sy_hezha = 0;
                F_syTrip = 0;
            }
        }
    }
}

// 电压采样与处理
void Vol_sample_process(void) // 实际测试为50ms处理一次
{
    IWDG_Feed(); // 喂狗
    if ((F_Vol == 10) && (F_Delay == 1) && (F_Vsam_begin == 1))
    {
        F_Vol = 0;

        T_V = T_V + 1;
        V_Sample(V_point); // 电压采样
        V_point++;
        if (V_point == 4)
        {
            V_point = 1;
        }
        Vol_Process();
        if (T_V > 100) // 20ms X 100 = 2S 更新一次
        {
            T_V = 0;
            V_max_process(FN_Vol + 1); // 电压最值记录
            V_min_process(FN_Vol + 1);
            Leak_max_process(); // 漏电最值记录
            Leak_min_process();
            FN_Vol = FN_Vol + 1;
            if (FN_Vol >= 3)
                FN_Vol = 0;
        }
    }
}

void Cur_Switch(unsigned char Type_Cur)
{
    unsigned char array_temp[26];
    // Type_Cur=1;

    switch (Type_Cur)
    {
    case 0:
    {
        // Delta_Cur = 20 + D_Cur*10;  //档位值
        Delta_Cur = D_Cur + 50;

        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); // 短延倍数之后数值
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); // 瞬动倍数之后数值
        H_Cur = 1.15 * Delta_Cur * Delta_Cur;
        // H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((235 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 3)); // 375=1.5*15/0.06  //235
        I3 = DLS_Cur;                                                       // 乘以10的原因是与显示值进行比较，由于小数点儿的原因显示值都扩大了10倍。
        if (I3 >= 1250)
            I3 = I3 - 100;
        if (I3 >= 1400)
            I3 = 1200;
        Over_Value = DLS_Cur;

        Over_Value = 1.1539 * Over_Value + 375.33;

        Over_Value_duanyan = DLD_Cur;
        Over_Value_duanyan = 1.1539 * Over_Value_duanyan + 375.33;

        //			if(Over_Value<=800)
        //			{
        //			Over_Value=1.8*Over_Value+170;
        //			}
        //			Over_Value=Over_Value+650;
        //
        //
        //			Over_Value_duanyan=DLD_Cur;//duanyan
        //
        //			if(Over_Value_duanyan<=800)
        //			{
        //			Over_Value_duanyan=1.8*Over_Value_duanyan+170;
        //			}
        //			Over_Value_duanyan=Over_Value_duanyan+650;

        I3_1 = DLS_Cur;
        I2 = Over_Value_duanyan;
        frame_current_code[0] = '1';
        frame_current_code[1] = '2';
        frame_current_code[2] = '5';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /*************125壳架*****************/
        EEPROM_R(Addr_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_I1_A_slope_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_I1_B_slope_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_I1_C_slope_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_I1_A_slope1_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_I1_B_slope1_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_I1_C_slope1_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_CurC_cal_tmp_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr100_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];
        EEPROM_R(Addr100_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];
        break;
    }
    case 1:
    {
        // Delta_Cur = 60 + D_Cur*10;  //???
        Delta_Cur = D_Cur + 63;
        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); //??????
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); //????????
                                                  //			H_Cur=D_C2_Array[D_Cur]-100;
                                                  //			H5_Cur=((D_C25_15Array[D_Cur]-500)<<TH_Long_Cur); //???
                                                  //			I2=D_C29_Array[D_Cur];
                                                  //			I2=(D_C2_2d_2Array[D_Cur]*(2*D2_Cur+2))<<1;
        H_Cur = 1.21 * Delta_Cur * Delta_Cur;
        // H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((351 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 3)); //	TH_Long_Cur="3s","4s","6s","8s","10s","12s","16s","18s"    //310

        //			///如果按电流档位调长延时，用if限制TH_Long_Cur，=0对应3s档位，等于1对应4s
        //			///if(TH_Long_Cur=0)
        //			   {
        //					 H5_Cur=((250*Delta_Cur*Delta_Cur)*(R_SD[TH_Long_Cur]+3));
        //		     }
        //

        I3 = DLS_Cur; // 乘以10的原因是与显示值进行比较，由于小数点儿的原因显示值都扩大了10倍。250kejia
        Over_Value = DLS_Cur;
        if (Over_Value <= 756)
        {
            Over_Value = Over_Value + 160;
        }
        else if (Over_Value <= 2400)
        {
            Over_Value = Over_Value + 280;
        }
        else if (Over_Value <= 2500)
        {
            Over_Value = Over_Value + 200;
        }
        if (DLS_Cur == 3500) // 250*14倍单调
        {
            Over_Value = Over_Value - 280;
        }

        Over_Value_duanyan = DLD_Cur;

        if (Over_Value_duanyan <= 756)
        {
            Over_Value_duanyan = Over_Value_duanyan + 160;
        }
        else if (Over_Value_duanyan <= 2400)
        {
            Over_Value_duanyan = Over_Value_duanyan + 280;
        }
        else if (Over_Value_duanyan <= 2500)
        {
            Over_Value_duanyan = Over_Value_duanyan + 300;
        }
        if (DLD_Cur == 3000) // 250*12倍单调
        {
            Over_Value_duanyan = Over_Value_duanyan + 280;
        }
        //			if(DLD_Cur==3500)//250*14倍单调
        //			{
        //			    Over_Value_duanyan=Over_Value_duanyan-280;
        //			}

        if (DLS_Cur < 1000)
        {
            I3_1 = (DLS_Cur * 7 >> 3) + (DLS_Cur >> 5); // 缩小了0.9
        }
        else
        {
            I3_1 = 900 + ((DLS_Cur - 1000) >> 2) + ((DLS_Cur - 1000) >> 4) + ((DLS_Cur - 1000) >> 5);
        }
        // I3 = I3 - (I3>>6);
        I2 = Over_Value_duanyan; //
        // I2=DLD_Cur;    //

        //			if((D3_Cur==1)&&(Delta_Cur>=200)) I3=I3+350;
        //			if(D3_Cur>=3) I3=I3-250;
        //

        frame_current_code[0] = '2';
        frame_current_code[1] = '5';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /******************************按键校准系数********************************/
        EEPROM_R(Addr_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        //		EEPROM_R(Addr_V1_A_slope,array_temp,2,0xA0);
        //		V1_slope[0]=(array_temp[1]<<8)+array_temp[0];

        //
        //		EEPROM_R(Addr_V1_B_slope,array_temp,2,0xA0);
        //		V1_slope[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr_V1_C_slope,array_temp,2,0xA0);
        //		V1_slope[2]=(array_temp[1]<<8)+array_temp[0];

        /*************250壳架*****************/
        EEPROM_R(Addr_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        //		EEPROM_R(Addr_Vol1_A_temp,array_temp,2,0xA0);
        //		Vol1_A_temp=(array_temp[1]<<8)+array_temp[0];
        //		EEPROM_R(Addr_Vol1_B_temp,array_temp,2,0xA0);
        //		Vol1_B_temp=(array_temp[1]<<8)+array_temp[0];
        //		EEPROM_R(Addr_Vol1_C_temp,array_temp,2,0xA0);
        //		Vol1_C_temp=(array_temp[1]<<8)+array_temp[0];
        //
        EEPROM_R(Addr_I1_A_slope_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_B_slope_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_C_slope_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_A_slope1_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_B_slope1_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_I1_C_slope1_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurC_cal_tmp_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];
        break;
    }

    case 2: // 400kejia
    {
        Delta_Cur = 160 + D_Cur;                  // 档位值
        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); // 倍数之后数值
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); // 瞬动倍数之后数值
        //		  H_Cur=D_C3_Array[D_Cur];
        //			H5_Cur=(D_C35_15Array[D_Cur]<<TH_Long_Cur);
        //			I2=D_C29_Array[D_Cur];
        H_Cur = 1.21 * Delta_Cur * Delta_Cur;
        // H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((360 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 3)); // 246   //360
        Over_Value = DLS_Cur;
        if (Over_Value <= 1280)
        {
            Over_Value = 0.8438 * Over_Value + 26.667;
        }
        else if (Over_Value <= 2400)
        {
            Over_Value = 0.5625 * Over_Value + 473.33;
        }
        else
        {
            Over_Value = Over_Value * 0.4182 + 771.75;
        }

        if (DLS_Cur == 5600) // 400*14±?μ￥μ÷
        {
            Over_Value = Over_Value - 150;
        }
        // duanyan
        Over_Value_duanyan = DLD_Cur;

        if (Over_Value_duanyan <= 1280)
        {
            Over_Value_duanyan = 0.8438 * Over_Value_duanyan + 26.667;
        }
        else if (Over_Value_duanyan <= 2400)
        {
            Over_Value_duanyan = 0.5625 * Over_Value_duanyan + 473.33;
        }
        else
        {
            Over_Value_duanyan = Over_Value_duanyan * 0.4182 + 771.75;
        }

        if (DLD_Cur == 5600) // 400*14±?μ￥μ÷
        {
            Over_Value_duanyan = Over_Value_duanyan - 150;
        }

        I3 = DLS_Cur; // 乘以10的原因是与显示值进行比较，由于小数点儿的原因显示值都扩大了10倍。
        I3_1 = DLS_Cur;
        // I3=(I3*7>>3)+(I3>>5);  //缩小了0.9
        // I3 = I3 - (I3>>6);

        //			if(Delta_Cur<=200) I3=I3-200;
        //			else if((D3_Cur<=1)&&(Delta_Cur>=200)) I3=I3-(I3*1)/10;
        //			else if((D3_Cur==2)&&(Delta_Cur>=200)) I3=I3-(I3*25)/100;
        //			else if((D3_Cur==3)&&(Delta_Cur>=400)) I3=I3-(I3*3)/10-200;
        //			else if((D3_Cur==3)&&(Delta_Cur>=200)&&(Delta_Cur<400)) I3=I3-(I3*2)/10-200;
        //			else if((D3_Cur==4)&&(Delta_Cur>=200)) I3=I3-(I3*4)/10;
        //			else if((D3_Cur==5)&&(Delta_Cur>=200)) I3=I3-(I3*4)/10-400;

        I2 = Over_Value_duanyan;

        frame_current_code[0] = '4';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /*************400壳架*****************/
        EEPROM_R(Addr400_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_A_slope_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_B_slope_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_C_slope_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_A_slope1_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_B_slope1_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_I1_C_slope1_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurC_cal_tmp_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr400_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];
        break;
    }
    case 3: // 630kejia
    {
        // Delta_Cur = 210+D_Cur*30;  //档位值
        Delta_Cur = D_Cur + 252;

        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); // 倍数之后数值
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); // 瞬动倍数之后数值
        H_Cur = 1.21 * Delta_Cur * Delta_Cur;

        H5_Cur = ((330 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 3)); // 375=1.5*15/0.06  //235
        I3 = DLS_Cur;                                                       // 乘以10的原因是与显示值进行比较，由于小数点儿的原因显示值都扩大了10倍。
        I3_1 = DLS_Cur;

        // shundong
        Over_Value = DLS_Cur;
        if (Over_Value <= 2200)
        {
            Over_Value = Over_Value * 0.6023 - 41.667;
        }
        else if (Over_Value <= 3780)
        {
            Over_Value = Over_Value * 0.3805 + 493.11;
        }
        else
        {
            Over_Value = Over_Value - 2750;
        }
        if (DLS_Cur == 6300) // 630*10倍单调
        {
            Over_Value = Over_Value - 1000;
        }
        if (DLS_Cur == 7560) // 630*12倍单调
        {
            Over_Value = Over_Value - 2000;
        }
        if (DLS_Cur == 8820) // 630*14倍单调
        {
            Over_Value = Over_Value - 3200;
        }

        // duanyan
        Over_Value_duanyan = DLD_Cur;

        if (Over_Value_duanyan <= 2200)
        {
            Over_Value_duanyan = Over_Value_duanyan * 0.6023 - 41.667;
        }
        else if (Over_Value_duanyan <= 3780)
        {
            Over_Value_duanyan = Over_Value_duanyan * 0.3805 + 493.11;
        }
        else
        {
            Over_Value_duanyan = Over_Value_duanyan - 2750;
        }
        if (DLD_Cur == 6300) // 630*10倍单调
        {
            Over_Value_duanyan = Over_Value_duanyan - 1000;
        }
        if (DLD_Cur == 7560) // 630*12倍单调
        {
            Over_Value_duanyan = Over_Value_duanyan - 2000;
        }
        if (DLD_Cur == 8820) // 630*14倍单调
        {
            Over_Value_duanyan = Over_Value_duanyan - 3200;
        }

        I2 = Over_Value_duanyan;

        frame_current_code[0] = '6';
        frame_current_code[1] = '3';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /*************630壳架*****************/
        EEPROM_R(Addr630_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];
        /*************400壳架*****************/
        //		EEPROM_R(Addr400_L1_slope,array_temp,2,0xA0);
        //		L1_slope=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_Leak1_temp,array_temp,2,0xA0);
        //		Leak1_temp=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_A_slope,array_temp,2,0xA0);
        //		I1_A_slope[0]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_B_slope,array_temp,2,0xA0);
        //		I1_B_slope[0]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_C_slope,array_temp,2,0xA0);
        //		I1_C_slope[0]=(array_temp[1]<<8)+array_temp[0];

        //		EEPROM_R(Addr400_I1_A_slope1,array_temp,2,0xA0);
        //		I1_A_slope[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_B_slope1,array_temp,2,0xA0);
        //		I1_B_slope[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_I1_C_slope1,array_temp,2,0xA0);
        //		I1_C_slope[1]=(array_temp[1]<<8)+array_temp[0];

        //
        //		EEPROM_R(Addr400_CurA_cal_tmp,array_temp,2,0xA0);
        //		CurA_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
        //
        //    EEPROM_R(Addr400_CurB_cal_tmp,array_temp,2,0xA0);
        //		CurB_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];
        //
        //    EEPROM_R(Addr400_CurC_cal_tmp,array_temp,2,0xA0);
        //		CurC_cal_tmp[0]=(array_temp[1]<<8)+array_temp[0];

        //    EEPROM_R(Addr400_CurA_cal_tmp1,array_temp,2,0xA0);
        //		CurA_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_CurB_cal_tmp1,array_temp,2,0xA0);
        //		CurB_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];
        //
        //		EEPROM_R(Addr400_CurC_cal_tmp1,array_temp,2,0xA0);
        //		CurC_cal_tmp[1]=(array_temp[1]<<8)+array_temp[0];

        EEPROM_R(Addr630_I1_A_slope_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_B_slope_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_C_slope_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_A_slope1_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_B_slope1_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_I1_C_slope1_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurC_cal_tmp_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr630_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];
        break;
    }
    case 4: // 800壳架在这里修改
    {
        Delta_Cur = 320 + D_Cur;                  // 档位值
        DLD_Cur = (Delta_Cur * (2 * D2_Cur + 2)); // 倍数之后数值
        DLS_Cur = (Delta_Cur * (2 * D3_Cur + 4)); // 瞬动倍数之后数值
        H_Cur = 1.21 * Delta_Cur * Delta_Cur;
        //	H5_Cur=((375*Delta_Cur*Delta_Cur)<<TH_Long_Cur);//375=1.5*15/0.06
        H5_Cur = ((320 * Delta_Cur * Delta_Cur) * (R_SD[TH_Long_Cur] + 3)); // 375=1.5*15/0.06
        I3 = DLS_Cur;                                                       // 乘以10的原因是与显示值进行比较，由于小数点儿的原因显示值都扩大了10倍。
        I3_1 = DLS_Cur;
        I2 = Over_Value_duanyan;

        Over_Value = DLS_Cur;
        /*下面写瞬动的校准曲线*/
        if (Over_Value <= 7200)
        {
            Over_Value = Over_Value * 0.4789 + 346.74;
        }
        else if (Over_Value <= 8000)
        {
            Over_Value = Over_Value - 4000;
        }
        else
        {
            Over_Value = Over_Value - 4875;
        }
        if ((DLS_Cur == 9600) || (DLS_Cur == 11200))
        {
            Over_Value = Over_Value - 850;
        }
        //			if(Over_Value<=7000)
        //			{
        //					Over_Value=Over_Value*0.475+325.74;
        //			}
        //
        //				 Over_Value=Over_Value*0.1992+1915.6;

        Over_Value_duanyan = DLD_Cur;
        /*下面写二段的校准曲线*/
        if (Over_Value_duanyan <= 7000)
        {
            Over_Value_duanyan = Over_Value_duanyan * 0.475 + 325.74;
        }

        Over_Value_duanyan = Over_Value_duanyan * 0.1992 + 1915.6;

        frame_current_code[0] = '8';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        /*************800壳架*****************/
        EEPROM_R(Addr800_L1_slope, array_temp, 2, 0xA0);
        L1_slope = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_Leak1_temp, array_temp, 2, 0xA0);
        Leak1_temp = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_A_slope, array_temp, 2, 0xA0);
        I1_A_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_B_slope, array_temp, 2, 0xA0);
        I1_B_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_C_slope, array_temp, 2, 0xA0);
        I1_C_slope[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_A_slope1, array_temp, 2, 0xA0);
        I1_A_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_B_slope1, array_temp, 2, 0xA0);
        I1_B_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_C_slope1, array_temp, 2, 0xA0);
        I1_C_slope[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurA_cal_tmp, array_temp, 2, 0xA0);
        CurA_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurB_cal_tmp, array_temp, 2, 0xA0);
        CurB_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurC_cal_tmp, array_temp, 2, 0xA0);
        CurC_cal_tmp[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurA_cal_tmp1, array_temp, 2, 0xA0);
        CurA_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurB_cal_tmp1, array_temp, 2, 0xA0);
        CurB_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurC_cal_tmp1, array_temp, 2, 0xA0);
        CurC_cal_tmp[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_A_slope_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_B_slope_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_C_slope_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_A_slope1_nv, array_temp, 2, 0xA0);
        I1_A_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_B_slope1_nv, array_temp, 2, 0xA0);
        I1_B_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_I1_C_slope1_nv, array_temp, 2, 0xA0);
        I1_C_slope_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurA_cal_tmp_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurB_cal_tmp_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurC_cal_tmp_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[0] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurA_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurA_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurB_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurB_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];

        EEPROM_R(Addr800_CurC_cal_tmp1_nv, array_temp, 2, 0xA0);
        CurC_cal_tmp_nv[1] = (array_temp[1] << 8) + array_temp[0];
        break;
    }
    }
}

void Cur_Switch_F(unsigned char Type_Cur)
{

    // Type_Cur=1;

    switch (Type_Cur)
    {
    case 0:
    {
        frame_current_code[0] = '8';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        break;
    }
    case 1:
    {
        frame_current_code[0] = '2';
        frame_current_code[1] = '5';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;

        break;
    }
    case 2:
    {
        frame_current_code[0] = '4';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;

        break;
    }
    case 3:
    {
        frame_current_code[0] = '6';
        frame_current_code[1] = '3';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        break;
    }
    case 4:
    {
        frame_current_code[0] = '8';
        frame_current_code[1] = '0';
        frame_current_code[2] = '0';
        frame_current_code[3] = frame_current_code[4] = frame_current_code[5] = 0x20;
        break;
    }
    }
}

unsigned int cur_handle(unsigned int x)
{
    //	int y;
    //	int y1;
    //	//电流框架等级为20~100A时
    //	if(Type_Cur==0) x= (x/5)>>2 ;   //x为采出来的值 0-4096
    //	//电流框架等级为60~250A时
    //	if(Type_Cur==1)   //需要改动
    //	{
    //		 x= (x*53)>>10 ;
    //	}
    //	//电流框架等级为200~400A时
    //	if(Type_Cur==2)
    //	{
    //		 x= (x*83)>>10 ;
    //	}
    //	//电流框架等级为60~250A时
    //	if(Type_Cur==3)
    //	{
    //		 x= (x*107)>>10 ;
    //	}
    ////	if(x>=760) I_factor_tmp = I_factor;
    ////	else if(x>=600) I_factor_tmp = I_factor>>1;
    ////	else if(x>=400) I_factor_tmp = I_factor>>2;
    ////	else if(x>=200)  I_factor_tmp = I_factor>>3;
    ////	else            I_factor_tmp = I_factor>>4;
    ////	if(160<x<200)
    ////	{
    ////		x=x-5;
    ////	}
    //  y1=x;  //便于仿真时观看变量
    //	y = y1;
    //	y1=0;
    ////	if(y<100)
    ////	y = y-10;
    //	if(y <= 10)     y = 0;
    //	return y ;
}

// void Cur_Sample_C(unsigned char tmp)
//{
//	unsigned char i ;
//	i=tmp-1 ;
////	F_Cur = 0;
//	if(i==0)
//	{
//	  AD_result=Get_Adc(ADC_Channel_10);
//	}
//	else if(i==1)
//	{
//		AD_result=Get_Adc(ADC_Channel_11);
//	}
//  else
//	{
//		AD_result=Get_Adc(ADC_Channel_12);
//	}
//	if(I_MAX_tmp[i]<I_Array[i])
//	{
//		I_MAX_tmp[i] = I_Array[i];
//	}
//	if(I_MIN_tmp[i]>I_Array[i])
//	{
//		I_MIN_tmp[i] = I_Array[i];
//	}
////	AD_result=Get_Adc(ADC_Channel_0);
//}

// void Cur_Sample(unsigned char tmp)
//{
//	unsigned char i ;
//	i=tmp-1 ;
////	F_Cur = 0;
//
//	if(i==0)
//	{
//	  AD_result=Get_Adc(ADC_Channel_10);
//	}
//	else if(i==1)
//	{
//		AD_result=Get_Adc(ADC_Channel_11);
//	}
//  else
//	{
//		AD_result=Get_Adc(ADC_Channel_12);
//	}
//
//	if(i<4)
//	{
//		I_Array[i]=AD_result ;
//		if(I_MAX_tmp[i]<I_Array[i])
//		{
//			I_MAX_tmp[i] = I_Array[i];
//		}
//		if(I_MIN_tmp[i]>I_Array[i])
//		{
//			I_MIN_tmp[i] = I_Array[i];
//		}
//	}
////	AD_result=Get_Adc(ADC_Channel_0);
//}

void Cur_Process(void)
{
    unsigned char i;
    if (F_trip_gl == 1)
    {
        for (i = 0; i < 3; i++)
        {
            if (isfenzha == 0)
            {

                I_Array[0] = 0;
                I_Array[1] = 0;
                I_Array[2] = 0;
            }
            I2_Array[i] = (long)I_Array[i] * (long)I_Array[i]; //  对电流进行平方
                                                               // I2_Array[1]=90000;
            if (I2_Array[i] >= H_Cur)
            {
                I2_Array_Sum[i] = I2_Array_Sum[i] + I2_Array[i];
            }
            else
            {

                I2_Array_Sum[i] = I2_Array_Sum[i] - 0.5 * I2_Array[i];
                if (I2_Array_Sum[i] < 0)
                {
                    I2_Array_Sum[i] = 0;
                }
            }

            //			I2_Array_Sum[i]=I2_Array_Sum[i]+I2_Array[i]-H_Cur ;  //H_Cur 为AD值的平方*1.15
            //			if(I2_Array_Sum[i]<0)
            //			{
            //				I2_Array_Sum[i]=0;
            //			}
            // 热积累脱扣处理
            // 若某一相超限
            if (I2_Array_Sum[i] >= H5_Cur) // H5_Cur9000
            {
                // I2_Array_Sum[i]=H5_Cur-(H_Cur<<2);
                I2_Array_Sum[0] = 0;
                I2_Array_Sum[1] = 0;
                I2_Array_Sum[2] = 0;
                // 若从没有过流故障发生
                if (F_I_STA == 0)
                {
                    Record_data_propare();
                    if (i == 0)
                    {
                        gz_disp = cur_handle_A(I_Array_xianshi[0]); // cur_handle处理为实际要显示的值
                    }
                    else if (i == 1)
                    {
                        gz_disp = cur_handle_B(I_Array_xianshi[1]); // cur_handle处理为实际要显示的值
                    }
                    else if (i == 2)
                    {
                        gz_disp = cur_handle_C(I_Array_xianshi[2]); // cur_handle处理为实际要显示的值
                    }
                    Trip_Action();
                    F_record_write = 1;
                    gz_reason = trip_reason_cur;
                    // putchar(gz_reason);
                    GZ_ph = i + 1;
                    // Write_Record(trip_reason_cur,(i+1));
                    F_gz_disp = A_gl + i;

                    // 写过流跳闸记录
                    // 如果重合闸功能开启
                    if (F_ia == 1)
                    {
                        F_ch = 0;
                        F_I_STA = 1;
                    }
                    // 如果过流重合闸功能关闭
                    else
                    {
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_ch = 1;
                    }
                    // 否则不再重合闸
                }
                // 连续第二次脱扣
                /*	else if(F_I_STA == 1)//若过流故障已发生一次,不再执行脱扣,只是记一下记录
                                                                {

                                                                }*/
                // 重合闸后10s内又发生电流脱扣
                else if (F_I_STA == 2)
                {
                    F_I_STA = 3;
                    // 写过流跳闸记录
                    F_ch = 1;
                    Record_data_propare();
                    if (i == 0)
                    {
                        gz_disp = cur_handle_A(I_Array_xianshi[0]); // cur_handle处理为实际要显示的值
                    }
                    else if (i == 1)
                    {
                        gz_disp = cur_handle_B(I_Array_xianshi[1]); // cur_handle处理为实际要显示的值
                    }
                    else if (i == 2)
                    {
                        gz_disp = cur_handle_C(I_Array_xianshi[2]); // cur_handle处理为实际要显示的值
                    }
                    // if(F_trip_gl==1)
                    {
                        Trip_Action();
                    }
                    F_record_write = 1;
                    gz_reason = trip_reason_cur;
                    // putchar(gz_reason);
                    GZ_ph = i + 1;
                    // Write_Record(trip_reason_cur,(i+1));
                    F_I_Lock = 1;
                    F_gz_disp = A_gl + i; // i的意思是哪一相发生过流故障
                }
            }
        }
    }

    // end of else

    // end of for(i=0;i<4;i++)

    F_ITrip = F_I_STA;
    // end of if(F_tb)
}

// 电流采样与处理
void Cur_sample_process(void)
{
    IWDG_Feed(); // 喂狗
    if (F_Delay == 1)
    {
        if (F_Cur == 10) // 以后20ms处理一次
        {
            I_Array[0] = cur_handle_A(I_Array_xianshi[0]);
            I_Array[1] = cur_handle_B(I_Array_xianshi[1]);
            I_Array[2] = cur_handle_C(I_Array_xianshi[2]);

            if (I_MAX_tmp[0] < I_Array_xianshi[0])
            {
                I_MAX_tmp[0] = I_Array_xianshi[0];
            }
            if (I_MIN_tmp[0] > I_Array_xianshi[0])
            {
                I_MIN_tmp[0] = I_Array_xianshi[0];
            }
            if (I_MAX_tmp[1] < I_Array_xianshi[1])
            {
                I_MAX_tmp[1] = I_Array_xianshi[1];
            }
            if (I_MIN_tmp[1] > I_Array_xianshi[1])
            {
                I_MIN_tmp[1] = I_Array_xianshi[1];
            }
            if (I_MAX_tmp[2] < I_Array_xianshi[2])
            {
                I_MAX_tmp[2] = I_Array_xianshi[2];
            }
            if (I_MIN_tmp[2] > I_Array_xianshi[2])
            {
                I_MIN_tmp[2] = I_Array_xianshi[2];
            }
            //				SMG_CLK=0;
            T_I = T_I + 1;
            if (T_I == 501) // 20ms X 100 = 2S 更新一次
            {
                T_I = 0;
                I_max_process(F_Cur_m + 1);
                I_min_process(F_Cur_m + 1);
                F_Cur_m = F_Cur_m + 1;
                if (F_Cur_m >= 3)
                    F_Cur_m = 0;
            }
            if (F_powerup_re == 1)
            {
                F_Record = 1;
                F_powerup_re = 0;
            }
            F_Cur = 0;
            Cur_Process();
        }
    }
}

/*********************************************
                漏电处理部分
**********************************************
Get_L(void)
signed int Get_AB(void)
signed int min(void)
void Clear_TB_array(void)
unsigned int Get_Delta_Leak(signed int tmp_a,signed int tmp_b)
void Leak_process(void)
void Quick_process(void)
void Auto_Leak_process(void)
void Normal_Leak_process(void)
**********************************************/

void Get_L(void)
{
    AD_tmp = 0;
    AD_tmp = ADC_ConvertedValue[0];
    Leak_Cur_Sum = Leak_Cur_Sum + AD_tmp;
}

// void TB_leak_process(void)
//{
//	if(F_Leak_Delay1==30)
//	{
//		Lea_Cur_old = Leak_Cur_disp;
//		F_Leak_Delay1=0;
//	}
//
//
//		if(Leak_Cur_disp > Lea_Cur_old)
//		{
//			Delta_Leak_Cur = Leak_Cur_disp - Lea_Cur_old;
//		}
////		else
////		{
////			Delta_Leak_Cur = Lea_Cur_old - Leak_Cur_disp;
////		}
//
//		if(Delta_Leak_Cur<0) Delta_Leak_Cur = 0;
//
//		if(Delta_Leak_Cur>=dianliu11[D_LCur])
//		{

//
//			if(isfenzha!=0)
//			{
//				Trip_Process();
//			}
//			Delta_Leak_Cur=0;
//			Lea_Cur_old=0;
//
//		}
//
//	}
void TB_leak_process(void)
{
    if (F_Leak_Delay == 0)
    {
        Lea_Cur_old = Leak_Cur_disp;
    }
    if (F_Leak_Delay == 1)
    {
        if (Leak_Cur_disp >= Lea_Cur_old)
        {
            Delta_Leak_Cur = Leak_Cur_disp - Lea_Cur_old;
        }
        else
        {
            Delta_Leak_Cur = Lea_Cur_old - Leak_Cur_disp;
        }

        if (Delta_Leak_Cur < 0)
            Delta_Leak_Cur = 0;
        if (Delta_Leak_Cur >= 20)
        {
            N_TB_T = N_TB_T + 6;
        }
        else
        {
            N_TB_T = N_TB_T - 2;
            if (N_TB_T < 0)
                N_TB_T = 0;
        }
        if (N_TB_T > N_TH)
        {
            N_TB_T = 0;
            if (isfenzha != 0)
            {
                Trip_Process();
            }
        }
        if (N_TB_T == 0)
        {
            Lea_Cur_old = Leak_Cur_disp;
        }
    }
}

char leak_f;
void Leak_process(void)
{

    int leak_tmp = 0;
    Leak_Cur = 0;
    //	Leak_Cur=(Leak_Cur_Sum>>6)+(Leak_Cur_Sum>>7)+(Leak_Cur_Sum>>9);//0.25倍
    leak_tmp = leak_handle(Leak_Cur_Sum);
    //	leak_tmp=leak_handle(Leak_xianshi_disp);
    if (leak_tmp < 0)
        Leak_Cur_disp = 0;
    else
        Leak_Cur_disp = leak_tmp;

    if (isfenzha == 0)
        F_leak_disp = 0;

    if (F_leak_disp < 2)
    {
        Leak_Cur_disp = 0;
        F_leak_disp++;
    }
    else
    {
        Leak_Cur_disp = leak_tmp;
        //				Leak_Cur_disp = 1000;
        //		Leak_Cur_disp_cal= leak_tmp;
    }
    Leak_Over_process(); // 20201202加入漏电告警记录处理Y

    //		Leak_Cur_disp_cal= leak_tmp;
    //		if(leak_tmp<=10) leak_tmp = 0;
    if (Leak_Cur_disp > Leak_MAX_tmp)
    {
        Leak_MAX_tmp = Leak_Cur_disp;
    }
    if (Leak_Cur_disp < Leak_MIN_tmp)
    {
        Leak_MIN_tmp = Leak_Cur_disp;
    }
    Leak_Cur_Sum = 0;
    if (D_LCur == 8) // 自动跟踪档位
    {
        Auto_Leak_process();
    }
    else
    {
        // Leak_Cur_disp=1000;
        Normal_Leak_process(); // 0.05 0.1 0.3 0.5 0.8 1
    }
    //	N_T=0 ;
    if (N_T >= N_TH)
    {
        N_T = 0;
        if ((isfenzha != 0) && (F_jiance != 1))
        {
            Trip_Process();
        }
    }
    // 这里貌似有问题
    else
    {
        if (F_al1)
            F_al1--;
    }
    if ((F_TB_trip == 1) || (F_Special_wave == 1))
    {
        TB_leak_process();
    }
}

void Quick_process(void)
{
    if (isfenzha != 0) // 在合闸位置
    {
        // 只有在0.2s档进行10倍的快速动作
        if (TH_LCur == 0)
        {
            Id3 = D_LCur3_Array[D_LCur];
            Id4 = D_LCur4_Array[D_LCur];
            if ((AD_result >= Id3) || (AD_result < Id4))
            {

                N_K = N_K + 2;
                // N_K=N_K+20;
                if (N_K >= 37)
                {
                    F_ks = 1;
                    N_K = 0;
                    N_T = 0;
                    if ((isfenzha != 0) && (F_jiance != 1))
                    {
                        Trip_Process();
                    }
                    // 快速动作分闸处理,
                }
            }
            else
            {
                N_K = N_K - 2;
                if (N_K <= 0)
                    N_K = 0;
            }
        }
    }
}

void Auto_Leak_process(void)
{
    // 如果是第一次上电
    // F_compare上电为2,其他为1

    if (F_Compare == 2)
    {
        F_Compare = 0;
        D_A_LCur = 11;
        // D_A_LCur漏电自动跟踪档位  //设定成最高档位
        Id1_A = D_ACur_Array[D_A_LCur];
        // 更新比较值
        Id1_L = H_A_L[D_A_LCur];
        // 自适应下限值,用于向下切换档位
        Id1_H = H_A_H[D_A_LCur];
        // 自适应上限值,用于向上切换档位
        // putchar(D_A_LCur);
    }
    // end of if(F_Compare==2)
    if (F_Trip == 0)
    {
        // N_A_L 自动跟踪计数下限
        if (N_A_L >= 12000)
        {

            if (D_A_LCur > 0)
                D_A_LCur = D_A_LCur - 1;

            N_A_H = N_A_L = 0;
            // putchar(D_A_LCur);
            // 切换档位,计数器清零
        }
        // 向上切换档位
        if (N_A_H >= 12000)
        {
            D_A_LCur = D_A_LCur + 1;
            if (D_A_LCur >= 11)
                D_A_LCur = 11;
            N_A_H = N_A_L = 0;
            // putchar(D_A_LCur);
            // 切换档位,计数器清零
        }
    }
    // end of if(F_Trip==0)
    // 第一次脱扣后,档位较脱扣前增加1
    if (F_Trip == 2)
    {
        if (F_Trip1 == 0)
        {
            D_A_LCur = D_A_LCur + 1;
            F_Trip1 = 1;
        }

        if (D_A_LCur >= 11)
            D_A_LCur = 11;
        N_A_H = N_A_L = 0;
    }
    // 死锁清零
    if (F_Trip == 3)
    {
        N_A_H = N_A_L = 0;
    }
    Id1_A = D_ACur_Array[D_A_LCur];
    // 自适应档位值,用于脱扣
    Id1_L = H_A_L[D_A_LCur];
    // 自适应下限值,用于向下切换档位
    Id1_H = H_A_H[D_A_LCur];
    // 自适应上限值,用于向上切换档位
    // 比较和计数
    if (Leak_Cur_disp >= Id1_H)
    {
        N_A_H = N_A_H + 2;
        N_A_L = N_A_L - 1;
    }
    else if (Leak_Cur_disp > Id1_L)
    {
        N_A_H = N_A_H - 1;
        N_A_L = N_A_L - 1;
    }
    else
    {
        N_A_L = N_A_L + 2;
        N_A_H = N_A_H - 1;
    }
    if (N_A_H < 0)
        N_A_H = 0;
    if (N_A_L < 0)
        N_A_L = 0;
    if (Leak_Cur_disp >= Id1_A)
    {
        N_T = N_T + 2;
        leak_f = 1;
    } // 24 7 15 只跟显示有关}
    // 低于动作门限75%
    else if (Leak_Cur_disp < ((Id1_A - Id1_A) >> 2))
    {
        leak_f = 0;
        N_T = N_T - 1;
        if (N_T <= 0)
            N_T = 0;
    }
}

void Normal_Leak_process(void)
{
    Id1 = D_LCur1_Array[D_LCur];
    Id2 = D_LCur2_Array[D_LCur];

    Id45 = D_LCur45_Array[D_LCur];

    Id1_delta = D_LCur_delta_Array[D_LCur];
    N_TH = TD_LCur1_Array[TH_LCur];

    if (TH_LCur == 4) // 0.1S档位
    {
        if (Leak_Cur_disp >= Id45)
        {
            N_T = N_T + 32;
            leak_f = 1;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            N_T = N_T + 6;
            leak_f = 1;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            N_T = N_T + 6;
            leak_f = 1;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            leak_f = 0;
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }

    else if (TH_LCur == 1) // 0.3S档位
    {
        if (Leak_Cur_disp >= Id45)
        {
            N_T = N_T + 10;
            leak_f = 1;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            N_T = N_T + 8;
            leak_f = 1;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            N_T = N_T + 6;
            leak_f = 1;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            leak_f = 0;
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }
    else if (TH_LCur == 2) // 0.5S档位
    {
        if (Leak_Cur_disp >= Id45)
        {
            N_T = N_T + 9;
            leak_f = 1;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            N_T = N_T + 8;
            leak_f = 1;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            N_T = N_T + 6;
            leak_f = 1;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            leak_f = 0;
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }
    else if (TH_LCur == 3) // 1S档位
    {
        if (Leak_Cur_disp >= Id45)
        {
            leak_f = 1;
            N_T = N_T + 10;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            leak_f = 1;
            N_T = N_T + 8;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            leak_f = 1;
            N_T = N_T + 6;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            leak_f = 0;
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }

    else
    {
        if (Leak_Cur_disp >= Id45)
        {
            leak_f = 1;
            N_T = N_T + 12;
        }
        else if (Leak_Cur_disp >= Id2)
        {
            leak_f = 1;
            N_T = N_T + 8;
        }
        else if (Leak_Cur_disp >= Id1)
        {
            leak_f = 1;
            N_T = N_T + 6;
        }
        else if (Leak_Cur_disp < (Id1 - (Id1 >> 2))) // Id1-Id2/4
        {
            leak_f = 0;
            N_T = N_T - 1;
            if (N_T <= 0)
                N_T = 0;
        }
    }
}

void DLS_DLD_process(void)
{

    if (F_C_IP == 1)
    {
        if (I_Array[3] >= H_DLD_Cur)
        {
            N_DLS = N_DLS + 2;
            if (N_DLS >= 20)
            {
                N_DLS = 0;
                Record_data_propare();
                gz_disp = 999;
                // if(F_trip_gl==1)
                {
                    Trip_Action();
                }
                gz_reason = trip_reason_cur;
                GZ_ph = 1;
                F_gz_disp = A_gl;
                F_record_write = 1;
                // putchar(gz_reason);
            }
        }
        else
        {
            if (N_DLS >= 1)
            {
                N_DLS = N_DLS - 1;
            }
        }
    }
}

void Wait_selftest(void)
{
    unsigned char i;

    if (get_key() == 0x50)
    {
        for (i = 0; i < 80; i++)
        {
            delay_ms(5);
        }
        if (get_key() == 0x50)
        {
            clear_screen();
            Lcd12864_Write12CnCHAR(0, 16, 2, "初始化设置...\r");

            factor_first_init(0);
            delay_ms(1000);
            delay_ms(1000);
        }
    }
}

void Day_factors_clear(void)
{
    F_Cur_m = 0;
    FN_Vol = 0;

    Leak_MAX = Leak_MAX_tmp = 0;
    Leak_MIN = Leak_MIN_tmp = Id1;
    //		Leak_MIN = Leak_MIN_tmp = 10000;
    V_MAX[0] = V_MAX[1] = V_MAX[2] = 0;
    V_MAX_tmp[0] = V_MAX_tmp[1] = V_MAX_tmp[2] = 0;
    V_MIN[0] = V_MIN[1] = V_MIN[2] = 60000; // old code is 3000
    V_MIN_tmp[0] = V_MIN_tmp[1] = V_MIN_tmp[2] = 60000;

    I_MAX[0] = I_MAX[1] = I_MAX[2] = I_MAX[3] = 0;
    I_MAX_tmp[0] = I_MAX_tmp[1] = I_MAX_tmp[2] = 0;
    I_MIN[0] = I_MIN[1] = I_MIN[2] = I_MIN[3] = 60000;                 // I2 ;
    I_MIN_tmp[0] = I_MIN_tmp[1] = I_MIN_tmp[2] = I_MIN_tmp[3] = 60000; // I2 ;
}

void state_init(void)
{
    IWDG_Feed(); // 喂狗
    unsigned char tim_array[8];
    N_T = 0;
    //	F_asy_sta=0;
    //	F_bsy_sta=0;
    //	F_csy_sta=0;
    key_state = 0x0000;
    F_record_write = 0;
    F_anolog_trip = 0;
    F_chonghezha = 0;
    F_Vol_Re = 0;
    F_Compare = 2;
    N_Trip = 0;
    F_Delay = 0;
    F_L_Delay = 0; // 解决上电快速动作
    F_Leak_Delay = 0;
    F_key = 0;
    N_K = 0;
    F_cd_set = 0;
    F_cal = 0;
    F_gz_disp = 0x0F;
    F_hezha_sta = 0;
    disp_status = 0;
    V_point = 1;
    F_Disp = 1;
    F_tingdian_V = 0;
    F_powerup_re = 1;
    F_Vsam_begin = 0;
    F_display = 0;
    F_Dataval = 0;
    F_Powerup = 0;
    N_Tingdian = 0;
    F_I_Lock = 0;
    T_64_200ms = 0;
    F_tingdian_fenzha = 0;
    N_I2[0] = N_I2[1] = N_I2[2] = N_I2[3] = 0;

    if (isfenzha == 0)
    {
        F_ZW = 0;
    }
    else
    {
        F_ZW = 1;
    }
    // clear_uart_sta();
    F_re_sta = 0;
    HAL_UART_Receive_IT(&huart1, (uint8_t *)tmp_uart_rx, 1);
    //	ds1302_read_time_uart(tim_array);
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
    old_day = tim_array[2];
    //	Day_factors_clear();//这里需要修改，读取当前记录就可以完成掉电最大数据不丢
}

void Cur_quick_protect(void)
{
    if ((TT_1 <= 63) && (F_Sample == 1))
    {
        Get_A_C();

        Get_B_C();

        Get_C_C();
    }
    TT_1 = TT_1 + 1;
    if ((TT_1 == 16) && (F_Sample == 0)) // 延时10ms
    {
        F_Sample = 1;
        TT_1 = 0;
    }
    if (TT_1 >= 64)
    {
        I_Array_action[0] = A_C_Sum; // 用作动作
        I_Array_action[1] = B_C_Sum;
        I_Array_action[2] = C_C_Sum;

        //				a++;
        //		if(a==3)
        //		{
        //				unsigned char arry[5];
        //				gz_disp=(I_Array_action[2]);
        //
        //				arry[4] =  (unsigned char)(gz_disp&0xff);
        //				arry[3] =  (unsigned char)((gz_disp&0xff00)>>8);
        //				arry[2] =  (unsigned char)((gz_disp&0xff0000)>>16);
        //				arry[1]=	 (unsigned char)((gz_disp&0xff0000)>>24);
        //				arry[0] = 0xFC;
        //				HAL_UART_Transmit(&huart1,(uint8_t*)arry,5,0xffff);
        ////					a=0;
        //		}

        D3_A_Quick_Process();

        D3_B_Quick_Process();

        D3_C_Quick_Process();
        TT_1 = 0;
        A_C_Sum = 0;
        B_C_Sum = 0;
        C_C_Sum = 0;
        T_64_1000ms++;
        //		if(T_64_1000ms==1) //延时40ms
        //		{
        //			F_Sample=1;
        //		}
        if (T_64_1000ms == 100)
        {
            N_B3D = 0;
            N_A3D = 0;
            N_C3D = 0;
            N_B2D = 0;
            N_A2D = 0;
            N_C2D = 0;
            T_64_1000ms = 0;
            F_quick_protect = 1;
            //				isfenzha=0;
        }
    }
}
void D3_A_Quick_Process(void)
{

    if (F_ip == 1)
    {
        N_T_TH = N_TH_DL[TH_DL];
        if (F_Over_A == 1)
        {
            F_Over_A = 0;
            N_A2D = N_A2D + 2;
            if (N_A2D >= N_T_TH)
            {
                N_A2D = 0;
                gz_reason = trip_reason_short;
                GZ_ph = 0x01;
                gz_disp = DLS_Cur; // 过点，此处应该修改
                Trip_ON;
                //	Write_Quick_Record(gz_reason,GZ_ph);
            }
        }
        else
        {
            if (N_A2D > 0)
                N_A2D = N_A2D - 1;
        }
    }
}
void D3_B_Quick_Process(void)
{

    if (F_ip == 1)
    {
        N_T_TH = N_TH_DL[TH_DL];
        if (F_Over_B == 1)
        {
            F_Over_B = 0;
            N_B2D = N_B2D + 2;
            if (N_B2D >= N_T_TH)
            {
                N_B2D = 0;
                gz_reason = trip_reason_short;
                GZ_ph = 0x02;
                gz_disp = DLS_Cur; // 过点，此处应该修改
                Trip_ON;
                //	Write_Quick_Record(gz_reason,GZ_ph);
            }
        }
        else
        {
            if (N_B2D > 0)
                N_B2D = N_B2D - 1;
        }
    }
}

void D3_C_Quick_Process(void)
{

    //	}
    if (F_ip == 1)
    {
        N_T_TH = N_TH_DL[TH_DL];
        if (F_Over_C == 1)
        {
            F_Over_C = 0;
            N_C2D = N_C2D + 2;
            if (N_C2D >= N_T_TH)
            {
                N_C2D = 0;
                gz_reason = trip_reason_short;
                GZ_ph = 0x03;
                gz_disp = DLS_Cur; // 过点，此处应该修改
                Trip_ON;
                //	Write_Quick_Record(gz_reason,GZ_ph);
            }
        }
        else
        {
            if (N_C2D > 0)
                N_C2D = N_C2D - 1;
        }
    }
    // if (F_ip == 1)
    //    {
    //        //		  I2_1=(I2*7>>3)+(I2>>5);//0.9倍
    //        N_T_TH = N_TH_DL[TH_DL];
    //        if ((cur_handle_C(I_Array_action[2])) >= I2)
    //        {
    //            N_C2D = N_C2D + 2;
    //            if (N_C2D >= N_T_TH) // 一个周期12个点及认为应该动作
    //            {
    //                N_C2D = 0;
    //                gz_reason = trip_reason_short;
    //                GZ_ph = 0x04;
    //                gz_disp = (cur_handle_C(I_Array_action[2])); // 过点，此处应该修改
    //                Trip_ON;
    //                //				Write_Quick_Record(gz_reason,GZ_ph);
    //            }
    //        }
    //        else
    //        {
    //        }
    //    }
}

void Power_Sample_A(void)
{
    I_A_Sum = 0;
    AD_tmp_V_Power[0] = 0;
    AD_tmp_V_Power_Zero[0] = 0;
    AD_tmp_V_Power[0] = ADC_ConvertedValue[4] - ADC_ConvertedValue[7]; // 电压采集
    AD_tmp_V_Power_Zero[0] = AD_tmp_V_Power[0];                        // 过零点数据采集处理
    /**********电压***********/
    if (AD_tmp_V_Power[0] < 0) // 电压去绝对值
    {
        AD_tmp_V_Power[0] = -AD_tmp_V_Power[0];
    }
    else
    {
        AD_tmp_V_Power[0] = AD_tmp_V_Power[0];
    }

    /*******************电流************************************/
    for (int I_Count = 0; I_Count < 2; I_Count++)
    {
        AD_tmp_I_Power[0] = 0;
        AD_tmp_I_Power[0] = ADC_ConvertedValue[1]; // 电流采集
        //		AD_tmp_I_Power[0]=200;//电流采集
        I_A_Sum += AD_tmp_I_Power[0];
    }
    AD_tmp_Power[0] = I_A_Sum >> 1;
    A_C_Sum += I_A_Sum >> 1;
    if (isfenzha != 0) // 在合闸位置
    {
        if (F_ip_3 == 1)
        {

            if (AD_tmp_Power[0] >= Over_Value) // Over_Value不同档位等于不同值
            {

                N_SD_A = N_SD_A + 2;
                if (N_SD_A >= 10)
                {
                    {
                        F_ch = 0;
                        Record_data_propare();                            // 把要写入的漏电，电压，电流值准备好以写入
                        gz_disp = cur_actionhandle_A(I_Array_xianshi[0]); // 过点，此处应该修改
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_3D_cur;
                        F_record_write = 1;
                        F_3d_trip = 1;
                        // putchar(gz_reason);
                        GZ_ph = 1;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl;
                        if (F_ia == 1) // F_ia  漏电重合闸标志位
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // 如果漏电重合闸功能开
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // 直接置3
                            F_I_Lock = 1;
                        }
                        // 否则不再重合闸
                    }
                    // 连续第二次脱扣
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 999; // 过点，此处应该修改
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }

                        F_record_write = 1;
                        gz_reason = trip_reason_3D_cur;
                        // putchar(gz_reason);
                        GZ_ph = 1;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;

                        F_gz_disp = A_gl;

                        // 写过流跳闸记录
                    }
                }
            }
            else
            {
                if (N_SD_A >= 1)
                    N_SD_A = N_SD_A - 1;
            }
        }
        if (F_ip == 1)
        {
            N_T_TH = N_TH_DL[TH_DL];
            if (AD_tmp_Power[0] >= Over_Value_duanyan) // Over_Value不同档位等于不同值
            {

                N_DY_A = N_DY_A + 2;

                if (N_DY_A >= N_T_TH)
                {
                    {
                        F_ch = 0;
                        Record_data_propare();                      // 把要写入的漏电，电压，电流值准备好以写入
                        gz_disp = cur_handle_A(I_Array_xianshi[0]); // 过点，此处应该修改
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_short;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 1;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl;
                        if (F_ia == 1) // F_ia  漏电重合闸标志位
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // 如果漏电重合闸功能开
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // 直接置3
                            F_I_Lock = 1;
                        }
                        // 否则不再重合闸
                    }
                    // 连续第二次脱扣
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 997; // 过点，此处应该修改
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }

                        F_record_write = 1;
                        gz_reason = trip_reason_short;
                        // putchar(gz_reason);
                        GZ_ph = 1;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;

                        F_gz_disp = A_gl;

                        // 写过流跳闸记录
                    }
                }
            }
            else
            {
                if (N_DY_A >= 1)
                    N_DY_A = N_DY_A - 1;
            }
        }
    }
    //		for(int I_Count=0;I_Count<2;I_Count++)
    //	{
    //		AD_tmp_I_PowerA[I_Count]=ADC_ConvertedValue[1];
    //	}
    //	if(AD_tmp_I_PowerA[1]>4*AD_tmp_I_PowerA[0])//如果后一个点大于前一个点4倍就赋值前一个点
    //	{
    //		AD_tmp_I_PowerA[1]=AD_tmp_I_PowerA[0];
    //	}
    //	else
    //	{
    //		AD_tmp_I_PowerA[1]=AD_tmp_I_PowerA[1];
    //	}
    //	I_A_Sum=AD_tmp_I_PowerA[0]+AD_tmp_I_PowerA[1];
    //	AD_tmp_Power[0]=I_A_Sum>>1;
    //	A_C_Sum+=I_A_Sum>>1;
}
void Power_Sample_B(void)
{
    I_B_Sum = 0;
    AD_tmp_V_Power[1] = 0;
    AD_tmp_V_Power_Zero[1] = 0;
    AD_tmp_V_Power[1] = ADC_ConvertedValue[5] - ADC_ConvertedValue[7];
    AD_tmp_V_Power_Zero[1] = AD_tmp_V_Power[1]; // 过零点数据采集处理
    /*****************电压******************/
    if (AD_tmp_V_Power[1] < 0)
    {
        AD_tmp_V_Power[1] = -AD_tmp_V_Power[1];
    }
    else
    {
        AD_tmp_V_Power[1] = AD_tmp_V_Power[1];
    }

    /*******************电流*******************/
    for (int I_Count = 0; I_Count < 2; I_Count++)
    {
        AD_tmp_I_Power[1] = 0;
        AD_tmp_I_Power[1] = ADC_ConvertedValue[2];
        I_B_Sum += AD_tmp_I_Power[1];
    }
    AD_tmp_Power[1] = I_B_Sum >> 1;
    B_C_Sum += I_B_Sum >> 1;
    if (isfenzha != 0) // 在合闸位置
    {
        if (F_ip_3 == 1)
        {

            if (AD_tmp_Power[1] >= Over_Value) // Over_Value不同档位等于不同值
            {

                N_SD_B = N_SD_B + 2;
                if (N_SD_B >= 10)
                {
                    {
                        F_ch = 0;
                        Record_data_propare();                            // 把要写入的漏电，电压，电流值准备好以写入
                        gz_disp = cur_actionhandle_B(I_Array_xianshi[1]); // 过点，此处应该修改
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_3D_cur;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 2;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl + 1;
                        if (F_ia == 1) // F_ia  漏电重合闸标志位
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // 如果漏电重合闸功能开
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // 直接置3
                            F_I_Lock = 1;
                        }
                        // 否则不再重合闸
                    }
                    // 连续第二次脱扣
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 999; // 过点，此处应该修改
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        F_record_write = 1;
                        gz_reason = trip_reason_3D_cur;
                        // putchar(gz_reason);
                        GZ_ph = 2;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_gz_disp = A_gl + 1;

                        // 写过流跳闸记录
                    }
                }
            }
            else
            {
                if (N_SD_B >= 1)
                    N_SD_B = N_SD_B - 1;
            }
        }
        if (F_ip == 1)
        {

            N_T_TH = N_TH_DL[TH_DL];
            if (AD_tmp_Power[1] >= Over_Value_duanyan) // Over_Value不同档位等于不同值
            {

                N_DY_B = N_DY_B + 2;
                if (N_DY_B >= N_T_TH)
                {
                    if (F_I_STA == 0)
                    {
                        F_ch = 0;
                        Record_data_propare();                      // 把要写入的漏电，电压，电流值准备好以写入
                        gz_disp = cur_handle_B(I_Array_xianshi[1]); // 过点，此处应该修改
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_short;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 2;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl + 1;
                        if (F_ia == 1) // F_ia  漏电重合闸标志位
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // 如果漏电重合闸功能开
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // 直接置3
                            F_I_Lock = 1;
                        }
                        // 否则不再重合闸
                    }
                    // 连续第二次脱扣
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 997; // 过点，此处应该修改
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        F_record_write = 1;
                        gz_reason = trip_reason_short;
                        // putchar(gz_reason);
                        GZ_ph = 2;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_gz_disp = A_gl + 1;

                        // 写过流跳闸记录
                    }
                }
            }
            else
            {
                if (N_DY_B >= 1)
                    N_DY_B = N_DY_B - 1;
            }
        }
    }
}

void Power_Sample_C(void)
{
    I_C_Sum = 0;
    AD_tmp_V_Power[2] = 0;
    AD_tmp_V_Power_Zero[2] = 0;
    AD_tmp_V_Power[2] = ADC_ConvertedValue[6] - ADC_ConvertedValue[7];
    AD_tmp_V_Power_Zero[2] = AD_tmp_V_Power[2]; // 过零点数据采集处理

    if (AD_tmp_V_Power[2] < 0)
    {
        AD_tmp_V_Power[2] = -AD_tmp_V_Power[2];
    }
    else
    {
        AD_tmp_V_Power[2] = AD_tmp_V_Power[2];
    }

    /**************电流***************************/
    for (int I_Count = 0; I_Count < 2; I_Count++) // 滤波
    {
        AD_tmp_I_Power[2] = 0;
        AD_tmp_I_Power[2] = ADC_ConvertedValue[3];
        I_C_Sum += AD_tmp_I_Power[2];
    }
    AD_tmp_Power[2] = I_C_Sum >> 1;
    C_C_Sum += I_C_Sum >> 1;
    if (isfenzha != 0) // 在合闸位置
    {
        if (F_ip_3 == 1)
        {

            if (AD_tmp_Power[2] >= Over_Value) // Over_Value不同档位等于不同值
            {

                N_SD_C = N_SD_C + 2;
                if (N_SD_C >= 10)
                {
                    {
                        F_ch = 0;
                        Record_data_propare();                            // 把要写入的漏电，电压，电流值准备好以写入
                        gz_disp = cur_actionhandle_C(I_Array_xianshi[2]); // 过点，此处应该修改
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_3D_cur;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 3;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl + 2;
                        if (F_ia == 1) // F_ia  漏电重合闸标志位
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // 如果漏电重合闸功能开
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // 直接置3
                            F_I_Lock = 1;
                        }
                        // 否则不再重合闸
                    }
                    // 连续第二次脱扣
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 999; // 过点，此处应该修改
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }

                        F_record_write = 1;
                        gz_reason = trip_reason_3D_cur;
                        // putchar(gz_reason);
                        GZ_ph = 3;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_gz_disp = A_gl + 2;

                        // 写过流跳闸记录
                    }
                }
            }
            else
            {
                if (N_SD_C >= 1)
                    N_SD_C = N_SD_C - 1;
            }
        }
        if (F_ip == 1)
        {
            N_T_TH = N_TH_DL[TH_DL];
            if (AD_tmp_Power[2] >= Over_Value_duanyan) // Over_Value不同档位等于不同值
            {

                N_DY_C = N_DY_C + 2;
                if (N_DY_C >= N_T_TH)
                {

                    if (F_I_STA == 0)
                    {
                        F_ch = 0;
                        Record_data_propare();                      // 把要写入的漏电，电压，电流值准备好以写入
                        gz_disp = cur_handle_C(I_Array_xianshi[2]); // 过点，此处应该修改
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }
                        gz_reason = trip_reason_short;
                        F_record_write = 1;
                        // putchar(gz_reason);
                        GZ_ph = 3;
                        // Write_Record(trip_reason_cur,(i+1));
                        F_gz_disp = A_gl + 2;
                        if (F_ia == 1) // F_ia  漏电重合闸标志位
                        {
                            F_I_STA = 1;
                            F_ch = 0;
                            F_I_Lock = 0;
                        }
                        // 如果漏电重合闸功能开
                        else
                        {
                            F_ch = 1;
                            F_I_STA = 3; // 直接置3
                            F_I_Lock = 1;
                        }
                        // 否则不再重合闸
                    }
                    // 连续第二次脱扣
                    if (F_I_STA == 2)
                    {
                        F_ch = 1;
                        gz_disp = 997; // 过点，此处应该修改
                        Record_data_propare();
                        // if(F_trip_gl==1)
                        {
                            Trip_Action();
                        }

                        F_record_write = 1;
                        gz_reason = trip_reason_short;
                        // putchar(gz_reason);
                        GZ_ph = 3;
                        // Write_Record(trip_reason_cur,1);
                        F_I_STA = 3;
                        F_I_Lock = 1;
                        F_gz_disp = A_gl + 2;
                    }
                }
            }
            else
            {
                if (N_DY_C >= 1)
                    N_DY_C = N_DY_C - 1;
            }
        }
    }
    //		for(int I_Count=0;I_Count<2;I_Count++)
    //	{
    //		AD_tmp_I_PowerC[I_Count]=ADC_ConvertedValue[3];
    //	}
    //	if(AD_tmp_I_PowerC[1]>4*AD_tmp_I_PowerC[0])//如果后一个点大于前一个点4倍就赋值前一个点
    //	{
    //		AD_tmp_I_PowerC[1]=AD_tmp_I_PowerC[0];
    //	}
    //	else
    //	{
    //		AD_tmp_I_PowerC[1]=AD_tmp_I_PowerC[1];
    //	}
    //	I_C_Sum=AD_tmp_I_PowerC[0]+AD_tmp_I_PowerC[1];
    //	AD_tmp_Power[2]=I_C_Sum>>1;
    //	C_C_Sum+=I_C_Sum>>1;
}

// 定时器3中断服务程序
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // TIM3中断
{
    if (htim->Instance == htim6.Instance) // 检查TIM3更新中断发生与否
    {
        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);//实现晶振损坏后可以正常工作程序，删这句不行？
        HAL_ADCEx_Calibration_Start(&hadc);
        HAL_ADC_Start_DMA(&hadc, ADC_ConvertedValue, 8);
        u16 AD_Vol_Check;
        if (F_quick_protect == 0) // 上电电流快速保护
        {
            Cur_quick_protect();
        }
        else
        {
            AD_Vol_Check = ADC_ConvertedValue[7];

            //				if((F_trip_sy==1)&&(T_delay>=150))
            //				{
            //				low_vol_prcoess();

            //				}
            //			 if(duandian==1)
            //			 {
            if ((F_trip_sy == 1) && (D_SY_yanshi == 0))
            {
                if (AD_Vol_Check < 150)
                {
                    N_Tingdian = N_Tingdian + 2;
//                    if (N_Tingdian >= 60)
//                    {
//                        if (isfenzha != 0)
//                        {
//                            Trip_ON;
//                            write_tingdian();
//                            N_Tingdian = 0;
//                        }
//                    }
                }
                else
                {
                    N_Tingdian = N_Tingdian - 2;
                    if (N_Tingdian <= 0)
                    {
                        N_Tingdian = 0;
                    }
                }
            }

            //		}
            if (T <= 63)
            {
                if (F_Vsam_begin == 1)
                {
                    if ((TT >= 0) && (TT <= 63)) // 改动  2017.12.29
                    {
                        V_Sample_A();

                        V_Sample_B();

                        V_Sample_CC();

                        TT = TT + 1;
                    }
                    if (TT >= 64)
                    {
                        F_V_AD++;
                        A_V_Sum_disp += A_V_Sum1;
                        B_V_Sum_disp += B_V_Sum1;
                        C_V_Sum_disp += C_V_Sum1;
                        if (F_V_AD >= 32)
                        {
                            F_V_AD = 0;
                            V_Array_disp[0] = A_V_Sum_disp >> 5;
                            V_Array_disp[1] = B_V_Sum_disp >> 5;
                            V_Array_disp[2] = C_V_Sum_disp >> 5;
                            A_V_Sum_disp = 0;
                            B_V_Sum_disp = 0;
                            C_V_Sum_disp = 0;
                        }
                        V_Array[0] = A_V_Sum1;
                        V_Array[1] = B_V_Sum1;
                        V_Array[2] = C_V_Sum1;
                        if ((vol_handle_A(V_Array[0]) <= 90) && (vol_handle_B(V_Array[1]) <= 90) && (vol_handle_C(V_Array[2]) <= 90))
                        {
                            if ((F_trip_sy == 1) && (D_SY_yanshi == 0))
                            {
                                if (isfenzha != 0)
                                {
                                    // Trip_ON;
                                    //low_vol_trip(2);
                                    //write_tingdian();
                                }
                            }
                        }
                        AQL_Judge_tmp = A_V_Sum1 * 100 / AD_tmp_VA_Max;
                        BQL_Judge_tmp = B_V_Sum1 * 100 / AD_tmp_VB_Max;
                        CQL_Judge_tmp = C_V_Sum1 * 100 / AD_tmp_VC_Max;
                        A_V_Sum1 = 0;
                        B_V_Sum1 = 0;
                        C_V_Sum1 = 0;
                        AD_tmp_VA_Max = 0;
                        AD_tmp_VB_Max = 0;
                        AD_tmp_VC_Max = 0;
                        TT = 0;
                    }
                }

                Power_Sample_A();
                Power_Sample_B();
                Power_Sample_C();
                // 第一步数据采集处理
                if ((Samp_start_end_flag == 0) && (F_Delay == 1))
                {

                    if (Re_point_VA < 70) // 计量相位调整64采样点数据准备
                    {

                        Zhou_bo_UA[Re_point_VA] = AD_tmp_V_Power_Zero[0]; // 电压A 200采样点
                        Zhou_bo_UB[Re_point_VA] = AD_tmp_V_Power_Zero[1]; // 电压B 200采样点
                        Zhou_bo_UC[Re_point_VA] = AD_tmp_V_Power_Zero[2]; // 电压C 200采样点

                        Zhou_bo_IA[Re_point_VA] = AD_tmp_Power[0]; // 电流A 200采样点
                        Zhou_bo_IB[Re_point_VA] = AD_tmp_Power[1]; // 电流B 200采样点
                        Zhou_bo_IC[Re_point_VA] = AD_tmp_Power[2]; // 电流C 200采样点
                        Re_point_VA++;
                    }

                    else
                    {
                        Samp_start_end_flag = 1; // 标志位为1为200点采集结束
                        Re_point_VA = 0;
                    }
                }
                Get_L();
                Switch_pos_judge();
                Flag_Updata();
                if (T == 32)
                {
                    if ((F_hezha_state == 1) && (isfenzha != 0)) // 合闸成功
                    {
                        F_hezha_state = 0;
                        F_hezha_delay = 1;
                        F_ZW = 1;
                        F_gz = 0x00;
                        F_gz_disp = 0x0F;
                        F_disp_h = 0;
                        F_Dataval = 0;
                        F_guocheng = 0;
                        F_hezha_sta = 0;
                        F_Disp = 1;
                        F_initial_lcd_hezha = 1;
                    }
                    if ((F_fenzha_state == 1) && (isfenzha == 0)) // 分闸成功
                    {
                        stop;
                        F_disp_tr = 0;
                        F_fenzha_state = 0;
                        F_ZW = 0;
                        F_guocheng = 0;
                        N_fenzha_time = 0;
                        F_Disp = 1;
                        key_state = 0;
                    }
                    if (LEDA_FLAG == 1)
                    {
                        if (Lcd_Count <= 3000)
                            Lcd_Count++;
                        else
                        {
                            LEDA_OFF;
                            LEDA_FLAG = 0;
                            Lcd_Count = 0;
                        }
                    }
                    Conter_Updata(); // 每10ms一次
                }
                // #if type_125   //打开了这个开关，目前不只有125壳架需要这种方式的按键试跳
                if (F_anolog_trip == 1) // 20230404按键试跳
                {

                    if ((T == 1) || (T == 9) || (T == 17) || (T == 25) || (T == 33) || (T == 41) || (T == 49) || (T == 57) || (T == 63))
                    // if((T==2)||(T==8)||(T==14)||(T==20)||(T==26)||(T==32)||(T==38)||(T==44)||(T==50)||(T==56)||(T==62))
                    {
                        Test_start;
                        // 7 Test_stop;
                        T_wave = T_wave + 1;
                    }
                    if ((T == 3) || (T == 11) || (T == 19) || (T == 27) || (T == 35) || (T == 43) || (T == 51) || (T == 59))
                    // if((T==4)||(T==10)||(T==16)||(T==22)||(T==28)||(T==34)||(T==40)||(T==46)||(T==52)||(T==58)||(T==63))
                    {
                        Test_stop;
                        // Test_start;
                        if (isfenzha == 0) // mrnow
                        {
                            T_wave = 1601;
                        }
                    }
                    if (T_wave >= 1600) // 控制每次按下试跳按键产生的波形为10秒//YJK左右mrnow
                    {
                        T_wave = 0;
                        // Test_stop;

                        Test_start;
                        F_anolog_trip = 0;
                    }
                }
                // #else

                // #endif
                //				if(F_anolog_trip==1)//20230404按键试跳
                //				{

                //					if((T==1)||(T==9)||(T==17)||(T==25)||(T==33)||(T==41)||(T==49)||(T==57)||(T==63))
                //					//if((T==2)||(T==8)||(T==14)||(T==20)||(T==26)||(T==32)||(T==38)||(T==44)||(T==50)||(T==56)||(T==62))
                //					{
                //					  // Test_start;
                //						//7 Test_stop;
                //						 T_wave=T_wave+1;
                //					}
                //					if((T==3)||(T==11)||(T==19)||(T==27)||(T==35)||(T==43)||(T==51)||(T==59))
                //					//if((T==4)||(T==10)||(T==16)||(T==22)||(T==28)||(T==34)||(T==40)||(T==46)||(T==52)||(T==58)||(T==63))
                //					{
                ////					   Test_stop;
                //						//Test_start;
                //						  if(isfenzha == 0) //mrnow
                //							{
                //							  T_wave = 1601;
                //							}
                //					}
                //					 if(T_wave>=1600)//控制每次按下试跳按键产生的波形为10秒//YJK左右mrnow
                //					 {
                //					    T_wave=0;
                //						  //Test_stop;
                //
                //						// Test_start;
                //						 F_anolog_trip = 0;
                //					 }

                //				}

                T = T + 1;

                if (T >= 64)
                {
                    F_V_Array_Flag = 1;
                    if (F_Leak_Delay == 1)
                    {
                        F_L_AD++;
                        Leak_xianshi_sum += Leak_Cur_Sum;
                        if (F_L_AD >= 16)
                        {
                            F_L_AD = 0;
                            Leak_xianshi_disp = Leak_xianshi_sum >> 4;
                            Leak_xianshi_sum = 0;
                        }
                        Leak_Cur_disp_temp = Leak_Cur_Sum;
                        Leak_process();
                    }

                    F_C_AD++;
                    A_C_Sum_disp += A_C_Sum;
                    B_C_Sum_disp += B_C_Sum;
                    C_C_Sum_disp += C_C_Sum;
                    if (F_C_AD >= 64)
                    {
                        I_I_Array_xianshi[0] = A_C_Sum_disp >> 6;
                        I_I_Array_xianshi[1] = B_C_Sum_disp >> 6;
                        I_I_Array_xianshi[2] = C_C_Sum_disp >> 6;
                        A_C_Sum_disp = 0;
                        B_C_Sum_disp = 0;
                        C_C_Sum_disp = 0;
                        F_C_AD = 0;
                    }
                    I_Array_xianshi[0] = A_C_Sum; // 用作动作
                    I_Array_xianshi[1] = B_C_Sum;
                    I_Array_xianshi[2] = C_C_Sum;

                    //					CurA_cal_tmp[0]=I_I_Array_xianshi[0];//A1
                    //					CurB_cal_tmp[0]=I_I_Array_xianshi[1];//B1
                    //					CurC_cal_tmp[0]=I_I_Array_xianshi[2];//C1
                    //
                    //					CurA_cal_tmp[1]=I_I_Array_xianshi[0];//A2
                    //					CurB_cal_tmp[1]=I_I_Array_xianshi[1];//B2
                    //					CurC_cal_tmp[1]=I_I_Array_xianshi[2];//C2

                    // D3_A_BH_Process();
                    // D3_B_BH_Process();
                    // D3_C_BH_Process();
                    Num_Cur_protect++;
                    if (Num_Cur_protect >= 5) // 每100ms过载长延时动作比较处理。
                    {
                        Num_Cur_protect = 0;
                        F_Cur = 10;
                    }
                    A_C_Sum = 0;
                    B_C_Sum = 0;
                    C_C_Sum = 0;
                    T = 0;
                }
            }
        }
    }
}

void Lackzero_judge(void)
{
    //	QL_A_tmp=((A_V_Sum1*V_A_slope[0])>>10)/AD_tmp_VA_Max;

    if ((V_Diferent >= 30) && (V_tmp_MAX >= 240)) // 50    245
    {

        N_QL_A = N_QL_A + 2;
        if (N_QL_A >= 40)
        {
            F_QLA_TRIP = 1;
            N_QL_A = 0;
        }
    }
    else
    {
        N_QL_A--;
        F_QLA_TRIP = 0;
        if (N_QL_A < 0)
            N_QL_A = 0;
    }
    //	if((V_Diferent>=60)&&(V_tmp_MAX>=270)&&(V_tmp_MIN<=218))
    if ((V_Diferent >= 30) && (V_tmp_MAX >= 240))
    {

        N_QL_B = N_QL_B + 2;
        if (N_QL_B >= 40)
        {
            F_QLB_TRIP = 1;
            N_QL_B = 0;
        }
    }
    else
    {
        N_QL_B--;
        F_QLB_TRIP = 0;
        if (N_QL_B < 0)
            N_QL_B = 0;
    }
    //	if((V_Diferent>=60)&&(V_tmp_MAX>=270)&&(V_tmp_MIN<=218))
    if ((V_Diferent >= 30) && (V_tmp_MAX >= 240))
    {

        N_QL_C = N_QL_C + 2;
        if (N_QL_C >= 40)
        {
            F_QLC_TRIP = 1;
            N_QL_C = 0;
        }
    }
    else
    {
        N_QL_C--;
        F_QLC_TRIP = 0;
        if (N_QL_C < 0)
            N_QL_C = 0;
    }
}
// 运行时间
void Run_time_process(void)
{
    IWDG_Feed();         // 喂狗
    if (F_run_time == 1) // 运行总时间 1min
    {
        F_run_time = 0;
        Sum_run_time = Sum_run_time + 1;
        if (Sum_run_time > 99999999)
        {
            Sum_run_time = 0;
        }
        DectoBCD(T_run_time_array, Sum_run_time, 4);
        MODIFY_EEP_W(Addr_protect_time, T_run_time_array, 4, 0xA0);
        IWDG_Feed(); // 喂狗
    }
}

void uart_com_process(void)
{

    unsigned char sta;
    // 串口处理
    if (F_Dataval == 1)
    {
        RS485_TX_EN; // 设置为发送模式
        delay_ms(5);
        sta = frame_check();
        F_debug = 1;
        if (sta == 0)
        {
            UART_process();
        }
        F_Dataval = 0;
        //		clear_uart_sta();
        delay_ms(5);
        delay_ms(5);
        RS485_RX_EN; // 设置为接收模式
    }
}

unsigned char read_tingdian(void)
{
    unsigned char tmp, tingdian[2];
    EEPROM_R(Addr_tingdian, tingdian, 1, 0xA0);
    tmp = tingdian[0];
    tingdian[0] = 0x00;
    return tmp;
}
void clear_tingdian(void)
{
    unsigned char tingdian[2];
    tingdian[0] = 0x00;
    MODIFY_EEP_W(Addr_tingdian, tingdian, 1, 0xA0);
}

void long_process(void)
{
    if (cui == 1 && ((key_state >= 0x25100) && (key_state <= 0x25FFF))) // 过流档位长按加
    {
        unsigned int temp_state_value_1;
        T_64_10s = 0;
        if (Type_Cur_change == 1)
        {
            if (Type_Cur == 0) // 过流档位
            {
                temp_state_value_1 = 0x4C;
            }
            else if (Type_Cur == 1)
            {
                temp_state_value_1 = 0xBC;
            }
            else if (Type_Cur == 2)
            {
                temp_state_value_1 = 0xF1;
            }
            else if (Type_Cur == 3)
            {
                temp_state_value_1 = 0x17B;
            }
            else if (Type_Cur == 4)
            {
                temp_state_value_1 = 0x1E1;
            }
            else
            {
                Type_Cur = 1;
                temp_state_value_1 = 0xBC;
            }
        }

        tiaozheng_key_state(0x25100, temp_state_value_1, 1); // 档位选择
        HAL_Delay(50);
        Fun_OP_Val();
    }

    // ((key_state>=0x23100)&&(key_state<=0x231FF))
    else if (cui == 1 && ((key_state >= 0x23100) && (key_state <= 0x231FF))) // 过压长按加
    {
        T_64_10s = 0;
        tiaozheng_key_state(0x23100, 0x33, 1); // 过压档位
        HAL_Delay(70);
        Fun_GY_Val();
    }
    else if (cui == 1 && ((key_state >= 0x24100) && (key_state <= 0x241FF))) // 欠压长按加
    {
        T_64_10s = 0;

        tiaozheng_key_state(0x24100, 0x33, 1);
        HAL_Delay(70);
        Fun_QY_Val();
    }
    else if (cui == 2 && ((key_state >= 0x25100) && (key_state <= 0x25FFF)))
    {
        T_64_10s = 0;
        unsigned int temp_state_value_1;
        if (Type_Cur_change == 1)
        {
            if (Type_Cur == 0) // 过流档位
            {
                temp_state_value_1 = 0x4C;
            }
            else if (Type_Cur == 1)
            {
                temp_state_value_1 = 0xBC;
            }
            else if (Type_Cur == 2)
            {
                temp_state_value_1 = 0xF1;
            }
            else if (Type_Cur == 3)
            {
                temp_state_value_1 = 0x17B;
            }
            else if (Type_Cur == 4)
            {
                temp_state_value_1 = 0x1E1;
            }
            else
            {
                Type_Cur = 1;
                temp_state_value_1 = 0xBC;
            }
        }

        tiaozheng_key_state(0x25100, temp_state_value_1, 0); // 档位选择
        HAL_Delay(50);
        Fun_OP_Val();
    }
    else if (cui == 2 && ((key_state >= 0x23100) && (key_state <= 0x231FF))) // 过压长按减
    {
        T_64_10s = 0;
        tiaozheng_key_state(0x23100, 0x33, 0); // 过压档位
        HAL_Delay(70);
        Fun_GY_Val();
    }
    else if (cui == 2 && ((key_state >= 0x24100) && (key_state <= 0x241FF)))
    {
        T_64_10s = 0;
        tiaozheng_key_state(0x24100, 0x33, 0);
        HAL_Delay(70);
        Fun_QY_Val();
    }

    IWDG_Feed(); // 喂狗
    long_key_temp = get_key();
    if (long_key_temp != 0)
    {
        //		if(F_Corr==0)
        //		{
        N_key_temp++;
        if ((N_key_temp > 100) && (long_key_temp != 0x07))
        {
            //				if(F_Corr==0)
            {
                long_key_process(long_key_temp);
                N_key_temp = 0;
            }
        }
        //	  }
        //		if((N_key_temp>120)&&(long_key_temp==0x07))//进入程序复位下载需要时间更长
        //		{
        //			long_key_process(long_key_temp);
        //			N_key_temp = 0;
        //		}
    }
    if (long_key_temp == 0)
    {
        cui = 0;
        N_key_temp = N_key_temp - 2;
        if (N_key_temp < 0)
        {

            N_key_temp = 0;
        }
    }
}

void Get_A_C(void)
{
    AD_tmp = 0;
    AD_tmp = ADC_ConvertedValue[1];
    A_C_Sum = A_C_Sum + AD_tmp;

    if (F_ip_3 == 1)
    {
        if (AD_tmp >= Over_Value) // Over_Value不同档位等于不同值
        {

            N_SD_A = N_SD_A + 2;
            if (N_SD_A >= 10)
            {
                N_SD_A = 0;
                gz_reason = trip_reason_3D_cur;
                gz_disp = DLS_Cur; // 过点，此处应该修改
                GZ_ph = 0x01;
                Trip_ON;
                ;
            }
        }
        else
        {
            if (N_SD_A >= 1)
                N_SD_A = N_SD_A - 1;
        }
    }
    //		if(F_ip==1)
    //	{
    //			N_T_TH = N_TH_DL[TH_DL];
    //			if(AD_tmp>=Over_Value_duanyan)//Over_Value不同档位等于不同值
    //			{
    //					N_DY_A = N_DY_A + 2;
    //					if(N_DY_A>=N_T_TH)  //连续超过三个点，记录
    //					{
    //
    //								N_DY_A=0;
    //								gz_reason=trip_reason_short;
    //								GZ_ph = 0x01;
    //								gz_disp=DLS_Cur;//(cur_handle_A(I_Array_action[0]));//过点，此处应该修改
    //								Trip_Action();
    //			//					Write_Quick_Record(gz_reason,GZ_ph);
    //					}
    //			}
    //
    ////			else
    ////			{
    ////				if(N_DY_A>=1)
    ////				N_DY_A = N_DY_A-1;
    ////			}
    //
    //
    //  }
    if (F_ip == 1)
    {

        if (AD_tmp >= Over_Value_duanyan) // Over_Value不同档位等于不同值
        {
            N_DY_A = N_DY_A + 2;
            if (N_DY_A >= 5) // 连续超过三个点，记录
            {

                N_DY_A = 0;
                F_Over_A = 1;
                //								gz_reason=trip_reason_short;
                //								GZ_ph = 0x01;
                //								gz_disp=DLS_Cur;//(cur_handle_A(I_Array_action[0]));//过点，此处应该修改
                //								Trip_Action();
            }
        }
        else
        {
            if (N_DY_A >= 1)
                N_DY_A = N_DY_A - 1;
        }
    }
}
void Get_B_C(void)
{
    AD_tmp = 0;
    AD_tmp = ADC_ConvertedValue[2];
    B_C_Sum = B_C_Sum + AD_tmp;

    if (F_ip_3 == 1)
    {
        if (AD_tmp >= Over_Value) // Over_Value不同档位等于不同值
        {

            N_SD_B = N_SD_B + 2;
            if (N_SD_B >= 10)
            {
                N_SD_B = 0;
                gz_reason = trip_reason_3D_cur;
                gz_disp = DLS_Cur; // 过点，此处应该修改
                GZ_ph = 0x02;
                Trip_ON;
                ;
            }
        }
        else
        {
            if (N_SD_B >= 1)
                N_SD_B = N_SD_B - 1;
        }
    }
    if (F_ip == 1)
    {

        if (AD_tmp >= Over_Value_duanyan) // Over_Value不同档位等于不同值
        {
            N_DY_B = N_DY_B + 2;
            if (N_DY_B >= 7) // 连续超过三个点，记录
            {

                N_DY_B = 0;
                F_Over_B = 1;
                //								gz_reason=trip_reason_short;
                //								GZ_ph = 0x02;
                //								gz_disp=DLS_Cur;//(cur_handle_A(I_Array_action[0]));//过点，此处应该修改
                //								Trip_Action();
            }
        }
        else
        {
            if (N_DY_B >= 1)
                N_DY_B = N_DY_B - 1;
        }
    }
}

void Get_C_C(void)
{
    AD_tmp = 0;
    AD_tmp = ADC_ConvertedValue[3];
    C_C_Sum = C_C_Sum + AD_tmp;

    if (F_ip_3 == 1)
    {
        if (AD_tmp >= Over_Value) // Over_Value不同档位等于不同值
        {

            N_SD_C = N_SD_C + 2;
            if (N_SD_C >= 10)
            {
                N_SD_C = 0;
                gz_reason = trip_reason_3D_cur;
                gz_disp = DLS_Cur; // 过点，此处应该修改
                GZ_ph = 0x02;
                Trip_ON;
                ;
            }
        }
        else
        {
            if (N_SD_C >= 1)
                N_SD_C = N_SD_C - 1;
        }
    }
    if (F_ip == 1)
    {

        if (AD_tmp >= Over_Value_duanyan) // Over_Value不同档位等于不同值
        {
            N_DY_C = N_DY_C + 2;
            if (N_DY_C >= 5) // 连续超过三个点，记录
            {

                N_DY_C = 0;
                F_Over_C = 1;
                //								gz_reason=trip_reason_short;
                //								GZ_ph = 0x03;
                //								gz_disp=DLS_Cur;//(cur_handle_A(I_Array_action[0]));//过点，此处应该修改
                //								Trip_Action();
            }
        }
        else
        {
            if (N_DY_C >= 1)
                N_DY_C = N_DY_C - 1;
        }
    }
}

void DW_3D_E2_read(void)
{
    IWDG_Feed(); // 喂狗
    unsigned char array_temp[26];

    // 保护功能*********************/
    EEPROM_R(Addr_I_2d, array_temp, 1, 0xA0);
    F_ip = array_temp[0];
    EEPROM_R(Addr_I_3d, array_temp, 1, 0xA0); // 17.6.21改
    F_ip_3 = array_temp[0];
    /*******************控制字，电流档位，壳架等级，过欠压档位*********************/
    EEPROM_R(Addr_crtl_word1, ctrlword, 5, 0xA0); // 读5个控制字
    //	delay_ms(5);
    ctrlword4_analyze();
    EEPROM_R(Addr_DD_LL, array_temp, 1, 0xA0);
    F_DD_L[0] = array_temp[0];
    if (F_DD_L[0] == 1)
    {
        F_trip_ld = 0;
        ctrlword[3] &= 0xFC;
        MODIFY_EEP_W(Addr_crtl_word4, &ctrlword[3], 1, 0xA0);
        ctrlword4_analyze();
        F_DD_L[0] = 0;
    }
    else
    {
        F_DD_L[0] = 0;
    }
    MODIFY_EEP_W(Addr_DD_LL, F_DD_L, 1, 0xA0);
    EEPROM_R(Addr_D_Cur, array_temp, 2, 0xA0);
    D_Cur = (array_temp[0] << 8) + (array_temp[1]);
    EEPROM_R(Addr_D2_Cur, array_temp, 1, 0xA0);
    D2_Cur = array_temp[0];
    EEPROM_R(Addr_D3_Cur, array_temp, 1, 0xA0);
    D3_Cur = array_temp[0];

    EEPROM_R(Addr_D2_Time, array_temp, 1, 0xA0);
    TH_DL = array_temp[0];
    EEPROM_R(Addr_CurLong_Time, array_temp, 1, 0xA0);
    TH_Long_Cur = array_temp[0];
    if (TH_Long_Cur > 7)
    {
        TH_Long_Cur = 0;
    }
    // putchar(D_Cur);
    EEPROM_R(Addr_Type_Cur, array_temp, 1, 0xA0);
    Type_Cur = array_temp[0];
    if (Type_Cur > 4)
    {
        Type_Cur = 1;
    }
    if ((Type_Cur == 0) && (D_Cur >= 76))
    {
        D_Cur = 76;
    }
    if ((Type_Cur == 1) && (D_Cur >= 187))
    {
        D_Cur = 187;
    }
    if ((Type_Cur == 2) && (D_Cur >= 240))
    {
        D_Cur = 240;
    }
    if ((Type_Cur == 3) && (D_Cur >= 378))
    {
        D_Cur = 378;
    }
    if ((Type_Cur == 4) && (D_Cur >= 480))
    {
        D_Cur = 480;
    }
    Cur_Switch(Type_Cur);
}

void D3_A_BH_Process(void)
{

    //	 if(isfenzha!=0)  //在合闸位置
    //{
    //	if(F_ip_3==1)
    //	{
    //			if((cur_actionhandle_A(I_Array_xianshi[0]))>=I3)
    //			{
    //				N_A3D=N_A3D+2 ;
    //				//N_K=N_K+20;
    //				if(N_A3D>=3)  //一个周期12个点及认为应该动作
    //				{
    ////						if(F_I_STA==0)
    //					{
    //						F_ch=0 ;
    //						Record_data_propare();   //把要写入的漏电，电压，电流值准备好以写入
    //				  	gz_disp=cur_actionhandle_A(I_Array_xianshi[0]);//过点，此处应该修改
    //						//if(F_trip_gl==1)
    //						{
    //							Trip_Action();
    //						}
    //						gz_reason=trip_reason_3D_cur;
    //						F_record_write = 1;
    //						F_3d_trip=1;
    //						//putchar(gz_reason);
    //						GZ_ph = 1;
    //						//Write_Record(trip_reason_cur,(i+1));
    //						F_gz_disp=A_gl ;
    //						if(F_ia==1)  //F_ia  漏电重合闸标志位
    //						{
    //							F_I_STA=1 ;
    //							F_ch=0 ;
    //							F_I_Lock = 0;
    //						}
    //						//如果漏电重合闸功能开
    //						else
    //						{
    //							F_ch=1 ;
    //							F_I_STA=3 ;  //直接置3
    //							F_I_Lock=1 ;
    //						}
    //						//否则不再重合闸
    //					}
    //					//连续第二次脱扣
    //					if(F_I_STA==2)
    //					{
    //						F_ch=1 ;
    //						gz_disp=999;//过点，此处应该修改
    //						Record_data_propare();
    //						//if(F_trip_gl==1)
    //						{
    //							Trip_Action();
    //						}
    //
    //						F_record_write = 1;
    //						gz_reason=trip_reason_3D_cur;
    //						//putchar(gz_reason);
    //						GZ_ph = 1;
    //						//Write_Record(trip_reason_cur,1);
    //						F_I_STA=3 ;
    //						F_I_Lock=1 ;
    //
    //						F_gz_disp=A_gl ;
    //
    //						//写过流跳闸记录
    //					}
    //				}
    //			}
    //			else
    //			{
    //				N_A3D=N_A3D-1 ;
    //				if(N_A3D<=0)
    //				N_A3D=0 ;
    //			}
    //	}
    if (F_ip == 1)
    {
        N_T_TH = N_TH_DL[TH_DL];
        if ((cur_handle_A(I_Array_xianshi[0])) >= I2)
        {
            N_A2D = N_A2D + 2;
            // N_K=N_K+20;
            // 2014年9月10日因快速动作误动，延长动作时间19 修改为25
            if (N_A2D >= N_T_TH) // 一个周期12个点及认为应该动作
            {
                //						if(F_I_STA==0)
                {
                    F_ch = 0;
                    Record_data_propare();                      // 把要写入的漏电，电压，电流值准备好以写入
                    gz_disp = cur_handle_A(I_Array_xianshi[0]); // 过点，此处应该修改
                    // if(F_trip_gl==1)
                    {
                        Trip_Action();
                    }
                    gz_reason = trip_reason_short;
                    F_record_write = 1;
                    // putchar(gz_reason);
                    GZ_ph = 1;
                    // Write_Record(trip_reason_cur,(i+1));
                    F_gz_disp = A_gl;
                    if (F_ia == 1) // F_ia  漏电重合闸标志位
                    {
                        F_I_STA = 1;
                        F_ch = 0;
                        F_I_Lock = 0;
                    }
                    // 如果漏电重合闸功能开
                    else
                    {
                        F_ch = 1;
                        F_I_STA = 3; // 直接置3
                        F_I_Lock = 1;
                    }
                    // 否则不再重合闸
                }
                // 连续第二次脱扣
                if (F_I_STA == 2)
                {
                    F_ch = 1;
                    gz_disp = 997; // 过点，此处应该修改
                    Record_data_propare();
                    // if(F_trip_gl==1)
                    {
                        Trip_Action();
                    }

                    F_record_write = 1;
                    gz_reason = trip_reason_short;
                    // putchar(gz_reason);
                    GZ_ph = 1;
                    // Write_Record(trip_reason_cur,1);
                    F_I_STA = 3;
                    F_I_Lock = 1;

                    F_gz_disp = A_gl;

                    // 写过流跳闸记录
                }
            }
        }
        else
        {
            N_A2D = N_A2D - 1;
            if (N_A2D <= 0)
                N_A2D = 0;
        }
    }
}

void D3_B_BH_Process(void)
{
    //	 if(isfenzha!=0)  //在合闸位置
    //{
    //	if(F_ip_3==1)
    //	{
    //			if((cur_actionhandle_B(I_Array_xianshi[1]))>=I3)
    //			{
    //				N_B3D=N_B3D+2 ;
    //				//N_K=N_K+20;
    //				if(N_B3D>=3)  //一个周期12个点及认为应该动作
    //				{
    ////						if(F_I_STA==0)
    //					{
    //						F_ch=0 ;
    //						Record_data_propare();   //把要写入的漏电，电压，电流值准备好以写入
    //				  	gz_disp=cur_actionhandle_B(I_Array_xianshi[1]);//过点，此处应该修改
    //						//if(F_trip_gl==1)
    //						{
    //							Trip_Action();
    //						}
    //						gz_reason=trip_reason_3D_cur;
    //						F_record_write = 1;
    //						//putchar(gz_reason);
    //						GZ_ph = 2;
    //						//Write_Record(trip_reason_cur,(i+1));
    //						F_gz_disp=A_gl+1 ;
    //						if(F_ia==1)  //F_ia  漏电重合闸标志位
    //						{
    //							F_I_STA=1 ;
    //							F_ch=0 ;
    //							F_I_Lock = 0;
    //						}
    //						//如果漏电重合闸功能开
    //						else
    //						{
    //							F_ch=1 ;
    //							F_I_STA=3 ;  //直接置3
    //							F_I_Lock=1 ;
    //						}
    //						//否则不再重合闸
    //					}
    //					//连续第二次脱扣
    //					if(F_I_STA==2)
    //					{
    //						F_ch=1 ;
    //						gz_disp=999;//过点，此处应该修改
    //						Record_data_propare();
    //						//if(F_trip_gl==1)
    //						{
    //							Trip_Action();
    //						}
    //						F_record_write = 1;
    //						gz_reason=trip_reason_3D_cur;
    //						//putchar(gz_reason);
    //						GZ_ph = 2;
    //						//Write_Record(trip_reason_cur,1);
    //						F_I_STA=3 ;
    //						F_I_Lock=1 ;
    //						F_gz_disp=A_gl+1 ;
    //
    //						//写过流跳闸记录
    //					}
    //				}
    //			}
    //			else
    //			{
    //				N_B3D=N_B3D-1 ;
    //				if(N_B3D<=0)
    //				N_B3D=0 ;
    //			}
    //	}
    if (F_ip == 1)
    {
        N_T_TH = N_TH_DL[TH_DL];
        if ((cur_handle_B(I_Array_xianshi[1])) >= I2)
        {
            N_B2D = N_B2D + 2;
            // N_K=N_K+20;
            // 2014年9月10日因快速动作误动，延长动作时间19 修改为25
            if (N_B2D >= N_T_TH) // 一个周期12个点及认为应该动作
            {
                if (F_I_STA == 0)
                {
                    F_ch = 0;
                    Record_data_propare();                      // 把要写入的漏电，电压，电流值准备好以写入
                    gz_disp = cur_handle_B(I_Array_xianshi[1]); // 过点，此处应该修改
                    {
                        Trip_Action();
                    }
                    gz_reason = trip_reason_short;
                    F_record_write = 1;
                    // putchar(gz_reason);
                    GZ_ph = 2;
                    // Write_Record(trip_reason_cur,(i+1));
                    F_gz_disp = A_gl + 1;
                    if (F_ia == 1) // F_ia  漏电重合闸标志位
                    {
                        F_I_STA = 1;
                        F_ch = 0;
                        F_I_Lock = 0;
                    }
                    // 如果漏电重合闸功能开
                    else
                    {
                        F_ch = 1;
                        F_I_STA = 3; // 直接置3
                        F_I_Lock = 1;
                    }
                    // 否则不再重合闸
                }
                // 连续第二次脱扣
                if (F_I_STA == 2)
                {
                    F_ch = 1;
                    gz_disp = 997; // 过点，此处应该修改
                    Record_data_propare();
                    // if(F_trip_gl==1)
                    {
                        Trip_Action();
                    }
                    F_record_write = 1;
                    gz_reason = trip_reason_short;
                    // putchar(gz_reason);
                    GZ_ph = 2;
                    // Write_Record(trip_reason_cur,1);
                    F_I_STA = 3;
                    F_I_Lock = 1;
                    F_gz_disp = A_gl + 1;

                    // 写过流跳闸记录
                }
            }
        }
        else
        {
            N_B2D = N_B2D - 1;
            if (N_B2D <= 0)
                N_B2D = 0;
        }
    }
}

void D3_C_BH_Process(void)
{
    //	 if(isfenzha!=0)  //在合闸位置
    //{
    //	if(F_ip_3==1)
    //	{
    //			if((cur_actionhandle_C(I_Array_xianshi[2]))>=I3)
    //			{
    //				N_C3D=N_C3D+2 ;
    //				//N_K=N_K+20;
    //
    //				if(N_C3D>=3)  //一个周期12个点及认为应该动作
    //				{
    ////						if(F_I_STA==0)
    //					{
    //						F_ch=0 ;
    //						Record_data_propare();   //把要写入的漏电，电压，电流值准备好以写入
    //				  	gz_disp=cur_actionhandle_C(I_Array_xianshi[2]);//过点，此处应该修改
    //						//if(F_trip_gl==1)
    //						{
    //							Trip_Action();
    //						}
    //						gz_reason=trip_reason_3D_cur;
    //						F_record_write = 1;
    //						//putchar(gz_reason);
    //						GZ_ph = 3;
    //						//Write_Record(trip_reason_cur,(i+1));
    //						F_gz_disp=A_gl+2 ;
    //						if(F_ia==1)  //F_ia  漏电重合闸标志位
    //						{
    //							F_I_STA=1 ;
    //							F_ch=0 ;
    //							F_I_Lock = 0;
    //						}
    //						//如果漏电重合闸功能开
    //						else
    //						{
    //							F_ch=1 ;
    //							F_I_STA=3 ;  //直接置3
    //							F_I_Lock=1 ;
    //						}
    //						//否则不再重合闸
    //					}
    //					//连续第二次脱扣
    //					if(F_I_STA==2)
    //					{
    //						F_ch=1 ;
    //						gz_disp=999;//过点，此处应该修改
    //						Record_data_propare();
    //						//if(F_trip_gl==1)
    //						{
    //							Trip_Action();
    //						}
    //
    //						F_record_write = 1;
    //						gz_reason=trip_reason_3D_cur;
    //						//putchar(gz_reason);
    //						GZ_ph = 3;
    //						//Write_Record(trip_reason_cur,1);
    //						F_I_STA=3 ;
    //						F_I_Lock=1 ;
    //						F_gz_disp=A_gl+2 ;
    //
    //						//写过流跳闸记录
    //					}
    //				}
    //			}
    //			else
    //			{
    //				N_C3D=N_C3D-1 ;
    //				if(N_C3D<=0)
    //				N_C3D=0 ;
    //			}
    //	}
    if (F_ip == 1)
    {
        N_T_TH = N_TH_DL[TH_DL];
        if ((cur_handle_C(I_Array_xianshi[2])) >= I2)
        {
            N_C2D = N_C2D + 2;
            // N_K=N_K+20;
            // 2014年9月10日因快速动作误动，延长动作时间19 修改为25
            if (N_C2D >= N_T_TH) // 一个周期12个点及认为应该动作
            {
                //						if(F_I_STA==0)
                {
                    F_ch = 0;
                    Record_data_propare();                      // 把要写入的漏电，电压，电流值准备好以写入
                    gz_disp = cur_handle_C(I_Array_xianshi[2]); // 过点，此处应该修改
                    // if(F_trip_gl==1)
                    {
                        Trip_Action();
                    }
                    gz_reason = trip_reason_short;
                    F_record_write = 1;
                    // putchar(gz_reason);
                    GZ_ph = 3;
                    // Write_Record(trip_reason_cur,(i+1));
                    F_gz_disp = A_gl + 2;
                    if (F_ia == 1) // F_ia  漏电重合闸标志位
                    {
                        F_I_STA = 1;
                        F_ch = 0;
                        F_I_Lock = 0;
                    }
                    // 如果漏电重合闸功能开
                    else
                    {
                        F_ch = 1;
                        F_I_STA = 3; // 直接置3
                        F_I_Lock = 1;
                    }
                    // 否则不再重合闸
                }
                // 连续第二次脱扣
                if (F_I_STA == 2)
                {
                    F_ch = 1;
                    gz_disp = 997; // 过点，此处应该修改
                    Record_data_propare();
                    // if(F_trip_gl==1)
                    {
                        Trip_Action();
                    }

                    F_record_write = 1;
                    gz_reason = trip_reason_short;
                    // putchar(gz_reason);
                    GZ_ph = 3;
                    // Write_Record(trip_reason_cur,1);
                    F_I_STA = 3;
                    F_I_Lock = 1;
                    F_gz_disp = A_gl + 2;

                    // 写过流跳闸记录
                }
            }
        }
        else
        {
            N_C2D = N_C2D - 2;
            if (N_C2D <= 0)
                N_C2D = 0;
        }
    }
}
unsigned int cur_handle_A(unsigned int x)
{
    if (((vol_handle_A(V_Array[0])) < 100) && ((vol_handle_B(V_Array[1])) < 100) && ((vol_handle_C(V_Array[2])) < 100)) // 没电压
    {
        F_Corr = 0;
        unsigned int y;
        if (Type_Cur == 0)
        {

            if (x <= CurA_cal_tmp_nv[0])
            {
                x = (x * I1_A_slope_nv[0]) >> 20;
            }
            else if (x > CurA_cal_tmp_nv[0])
            {
                x = 50 + (((x - CurA_cal_tmp_nv[0]) * I1_A_slope_nv[1]) >> 20);
            }
            else
            {
            }

            // if(x>=300) x=x+3*(x-300);
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 1) // 需要改动
        {

            if (x <= CurA_cal_tmp_nv[0])
            {
                x = (x * I1_A_slope_nv[0]) >> 20;
            }
            else if (x > CurA_cal_tmp_nv[0])
            {
                x = 100 + (((x - CurA_cal_tmp_nv[0]) * I1_A_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为200~400A时
        if (Type_Cur == 2)
        {

            if (x <= CurA_cal_tmp_nv[0])
            {
                x = (x * I1_A_slope_nv[0]) >> 20;
            }
            else if (x > CurA_cal_tmp_nv[0])
            {
                x = 160 + (((x - CurA_cal_tmp_nv[0]) * I1_A_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 3)
        {

            if (x <= CurA_cal_tmp_nv[0])
            {
                x = (x * I1_A_slope_nv[0]) >> 20;
            }
            else if (x > CurA_cal_tmp_nv[0])
            {
                x = 252 + (((x - CurA_cal_tmp_nv[0]) * I1_A_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        if (Type_Cur == 4)
        {

            if (x <= CurA_cal_tmp_nv[0])
            {
                x = (x * I1_A_slope_nv[0]) >> 20;
            }
            else if (x > CurA_cal_tmp_nv[0])
            {
                x = 320 + (((x - CurA_cal_tmp_nv[0]) * I1_A_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        I_A_vaule = x;
        if (I_A_vaule < 125 && I_B_vaule < 30 && I_C_vaule < 30 && LEDA_FLAG == 0)
        {
            I_A_vaule = I_A_vaule * 0.83;
        }
        else if (I_A_vaule < 160 && I_B_vaule < 30 && I_C_vaule < 30 && LEDA_FLAG == 1)
        {
            I_A_vaule = I_A_vaule * 0.83;
        }
        if (I_A_vaule <= 21)
            I_A_vaule = 0;
        IA_uart_temp = y;
        return I_A_vaule;
    }
    else
    {
        F_Corr = 0;
        unsigned int y;
        if (Type_Cur == 0)
        {

            if (x <= CurA_cal_tmp[0])
            {
                x = (x * I1_A_slope[0]) >> 20;
            }
            else if (x > CurA_cal_tmp[0])
            {
                x = 50 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
            }
            else
            {
            }

            // if(x>=300) x=x+3*(x-300);
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 1) // 需要改动
        {

            if (x <= CurA_cal_tmp[0])
            {
                x = (x * I1_A_slope[0]) >> 20;
            }
            else if (x > CurA_cal_tmp[0])
            {
                x = 100 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为200~400A时
        if (Type_Cur == 2)
        {

            if (x <= CurA_cal_tmp[0])
            {
                x = (x * I1_A_slope[0]) >> 20;
            }
            else if (x > CurA_cal_tmp[0])
            {
                x = 160 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 3)
        {

            if (x <= CurA_cal_tmp[0])
            {
                x = (x * I1_A_slope[0]) >> 20;
            }
            else if (x > CurA_cal_tmp[0])
            {
                x = 252 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
            }
            else
            {
            }
        }
        if (Type_Cur == 4)
        {

            if (x <= CurA_cal_tmp[0])
            {
                x = (x * I1_A_slope[0]) >> 20;
            }
            else if (x > CurA_cal_tmp[0])
            {
                x = 320 + (((x - CurA_cal_tmp[0]) * I1_A_slope[1]) >> 20);
            }
            else
            {
            }
        }
        I_A_vaule = x;

        if (I_A_vaule <= 21)
            I_A_vaule = 0;
        IA_uart_temp = y;
        return I_A_vaule;
    }
}

unsigned int cur_handle_B(unsigned int x)
{
    if (((vol_handle_A(V_Array[0])) < 100) && ((vol_handle_B(V_Array[1])) < 100) && ((vol_handle_C(V_Array[2])) < 100)) // 没电压
    {
        F_Corr = 0;
        unsigned int y;
        if (Type_Cur == 0)
        {

            if (x <= CurB_cal_tmp_nv[0])
            {
                x = (x * I1_B_slope_nv[0]) >> 20;
            }
            else if (x > CurB_cal_tmp_nv[0])
            {
                x = 50 + (((x - CurB_cal_tmp_nv[0]) * I1_B_slope_nv[1]) >> 20);
            }
            else
            {
            }

            // if(x>=300) x=x+3*(x-300);
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 1) // 需要改动
        {

            if (x <= CurB_cal_tmp_nv[0])
            {
                x = (x * I1_B_slope_nv[0]) >> 20;
            }
            else if (x > CurB_cal_tmp_nv[0])
            {
                x = 100 + (((x - CurB_cal_tmp_nv[0]) * I1_B_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为200~400A时
        if (Type_Cur == 2)
        {
            //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
            //		     x=(x>>11)+(x>>12);

            if (x <= CurB_cal_tmp_nv[0])
            {
                x = (x * I1_B_slope_nv[0]) >> 20;
            }
            else if (x > CurB_cal_tmp_nv[0])
            {
                x = 160 + (((x - CurB_cal_tmp_nv[0]) * I1_B_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        if (Type_Cur == 3)
        {
            //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
            //		     x=(x>>13)+(x>>14);

            if (x <= CurB_cal_tmp_nv[0])
            {
                x = (x * I1_B_slope_nv[0]) >> 20;
            }
            else if (x > CurB_cal_tmp_nv[0])
            {
                x = 252 + (((x - CurB_cal_tmp_nv[0]) * I1_B_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        if (Type_Cur == 4)
        {

            if (x <= CurB_cal_tmp_nv[0])
            {
                x = (x * I1_B_slope_nv[0]) >> 20;
            }
            else if (x > CurB_cal_tmp_nv[0])
            {
                x = 320 + (((x - CurB_cal_tmp_nv[0]) * I1_B_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        I_B_vaule = x;
        if (I_B_vaule < 125 && I_A_vaule < 30 && I_C_vaule < 30 && LEDA_FLAG == 0)
        {
            I_B_vaule = I_B_vaule * 0.83;
        }
        else if (I_B_vaule < 160 && I_A_vaule < 30 && I_C_vaule < 30 && LEDA_FLAG == 1)
        {
            I_B_vaule = I_B_vaule * 0.83;
        }
        if (I_B_vaule <= 21)
            I_B_vaule = 0;
        IB_uart_temp = y;
        return I_B_vaule;
    }
    else
    {
        F_Corr = 0;
        unsigned int y;
        if (Type_Cur == 0)
        {

            if (x <= CurB_cal_tmp[0])
            {
                x = (x * I1_B_slope[0]) >> 20;
            }
            else if (x > CurB_cal_tmp[0])
            {
                x = 50 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
            }
            else
            {
            }

            // if(x>=300) x=x+3*(x-300);
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 1) // 需要改动
        {

            if (x <= CurB_cal_tmp[0])
            {
                x = (x * I1_B_slope[0]) >> 20;
            }
            else if (x > CurB_cal_tmp[0])
            {
                x = 100 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为200~400A时
        if (Type_Cur == 2)
        {
            //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
            //		     x=(x>>11)+(x>>12);

            if (x <= CurB_cal_tmp[0])
            {
                x = (x * I1_B_slope[0]) >> 20;
            }
            else if (x > CurB_cal_tmp[0])
            {
                x = 160 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
            }
            else
            {
            }
        }
        if (Type_Cur == 3)
        {
            //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
            //		     x=(x>>13)+(x>>14);

            if (x <= CurB_cal_tmp[0])
            {
                x = (x * I1_B_slope[0]) >> 20;
            }
            else if (x > CurB_cal_tmp[0])
            {
                x = 252 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
            }
            else
            {
            }
        }
        if (Type_Cur == 4)
        {

            if (x <= CurB_cal_tmp[0])
            {
                x = (x * I1_B_slope[0]) >> 20;
            }
            else if (x > CurB_cal_tmp[0])
            {
                x = 320 + (((x - CurB_cal_tmp[0]) * I1_B_slope[1]) >> 20);
            }
            else
            {
            }
        }
        I_B_vaule = x;
        if (I_B_vaule <= 21)
            I_B_vaule = 0;
        IB_uart_temp = y;
        return I_B_vaule;
    }
}

unsigned int cur_handle_C(unsigned int x)
{
    if (((vol_handle_A(V_Array[0])) < 100) && ((vol_handle_B(V_Array[1])) < 100) && ((vol_handle_C(V_Array[2])) < 100)) // 没电压
    {
        F_Corr = 0;
        unsigned int y;
        if (Type_Cur == 0)
        {

            if (x <= CurC_cal_tmp_nv[0])
            {
                x = (x * I1_C_slope_nv[0]) >> 20;
            }
            else if (x > CurC_cal_tmp_nv[0])
            {
                x = 50 + (((x - CurC_cal_tmp_nv[0]) * I1_C_slope_nv[1]) >> 20);
            }
            else
            {
            }

            // if(x>=300) x=x+3*(x-300);
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 1) // 需要改动
        {

            if (x <= CurC_cal_tmp_nv[0])
            {
                x = (x * I1_C_slope_nv[0]) >> 20;
            }
            else if (x > CurC_cal_tmp_nv[0])
            {
                x = 100 + (((x - CurC_cal_tmp_nv[0]) * I1_C_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为200~400A时
        if (Type_Cur == 2)
        {
            //        y = (x>>10)+(x>>11);
            //		   x=(x>>13)+(x>>14);

            if (x <= CurC_cal_tmp_nv[0])
            {
                x = (x * I1_C_slope_nv[0]) >> 20;
            }
            else if (x > CurC_cal_tmp_nv[0])
            {
                x = 160 + (((x - CurC_cal_tmp_nv[0]) * I1_C_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 3)
        {
            //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
            //		     x=(x>>13)+(x>>14);

            if (x <= CurC_cal_tmp_nv[0])
            {
                x = (x * I1_C_slope_nv[0]) >> 20;
            }
            else if (x > CurC_cal_tmp_nv[0])
            {
                x = 252 + (((x - CurC_cal_tmp_nv[0]) * I1_C_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }
        if (Type_Cur == 4)
        {

            if (x <= CurC_cal_tmp_nv[0])
            {
                x = (x * I1_C_slope_nv[0]) >> 20;
            }
            else if (x > CurC_cal_tmp_nv[0])
            {
                x = 320 + (((x - CurC_cal_tmp_nv[0]) * I1_C_slope_nv[1]) >> 20);
            }
            else
            {
            }
        }

        I_C_vaule = x;
        if (I_C_vaule < 125 && I_A_vaule < 30 && I_B_vaule < 30 && LEDA_FLAG == 0)
        {
            I_C_vaule = I_C_vaule * 0.83;
        }
        else if (I_C_vaule < 160 && I_A_vaule < 30 && I_B_vaule < 30 && LEDA_FLAG == 1)
        {
            I_C_vaule = I_C_vaule * 0.83;
        }
        if (I_C_vaule <= 21)
            I_C_vaule = 0;
        IC_uart_temp = y;
        return I_C_vaule;
    }
    else
    {
        F_Corr = 0;
        unsigned int y;
        if (Type_Cur == 0)
        {

            if (x <= CurC_cal_tmp[0])
            {
                x = (x * I1_C_slope[0]) >> 20;
            }
            else if (x > CurC_cal_tmp[0])
            {
                x = 50 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
            }
            else
            {
            }

            // if(x>=300) x=x+3*(x-300);
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 1) // 需要改动
        {

            if (x <= CurC_cal_tmp[0])
            {
                x = (x * I1_C_slope[0]) >> 20;
            }
            else if (x > CurC_cal_tmp[0])
            {
                x = 100 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为200~400A时
        if (Type_Cur == 2)
        {
            //        y = (x>>10)+(x>>11);
            //		   x=(x>>13)+(x>>14);

            if (x <= CurC_cal_tmp[0])
            {
                x = (x * I1_C_slope[0]) >> 20;
            }
            else if (x > CurC_cal_tmp[0])
            {
                x = 160 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
            }
            else
            {
            }
        }
        // 电流框架等级为60~250A时
        if (Type_Cur == 3)
        {
            //         y = (x>>10)+(x>>11)+(((x>>10)+(x>>11))>>2);
            //		     x=(x>>13)+(x>>14);

            if (x <= CurC_cal_tmp[0])
            {
                x = (x * I1_C_slope[0]) >> 20;
            }
            else if (x > CurC_cal_tmp[0])
            {
                x = 252 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
            }
            else
            {
            }
        }
        if (Type_Cur == 4)
        {

            if (x <= CurC_cal_tmp[0])
            {
                x = (x * I1_C_slope[0]) >> 20;
            }
            else if (x > CurC_cal_tmp[0])
            {
                x = 320 + (((x - CurC_cal_tmp[0]) * I1_C_slope[1]) >> 20);
            }
            else
            {
            }
        }
    }

    I_C_vaule = x;
    if (I_C_vaule <= 21)
        I_C_vaule = 0;
    //	IC_uart_temp = y;
    return I_C_vaule;
}

unsigned int cur_actionhandle_A(unsigned int x)
{
    // 电流框架等级为20~100A时
    unsigned int y;
    if (Type_Cur == 0)
    {

        //				 if(x<=24750)
        //				{
        //						x = x/55;
        //				}
        //				else
        //				{
        //				  x=450+(x-24750)/13;//15
        //				}
        //
        if (x <= 46200)
        {
            x = x / 66;
        }
        else
        {
            x = 700 + (x - 46200) / 24; // 15
        }
    }
    // 电流框架等级为60~250A时
    if (Type_Cur == 1) // 需要改动//DLS_Cur_Value[0]=DLS_Cur_AD_value[0]/DLS_Cur_slope[0];瞬动电流值=瞬动电流AD值/瞬动斜率
    {

        if (x <= 66000) // 1100
        {
            x = x / 60;
        }
        else if (x < 76800) // 2000
        {
            x = 1100 + (x - 66000) / 12; // 15
        }
        else
        {
            x = 2000 + (x - 76800) / 8;
        }
        //
        //				if(x<=850)  x=x+(35*x)/100;
        //				else if((x>850)&&(x<2000)) x=x+1000;
        //				else if((x>850)&&(x<2000)) x=x+550;
        //				else if((x>2000)&&(x<2900)) x=x+1600;
        //				else if(x>2900) x=x+1600;
        if ((x > 850) && (x < 2200))
            x = x + 100;
        else if ((x > 2200) && (x < 2900))
            x = x + 200;
        if (x <= 500)
            x = x * 1.4;
        else if ((x > 500) && (x <= 1100))
            x = x * 1.3;
        else if (x > 1100)
            x = x * 1.5;
    }
    // 电流框架等级为200~400A时
    if (Type_Cur == 2)
    {
        if (x <= 41800) // 1100
        {
            x = x / 38;
        }
        else if (x < 77900)
        {
            x = 1100 + (x - 41800) / 19;
        }
        else
        {
            x = 3000 + (x - 77900) / 3;
        }
        if ((x > 2400) && (x <= 2800))
            x = x + 400;
        else if ((x > 2800) && (x < 3400))
            x = x + 1200;
        else if (x >= 3400)
            x = x + 300;

        // if((x>2800)&&(x<3600)) x=x+1400;
        //				else if(x>3600) x=x+500;
    }
    // 电流框架等级为60~250A时
    if (Type_Cur == 3)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 56300)
        {
            x = 1100 + (x - 30800) / 14;
        }
        else if (x < 67400)
        {
            x = 2800 + (x - 56300) / 3;
        }
        else if (x < 73000)
        {
            x = 5971 + (x - 67400) / 4;
        }
        else
        {
            x = 10000;
        }
    }
    if (Type_Cur == 4)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 25;
        }
        else if (x < 87260)
        {
            x = 2360 + (x - 62300) / 24;
        }
        else if (x < 96860)
        {
            x = 3400 + (x - 87260) / 6;
        }
        else if (x < 103260)
        {
            x = 5000 + (x - 96860) / 2;
        }
        else if (x < 106460)
        {
            x = 8200 + (x - 103260) / 2;
        }
        else
        {
            x = 9100 + (x - 106460) / 1;
        }
        if ((x > 6000) && (x < 9800))
            x = x - 1000;

        if (x <= 3000)
            x = x * 1.1;
        else if (x > 3000)
            x = x * 1.2;
    }

    IA_action_temp = x;
    return IA_action_temp;
}

unsigned int cur_actionhandle_B(unsigned int x)
{
    // 电流框架等级为20~100A时
    unsigned int y;
    if (Type_Cur == 0)
    {
        //				 if(x<=24750)
        //				{
        //						x = x/55;
        //				}
        //				else
        //				{
        //				  x=450+(x-24750)/13;//15
        //				}
        if (x <= 46200)
        {
            x = x / 66;
        }
        else
        {
            x = 700 + (x - 46200) / 24; // 15
        }
    }
    // 电流框架等级为60~250A时
    if (Type_Cur == 1) // 需要改动//DLS_Cur_Value[0]=DLS_Cur_AD_value[0]/DLS_Cur_slope[0];瞬动电流值=瞬动电流AD值/瞬动斜率
    {

        if (x <= 66000) // 1100
        {
            x = x / 60;
        }
        else if (x < 76800) // 2000
        {
            x = 1100 + (x - 66000) / 12; // 15
        }
        else
        {
            x = 2000 + (x - 76800) / 8;
        }
        if ((x > 850) && (x < 2200))
            x = x + 150;

        if (x <= 500)
            x = x * 1.4;
        else if ((x > 500) && (x <= 1100))
            x = x * 1.3;
        else if (x > 1100)
            x = x * 1.5;
        //				if(x<=850)  x=x+(35*x)/100;
        //				else if((x>850)&&(x<2000)) x=x+900;
        //				else if((x>850)&&(x<2000)) x=x+500;
        //				else if((x>2000)&&(x<2900)) x=x+1600;
        //				else if(x>2900) x=x+1600;
    }
    // 电流框架等级为200~400A时
    if (Type_Cur == 2)
    {
        if (x <= 41800) // 1100
        {
            x = x / 38;
        }
        else if (x < 77900)
        {
            x = 1100 + (x - 41800) / 19;
        }
        else
        {
            x = 3000 + (x - 77900) / 3;
        }
        if ((x > 2400) && (x <= 2800))
            x = x + 300;
        else if ((x > 2800) && (x < 3400))
            x = x + 1000;
        else if (x > 4000)
            x = x - 300;
    }
    // 电流框架等级为60~250A时
    if (Type_Cur == 3) // 630
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 56300)
        {
            x = 1100 + (x - 30800) / 15; /// 15-14
        }
        else if (x < 67400)
        {
            x = 2800 + (x - 56300) * 2 / 7; /// 2800-2921
        }
        else if (x < 73000)
        {
            x = 5971 + (x - 67400) / 4; /// 5971-6092
        }
        else
        {
            x = 10000;
        }
    }

    if (Type_Cur == 4)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 25;
        }
        else if (x < 87260)
        {
            x = 2360 + (x - 62300) / 24;
        }
        else if (x < 96860)
        {
            x = 3400 + (x - 87260) / 6;
        }
        else if (x < 103260)
        {
            x = 5000 + (x - 96860) / 2;
        }
        else if (x < 106460)
        {
            x = 8200 + (x - 103260) / 2;
        }
        else
        {
            x = 9100 + (x - 106460) / 1;
        }
        if ((x > 6000) && (x < 9800))
            x = x - 1000;

        if (x <= 3000)
            x = x * 1.1;
        else if (x > 3000)
            x = x * 1.2;
    }

    IB_action_temp = x;
    return IB_action_temp;
}

unsigned int cur_actionhandle_C(unsigned int x)
{
    // 电流框架等级为20~100A时
    unsigned int y;
    if (Type_Cur == 0)
    {

        //				 if(x<=24750)
        //				{
        //						x = x/55;
        //				}
        //				else
        //				{
        //				  x=450+(x-24750)/13;//15
        //				}
        if (x <= 46200)
        {
            x = x / 66;
        }
        else
        {
            x = 700 + (x - 46200) / 24; // 15
        }
    }
    // 电流框架等级为60~250A时
    if (Type_Cur == 1) // 需要改动//DLS_Cur_Value[0]=DLS_Cur_AD_value[0]/DLS_Cur_slope[0];瞬动电流值=瞬动电流AD值/瞬动斜率
    {

        if (x <= 66000) // 1100
        {
            x = x / 60;
        }
        else if (x < 76800) // 2000
        {
            x = 1100 + (x - 66000) / 12; // 15
        }
        else
        {
            x = 2000 + (x - 76800) / 8;
        }
        if ((x > 850) && (x < 2200))
            x = x + 100;
        else if ((x > 2200) && (x < 2900))
            x = x + 200;
        if (x <= 500)
            x = x * 1.4;
        else if ((x > 500) && (x <= 1100))
            x = x * 1.3;
        else if (x > 1100)
            x = x * 1.5;
        //				if(x<=850)  x=x+(35*x)/100;
        //				else if((x>850)&&(x<2000)) x=x+900;
        //				else if((x>850)&&(x<2000)) x=x+500;
        //				else if((x>2000)&&(x<2900)) x=x+1600;
        //				else if(x>2900) x=x+1600;
    }
    // 电流框架等级为200~400A时
    if (Type_Cur == 2)
    {
        if (x <= 41800) // 1100
        {
            x = x / 38;
        }
        else if (x < 77900)
        {
            x = 1100 + (x - 41800) / 19;
        }
        else
        {
            x = 3000 + (x - 77900) / 3;
        }
        if ((x > 2400) && (x <= 2800))
            x = x + 300;
        else if ((x > 2800) && (x < 3400))
            x = x + 1100;
        else if (x > 4000)
            x = x - 200;
    }
    // 电流框架等级为60~250A时
    if (Type_Cur == 3)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 56300)
        {
            x = 1100 + (x - 30800) / 15;
        }
        else if (x < 67400)
        {
            x = 2800 + (x - 56300) / 3;
        }
        else if (x < 73000)
        {
            x = 5971 + (x - 67400) / 4; /// 5971-6092
        }
        else
        {
            x = 100000;
        }
    }
    if (Type_Cur == 4)
    {

        if (x <= 30800)
        {
            x = x / 28;
        }
        else if (x < 62300)
        {
            x = 1100 + (x - 30800) / 25;
        }
        else if (x < 87260)
        {
            x = 2360 + (x - 62300) / 24;
        }
        else if (x < 96860)
        {
            x = 3400 + (x - 87260) / 6;
        }
        else if (x < 103260)
        {
            x = 5000 + (x - 96860) / 2;
        }
        else if (x < 106460)
        {
            x = 8200 + (x - 103260) / 2;
        }
        else
        {
            x = 9100 + (x - 106460) / 1;
        }
        if ((x > 6000) && (x < 9800))
            x = x - 1000;

        if (x <= 3000)
            x = x * 1.1;
        else if (x > 3000)
            x = x * 1.2;
    }

    IC_action_temp = x;
    return IC_action_temp;
}
void V_Sample_A(void)
{
    AD_tmp_V = 0;
    AD_tmp_V = ADC_ConvertedValue[6];
    A_V_Sum1 = AD_tmp_V + A_V_Sum1;
    if (AD_tmp_VA_Max <= AD_tmp_V)
        AD_tmp_VA_Max = AD_tmp_V;
    //	if(AD_tmp_V>=2800)
    //	{
    //		A_QL=1;
    //	}
    if (AD_tmp_V >= 3100)
    {
        N_TD_A = N_TD_A + 1;
    }
}
void V_Sample_B(void)
{
    AD_tmp_V = 0;
    AD_tmp_V = ADC_ConvertedValue[5];
    B_V_Sum1 = AD_tmp_V + B_V_Sum1;
    if (AD_tmp_VB_Max <= AD_tmp_V)
        AD_tmp_VB_Max = AD_tmp_V;
    //	if(AD_tmp_V>=2800)
    //	{
    //		B_QL=1;
    //	}
    if (AD_tmp_V >= 3100)
    {
        N_TD_B = N_TD_B + 1;
    }
}
void V_Sample_CC(void)
{
    AD_tmp_V = 0;
    AD_tmp_V = ADC_ConvertedValue[4];
    C_V_Sum1 = AD_tmp_V + C_V_Sum1;
    if (AD_tmp_VC_Max <= AD_tmp_V)
        AD_tmp_VC_Max = AD_tmp_V;
    //	if(AD_tmp_V>=2800)
    //	{
    //		C_QL=1;
    //	}
    if (AD_tmp_V >= 3100)
    {
        N_TD_C = N_TD_C + 1;
    }
}

unsigned int leak_handle(unsigned int x)
{
    unsigned int Leak_t;
    //	Num_Lv_handle();
    Leak_t = x;

    Leak_t = (Leak_t * L1_slope) >> 20;
    if (Leak_t <= 19)
    {
        Leak_t = 0;
    }

    return (Leak_t);
}

unsigned int vol_handle_A(unsigned int value)
{
    unsigned int V_t;
    V_t = value;

    V_t = (V_t * V1_slope[0]) >> 20;

    if (V_t >= 650)
        V_t = 0;
    if (V_t <= 30)
        V_t = 0;
    return (V_t);
}

unsigned int vol_handle_B(unsigned int value)
{
    unsigned int V_t;
    V_t = value;
    //		if(F_Corr==0)
    //		{
    //		  V_t=(V_t*V1_slope[1])>>20;
    ////      V_t=V_t/10;
    //		}
    //		else
    //		{
    //			V_t=(V_t*V_B_slope[0])>>10;
    //      V_t=V_t/100;
    //
    //		}
    V_t = (V_t * V1_slope[1]) >> 20;
    if (V_t >= 650)
        V_t = 0;
    if (V_t <= 30)
        V_t = 0;
    return (V_t);
}
unsigned int vol_handle_C(unsigned int value)
{
    unsigned int V_t;
    V_t = value;
    //		if(F_Corr==0)
    //		{
    //		  V_t=(V_t*V1_slope[2])>>20;
    ////      V_t=V_t/10;
    //		}
    //		else
    //		{
    //			V_t=(V_t*V_C_slope[0])>>10;
    //      V_t=V_t/100;
    //
    //		}

    V_t = (V_t * V1_slope[2]) >> 20;
    if (V_t >= 650)
        V_t = 0;
    if (V_t <= 30)
        V_t = 0;
    return (V_t);
}

void Day_updata_process(void)
{
    IWDG_Feed(); // 喂狗
    if (F_day_updata == 1)
    {
        unsigned char tim_array_tmp[10];
        F_day_updata = 0;
        HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BCD);
        HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BCD);
        tim_y = sdatestructure.Year; // tim_y为十进制，要转换二进制
        tim_m = sdatestructure.Month;
        tim_d = sdatestructure.Date;
        //			now_month = tim_array_tmp[1];
        //			now_day = tim_array_tmp[2];
        now_month = tim_m;
        now_day = tim_d;
        if ((now_day != old_day) || (now_month != old_month))
        //		if(now_day!=old_day)
        {
            Day_factors_clear();
            old_day = now_day;
            old_month = now_month;
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
            // clear_uart_sta();
            F_Dataval = 0;
        }
    }
}
void write_tingdian(void)
{
    unsigned char tingdian[2];
    tingdian[0] = 0x55;
    MODIFY_EEP_W(Addr_tingdian, tingdian, 1, 0xA0);
}

unsigned int cur_cal_handle(unsigned int x)
{
    //	int y;
    //	int y1;
    //	//电流框架等级为20~100A时
    //	if(Type_Cur==0)
    //	{
    //		 x= (x*103)>>10 ;
    //		y1 = x;
    //	}
    //	//电流框架等级为60~250A时
    //	if(Type_Cur==1)   //需要改动
    //	{
    //		 x= (x*98)>>11 ;
    //		 y1 = x;
    //	}
    //	//电流框架等级为200~400A时
    //	if(Type_Cur==2)
    //	{
    //		 x= (x*31)>>9 ;
    //		y1 = x;
    //	}
    //	//电流框架等级为60~250A时
    //	if(Type_Cur==3)
    //	{
    //		 x= (x*92)>>10 ;
    //		y1 = x;
    //	}
    //	y = y1;
    //	y1=0;
    //	if(y <= 10)     y = 0;
    //	return y ;
}

unsigned int vol_cal_handle(unsigned int value)
{
    unsigned int V_t;
    V_t = value;

    if (V_t < 300)
        return 0;
    else
    {
        V_t = (V_t * 78) >> 9;
    }
    //  qian1=V_t;
    return (V_t);
}

void hand_short_process(void)
{
    IWDG_Feed(); // 喂狗
//    switch (External_Gate_Control_Flag)
//    {
//    case 0: // 常规控制方式，即短接分闸，短接合闸
//        if (WF == 1)
//        {
//            delay_ms(5);
//            if (WF == 1)
//            {
//                if (isfenzha == 1)
//                {
//                    F_fz = 1;
//                    F_hz = 0;
//                }
//            }
//        }
//        if (WH == 1)
//        {
//            delay_ms(5);
//            if (WH == 1)
//            {
//                if (isfenzha == 0)
//                {
//                    F_fz = 0;
//                    F_hz = 1;
//                }
//            }
//        }
//        break;
//    case 1: // 短接则分闸，断开则合闸      //只有短接的情况下，各个分合闸指令正常，若未短接，则一直保持分闸状态（已弃用）
//        if (WF == 1)
//        {
//            // delay_ms(5);
//            if (WF == 1)
//            {
//                if (isfenzha == 1)
//                {
//                    F_fz = 1;
//                    F_hz = 0;
//                }
//            }
//        }
//        else
//        {
//            if (isfenzha == 0)
//            {
//                F_fz = 0;
//                F_hz = 1;
//            }
//        }

//        break;
//    case 2: // 短接则合闸，断开则分闸       //只有短接的时候，各个分合闸指令正常，短接合闸的点如果断开，就必须一直保持合闸状态
//        if (WH == 1)
//        {
//            delay_ms(5);
//            if (WH == 1)
//            {
//                if (isfenzha == 0)
//                {
//                    F_fz = 0;
//                    F_hz = 1;
//                }
//            }
//        }
//        else
//        {
//            if (isfenzha == 1)
//            {
//                F_fz = 1;
//                F_hz = 0;
//            }
//        }
//        break;
//    default:
//        if (WF == 1)
//        {
//            delay_ms(5);
//            if (WF == 1)
//            {
//                if (isfenzha == 1)
//                {
//                    F_fz = 1;
//                    F_hz = 0;
//                }
//            }
//        }
//        if (WH == 1)
//        {
//            delay_ms(5);
//            if (WH == 1)
//            {
//                if (isfenzha == 0)
//                {
//                    F_fz = 0;
//                    F_hz = 1;
//                }
//            }
//        }
//        break;
//    }

//费控

	if(WH == 0)
	{}
	else if(WH == 1)
	{
            delay_ms(5);
            if (WH == 1)
            {
                if (isfenzha == 1)
                {
                    F_fz = 1;
                    F_hz = 0;
                }
            }
	}

//static u8 last_ctrl_state = 0;    // 上一次控制信号电平
//static u8 now_ctrl_state = 0;    // 允许自动控制标志（保护脱扣后=0）

//				now_ctrl_state = WH;
//        if (now_ctrl_state == 0 &&(last_ctrl_state ==1))
//        {
//            delay_ms(5);
//            if (now_ctrl_state == 0)
//            {
//                if (isfenzha == 0)
//                {
//                    F_fz = 0;
//                    F_hz = 1;
//                }
//            }
//        }
//        if (now_ctrl_state == 1 &&(last_ctrl_state ==0))
//        {
//            delay_ms(5);
//            if (now_ctrl_state == 1)
//            {
//                if (isfenzha == 1)
//                {
//                    F_fz = 1;
//                    F_hz = 0;
//                }
//            }
//        }
//				last_ctrl_state = now_ctrl_state;
}

void IWDG_Feed(void)
{
    HAL_IWDG_Refresh(&hiwdg); // 喂狗
}

void data_clear(void)
{
    int Addr_factor;
    unsigned char array_temp[10];
    unsigned int lenth;
    unsigned char Buf_temp[30];
    // 事件清零
    clear_screen();
    Lcd12864_Write12CnCHAR(0, 16, 2, "数据清零中...");
    Num_clearall = Num_clearall + 1;
    DectoBCD(Buf_temp, Num_clearall, 3);
    MODIFY_EEP_W(Addr_clear_num, Buf_temp, 3, 0xA0);

    Addr_factor = Addr_max_leak;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Avol;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Bvol;
    lenth = 288;
    IWDG_Feed();
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Cvol;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Acur;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Bcur;
    lenth = 288;
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    IWDG_Feed();
    Addr_factor = Addr_max_Ccur;
    lenth = 288;
    IWDG_Feed();
    EEPROM_C(Addr_factor, lenth, 0xA0);
    delay_ms(5);
    //	Leak_MAX_ualue=0;

    /*          累计记录清零          */
    // 数据清零总次数 000000
    IWDG_Feed();
    //	array_temp[0] = array_temp[1]=array_temp[2] = 0;
    //	lenth=Lenth_clear_num ;
    //	Addr_factor=Addr_clear_num ;
    //	MODIFY_EEP_W(Addr_factor,array_temp,lenth);
    // 脱扣次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_trip_num, array_temp, 2, 0xA0);
    Num_tripall = 0;
    // close 次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_close_num, array_temp, 2, 0xA0);
    Num_triplock = 0;
    // 漏电脱扣次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_leak_num, array_temp, 2, 0xA0);
    Num_tripleak = 0;
    // 电流脱扣次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_current_num, array_temp, 2, 0xA0);
    Num_tripcur = 0;
    // 电压脱扣次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_vol_num, array_temp, 2, 0xA0);
    Num_tripvol = 0;
    // 手动脱扣次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_hand_num, array_temp, 2, 0xA0);
    Num_triphand = 0;
    // 零相脱扣次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_zero_num, array_temp, 2, 0xA0);
    Num_tripzero = 0;
    // 测试脱扣次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_test_num, array_temp, 2, 0xA0);
    Num_triptest = 0;
    // 短路短延次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_2D_num, array_temp, 2, 0xA0);
    Num_tripdelay = 0;

    // 剩余电流变化次数
    //	array_temp[0] = 0;
    //	MODIFY_EEP_W(Addr_leakchange_num,array_temp,1);
    // 自检次数
    //	array_temp[0] = 0;
    //	MODIFY_EEP_W(Addr_tripkey_num,array_temp,1);
    // 短路短瞬次数
    array_temp[0] = array_temp[1] = 0;
    MODIFY_EEP_W(Addr_3D_num, array_temp, 2, 0xA0);
    Num_tripinstant = 0;
    IWDG_Feed();
    /*      事件记录指针清零            */
    //  漏电记录的地址指针

    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_trip, array_temp, 1, 0xA0);

    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_trip_24C256, array_temp, 1, 0xA0);
    IWDG_Feed();
    array_temp[0] = 0;
    MODIFY_EEP_W(Addr_point_event_self, array_temp, 1, 0xA0);
    // Rewrite_buffer(0);
    // pw1 = 0x12;pw2 = 0x34;pw3 = 0x56;pw4 = 0x78;
    // IapEraseSector(512);
    // IapEraseSector(1024);
    Addr_factor = 10500;
    lenth = 1000;
    //	EEPROM_C(Addr_factor,lenth);
    //	EEPROM_R(Addr_FACTORINIT_value,array_tmp,150);
    //	MODIFY_EEP_W(Addr_FACTORINIT_value,array_tmp,150);
}

void welcome()
{
    Lcd12864_Write16CnCHAR(0, 0, 1, "  欢 迎 使 用 ");
    //
    Lcd12864_Write24CnCHAR(0, 0, 4, "漏电断路器");

    //		draw_horizontal_line(28,0,58);

    draw_horizontal_line(28, 0, 127);
    //			draw_horizontal_line(26,0,127);
    //			draw_horizontal_line(24,0,127);
    HAL_Delay(2000);
    clear_screen();
}


uint8_t F_fenhezha = 0;

uint8_t array_test[4]={0x11,0x22,0x33,0x44};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	unsigned int tingdian_tmp;
	unsigned char array_temp[2];
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	delay_init(48);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  MX_RTC_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  //MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
	IWDG_Feed(); //喂狗
	EEPROM_R(Addr_Type_Cur,array_temp,1,0xA0);
	Type_Cur=array_temp[0];

	Cur_Switch(Type_Cur);
	DW_3D_E2_read();
		
  MX_TIM6_Init();
	HAL_TIM_Base_Start_IT(&htim6);
	
	
  initial_lcd();
  clear_screen();
  
	if(isfenzha==0)
	{	LEDA_ON
		LEDA_FLAG =1;
	}
	else 
	{	LEDA_OFF
		LEDA_FLAG =0;
	}
	
  /* USER CODE BEGIN 2 */
 	Wait_selftest();   //等待初始化
	factors_init();

	N_Tingdian=0;
	F_gz=0x00 ;
	F_gz_disp = 0x0f;//无故障
	clear_flags();           //需要改

	IWDG_Feed(); //喂狗

	state_init();

	F_Disp = 1;
	F_key=0;
 
  sssj_N=1;
	sssj_N_xunhuan=1;

	F_re_sta=0;
	clear_flags();
  F_sssj=0;

	tingdian_tmp = 0x00;
	tingdian_tmp = read_tingdian();
	if(tingdian_tmp==0x55)
	{
		tingdian_tmp = 0;
		clear_tingdian();
		if(shangdian!=0)
		{
			F_record_write = 1;
			gz_reason = trip_reason_powerdown;
			F_tim_gz = 1;
			GZ_ph=1;
		}		
		if(isfenzha!=0)
		{
			F_gz = 0;
		}
	}
	if((isfenzha==0)&&(shangdian==1))   //isfenzha=0为分闸状态
	{
		if(isfenzha==0)
		{
			delay_ms(2);
			if(isfenzha==0)
			{
				F_shangdian_hezha = 1;
			}
		}	
	}
	RS485_RX_EN;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//		RS485_TX_EN;
//		HAL_UART_Transmit(&huart1, (uint8_t *)array_test, 4, 0xffff);
		
		
		
		F_fenhezha = isfenzha;

		
		
		
		
		
		
		
		uart_com_process();  //串口处理		
		hand_short_process();//外部短接分合闸
		IWDG_Feed();		
	  if(isfenzha==0)  //分闸状态
		{
			hezha_process();
		}
		else
		{
			fenzha_process();
		} 	                         	
		Nomal_Process();	 
		Cur_sample_process();//电流采样与处理
		Vol_sample_process();//电压采样与处理			
		Run_time_process();	
    Day_updata_process();	
	  if(F_record_write==1)
		{
		  if(F_guocheng==0)
			{
				Write_Record(gz_reason,GZ_ph);
				F_record_write = 0;
			}			
		}
		if(F_leak_record==1)//差值和时间间隔结合记录法
		{
			F_leak_record = 0;
			T_leak_record = 0;
			Write_Leak_Record();
		} 
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_HIGH);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14
                              |RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
