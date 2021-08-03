#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "Electroporation.h"
#include "stm32f4xx_gpio.h"


					   /*  Default values  */
SET_PARAM Set_Parameters = {250, 10, 50};									// or {.Period_length = 250, .Pulse_rate = 10, .Duty_cycle = 50}
GPIO_InitTypeDef GPIO_InitStruct;

uint16_t count = 0;															// to switch between parameters (Period, Pulse and Duty cycle)
uint32_t High_DutyCycle;
uint32_t Low_DutyCycle;

void GPIO_Config(void)														// GPIO_Config(); add to main() function
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

//  PINS FOR OUTPUT MOSFETS
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);


//  PINS FOR CONTROL INPUT BUTTONS
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void Set_Param(void)
{
	if(GPIO_ReadInputDataBit(GPIOA, BUTTON_MODE))
	{
		e_delay(150);
		count++;
		while(GPIO_ReadInputDataBit(GPIOA, BUTTON_MODE));
	}

	switch(count)
	{
		case 1:		// Set Period
			if(GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) && (Set_Parameters.Period_length < 5000))
			{
				Set_Parameters.Period_length += 50;
				while(GPIO_ReadInputDataBit(GPIOA, BUTTON_UP));
				e_delay(250);
			}

			if(GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN) && (Set_Parameters.Period_length != 0))
			{
				Set_Parameters.Period_length -= 50;
				while(GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN));
				e_delay(250);
			}
			break;

		case 2:		// Set Pulse rate
			if(GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) && (Set_Parameters.Pulse_rate < 100))
			{
				Set_Parameters.Pulse_rate += 10;
				while(GPIO_ReadInputDataBit(GPIOA, BUTTON_UP));
				e_delay(250);
			}

			if(GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN) && (Set_Parameters.Pulse_rate != 0))
			{
				Set_Parameters.Pulse_rate -= 10;
				while(GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN));
				e_delay(250);
			}
			break;

		case 3:		// Set Duty cycle
			if(GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) && (Set_Parameters.Duty_cycle < 100))
			{
				Set_Parameters.Duty_cycle += 10;
				while(GPIO_ReadInputDataBit(GPIOA, BUTTON_UP));
				e_delay(250);
			}

			if(GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN) && (Set_Parameters.Duty_cycle != 0))
			{
				Set_Parameters.Duty_cycle -= 10;
				while(GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN));
				e_delay(250);
			}

			break;

		default:
			count = 1;
			break;
	}
/*		This  formula gives us setting duty cycle rate     */
	High_DutyCycle = (Set_Parameters.Duty_cycle*Set_Parameters.Period_length)/100;
	Low_DutyCycle = Set_Parameters.Period_length - High_DutyCycle;
}


void Volt_800V()
{
	for(int i = 0 ; i < Set_Parameters.Pulse_rate ; i++)
	{
		GPIO_SetBits(GPIOD, OUTPUT_800V);
		e_delay(High_DutyCycle);
		GPIO_ResetBits(GPIOD, OUTPUT_800V);
		e_delay(Low_DutyCycle);
	}
}


void Volt_1200V()
{
	for(int i = 0 ; i < Set_Parameters.Pulse_rate ; i++)
	{
		GPIO_SetBits(GPIOD, OUTPUT_1200V);
		e_delay(High_DutyCycle);
		GPIO_ResetBits(GPIOD, OUTPUT_1200V);
		e_delay(Low_DutyCycle);
	}
}


void Volt_1500V()
{
	for(int i = 0 ; i < Set_Parameters.Pulse_rate ; i++)
	{
		GPIO_SetBits(GPIOD, OUTPUT_1500V);
		e_delay(High_DutyCycle);
		GPIO_ResetBits(GPIOD, OUTPUT_1500V);
		e_delay(Low_DutyCycle);
	}
}


void Discharge_Cap(void)
{
	GPIO_SetBits(GPIOD, OUTPUT_DISCHARGE);
	e_delay(3000);														// in the future i will update this func when develop hardware design
	GPIO_ResetBits(GPIOD, OUTPUT_DISCHARGE);							// i will create func for detect to measure the current level in capacitors
}

void e_delay(uint32_t time)
{
	time = time*21000;													// this formula gives us 1 second equals 1000 milliseconds
	while(time--);
}



