/*
 * switches.c
 *
 * This task reads the switches debounces them and put their
 * code to a queue
 * 
 * 
 * Created: 6/18/2019 21:20:44
 * Author: Pipei Sandor
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"
#include "semphr.h"
#include "queue.h"

static SemaphoreHandle_t xIsrSwSemaphore;
static UBaseType_t uxSwQueueLength = 2;
static UBaseType_t swTaskPriority = 3;
static uint16_t swStackDepth = 200;

QueueHandle_t xSwQueue;

#define SWMASK		0x07
#define SWMASK_N	0

ISR(PORTA_INT0_vect)
{
	BaseType_t xHigherPriorityTaskWoken;
	
	xHigherPriorityTaskWoken = pdFALSE;
	
	portENTER_CRITICAL();
	/* Disable port interrupt */
	PORTA.INT0MASK = SWMASK_N;
	portEXIT_CRITICAL();
	
	xSemaphoreGiveFromISR(xIsrSwSemaphore, &xHigherPriorityTaskWoken);
	
}

void swTask(void *pvParameters)
{
	
	const TickType_t xDelay100ms = 100 / portTICK_RATE_MS;
	const TickType_t xDelay500ms = 500 / portTICK_RATE_MS;
	uint8_t swID = 0;
	portBASE_TYPE	xSwQueueStatus;
	
	for(;;)
	{
		/*Wait for Isr */
		xSemaphoreTake(xIsrSwSemaphore, portMAX_DELAY);
		
		/* Wait until switch settles (about 100 ms) */
		vTaskDelay(xDelay100ms);
		
		/* Enter critical section */
		portENTER_CRITICAL();
		while( (swID = (~(PORTA.IN))) & SWMASK)
		{
			
			portEXIT_CRITICAL();
			/* Get the switch id and put on the queue */
			xSwQueueStatus = xQueueSendToBack(xSwQueue,&swID,0);
			/* Check if queue is empty */ 
			if(xSwQueueStatus != pdPASS )
			{
				/* Queue is full */
				break;
			}
			/* A small delay for increment */
			vTaskDelay(xDelay500ms);
			/* Critical section end */
			portENTER_CRITICAL();
		}		
		/* Re enable interrupts */
		PORTA.INT0MASK = SWMASK;
		/* Critical section end */
		portEXIT_CRITICAL();
		/* Let another task run */
		taskYIELD();
	}
}

void createSwTask(void)
{
	/* Set port direction to input */
	PORTA.DIR = 0;
	/* Initialize port interrupt (falling edge) for switches */
	PORTCFG.MPCMASK = 0xFF; /* Set multiple pins once */
	PORTA.PIN0CTRL = PORT_ISC_FALLING_gc;
	/* Enable interrupt on all port pins */
	PORTA.INT0MASK = 0xFF;
	PORTA.INTCTRL = 0x03;
	
	xIsrSwSemaphore = xSemaphoreCreateBinary();
	xSwQueue = xQueueCreate(uxSwQueueLength, sizeof(uint8_t));
	xTaskCreate( swTask, "swTask", swStackDepth, NULL, swTaskPriority, NULL);
	
}

