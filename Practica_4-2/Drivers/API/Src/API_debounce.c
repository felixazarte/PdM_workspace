
/* Includes ------------------------------------------------------------------*/
#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
/* Private functions ---------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;         // estadadoAntiRebote_t

/* Private define ------------------------------------------------------------*/
#define TIEMPO_ANTIRREBOTE	40    // BUTTON_DEBOUNCE_TIME

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static delay_t botonDelay;
static debounceState_t  botonEstadoActual;
static bool_t botonPresionado;

// Inicializa la máquina de estados del antirrebote del botón.
void debounceFSM_init()
{
	botonEstadoActual = BUTTON_UP; // La MEF inicializa con el botón sin presionar.
	delayInit(&botonDelay, TIEMPO_ANTIRREBOTE); // Inicializo el delay.
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO); /* Initialize BSP PB for BUTTON_USER */
	botonPresionado = false; // Pongo en 0 el flag
}
 // Actualizo la MEF
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
				botonPresionado = true; // Levanto el flag para indicar que se presionó el botón.
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
		// Espero el tiempo configurado antes de volver a chequear el valor del pulsador.
		if(delayRead(&botonDelay))
		{
			// Paso el tiempo de delay.
			if(!BSP_PB_GetState(BUTTON_USER))
			{
				// El botón sigue sin ser presionado, indico que efectivamente se soltó.
				botonEstadoActual = BUTTON_UP;
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

bool_t readKey()
{
	bool_t ret;
	ret = botonPresionado; // Me hago una copia booleano que me indica si se detecto al menos un flanco negativo del botón (una pulsacion)
	botonPresionado = false; // Reinicializo
	return ret; // Devuelvo si se pulsó al menos una vez el pulsador
}
