
/* Includes ------------------------------------------------------------------*/
#include "API_debounce.h"

static delay_t          botonDelay;
static debounceState_t  botonEstadoActual;
static bool_t           flagRaising;    // Flag si el botón se soltó.
static bool_t           flagFalling;    // Flag si el botón se presinó.

//Inicializa la maquina de estados con boton en alto, inicializaliza el pulsador
void debounceFSM_init()
{
	botonEstadoActual = BUTTON_UP;
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	delayInit(&botonDelay, TIEMPO_ANTIRREBOTE); //inicializa el retardo no bloqueante de verifiacion de la MEF
}

//Implementacion de maquina de estados, se debe checkear periodicamente
void debounceFSM_update()
{
	switch (botonEstadoActual)
	{
	case BUTTON_UP:
		if(BSP_PB_GetState(BUTTON_USER))
		{
			// Se detecto que presionaron el botón, inicio proceso antirrebote.
			botonEstadoActual = BUTTON_FALLING;
			delayRead(&botonDelay);
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
				flagFalling = true;
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
			delayRead(&botonDelay);
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
				flagRaising = true;
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

//Funciones intermedias para acceder variables internas
bool_t buttonPressed()
{
	bool_t ret1;
	ret1 = flagFalling; // Hago una copia booleano que me indica si se detecto al menos un flanco negativo del botón (una pulsacion)
	flagFalling = false; // Reinicializo
	return ret1; // Devuelvo si se pulsó al menos una vez el botón.
}

bool_t buttonReleased()
{
	bool_t ret2;
	ret2 = flagRaising; // Hago una copia booleano que me indica si se detecto al menos un flanco positivo del botón (una pulsacion)
	flagRaising = false; // Reinicializo
	return ret2; // Devuelvo si se pulsó al menos una vez el botón.
}
