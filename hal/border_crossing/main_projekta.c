#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "delay.h"
#include "misc.h"
#include "pwm.h"
#include "display16x2.h"

void delay_ms_soft(uint32_t ms);

int main(void){

	HAL_Init();
	LCD_Initialization();
  	LCD_clear();
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// initialize 4 LED's on the board 
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitTypeDef GPIO_Struct;
	__HAL_RCC_GPIOD_CLK_ENABLE(); //1.
	GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	//stepper motor buttons
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_1| GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
		 
	//stepper motor 1
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull= GPIO_NOPULL;
	GPIO_InitStruct.Speed= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//stepper motor 2
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_Struct.Pin = GPIO_PIN_0|GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_Struct.Pull= GPIO_NOPULL;
	GPIO_Struct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Struct.Speed= GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_Struct);
	
	//IR senzori
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	
	initUSART2(921600);
	//int stepper_motor1 = 1;
	//int stepper_motor2 = 0;
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww 	
	printUSART2("Starting program...\n");	
	while(1){
	
		printUSART2("Startam while\n");
		//delay_ms_soft(1000);
		
		//if(stepper_motor1 == 1){
		
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
		
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
			
		}
		
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)){
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
			
		}
		
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)){
			//if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
			//stepper_motor1()
			int i;
			printUSART2("Startam motor1\nsm1:");
			for(i = 0; i < 130; i++){
			printUSART2("+");
					GPIOB->ODR = 0x01;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x02;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x04;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x08;	
					delay_ms_soft(10);
				}
			delay_ms_soft(10000);
			for(i = 0; i < 130; i++){
					GPIOB->ODR = 0x08;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x04;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x02;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x01;
					delay_ms_soft(10);
			}
		}
		
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)){
			//if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
			//stepper_motor1()
			int i;
			printUSART2("Startam motor2\nsm2:");
			for(i = 0; i < 130; i++){
			printUSART2("+");
					GPIOB->ODR = 0x01;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x02;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x04;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x08;	
					delay_ms_soft(10);
				}
			delay_ms_soft(10000);
			for(i = 0; i < 130; i++){
					GPIOB->ODR = 0x08;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x04;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x02;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x01;
					delay_ms_soft(10);
			}
		}
				
		
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1){
			printUSART2("Na termiinalu A nema auto\n");
			LCD_CursorSet(0,0);
  			delay_ms(15);
  			LCD_PutStringScreen("TERMINAL A: FREE!\0");
		}
		else{
			printUSART2("Na termiinalu A ima auto\n");
			LCD_CursorSet(0,0);
  			delay_ms(15);
  			LCD_PutStringScreen("TERMINAL A: FULL!\0");
		}
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1){
			printUSART2("Na termiinalu B nema auto\n");
			LCD_CursorSet(2,0);
  			delay_ms(15);
  			LCD_PutStringScreen("TERMINAL B: FREE!\0");
		}
		else{
			printUSART2("Na termiinalu B ima auto\n");
			LCD_CursorSet(2,0);
  			delay_ms(15);
  			LCD_PutStringScreen("TERMINAL B: FULL!\0");
		}
		delay_ms_soft(1000);
		LCD_clear();
	}
}


void delay_ms_soft(uint32_t ms)
{
	volatile uint32_t k = 10500 * ms;
	while(k--);
}
