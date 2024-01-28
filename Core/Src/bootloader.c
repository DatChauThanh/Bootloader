/*
 * Bootloader Basic
 *
 * Author : Chau Thanh Dat
 * 31.12.2023
 */
#include "bootloader.h"

//=====================INIT Bootloader======================//
AppSelection App;

void bootloaderInit()
{
	if(HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_RESET)
	{
		App = App1;
	}
	else
	{
		App = App2;
	}

	if(App == App1)
	{
		MFPEC_voidErasePage(48);
		MFPEC_u8ProgramOneWordFlash(0x0800C000,0x12345678);
		uint8_t readataEmpty_Counter = 0;
		for(uint8_t i = 0; i < 10 ;i++)
		{
			if(readData(APP1_ADDRESS_START + (i*4)) == -1)
			{
				readataEmpty_Counter ++ ;
			}
		}
		if(readataEmpty_Counter != 10)
		{
			DeInit();
			JumpToApplicationApp(APP1_ADDRESS_START);
		}
		else	errorBlink();
	}
	else if (App == App2)
	{
		MFPEC_voidErasePage(48);
		MFPEC_u8ProgramOneWordFlash(0x0800C000,0x87654321);
		uint8_t readataEmpty_Counter = 0;
		for(uint8_t i = 0; i < 10 ;i++)
		{
			if(readData(APP2_ADDRESS_START + (i*4)) == -1)
			{
				readataEmpty_Counter ++ ;
			}
		}
		if(readataEmpty_Counter != 10)
		{
			DeInit();
			JumpToApplicationApp(APP2_ADDRESS_START);
		}
		else	errorBlink();
	}
	else	errorBlink();
}
//===================Sub-Func Bootloader====================//
void DeInit()
{
	//-- reset peripherals to guarantee flawless start of user application
	HAL_GPIO_DeInit(LED_GPIO_Port, LED_Pin);
	  __HAL_RCC_GPIOC_CLK_DISABLE();
	  __HAL_RCC_GPIOD_CLK_DISABLE();
	  __HAL_RCC_GPIOB_CLK_DISABLE();
	  __HAL_RCC_GPIOA_CLK_DISABLE();
	HAL_RCC_DeInit();
	HAL_DeInit();
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;
}

void JumpToApplicationApp(const uint32_t address)
{
	const JumpStruct* vector_p = (JumpStruct*)address;

	DeInit();
	/* let's do The Jump! */
	/* Jump, used asm to avoid stack optimization */
	asm("msr msp, %0; bx %1;" : : "r"(vector_p->stack_addr), "r"(vector_p->func_p));
}

void errorBlink()
{
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	while(1)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(500);

		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(800);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(800);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(800);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(500);

		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(3000);
	}
}

uint32_t readData(uint32_t address)
{
	uint32_t read_data;
	read_data = *(uint32_t*)(address);
	return read_data;
}
