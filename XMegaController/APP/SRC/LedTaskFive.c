/*
 * LedTaskFive.c
 *
 * Created: 6/20/2019 18:05:48
 *  Author: psany
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"
#include "semphr.h"
#include "queue.h"

extern SemaphoreHandle_t ledMatrix[];

void LedTaskFive(void *pvParameters)
{
	
	const TickType_t xDelay100ms = 100 / portTICK_RATE_MS;
	
	for(;;)
	{
		xSemaphoreTake(ledMatrix[4], portMAX_DELAY);
		
		portENTER_CRITICAL();
		PORTD.OUTTGL = (1 << 4);;
		portEXIT_CRITICAL();
		
		vTaskDelay(xDelay100ms);
		
		portENTER_CRITICAL();
		PORTD.OUTTGL = (1 << 4);;
		portEXIT_CRITICAL();
	}
}

void createLedTaskFive(void)
{
	/* Set port direction to output */
	PORTD.OUT = 0xFF;
	PORTD.DIR = 0xFF;
	
	xTaskCreate( LedTaskFive, "ledTsk5", 100, NULL, 3, NULL);
	
}
