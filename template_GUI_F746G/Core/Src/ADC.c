/*
 * ADC.c
 */


#include "ADC.h"


ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc3;
DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc3;
TIM_HandleTypeDef htim7;

static void MX_ADC1_Init(void);
static void MX_ADC3_Init(void);
static void MX_TIM7_Init(void);
static void MX_DMA_Init(void);

int16_t ch1[ADC_BUFFER_SIZE];
int16_t ch2[ADC_BUFFER_SIZE];

void adc_init(void){
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_ADC3_Init();
	MX_TIM7_Init();

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ch1, ADC_BUFFER_SIZE);
	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)ch2, ADC_BUFFER_SIZE);
	HAL_TIM_Base_Start_IT(&htim7);
}

static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(DMA2_Stream1_IRQn);

}

static void MX_ADC1_Init(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{

	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{

	}


}

/**
 * @brief adc3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC3_Init(void)
{

	ADC_ChannelConfTypeDef sConfig = {0};

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc3.Instance = ADC3;
	hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc3.Init.Resolution = ADC_RESOLUTION_12B;
	hadc3.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc3.Init.ContinuousConvMode = DISABLE;
	hadc3.Init.DiscontinuousConvMode = DISABLE;
	hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc3.Init.NbrOfConversion = 1;
	hadc3.Init.DMAContinuousRequests = ENABLE;
	hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc3) != HAL_OK)
	{

	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
	{

	}

}

static void MX_TIM7_Init(void)
{


	TIM_MasterConfigTypeDef sMasterConfig = {0};

	__HAL_RCC_TIM7_CLK_ENABLE();

	htim7.Instance = TIM7;
	htim7.Init.Prescaler = 99;
	htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim7.Init.Period = 999;
	htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_Base_Init(&htim7);
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
	{

	}

	HAL_NVIC_SetPriority(TIM7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if(hadc->Instance==ADC1)
	{

		/* Peripheral clock enable */
		__HAL_RCC_ADC1_CLK_ENABLE();

		/**adc1 GPIO Configuration
    PA0/WKUP     ------> adc1_IN0
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_0;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* adc1 DMA Init */
		/* adc1 Init */
		hdma_adc1.Instance = DMA2_Stream4;
		hdma_adc1.Init.Channel = DMA_CHANNEL_0;
		hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adc1.Init.Mode = DMA_CIRCULAR;
		hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
		hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
		hdma_adc1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_adc1.Init.MemBurst = DMA_MBURST_SINGLE;
		hdma_adc1.Init.PeriphBurst = DMA_PBURST_SINGLE;

		if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
		{

		}

		__HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);

		/* USER CODE BEGIN adc1_MspInit 1 */

		/* USER CODE END adc1_MspInit 1 */
	}
	else if(hadc->Instance==ADC3)
	{
		/* USER CODE BEGIN adc3_MspInit 0 */

		/* USER CODE END adc3_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_ADC3_CLK_ENABLE();

		/**adc3 GPIO Configuration
    PF7     ------> adc3_IN5
    PF6     ------> adc3_IN4
    PF10     ------> adc3_IN8
    PF9     ------> adc3_IN7
    PF8     ------> adc3_IN6
    PA0/WKUP     ------> adc3_IN0
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);


		/* adc3 DMA Init */
		/* adc3 Init */
		hdma_adc3.Instance = DMA2_Stream1;
		hdma_adc3.Init.Channel = DMA_CHANNEL_2;
		hdma_adc3.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc3.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc3.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc3.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc3.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adc3.Init.Mode = DMA_CIRCULAR;
		hdma_adc3.Init.Priority = DMA_PRIORITY_MEDIUM;
		hdma_adc3.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
		hdma_adc3.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_adc3.Init.MemBurst = DMA_MBURST_SINGLE;
		hdma_adc3.Init.PeriphBurst = DMA_PBURST_SINGLE;
		HAL_DMA_Init(&hdma_adc3);
		__HAL_LINKDMA(hadc,DMA_Handle,hdma_adc3);

		/* USER CODE BEGIN adc3_MspInit 1 */

		/* USER CODE END adc3_MspInit 1 */
	}

}

void TIM7_IRQHandler(void) {
	//HAL_TIM_IRQHandler(&htim7);

	__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
	hadc3.Instance->CR2 |= (uint32_t)ADC_CR2_SWSTART;
	hadc1.Instance->CR2 |= (uint32_t)ADC_CR2_SWSTART;
}



/**
 * @brief This function handles DMA2 stream0 global interrupt.
 */
void DMA2_Stream4_IRQHandler(void) {
	HAL_DMA_IRQHandler(&hdma_adc1);
}
void DMA2_Stream1_IRQHandler(void) {
	HAL_DMA_IRQHandler(&hdma_adc3);
}


