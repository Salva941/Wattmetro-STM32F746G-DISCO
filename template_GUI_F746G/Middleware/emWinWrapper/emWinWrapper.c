/*
 * ll_wfm_graph.c
 *
 *  Created on: Sep 22, 2020
 *      Author: ADF
 */
#include "stm32f7xx_hal.h"
#include "main.h"
#include "stm32f7xx_it.h"

#include "GUI.h"
#include "WM.h"
#include "IMAGE.h"
#include "DIALOG.h"
#include "BUTTON.h"
#include "emWinWrapper.h"
#include "mtouch.h"

extern void DIALOG_init(void (*cbGesture)(Gesture_t *gesture));
extern volatile GUI_TIMER_TIME OS_TimeMS;
extern LTDC_HandleTypeDef hltdc;

int GUI_Initialized = 0;
TIM_HandleTypeDef Tim3Handle;


void GUI_initialize(void (*cbGesture)(Gesture_t *gesture)) {
	uint32_t uwPrescalerValue = (uint32_t) ((SystemCoreClock /2) / 10000) - 1;

	/* Set TIMx instance */
	Tim3Handle.Instance = TIM3;

	/* Initialize TIM3 peripheral as follows:
       + Period = 500 - 1
       + Prescaler = ((SystemCoreClock/2)/10000) - 1
       + ClockDivision = 0
       + Counter direction = Up
	 */
	Tim3Handle.Init.Period = 500 - 1;
	Tim3Handle.Init.Prescaler = uwPrescalerValue;
	Tim3Handle.Init.ClockDivision = 0;
	Tim3Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	if(HAL_TIM_Base_Init(&Tim3Handle) != HAL_OK)
	{
		while(1);
	}

	/*##-2- Start the TIM Base generation in interrupt mode ####################*/
	/* Start Channel1 */
	if (HAL_TIM_Base_Start_IT(&Tim3Handle) != HAL_OK)
	{
		while(1);
	}

	/***********************************************************/

	BSP_TS_Init(480, 272);

	/* Init the STemWin GUI Library */
	BSP_SDRAM_Init(); /* Initializes the SDRAM device */
	__HAL_RCC_CRC_CLK_ENABLE(); /* Enable the CRC Module */
	//MX_GPIO_Init();
	GUI_Init();

	//  GUI_DispStringAt("Oscilloscope Starting...", 0, 0);

	/* Multi buffering enable */
	WM_MULTIBUF_Enable(1);

	GUI_MTOUCH_Enable(1);

	GUI_Initialized = 1;

	/* Activate the use of memory device feature */
	WM_SetCreateFlags(WM_CF_MEMDEV);



	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();

	WM_GESTURE_Enable(1);

	DIALOG_init(cbGesture);
}

/*****************************************************************************************************************************************/

/**
 * @brief  Provide the GUI with current state of the touch screen
 * @param  None
 * @retval None
 */
void BSP_Pointer_Update(void)
{
	static GUI_PID_STATE TS_State = {0, 0, 0, 0};
	__IO TS_StateTypeDef  ts;
	uint16_t xDiff, yDiff;

	BSP_TS_GetState((TS_StateTypeDef *)&ts);

	if((ts.touchX[0] >= LCD_GetXSize()) ||(ts.touchY[0] >= LCD_GetYSize()) )
	{
		ts.touchX[0] = 0;
		ts.touchY[0] = 0;
		ts.touchDetected =0;
	}

	xDiff = (TS_State.x > ts.touchX[0]) ? (TS_State.x - ts.touchX[0]) : (ts.touchX[0] - TS_State.x);
	yDiff = (TS_State.y > ts.touchY[0]) ? (TS_State.y - ts.touchY[0]) : (ts.touchY[0] - TS_State.y);


	if((TS_State.Pressed != ts.touchDetected ) ||
			(xDiff > 30 )||
			(yDiff > 30))
	{
		TS_State.Pressed = ts.touchDetected;
		TS_State.Layer = 0;
		if (ts.touchDetected)
		{
			TS_State.x = ts.touchX[0];
			TS_State.y = ts.touchY[0];
			GUI_TOUCH_StoreStateEx(&TS_State);
		}
		else
		{
			GUI_TOUCH_StoreStateEx(&TS_State);
			TS_State.x = 0;
			TS_State.y = 0;
		}

		MTOUCH_AddTouchData(&ts);
	}
}


/**
 * @brief  BSP_Background.
 * @param  None
 * @retval None
 */
void BSP_Background(void)
{
	/* Capture input event and updade cursor */
	if(GUI_Initialized == 1)
	{
		BSP_Pointer_Update();
	}
}





/**
 * @brief  This function handles TIM interrupt request.
 * @param  None
 * @retval None
 */
void TIM3_IRQHandler(void)
{
	//timer 3 used for touch screen
	if (__HAL_TIM_GET_FLAG((&Tim3Handle), TIM_FLAG_UPDATE) != RESET)
	{
		if (__HAL_TIM_GET_IT_SOURCE((&Tim3Handle), TIM_IT_UPDATE) != RESET)
		{
			__HAL_TIM_CLEAR_IT((&Tim3Handle), TIM_IT_UPDATE);
			BSP_Background();

		}
	}
}

/**
 * @brief  This function handles LTDC global interrupt request.
 * @param  None
 * @retval None
 */
void LTDC_IRQHandler(void)
{
	HAL_LTDC_IRQHandler(&hltdc);
}

void GUI_IncTick(void)
{
	OS_TimeMS++;
}


