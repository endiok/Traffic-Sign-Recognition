#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Motor.h"
uint16_t RxData;
int8_t Speed;
int main(void)   // n-FD x-FE 80-4A
{
	OLED_Init();
	OLED_ShowString(1,1,"RxData:");
	Serial_Init();
	Motor_Init();
	OLED_ShowString(2,1,"Speed:");
	while (1)
	{
		if(Serial_GetRxFlag())
		{
			RxData=0;
			RxData=Serial_GetRxData();	
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1,8,RxData,2);
			
		}
		if(RxData==0xFD)
		{
			Speed=-50;
			OLED_ShowString(3,1,"The sign is n ");
		}
		else if(RxData==0xFE)
		{
			Speed=-100;
			OLED_ShowString(3,1,"The sign is x ");
		}
		else if(RxData==0x4A)
		{
			Speed=-80;
			OLED_ShowString(3,1,"The sign is 80");
		}
		else
		{
			Speed=0;
			OLED_ShowString(3,1,"The sign is   ");
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(2,7,Speed,3);
	}
}
