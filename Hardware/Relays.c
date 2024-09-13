#include "Relays.h"
 
void Relay_init(void)//对继电器初始化
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(Relay_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Pin = Relay_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Relay_PORT, &GPIO_InitStructure);
	
}          
 
void Relay_on(void)
{
	GPIO_SetBits(Relay_PORT,Relay_PIN);
}
 
void Relay_off(void)
{ 
	GPIO_ResetBits(Relay_PORT,Relay_PIN);
}
