/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdio.h>

#include "GUI.h"
#include "WM.h"
#include "IMAGE.h"
#include "DIALOG.h"
#include "BUTTON.h"
#include "emWinWrapper.h"
#include "mtouch.h"
#include "string.h"


/* Private typedef -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define ID_WINDOW_0 	(GUI_ID_USER + 0x00)
#define ID_WINDOW_1 	(GUI_ID_USER + 0x01)
#define ID_GRAPH_0 		(GUI_ID_USER + 0x02)


// DEFINE PER STAMPARE VISUALIZZARE MISURE SUL DISPLAY
#define ID_TEXT_0 		(GUI_ID_USER + 0x10)
#define ID_TEXT_1 		(GUI_ID_USER + 0x20)
#define ID_TEXT_2 		(GUI_ID_USER + 0x30)
#define ID_TEXT_3 		(GUI_ID_USER + 0x40)
#define ID_TEXT_4 		(GUI_ID_USER + 0x50)


// DICHIARAZIONI PER VISUALIZZARE IL SEGNALE SUL DISPLAY E LE MISURE
static GRAPH_DATA_Handle hData1;		//Object CH1
static GRAPH_DATA_Handle hData2;		//Object CH2
static int gesture_occurred = 0;


typedef struct {
	float value1;

}misure_t;

static WM_HWIN hDialog;
static WM_HWIN hGraph;
static WM_HWIN hTxtXAxis;
static WM_HWIN hTxtMeasurements;	//testo libero che l'utente puo' sovrappore in alto a destra
static WM_HWIN htxtMeas[N_TXT]; 		//Vrms, Irms, P, Q, S
static WM_HWIN hTxtTitle;

static GRAPH_SCALE_Handle hYScale;
static GRAPH_SCALE_Handle hXScale;


MTOUCH_GestureData_s gestureData;

static const char _yaxisText[] = "Grandezza [unita' di misura]";
static const char *yaxisText = _yaxisText;

static void (*GUI_cbGesture)(Gesture_t *gesture) = NULL; // deve essere usata solo dalla libreria (dich var globale che deve contenere l'ind della funz)

static const GUI_WIDGET_CREATE_INFO _aDialogTxt1[] =
{		//							Nome					id				X					Y						lunghezza					altezza
		{ WINDOW_CreateIndirect, 	"Window", 				ID_WINDOW_0, 	0, 					0, 					   SCREEN_X, 		        SCREEN_Y, 	(WM_CF_GESTURE | WM_CF_ZOOM), 			0x0, 	0 },
		{ TEXT_CreateIndirect, 		"Watt Meter", 			ID_TEXT_0, 		SCREEN_X/3-20,	   20,		                    200,				SCREEN_Y/5,							50,				0x0,	0 },
		{ TEXT_CreateIndirect, 		"Value= ", 		  	  	ID_TEXT_1, 		10,		           90+0*(SCREEN_Y-90)/3,   SCREEN_X,				SCREEN_Y/5,							50,				0x0,	0 },
		{ TEXT_CreateIndirect, 		"Value= ", 		  	  	ID_TEXT_2, 		10,		           90+1*(SCREEN_Y-90)/3,   SCREEN_X,				SCREEN_Y/5,							50,				0x0,	0 },
		{ TEXT_CreateIndirect, 		"Value= ", 		  	  	ID_TEXT_3, 		10,			       90+2*(SCREEN_Y-90)/3,   SCREEN_X,				SCREEN_Y/5,							50,				0x0,	0 },
/*		//							Nome					id				X					Y						lunghezza					altezza
		{ WINDOW_CreateIndirect, 	"Window2", 				ID_WINDOW_1, 	0, 					0, 					   SCREEN_X, 		        SCREEN_Y, 	(WM_CF_GESTURE | WM_CF_HIDE | WM_CF_ZOOM), 	0x0, 	0 },
		{ TEXT_CreateIndirect, 		"Watt Meter2", 		  	ID_TEXT_4, 		10,		           90,		              	    250,				SCREEN_Y/5,							50,				0x0,	0 },
		{ TEXT_CreateIndirect, 		"Value= ", 		  	  	ID_TEXT_5, 		10,		           90+(SCREEN_Y-90)/3,		    250,				SCREEN_Y/5,							50,				0x0,	0 },
		{ TEXT_CreateIndirect, 		"Value= ", 		  	  	ID_TEXT_6, 		50+180,		       90+0*(SCREEN_Y-90)/3,		250,				SCREEN_Y/5,							50,				0x0,	0 },
		{ TEXT_CreateIndirect, 		"Value= ", 		  	  	ID_TEXT_7, 		50+180,		       90+1*(SCREEN_Y-90)/3,		250,				SCREEN_Y/5,							50,				0x0,	0 }
*/
};

static const GUI_WIDGET_CREATE_INFO _aDialog[] =
{		//							Nome					id				X					Y					lunghezza					altezza
		{ WINDOW_CreateIndirect, 	"Window", 				ID_WINDOW_0, 	0, 					0, 					SCREEN_X, 					SCREEN_Y, 	(uint16_t)(WM_CF_GESTURE | WM_CF_ZOOM), 0x0, 0 },

		{ GRAPH_CreateIndirect, 	"Graph", 				ID_GRAPH_0, 	DIFF_GRA2SCREEN/2,	DIFF_GRA2SCREEN/2,	GRAPH_SIZE_X+BORDER_SIZE_LEFT, GRAPH_SIZE_Y+BORDER_SIZE_BOTOM, 	(uint16_t)(WM_CF_GESTURE | WM_CF_ZOOM), 0x0, 0 },
		{ TEXT_CreateIndirect, 	"grandezza [unita' di misura] ", ID_TEXT_4, BORDER_SIZE_LEFT,	BOTOM_BORDER_POS+8,			GRAPH_SIZE_X, 	20, 			TEXT_CF_HCENTER,	0x0,	0 },
		{ TEXT_CreateIndirect, 		"Value= ", 		  	  	ID_TEXT_0, 		SCREEN_X-100,		10,		100,		20,							0,				0x0,	0 },

};



/*********************************************************************
 *       _UserDraw
 *
 * Purpose:
 *   This routine is called by the GRAPH object before anything is drawn
 *   and after the last drawing operation.
 */
static void _UserDraw(WM_HWIN hWin, int Stage) {

	if (Stage != GRAPH_DRAW_LAST) {
		return;
	}

	GUI_RECT Rect, RectInvalid;
	int FontSizeY;
	GUI_SetFont(&GUI_Font13_ASCII);
	FontSizeY = GUI_GetFontSizeY();
	WM_GetInsideRect(&Rect);
	WM_GetInvalidRect(hWin, &RectInvalid);
	Rect.x1 = Rect.x0 + FontSizeY;
	GUI_SetColor(GUI_DARKBLUE);
	GUI_DispStringInRectEx(yaxisText, &Rect, GUI_TA_HCENTER, strlen(yaxisText), GUI_ROTATE_CCW);

	if (gestureData.gesture != NONE) {

		GUI_SetColor(GUI_BLACK);
		GUI_SetPenSize(1);

		if ((gestureData.x_0 < BORDER_SIZE_LEFT) || (gestureData.y_0 > GRAPH_SIZE_Y)){
			GUI_DrawLine(0, 0, 0, 0);
		} else {
			GUI_DrawLine(gestureData.x_0, 0, gestureData.x_0, GRAPH_SIZE_Y);
			GUI_DrawLine(BORDER_SIZE_LEFT, gestureData.y_0, GRAPH_SIZE_X + BORDER_SIZE_LEFT, gestureData.y_0);
		}
	}
}




/**
 * @brief  Callback routine of the font dialog
 * @param  pMsg: pointer to data structure of type WM_MESSAGE
 * @retval None  */
static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int     NCode;
	int     Id;

	// USER START (Optionally insert additional variables)
	// USER END
	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:

		// Initialization of 'Window'
		hItem = pMsg->hWin;
		WINDOW_SetBkColor(hItem, GUI_WHITE);

		hTxtXAxis = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
		TEXT_SetTextColor(hTxtXAxis, GUI_DARKBLUE);
		// TEXT_SetRotation(hItemTxt, GUI_ROTATE_CCW);

#if TXT_UI
		// COMANDI DOVE VISUALIZZIAMO LE MISURE
	    hTxtTitle = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
	    TEXT_SetTextColor(hTxtTitle, GUI_BLACK);
	    TEXT_SetFont(hTxtTitle, &GUI_Font32B_1);

		htxtMeas[TXT_1RAW] = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		TEXT_SetTextColor(htxtMeas[TXT_1RAW], GUI_BLUE);
		TEXT_SetFont(htxtMeas[TXT_1RAW], &GUI_Font32B_1);
		TEXT_SetTextAlign(htxtMeas[TXT_1RAW], TEXT_CF_LEFT);

		htxtMeas[TXT_2RAW] = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
	    TEXT_SetTextColor(htxtMeas[TXT_2RAW], GUI_BLUE);
		TEXT_SetFont(htxtMeas[TXT_2RAW], &GUI_Font32B_1);
		TEXT_SetTextAlign(htxtMeas[TXT_2RAW], TEXT_CF_LEFT);

		htxtMeas[TXT_3RAW] = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
	    TEXT_SetTextColor(htxtMeas[TXT_3RAW], GUI_BLUE);
	    TEXT_SetFont(htxtMeas[TXT_3RAW], &GUI_Font32B_1);
	    TEXT_SetTextAlign(htxtMeas[TXT_3RAW], TEXT_CF_LEFT);
#else
	    // COMANDI DOVE VISUALIZZIAMO LE MISURE
   		hTxtMeasurements = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
   		TEXT_SetTextColor(hTxtMeasurements, GUI_BLUE);

		//COMANDI GRIGLIA
		hGraph = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
		GRAPH_SetBorder(hGraph, BORDER_SIZE_LEFT, 0, 0, BORDER_SIZE_BOTOM);


		GRAPH_SetGridDistY(hGraph, (GRAPH_SIZE_Y/DIV_Y));									//Distanza divisori verticali
		GRAPH_SetGridDistX(hGraph, (GRAPH_SIZE_X/DIV_X));									//Distanza divisori orizzontali
		GRAPH_SetLineStyleV(hGraph, 2);         																	//Griglia verticale tratteggiata
		GRAPH_SetLineStyleH(hGraph, 2);          																	//Griglia orizzontale tratteggiata
		GRAPH_SetColor(hGraph, GUI_WHITE, GRAPH_CI_BK);																//Colore del graph
		GRAPH_SetColor(hGraph, GUI_LIGHTGRAY, GRAPH_CI_GRID);														//Colore griglia
		GRAPH_SetGridVis(hGraph, 1);

		GRAPH_SetUserDraw(hGraph, _UserDraw);

		hYScale = GRAPH_SCALE_Create(BORDER_SIZE_LEFT, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, GRAPH_SIZE_Y/DIV_Y);
		GRAPH_SCALE_SetTextColor(hYScale, GUI_DARKBLUE);
		GRAPH_AttachScale(hGraph, hYScale);
		GRAPH_SCALE_SetNumDecs(hYScale, 3);

		hXScale = GRAPH_SCALE_Create(BOTOM_BORDER_POS+8, GUI_TA_BOTTOM, GRAPH_SCALE_CF_HORIZONTAL, GRAPH_SIZE_X/DIV_X);
		GRAPH_SCALE_SetTextColor(hXScale, GUI_DARKBLUE);
		GRAPH_AttachScale(hGraph, hXScale);
#endif

		break;
	case WM_TOUCH:     	 	/* Touch screen message */
	case WM_TOUCH_CHILD:    /* Touch screen message to ancestors */
	case WM_KEY:            /* Key has been pressed */
	{
		if (!gesture_occurred) {
			//MTOUCH_GestureData_s gestureData;
			MTOUCH_GetGesture(&gestureData);

			GUI_cbGesture((Gesture_t *)&gestureData); // Per inviare gesture all'utente
			gesture_occurred++;
		}
	}
	break;
	case WM_NOTIFY_PARENT:
		Id    = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch(Id) {
		//gestione dei tasti qui
		((void)NCode);
		}
		break;
		default:
			gesture_occurred = 0;
			WM_DefaultProc(pMsg);
			break;
	}
}

void DIALOG_init(void (*cbGesture)(Gesture_t *gesture)) {
	WM_MULTIBUF_Enable(1);
#if TXT_UI
	hDialog = GUI_CreateDialogBox(_aDialogTxt1, GUI_COUNTOF(_aDialogTxt1), _cbDialog, WM_GetDesktopWindowEx(0), 0, 0);
#else
	hDialog = GUI_CreateDialogBox(_aDialog, GUI_COUNTOF(_aDialog), _cbDialog, WM_GetDesktopWindowEx(0), 0, 0);

	hData1 = GRAPH_DATA_YT_Create(GUI_BLUE, GRAPH_SIZE_X, NULL, GRAPH_SIZE_X);
	GRAPH_AttachData (hGraph, hData1);

	hData2 = GRAPH_DATA_YT_Create(GUI_RED, GRAPH_SIZE_X, NULL, GRAPH_SIZE_X);
	GRAPH_AttachData (hGraph, hData2);
#endif
	while (cbGesture == NULL) {
		// IMPLEMENTARE LA FUNZIONE DI GESTIONE DELLE GESTURE
	}
	GUI_cbGesture = cbGesture;

	//WM_SetFocus(hWin1);
}


void GUI_poll(void) {
	GUI_Exec();
	WM_PaintWindowAndDescs(hDialog);
}


int max_value(uint16_t *pSamples, int size) {
	// Initialize maximum element
	int max = *pSamples;
	pSamples++;

	while (--size) {
		if (*pSamples > max) {
			max = *pSamples;
		}
		pSamples++;
	}
	return max;
}

void GUI_DrawChart(uint16_t *pData, int size, int channel, int fullscale) {
	GRAPH_DATA_Handle hData = 0;

	if (channel == 1) {
		hData = hData1;
	} else {
		hData = hData2;
	}

	if (size > GRAPH_SIZE_X) {
		size = GRAPH_SIZE_X;
	}

	int value = 0;

	for (int i = 0; i < size; i++) {
		value = (((int32_t)pData[i]*(GRAPH_SIZE_Y - 2))/fullscale);
		GRAPH_DATA_YT_AddValue(hData, value);
	}
}

int GUI_DrawChartAutoscale(uint16_t *pData, int size, int channel) {
	GRAPH_DATA_Handle hData = 0;

	if (channel == 1) {
		hData = hData1;
	} else {
		hData = hData2;
	}

	if (size > GRAPH_SIZE_X) {
		size = GRAPH_SIZE_X;
	}

	int value = 0;
	int max = max_value(pData, GRAPH_SIZE_X);
	if (max == 0) max = 1;

	for (int i = 0; i < size; i++) {
		value = (((int32_t)pData[i]*(GRAPH_SIZE_Y - 2))/max);
		GRAPH_DATA_YT_AddValue(hData, value);
	}

	GRAPH_SCALE_SetFactor(hYScale, 1.0*max/(GRAPH_SIZE_Y*1000.0));
	return max;
}

void GUI_setOrizzontalScale(float scale, int numDecDigit, int offset) {
	GRAPH_SCALE_SetNumDecs(hXScale, numDecDigit);
	GRAPH_SCALE_SetFactor(hXScale, scale);
	GRAPH_SCALE_SetOff(hXScale, -offset);
}

void GUI_setVerticalScale(float scale, int numDecDigit, int offset) {
	GRAPH_SCALE_SetNumDecs(hYScale, numDecDigit);
	GRAPH_SCALE_SetFactor(hYScale, scale);
	GRAPH_SCALE_SetOff(hYScale, -offset);
}


void GUI_setOrizzontalAxisLabel(const char *axis_label) {
	TEXT_SetText(hTxtXAxis, axis_label);
	TEXT_SetTextAlign(hTxtXAxis, TEXT_CF_HCENTER);
}

void GUI_setVerticalAxisLabel(const char *axis_label) {
	yaxisText = axis_label;
}

#if TXT_UI
void GUI_setTextValue(char *pTxt, TextId_t ind) {
	TEXT_SetText(htxtMeas[ind], pTxt);
}
#else
void GUI_setTextValue(char *pTxt) {
	TEXT_SetText(hTxtMeasurements, pTxt);
}
#endif

void bhooo(const char *txt) {
	TEXT_SetText(hTxtMeasurements, txt);
	TEXT_SetTextAlign(hTxtMeasurements, TEXT_CF_HCENTER);
}


/*************************** End of file ****************************/
