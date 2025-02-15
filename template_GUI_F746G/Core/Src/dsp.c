/*
 * dsp.c
 *
 */

#include "dsp.h"

int16_t *pdata=0;
int16_t *pdata2=0;
volatile float V_RMS = 0, A_RMS = 0, s_power = 0, a_power = 0, q_power = 0, PF=0;


float calculate_RMS(int16_t* pSamples, uint16_t len) {

	int i=0;
	float RMS=0;

	for(i=0; i<len; i++)
	{
		RMS +=pSamples[i]*pSamples[i];
	}

	RMS=sqrt(RMS/(len));
	return RMS;
}

float calculate_mean(int16_t* pSamples, uint16_t len) {

	int i=0;
	float mean=0;

	for(i=0; i<len; i++)
	{
		mean +=pSamples[i];
	}
	mean=mean/(len);

	return mean;
}


void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* p){

	if(pdata!=0)
	{
		HAL_NVIC_DisableIRQ(TIM7_IRQn);
	} else {
		pdata = &ch1[0];		//quando pdata=0 puntiamo pdata a ch1[0] e pdata2 al ch2[0]
		pdata2= &ch2[0];
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef * p){

	if (pdata!=0){
		HAL_NVIC_DisableIRQ(TIM7_IRQn);
	} else
	{
		pdata= &ch1[ADC_BUFFER_SIZE/2];		//quando pdata=0 puntiamo pdata a ch1[seconda metà] e pdata2 al ch2[seconda metà]
		pdata2=&ch2[ADC_BUFFER_SIZE/2];
	}
}

float active_power(int16_t* voltage,int16_t* current, int size)
{
	int64_t power=0;

	for(int i=0;i<size;i++) {
		power+=voltage[i]*current[i]; //calcolo della potenza istantanea
	}
	return ((3.3*3.3*power)/(size*4095.0*4095.0));
}

float no_active_power(float P,float S)
{
	q_power=sqrt((S*S)-(P*P));
	return q_power;
}

void eliminaMedia(int16_t* pSamples, uint16_t len) {

	int16_t mean=calculate_mean(pSamples, len);

	for(int i=0;i<len;i++) {
		pSamples[i] -= mean;
	}
}

void elabora(float *dato) {

	if (pdata!=0)
	{
		int ind_i = Cross(pdata, ADC_BUFFER_SIZE/2, 2048, 0); //soglia 2048 ->4096(corrispende a 3V circa)/2
		int ind_f = ReverseCross(pdata, ADC_BUFFER_SIZE/2, 2048, 0);
		int N_sample = ind_f-ind_i;

		eliminaMedia(pdata, N_sample);	//elimino la componente continua dal segnale
		eliminaMedia(pdata2, N_sample);

		a_power=active_power(pdata, pdata2, N_sample);

		V_RMS=(calculate_RMS(pdata, N_sample))*3.3/4095;
		A_RMS=(calculate_RMS(pdata2, N_sample))*3.3/4095;
		s_power=V_RMS*A_RMS;

		q_power=no_active_power(a_power, s_power);
		PF=a_power/s_power;

		dato[0]=V_RMS;		//in un vettore salviamo i risultati ottenuti
		dato[1]=A_RMS;
		dato[2]=a_power;
		dato[3]=s_power;
		dato[4]=q_power;
		dato[5]=PF;

		HAL_NVIC_EnableIRQ(TIM7_IRQn);
		pdata=0;		//resettiamo il pdata dopo che gli elementi sono stati elaborati

	}
}

