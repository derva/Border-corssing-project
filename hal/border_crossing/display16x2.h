/*
 * File: LCD16x2.h
 * Driver Name: [[ LCD16x2 Display (GPIO 4-Bit Mode) ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Ver: 1.1
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

#ifndef display16x2_H_
#define display16x2_H_

#include "stm32f4xx_hal.h"



typedef struct
{
	GPIO_TypeDef * LCD_GPIO;
	uint16_t D4_PIN;
	uint16_t D5_PIN;
	uint16_t D6_PIN;
	uint16_t D7_PIN;
	uint16_t EN_PIN;
	uint16_t RS_PIN;
	uint16_t LCD_EN_Delay;
}display16x2_CfgType;

extern const display16x2_CfgType display16x2_CfgParam;


//-----[ Prototypes For All Functions ]-----

void LCD_Initialization();                  // Initialize The LCD For 4-Bit Interface
void LCD_clear();                 // Clear The LCD Display
void LCD_sl();                    // Shift The Entire Display To The Left
void LCD_sr();                    // Shift The Entire Display To The Right
void LCD_command(unsigned char);      // Send Command To LCD
void LCD_4bitdata(unsigned char);     // Send 4-Bit Data To LCD
void LCD_CursorSet(unsigned char, unsigned char);  // Set Cursor Position
void LCD_PutCharScreen(char);        // Write Character To LCD At Current Position
void LCD_PutStringScreen(char*);     // Write A String To LCD


#endif /* display16x2_H_ */
