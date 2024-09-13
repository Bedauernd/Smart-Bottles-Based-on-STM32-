#ifndef __AD_H
#define __AD_H

#include "stm32f10x.h" // Device header
#include "stdint.h"

#define AD_CLK			RCC_APB2Periph_GPIOA
#define Water_Level_PIN		GPIO_Pin_0
#define Water_Quality_PIN 	GPIO_Pin_1
#define AD_PORT		GPIOA 


void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);
uint16_t Get_Adc_Average(uint8_t ADC_Channel,uint8_t times);

#endif
