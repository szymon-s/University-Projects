/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
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
I2C_HandleTypeDef hi2c1;

IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_IWDG_Init(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile _Bool buttonPressed=0 , selPressed=0, incPressed=0, decPressed=0, nextPressed=0, beforePressed=0;
uint8_t Temp_byte1=0, Temp_byte2=0;
uint8_t currentRow=1;
_Bool editionEnabled=0;
_Bool editionEnd=0;
_Bool hysteresisActive=0;
_Bool working=0;
uint8_t mode=0;
uint8_t modeNew=0;
_Bool manual=0;
volatile float timePassed=0.0;
float temperature=0.0;
float workingTime=1.0;
float restingTime=1.0;
float workingTemperature=30.0;
float hysteresis=5.0;
_Bool manualNew=0;
float workingTimeNew=1.0;
float restingTimeNew=1.0;
float workingTemperatureNew=30.0;
float hysteresisNew=5.0;
char firstRowString[20];
char secondRowString[20];
char thirdRowString[20];
char fourthRowString[20];


void Delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);
	    while ((__HAL_TIM_GET_COUNTER(&htim1))<us);
}

#define SLAVE_ADDRESS_LCD 0x4E // change this according to your setup

void lcd_send_cmd (char cmd)
{
	__disable_irq();
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,data_t, 4, 100);
	__enable_irq();
}

void lcd_send_data (char data)
{

	__disable_irq();
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD, data_t, 4, 100);

	__enable_irq();
}





void loadingScreen()
{
	int i;
	int j=0;
	char first[20]=	{'I','N','I','C','J','A','L','I','Z','A','C','J','A',' ',' ',' ',' ',' ',' ',' '};
	char second[20]={'.','.','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	char third[20]=	{'.','.','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	char fourth[20]={'.','.','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

	for(i=0x00; i<0x14 ; i++)
	{
		lcd_send_cmd (0x80|i);
		lcd_send_data(first[j]);
		HAL_Delay(10);
		j++;
	}
	j=0;
	for(i=0x40; i<0x54 ; i++)
	{
		lcd_send_cmd (0x80|i);
		lcd_send_data(second[j]);
		HAL_Delay(10);
		j++;
	}
	j=0;

	for(i=0x14;i<0x28;i++)
	{
		lcd_send_cmd (0x80|i);
		lcd_send_data(third[j]);
		HAL_Delay(10);
		j++;
	}
	j=0;
	for(i=0x54; i<0x68 ; i++)
	{
		lcd_send_cmd (0x80|i);
		lcd_send_data(fourth[j]);
		HAL_Delay(10);
		j++;
	}

	HAL_Delay(200);
}

void lcd_init (void)
{

	// 4 bit initialisation
	HAL_Delay(41);  // wait for >40ms
	lcd_send_cmd (0x30);
	Delay_us(42000);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	Delay_us(110);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(50);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(50);

	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)

	loadingScreen();
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}



int DS18B20_Start (void)
{
	int Response = 0;
	Set_Pin_Output(DS18B20_GPIO_Port, DS18B20_Pin);   // set the pin as output
	HAL_GPIO_WritePin (DS18B20_GPIO_Port, DS18B20_Pin, 0);  // pull the pin low
	Delay_us (480-8);   // delay according to datasheet

	Set_Pin_Input(DS18B20_GPIO_Port, DS18B20_Pin);    // set the pin as input
	Delay_us (60);    // delay according to datasheet

	if (!(HAL_GPIO_ReadPin (DS18B20_GPIO_Port, DS18B20_Pin))) Response = 1;    // if the pin is low i.e the presence pulse is detected
	else Response = -1;

	Delay_us (420); // 480 us delay totally.

	return Response;
}

void DS18B20_Write (uint8_t data)
{
	Set_Pin_Output(DS18B20_GPIO_Port, DS18B20_Pin);  // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			Set_Pin_Output(DS18B20_GPIO_Port, DS18B20_Pin);  // set as output
			HAL_GPIO_WritePin (DS18B20_GPIO_Port, DS18B20_Pin, 0);  // pull the pin LOW
			Delay_us (2);  // wait for 1 us
			HAL_GPIO_WritePin (DS18B20_GPIO_Port, DS18B20_Pin, 1);  // pull the pin LOW
			Delay_us (2);  // wait for 1 us

			Set_Pin_Input(DS18B20_GPIO_Port, DS18B20_Pin);  // set as input
			Delay_us (42-8);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			Set_Pin_Output(DS18B20_GPIO_Port, DS18B20_Pin);
			HAL_GPIO_WritePin (DS18B20_GPIO_Port, DS18B20_Pin, 0);  // pull the pin LOW
			Delay_us (60);  // wait for 60 us

			Set_Pin_Input(DS18B20_GPIO_Port, DS18B20_Pin);
		}
	}
}

uint8_t DS18B20_Read (void)
{
	uint8_t value=0;

	Set_Pin_Input(DS18B20_GPIO_Port, DS18B20_Pin);

	for (int i=0;i<8;i++)
	{
		Set_Pin_Output(DS18B20_GPIO_Port, DS18B20_Pin);   // set as output

		HAL_GPIO_WritePin (DS18B20_GPIO_Port, DS18B20_Pin, 0);  // pull the data pin LOW
		Delay_us (5);  // wait for > 1us

		Set_Pin_Input(DS18B20_GPIO_Port, DS18B20_Pin);  // set as input
		if (HAL_GPIO_ReadPin (DS18B20_GPIO_Port, DS18B20_Pin))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		else
			value |= 0<<i;  // read = 0
		Delay_us (60-8);  // wait for 60 us
	}
	return value;
}

void prepareTemperature()
{
	DS18B20_Start();
	HAL_Delay(1);
	DS18B20_Write(0xCC);
	DS18B20_Write(0x44);
}

void readTemperature()
{
	 HAL_Delay(550);
	 DS18B20_Start();
	 HAL_Delay(1);
	 DS18B20_Write(0xCC);
	 DS18B20_Write(0xBE);

	 Temp_byte1= DS18B20_Read();
	 Temp_byte2= DS18B20_Read();
	 temperature=(float)((Temp_byte2<<8)|Temp_byte1)/16;
	 if(temperature<0.0 || temperature>125.0)
		 temperature=0.0;
}

void updateScreen()
{
	lcd_send_cmd (0x80|0x00);
	lcd_send_string(firstRowString);
	lcd_send_cmd (0x80|0x0E);
	if(working)
		lcd_send_string("P:ON  ");
	else
		lcd_send_string("P:OFF ");
 	lcd_send_cmd (0x80|0x40);
 	lcd_send_string(secondRowString);
 	lcd_send_cmd (0x80|0x14);
 	lcd_send_string(thirdRowString);
 	lcd_send_cmd (0x80|0x54);
 	lcd_send_string(fourthRowString);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim2)
	{
		timePassed+=0.5;
	}
}

void checkKeyboard()
{
	if(buttonPressed)
	{
		if(selPressed)
		{
			editionEnabled = !editionEnabled;
			if(!editionEnabled)
				editionEnd=1;
			HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,editionEnabled);
			selPressed=0;
		}
		else if(editionEnabled)
		{
				if (decPressed)
				{
					if(modeNew==0)
					{
						currentRow++;
						if(currentRow>2)
							currentRow=1;

					}
					else
					{
						currentRow++;
						if(currentRow>3)
							currentRow=1;
					}
					decPressed=0;

				}
				else if (incPressed)
				{
					if(modeNew==0)
					{
						currentRow--;
						if(currentRow<1)
							currentRow=2;
					}
					else
					{
						currentRow--;
						if(currentRow<1)
							currentRow=3;
					}
					incPressed=0;
				}
				else if (beforePressed)
				{
					switch(modeNew)
					{
						case 0:
							switch(currentRow)
							{
							case 1:
								modeNew=2;
								break;
							case 2:
								manualNew=!manualNew;
								break;
							}
							break;
						case 1:
							switch(currentRow)
							{
								case 1:
									modeNew=0;
									break;
								case 2:
									workingTemperatureNew-=0.5;
									if(workingTemperatureNew<5.0)
										workingTemperatureNew=5.0;
									break;
								case 3:
									hysteresisNew-=0.5;
									if(hysteresisNew<0.5)
										hysteresisNew=0.5;
									break;
							}
							break;
						case 2:
							switch(currentRow)
							{
							case 1:
								modeNew=1;
								break;
							case 2:
								workingTimeNew-=0.5;
								if(workingTimeNew<0.5)
									workingTimeNew=0.5;
								break;
							case 3:
								restingTimeNew-=0.5;
								if(restingTimeNew<0.5)
									restingTimeNew=0.5;
								break;
							}
							break;
					}
					beforePressed=0;
				}
				else if (nextPressed)
				{
					switch(modeNew)
							{
								case 0:
								switch(currentRow)
								{
								case 1:
									modeNew=1;
									break;
								case 2:
									manualNew=!manualNew;
									break;
								}
								break;
								case 1:
									switch(currentRow)
									{
										case 1:
											modeNew=2;
											break;
										case 2:
											workingTemperatureNew+=0.5;
											if(workingTemperatureNew>80.0)
												workingTemperatureNew=80.0;
											break;
										case 3:
											hysteresisNew+=0.5;
											if(hysteresisNew>30.0)
												hysteresisNew=30.0;
											break;
									}
									break;
								case 2:
									switch(currentRow)
									{
									case 1:
										modeNew=0;
										break;
									case 2:
										workingTimeNew+=0.5;
										if(workingTimeNew>60.0)
											workingTimeNew=60.0;
										break;
									case 3:
										restingTimeNew+=0.5;
										if(restingTimeNew>60.0)
											restingTimeNew=60.0;
										break;
									}
									break;
							}
					nextPressed=0;
				}
		}
		HAL_Delay(150);
		buttonPressed=0;
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(!buttonPressed)
	{
		buttonPressed=1;
		if(GPIO_Pin==SEL_Pin)
		{
			selPressed=1;
		}
		else if(GPIO_Pin==DEC_Pin)
		{
			decPressed=1;
		}
		else if (GPIO_Pin==INC_Pin)
		{
			incPressed=1;
		}
		else if (GPIO_Pin==BEFORE_Pin)
		{
			beforePressed=1;
		}
		else if (GPIO_Pin==NEXT_Pin)
		{
			nextPressed=1;
		}
	}
}

void updateCursor()
{
	if(editionEnabled)
	{
		  switch(currentRow)
		  {
			 case 1:
				 lcd_send_cmd (0x80|0x53);
				 lcd_send_data(127);
				 lcd_send_cmd (0x80|0x67);
				 lcd_send_data(' ');
				 lcd_send_cmd (0x80|0x27);
				 lcd_send_data(' ');
				 break;
			 case 2:
				 lcd_send_cmd (0x80|0x27);
				 lcd_send_data(127);
				 lcd_send_cmd (0x80|0x53);
				 lcd_send_data(' ');
				 lcd_send_cmd (0x80|0x67);
				 lcd_send_data(' ');
				 break;
			 case 3:
				 lcd_send_cmd (0x80|0x67);
				 lcd_send_data(127);
				 lcd_send_cmd (0x80|0x53);
				 lcd_send_data(' ');
				 lcd_send_cmd (0x80|0x27);
				 lcd_send_data(' ');
				 break;
		  }
	}
	else
	{
			lcd_send_cmd (0x80|0x27);
			 lcd_send_data(' ');
			lcd_send_cmd (0x80|0x53);
			 lcd_send_data(' ');
			lcd_send_cmd (0x80|0x67);
			 lcd_send_data(' ');
	}
}
void controlRelay()
{
	switch(mode)
	{
		case 0:
			working=manual;
			break;

		case 1:
			if(temperature<workingTemperature)
			{
				if(temperature<(workingTemperature-hysteresis) || !hysteresisActive)
				{
					hysteresisActive = 0;
					working=1;
				}
			}
			else
			{
				hysteresisActive=1;
				working=0;
			}
			break;

		case 2:
			if(working)
			{
				if(timePassed>=workingTime)
				{
					working=0;
					timePassed=0;
					__HAL_TIM_SET_COUNTER(&htim2,0);
				}
			}
			else
			{
				if(timePassed>=restingTime)
				{
					working=1;
					timePassed=0;
					__HAL_TIM_SET_COUNTER(&htim2,0);
				}
			}
			break;

	}
}

void prepareStrings()
{
	snprintf(firstRowString,19,			"TEMP:%.1f %cC",temperature,223);
	switch(modeNew)
	{
		case 0:
			snprintf		(secondRowString,19,	"TRYB:MANUALNY      ");
			if(manualNew)
				snprintf	(thirdRowString,19,	"PRACA POMPY:TAK    ");
			else
				snprintf	(thirdRowString,19,	"PRACA POMPY:NIE    ");
			snprintf		(fourthRowString,19,	"                   ");
			break;
		case 1:
			snprintf		(secondRowString,19,	"TRYB:TEMPERATURA   ");
			snprintf		(thirdRowString,19, 	"TEMP WYL:%.1f %cC  ",workingTemperatureNew,223);
			snprintf		(fourthRowString,19,	"HISTEREZA:%.1f %cC ",hysteresisNew,223);
			break;
		case 2:
			snprintf		(secondRowString,19,	"TRYB:CZAS          ");
			snprintf		(thirdRowString,19, 	"PRACA:%.1f min     ",workingTimeNew);
			snprintf		(fourthRowString,19,	"SPOCZYNEK:%.1f min ",restingTimeNew);
			break;
	}
}
void updateVariables()
{
	mode=modeNew;
	manual=manualNew;
	workingTime=workingTimeNew;
	restingTime=restingTimeNew;
	workingTemperature=workingTemperatureNew;
	hysteresis=hysteresisNew;
	hysteresisActive=0;
	if(mode==2)
		{
			working=1;
			timePassed=0;
			__HAL_TIM_SET_COUNTER(&htim2,0);
		}
}
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_Base_Start_IT(&htim2);
  prepareTemperature();
  readTemperature();
  lcd_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  	  	prepareTemperature();
	  	  	checkKeyboard();
	  	  	readTemperature();
	  	  	if(editionEnd)
	  	  	{
	  	  		updateVariables();
	  	  		currentRow=1;
	  	  		editionEnd=0;
	  	  	}
	  	  	controlRelay();
	  	  	prepareStrings();
		 	HAL_GPIO_WritePin(GPIOB,RELAY_Pin,working);
		 	HAL_IWDG_Refresh(&hiwdg);
		 	updateScreen();
		 	updateCursor();


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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 36;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration 
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10808ED6;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_DISABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 2999;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

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
  htim1.Init.Prescaler = 72-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
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
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
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

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 40000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 54000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  huart2.Init.BaudRate = 115200;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DS18B20_Pin|LED_Pin|RELAY_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : NEXT_Pin BEFORE_Pin INC_Pin DEC_Pin 
                           SEL_Pin */
  GPIO_InitStruct.Pin = NEXT_Pin|BEFORE_Pin|INC_Pin|DEC_Pin 
                          |SEL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DS18B20_Pin */
  GPIO_InitStruct.Pin = DS18B20_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(DS18B20_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_Pin RELAY_Pin */
  GPIO_InitStruct.Pin = LED_Pin|RELAY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
