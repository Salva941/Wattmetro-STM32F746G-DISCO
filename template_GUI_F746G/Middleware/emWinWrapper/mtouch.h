#ifndef MTOUCH_H
#define MTOUCH_H

#include <stdint.h>
#include "stm32746g_discovery_ts.h"
#define MTOUCH_GESTURE_INERTIA 2

typedef enum {
	NONE = 0,
	TOUCH = 1,
	MOVE_UP = 2,
	MOVE_DOWN = 3,
	MOVE_LEFT = 4,
	MOVE_RIGHT = 5,
	SPREAD_X = 6,
	PINCH_X = 7,
	SPREAD_Y = 8,
	PINCH_Y = 9,
} MTOUCH_GestureID;

typedef struct {
	uint8_t points;
	uint16_t x[2];
	uint16_t y[2];
} MTOUCH_TouchData_s;

typedef struct {
	MTOUCH_GestureID gesture;
	uint16_t x_0;
	uint16_t y_0;
} MTOUCH_GestureData_s;

void MTOUCH_AddTouchData(TS_StateTypeDef *TS_State);

void MTOUCH_GetGesture(MTOUCH_GestureData_s *gestureData);


extern void manage_gesturecb(MTOUCH_GestureData_s *gestureData, int *scale_factor);

#endif /* MTOUCH_H */
