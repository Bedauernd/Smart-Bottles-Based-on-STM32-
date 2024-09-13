#include "stm32f10x.h"

#define Relay_CLK		RCC_APB2Periph_GPIOB
#define Relay_PIN		GPIO_Pin_11                  
#define Relay_PORT		GPIOB 

void Relay_init(void);
 
void Relay_on(void);
 
void Relay_off(void);

