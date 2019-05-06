/*
 * timer_tjb.c
 *
 *  Created on: Apr 5, 2019
 *      Author: Tushar Jayesh Barot
 */

#include "General.h"

void timer_init()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	TIM2->CR1 &= ~TIM_CR1_CEN;
	TIM2->PSC = 72-1;	// CLK(72,000,000)/PSC(7200) = 1,000,000Hz
	TIM2->ARR = F_SAMPLE;	// 4KHz

//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//
//	NVIC_Init(&NVIC_InitStructure);

	TIM2->CNT = 0;
	TIM2->EGR |= TIM_EGR_UG;	// update generate
	TIM2->DIER |= TIM_DIER_UIE;	// update interrupt enable
	DBGMCU->CR |= DBGMCU_CR_DBG_TIM2_STOP;	// halt timer in debug mode
	TIM2->CR1 |= TIM_CR1_CEN; // counter enable
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 1);
}

static volatile uint32_t tim2_overflow = 0;

void TIM2_IRQHandler()
{
	TIM2->SR &= ~TIM_SR_UIF;
	tim2_overflow++;

	if(new_flag == 0)
	{adc_start();}
	new_flag++;

//	if((tim2_overflow % 2) == 0)
//	{
//		GPIOB->ODR ^= GPIO_ODR_ODR0;	// Set GPIOB0
//	}
}
