/*
 * ADC.h
 *
 */
#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdint.h>
#include "stm32f7xx_hal.h"

#define  FFT_SIZE 1024
#define  ADC_BUFFER_SIZE FFT_SIZE

extern void adc_init(void);

extern int16_t ch1[ADC_BUFFER_SIZE];
extern int16_t ch2[ADC_BUFFER_SIZE];

#endif /* INC_ADC_H_ */


