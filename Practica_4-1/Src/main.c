/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/main.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_delay.h"
/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/** @addtogroup UART_Printf
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;    // estadoAntirrebote_t

/* Private define ------------------------------------------------------------*/
#define TIEMPO_ANTIRREBOTE  40

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
delay_t botonDelay;
debounceState_t botonEstadoActual;

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

// Inicializa la máquina de estados finito del antirrebote del botón.
static void debounceFSM_init();

// Actualiza la máquina de estados finito del antirrebote del botón.
static void debounceFSM_update();

// Ejecuta las acciones correspondientes cuando se presiona el botón, invierte el estado del LED1.
static void buttonPressed();

// Ejecuta las acciones correspondientes cuando se suelta el botón, invierte el estado del LED3.
static void buttonReleased();

/* Private functions ---------------------------------------------------------*/


/**
 * @brief  Main program
 * @param  None
 * @retval None
 */

int main(void)
{
	/* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP Led for LEDs */
	BSP_LED_Init(LED1);   // LED_GREEN
	BSP_LED_Init(LED3);   // LED_RED

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	/* Inicializo MEF	*/
	debounceFSM_init();

	/* Infinite loop */
	while (1)
	{
		debounceFSM_update(); // Actualizo la máquina de estados.
	}
}

// Ejecuta las acciones correspondientes cuando se presiona el botón.
void buttonPressed()
{
	BSP_LED_Toggle(LED1);
}

// Ejecuta las acciones correspondientes cuando se suelta el botón.
void buttonReleased()
{
	BSP_LED_Toggle(LED3);
}

// Inicializa la máquina de estados del antirrebote del botón.
void debounceFSM_init()
{
	botonEstadoActual = BUTTON_UP; // La MEF inicializa con el botón sin presionar.
	delayInit(&botonDelay, TIEMPO_ANTIRREBOTE); // Inicializo el delay.
}

//Actualiza la máquina de estados del antirrebote del botón.
void debounceFSM_update()
{
	switch (botonEstadoActual)
	{
	case BUTTON_UP:
		if(BSP_PB_GetState(BUTTON_USER))
		{
			// Se detecto que presionaron el botón, inicio proceso antirrebote.
			botonEstadoActual = BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		// Espero el tiempo configurado antes de volver a chequear el valor del botón.
		if(delayRead(&botonDelay))
		{
			// Paso el tiempo de delay.
			if(BSP_PB_GetState(BUTTON_USER))
			{
				// El botón sigue presionado, indico que efectivamente se presionó.
				botonEstadoActual = BUTTON_DOWN;
				buttonPressed(); // Realizo accion correspondiente a la pulsacion del pulsador.
			}
			else
			{
				// Paso el tiempo pero no estaba presionado, lo interpreto como un rebote, indico que el botón sigue NO presionado.
				botonEstadoActual = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if(!BSP_PB_GetState(BUTTON_USER))
		{
			// Se detecto que soltaron el botón, inicio proceso antirrebote.
			botonEstadoActual = BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		// Espero el tiempo configurado antes de volver a chequear el valor del botón.
		if(delayRead(&botonDelay))
		{
			// Paso el tiempo de delay.
			if(!BSP_PB_GetState(BUTTON_USER))
			{
				// El botón sigue sin ser presionado, indico que efectivamente se soltó.
				botonEstadoActual = BUTTON_UP;
				buttonReleased(); // Realizo accion correspondiente a la liberación del pulsador.
			}
			else
			{
				// Paso el tiempo pero estaba presionado, lo interpreto como un rebote, indico que el botón sigue presionado.
				botonEstadoActual = BUTTON_DOWN;
			}

		}
		break;
	default:
		botonEstadoActual = BUTTON_UP; // En caso que pierda los estados, lo inicializo.
		break;
	}
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 180000000
 *            HCLK(Hz)                       = 180000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 360
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            PLL_R                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
      clocked below the maximum system frequency, to update the voltage scaling value
      regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	if(HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
       clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
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
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
