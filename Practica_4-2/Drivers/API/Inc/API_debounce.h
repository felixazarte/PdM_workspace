/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DEBOUNCE_H
#define __API_DEBOUNCE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include <stdint.h>					/* <- Standard integer library */
#include <stdbool.h>				/* <- Standar bool library*/


/* Exported types ------------------------------------------------------------*/
/* ################ My variable definitions ################ */
typedef bool bool_t;

/* ################ My function definitions ################ */
// Inicializa la máquina de estados finito del antirrebote del botón.
void debounceFSM_init();

// Actualiza la máquina de estados finito del antirrebote del botón.
void debounceFSM_update();

// Devuelve true si se detecto una pulsacion del botón (flanco negativo).
bool_t readKey();

#endif /* __API_DEBOUNCE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
