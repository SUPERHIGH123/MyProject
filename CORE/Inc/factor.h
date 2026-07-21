#ifndef __factors_h
#define __factors_h


int num = 1;
// const unsigned int T_HV_Array[]={9,19,37,55,73,91,109,127,145,163,181}; //过压比较门限数组  140 150 160 170 180
// const unsigned int T_LV_Array[]={9,19,37,55,73,91,109,127,145,163,181}; //140 150 160 170 180
const unsigned int T_HV_Array[] = {5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200}; // 过压比较门限数组  140 150 160 170 180
const unsigned int T_LV_Array[] = {5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200}; // 140 150 160 170 180

const unsigned int T_SV_Array[] = {1, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200};
volatile unsigned char Vol_g_T = 0, Vol_q_T = 0, Vol_s_T = 0, F_TIME = 0, V_point = 0, Vol_ch = 0; // 过欠压保护时间档位指针
unsigned char F_L_err = 0, F_AVcal_err = 0, F_BVcal_err = 0, F_CVcal_err = 0;
volatile unsigned int Leak_Cur_disp_cal = 0;
unsigned char F_AIcal_err = 0, F_BIcal_err = 0, F_CIcal_err = 0, F_aIcal_err = 0, F_bIcal_err = 0, F_cIcal_err = 0;
unsigned char F_cal_finish = 0;
union adres
{
    int y1;
    unsigned char adre[2];
} adresult;
signed char F_cal_L = 0, F_cal_V_A = 0, F_cal_V_B = 0, F_cal_V_C = 0, F_cal_I_A = 0, F_cal_I_B = 0, F_cal_I_C = 0;
volatile unsigned char F_Dataval1;
volatile signed int I_A_factor = 0, V_A_factor = 0, I_B_factor = 0, V_B_factor = 0, I_C_factor = 0, V_C_factor = 0, V1_slope[3] = {0};
volatile unsigned short int I1_A_slope[2] = {0}, I1_B_slope[2] = {0}, I1_C_slope[2] = {0}, I1_A_slope_nv[2] = {0}, I1_B_slope_nv[2] = {0}, I1_C_slope_nv[2] = {0};
volatile unsigned short int I1_400A_slope[2] = {0}, I1_400B_slope[2] = {0}, I1_400C_slope[2] = {0};
volatile unsigned short int I1_630A_slope[2] = {0}, I1_630B_slope[2] = {0}, I1_630C_slope[2] = {0};
volatile unsigned short int I1_800A_slope[2] = {0}, I1_800B_slope[2] = {0}, I1_800C_slope[2] = {0};
volatile unsigned char F_hezha_state, F_fenzha_state, F_hezha_delay;
volatile unsigned long Delta_Cur, DLD_Cur, DLS_Cur;
volatile unsigned int N_fenzha_time = 0, N_hezha_time = 0, N_display_time = 0;
/*******************************************************************************
 ******************************标志位区*****************************************
 ********************************************************************************/
volatile unsigned char F_nokey, F_clear_al, F_QY_hezha, F_SY_hezha, F_syTrip, F_GY_hezha, F_QX_hezha, F_qyTrip, F_gyTrip, F_qyTrip, F_qxTrip, F_lzTrip, F_QL_hezha;
volatile unsigned char F_dianya_chonghe = 0, F_tim_gz, F_analog_trip, F_dataalarm_all, F_lightalarm, F_voicealarm, F_timealarm, F_classreturn, F_chonghezha;
volatile unsigned char F_trip_ld, F_trip_qy, F_trip_gy, F_dataalarm_xq, F_trip_xq = 1, F_trip_gl, F_data_clear, F_trip_xl, F_trip_sy, F_Corr, F_auto_ld;
volatile unsigned char F_trip_QX = 0, F_trip_QL = 0, F_VLH = 0;
unsigned char F_DD_L[1];
volatile unsigned char F_shangdian_hezha;
volatile unsigned char F_50hz_nomal, F_fz, F_hz, F_FR, F_I_Trip, F_IQ_Trip, F_ITrip, F_VTrip, F_L_Lock, F_STrip, F_TTrip, F_UP_hezha, F_V_Nomal, F_VL, F_VH, F_powerup_re, F_disp_tr;
unsigned char shangdian = 0, duandian = 0, jiaozhun, LD_hezha = 0, DY_hezha = 0, DL_hezha = 0;
volatile unsigned char F_disp_h, F_yc_hezha, F_yc_fenzha, F_an_fenzha;
volatile unsigned char F_MODE, F_TB_start;
volatile unsigned char F_hezha_js, F_fenzha_js, F_an_js;
volatile unsigned char F_day_updata, F_time_trip, F_timer_triped;
volatile unsigned char F_int0, F_key, F_TB_gz = 0;
volatile unsigned char F_L_Delay, F_debug, F_leak_record, F_Uart, F_Frequncy, F_Record, F_Sync, F_Buttom, F_Vol, F_Disp, F_guocheng, F_Delay, F_Leak_Delay, F_Vol_Re, LEDA_FLAG, F_Leak_Delay1;
volatile unsigned long int A_C_Sum_3 = 0, B_C_Sum_3 = 0, C_C_Sum_3 = 0, A_C_Sum_MAX;
volatile unsigned char F_gl, F_tb, F_zd, F_hb, F_hb_old, F_qa, F_ga, F_la, F_la1, F_db, F_ni, F_la2, F_yc, F_cd, F_QUIT, F_tingdian_V, F_ks;
volatile unsigned char F_dataalarm_gl, F_dataalarm_gy, F_dataalarm_qy, F_dataalarm_xl, F_al;
volatile unsigned char F_N_shangdian = 0;
unsigned char F_shangdian_2 = 0;
unsigned char F_initial_lcd = 0;
unsigned char F_initial_lcd_hezha = 0, F_hezha_set = 0;
volatile signed int N_shangdian_hezha = 0;
volatile unsigned char F_gz, F_tingdian_fenzha = 0, kaiguan_state_old, kaiguan_state_new;
volatile unsigned char F_disp_jg;
volatile unsigned char F_disp_jg;
volatile unsigned char F_Cur = 0, iii = 0, F_ip, F_ip_3, F_cd_set, F_ia, N_anolog_trip, F_I_STA = 0, F_I_Lock, F_jianyan = 0;
unsigned char BCD_temp[2] = {0}, N_DLS = 0;
volatile unsigned short int L_factor = 0, I_factor = 0, V_factor = 0, L_factor_tmp = 0, I_factor_tmp = 0, V_factor_tmp = 0, L1_slope = 0;
unsigned char self_addr_code[6], EEPROM_array_tmp[150], F_gz_disp = 0, F_ch = 0;
unsigned char self_addr_code_temp[6];
volatile signed int N_qx_hezha = 0, N_qy_hezha = 0, N_sy_hezha = 0, N_gy_hezha = 0, N_aqy_trip = 0, N_bqy_trip = 0, N_cqy_trip = 0, N_agy_trip = 0, N_bgy_trip = 0, N_cgy_trip = 0, N_asy_trip = 0, N_bsy_trip = 0, N_csy_trip = 0, N_lz_hezha = 0;
volatile signed int N_a_bqx_trip = 0, N_a_cqx_trip = 0, N_b_aqx_trip = 0, N_b_cqx_trip = 0, N_c_aqx_trip = 0, N_c_bqx_trip = 0;
volatile unsigned char hezha_num = 0, F_al1 = 0;
volatile unsigned int ci_shu = 0;
// 定义转换结果变量
// 漏电流、A相电压、B相电压、C相电压、A相电流、B相电流、C相电流、零相电流、
volatile unsigned int Leak_Cur_disp_temp = 0, Leak_xianshi_disp = 0;
volatile unsigned int L_Cur = 0, A_Vol = 0, B_Vol = 0, C_Vol = 0, I_VAL = 0, V_Array[3] = {0}, V_Array_record[3] = {0}, V_sample[3] = {0}, V_Array_disp[3] = {0};
volatile unsigned int A_Cur = 0, B_Cur = 0, C_Cur = 0, Z_Cur = 0, Power_A_Value = 0, Power_B_Value = 0, Power_C_Value = 0;
volatile unsigned long I2 = 0, I3 = 0, I3_1 = 0;
volatile unsigned int H_DLD_Cur = 0;
volatile unsigned char pre_sta = 0, F_sssj = 0;
volatile unsigned int N_key = 0, N_disp = 0;
volatile unsigned int Over_Value, Over_Value_duanyan;
volatile unsigned char F_gc = 1;
volatile unsigned char F_wait_DY_Normal = 0;
volatile unsigned long T_64_xs = 0;

volatile unsigned int T_Timer2 = 0, Value_Timer1 = 0, Num_leakquit = 0;
volatile unsigned int H_D_V;
volatile signed int N_T_TH, N_I2[4] = {0}, N_Tingdian = 0;
signed int N_I22[4] = {0};
// volatile signed int N_TH_DL[]={30,200,400,600,850,900,900};//{100,200,300,400,600,800,1s
volatile signed int N_TH_DL[] = {5, 6, 16, 26, 36, 56, 76}; //{5,6,16,26,36,56,76}  {5,24,38,52,80,108,136}
// volatile unsigned char pw1,pw2,pw3,pw4;
volatile unsigned char F_pw1, F_pw2, F_pw3, F_pw4;
signed int V_temp[3], V_temp_tmp[3];

volatile signed long I2_Array_Sum[4] = {0}, I_I_Array_xianshi[20] = {0}, CurA_cal_tmp[5] = {0}, CurA_cal_tmp_nv[5] = {0}, CurB_cal_tmp[5] = {0}, CurB_cal_tmp_nv[5] = {0}, CurC_cal_tmp[5] = {0}, CurC_cal_tmp_nv[5] = {0}, Leak1_temp = 0, Vol1_A_temp = 0, Vol1_B_temp = 0, Vol1_C_temp = 0;
volatile signed long CurA400_cal_tmp[5] = {0}, CurB400_cal_tmp[5] = {0}, CurC400_cal_tmp[5] = {0};
volatile signed long CurA630_cal_tmp[5] = {0}, CurB630_cal_tmp[5] = {0}, CurC630_cal_tmp[5] = {0};
volatile signed long CurA800_cal_tmp[5] = {0}, CurB800_cal_tmp[5] = {0}, CurC800_cal_tmp[5] = {0};
volatile unsigned int I_Array[20] = {0}, I_Array_xianshi[20] = {0}, I_Array_action[3] = {0};
// unsigned short int Cur_cal_tmp[2]={100,500};
unsigned long Cur_cal_tmp[2] = {100, 250}; // 500
volatile unsigned long I2_Array[4] = {0};
volatile unsigned char F_I2_Array[4] = {0}, F_I_Array[4] = {0};

volatile unsigned long Time_procetect = 0, Sum_run_time = 0, Leak_xianshi_sum = 0;
volatile signed int N_SD_A = 0, N_SD_B = 0, N_SD_C = 0, F_Over_A = 0, F_Over_B = 0, F_Over_C = 0, N_DY_A = 0, N_DY_B = 0, N_DY_C = 0, F_Over_Number_duanyan = 0, TT_duanyan = 0, duanyan_record = 0;

// 串口
volatile unsigned char UART_T_Buf[60] = {0}, UART_S_Buf[60] = {0}, R_point = {0}, T_point = 0, F_Dataval = 0, Uart_od = 0, TTT[3] = {0};
volatile unsigned char tmp_uart_rx[50];
volatile unsigned long T_yc_hezha = 0, T_yc_fenzha = 0, T_yc_fenzha_js = 0, T_yc_hezha_js = 0, T_an_fenzha = 0, T_an_fenzha_js = 0;

volatile unsigned int E2_addr = 0;
volatile unsigned int gz_disp = 0;
volatile unsigned int key_state = 0;

extern volatile unsigned char tim_m3, tim_d3, tim_h3, tim_f3, tim_s3;
extern volatile unsigned int tim_y3;
volatile unsigned char button_status = 0, F_hezha_sta = 0, T_AD = 0, TT_AD = 0;
volatile unsigned char TT_1 = 0;

signed char N_key_temp = 0;
unsigned char disp_status = 0, long_key_temp = 0, F_cal = 0;
// 定义各种定时器

volatile unsigned char F_AD = 1, T_64_3 = 0, T_64_4 = 0, T_64_25 = 0, T_64_2 = 0, T_64_1 = 0, T_64_6 = 0, T_V = 0, T_L = 0, T_64_4_Re = 0; // 各种计数器
volatile unsigned int T_64_2min = 0;
volatile unsigned int T_64_hezha_delay = 0, T_sssj_N = 0, T_I = 0, T_64_1min = 0, T_64_15m = 0, T_64_20m = 0, T_64_2m = 0, T_64_10s = 0, T_64_6s = 0, T_64_11s = 0, T_64_31s = 0, T_64_40s = 0, T_64_500ms = 0, T_64_200ms = 0, T_64_100ms = 0;
// 定义各种标志位
volatile unsigned char F_Trip = 0, F_Trip1;
volatile unsigned char F_GTrip = 0, F_QTrip = 0, F_fenzha_C = 0, F_Rise = 0, F_50Hz = 0, F_Powerup = 0, F_Firstrise = 0, F_Updata = 0, F_Compare = 0, F_Vsam_begin = 0, F_display = 0; // 各种标志位
volatile unsigned char F_Alarm = 0, F_A_Trip = 0, F_hezha = 0, F_Vtest = 0, F_UTrip = 0, F_HTrip = 0, F_L_hezha, F_I_hezha = 0, F_V_hezha = 0, F_ZW = 0;
// unsigned char F_fenzha_G_Array[3],F_fenzha_Q_Array[3];
volatile unsigned char F_asy_sta = 0, F_bsy_sta = 0, F_csy_sta = 0;
// 过流保护电流档位
volatile unsigned char D_M_Cur = 0, D_I2 = 0, D_S = 0;   // 过流保护规格,档位长度,档位指针
volatile unsigned char Type_Cur = 0, D2_Cur, D3_Cur = 0; // 过流保护规格,档位长度,档位指针
volatile unsigned int D_Cur = 0;
volatile unsigned long H_Cur = 0, H5_Cur = 0;
// 过欠压保护时间档位
volatile unsigned int Vol_g = 0, Vol_q = 0; // 过欠压保护时间档位指针
volatile unsigned char Vol_up = 0, Vol_down = 0;

volatile signed char TH_V = 0; // 时间比较门限

volatile signed int N_K = 0, N_A3D = 0, N_B3D = 0, N_C3D = 0, N_A2D = 0, N_B2D = 0, N_C2D = 0, N_BASE = 0;
unsigned char N_GY_yanshi = 0, N_QY_yanshi = 0, D_GY_yanshi = 0, D_QY_yanshi = 0, D_SY_yanshi = 0;

// 漏电保护电流档位
volatile unsigned char D_LCur = 0, D_A_LCur = 0, LC_N = 0;      // 漏电电流档位指针
volatile unsigned char TH_LCur = 0, TH_DL = 0, TH_Long_Cur = 0; // 漏电时间档位指针
volatile signed int N_T1 = 0, N_T2 = 0, N_T3 = 0, N_T = 0;      // 漏电时间计数器
volatile unsigned int Id1 = 0, Id2 = 0, Id3 = 0, Id4 = 0, Id1_A = 0, Id1_H = 0, Id1_L = 0, Id1_delta = 0, Id2_delta = 0;
volatile signed int N_TH1 = 0, N_TH2 = 0, N_TH3 = 0, N_TH = 0, N_A_T = 0, N_A_L = 0, N_A_H = 0, N_delta = 0, N_TB_T = 0;
volatile unsigned int Id45 = 0;

volatile unsigned char F_anolog_trip = 0;
volatile unsigned char F_hezha_undo = 0;
extern unsigned char dispbit[8];
volatile unsigned char baud = 0x01, baud_uart = 0x08;
volatile unsigned int IA_uart_temp = 0, IB_uart_temp = 0, IC_uart_temp = 0;
volatile unsigned int VA_uart_temp = 0, VB_uart_temp = 0, VC_uart_temp = 0;
volatile unsigned int IA_action_temp = 0, IB_action_temp = 0, IC_action_temp = 0;
volatile unsigned char T_A = 0, F_FI = 0, F_T = 0, GZ_ph = 0, GZ_ph_disp = 0;

volatile int N_Trip = 0;

// 新修改增加变量
volatile signed int AD_tmp = 0, N_A_phase, I_A_Array[3];
volatile unsigned long int Leak_Cur_Sum = 0, TEMP1[2], TEMP2[2];
volatile unsigned long int A_C_Sum = 0, B_C_Sum = 0, C_C_Sum = 0, A_C_Sum_disp = 0, B_C_Sum_disp = 0, C_C_Sum_disp = 0;
volatile unsigned int Cur_A_temp[7] = {0}, Cur_B_temp[7] = {0}, Cur_C_temp[7] = {0}, Leak_temp[3] = {0};
unsigned int Vol_A_temp[3], Vol_B_temp[3], Vol_C_temp[3];
unsigned short int V_A_slope[3], V_B_slope[3], V_C_slope[3], L_slope[3], I_A_slope[5], I_B_slope[5], I_C_slope[5], Vol_C_disp[3], Vol_B_disp[3], Vol_A_disp[3], Cur_A_disp[5], Cur_B_disp[5], Cur_C_disp[5], Leak_disp[3];
signed int I_C_vaule, I_A_vaule, I_B_vaule, AD_A_value, AD_B_value, AD_C_value;
volatile unsigned int Leak_Cur = 0, Leak_Cur1 = 0, Lea_Cur_old = 0;
volatile int Delta_Leak_Cur;
volatile unsigned int T_updata = 0, Leak_Cur_disp = 0, Leak_Cur_disp_record = 0;
volatile unsigned char T = 0, T_PH = 0, TT = 0;
unsigned char F_qingling = 0;
volatile unsigned char F_gz_clear, F_time_compare, T_50hz_tmp, F_sys_pulse, F_Leak_Alarm, F_qxATrip, F_qxBTrip, F_qxCTrip, F_qxallTrip = 0;
volatile unsigned char N_Leak_TH = 0, gz_reason = 0x00;
volatile unsigned long Num_clearall = 0, Vol_A_Sum = 0;
volatile unsigned int Num_tripall, Num_triplock, Num_tripleak, Num_tripcur, Num_tripvol, Vol_A_aver, Num_leakover;
volatile unsigned int Num_triphand, Num_tripzero, Num_triptest, Num_tripkey, Num_leakprotect;
volatile unsigned int Num_quitleak, Num_tripdelay, Num_tripinstant;

volatile unsigned char point_event_trip = 0, point_event_trip_24C256 = 0, max_phase = 0, F_run_time = 0, point_event_leak = 0;
volatile unsigned char password_0class[4], password_1class[4], password_2class[4];
unsigned char ctrlword[5], stateword[5];
volatile unsigned int Leak_Alarm_Value = 0, T_run_time = 0;
volatile unsigned char Leak_record_value = 0, Leak_record_time = 0, Timer_trip[3];
// unsigned char overvoltage_setting[2],undervoltage_setting[2],phasevoltage_setting[2];
volatile unsigned char cur_setting[3], overcur_setting;
unsigned char remote_trip_time[2] = {0xff, 0xff}, remote_close_time[2] = {0xff, 0xff}, analog_trip_time[2] = {0xff, 0xff};
volatile unsigned int point_Leak_record = 0;

volatile unsigned char point_trip = 0, F_set_state = 0, N_fenzha = 0, N_hezha = 0;
volatile unsigned int T_set_state = 0, T_time_trip = 0;
volatile unsigned char F_leak_maxmin = 0, F_Conter_Updata = 0, F_TB_trip = 0, F_C_IP = 0, F_Special_wave = 0;

volatile unsigned char F_jiance = 0;
volatile unsigned char point_leak_max = 0, F_GJ_FUNC = 0;

unsigned char dev_id_code[Lenth_dev_id + 1] = {0x08, 0x08, 0x08, 0x08, 0x08, 0x08};
volatile unsigned char dev_addr_code[Lenth_dev_addr + 1] = {0x06, 0x05, 0x04, 0x03, 0x02, 0x01};

volatile unsigned int T_delay = 0;

unsigned char dev_code_code[32] = {"3330025000102030405069          "};
unsigned char dev_code_code_head[12] = {"333002500"};

volatile unsigned char rated_V_code[Lenth_rated_V] = "400   ";
volatile unsigned char rated_I_code[Lenth_rated_I] = "100   ";
volatile unsigned char frame_current_code[Lenth_frame_current] = "250   ";
unsigned char equi_type_code[Lenth_equi_type + 1] = "123456    ";

unsigned char production_date_code[Lenth_production_date] = "20170914  ";
unsigned char protocol_ver_code[Lenth_protocol_ver] = "DLT-2007        ";
unsigned char factory_code_code[Lenth_factory_code] = "A065468               ";

unsigned char auto_closing_code[Lenth_auto_closing] = "20-60                   ";
unsigned char leak_valve_code[Lenth_leak_valve] = {0x50, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x05, 0x00, 0x08, 0x00, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char leak_time_code[Lenth_leak_time] = {0x60, 0x00, 0x00, 0x01, 0x50, 0x01, 0x00, 0x03, 0xFF, 0xFF};
unsigned char break_time_code[Lenth_break_time] = {0x00, 0x02, 0x00, 0x03, 0x00, 0x05, 0x00, 0x10, 0xFF, 0xFF};

unsigned char leak_type_code[Lenth_leak_type] = "AC                      ";
unsigned char install_phase_type_code[Lenth_install_phase] = "IS  ";
unsigned char alarm_value_code[Lenth_alarm_value] = {0x00, 0x05};
unsigned char record_value_code[Lenth_record_value + 1] = {0x10, 0xFF};
unsigned char record_time_code[Lenth_record_time + 1] = {0x10, 0xFF};
unsigned char timed_trip_code[Lenth_timed_trip] = {0x00, 0x00, 0x00};
unsigned char over_vol_code[Lenth_over_vol] = {0x00, 0x28};
unsigned char under_vol_code[Lenth_under_vol] = {0x00, 0x16};
unsigned char break_phase_code[Lenth_break_phase] = {0x00, 0x12};
unsigned char rated_current_code[Lenth_rated_current] = {0x00, 0x06, 0x00};
unsigned char over_current_code[Lenth_over_current + 1] = {0x06, 0x00};

volatile unsigned int DLS_Cur_IV_AD_value[5] = {0}, DLS_Cur_IV_slope[5] = {0}, DLS_Cur_IV_Value[5] = {0};
volatile unsigned int DLS_Cur_I_AD_value[5] = {0}, DLS_Cur_I_slope[5] = {0}, DLS_Cur_I_Value[5] = {0};
volatile unsigned int DLS_Cur_II_AD_value[5] = {0}, DLS_Cur_II_slope[5] = {0}, DLS_Cur_II_Value[5] = {0};
volatile unsigned int DLS_Cur_III_AD_value[5] = {0}, DLS_Cur_III_slope[5] = {0}, DLS_Cur_III_Value[5] = {0};

const unsigned long D_C3_Array[] = {14169, 17116, 20342, 23846, 27628, 31689, 36028, 41515, 46461, 51199, 56676};                                         // 200~400各档位1.15倍电流值
const unsigned long D_C35_15Array[] = {7554313, 9125752, 10845568, 12713760, 14730328, 16895272, 19208593, 22133812, 24770863, 27296938, 30217252};       // 60~250各档位1.5倍电流值//1.5平方*120 ,,
                                                                                                                                                          //   60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long D_C3H_Array[] = {300, 490, 720, 980, 1160, 1380, 1590, 1840, 2060, 2260, 2380, 2460, 2600, 2700, 2820, 2940, 3140, 3220, 3360, 3480}; // 已经改过了  用来短路短延时的
                                                                                                                                                          //   60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long D_C3_2d_2Array[] = {200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400};

const unsigned long D_C3_3d_6Array[] = {0};
const unsigned long D_C3_3d_8Array[] = {0};
const unsigned long D_C3_3d_10Array[] = {0};
const unsigned long D_C3_3d_12Array[] = {0};

const unsigned long D_C4_Array[] = {5009, 6642, 8505, 10598, 13166, 16012, 19137, 22219, 25875, 29073, 33235, 37260, 42393, 46924, 52174}; // 200~400各档位1.15倍电流值
// const unsigned long D_C4_Array[]={20036,26568,34020,42392,52664,64048,76548,88876,103500,29073,116292,149040,169572,187696,208696};
const unsigned long D_C45_15Array[] = {2670772, 3541410, 4534672, 5650560, 7019668, 8537152, 10203013, 11846188, 13795312, 15500413, 17719312, 19865250, 22602240, 25017952, 27816868}; // 60~250各档位1.5倍电流值//1.5平方*120 ,,
// const unsigned long D_C45_15Array[]={10683088,14165640,18138688,5650560,22602240,34148608,40812052,47384752,55181248,62001652,70877248,79461000,90408960,100071808,111267472};
//
// const unsigned long D_C45_15Array[]={88181938,115176409,145770142,179963139,217755398,259146920,304137705,319934469,352727753,404917063,460705636,520093472,583080571,649666932,719852557};
//   60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long D_C4H_Array[] = {300, 490, 720, 980, 1160, 1380, 1590, 1840, 2060, 2260, 2380, 2460, 2600, 2700, 2820, 2940, 3140, 3220, 3360, 3480}; // 已经改过了  用来短路短延时的
                                                                                                                                                          //   60  70  80  90 100 110 120 130 140 150 160 170 180 190 200 210 220 230 240 250
const unsigned long D_C4_2d_2Array[] = {210, 240, 270, 300, 330, 360, 390, 420, 450, 480, 510, 540, 570, 600, 630};

const unsigned long D_C4_3d_6Array[] = {0};
const unsigned long D_C4_3d_8Array[] = {0};
const unsigned long D_C4_3d_10Array[] = {0};
const unsigned long D_C4_3d_12Array[] = {0};

float Power_factor[3] = {0}, Active_Pow[3] = {0}, Total_power[3] = {0};

const unsigned char D_V_Array[] = {1, 14, 27, 39, 52, 64}; //{4,9,14,19,24,29};//过欠压时间档位数组 500ms 1000ms  1500ms  2000ms   2500ms 3000ms

const unsigned int D_HV_Array[] = {250, 260, 270, 280, 290, 300}; // 过压比较门限数组  140 150 160 170 180
const unsigned int D_LV_Array[] = {140, 150, 160, 170, 180, 190}; // 140 150 160 170 180
// 欠压比较门限数组
const unsigned int D_UP_Array[] = {240, 250, 260, 270, 280, 290};
const unsigned int D_DOWN_Array[] = {140, 150, 160, 170, 180, 190, 200};

const unsigned char D_I2_Array[] = {4, 11, 17, 23, 30};
// 漏电动作值                         30 50 100 300 500 800 1000
// const unsigned long D_LCur1_Array[]={28,42,80,240,400,640,800};//0.8倍数组                               0  1   2  3   4   5    6
const unsigned long D_LCur1_Array[] = {24, 40, 80, 160, 240, 400, 640, 800}; // 0.8倍数组                               0  1   2  3   4   5    6
// const unsigned long D_LCur2_Array[]={40,55,110,220,330,550,880,1100};//1.1倍数组
const unsigned long D_LCur2_Array[] = {40, 65, 130, 260, 390, 650, 1040, 1300}; // 1.3倍数组

const unsigned long D_LCur45_Array[] = {90, 150, 300, 600, 900, 1500, 2400, 3000}; // 4.5倍数组  2022.9.29

const unsigned int D_LCur3_Array[] = {2300, 2300, 2300, 2300, 3200, 3200, 3200, 3200}; // 10倍数组上限
const unsigned int D_LCur4_Array[] = {1700, 1800, 1800, 1800, 1220, 1220, 1220, 1220}; // 10倍数组下限
const unsigned int D_LCur_delta_Array[] = {0, 0, 0, 0, 40, 80, 0, 0};                  // 突变数组

const unsigned long H_A_L[12] = {1, 20, 80, 140, 200, 260, 320, 380, 440, 500, 560, 620};
const unsigned long H_A_H[12] = {40, 100, 160, 220, 280, 340, 400, 460, 520, 580, 640, 700};
const unsigned long D_ACur_Array[12] = {60, 120, 180, 240, 300, 360, 420, 480, 540, 600, 660, 720};

const unsigned char TD_LCur1_Array[] = {40, 72, 120, 144, 24};

const unsigned char TD_LCur2_Array[] = {7, 11, 19, 39, 3};
const unsigned char TD_LCur3_Array[] = {3, 5, 9, 19, 1};

//      unsigned int Leak_time_class[]={200,300,500,1000};
volatile unsigned int Leak_limit_time_class[] = {200, 300, 500, 1000};

// code const  unsigned int N_Trip_Array[]={1000,30000,90000};//20s,10m,30m//{1000,2000,3000};//
const unsigned int N_Trip_Array[] = {1000, 3000, 9000}; // 20s,10m,30m//{1000,2000,3000};//

volatile unsigned long Num_leak_record, T_leak_record, T_day_updata;
volatile unsigned int V_MAX[3], V_MAX_tmp[3];
volatile unsigned int V_MIN_tmp[3] = {60000, 60000, 60000}, V_MIN[3] = {60000, 60000, 60000}; // old code 3000
unsigned char T_run_time_array[5] = {0}, tim_array[8], now_year, old_year, now_month, old_month, now_day, old_day;
volatile unsigned int I_Array_record[4], I_MIN[4] = {60000, 60000, 60000, 60000}, I_MAX[4], I_MIN_tmp[4] = {60000, 60000, 60000, 60000}, I_MAX_tmp[4];
volatile unsigned int Leak_MIN_tmp, Leak_MAX_tmp, Leak_MIN, Leak_MAX;
unsigned char Num_Sync, Leak_Over_array[20], FN_Vol, F_Cur_m;

volatile unsigned char point_leak_max, point_leak_min;
volatile unsigned char point_Avol_max, point_Bvol_max, point_Cvol_max;
volatile unsigned char point_Acur_max, point_Bcur_max, point_Ccur_max;
volatile unsigned char point_Avol_min, point_Bvol_min, point_Cvol_min;
volatile unsigned char point_Acur_min, point_Bcur_min, point_Ccur_min;
volatile unsigned char point_event_leak, point_event_alarm;
volatile unsigned int point_Leak_record;
volatile unsigned char point_event_trip, point_event_trip_24C256, point_event_leak, F_hezha_sta, point_event_self;
unsigned char V_sample_tem = 0, C_sample_tem = 0;
extern unsigned int temp_AD, temp_AD1;
volatile signed int AD_result = 0, AD_TEMP = 0, C_AD_result[3], AD_result1 = 0, AD_JIAOZHUN = 0, N_JIAOZHUN = 0, F_JIAOZHUN = 0;
// 最基本的AD采样值
volatile unsigned char F_V_AD = 0, F_C_AD = 0, F_L_AD = 0;
volatile unsigned char V_B_point = 0, Leak_piont = 0, I_point = 0, Num_Cur_protect = 0;
unsigned int ADC_ConvertedValue[8], ADC_ConvertedValue1[3];
volatile unsigned long A_V_Sum1 = 0, B_V_Sum1 = 0, C_V_Sum1 = 0, A_V_Sum_disp = 0, B_V_Sum_disp = 0, C_V_Sum_disp = 0;
volatile unsigned char T_64_1000ms = 0, F_quick_protect = 0, F_Bottom_queding = 0;
unsigned char A_QL = 0, B_QL = 0, C_QL = 0;
signed int N_QL = 0;
signed int N_TD_A = 0, N_TD_B = 0, N_TD_C = 0, N_QL_A = 0, N_QL_B = 0, N_QL_C = 0;
unsigned char F_QLA_TRIP = 0, F_QLB_TRIP = 0, F_QLC_TRIP = 0, F_QL_TRIP = 0;
unsigned char F_qlchonghe = 1, F_shiya_hezha = 0;
unsigned char N_delay_3D = 0;
signed int N_delay_DL = 0;
volatile signed int N_a_bql_trip = 0, N_a_cql_trip = 0, N_b_aql_trip = 0, N_b_cql_trip = 0, N_c_aql_trip = 0, N_c_bql_trip = 0;
unsigned char LouD_GaoJing = 0;
volatile signed int Leak_Cur_uart;
unsigned short int AQL_Judge_tmp = 0, BQL_Judge_tmp = 0, CQL_Judge_tmp = 0;
volatile signed int AD_tmp_V = 0, AD_tmp_VA_Max = 0, AD_tmp_VB_Max = 0, AD_tmp_VC_Max = 0;
// volatile signed int AD_tmp_V=0;
unsigned char R_SD[8] = {0, 1, 3, 5, 7, 9, 13, 15};

volatile unsigned int Samp_start_end_flag = 0, Re_point_VA = 0, T_LED_1s = 0, Re_UA_j = 0, Re_UB_j = 0, Re_UC_j = 0, Re_IA_j = 0, Re_IB_j = 0, Re_IC_j = 0, Re_dot_U[3] = {0}, Re_dot_I[3] = {0};
volatile signed int Re_Zhou_bo_UA[64] = {0}, Re_Zhou_bo_UB[64] = {0}, Re_Zhou_bo_UC[64] = {0};
volatile signed int Re_Zhou_bo_IA[64] = {0}, Re_Zhou_bo_IB[64] = {0}, Re_Zhou_bo_IC[64] = {0};
volatile signed int Zhou_bo_UA[70] = {0}, Zhou_bo_UB[70] = {0}, Zhou_bo_UC[70] = {0}, Zhou_bo_IA[70] = {0}, Zhou_bo_IB[70] = {0}, Zhou_bo_IC[70] = {0};
volatile signed int Zhou_bo_Ins_UA[64] = {0}, Zhou_bo_Ins_UB[64] = {0}, Zhou_bo_Ins_UC[64] = {0}, Zhou_bo_De_IA[64] = {0}, Zhou_bo_De_IB[64] = {0}, Zhou_bo_De_IC[64] = {0};
volatile signed int N_T_TH, Phase_Differ[3] = {0}, Cross_Zero[3] = {0}, Phase_Differ1[3] = {0}, Phase_Differ_A[16] = {0}, Phase_Differ_B[16] = {0}, Phase_Differ_C[16] = {0};
volatile signed int Zhou_bo_De_UA[64] = {0}, Zhou_bo_De_UB[64] = {0}, Zhou_bo_De_UC[64] = {0}, Zhou_bo_Ins_IA[64] = {0}, Zhou_bo_Ins_IB[64] = {0}, Zhou_bo_Ins_IC[64] = {0};
float Zhou_bojilu[600] = {0}, UI_AD_multi[3] = {0}, Phase_Differ_buffer[3] = {0}, Power_factor_test[3] = {0}, Power_factor_test_Ave[3] = {0};
float Power_factor_testA[4] = {0}, Power_factor_testB[4] = {0}, Power_factor_testC[4] = {0}, Phase_Differ_A_Two = 0, Phase_Differ_B_Two = 0, Phase_Differ_C_Two = 0;

volatile signed int AD_tmp_pow, AD_tmp_Power[3] = {0};
volatile signed int AD_tmp_A_V_min = 4095, AD_tmp_B_V_min, AD_tmp_C_V_min, Min_A_V_128, AD_tmp_A_V_max;
volatile unsigned long int I_A_Sum = 0, I_B_Sum = 0, I_C_Sum = 0;
volatile unsigned char Fun_Power = 0, Fun_Power_Flag = 0, Fun_Power1 = 0, Fun_Power_Flag1 = 0, Fun_Power_test = 0, YiChang_A_Flag = 0, YiChang_B_Flag = 0, YiChang_C_Flag = 0;
volatile signed int Zhou_bojilu_V[640] = {0}, Zhou_bojilu_A[640] = {0}, Phase_Differ_average[3] = {0}, QPhase_Differ_average[3] = {0}, Phase_Differ_buffer1[3] = {0};
volatile signed int Phase_Differ_A_one[16] = {0}, Phase_Differ_B_one[16] = {0}, Phase_Differ_C_one[16] = {0};
volatile signed int Phase_Differ_A_Two_Av = 0, Phase_Differ_B_Two_Av = 0, Phase_Differ_C_Two_Av = 0;
volatile unsigned int Power_pool[161] = {
    1000, 1000, 1000, 1000, 999, 999, 998, 998, 997, 996,
    995, 994, 993, 992, 991, 989, 988, 986, 984, 983,
    981, 979, 977, 975, 972, 970, 968, 965, 962, 960,
    957, 954, 951, 948, 945, 942, 938, 935, 931, 928,
    924, 920, 916, 912, 908, 904, 900, 895, 891, 887,
    882, 877, 872, 868, 863, 858, 853, 847, 842, 837,
    831, 826, 820, 815, 809, 803, 797, 791, 785, 779,
    773, 767, 760, 754, 748, 741, 734, 728, 721, 714,
    707, 700, 693, 686, 679, 672, 664, 657, 649, 642,
    634, 627, 619, 611, 604, 596, 588, 580, 572, 564,
    556, 547, 539, 531, 522, 514, 506, 497, 489, 480,
    471, 463, 454, 445, 436, 428, 419, 410, 401, 392,
    383, 374, 364, 355, 346, 337, 328, 318, 309, 300,
    290, 281, 271, 262, 252, 243, 233, 224, 214, 205,
    195, 185, 176, 166, 156, 147, 137, 127, 118, 108,
    98, 88, 78, 69, 59, 49, 39, 29, 20, 10, 0

};
volatile signed int AD_tmp_V_Power[3] = {0}, AD_tmp_I_Power[3] = {0}, AD_tmp_V_Power_Zero[3] = {0}, AD_tmp_I_Power_Zero[3] = {0};
volatile signed int AD_tmp_I_PowerA[2] = {0}, AD_tmp_I_PowerB[2] = {0}, AD_tmp_I_PowerC[2] = {0};

volatile unsigned char TH_hezha_delay;
volatile unsigned char hezha_delay;
volatile unsigned char hezha_delay_arry[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //

unsigned char hezha_delay_show[10][4] =
    {
        "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s"};

#endif
