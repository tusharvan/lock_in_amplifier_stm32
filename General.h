/*
 * General.h
 *
 *  Created on: Apr 8, 2019
 *      Author: Tushar Jayesh Barot
 */

#ifndef GENERAL_H_
#define GENERAL_H_

#define F_SAMPLE 333

#include <stddef.h>
#include <math.h>
//#include <stdlib.h>

#include "stm32f10x.h"

#include "adc_tjb.h"
#include "timer_tjb.h"

#include <stdint.h>
#include <math.h>

extern  volatile uint16_t 	    new_sig;
extern  volatile uint16_t 	    new_ref;
extern	volatile uint32_t		new_flag;
extern	uint32_t		head;

#endif /* GENERAL_H_ */
