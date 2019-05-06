/*
 * clock_tjb.h
 *
 *  Created on: 19 Jun 2018
 *  Updated for Blue pill(STM32F103C8T6) on 02-04-19
 *      Author: Tushar Barot
 */

void systickInit(uint32_t frequency) {
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / frequency);
}

static volatile uint32_t ticks=0;//,temp1=0;
static volatile int16_t clk_cnt=-1,clk_temp=0;

void SysTick_Handler(void) {
	ticks++;
}

uint32_t millis(void) {
  return ticks;
}

void delay_ms(uint32_t t) {
  uint32_t start, end;
  start = millis();
  end = start + t;
  if (start < end)
  {
	  while ((millis() >= start) && (millis() < end));
  }
}

/*void delay_us(uint32_t t) {
  uint32_t start, end;
  start = micros();
  end = start + t;
  if (start < end)
  {
	  while ((micros() >= start) && (micros() < end));
  }
}*/

void clock_config()
{
	systickInit(1000);
	// APB2=AHB=72MHz & APB1=72/2=36MHz
	RCC->CFGR |= (RCC_CFGR_PPRE2_DIV2 || RCC_CFGR_PPRE1_DIV4);
}
