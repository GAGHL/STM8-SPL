#include "stm8s.h"
#include "stm8s_it.h"

extern unsigned int overflow_count;
extern unsigned long pulse_ticks;
extern unsigned long start_time;
extern unsigned long end_time;
 
 
void TIM1_UPD_IRQHandler(void) 
{
     overflow_count++;
     TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
     TIM1_ClearFlag(TIM1_FLAG_UPDATE);
}
 
 
void TIM1_CH1_CCP_IRQHandler(void) 
{
     end_time = TIM1_GetCapture1();
     pulse_ticks = ((overflow_count << 16) - start_time + end_time);
     start_time = end_time;
     overflow_count = 0;
     TIM1_ClearITPendingBit(TIM1_IT_CC1);
     TIM1_ClearFlag(TIM1_FLAG_CC1);
}

 
extern unsigned int value;
 
extern unsigned char n;
extern unsigned char seg;
extern const unsigned char num[10];

#define SEG_A		1
#define SEG_B		2
#define SEG_C		4
#define SEG_D		8
#define SEG_E		16
#define SEG_F		32
#define SEG_G		64

#define SegNum_0	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F)
#define SegNum_1	(SEG_B|SEG_C)
#define SegNum_2	(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G)
#define SegNum_3	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G)
#define SegNum_4	(SEG_B|SEG_C|SEG_F|SEG_G)
#define SegNum_5	(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G)
#define SegNum_6	(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define SegNum_7	(SEG_A|SEG_B|SEG_C)
#define SegNum_8	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G)
#define SegNum_9	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G)

void AWU_trigger_IRQHandler(void)
{
AWU_GetFlagStatus();
}

void SegWriteByte(char Data)
{
	int i;
char Pin[] =  			   {GPIO_PIN_1,GPIO_PIN_7,GPIO_PIN_6,GPIO_PIN_5,GPIO_PIN_4,GPIO_PIN_3,GPIO_PIN_6};
GPIO_TypeDef *GPIOx[]= {GPIOD,			GPIOC,			GPIOC,		GPIOC,		GPIOC,		 GPIOC,			GPIOD};
	
	
	for( i=0;i<7;i++)
	{
		if(Data&1)
		{
			GPIOx[i]->ODR |=Pin[i];
		}
		else
		{
			GPIOx[i]->ODR &=~Pin[i];
		}
		Data>>=1;
	}
	GPIO_WriteHigh(GPIOB, GPIO_PIN_4);
}

 
void TIM4_UPD_IRQHandler(void) 
{
	/*
	static char index = 0;
	GPIOD->ODR &=~((GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5));
	switch(index++)
	{
		case 0: 
		n = (value / 1000);
		SegWriteByte(num[n]);
		GPIOD->ODR |=(GPIO_PIN_5);
		break;
		case 1: 
		n = ((value / 100) % 10);
		SegWriteByte(num[n]);
		GPIOD->ODR |=(GPIO_PIN_4);
		break;
		case 2: 
		n = ((value / 10) % 10);
		SegWriteByte(num[n]);
		GPIOD->ODR |=(GPIO_PIN_3);
		break;
		case 3:
    n = (value % 10);		
		SegWriteByte(num[n]);
		GPIOD->ODR |=(GPIO_PIN_2);
		break;
	}
	
	 if(index>3)
		index = 0;
		TIM4_ClearFlag(TIM4_FLAG_UPDATE);
		*/
}
