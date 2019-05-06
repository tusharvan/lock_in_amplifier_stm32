/*
 * adc_tjb.c
 *
 *  Created on: Apr 5, 2019
 *      Author: Tushar Jayesh Barot
 */

#include "General.h"

void adc_init()
{
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8; 	// 72MHz/8 = 9MHz (max. 14MHz)

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC2EN;

	// analog input PA0 & PA1
	GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0 | GPIO_CRL_CNF1 | GPIO_CRL_MODE1);

	// set sample time ==> SAMPLETIME(239.5 cycles) + CONVERSION(12.5 cycles) = 252 ADC clk cycles
	ADC1->SMPR2 |= ADC_SMPR2_SMP0;
	ADC2->SMPR2 |= ADC_SMPR2_SMP0;

	// NOTE: set length of sequence(sqr1) and channels(sqr3)
	ADC1->SQR3 &= ~(ADC_SQR3_SQ1);	// ADC1 channel 0
	ADC2->SQR3 |= ADC_SQR3_SQ1_0;	// ADC2 channel 1

	// continuous conversion | SWSTART trigger
	ADC1->CR2 |= ADC_CR2_EXTTRIG | ADC_CR2_EXTSEL;	// | ADC_CR2_CONT;
	ADC2->CR2 |= ADC_CR2_EXTTRIG | ADC_CR2_EXTSEL;	// | ADC_CR2_CONT;

	// Configure Dual mode in ADC1 only
	ADC1->CR1 |= ADC_CR1_DUALMOD_1 | ADC_CR1_DUALMOD_2;

	// ADC turned on
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC2->CR2 |= ADC_CR2_ADON;

	// ADC1 and ADC2 calibration
	ADC1->CR2 |= ADC_CR2_RSTCAL;			// Reset calibration registers
	while((ADC1->CR2 & ADC_CR2_RSTCAL) != 0)// Wait till calibration registers are cleared
	{;}
	ADC1->CR2 |= ADC_CR2_CAL;				// Enable ADC calibration
	while((ADC1->CR2 & ADC_CR2_CAL) != 0)	// Wait till calibration is complete
	{;}
	//______________________________________
	ADC2->CR2 |= ADC_CR2_RSTCAL;			// Reset calibration registers
	while((ADC2->CR2 & ADC_CR2_RSTCAL) != 0)// Wait till calibration registers are cleared
	{;}
	ADC2->CR2 |= ADC_CR2_CAL;				// Enable ADC calibration
	while((ADC2->CR2 & ADC_CR2_CAL) != 0)	// Wait till calibration is complete
	{;}
}

void adc_start(void)
{
	ADC1->CR2 |= ADC_CR2_SWSTART; // start conversion
}

uint16_t adc_read()
{
	while(!(ADC1->SR & ADC_SR_EOC))	// wait till conversion is complete
	{;}

	return (ADC1->DR);
}
