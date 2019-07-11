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
 #include <avr/interrupt.h>
 
 #include "FreeRTOS.h"
 #include "task.h"
 #include "croutine.h"
 #include "semphr.h"
 
 extern void createSwTask(void);
 extern void createSequencerTask(void);
 extern void createLedTaskOne(void);
 extern void createLedTaskTwo(void);
 extern void createLedTaskThree(void);
 extern void createLedTaskFour(void);
 extern void createLedTaskFive(void);
 extern void createLedTaskSix(void);
 extern void createLedTaskSeven(void);
 
void sysInit(void)
{
	
	/* Enable 32Mhz Internal Oscillator */
	OSC.CTRL |= OSC_RC32MEN_bm;
	/* Wait until the oscillator is stable */	 
	while( (OSC.STATUS & OSC_RC32MRDY_bm) == 0);		
	/* Set sys clock to use the 32MHz Internal Oscillator */
	_PROTECTED_WRITE(CLK_CTRL, CLK_SCLKSEL0_bm);
	/* Enable all interrupt levels */
	PMIC.CTRL |= PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
	/* Enable global interrupts */
	sei();
}


int main(void)
 {
	 sysInit();
	 createSwTask();
	 createSequencerTask();
	 createLedTaskOne();
	 createLedTaskTwo();
	 createLedTaskThree();
	 createLedTaskFour();
	 createLedTaskFive();
	 createLedTaskSix();
	 createLedTaskSeven();
	 
	 vTaskStartScheduler();
	 while (1)
	 {
	 }
 }