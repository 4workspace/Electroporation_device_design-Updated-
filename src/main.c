#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "Electroporation.h"


int main(void)
{
	GPIO_Config();

	while(1)
	{

		Set_Param();												// Setting Period_length, Pulse_rate and Duty_cycle

	  if(GPIO_ReadInputDataBit(GPIOA, BUTTON_800V))					// if pressed button for 800V apply
	  {
		  while(GPIO_ReadInputDataBit(GPIOA, BUTTON_800V));
		  e_delay(250);
		  Volt_800V();
	  }

	  else if(GPIO_ReadInputDataBit(GPIOA, BUTTON_1200V))			// if pressed button for 1200V apply
	  {
		  while(GPIO_ReadInputDataBit(GPIOA, BUTTON_1200V));
		  e_delay(250);
		  Volt_1200V();
	  }

	  else if(GPIO_ReadInputDataBit(GPIOA, BUTTON_1500V))			// if pressed button for 1500V apply
	  {
		  while(GPIO_ReadInputDataBit(GPIOA, BUTTON_1500V));
		  e_delay(250);
		  Volt_1500V();
	  }

	  else if(GPIO_ReadInputDataBit(GPIOA, BUTTON_DISCHARGE))		// if pressed button for discharge capacitors
	  {
		  while(GPIO_ReadInputDataBit(GPIOA, BUTTON_DISCHARGE));
		  e_delay(250);
		  Discharge_Cap();
	  }
  }

}





/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
