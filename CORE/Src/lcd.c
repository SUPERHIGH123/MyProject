#include "lcd.h"
// #include "sys.h"
// #include "gpio.h"
#include "delay.h"



//void transfer_command(uint8_t data) 
//{
//    // 第一步：设置 RS = 0（命令模式）
//    RS_LOW;
//	delay_us(1);
//    // 第二步：RD 高电平
//    RD_HIGH;
//		delay_us(1);

//    // 第三步：设置 D0 ~ D7 数据线
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, (data & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, (data & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, (data & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, (data & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//WR_LOW;
//		delay_us(1);
//    // 第四步：WR 低脉冲写入
//    __NOP(); __NOP();
//    WR_HIGH;
//}

//void transfer_data(uint8_t data) 
//{
//    // 第一步：设置 RS = 1（数据模式）
//    RS_HIGH;
//	delay_us(1);
//    // 第二步：RD 高电平
//    RD_HIGH;
//		delay_us(1);

//    // 第三步：设置 D0 ~ D7 数据线
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, (data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, (data & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, (data & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, (data & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, (data & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
//    WR_LOW;
//    // 第四步：WR 低脉冲写入
//	delay_us(1);
//    __NOP(); __NOP();
//    WR_HIGH;
//}

void transfer_command(uint8_t data2) 
{
	uint8_t data1=0;
	data1 = data2;
    // 第一步：设置 RS = 0（命令模式）
    RS_LOW;

    // 第二步：RD 高电平
    RD_HIGH;
delay_us(1);
	 WR_LOW;
//		if (data2 & 0x01) data1 |= 0x80;
//    if (data2 & 0x02) data1 |= 0x40;
//    if (data2 & 0x04) data1 |= 0x20;
//    if (data2 & 0x08) data1 |= 0x10;
//    if (data2 & 0x10) data1 |= 0x08;
//    if (data2 & 0x20) data1 |= 0x04;
//    if (data2 & 0x40) data1 |= 0x02;
//    if (data2 & 0x80) data1 |= 0x01;
    // 第三步：设置 D0 ~ D7 数据线
    if (data1 & 0x01) GPIOB->BSRR = (1 << 5); else GPIOB->BSRR = (1 << (5 + 16)); // D0 -> PB5
    if (data1 & 0x02) GPIOB->BSRR = (1 << 4); else GPIOB->BSRR = (1 << (4 + 16)); // D1 -> PB4
    if (data1 & 0x04) GPIOB->BSRR = (1 << 3); else GPIOB->BSRR = (1 << (3 + 16)); // D2 -> PB3
    if (data1 & 0x08) GPIOD->BSRR = (1 << 2); else GPIOD->BSRR = (1 << (2 + 16)); // D3 -> PD2
    if (data1 & 0x10) GPIOC->BSRR = (1 << 12); else GPIOC->BSRR = (1 << (12 + 16)); // D4 -> PC12
    if (data1 & 0x20) GPIOC->BSRR = (1 << 11); else GPIOC->BSRR = (1 << (11 + 16)); // D5 -> PC11
    if (data1 & 0x40) GPIOC->BSRR = (1 << 10); else GPIOC->BSRR = (1 << (10 + 16)); // D6 -> PC10
    if (data1 & 0x80) GPIOA->BSRR = (1 << 15); else GPIOA->BSRR = (1 << (15 + 16)); // D7 -> PA15

//    if (data1 & 0x80) GPIOB->BSRR = (1 << 5); else GPIOB->BSRR = (1 << (5 + 16)); // D0 -> PB5
//    if (data1 & 0x40) GPIOB->BSRR = (1 << 4); else GPIOB->BSRR = (1 << (4 + 16)); // D1 -> PB4
//    if (data1 & 0x20) GPIOB->BSRR = (1 << 3); else GPIOB->BSRR = (1 << (3 + 16)); // D2 -> PB3
//    if (data1 & 0x10) GPIOD->BSRR = (1 << 2); else GPIOD->BSRR = (1 << (2 + 16)); // D3 -> PD2
//    if (data1 & 0x08) GPIOC->BSRR = (1 << 12); else GPIOC->BSRR = (1 << (12 + 16)); // D4 -> PC12
//    if (data1 & 0x04) GPIOC->BSRR = (1 << 11); else GPIOC->BSRR = (1 << (11 + 16)); // D5 -> PC11
//    if (data1 & 0x02) GPIOC->BSRR = (1 << 10); else GPIOC->BSRR = (1 << (10 + 16)); // D6 -> PC10
//    if (data1 & 0x01) GPIOA->BSRR = (1 << 15); else GPIOA->BSRR = (1 << (15 + 16)); // D7 -> PA15
    // 第四步：WR 低脉冲写入
   delay_us(1);
    __NOP(); __NOP();
    WR_HIGH;
}

void transfer_data(uint8_t data2) 
{
		uint8_t data1=0;
	data1 = data2;
    // 第一步：设置 RS = 1（数据模式）
    RS_HIGH;

    // 第二步：RD 高电平
    RD_HIGH;
	delay_us(1);
    WR_LOW;
//		if (data2 & 0x01) data1 |= 0x80;
//    if (data2 & 0x02) data1 |= 0x40;
//    if (data2 & 0x04) data1 |= 0x20;
//    if (data2 & 0x08) data1 |= 0x10;
//    if (data2 & 0x10) data1 |= 0x08;
//    if (data2 & 0x20) data1 |= 0x04;
//    if (data2 & 0x40) data1 |= 0x02;
//    if (data2 & 0x80) data1 |= 0x01;
    // 第三步：设置 D0 ~ D7 数据线
    if (data1 & 0x01) GPIOB->BSRR = (1 << 5); else GPIOB->BSRR = (1 << (5 + 16)); // D0 -> PB5
    if (data1 & 0x02) GPIOB->BSRR = (1 << 4); else GPIOB->BSRR = (1 << (4 + 16)); // D1 -> PB4
    if (data1 & 0x04) GPIOB->BSRR = (1 << 3); else GPIOB->BSRR = (1 << (3 + 16)); // D2 -> PB3
    if (data1 & 0x08) GPIOD->BSRR = (1 << 2); else GPIOD->BSRR = (1 << (2 + 16)); // D3 -> PD2
    if (data1 & 0x10) GPIOC->BSRR = (1 << 12); else GPIOC->BSRR = (1 << (12 + 16)); // D4 -> PC12
    if (data1 & 0x20) GPIOC->BSRR = (1 << 11); else GPIOC->BSRR = (1 << (11 + 16)); // D5 -> PC11
    if (data1 & 0x40) GPIOC->BSRR = (1 << 10); else GPIOC->BSRR = (1 << (10 + 16)); // D6 -> PC10
    if (data1 & 0x80) GPIOA->BSRR = (1 << 15); else GPIOA->BSRR = (1 << (15 + 16)); // D7 -> PA15

//    if (data1 & 0x80) GPIOB->BSRR = (1 << 5); else GPIOB->BSRR = (1 << (5 + 16)); // D0 -> PB5
//    if (data1 & 0x40) GPIOB->BSRR = (1 << 4); else GPIOB->BSRR = (1 << (4 + 16)); // D1 -> PB4
//    if (data1 & 0x20) GPIOB->BSRR = (1 << 3); else GPIOB->BSRR = (1 << (3 + 16)); // D2 -> PB3
//    if (data1 & 0x10) GPIOD->BSRR = (1 << 2); else GPIOD->BSRR = (1 << (2 + 16)); // D3 -> PD2
//    if (data1 & 0x08) GPIOC->BSRR = (1 << 12); else GPIOC->BSRR = (1 << (12 + 16)); // D4 -> PC12
//    if (data1 & 0x04) GPIOC->BSRR = (1 << 11); else GPIOC->BSRR = (1 << (11 + 16)); // D5 -> PC11
//    if (data1 & 0x02) GPIOC->BSRR = (1 << 10); else GPIOC->BSRR = (1 << (10 + 16)); // D6 -> PC10
//    if (data1 & 0x01) GPIOA->BSRR = (1 << 15); else GPIOA->BSRR = (1 << (15 + 16)); // D7 -> PA15

    // 第四步：WR 低脉冲写入
delay_us(1);
    __NOP(); __NOP();
    WR_HIGH;
}

//void transfer_command(uint8_t data1)
//{
//    uint16_t data2 = 0;
//	data2 = data1;
//	WR_HIGH;
//    RS_LOW;       // 命令模式
//    RD_HIGH;
//	

//    // 清除所有数据线
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET); // PB3, PB4, PB5
//    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);                          // PD2
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET); // PC10~12
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);                         // PA15

//    // 设置各个数据线（data2 由你根据 data1 设置）
//    if (data2 & 0x80) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET); // D7
//    if (data2 & 0x40) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET); // D6
//    if (data2 & 0x20) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET); // D5
//    if (data2 & 0x10) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET); // D4
//    if (data2 & 0x08) HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);  // D3
//    if (data2 & 0x04) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);  // D2
//    if (data2 & 0x02) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);  // D1
//    if (data2 & 0x01) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);  // D0

//    WR_LOW;
//		delay_us(1);
//    WR_HIGH;
//}
//void transfer_data(uint8_t data1)
//{
//    uint16_t data2 = 0;
//	data2 = data1;
//WR_HIGH;
//    RS_HIGH;       // 命令模式
//    RD_HIGH;

//    // 清除所有数据线
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET); // PB3, PB4, PB5
//    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);                          // PD2
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET); // PC10~12
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);                         // PA15

//    // 设置各个数据线（data2 由你根据 data1 设置）
//    if (data2 & 0x80) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET); // D7
//    if (data2 & 0x40) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET); // D6
//    if (data2 & 0x20) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET); // D5
//    if (data2 & 0x10) HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET); // D4
//    if (data2 & 0x08) HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);  // D3
//    if (data2 & 0x04) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);  // D2
//    if (data2 & 0x02) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);  // D1
//    if (data2 & 0x01) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);  // D0

//    WR_LOW;
//		delay_us(1);
//    WR_HIGH;
//}

//void transfer_command(uint8_t data1)
//{
//    uint16_t data2 = 0;

//    // 位翻转（bit反序）
////    if (data1 & 0x01) data2 |= 0x80;
////    if (data1 & 0x02) data2 |= 0x40;
////    if (data1 & 0x04) data2 |= 0x20;
////    if (data1 & 0x08) data2 |= 0x10;
////    if (data1 & 0x10) data2 |= 0x08;
////    if (data1 & 0x20) data2 |= 0x04;
////    if (data1 & 0x40) data2 |= 0x02;
////    if (data1 & 0x80) data2 |= 0x01;
//    RS_LOW;       // 命令模式
//    RD_HIGH;
//	
//    // 清引脚
//    GPIOB->ODR &= ~(0x38);       // PB5,4,3
//    GPIOD->ODR &= ~(1 << 2);     // PD2
//    GPIOC->ODR &= ~(0x1C00);     // PC12,11,10
//    GPIOA->ODR &= ~(1 << 15);    // PA15


//	//delay_us(10);

//    // 输出数据位到总线
////    if (data2 & 0x01) GPIOA->ODR |= (1 << 15); // D7
////    if (data2 & 0x02) GPIOC->ODR |= (1 << 10); // D6
////    if (data2 & 0x04) GPIOC->ODR |= (1 << 11); // D5
////    if (data2 & 0x08) GPIOC->ODR |= (1 << 12); // D4
////    if (data2 & 0x10) GPIOD->ODR |= (1 << 2);  // D3
////    if (data2 & 0x20) GPIOB->ODR |= (1 << 3);  // D2
////    if (data2 & 0x40) GPIOB->ODR |= (1 << 4);  // D1
////    if (data2 & 0x80) GPIOB->ODR |= (1 << 5);  // D0

//    if (data2 & 0x80) GPIOA->ODR |= (1 << 15); // D7
//    if (data2 & 0x40) GPIOC->ODR |= (1 << 10); // D6
//    if (data2 & 0x20) GPIOC->ODR |= (1 << 11); // D5
//    if (data2 & 0x10) GPIOC->ODR |= (1 << 12); // D4
//    if (data2 & 0x08) GPIOD->ODR |= (1 << 2);  // D3
//    if (data2 & 0x04) GPIOB->ODR |= (1 << 3);  // D2
//    if (data2 & 0x02) GPIOB->ODR |= (1 << 4);  // D1
//    if (data2 & 0x01) GPIOB->ODR |= (1 << 5);  // D0

//    WR_LOW;
//		delay_us(10);
//    WR_HIGH;
//}
//void transfer_data(unsigned char data1)
//{
//    u16 data2;
//    data2 = 0;

//	  RS_HIGH;       // 设置为数据写入模式
//    RD_HIGH;       // RD 拉高
//	
//    // 位反转
////    if (data1 & 0x01) data2 |= 0x80;
////    if (data1 & 0x02) data2 |= 0x40;
////    if (data1 & 0x04) data2 |= 0x20;
////    if (data1 & 0x08) data2 |= 0x10;
////    if (data1 & 0x10) data2 |= 0x08;
////    if (data1 & 0x20) data2 |= 0x04;
////    if (data1 & 0x40) data2 |= 0x02;
////    if (data1 & 0x80) data2 |= 0x01;

//    // 清所有相关引脚
//    GPIOB->ODR &= ~(0x38);       // 清 PB5, PB4, PB3
//    GPIOD->ODR &= ~(1 << 2);     // 清 PD2
//    GPIOC->ODR &= ~(0x1C00);     // 清 PC12, PC11, PC10
//    GPIOA->ODR &= ~(1 << 15);    // 清 PA15


////delay_us(10);

//    // 输出数据到总线
////    if (data2 & 0x01) GPIOA->ODR |= (1 << 15); // D7
////    if (data2 & 0x02) GPIOC->ODR |= (1 << 10); // D6
////    if (data2 & 0x04) GPIOC->ODR |= (1 << 11); // D5
////    if (data2 & 0x08) GPIOC->ODR |= (1 << 12); // D4
////    if (data2 & 0x10) GPIOD->ODR |= (1 << 2);  // D3
////    if (data2 & 0x20) GPIOB->ODR |= (1 << 3);  // D2
////    if (data2 & 0x40) GPIOB->ODR |= (1 << 4);  // D1
////    if (data2 & 0x80) GPIOB->ODR |= (1 << 5);  // D0

//    if (data2 & 0x80) GPIOA->ODR |= (1 << 15); // D7
//    if (data2 & 0x40) GPIOC->ODR |= (1 << 10); // D6
//    if (data2 & 0x20) GPIOC->ODR |= (1 << 11); // D5
//    if (data2 & 0x10) GPIOC->ODR |= (1 << 12); // D4
//    if (data2 & 0x08) GPIOD->ODR |= (1 << 2);  // D3
//    if (data2 & 0x04) GPIOB->ODR |= (1 << 3);  // D2
//    if (data2 & 0x02) GPIOB->ODR |= (1 << 4);  // D1
//    if (data2 & 0x01) GPIOB->ODR |= (1 << 5);  // D0

//    WR_LOW;        // 写入脉冲
//		delay_us(10);
//    WR_HIGH;
//}



//void transfer_command(u8 data1)
//{
//    u16 data2, data4, data5;
//    data2 = 0;
//    if (data1 & 0x01)
//        data2 |= 0x80;
//    if (data1 & 0x02)
//        data2 |= 0x40;
//    if (data1 & 0x04)
//        data2 |= 0x20;
//    if (data1 & 0x08)
//        data2 |= 0x10;
//    if (data1 & 0x10)
//        data2 |= 0x08;
//    if (data1 & 0x20)
//        data2 |= 0x04;
//    if (data1 & 0x40)
//        data2 |= 0x02;
//    if (data1 & 0x80)
//        data2 |= 0x01;

//    data4 = (data2 & 0x7F);
//    data5 = ((data2 & 0x80) >> 4);

//    GPIOD->ODR &= 0xFF80;
//    GPIOB->ODR &= 0xFFF7;
//    RS_LOW;

//    RD_HIGH;
//    GPIOD->ODR |= data4;
//    GPIOB->ODR |= data5;
//    WR_LOW;
//    WR_HIGH;
//}

//void transfer_data(unsigned char data1)
//{
//    u16 data2, data4, data5;
//    data2 = 0;
//    if (data1 & 0x01)
//        data2 |= 0x80;
//    if (data1 & 0x02)
//        data2 |= 0x40;
//    if (data1 & 0x04)
//        data2 |= 0x20;
//    if (data1 & 0x08)
//        data2 |= 0x10;
//    if (data1 & 0x10)
//        data2 |= 0x08;
//    if (data1 & 0x20)
//        data2 |= 0x04;
//    if (data1 & 0x40)
//        data2 |= 0x02;
//    if (data1 & 0x80)
//        data2 |= 0x01;

//    data4 = (data2 & 0x7F);
//    data5 = ((data2 & 0x80) >> 4);

//    GPIOD->ODR &= 0xFF80;
//    GPIOB->ODR &= 0xFFF7;
//    RS_HIGH; // 数据寄存器

//    RD_HIGH;
//    GPIOD->ODR |= data4;
//    GPIOB->ODR |= data5;
//    WR_LOW;
//    WR_HIGH;
//}

//void initial_lcd(void)
//{
//    RESET_HIGH;
//    delay_ms(200);
//    RESET_LOW;
//    delay_ms(500);
//    RESET_HIGH;
//    delay_ms(20);

//    transfer_command(0xA2); // Bias 1/9
//    transfer_command(0xA0); // ADC Normal
//    transfer_command(0xC8); // COM Output Reverse
//    transfer_command(0xA6); // Normal Display

//    transfer_command(0x2C); // Booster
//    delay_ms(50);
//    transfer_command(0x2E); // Regulator
//    delay_ms(50);
//    transfer_command(0x2F); // Follower
//    delay_ms(50);

//    transfer_command(0x81); // Set Contrast Mode
//    transfer_command(0x30); // Set Contrast (Try 0x1F ~ 0x30)

//    transfer_command(0xAF); // Display ON
//}



void initial_lcd()

{
	RESET_HIGH;
	delay_ms(20);
	RESET_LOW;
	delay_ms(100);
	RESET_HIGH;
	delay_ms(20);

	transfer_command(0xa2);		//1/9 Bias
	transfer_command(0xa6);		//Set Inverse display
	transfer_command(0xa0);		//ADC set (SEG)
	transfer_command(0xc8);		//COM reves

	transfer_command(0x24);		//有效值范围：0X20-0X27粗调 每升高一阶电压增加零点几伏
	transfer_command(0x81);		//Electronic Volume Mode Set
	transfer_command(0x1f);		//有效值范围：0X00-0X3F微调 每升高一阶电压增加零点零几伏
	transfer_command(0x2c);
	delay_ms(200);                      //延时200mS
	transfer_command(0x2f);		//The Power Control Set
	delay_ms(200);                     //延时200mS
	transfer_command(0xaf);		//Lcd Disply ON

}

void lcd_address(unsigned char page, unsigned char column)
{
    // cs1=0;
    column = column - 1;
    page = page - 1;
    transfer_command(0xb0 + page); // B0为起始页

    transfer_command(((column >> 4) & 0x0f) + 0x10); // 0000 1111  高4位   解析地址的函数
    transfer_command(column & 0x0f);
}

void clear_screen(void)
{

    int i, j;
    for (i = 0Xb0; i < 0Xb9; i++)
    {
        transfer_command(i);
        transfer_command(0x10);
        transfer_command(0x00);
        for (j = 0; j < 132; j++)
        {
            transfer_data(0x00);
        }
    }
}

void font1(void)
{
    int i, j;
    for (i = 0Xb0; i < 0Xb8; i++)
    {
        transfer_command(i);
        transfer_command(0x10);
        transfer_command(0x00);
        for (j = 0; j < 128; j++)
        {
            transfer_data(0XFF);
        }
    }
}
void font4(void)
{
    int i, j;
    for (i = 0Xb0; i < 0Xb1; i++)
    {
        transfer_command(i);
        transfer_command(0x10);
        transfer_command(0x00);
        for (j = 0; j < 32; j++)
        {
            transfer_data(0XFF);
            transfer_data(0X00);
            transfer_data(0X00);
            transfer_data(0XFF);
        }
    }
}
/******************************清除特定行***********************************/
void clear_define_screen(unsigned char x0, u8 x1, unsigned char y0, unsigned char y1)
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
void disp_grap(char *dp)
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        // cs1=0;
        transfer_command(0xb0 + i); // set page address,
        transfer_command(0x10);
        transfer_command(0x00);
        for (j = 0; j < 128; j++)
        {
            transfer_data(*dp);
            dp++;
        }
    }
}
