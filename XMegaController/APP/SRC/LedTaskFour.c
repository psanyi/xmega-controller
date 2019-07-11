/*
 * LedTaskFour.c
 *
 * Created: 6/20/2019 18:05:29
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

void LedTaskFour(void *pvParameters)
{
	
	const TickType_t xDelay100ms = 100 / portTICK_RATE_MS;
	
	for(;;)
	{
		xSemaphoreTake(ledMatrix[3], portMAX_DELAY);
		
		portENTER_CRITICAL();
		PORTD.OUTTGL = (1 << 3);
		portEXIT_CRITICAL();
		
		vTaskDelay(xDelay100ms);
		
		portENTER_CRITICAL();
		PORTD.OUTTGL = (1 << 3);
		portEXIT_CRITICAL();
	}
}

void createLedTaskFour(void)
{
	/* Set port direction to output */
	PORTD.OUT = 0xFF;
	PORTD.DIR = 0xFF;
	
	xTaskCreate( LedTaskFour, "ledTsk4", 100, NULL, 3, NULL);
	
}
