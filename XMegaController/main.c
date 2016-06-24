/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2016 Pipei Sandor - All Rights Reserved
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge MA 02139,
 *   USA; either version 2 of the License, or (at your option) any later
 *   version; incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

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
	 
	 vTaskStartScheduler();
	 while (1)
	 {
	 }
 }