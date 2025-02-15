/*
 * emWinWrapper.h
 *
 *  Created on: Sep 22, 2020
 *      Author: giovanni
 */

#ifndef EMWINWRAPPER_H_
#define EMWINWRAPPER_H_

#define TXT_UI	1	//commenta se vuoi l'interfaccia con grafico

#define SCREEN_X			471L				//X dello schermo
#define SCREEN_Y			272L				//Y dello schermo

//TODO: spostare questo dove stanno le size dei widget

#define BORDER_SIZE_LEFT	47			//Bordo sinistro
#define BORDER_SIZE_BOTOM 	24			//Bordo inferiore del graph


#define DIFF_GRA2SCREEN		0
#define GRAPH_SIZE_X		(SCREEN_X-DIFF_GRA2SCREEN-BORDER_SIZE_LEFT)
#define GRAPH_SIZE_Y		(SCREEN_Y-DIFF_GRA2SCREEN-BORDER_SIZE_BOTOM)
#define BOTOM_BORDER_POS	GRAPH_SIZE_Y+(DIFF_GRA2SCREEN)


#define DIV_X	10
#define DIV_Y	8

typedef enum {
	GEST_NONE = 0,
	GEST_TOUCH =1,
	GEST_MOVE_UP = 2,
	GEST_MOVE_DOWN = 3,
	GEST_MOVE_LEFT = 4,
	GEST_MOVE_RIGHT = 5,
	GEST_SPREAD_X = 6,
	GEST_PINCH_X = 7,
	GEST_SPREAD_Y = 8,
	GEST_PINCH_Y = 9,
} GestureId_t;

typedef struct {
	GestureId_t id;
	uint16_t x;
	uint16_t y;
} Gesture_t;

typedef enum {
	TXT_1RAW,
	TXT_2RAW,
	TXT_3RAW,
	N_TXT
} TextId_t;


extern void GUI_initialize(void (*cbGesture)(Gesture_t *gesture));  // all aui init passare come parametro puntatore a funz (come per la cb)
extern void GUI_poll(void);

extern void GUI_IncTick(void);
//funzione di diesgno
extern void GUI_DrawChart(uint16_t *pData, int size, int channel, int fullscale);
extern int GUI_DrawChartAutoscale(uint16_t *pData, int size, int channel);
//imposta il numero di secondi (o di Hz) per ogni pixel
extern void GUI_setOrizzontalScale(float scale, int numDecDigit, int offset);
extern void GUI_setVerticallScale(float scale, int numDecDigit, int offset);

extern void GUI_setOrizzontalAxisLabel(const char *axis_label);
extern void GUI_setVerticalAxisLabel(const char *axis_label);
//void GUI_setVerticalScale(int16_t *pSamples, int scale);
#if TXT_UI
extern void GUI_setTextValue(char *pTxt, TextId_t id);
#else
extern void GUI_setTextValue(char *pTxt);
#endif



#endif /* EMWINWRAPPER_H_ */
