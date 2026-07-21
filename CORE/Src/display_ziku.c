#include "display_ziku.h"
#include "LCD.h"
#include "ziku.h"
#include "disp.h"
#include "delay.h"
extern void putchar(unsigned char dat);
unsigned char display_graphic_16x16(uchar page, uchar column, uchar *dp)
{
    uchar i, j;
    // cs1 = 0;
    for (j = 0; j < 2; j++)
    {
        lcd_address(page + j, column);

        for (i = 0; i < 16; i++)
        {
            transfer_data(*dp);
            dp++;
        }
    }
    // cs1 = 1;
    return (16);
}

unsigned char display_graphic_quanping(uchar page, uchar column, uchar *dp)
{
    uchar i, j;
    // cs1 = 0;
    for (j = 0; j < 8; j++)
    {
        lcd_address(page + j, column);

        for (i = 0; i < 128; i++)
        {
            transfer_data(*dp);
            dp++;
        }
    }
    // cs1 = 1;
    return (16);
}

void display_xianfangkuai(unsigned char x0, uchar y0, unsigned char daxiao, unsigned char yuan_fang)
{

    if (yuan_fang == 1)
    {
        //		display_graphic_16x16(x0,y0,sanjiao);
    }
    else
    {
        if (daxiao == 0)
        {
            display_graphic_16x16(x0, y0, xiaofuangkuai);
        }
        else if (daxiao == 1)
        {
            display_graphic_16x16(x0, y0, dafuangkuai);
        }
    }
}

unsigned char Lcd12864_Write8CnCHAR(unsigned char F_rever, unsigned char x, unsigned char y, unsigned char *cn)

{
    unsigned char j, x1, x2, wordNum, k, n, x0, y0;
    unsigned char *zifuchuan = cn;

    x0 = x;
    y0 = y;
    y0 += 0xB0; // 起始列给  求取Y坐标的值

    transfer_command(y0);
    while (*zifuchuan != '\0') // 字符串结束以0结束
    {

        transfer_command(y0); // 设置Y坐标

        x1 = (x0 >> 4) & 0x0F;
        x2 = x0 & 0x0F;

        transfer_command(0x10 + x1);
        transfer_command(0x04 + x2); // X坐标分为高四位和低四位

        if (*zifuchuan > 0x80)
        {
            for (wordNum = 0; wordNum < 93; wordNum++)
            {
                // 查询要写的字在字库中的位置
                if ((CN16CHAR[wordNum].Index[0] == *zifuchuan) && (CN16CHAR[wordNum].Index[1] == *(zifuchuan + 1)))
                {
                    for (j = 0; j < 16; j++) // 写一个字
                    {
                        if (j == 8) // 大于等于16时切换作
                        {
                            transfer_command(y0 + 1);
                            transfer_command(0x10 + x1);
                            transfer_command(0x04 + x2);
                        }
                        transfer_data(CN16CHAR[wordNum].Msk[j]);
                    }
                    x0 += 5;
                }
            }
            zifuchuan += 2;
        }
        else
        {
            if (*zifuchuan == '\r')
            {

                y0 = y0 + 2;
                x0 = 0;
                zifuchuan++;
                transfer_command(y0);

                x1 = (x0 >> 4) & 0x0F;
                x2 = x0 & 0x0F;

                transfer_command(0x10 + x1);
                transfer_command(0x04 + x2);
            }

            else
            {
                if ((x0 + 8) > 128)
                {
                    x0 = 0;
                    y0 = y0 + 2;
                    if (y0 > 63)
                    {
                        y0 = 0;
                    }
                }

                for (n = 0; n < 2; n++)
                {

                    transfer_command(y0 + n);

                    transfer_command(0x10 + x1);
                    transfer_command(0x04 + x2);
                    for (k = 0; k < 8; k++)
                    {

                        transfer_data(ascii_table_8x16[*zifuchuan - 0x20][k + 8 * n]);
                    }
                }
                x0 += 5;
                zifuchuan += 1;
            }
        }
    }

    return 1;
}

unsigned char Lcd12864_Write16CnCHAR(unsigned char F_rever, unsigned char x, unsigned char y, unsigned char *cn)
{
    unsigned char j, x1, x2, wordNum, k, n, x0, y0;
    unsigned char *zifuchuan = cn;

    x0 = x;
    y0 = y;
    y0 += 0xB0; // 起始列给  求取Y坐标的值

    transfer_command(y0);
    while (*zifuchuan != '\0') // 字符串结束以0结束
    {

        transfer_command(y0); // 设置Y坐标
        x1 = (x0 >> 4) & 0x0F;
        x2 = x0 & 0x0F;

        transfer_command(0x10 + x1);
        transfer_command(0x04 + x2); // X坐标分为高四位和低四位
        //		 lcd_address(x0,y0);

        if (*zifuchuan > 0x80)
        {
            for (wordNum = 0; wordNum < 150; wordNum++)
            {
                // 查询要写的字在字库中的位置
                if ((CN16CHAR[wordNum].Index[0] == *zifuchuan) && (CN16CHAR[wordNum].Index[1] == *(zifuchuan + 1)))
                {
                    for (j = 0; j < 32; j++) // 写一个字
                    {
                        if (j == 16) // 大于等于16时切换作
                        {
                            transfer_command(y0 + 1);
                            transfer_command(0x10 + x1);
                            transfer_command(0x04 + x2);
                        }
                        transfer_data(CN16CHAR[wordNum].Msk[j]);
                    }
                    x0 += 16;
                }
            }
            zifuchuan += 2;
        }
        else
        {
            if (*zifuchuan == '\r')
            {

                y0 = y0 + 2;
                x0 = 0;
                zifuchuan++;
                transfer_command(y0);

                x1 = (x0 >> 4) & 0x0F;
                x2 = x0 & 0x0F;

                transfer_command(0x10 + x1);
                transfer_command(0x04 + x2);
            }

            else
            {
                if ((x0 + 8) > 128)
                {
                    x0 = 0;
                    y0 = y0 + 2;
                    if (y0 > 63)
                    {
                        y0 = 0;
                    }
                }

                for (n = 0; n < 2; n++)
                {

                    transfer_command(y0 + n);

                    transfer_command(0x10 + x1);
                    transfer_command(0x04 + x2);
                    for (k = 0; k < 8; k++)
                    {

                        transfer_data(ascii_table_8x16[*zifuchuan - 0x20][k + 8 * n]);
                    }
                }
                x0 += 8;
                zifuchuan += 1;
            }
        }
    }
    return 1;
}
unsigned char Lcd12864_Write12CnCHAR(unsigned char F_rever, unsigned char x, unsigned char y, unsigned char *cn)
{
    unsigned char j, x1, x2, wordNum, k, n, x0, y0;
    unsigned char *zifuchuan = cn;

    x0 = x;
    y0 = y;
    y0 += 0xB0; // 起始列给  求取Y坐标的值

    transfer_command(y0);
    while (*zifuchuan != '\0') // 字符串结束以0结束
    {
        transfer_command(y0); // 设置Y坐标
        x1 = (x0 >> 4) & 0x0F;
        x2 = x0 & 0x0F;
        transfer_command(0x10 + x1);
        transfer_command(0x00 + x2); // X坐标分为高四位和低四位

        if (*zifuchuan > 0x80)
        {
            if (F_rever == 0)
            {
                for (wordNum = 0; wordNum < sizeof(CN12CHAR) / 24; wordNum++)
                {
                    // 查询要写的字在字库中的位置
                    if ((CN12CHAR[wordNum].Index[0] == *zifuchuan) && (CN12CHAR[wordNum].Index[1] == *(zifuchuan + 1)))
                    {
                        for (j = 0; j < 24; j++) // 写一个字
                        {
                            if (j == 12) // 大于等于12时切换作
                            {
                                transfer_command(y0 + 1);
                                transfer_command(0x10 + x1); // 设置列地址高位
                                transfer_command(0x00 + x2); // 设置列地址低位
                            }
                            transfer_data(CN12CHAR[wordNum].Msk[j]);
                        }
                        x0 += 12;
                    }
                }
                zifuchuan += 2;
            }
            else if (F_rever == 1)
            {
                for (wordNum = 0; wordNum < sizeof(CN12CHAR) / 24; wordNum++)
                {
                    // 查询要写的字在字库中的位置
                    if ((CN12CHAR[wordNum].Index[0] == *zifuchuan) && (CN12CHAR[wordNum].Index[1] == *(zifuchuan + 1)))
                    {
                        for (j = 0; j < 24; j++) // 写一个字
                        {
                            if (j == 12) // 大于等于12时切换作
                            {
                                transfer_command(y0 + 1);
                                transfer_command(0x10 + x1);
                                transfer_command(0x00 + x2);
                            }
                            transfer_data(~(CN12CHAR[wordNum].Msk[j]));
                        }
                        x0 += 12;
                    }
                }
                zifuchuan += 2;
            }
        }
        else
        {
            if (*zifuchuan == '\r')
            {
                y0 = y0 + 2;
                x0 = 0;
                zifuchuan++;
                transfer_command(y0);

                x1 = (x0 >> 4) & 0x0F;
                x2 = x0 & 0x0F;

                transfer_command(0x10 + x1);
                transfer_command(0x00 + x2);
            }
            else
            {
                if ((x0 + 6) > 128)
                {
                    x0 = 0;
                    y0 = y0 + 2;
                    if (y0 > 63)
                    {
                        y0 = 0;
                    }
                }

                for (n = 0; n < 2; n++)
                {
                    transfer_command(y0 + n);

                    transfer_command(0x10 + x1);
                    transfer_command(0x00 + x2);
                    if (F_rever == 0)
                    {
                        for (k = 0; k < 6; k++)
                        {
                            transfer_data(ascii_table_6x12[*zifuchuan - 0x20][k + 6 * n]);
                        }
                    }
                    else
                    {
                        for (k = 0; k < 6; k++)
                        {
                            transfer_data(~(ascii_table_6x12[*zifuchuan - 0x20][k + 6 * n]));
                        }
                    }
                }
                x0 += 6;
                zifuchuan += 1;
            }
        }
    }
    return 1;
}
unsigned char Lcd12864_Write24CnCHAR(unsigned char F_rever, unsigned char x, unsigned char y, unsigned char *cn)
{
    unsigned char j, x1, x2, wordNum, k, n, x0, y0;
    unsigned char *zifuchuan = cn;

    x0 = x;
    y0 = y;
    y0 += 0xB0; // 起始列给  求取Y坐标的值

    transfer_command(y0);
    while (*zifuchuan != '\0') // 字符串结束以0结束
    {
        transfer_command(y0); // 设置Y坐标
        x1 = (x0 >> 4) & 0x0F;
        x2 = x0 & 0x0F;
        transfer_command(0x10 + x1);
        transfer_command(0x00 + x2); // X坐标分为高四位和低四位

        if (*zifuchuan > 0x80)
        {
            if (F_rever == 0)
            {
                for (wordNum = 0; wordNum < sizeof(CN24CHAR) / 72; wordNum++)
                {
                    // 查询要写的字在字库中的位置
                    if ((CN24CHAR[wordNum].Index[0] == *zifuchuan) && (CN24CHAR[wordNum].Index[1] == *(zifuchuan + 1)))
                    {
                        for (j = 0; j < 72; j++) // 写一个字
                        {
                            if (j % 24 == 0 && j != 0) // 每24字节切换行
                            {
                                transfer_command(y0 + j / 24);
                                transfer_command(0x10 + x1);
                                transfer_command(0x00 + x2);
                            }
                            transfer_data(CN24CHAR[wordNum].Msk[j]);
                        }
                        x0 += 24;
                    }
                }
                zifuchuan += 2;
            }
            else if (F_rever == 1)
            {
                for (wordNum = 0; wordNum < sizeof(CN24CHAR) / 72; wordNum++)
                {
                    // 查询要写的字在字库中的位置
                    if ((CN24CHAR[wordNum].Index[0] == *zifuchuan) && (CN24CHAR[wordNum].Index[1] == *(zifuchuan + 1)))
                    {
                        for (j = 0; j < 72; j++) // 写一个字
                        {
                            if (j % 24 == 0 && j != 0) // 每24字节切换行
                            {
                                transfer_command(y0 + j / 24);
                                transfer_command(0x10 + x1);
                                transfer_command(0x00 + x2);
                            }
                            transfer_data(~(CN24CHAR[wordNum].Msk[j]));
                        }
                        x0 += 24;
                    }
                }
                zifuchuan += 2;
            }
        }
        else
        {
            if (*zifuchuan == '\r')
            {
                y0 = y0 + 3;
                x0 = 0;
                zifuchuan++;
                transfer_command(y0);

                x1 = (x0 >> 4) & 0x0F;
                x2 = x0 & 0x0F;

                transfer_command(0x10 + x1);
                transfer_command(0x00 + x2);
            }
            else
            {
                //                if ((x0 + 12) > 128)
                //                {
                //                    x0 = 0;
                //                    y0 = y0 + 3;
                //                    if (y0 > 63)
                //                    {
                //                        y0 = 0;
                //                    }
                //                }

                //                for (n = 0; n < 3; n++)
                //                {
                //                    transfer_command(y0 + n);

                //                    transfer_command(0x10 + x1);
                //                    transfer_command(0x00 + x2);
                //                    if (F_rever == 0)
                //                    {
                //                        for (k = 0; k < 12; k++)
                //                        {
                //                            transfer_data(ascii_table_12x24[*zifuchuan - 0x20][k + 12 * n]);
                //                        }
                //                    }
                //                    else
                //                    {
                //                        for (k = 0; k < 12; k++)
                //                        {
                //                            transfer_data(~(ascii_table_12x24[*zifuchuan - 0x20][k + 12 * n]));
                //                        }
                //                    }
                //                }
                //                x0 += 12;
                //                zifuchuan += 1;
            }
        }
    }
    return 1;
}

// unsigned char Lcd12864_Write25CnCHAR(unsigned char F_rever, unsigned char x, unsigned char y, unsigned char *cn)
//{
//     unsigned char j, x1, x2, wordNum, x0, y0;
//     unsigned char *zifuchuan = cn;

//    x0 = x;
//    y0 = y;
//    y0 += 0xB0; // 起始列给  求取Y坐标的值

//    transfer_command(y0);
//    while (*zifuchuan != '\0') // 字符串结束以0结束
//    {
//        transfer_command(y0); // 设置Y坐标
//        x1 = (x0 >> 4) & 0x0F;
//        x2 = x0 & 0x0F;
//        transfer_command(0x10 + x1);
//        transfer_command(0x00 + x2); // X坐标分为高四位和低四位

//        if (*zifuchuan > 0x80)
//        {
//            if (F_rever == 0)
//            {
//                for (wordNum = 0; wordNum < sizeof(CN25CHAR) / 50; wordNum++)
//                {
//                    // 查询要写的字在字库中的位置
//                    if ((CN25CHAR[wordNum].Index[0] == *zifuchuan) && (CN25CHAR[wordNum].Index[1] == *(zifuchuan + 1)))
//                    {
//                        for (j = 0; j < 50; j++) // 写一个字
//                        {
//                            if (j == 25) // 大于等于25时切换作
//                            {
//                                transfer_command(y0 + 1);
//                                transfer_command(0x10 + x1); // 设置列地址高位
//                                transfer_command(0x00 + x2); // 设置列地址低位
//                            }
//                            transfer_data(CN25CHAR[wordNum].Msk[j]);
//                        }
//                        x0 += 25;
//                    }
//                }
//                zifuchuan += 2;
//            }
//            else if (F_rever == 1)
//            {
//                for (wordNum = 0; wordNum < sizeof(CN25CHAR) / 50; wordNum++)
//                {
//                    // 查询要写的字在字库中的位置
//                    if ((CN25CHAR[wordNum].Index[0] == *zifuchuan) && (CN25CHAR[wordNum].Index[1] == *(zifuchuan + 1)))
//                    {
//                        for (j = 0; j < 50; j++) // 写一个字
//                        {
//                            if (j == 25) // 大于等于25时切换作
//                            {
//                                transfer_command(y0 + 1);
//                                transfer_command(0x10 + x1);
//                                transfer_command(0x00 + x2);
//                            }
//                            transfer_data(~(CN25CHAR[wordNum].Msk[j]));
//                        }
//                        x0 += 25;
//                    }
//                }
//                zifuchuan += 2;
//            }
//        }
//        else
//        {
//            if (*zifuchuan == '\r')
//            {
//                y0 = y0 + 2;
//                x0 = 0;
//                zifuchuan++;
//                transfer_command(y0);

//                x1 = (x0 >> 4) & 0x0F;
//                x2 = x0 & 0x0F;

//                transfer_command(0x10 + x1);
//                transfer_command(0x00 + x2);
//            }
//            else
//            {
////                if ((x0 + 13) > 128) // ASCII 字符宽度假设为13像素
////                {
////                    x0 = 0;
////                    y0 = y0 + 2;
////                    if (y0 > 63)
////                    {
////                        y0 = 0;
////                    }
////                }

////                for (unsigned char n = 0; n < 2; n++)
////                {
////                    transfer_command(y0 + n);

////                    transfer_command(0x10 + x1);
////                    transfer_command(0x00 + x2);
////                    if (F_rever == 0)
////                    {
////                        for (unsigned char k = 0; k < 13; k++) // ASCII 字符宽度假设为13像素
////                        {
////                            transfer_data(ascii_table_13x25[*zifuchuan - 0x20][k + 13 * n]);
////                        }
////                    }
////                    else
////                    {
////                        for (unsigned char k = 0; k < 13; k++)
////                        {
////                            transfer_data(~(ascii_table_13x25[*zifuchuan - 0x20][k + 13 * n]));
////                        }
////                    }
////                }
////                x0 += 13;
////                zifuchuan += 1;
//            }
//        }
//    }
//    return 1;
//}

void display_ASCIIstring_6x12(unsigned char page, unsigned char column, unsigned char *text)
{
    unsigned char i = 0, j, k, n;
    unsigned char x0, y0;
    unsigned char *temp_text = text;
    x0 = page;
    y0 = column;

    while ((temp_text[i] > 0x00) && (temp_text[i] != '\0'))
    {
        if ((temp_text[i] >= 0x20) && (temp_text[i] < 0x7e))
        {
            j = temp_text[i] - 0x20;
            for (n = 0; n < 2; n++)
            {
                lcd_address(x0 + n, y0);
                for (k = 0; k < 6; k++)
                {
                    transfer_data(ascii_table_6x12[j][k + 6 * n]);
                }
            }
            i++;
            y0 += 6;
        }
    }
}

void display_ASCIIstring_6x12_with_underline(unsigned char page, unsigned char column, unsigned char *text)
{
    unsigned char i = 0, j, k, n;
    unsigned char x0, y0;
    unsigned char *temp_text = text;
    x0 = page;
    y0 = column;

    // Define the additional bytes to be ORed with the character data
    unsigned char or_mask[12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08};

    while ((temp_text[i] > 0x00) && (temp_text[i] != '\0'))
    {
        if ((temp_text[i] >= 0x20) && (temp_text[i] < 0x7e))
        {
            j = temp_text[i] - 0x20;
            for (n = 0; n < 2; n++)
            {
                lcd_address(x0 + n, y0);
                for (k = 0; k < 6; k++)
                {
                    // Apply the OR operation with corresponding mask byte
                    transfer_data(ascii_table_6x12[j][k + 6 * n] | or_mask[k + 6 * n]);
                }
            }
            i++;
            y0 += 6;
        }
    }
}

void display_ASCIIstring_6x12_right_align(unsigned char page, unsigned char column, unsigned char *text)
{
    unsigned char i = 0, j, k, n;
    unsigned char x0, y0;
    unsigned char *temp_text = text;
    unsigned char text_length = 0;

    // 计算字符串的长度
    while ((temp_text[text_length] > 0x00) && (temp_text[text_length] != '\0'))
    {
        text_length++;
    }

    // 计算右对齐起始列的位置
    x0 = page;
    y0 = column - text_length * 6;

    while ((temp_text[i] > 0x00) && (temp_text[i] != '\0'))
    {
        if ((temp_text[i] >= 0x20) && (temp_text[i] < 0x7e))
        {
            j = temp_text[i] - 0x20;
            for (n = 0; n < 2; n++)
            {
                lcd_address(x0 + n, y0);
                for (k = 0; k < 6; k++)
                {
                    transfer_data(ascii_table_6x12[j][k + 6 * n]);
                }
            }
            i++;
            y0 += 6;
        }
    }
}

void display_ASCIIstring_8x16(unsigned char page, unsigned char column, unsigned char *text)
{
    uchar i = 0, j, k, n;
    uchar x0, y0;
    uchar *temp_text = text;
    x0 = page;
    y0 = column;
    while ((temp_text[i] > 0x00) && (temp_text[i] != '\0'))
    {

        if ((temp_text[i] >= 0x20) && (temp_text[i] < 0x7e))
        {
            j = temp_text[i] - 0x20;
            for (n = 0; n < 2; n++)
            {
                lcd_address(x0 + n, y0);
                for (k = 0; k < 8; k++)
                {
                    transfer_data(ascii_table_8x16[j][k + 8 * n]);
                }
            }
            i++;
            y0 += 8;
        }
    }
}

void display_ASCIIstring_8x16_frame(unsigned char page, unsigned char column, unsigned char *text)
{
    unsigned char i = 0, j, k, n, m;
    unsigned char x0, y0;
    unsigned char Temp_display[16];
    unsigned char *temp_text = text;
    x0 = page;
    y0 = column;
    // cs1=0;
    while ((temp_text[i] > 0x00) && (temp_text[i] != '\0'))
    {
        if ((temp_text[i] >= 0x20) && (temp_text[i] < 0x7e))
        {
            j = temp_text[i] - 0x20;
            if (i == 0)
            {
                for (m = 0; m < 16; m++)
                {
                    Temp_display[m] = (ascii_table_8x16[j][m] | frame_8_16_left[m]);
                }
            }
            else
            {
                for (m = 0; m < 16; m++)
                {
                    Temp_display[m] = (ascii_table_8x16[j][m] | frame_8_16_shangxia[m]);
                }
            }

            for (n = 0; n < 2; n++)
            {
                lcd_address(x0 + n, y0);
                for (k = 0; k < 8; k++)
                {
                    //					if(i==0)
                    //					{
                    //					}

                    transfer_data(Temp_display[k + 8 * n]);
                    //				 transfer_data(ascii_table_8x16[j][k+8*n]);  //数字0的位置时0x20   //k+8*n 分别等于 0 1      8 9 10 11 12  13 14 15
                }
            }
            i++;
            y0 += 8;
        }
    }
    if ((temp_text[i - 1] >= 0x20) && (temp_text[i - 1] < 0x7e))
    {
        y0 -= 8;
        j = temp_text[i - 1] - 0x20;
        for (m = 0; m < 16; m++)
        {
            Temp_display[m] = (ascii_table_8x16[j][m] | frame_8_16_right[m]);
        }
        for (n = 0; n < 2; n++)
        {
            lcd_address(x0 + n, y0);
            for (k = 0; k < 8; k++)
            {
                //					if(i==0)
                //					{
                //					}

                transfer_data(Temp_display[k + 8 * n]);
                //				 transfer_data(ascii_table_8x16[j][k+8*n]);  //数字0的位置时0x20   //k+8*n 分别等于 0 1      8 9 10 11 12  13 14 15
            }
        }
    }
}

void display_sanjiao(unsigned char x0, unsigned char y0, unsigned char black_up, unsigned char black_down)
{

    if ((black_up == 1) && (black_down == 1))
    {
        display_graphic_16x16(x0, y0, sanjiao_black);
    }
    else if ((black_up == 1) && (black_down == 0))
    {
        display_graphic_16x16(x0, y0, sanjiao_shangblack);
    }
    else if ((black_up == 0) && (black_down == 1))
    {
        display_graphic_16x16(x0, y0, sanjiao_xiablack);
    }
    else if ((black_up == 0) && (black_down == 0))
    {
        display_graphic_16x16(x0, y0, sanjiao_white);
    }
}

void display_shouzhi(unsigned char x0, unsigned char y0)
{
    display_graphic_16x16(x0, y0, shouzhi);
}

void display_biankuang(unsigned char x0, unsigned char x1, unsigned char y0, unsigned char y1)
{
    unsigned char i, j;
    unsigned char x2, x3, y2, y3;
    x2 = x0;
    x3 = x1;
    y2 = y0;
    y3 = y1;

    // cs1=0;
    for (i = x2; i < x3; i++)
    {

        transfer_command(0xb0 + i); //

        transfer_command(((y2 >> 4) & 0x0f) + 0x10);
        transfer_command(y2 & 0x0f);
        for (j = y2; j < y3; j++)
        {
            transfer_data(0x00);
        }
    }
    // cs1=1;
}

unsigned char or_process(unsigned char *dp1, unsigned char *dp2)
{
    unsigned char i, j;
    unsigned char final_data[32];
    for (i = 0; i < 32; i++)
    {
        temp_frame[i] = dp1[i] | dp2[i];
        temp_frame[i] = dp1[i] | dp2[i];
    }
    j = j;
    //   *temp_frame=*final_data;
}

void display_kaiguan_frame(unsigned char x0, unsigned char y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = kai[i] | frame3[i];
            //			Temp_display[i]=dp1[i]|dp2[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
    else if (Flag == 0)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = guan[i] | frame3[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
}

void display_jiaozhun_frame(unsigned char x0, unsigned char y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = t_jz[i] | frame3[i];
            //			Temp_display[i]=dp1[i]|dp2[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
    else if (Flag == 0)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = key_jz[i] | frame3[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
}
void display_shifou_frame(unsigned char x0, uchar y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = keyi[i] | frame3[i];
            //			Temp_display[i]=dp1[i]|dp2[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
    else if (Flag == 0)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = fou[i] | frame3[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
}
void draw_horizontal_line(uint8_t y, uint8_t start_x, uint8_t end_x)
{
    if (y >= 64 || start_x >= 128 || end_x >= 128 || start_x > end_x)
    {
        // 参数无效，超出显示范围
        return;
    }

    uint8_t page = y / 8;         // 计算所在的页面
    uint8_t bit_position = y % 8; // 计算页面内的位位置

    // 设置页面地址
    transfer_command(0xb0 + page);
    // 设置列地址的高位和低位（从start_x开始）
    transfer_command(0x10 | (start_x >> 4));
    transfer_command(0x00 | (start_x & 0x0F));

    for (uint8_t x = start_x; x <= end_x; x++)
    {
        // 传输数据，设置指定行的位
        transfer_data(1 << bit_position);
    }
}
void display_kaiguan(unsigned char x0, uchar y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        //		for(i=0;i<32;i++)
        //		{
        //		  Temp_display[i]=kai[i];
        ////			Temp_display[i]=dp1[i]|dp2[i];
        //		}
        //		display_graphic_16x16(x0,y0,Temp_display);
        Lcd12864_Write12CnCHAR(0, y0, x0 - 1, "启用");
    }
    else if (Flag == 0)
    {
        //		for(i=0;i<32;i++)
        //		{
        //		  Temp_display[i]=guan[i];
        //		}
        //			display_graphic_16x16(x0,y0,Temp_display);
        Lcd12864_Write12CnCHAR(0, y0, x0 - 1, "禁用");
    }
}

void display_jiaozhun(unsigned char x0, unsigned char y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = t_jz[i];
            //			Temp_display[i]=dp1[i]|dp2[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
    else if (Flag == 0)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = key_jz[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
}
void display_shifou(unsigned char x0, uchar y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = keyi[i];
            //			Temp_display[i]=dp1[i]|dp2[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
    else if (Flag == 0)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = fou[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
}

unsigned char display_graphic_8x16(unsigned char page, unsigned char column, unsigned char *dp)
{
    uchar i, j;
    // cs1 = 0;
    for (j = 0; j < 2; j++)
    {
        lcd_address(page + j, column);

        for (i = 0; i < 8; i++)
        {
            transfer_data(*dp);
            dp++;
        }
    }
    // cs1 = 1;
    return (16);
}
unsigned char display_graphic_6x12(unsigned char page, unsigned char column, unsigned char *dp)
{
    uchar i, j;

    for (j = 0; j < 2; j++)
    {
        lcd_address(page + j, column);

        for (i = 0; i < 6; i++)
        {
            transfer_data(*dp);
            dp++;
        }
    }
    return 12;
}

unsigned char display_graphic_1x16(unsigned char page, unsigned char column, unsigned char *dp)
{
    uchar i, j;
    // cs1 = 0;
    for (j = 0; j < 2; j++)
    {
        lcd_address(page + j, column);

        for (i = 0; i < 1; i++)
        {
            transfer_data(*dp);
            dp++;
        }
    }
    // cs1 = 1;
    return (16);
}

unsigned char display_graphic_2x16(unsigned char page, unsigned char column, unsigned char *dp)
{
    uchar i, j;
    // cs1 = 0;
    for (j = 0; j < 2; j++)
    {
        lcd_address(page + j, column);

        for (i = 0; i < 2; i++)
        {
            transfer_data(*dp);
            dp++;
        }
    }
    // cs1 = 1;
    return (16);
}

void display_kaiguan_fanxian(unsigned char x0, unsigned char y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = ~kai[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
    else if (Flag == 0)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = ~guan[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
}
void display_jiaozhun_fanxian(unsigned char x0, unsigned char y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = ~t_jz[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
    else if (Flag == 0)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = ~key_jz[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
}

void display_shifou_fanxian(unsigned char x0, unsigned char y0, unsigned char Flag)
{
    unsigned char i;
    unsigned char Temp_display[32];
    if (Flag == 1)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = ~keyi[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
    else if (Flag == 0)
    {
        for (i = 0; i < 32; i++)
        {
            Temp_display[i] = ~fou[i];
        }
        display_graphic_16x16(x0, y0, Temp_display);
    }
}

void display_ASCIIstring_8x16_fanxian(unsigned char page, unsigned char column, unsigned char *text)
{
    uchar i = 0, j, k, n;
    uchar x0, y0;

    uchar *temp_text = text;
    x0 = page;
    y0 = column;
    while ((temp_text[i] > 0x00) && (temp_text[i] != '\0'))
    {

        if ((temp_text[i] >= 0x20) && (temp_text[i] < 0x7e))
        {
            j = temp_text[i] - 0x20;
            for (n = 0; n < 2; n++)
            {
                lcd_address(x0 + n, y0);
                for (k = 0; k < 8; k++)
                {

                    transfer_data((~ascii_table_8x16[j][k + 8 * n]));
                }
            }
            i++;
            y0 += 8;
        }
    }
}
