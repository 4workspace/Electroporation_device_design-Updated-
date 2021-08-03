#ifndef __ELECTROPORATION_H
#define __ELECTROPORATION_H

typedef struct
{
	uint16_t Period_length;													// milisecond
	uint8_t Pulse_rate;
	uint8_t Duty_cycle;

}SET_PARAM;


// FOR GPIOA PINS
#define BUTTON_MODE					GPIO_Pin_0
#define BUTTON_UP					GPIO_Pin_1
#define BUTTON_DOWN					GPIO_Pin_2
#define BUTTON_800V					GPIO_Pin_3
#define BUTTON_1200V				GPIO_Pin_4
#define BUTTON_1500V				GPIO_Pin_5
#define BUTTON_DISCHARGE			GPIO_Pin_6
#define BUTTON_CUTOFF				GPIO_Pin_7								// Using interrupt

// FOR GPIOD PINS
#define OUTPUT_800V				    GPIO_Pin_12
#define OUTPUT_1200V				GPIO_Pin_13
#define OUTPUT_1500V				GPIO_Pin_14
#define OUTPUT_DISCHARGE			GPIO_Pin_15


void GPIO_Config();
void Set_Param(void);
void Volt_800V();
void Volt_1200V();
void Volt_1500V();
void Discharge_Cap(void);
void e_delay(uint32_t);

#endif
