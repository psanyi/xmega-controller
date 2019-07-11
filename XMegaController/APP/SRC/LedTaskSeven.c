/*
 * LedTaskSeven.c
 *
 * Created: 6/20/2019 18:07:24
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

void LedTaskSeven(void *pvParameters)
{
	
	const TickType_t xDelay100ms = 100 / portTICK_RATE_MS;
	
	for(;;)
	{
		xSemaphoreTake(ledMatrix[6], portMAX_DELAY);
		
		portENTER_CRITICAL();
		PORTD.OUTTGL = (1 << 6);
		portEXIT_CRITICAL();
		
		vTaskDelay(xDelay100ms);
		
		portENTER_CRITICAL();
		PORTD.OUTTGL = (1 << 6);
		portEXIT_CRITICAL();
	}
}

void createLedTaskSeven(void)
{
	/* Set port direction to output */
	PORTD.OUT = 0xFF;
	PORTD.DIR = 0xFF;
	
	xTaskCreate( LedTaskSeven, "ledTsk6", 100, NULL, 3, NULL);
	
}