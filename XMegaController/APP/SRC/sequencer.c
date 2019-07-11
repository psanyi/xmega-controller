/*
 * sequencer.c
 *
 * Created: 6/19/2019 20:43:28
 *  Author: Pipei Sandor
 */ 
 #include <avr/io.h>
 #include <avr/interrupt.h>
 
 #include "FreeRTOS.h"
 #include "task.h"
 #include "croutine.h"
 #include "semphr.h"
 #include "timers.h"
 
 #define MAXLEDS	8
SemaphoreHandle_t ledMatrix[MAXLEDS];

static UBaseType_t seqTaskPriority = 2;
static uint16_t seqStackDepth = 500;
static TimerHandle_t seqTimer;
static TickType_t seqSpeed = 500;
static uint8_t ledCounter = 0;

extern QueueHandle_t xSwQueue;

void seqTimerCallback(TimerHandle_t xTimer)
{
	if(ledCounter < MAXLEDS-1)
	{
		xSemaphoreGive(ledMatrix[ledCounter]);
		ledCounter++;
	}
	else
	{
		ledCounter = 0;
	}
}

void seqTask(void *pvParameters)
{
	uint8_t swID;
	uint8_t seqState = 0;
	portBASE_TYPE xStatus;
	
	for(;;)
	{
		xStatus = xQueueReceive(xSwQueue, &swID, portMAX_DELAY);
		
		if(xStatus == pdPASS)
		{
			switch(swID)
			{
				case 1: 
				{
					if(seqState == 0)
					{
						xTimerStart(seqTimer, 0);
						seqState = 1;
					}
					else
					{
						xTimerStop(seqTimer, 0);
						seqState = 0;		
					}
					break;		
				}
				case 2:
				{
					seqSpeed += 50;
					xTimerChangePeriod(seqTimer,seqSpeed / portTICK_RATE_MS, 0 );
					break;
				}
				case 4: 
				{
					if(seqSpeed > 50)
					{
						seqSpeed -= 50;
						xTimerChangePeriod(seqTimer,seqSpeed / portTICK_RATE_MS, 0 );
					}
					break;
				}
				default:break;
				
			}
		}
		else
		{
			
		}
	}
}

void createSequencerTask(void)
{
	uint8_t i;
	seqTimer = xTimerCreate("seqTim",seqSpeed / portTICK_RATE_MS, pdTRUE, 0, seqTimerCallback);
	if(seqTimer != NULL)
	{
		for(i=0; i<MAXLEDS; i++)
		{
			ledMatrix[i] = xSemaphoreCreateBinary();
		}
		xTaskCreate( seqTask, "seqTask", seqStackDepth, NULL, seqTaskPriority, NULL);
	}
	
}