 /*********************************************************************************
 *
 * [File Name]: Shower_Water_Monitor.c
 *
 * [Author]: Alaa Elsayed
 *
 * [Date Created]: 21 / 12 / 2021
 *
 * [Description]: Source File for System to measure 1) Volume of Water
 * 													2) Cost of the Water
 * 													3) Flow Rate
 * 				  Using Flow Sensor ( YF-S201 ).
 *
 *********************************************************************************/


#include "Shower_Water_Monitor.h"


/* External INT0 Interrupt Service Routine */
ISR(INT0_vect)
{
	/* Increment the counter of the pulses */
	g_pulses++;
}


/* External INT0 Enable and Configuration Function */
void INT0_Init_Sensor(void)
{
	/* Configure INT0/PD2 as Input Pin */
	GPIO_setupPinDirection(Sensor_PORT_ID, Sensor_PIN_ID, PIN_INPUT);

	/* Trigger INT0 with the Raising Edge */
	MCUCR |= ( 1 << ISC00 );
	MCUCR |= ( 1 << ISC01 );

	/* Enable external interrupt pin INT0 */
	GICR  |= ( 1 << INT0 );
} /* End INT0_Init */



/* External INT1 Interrupt Service Routine */
ISR (INT1_vect)
{
	/* If the water is running, the button should toggle the mode */
	if ( g_water_status == RUNNING )
	{
		g_mode = (g_mode) ^ (1); /* Toggle the current mode */
		g_mode_changed = 1; 	 /* Raise a flag indicate that the mode has changed */
	}
	else /* If the water is stopped, the button should clears the counters */
	{
		g_pulses = 0;		 /* Clear the total number of pulses */
		g_last_pulses = 0;	 /* Clear the last total number of pulses */
	}
}


/* External INT1 Enable and Configuration function */
void INT1_Init_Button(void)
{
	/* Configure INT1/PD3 as Input Pin */
	GPIO_setupPinDirection(Button_PORT_ID, Button_PIN_ID, PIN_INPUT);

	/* Trigger INT1 with the Raising Edge */
	MCUCR |= ( 1 << ISC10 );
	MCUCR |= ( 1 << ISC11 );

	/* Enable external interrupt pin INT1 */
	GICR  |= ( 1 << INT1 );
} /* End INT1_Init */



/* function main begins program execution */
int main(void)
{
	/********** Initialization Code **********/

	float32 volume; /* Variable to store the total volume of the water */
	float32 cost; /* Variable to store the total cost of the water */
	float32 rate; /* Variable to store the total rate of the water */

	Buzzer_Init(); /* Initialize the Buzzer */
	LCD_init(); /* Initialize the LCD */

	SREG |= ( 1 << 7 ); /* Enable interrupts by setting I-Bit */

	INT0_Init_Sensor(); /* Enable Sensor Interrupt */
	INT1_Init_Button(); /* Enable Button Interrupt */

	LCD_displayString("Total:       L"); /* Represent the total volume of the water */


	/* Super Loop */
	for(;;)
	{
		/********** Application Code **********/

		/* If the numbers of the screen became zero avoid overwrite */
		if(g_pulses == 0 && g_last_pulses == 0)
		{
			LCD_moveCursor(0, 10);
			LCD_displayString("  ");
		}

		/* If the mode has changed, Update the text label */
		do
		{
			LCD_moveCursor(1, 0); /* Move the cursor to the second line */

			if ( g_mode == Rate_Mode ) /* If the new mode is on rate mode */
			{
				LCD_displayString("Rate:        L/s"); 	/* Represent the flow rate of the water text label */
			}
			else /* If the new mode is on cost mode */
			{
				LCD_displayString("Cost:        Pt."); 	/* Represent the cost of the water text label */
			}

			g_mode_changed = 0; /* Reset the flag indicating that the mode has changed */
		} while( g_mode_changed == 1 );

		volume = g_pulses / 450.00; 		/* Calculate the total volume of the water */

		LCD_moveCursor( 0, 7 ); 		/* Move the cursor to the first line to represent volume */
		LCD_FloatToString(volume); 	/* Show volume in its proper location */

		/* If the Person exceeds the average amount of water during shower ( 20 Gallons ) */
		if (volume >= 55.00 )
		{
			Buzzer_On(); 		 /* Turn ON the buzzer to alarm him to stop the use of water */
		}
		else
		{
			Buzzer_Off();		/* If not Keep the buzzer OFF */
		}

		LCD_moveCursor( 1, 7 );			/* Move the cursor to the second line to represent the other value */

		if ( g_mode == Rate_Mode ) /* If the new mode is on rate mode */
		{
			rate = 1000.00 * ( g_pulses - g_last_pulses ) / 450.00 / REFRESH_RATE; 			/* Calculate the flow rate of running water */
			LCD_FloatToString(rate);									/* Show flow rate in its proper location */
		}
		else /* If the new mode is on cost mode */
		{
			cost = volume * COST_PER_LITER;		/* Calculate the total cost of the water */
			LCD_FloatToString(cost);			/* Show cost of the water in its proper location */
		}

		/*
		 * Compare last total number of pulses with the current number of pulses
		 * 				-> if they are the same then the water is stopped
		 * 				-> if there is change then the water is running
		 */
		if( g_last_pulses == g_pulses )
		{
			g_water_status = STOPPED;
		}
		else
		{
			g_water_status = RUNNING;
		}

		g_last_pulses = g_pulses; /* Set the last total number of pulses to the current number of pulses */

		_delay_ms(REFRESH_RATE);  /* Delay 200 ms before each update */
	} /* End Super loop */

} /* End Main Function */
