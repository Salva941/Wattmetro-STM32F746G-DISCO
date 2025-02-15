/*
 * trigger.h
 *

 */
#ifndef INC_TRIGGER_H_
#define INC_TRIGGER_H_

#include "math.h"
#include <stdint.h>


#define HYSTERESY 10

extern int16_t CrossNegative (int16_t *pSamples, uint16_t len, uint16_t soglia);
extern int16_t CrossPositive (int16_t *pSamples, uint16_t len, uint16_t soglia);
extern int16_t Cross (int16_t *pSamples, uint16_t len, uint16_t soglia, int slope);

extern int16_t ReverseCrossNegative (int16_t *pSamples, uint16_t len, uint16_t soglia);
extern int16_t ReverseCrossPositive (int16_t *pSamples, uint16_t len, uint16_t soglia);
extern int16_t ReverseCross (int16_t *pSamples, uint16_t len, uint16_t soglia, int slope);

#endif /* INC_TRIGGER_H_ */
