/*
 * File: LCD16x2.c
 * Driver Name: [[ LCD16x2 Display (GPIO 4-Bit Mode) ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

//#include "display16x2.h"
//#include "displayconfig.h"
#include "delay.h"

#include "display16x2.h"

const display16x2_CfgType display16x2_CfgParam =
{
	GPIOC,
	//Pinovi
	GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_9, GPIO_PIN_14, GPIO_PIN_13,
	20
};


//-----[ Alphanumeric LCD 16x2 Routines ]-----
void delay_us(uint32_t ms)
{
	volatile uint32_t k = 10500 * ms;
	while(k--);
}
void delay_ms(uint32_t ms)
{
	volatile uint32_t k = 10500 * ms;
	while(k--);
}
void LCD_4bitdata(unsigned char Data)
{
    if(Data & 1)
    	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D4_PIN, 1);
    else
    	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D4_PIN, 0);
    if(Data & 2)
    	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D5_PIN, 1);
    else
    	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D5_PIN, 0);
    if(Data & 4)
    	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D6_PIN, 1);
    else
    	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D6_PIN, 0);
    if(Data & 8)
    	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D7_PIN, 1);
    else
    	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D7_PIN, 0);
}
void LCD_command(unsigned char a_CMD)
{
    // Select Command Register
    HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.RS_PIN, 0);
    // Move The Command Data To LCD
    LCD_4bitdata(a_CMD);
    // Send The EN Clock Signal
    HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.EN_PIN, 1);
    delay_us(display16x2_CfgParam.LCD_EN_Delay);
    HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.EN_PIN, 0);
    delay_us(display16x2_CfgParam.LCD_EN_Delay);
}
void LCD_clear()
{
    LCD_command(0);
    LCD_command(1);
    delay_us(70);
}
void LCD_CursorSet(unsigned char r, unsigned char c)
{
    unsigned char Temp,Low4,High4;
    if(r == 1)
    {
      Temp  = 0x80 + c - 1; //0x80 is used to move the cursor
      High4 = Temp >> 4;
      Low4  = Temp & 0x0F;
      LCD_command(High4);
      LCD_command(Low4);
    }
    if(r == 2)
    {
      Temp  = 0xC0 + c - 1;
      High4 = Temp >> 4;
      Low4  = Temp & 0x0F;
      LCD_command(High4);
      LCD_command(Low4);
    }
    delay_ms(2);
}
void LCD_Initialization()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	// Initialize The DWT Delay Function Which Will Be Used Later On
    // IO Pin Configurations
	if(display16x2_CfgParam.LCD_GPIO == GPIOA)
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	else if(display16x2_CfgParam.LCD_GPIO == GPIOB)
	    __HAL_RCC_GPIOB_CLK_ENABLE();
	else if(display16x2_CfgParam.LCD_GPIO == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else if(display16x2_CfgParam.LCD_GPIO == GPIOD)
		__HAL_RCC_GPIOD_CLK_ENABLE();
	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D4_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D5_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D6_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.D7_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.RS_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.EN_PIN, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = display16x2_CfgParam.D4_PIN | display16x2_CfgParam.D5_PIN |
			display16x2_CfgParam.D6_PIN |display16x2_CfgParam.D7_PIN | display16x2_CfgParam.RS_PIN |
			display16x2_CfgParam.EN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(display16x2_CfgParam.LCD_GPIO, &GPIO_InitStruct);

	// The Init. Procedure As Described In The Datasheet
    HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.RS_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.EN_PIN, GPIO_PIN_RESET);
    LCD_4bitdata(0x00);
    delay_ms(150);
    LCD_command(0x03);
    delay_ms(5);
    LCD_command(0x03);
    delay_us(150);
    LCD_command(0x03);
    LCD_command(0x02);
    LCD_command(0x02);
    LCD_command(0x08);
    LCD_command(0x00);
    LCD_command(0x0C);
    LCD_command(0x00);
    LCD_command(0x06);
    LCD_command(0x00);
    LCD_command(0x01);
}
void LCD_PutCharScreen(char Data)
{
   char Low4,High4;
   Low4  = Data & 0x0F;
   High4 = Data & 0xF0;

   HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.RS_PIN, 1);

   LCD_4bitdata(High4>>4);
   HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.EN_PIN, 1);
   delay_us(display16x2_CfgParam.LCD_EN_Delay);
   HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.EN_PIN, 0);
   delay_us(display16x2_CfgParam.LCD_EN_Delay);

   LCD_4bitdata(Low4);
   HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.EN_PIN, 1);
   delay_us(display16x2_CfgParam.LCD_EN_Delay);
   HAL_GPIO_WritePin(display16x2_CfgParam.LCD_GPIO, display16x2_CfgParam.EN_PIN, 0);
   delay_us(display16x2_CfgParam.LCD_EN_Delay);
}

void LCD_sr()
{
    LCD_command(0x01);
    LCD_command(0x0C);
    delay_us(35);
}
void LCD_PutStringScreen(char *str)
{
    int i;
    for(i=0;str[i]!='\0';i++)
       LCD_PutCharScreen(str[i]);
}
void LCD_sl()
{
    LCD_command(0x01);
    LCD_command(0x08);
    delay_us(35);
}
