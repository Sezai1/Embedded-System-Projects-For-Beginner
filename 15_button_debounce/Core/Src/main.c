/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
// Kullanilan Kutuphaneleri Ekle
#include "stdio.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define Button_1 GPIO_PIN_1  // Buton1 A portun pin 1 numarasina bagli
#define Button_2 GPIO_PIN_2  // Buton2 A portun pin 2 numarasina bagli

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
// Global degiskenleri tanimla.
uint8_t state1;
uint8_t state2;
uint32_t gettick1;
uint32_t gettick2;
int button1_data;
int button2_data;
char error_message[40];
// int counter = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

void Read_Button()  // Buton durumunu okuma fonksiyonu
{
	  state1 = HAL_GPIO_ReadPin(GPIOA, Button_1); // boton1 logic durumunu oku.
	  state2 = HAL_GPIO_ReadPin(GPIOA, Button_2); // boton2 logic durumunu oku.

	  while(state1 | state2)  // Buton1 veya buton2 basildiysa donguden cikma.
	  {
		  gettick1 = HAL_GetTick(); // Mikroislemci calismaya basladiginden beri 1. gecen sureyi olc.
		  HAL_TIM_Base_Start_IT(&htim1);  // 300 milisaniye periyotlu timer birimini baslat.
		  state1 = HAL_GPIO_ReadPin(GPIOA, Button_1); // Buton1 durumunu devamli oku.
		  state2 = HAL_GPIO_ReadPin(GPIOA, Button_2); // Buton2 durumunu devamlı oku.
	  }

	  gettick2 = HAL_GetTick();  // Mikroislemci calismaya basladigindan beri 2. gecen sureyi olc.
	  if(gettick2 - gettick1 < 300 ) // Buton1 veya buton2 basili kalma suresi 300' den kucukse
		  HAL_TIM_Base_Stop_IT(&htim1); /* Timer sayacini durdur.(Boylce HAL_TIM_PeriodElapsedCallback
				  	  	  	  	  	  	... fonksiyonu calismayacak. Debounce suresi = 300ms) */
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Timer sayaci autoreload degerine ulastiginda PC bu fonksiyonu calistiracak.(Periyodik olarak)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // Debounce suresi asildiysa
{															// ... bu fonksiyonu calistir.
      button1_data = state1;  // Buton1 durumunu set et
      button2_data = state2;  // Buton2 durumunu set et
      // counter++;
	  if (button1_data & button2_data) // Buton1 ve buton2 ikisi birden basiliysa
		  strcpy(error_message,"Button1 and Button2 timed out"); // Hata mesajini olustur.
	  else if (button1_data) // Sadece buton1 basildiysa,
		  strcpy(error_message,"Button1 timed out"); // Hata mesajini olustur.
	  else if (button2_data  ) // Sadece buton2 basildiysa,
	  	  strcpy(error_message,"Button2 timed out");  // Hata mesajini olustur.
	  else;

	  HAL_TIM_Base_Stop_IT(&htim1); // Timer sayacini durdur. (Herhangi bir buton bir daha
	  // ... basili kalmazsa timer calismayacak.)
}
/* Timer ayarlari CubeMX ile yapildi. Yapilan  ayarlar su sekildedir;
- Timer1 aktif edildi ve Timer1 biriminin bagli oldugu hat (APB2) frekansi 16MHz ayarlandi.
- Prescaler degeri = 16000 yapilarak timer frekansi 1kHz ayarlandi.(Boylece 1ms'de bir counter
degeri 1 artacak.
- Autoreload degeri = 300 ayarlandi. Counter degeri 300 oldugunda overflow olusacak ve PC
HAL_TIM_PeriodElapsedCallback fonksiyonunu calistiracak.
- Sonuc olarak buton  300ms'den uzun basili kaldiysa debounce suresi asilmis olacak. */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  Read_Button();  // Buton durumu okuma fonksiyonunu cagir.
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 16000-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 300-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pins : PA1 PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
