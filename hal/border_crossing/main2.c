#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"

void delay_ms_soft(uint32_t ms);

int main(void){

	HAL_Init();
	//FILE *logfile;
	//logfile = fopen("logfile.txt", "w");	
	//fprintf(logfile, "test");
	//fputs("test", logfile);
	//fclose(logfile);
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
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.Pin = GPIO_PIN_7;
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
	int stepper_motor1 = 1;
	//int stepper_motor2 = 0;
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww 	
	printUSART2("Starting program...");	
	while(1){
	
		printUSART2("Startam while\n");
		//delay_ms_soft(1000);
		
		//if(stepper_motor1 == 1){
		
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
			
		}
		
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)){
			//if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
			//stepper_motor1()
			int i;
			printUSART2("startam motor1\n");
			for(i = 0; i < 130; i++){
			printUSART2("s1");
					GPIOB->ODR = 0x08;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x04;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x02;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x01;	
					delay_ms_soft(10);
				}
			delay_ms_soft(10000);
			for(i = 0; i < 130; i++){
					GPIOB->ODR = 0x01;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x2;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x04;	
					delay_ms_soft(10);
					GPIOB->ODR = 0x08;	
					delay_ms_soft(10);
			}
		}
				
		
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1){
			printUSART2("Na termiinalu A ima auto\n");
		}
		else{
			printUSART2("Na termiinalu A nema auto\n");
		}
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1){
			printUSART2("Na termiinalu B ima auto\n");
		}
		else{
			printUSART2("Na termiinalu B nema auto\n");
		}
		delay_ms_soft(1000);
	}
}


void delay_ms_soft(uint32_t ms)
{
	volatile uint32_t k = 10500 * ms;
	while(k--);
}
