/**
 ******************************************************************************
 * @file    src/mtouch.c
 * @author  Krzysztof Chojnowski
 * @brief   Simple multi-touch gesture recognition library
 ******************************************************************************
 **/

#include "mtouch.h"

static TS_StateTypeDef touchDataPrev = {0, {0, 0, 0, 0, 0}, {0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};
static TS_StateTypeDef touchDataCurr = {0, {0, 0, 0, 0, 0}, {0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 0};
static uint16_t origin[2];

static inline void MTOUCH_CalculateDelta(uint16_t x1, uint16_t x2,
		int16_t* delta, uint16_t* deltaAbs) {
	*delta = x1 - x2;
	*deltaAbs = *delta > 0 ? *delta : *delta * -1;
}

MTOUCH_GestureID MTOUCH_DecodeGesture_1Point(void) {
	int16_t dx, dy;
	uint16_t dxAbs, dyAbs;

	MTOUCH_CalculateDelta(touchDataCurr.touchX[0], touchDataPrev.touchX[0], &dx, &dxAbs);
	MTOUCH_CalculateDelta(touchDataCurr.touchY[0], touchDataPrev.touchY[0], &dy, &dyAbs);

	if (dxAbs > dyAbs) {
		if (dxAbs < MTOUCH_GESTURE_INERTIA)
			return TOUCH;
		else if (dx > 0)
			return MOVE_RIGHT;
		else
			return MOVE_LEFT;
	} else {
		if (dyAbs < MTOUCH_GESTURE_INERTIA)
			return TOUCH;
		else if (dy > 0)
			return MOVE_DOWN;
		else
			return MOVE_UP;
	}
}

MTOUCH_GestureID MTOUCH_DecodeGesture_2Point() {
	int16_t dxPrev, dxCurr, dyPrev, dyCurr, dx, dy;
	uint16_t dxPrevAbs, dxCurrAbs, dyPrevAbs, dyCurrAbs, dxAbs, dyAbs;

	MTOUCH_CalculateDelta(touchDataPrev.touchX[1], touchDataPrev.touchX[0], &dxPrev, &dxPrevAbs);
	MTOUCH_CalculateDelta(touchDataCurr.touchX[1], touchDataCurr.touchX[0], &dxCurr, &dxCurrAbs);
	MTOUCH_CalculateDelta(touchDataPrev.touchY[1], touchDataPrev.touchY[0], &dyPrev, &dyPrevAbs);
	MTOUCH_CalculateDelta(touchDataCurr.touchY[1], touchDataCurr.touchY[0], &dyCurr, &dyCurrAbs);

	MTOUCH_CalculateDelta(dxCurrAbs, dxPrevAbs, &dx, &dxAbs);
	MTOUCH_CalculateDelta(dyCurrAbs, dyPrevAbs, &dy, &dyAbs);

	if (dxAbs > dyAbs) {
		if (dxAbs < MTOUCH_GESTURE_INERTIA)
			return TOUCH;
		else if (dx > 0)
			return SPREAD_X;
		else
			return PINCH_X;
	} else {
		if (dyAbs < MTOUCH_GESTURE_INERTIA)
			return TOUCH;
		else if (dy > 0)
			return SPREAD_Y;
		else
			return PINCH_Y;
	}
}

void MTOUCH_GetGesture(MTOUCH_GestureData_s *gestureData) {

	if (touchDataCurr.touchDetected == 0) {
		gestureData->gesture = NONE;
	} else if (touchDataCurr.touchDetected != touchDataPrev.touchDetected) {
		if (touchDataCurr.touchDetected == 1) {
			origin[0] = touchDataCurr.touchX[0];
			origin[1] = touchDataCurr.touchY[0];
		} else if (touchDataCurr.touchDetected == 2) {
			origin[0] = (touchDataCurr.touchX[0] + touchDataCurr.touchX[1]) / 2;
			origin[1] = (touchDataCurr.touchY[0] + touchDataCurr.touchY[1]) / 2;
		}
		gestureData->gesture = TOUCH;
		//MTOUCH_SetGestureOrigin(gestureData);
	} else if (touchDataCurr.touchDetected == 1) {
		gestureData->gesture = MTOUCH_DecodeGesture_1Point();
		//MTOUCH_SetGestureOrigin(gestureData);
	} else if (touchDataCurr.touchDetected == 2) {
		gestureData->gesture = MTOUCH_DecodeGesture_2Point();
		//MTOUCH_SetGestureOrigin(gestureData);
	} else {
		gestureData->gesture = NONE;
	}
	gestureData->x_0 = touchDataCurr.touchX[0];
	gestureData->y_0 = touchDataCurr.touchY[0];
}

void MTOUCH_AddTouchData(TS_StateTypeDef *TS_State) {
	touchDataPrev = touchDataCurr;
	touchDataCurr = *TS_State;
}

