#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_exti.h"
#include "misc.h"

uint8_t mode = 0;

void Delay(u32 ticks)
{
	while(ticks != 0) ticks--;
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		Delay(10000);
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
		{
			mode++;
			if(mode > 1) mode = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

int main(void) //////////////////4вариант//////////////////
{
	//////////////////Светодиоды//////////////////
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	//////////////////Кнопка//////////////////
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIOA_InitStruct;
	GPIO_StructInit(&GPIOA_InitStruct);
	GPIOA_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIOA_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIOA_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIOA_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIOA_InitStruct);

	//////////////////EXTI//////////////////
	RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	//////////////////NVIC//////////////////
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

    while(1)
    {
    	if(mode == 0)
    	{
    		GPIO_SetBits(GPIOD, GPIO_Pin_12);
    		Delay(1000000);
    		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    		Delay(1000000);
    		GPIO_SetBits(GPIOD, GPIO_Pin_13);
    		Delay(1000000);
    		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    		Delay(1000000);
    		GPIO_SetBits(GPIOD, GPIO_Pin_14);
    		Delay(1000000);
    		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    		Delay(1000000);
    		GPIO_SetBits(GPIOD, GPIO_Pin_15);
    		Delay(1000000);
    		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    		Delay(1000000);
    	}
    	if(mode == 1)
    	{
    		GPIO_SetBits(GPIOD, GPIO_Pin_12);
    		Delay(1000000);
    		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    		Delay(1000000);
    		GPIO_SetBits(GPIOD, GPIO_Pin_15);
    		Delay(1000000);
    		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    		Delay(1000000);
    		GPIO_SetBits(GPIOD, GPIO_Pin_14);
    		Delay(1000000);
    		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    		Delay(1000000);
    		GPIO_SetBits(GPIOD, GPIO_Pin_13);
    		Delay(1000000);
    		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    		Delay(1000000);
    	}
    }
}
