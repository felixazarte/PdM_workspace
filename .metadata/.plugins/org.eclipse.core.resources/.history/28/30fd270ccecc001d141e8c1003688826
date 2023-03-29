
/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"
#include "stm32f4xx_hal.h"
/* Private functions ---------------------------------------------------------*/

/* Implementation of non-blocking delay functions */
void delayInit( delay_t * delay, tick_t duration )
{
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead( delay_t * delay )
{
	if(!delay->running)
	{
		delay->running = true;
		delay->startTime = HAL_GetTick();
	}
	else
	{
		if(HAL_GetTick() - delay->startTime >= delay->duration)
		{
			delay->running = false;
			return true;
		}
	}
	return false;
}

void delayWrite( delay_t * delay, tick_t duration )
{
	delay->duration = duration;
}
