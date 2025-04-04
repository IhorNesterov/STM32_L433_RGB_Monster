/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "NOS_Lib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
DMA_HandleTypeDef hdma_tim2_ch1;
DMA_HandleTypeDef hdma_tim2_up;
DMA_HandleTypeDef hdma_tim2_ch2_ch4;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
extern uint8_t frameBufferA[3 * 512];
extern uint8_t frameBufferB[3 * 512];
extern uint8_t frameBufferC[3 * 512];
extern uint8_t frameBufferD[3 * 512];

NOS_TimeEvent screenUpdateEvent = {0};

WS2812B_Strip stripA = {0};
WS2812B_Strip stripB = {0};
WS2812B_Strip stripC = {0};
WS2812B_Strip stripD = {0};

PixelColor pixelsA[512];
PixelColor pixelsB[512];
PixelColor pixelsC[512];
PixelColor pixelsD[512];

NOS_UART_Struct UART2;
NOS_UART_Struct UART1;

int receiveTime = 0;

int uartPixelCount = 0;

int currColor = 0;
int buttonDelay = 0;

Effect_Struct breatheA = {0};
Effect_Struct rainbowA = {0};
Effect_Struct dotsA = {0};
Effect_Struct walkingPixelA = {0};
Effect_Struct steadyColorA = {0};

NOS_Short value;

UART_Message lastMessage;
UART_Message bluetoothMessage;

NOS_Flash_Chunk tempInitChunk = {0};

NOS_Flash_Memory_Struct flashMemoryStruct = {0};

PixelColor nullColor = {0,0,0};
PixelColor white = {255,255,255};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
bool receive = false;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
  if(huart->Instance == USART2)
  {  
    NOS_UART_ReceiveHandler(&UART2,huart);
    receive = true;
  }

  if(huart->Instance == USART1)
  {
    NOS_UART_ReceiveHandler(&UART1,huart);
    receive = true;
  }
}

bool tick = false;
bool screenUpdate = false;

#define FLASH_REBUILD
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
  MX_DMA_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1,UART1.rx_buff,1);
  HAL_UART_Receive_IT(&huart2,UART2.rx_buff,1);

  HAL_UART_Transmit(&huart1,"HELLO",sizeof("HELLO"),1000);
  HAL_UART_Transmit(&huart2,"HELLO",sizeof("HELLO"),1000);

  visInit();

  NOS_WS2812B_Strip_FullInit(&stripA,&frameBufferA,&pixelsA,128);
  NOS_WS2812B_Strip_FullInit(&stripB,&frameBufferB,&pixelsB,128);
  NOS_WS2812B_Strip_FullInit(&stripC,&frameBufferC,&pixelsC,128);
  NOS_WS2812B_Strip_FullInit(&stripD,&frameBufferD,&pixelsD,128);

  NOS_TimeEvent_Init(&screenUpdateEvent, 20);

  NOS_UART_ReceiveAbort(&UART2,&huart2);
  NOS_UART_ReceiveAbort(&UART1,&huart1);

  /*
  NOS_FlashMemory_Struct_Init(&flashMemoryStruct,FLASH_STORAGE_A);

  NOS_Flash_Chunk_Init(&tempInitChunk,&breatheA,sizeof(Effect_Struct));
  NOS_FlashMemory_Struct_AddChunk(&flashMemoryStruct,&tempInitChunk);

  NOS_Flash_Chunk_Init(&tempInitChunk,&rainbowA,sizeof(Effect_Struct));
  NOS_FlashMemory_Struct_AddChunk(&flashMemoryStruct,&tempInitChunk);

  NOS_Flash_Chunk_Init(&tempInitChunk,&dotsA,sizeof(Effect_Struct));
  NOS_FlashMemory_Struct_AddChunk(&flashMemoryStruct,&tempInitChunk);

  NOS_Flash_Chunk_Init(&tempInitChunk,&walkingPixelA,sizeof(Effect_Struct));
  NOS_FlashMemory_Struct_AddChunk(&flashMemoryStruct,&tempInitChunk);

  NOS_Flash_Chunk_Init(&tempInitChunk,&steadyColorA,sizeof(Effect_Struct));
  NOS_FlashMemory_Struct_AddChunk(&flashMemoryStruct,&tempInitChunk);
  
  #ifndef FLASH_REBUILD
  if(NOS_FlashMemory_Struct_Validate(&flashMemoryStruct))
  {
    NOS_Flash_Memory_Struct_Load(&flashMemoryStruct);
  }
  else
  {
    NOS_WS2812B_Strip_Effect_Init(&breatheA,&nullColor,100,1,60,80,0,0,0,0,EFFECT_BREATHE_ID,true);
    NOS_WS2812B_Strip_Effect_Init(&rainbowA,&nullColor,1000,1,200,800,0,0,0,0,EFFECT_RAINBOW_ID,true);
    NOS_WS2812B_Strip_Effect_Init(&dotsA,&white,40,1,0,100,0,0,0,0,EFFECT_DOTS_ID,true);
    NOS_WS2812B_Strip_Effect_Init(&walkingPixelA,&white,1000,1,0,48,3,0,0,0,EFFECT_WALKING_PIXELS_ID,true);
    NOS_WS2812B_Strip_Effect_Init(&steadyColorA,&white,0,0,0,0,0,0,0,0,EFFECT_STEADY_COLOR_ID,true);
  }
  #endif
*/
  #ifdef FLASH_REBUILD
  NOS_WS2812B_Strip_Effect_Init(&breatheA,&nullColor,20,1,40,60,0,0,0,0,EFFECT_BREATHE_ID,true);
  NOS_WS2812B_Strip_Effect_Init(&rainbowA,&nullColor,1000,1,200,800,0,0,0,0,EFFECT_RAINBOW_ID,false);
  NOS_WS2812B_Strip_Effect_Init(&dotsA,&white,40,1,0,100,0,0,0,0,EFFECT_DOTS_ID,false);
  NOS_WS2812B_Strip_Effect_Init(&walkingPixelA,&white,100,1,0,48,3,0,0,0,EFFECT_WALKING_PIXELS_ID,false);
  NOS_WS2812B_Strip_Effect_Init(&steadyColorA,&white,0,0,0,0,0,0,0,0,EFFECT_STEADY_COLOR_ID,false);
  #endif

  NOS_WS2812B_Strip_Effects_AddEffect(&stripA,breatheA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripB,breatheA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripC,breatheA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripD,breatheA);

  NOS_WS2812B_Strip_Effects_AddEffect(&stripA,rainbowA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripB,rainbowA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripC,rainbowA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripD,rainbowA);

  NOS_WS2812B_Strip_Effects_AddEffect(&stripA,dotsA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripB,dotsA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripC,dotsA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripD,dotsA);

  NOS_WS2812B_Strip_Effects_AddEffect(&stripA,walkingPixelA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripB,walkingPixelA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripC,walkingPixelA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripD,walkingPixelA);

  NOS_WS2812B_Strip_Effects_AddEffect(&stripA,steadyColorA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripB,steadyColorA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripC,steadyColorA);
  NOS_WS2812B_Strip_Effects_AddEffect(&stripD,steadyColorA);

  NOS_WS2812B_Strip_ColorFill(&stripA,white);
  NOS_WS2812B_Strip_ColorFill(&stripB,white);
  NOS_WS2812B_Strip_ColorFill(&stripC,white);
  NOS_WS2812B_Strip_ColorFill(&stripD,white);

  NOS_WS2812B_Strip_Update(&stripA);
  NOS_WS2812B_Strip_Update(&stripB);
  NOS_WS2812B_Strip_Update(&stripC);
  NOS_WS2812B_Strip_Update(&stripD);

  NOS_Strip_UART_ParseStringCommand(&stripA,"&/Breathe/70/80/20/true/&/Rainbow/#0000ff/#7f00ff/60/false/&/Dots/#ffff00/60/true/&/Walking/#ffff00/5/70/false/&/Steady/#00ff00/false/&",136);
  NOS_Strip_UART_ParseStringCommand(&stripB,"&/Breathe/70/80/20/true/&/Rainbow/#0000ff/#7f00ff/60/false/&/Dots/#ffff00/60/true/&/Walking/#ffff00/5/70/false/&/Steady/#00ff00/false/&",136);
  NOS_Strip_UART_ParseStringCommand(&stripC,"&/Breathe/70/80/20/true/&/Rainbow/#0000ff/#7f00ff/60/false/&/Dots/#ffff00/60/true/&/Walking/#ffff00/5/70/false/&/Steady/#00ff00/false/&",136);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if(tick)
    {
          NOS_UART_Timer_Handler(&UART2);
          NOS_UART_Timer_Handler(&UART1);

          NOS_TimeEvent_TickHandler(&screenUpdateEvent);

          NOS_WS2812B_Strip_Effects_Handler(&stripA);
          NOS_WS2812B_Strip_Effects_Handler(&stripB);
          NOS_WS2812B_Strip_Effects_Handler(&stripC);
          NOS_WS2812B_Strip_Effects_Handler(&stripD);
          tick = false;
    }

    if(NOS_UART_CheckReceive(&UART1))
    {
      if(NOS_Strip_UART_ParseStringCommand(&stripA,UART1.rx_buff,UART1.lastMessageSize))
      {
        NOS_Strip_UART_ParseStringCommand(&stripB,UART1.rx_buff,UART1.lastMessageSize);
        NOS_Strip_UART_ParseStringCommand(&stripC,UART1.rx_buff,UART1.lastMessageSize);
        NOS_Strip_UART_ParseStringCommand(&stripD,UART1.rx_buff,UART1.lastMessageSize);

        /*
        NOS_WS2812B_Strip_Effect_Copy(&breatheA,&stripA.effects[0]);
        NOS_WS2812B_Strip_Effect_Copy(&rainbowA,&stripA.effects[1]);
        NOS_WS2812B_Strip_Effect_Copy(&dotsA,&stripA.effects[2]);
        NOS_WS2812B_Strip_Effect_Copy(&walkingPixelA,&stripA.effects[3]);
        NOS_WS2812B_Strip_Effect_Copy(&steadyColorA,&stripA.effects[4]);
        */

        //NOS_Flash_Memory_Struct_Save(&flashMemoryStruct);
      }

      NOS_UART_EndReceive(&UART1);
      HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
      
      NOS_WS2812B_Strip_Update(&stripA);
      NOS_WS2812B_Strip_Update(&stripB);
      NOS_WS2812B_Strip_Update(&stripC);
      NOS_WS2812B_Strip_Update(&stripD);
      visHandle();

    }

    if(NOS_UART_CheckReceive(&UART2))
    {
      if(NOS_UART_ParsePacket(&UART2,&lastMessage)) 
      {
      
      switch (lastMessage.channel.data)
      {
        //Global leds strips commands
        case 0x01:
        
          NOS_Strip_UART_ParseCommand(&stripA,&lastMessage);
          NOS_Strip_UART_ParseCommand(&stripB,&lastMessage);
          NOS_Strip_UART_ParseCommand(&stripC,&lastMessage);
          NOS_Strip_UART_ParseCommand(&stripD,&lastMessage);

          NOS_WS2812B_Strip_Effect_Copy(&breatheA,&stripA.effects[0]);
          NOS_WS2812B_Strip_Effect_Copy(&rainbowA,&stripA.effects[1]);
          NOS_WS2812B_Strip_Effect_Copy(&dotsA,&stripA.effects[2]);
          NOS_WS2812B_Strip_Effect_Copy(&walkingPixelA,&stripA.effects[3]);
          NOS_WS2812B_Strip_Effect_Copy(&steadyColorA,&stripA.effects[4]);


          //NOS_Flash_Memory_Struct_Save(&flashMemoryStruct);

        break;

        //stripA commands
        case 0x02:

          NOS_Strip_UART_ParseCommand(&stripA,&lastMessage);
          NOS_WS2812B_Strip_Effect_Copy(&dotsA,&stripA.effects[2]);
          //NOS_Flash_Memory_Struct_Save(&flashMemoryStruct);

        break;

        //stripB commands
        case 0x03:

          NOS_Strip_UART_ParseCommand(&stripB,&lastMessage);
          NOS_WS2812B_Strip_Effect_Copy(&dotsA,&stripB.effects[2]);
          //NOS_Flash_Memory_Struct_Save(&flashMemoryStruct);
              
        break;

        //stripC commands
        case 0x04:

          NOS_Strip_UART_ParseCommand(&stripC,&lastMessage);
          NOS_WS2812B_Strip_Effect_Copy(&dotsA,&stripC.effects[2]);
          //NOS_Flash_Memory_Struct_Save(&flashMemoryStruct);

        break;

        //stripD commands
        case 0x05:

          NOS_Strip_UART_ParseCommand(&stripD,&lastMessage);
          NOS_WS2812B_Strip_Effect_Copy(&dotsA,&stripD.effects[2]);
          //NOS_Flash_Memory_Struct_Save(&flashMemoryStruct);

        break;

          default:
          break;
        }
      }

      NOS_UART_EndReceive(&UART2);
      HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
      
      NOS_UART_PacketApprovedNotice(&lastMessage,&huart2);
      
      NOS_WS2812B_Strip_Update(&stripA);
      NOS_WS2812B_Strip_Update(&stripB);
      NOS_WS2812B_Strip_Update(&stripC);
      NOS_WS2812B_Strip_Update(&stripD);
      visHandle();
      
    }

    if (NOS_TimeEvent_Check(&screenUpdateEvent))
    {
      
      NOS_WS2812B_Strip_Update(&stripA);
      NOS_WS2812B_Strip_Update(&stripB);
      NOS_WS2812B_Strip_Update(&stripC);
      NOS_WS2812B_Strip_Update(&stripD);

      visHandle();
      
      NOS_TimeEvent_FinishEvent(&screenUpdateEvent);
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 460800;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DIA_LED_Pin|WS_LED_1_Pin|WS_LED_2_Pin|WS_LED_3_Pin
                          |WS_LED_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DIA_LED_Pin WS_LED_1_Pin WS_LED_2_Pin WS_LED_3_Pin
                           WS_LED_4_Pin */
  GPIO_InitStruct.Pin = DIA_LED_Pin|WS_LED_1_Pin|WS_LED_2_Pin|WS_LED_3_Pin
                          |WS_LED_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PH3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
