/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DELAY_H
#define __API_DELAY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include <stdint.h>					/* <- Standard integer library */
#include <stdbool.h>				/* <- Standar bool library*/


/* Exported types ------------------------------------------------------------*/
/* ################ My variable definitions ################ */
typedef uint32_t tick_t;
typedef bool bool_t;
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

/* ################ My function definitions ################ */
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );


#endif /* __API_DELAY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
