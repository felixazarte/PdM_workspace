/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DEBOUNCE_H
#define __API_DEBOUNCE_H


#include "stdbool.h"                /* <- Standar bool library*/
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "API_delay.h"

#define TIEMPO_ANTIRREBOTE	40   // FSM_UPDATE_PERIOD 40

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;

typedef bool bool_t;

/* ################ My function definitions ################ */
// Inicializa la máquina de estados finito del antirrebote del botón.
void debounceFSM_init();
// Actualiza la máquina de estados finito del antirrebote del botón.
void debounceFSM_update();
// Ejecuta las acciones correspondientes cuando se presiona el botón, flanco descendente.
bool_t buttonPressed();
// Ejecuta las acciones correspondientes cuando se suelta el botón, flanco ascendente.
bool_t buttonReleased();




#endif /* __API_DEBOUNCE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
