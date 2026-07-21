#include "24cxx.h"
#include "delay.h"
#include "myiic.h"

// 在AT24CXX指定地址读出一个数据
// ReadAddr:开始读数的地址
// 返回值  :读到的数据
u8 AT24CXX_ReadOneByte(u16 ReadAddr, u8 ChooseAddr)
{
    u8 temp = 0;
    IIC_Start();
    if (EE_TYPE > AT24C16)
    {
        IIC_Send_Byte(ChooseAddr); // 发送写命令
        IIC_Wait_Ack();
        IIC_Send_Byte(ReadAddr >> 8); // 发送高地址
        //		IIC_Wait_Ack();
    }
    else
        IIC_Send_Byte(ChooseAddr + ((ReadAddr / 256) << 1)); // 发送器件地址0XA0,写数据

    IIC_Wait_Ack();
    IIC_Send_Byte(ReadAddr % 256); // 发送低地址
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(ChooseAddr + 1); // 进入接收模式
    IIC_Wait_Ack();
    temp = IIC_Read_Byte(0);
    IIC_Stop(); // 产生一个停止条件
    return temp;
}
u8 AT24CXX_ReadLongByte(u16 ReadAddr, u8 length, u8 *ps, u8 ChooseAddr)
{
    IIC_Start();
    if (EE_TYPE > AT24C16)
    {
        IIC_Send_Byte(ChooseAddr); // 发送写命令
        IIC_Wait_Ack();
        IIC_Send_Byte(ReadAddr >> 8); // 发送高地址
        //		IIC_Wait_Ack();
    }
    else
        IIC_Send_Byte(ChooseAddr + ((ReadAddr / 256) << 1)); // 发送器件地址0XA0,写数据

    IIC_Wait_Ack();
    IIC_Send_Byte(ReadAddr % 256); // 发送低地址
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(ChooseAddr + 1); // 进入接收模式
    IIC_Wait_Ack();
    for (; --length > 0; ps++)
    {
        *ps = IIC_Read_Byte(1);
        //			IIC_Ack();
    }
    *ps = IIC_Read_Byte(0);
    //		IIC_NAck();
    IIC_Stop();
    return 0;
}
// 在AT24CXX指定地址写入一个数据
// WriteAddr  :写入数据的目的地址
// DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(u16 WriteAddr, unsigned char DataToWrite, unsigned char ChooseAddr)
{
    IIC_Start();
    if (EE_TYPE > AT24C16)
    {
        IIC_Send_Byte(ChooseAddr); // 发送写命令
        IIC_Wait_Ack();
        IIC_Send_Byte(WriteAddr >> 8); // 发送高地址
    }
    else
    {
        IIC_Send_Byte(ChooseAddr + ((WriteAddr / 256) << 1)); // 发送器件地址0XA0,写数据
    }
    IIC_Wait_Ack();
    IIC_Send_Byte(WriteAddr % 256); // 发送低地址
    IIC_Wait_Ack();
    IIC_Send_Byte(DataToWrite); // 发送字节
    IIC_Wait_Ack();
    IIC_Stop(); // 产生一个停止条件
    delay_ms(15);
}

void MODIFY_EEP_W(unsigned int WriteAddr, unsigned char *a, unsigned char Len, unsigned char SelectAddr)
{
    unsigned char t;
    for (t = 0; t < Len; t++)
    {
        AT24CXX_WriteOneByte(WriteAddr + t, *a, SelectAddr);
        a++;
    }
}

void EEPROM_R(unsigned int WriteAddr, unsigned char *a, unsigned char Len, unsigned char SelectAddr)
{
    u8 t;
    for (t = 0; t < Len; t++)
    {
        *a = AT24CXX_ReadOneByte(WriteAddr++, SelectAddr);
        a++;
    }
}

void EEPROM_C(unsigned int AT24C64_address, unsigned int count, unsigned char SelectAddr)
{
    while (count--)
    {
        IIC_Start();
        /*I2C_Send_Byte( 0xa0 + AT24C64_address /256 *2);*/ /* 24C16  USE */
        IIC_Send_Byte(SelectAddr);
        IIC_Wait_Ack();
        IIC_Send_Byte(AT24C64_address / 256);
        IIC_Wait_Ack();
        IIC_Send_Byte(AT24C64_address % 256);
        IIC_Wait_Ack();
        // I2C_Send_Byte( *(unsigned char*)mcu_address );
        IIC_Send_Byte(0xFF);
        IIC_Wait_Ack();
        IIC_Stop();
        delay_ms(2); /* waiting for write cycle to be completed */
        AT24C64_address++;
    }
}
