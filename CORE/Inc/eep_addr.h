#ifndef __EEP_ADDR_H
#define __EEP_ADDR_H



#define F_vison 0 // 编译条件定义
/*************************************
          内部存储第0页
          包括：校准值；档位，控制字；
                累计记录；事件记录
                部分参数变量
**************************************/
#define Addr_FACTORINIT_value 10000 // 2字节，初始化标志
#define Addr_point_event_trip 10003 // 2字节，内部记录跳闸记录
#define Addr_L_factor 10005         // 2字节，漏电校准值
#define Addr_V_factor 10007         // 2字节，电压校准值
#define Addr_I_factor 10009         // 2字节，电流校准值
#define Addr_I_2d 10011             // 1字节，二段保护功能
#define Addr_I_ia 10012             // 1字节，电流重合闸保护功能
#define Addr_L_TB 10013             // 1字节，突变保护功能
#define Addr_C_IP 10014             // 1字节，短路短延时功能
#define Addr_L_JC 10015
#define Addr_F_gc 10146
#define Addr_crtl_word1 10018   // 1字节，控制字1
#define Addr_crtl_word2 10019   // 1字节，控制字2
#define Addr_crtl_word3 10020   // 1字节，控制字3
#define Addr_crtl_word4 10021   // 1字节，控制字4
#define Addr_crtl_word5 10022   // 1字节，控制字5
#define Addr_ctrlword 10018     // 4字节，控制字1-5
#define Addr_Type_Cur 10023     // 1字节，电流壳架等级
#define Addr_Vol_g 10024        // 1字节，过压档位
#define Addr_Vol_q 10025        // 1字节，欠压档位
#define Addr_D_A_Lcur 10026     // 1字节，漏电自动档位
#define Addr_D_Cur 10500        // 4字节，电流档位
#define Addr_baud 10028         // 1字节，波特率
#define Addr_dev_addr 10029     // 6字节，设备通信地址
#define Addr_clear_num 10035    // 3字节，清零次数
#define Addr_trip_num 10038     // 2字节，总跳闸次数
#define Addr_close_num 10040    // 2字节，闭锁跳闸次数
#define Addr_leak_num 10042     // 2字节，漏电跳闸次数
#define Addr_current_num 10044  // 2字节，电流跳闸次数
#define Addr_vol_num 10046      // 2字节，电压跳闸次数
#define Addr_hand_num 10048     // 2字节，手动跳闸次数
#define Addr_zero_num 10050     // 2字节，缺零跳闸次数
#define Addr_test_num 10052     // 2字节，测试跳闸次数
#define Addr_leakquit_num 10054 // 2字节，漏电退运次数
#define Addr_2D_num 10410       // 2字节，短路延时跳闸次数
#define Addr_3D_num 10412       // 2字节，短路瞬时跳闸次数
#define Addr_leakover_num 10414 // 1字节，剩余电流超限次数
// #define Addr_tripkey_num       10416   //1字节，自检次数
#define Addr_leakprotect_num 10416 // 1字节，剩余电流保护退出报警次数
// #define Addr_leakchange_num    10417   //1字节，剩余电流保护变化次数

#define Addr_protect_time 10056 // 4字节，运行总时间
#define Addr_dev_id 10060       // 6字节，设备号
#define Addr_dev_code 10066     // 32字节，资产代码
#define Addr_equi_type 10098    // 10字节，设备类型
#define Addr_factory_code 10108 // 24字节，厂家代码
#define Addr_0_password 10132   // 4字节，密码0
#define Addr_1_password 10136   // 4字节，密码1
#define Addr_2_password 10140   // 4字节，密码2
#define Addr_Vol_ch 10147       // 过欠压重合闸

#define Addr_I_3d 10250
#define Addr_D2_Cur 10251
#define Addr_D3_Cur 10252
#define Addr_D2_Time 10253
#define Addr_CurLong_Time 10254
#define Addr_DD_LL 10256
#define Addr_SY_yanshi 10291
#define Addr_GY_yanshi 10257
#define Addr_QY_yanshi 10258
#define Addr_QX_BAOHU 10259
#define Addr_QL_BAOHU 10260
#define Addr_shangdian 10261
#define Addr_loudian 10264
#define Addr_dianya 1002  // 1字节
#define Addr_dianliu 1001 // 1字节
#define Addr_jiaozhun 10300
#define Addr_DIANYA_chonghe 10262
#define Addr_duandian 10263
#define Addr_tingdian 10283 // 已用
#define Addr_SY_F 10288
// #define Addr_SY_T    10291	//2字节，电流校准值
#define Addr_data_clear 10316

#define Addr_AV_factor 10265 // 2字节，电压校准值
#define Addr_BV_factor 10267 // 2字节，电流校准值
#define Addr_CV_factor 10269 // 2字节，电压校准值
#define Addr_AI_factor 10271 // 2字节，电流校准值
#define Addr_BI_factor 10273 // 2字节，电压校准值
#define Addr_CI_factor 10275 // 2字节，电流校准值

#define Addr_L_F 10276  // 2字节，电压校准值
#define Addr_AV_F 10277 // 2字节，电压校准值
#define Addr_BV_F 10278 // 2字节，电流校准值
#define Addr_CV_F 10279 // 2字节，电压校准值
#define Addr_AI_F 10280 // 2字节，电流校准值
#define Addr_BI_F 10281 // 2字节，电压校准值
#define Addr_CI_F 10282 // 2字节，电流校准值

#define Addr_L1_slope 10304
#define Addr_V1_A_slope 10306
#define Addr_V1_B_slope 10308
#define Addr_V1_C_slope 10310

#define Addr_I1_A_slope 10312 // 250壳架
#define Addr_I1_B_slope 10314
#define Addr_I1_C_slope 10316

#define Addr_I1_A_slope1 10318
#define Addr_I1_B_slope1 10320
#define Addr_I1_C_slope1 10322

#define Addr_CurA_cal_tmp 10324
#define Addr_CurB_cal_tmp 10326
#define Addr_CurC_cal_tmp 10328

#define Addr_CurA_cal_tmp1 10330
#define Addr_CurB_cal_tmp1 10332
#define Addr_CurC_cal_tmp1 10334

#define Addr_Leak1_temp 10336

#define Addr_Vol1_A_temp 10338
#define Addr_Vol1_B_temp 10340
#define Addr_Vol1_C_temp 10342

#define Addr400_I1_A_slope 10344 // 400壳架
#define Addr400_I1_B_slope 10346
#define Addr400_I1_C_slope 10348

#define Addr400_I1_A_slope1 10350
#define Addr400_I1_B_slope1 10352
#define Addr400_I1_C_slope1 10354

#define Addr400_CurA_cal_tmp 10356
#define Addr400_CurB_cal_tmp 10358
#define Addr400_CurC_cal_tmp 10360

#define Addr400_CurA_cal_tmp1 10362
#define Addr400_CurB_cal_tmp1 10364
#define Addr400_CurC_cal_tmp1 10366

#define Addr630_I1_A_slope 10368 // 630壳架
#define Addr630_I1_B_slope 10370
#define Addr630_I1_C_slope 10372

#define Addr630_I1_A_slope1 10374
#define Addr630_I1_B_slope1 10376
#define Addr630_I1_C_slope1 10378

#define Addr630_CurA_cal_tmp 10380
#define Addr630_CurB_cal_tmp 10382
#define Addr630_CurC_cal_tmp 10384

#define Addr630_CurA_cal_tmp1 10386
#define Addr630_CurB_cal_tmp1 10388
#define Addr630_CurC_cal_tmp1 10390

#define Addr800_I1_A_slope 10392 // 800壳架
#define Addr800_I1_B_slope 10394
#define Addr800_I1_C_slope 10396

#define Addr800_I1_A_slope1 10398
#define Addr800_I1_B_slope1 10400
#define Addr800_I1_C_slope1 10402

#define Addr800_CurA_cal_tmp 10404
#define Addr800_CurB_cal_tmp 10406
#define Addr800_CurC_cal_tmp 10408

#define Addr800_CurA_cal_tmp1 10410
#define Addr800_CurB_cal_tmp1 10412
#define Addr800_CurC_cal_tmp1 10414

#define Addr100_I1_A_slope 10416 // 100壳架
#define Addr100_I1_B_slope 10418
#define Addr100_I1_C_slope 10420

/****无电压校准2024 6 18 崔家铭*****/
#define Addr100_I1_A_slope_nv 10526 // 100壳架无电压
#define Addr100_I1_B_slope_nv 10528
#define Addr100_I1_C_slope_nv 10530
#define Addr100_CurA_cal_tmp_nv 10532
#define Addr100_CurB_cal_tmp_nv 10534
#define Addr100_CurC_cal_tmp_nv 10536

#define Addr_I1_A_slope_nv 10538 // 250壳架
#define Addr_I1_B_slope_nv 10540
#define Addr_I1_C_slope_nv 10542

#define Addr_CurA_cal_tmp_nv 10544
#define Addr_CurB_cal_tmp_nv 10546
#define Addr_CurC_cal_tmp_nv 10548

#define Addr400_I1_A_slope_nv 10550 // 400壳架
#define Addr400_I1_B_slope_nv 10552
#define Addr400_I1_C_slope_nv 10554

#define Addr400_CurA_cal_tmp_nv 10556
#define Addr400_CurB_cal_tmp_nv 10558
#define Addr400_CurC_cal_tmp_nv 10560

#define Addr630_I1_A_slope_nv 10562 // 630壳架
#define Addr630_I1_B_slope_nv 10564
#define Addr630_I1_C_slope_nv 10566

#define Addr630_CurA_cal_tmp_nv 10568
#define Addr630_CurB_cal_tmp_nv 10570
#define Addr630_CurC_cal_tmp_nv 10572

#define Addr800_I1_A_slope_nv 10574 // 800壳架
#define Addr800_I1_B_slope_nv 10576
#define Addr800_I1_C_slope_nv 10578

#define Addr800_CurA_cal_tmp_nv 10580
#define Addr800_CurB_cal_tmp_nv 10582
#define Addr800_CurC_cal_tmp_nv 10584

#define Addr100_I1_A_slope1_nv 10586 // 100壳架无电压
#define Addr100_I1_B_slope1_nv 10588
#define Addr100_I1_C_slope1_nv 10590
#define Addr100_CurA_cal_tmp1_nv 10592
#define Addr100_CurB_cal_tmp1_nv 10594
#define Addr100_CurC_cal_tmp1_nv 10596

#define Addr_I1_A_slope1_nv 10598 // 250壳架
#define Addr_I1_B_slope1_nv 10600
#define Addr_I1_C_slope1_nv 10602

#define Addr_CurA_cal_tmp1_nv 10604
#define Addr_CurB_cal_tmp1_nv 10606
#define Addr_CurC_cal_tmp1_nv 10608

#define Addr400_I1_A_slope1_nv 10610 // 400壳架
#define Addr400_I1_B_slope1_nv 10612
#define Addr400_I1_C_slope1_nv 10614

#define Addr400_CurA_cal_tmp1_nv 10616
#define Addr400_CurB_cal_tmp1_nv 10618
#define Addr400_CurC_cal_tmp1_nv 10620

#define Addr630_I1_A_slope1_nv 10622 // 630壳架
#define Addr630_I1_B_slope1_nv 10624
#define Addr630_I1_C_slope1_nv 10626

#define Addr630_CurA_cal_tmp1_nv 10628
#define Addr630_CurB_cal_tmp1_nv 10630
#define Addr630_CurC_cal_tmp1_nv 10632

#define Addr800_I1_A_slope1_nv 10634 // 800壳架
#define Addr800_I1_B_slope1_nv 10636
#define Addr800_I1_C_slope1_nv 10638

#define Addr800_CurA_cal_tmp1_nv 10640
#define Addr800_CurB_cal_tmp1_nv 10642
#define Addr800_CurC_cal_tmp1_nv 10644
/****无电压校准结束*****/
#define Addr100_I1_A_slope1 10422
#define Addr100_I1_B_slope1 10424
#define Addr100_I1_C_slope1 10426

#define Addr100_CurA_cal_tmp 10428
#define Addr100_CurB_cal_tmp 10430
#define Addr100_CurC_cal_tmp 10432

#define Addr100_CurA_cal_tmp1 10434
#define Addr100_CurB_cal_tmp1 10436
#define Addr100_CurC_cal_tmp1 10438

#define Addr100_L1_slope 10440
#define Addr400_L1_slope 10442
#define Addr630_L1_slope 10444
#define Addr800_L1_slope 10446

#define Addr100_Leak1_temp 10448
#define Addr400_Leak1_temp 10450
#define Addr630_Leak1_temp 10452
#define Addr800_Leak1_temp 10454

#define Addr_alarm_value 12   // 2字节，漏电超限告警整定值
#define Addr_record_value 14  // 2字节，漏电记录差值整定值
#define Addr_record_time 16   // 2字节，漏电记录定时整定值
#define Addr_timed_trip 18    // 3字节，定时试跳设定时间
#define Addr_over_vol 21      // 2字节，过压整定值
#define Addr_under_vol 23     // 2字节，欠压整定值
#define Addr_break_phase 25   // 2字节，缺相整定值
#define Addr_rated_current 27 // 3字节，额定电流整定值
#define Addr_over_current 30  // 1字节，电流超限报警整定值
#define Addr_remote_trip 31   // 2字节，远程跳闸时间
#define Addr_remote_close 33  // 2字节，远程合闸时间
#define Addr_analog_trip 35   // 2字节，远程模拟试跳时间

#define Addr_leak_valve 188
#define Addr_leak_time 208
#define Addr_break_time 218

#define Addr_max_leak 346  // 漏电最大值
#define Addr_max_Avol 634  // A相电压最大值
#define Addr_max_Bvol 922  // B相电压最大值
#define Addr_max_Cvol 1210 // C相电压最大值
#define Addr_max_Acur 1498 // A相电流最大值
#define Addr_max_Bcur 1786 // B相电流最大值
#define Addr_max_Ccur 2074 // C相电流最大值
#define Addr_min_leak 2362 // 漏电最小值
#define Addr_min_Avol 2650 // A相电压最小值
#define Addr_min_Bvol 2938 // B相电压最小值
#define Addr_min_Cvol 3226 // C相电压最小值
#define Addr_min_Acur 3514 // A相电流最小值
#define Addr_min_Bcur 3802 // B相电流最小值
#define Addr_min_Ccur 4090 // C相电流最小值

#define Addr_event_leak 4378   // 漏电事件
#define Addr_event_self 4528   // 自检事件
#define Addr_event_trip 4788   // 跳闸事件
#define Addr_event_alarm 5038  // 告警事件
#define Addr_record_leak1 5158 // 漏电记录1
#define Addr_record_leak2 7462 // 漏电记录2

#define Addr_point_leak_max 9766
#define Addr_point_Avol_max 9767
#define Addr_point_Bvol_max 9768
#define Addr_point_Cvol_max 9769
#define Addr_point_Acur_max 9770
#define Addr_point_Bcur_max 9771
#define Addr_point_Ccur_max 9772
#define Addr_point_leak_min 9773
#define Addr_point_Avol_min 9774
#define Addr_point_Bvol_min 9775
#define Addr_point_Cvol_min 9776
#define Addr_point_Acur_min 9777
#define Addr_point_Bcur_min 9778
#define Addr_point_Ccur_min 9779
#define Addr_point_leakrecord 9780
#define Addr_point_event_trip_24C256 9782
#define Addr_point_event_self 9783
#define Addr_F_GJ_FUNC 9800
#define Addr_point_event_leak 9801
// 宏定义    普通校准      地址        长度       含义       段
#define Addr_Vol_ad 9802    // 18   3*2*3  3相*两点*一个点长度3（实际占用2字节）
#define Addr_Vol_slope 9820 // 18
#define Addr_Vol_Disp 9838  // 18

#define Addr_Leak_ad 9856    // 6               三点校准*一个点长度2
#define Addr_Leak_slope 9862 // 6
#define Addr_Leak_Disp 9868  // 6

#define Addr_Cur_250 9874       // 30 			5*2*3  ad值 五点*2字节*三相
#define Addr_Cur_slope_250 9904 // 30 	5*2*3  斜率
#define Addr_Cur_Disp_250 9934  // 30 			5*2*3  实际接收到的校准点的值（例如10、50、300等）
// 最值记录  段
#define Addr_min_Avol_TD 10800 // 4
#define Addr_min_Bvol_TD 10804 // 4
#define Addr_min_Cvol_TD 10808 // 4
#define Addr_max_Avol_TD 10812 // 4
#define Addr_max_Bvol_TD 10816 // 4
#define Addr_max_Cvol_TD 10820 // 4

/****四位密码1*4=4字节（2022.2.21温州杨济恺加）*****/
#define Addr_mima_set 10824      // 4
#define Addr_L_specialwave 10828 // 1

/*****漏电延时档位***********/
#define Addr_TH_LCur 12000 // 1

/*****电机合闸延时档位***********/
#define Addr_hezha_delay 13000

/***************************瞬动校准*********************************/
#define Addr_DLS_Cur_IV_AD_value 10900 // 45			5*3 ad值 五点*3字节
#define Addr_DLS_Cur_IV_slope 10915    // 45			5*3  斜率
#define Addr_DLS_Cur_IV_Value 10930    // 45			5*3 瞬动电流值

#define Addr_DLS_Cur_I_AD_value 10945 // 45			5*3  ad值 五点*3字节
#define Addr_DLS_Cur_I_slope 10960    // 45			5*3  斜率
#define Addr_DLS_Cur_I_Value 10975    // 45			5*3 瞬动电流值

#define Addr_DLS_Cur_II_AD_value 10990 // 45			5*3  ad值 五点*3字节
#define Addr_DLS_Cur_II_slope 11005    // 45			5*3  斜率
#define Addr_DLS_Cur_II_Value 11020    // 45			5*3 瞬动电流值

#define Addr_DLS_Cur_III_AD_value 11035 // 45			5*3  ad值 五点*3字节
#define Addr_DLS_Cur_III_slope 11050    // 45			5*3  斜率
#define Addr_DLS_Cur_III_Value 11065    // 45			5*3 瞬动电流值
/*************************************/

//短接分合闸模式地址
#define External_Gate_Control_Flag_Addr 13010 

#endif