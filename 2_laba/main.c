#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "system_stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

uint8_t mode = 0;
uint8_t k = 1;

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
		{
			mode++;
			if(mode > 1) mode = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		k++;
		if(k >4) k = 1;
	}
}

int main(void)
{
    //SystemInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIOA_InitStruct;
	GPIO_StructInit(&GPIOA_InitStruct);
	GPIOA_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIOA_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIOA_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIOA_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIOA_InitStruct);

	RCC_AHB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	///////////////////////////////////
	NVIC_InitTypeDef nvic_struct;
	nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
	nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_struct.NVIC_IRQChannelSubPriority = 1;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&nvic_struct);

	TIM_TimeBaseInitTypeDef tim_struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	tim_struct.TIM_Period = 50 - 1;
	tim_struct.TIM_Prescaler = 14000 - 1;
	tim_struct.TIM_ClockDivision = 0;
	tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &tim_struct);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

    while(1)
    {
    	if(mode == 0)
    	{
    		if(k == 1)
    		{
        		GPIO_SetBits(GPIOD, GPIO_Pin_12);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    		}
    		if(k == 2)
    		{
        		GPIO_SetBits(GPIOD, GPIO_Pin_13);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    		}
    		if(k == 3)
    		{
        		GPIO_SetBits(GPIOD, GPIO_Pin_14);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    		}
    		if(k == 4)
    		{
        		GPIO_SetBits(GPIOD, GPIO_Pin_15);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    		}
    	}
    	if(mode == 1)
    	{
    		if(k == 1)
    		{
        		GPIO_SetBits(GPIOD, GPIO_Pin_12);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    		}
    		if(k == 2)
    		{
        		GPIO_SetBits(GPIOD, GPIO_Pin_15);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    		}
    		if(k == 3)
    		{
        		GPIO_SetBits(GPIOD, GPIO_Pin_14);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    		}
    		if(k == 4)
    		{
        		GPIO_SetBits(GPIOD, GPIO_Pin_13);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
        		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    		}
    	}
    }
}
