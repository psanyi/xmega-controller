/*
 * XMegaController.c
 *
 * Created: 6/22/2016 21:06:21
 * Author : Pipei Sandor
 */ 

 #include <avr/io.h>
 #include "FreeRTOS.h"
 #include "task.h"
 #include "croutine.h"

 void TestTaskFunction1(void *pvParameters)
 {
	 for(;;)
	 {

	 }
	 vTaskDelete(NULL);
 }

 void TestTaskFunction2(void *pvParameters)
 {
	 for(;;)
	 {

	 }
	 vTaskDelete(NULL);
 }
 int main(void)
 {
	 xTaskCreate(TestTaskFunction1, "Task_1",1000, NULL,1,NULL);
	 xTaskCreate(TestTaskFunction2, "Task_2",1000, NULL,1,NULL);
	 /* Replace with your application code */
	 vTaskStartScheduler();
	 while (1)
	 {
	 }
 }