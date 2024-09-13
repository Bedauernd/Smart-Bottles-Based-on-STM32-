#include "stm32f10x.h" 
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

#include "Delay.h"
#include "OLED.h"
#include "DS18B20.h"
#include "Relays.h"
#include "Water_AD.h"
#include "Serial.h"


float Water_T = 0, Water_Q = 0, Water_L = 0;
int Hope_T = 30;


void Get_Water_T()
{
	Water_T = DS18B20_Get_Temp();
}

void Get_Water_Q()
{
	Water_Q = (float)Get_Adc_Average(1,50)/4096*1000;
}

void Get_Water_L()
{
	Water_L = (float)Get_Adc_Average(0,50)/4096*40;
}

void Change_Relays()
{
	if(Water_T - Hope_T >= 0)
	{
		Relay_on();
	}
	else
	{
		Relay_off();
	}
}

int Is_All_Digit(char* str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
		if (str[i] <= '0' && str[i] >= '9')
        {
            return 0;
        }
    }
    return 1;
}

void Serial_Check()
{
	if (Serial_RxFlag == 1)		//如果接收到数据包
		{
			/*将收到的数据包与预设的指令对比，以此决定将要执行的操作*/
			if (strcmp(Serial_RxPacket, "Messige") == 0)			//如果收到Messige指令
			{
				Serial_Printf("水温: %.2f\r\n",Water_T);
				Serial_Printf("水质: %.2f\r\n",Water_Q);
				Serial_Printf("水量: %.2f\r\n",Water_L);
				Serial_Printf("期望水温: %d\r\n",Hope_T);
				Serial_SendString("发送完成\r\n");//串口回传一个字符串
			}
			else if(Is_All_Digit(Serial_RxPacket))
			{
				Hope_T = atol(Serial_RxPacket);
				Serial_Printf("期望温度： %d\r\n",Hope_T);
			}
			else//上述所有条件均不满足，即收到了未知指令
			{
				Serial_SendString("指令错误\r\n"); //串口回传一个字符串
			}
			Serial_RxFlag = 0; //处理完成后，需要将接收数据包标志位清零，否则将无法接收后续数据包
		}
}


int main(void)
{
	/*初始化*/
	OLED_Init();
	Relay_init();
	AD_Init();
	Serial_Init();
	
	/*显示屏调整*/
	OLED_ShowChinese(32,0,"智能水杯");
	OLED_ShowChinese(0,16,"水温：");
	OLED_ShowChinese(100,16,"℃");
	OLED_ShowChinese(0,32,"水质：");
	OLED_ShowString(100,32,"PMM",OLED_8X16);
	OLED_ShowChinese(0,48,"水量：");
	OLED_ShowString(100,48,"MM",OLED_8X16);
	
	while (1)
	{
		Get_Water_T();
		OLED_ShowFloatNum(40,16,Water_T,2,2,OLED_8X16,0);
		OLED_ClearArea(40,16,2,2);
		
		Get_Water_Q();
		OLED_ShowFloatNum(40,32,Water_Q,3,2,OLED_8X16,0);
		OLED_ClearArea(40,32,3,2);
		
		Get_Water_L();
		OLED_ShowFloatNum(40,48,Water_L,2,2,OLED_8X16,0);
		OLED_ClearArea(40,48,2,2);
		
		OLED_Update();
		
		Change_Relays();//控制继电器
		Serial_Check();
	}
	
}

