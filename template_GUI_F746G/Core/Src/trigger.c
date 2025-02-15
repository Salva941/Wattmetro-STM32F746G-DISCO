/*
 * trigger.c
 *

 */

#include "trigger.h"


int16_t CrossNegative (int16_t *pSamples, uint16_t len, uint16_t soglia)
{
	int k=0;
	soglia+= HYSTERESY; //soglia superiore
	while((k < len) && (pSamples[k] < soglia))   //ci accertiamo di trovarci sopra la soglia superiore
	{
		k++;
	}
	soglia-= 2*HYSTERESY; //soglia inferiore
	while((k < len) && (pSamples[k] > soglia))  //ci prendiamo l'indice nel momento in cui superioriamo la soglia inferiore
	{
		k++;
	}
	if(k >= len)
	{
		return -1;
	}
	else
	{
		return k;
	}
}


int16_t CrossPositive (int16_t *pSamples, uint16_t len, uint16_t soglia)
{
	int k=0;
	soglia-= HYSTERESY; //soglia inferiore
	while((k<len) && (pSamples[k] > soglia))   //ci accertiamo di trovarci sotto la soglia inferiore
	{
		k++;
	}
	soglia+= 2*HYSTERESY; //soglia superiore
	while( (k < len) && (pSamples[k] > soglia))  //ci prendiamo l'indice nel momento in cui superioriamo la soglia superiore
	{
		k++;
	}

	if(k > len-1)
	{
		return -1;
	}
	else
	{
		return k;
	}
}

int16_t Cross (int16_t *pSamples, uint16_t len, uint16_t soglia, int slope)
{
	if (slope==0){  //se scelgo slope=0 scelgo il fronte di discesa
		return CrossNegative(pSamples, len, soglia);
	}
	else {  //se scelgo slope!=0 scelgo il fronte di salita
		return CrossPositive(pSamples, len, soglia);

	}
}


int16_t ReverseCrossPositive(int16_t *pBuffer, uint16_t len, uint16_t soglia)
{
	int k=len-1;
	soglia += HYSTERESY;
	while((k > 0) && (pBuffer[k] < soglia) ){
		k--;
	}

	soglia -= 2*HYSTERESY;
	while((k > 0) && pBuffer[k] > soglia ){
		k--;
	}
	if(k>0)
	{
		return k;
	}
	else{
		return -1;
	}
}

int16_t ReverseCrossNegative(int16_t *pBuffer, uint16_t len, uint16_t soglia)
{
	int k=len-1;
	soglia -= HYSTERESY;
	while((k > 0) && (pBuffer[k] > soglia)){
		k--;
	}
	soglia += 2*HYSTERESY;

	while((k > 0) && (pBuffer[k] < soglia))
	{
		k--;
	}
	if(k>0)
	{
		return k;
	}
	else{
		return -1;
	}
}

int16_t ReverseCross(int16_t *pBuffer, uint16_t len, uint16_t soglia, int slope) //0: negative, !0:positive
{
	if (slope == 0){
		return ReverseCrossNegative(pBuffer, len, soglia);
	} else {
		return ReverseCrossPositive(pBuffer, len, soglia);
	}
}
