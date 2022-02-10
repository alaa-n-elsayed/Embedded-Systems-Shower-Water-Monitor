 /*********************************************************************************
 *
 * [File Name]: Shower_Water_Monitor.h
 *
 * [Author]: Alaa Elsayed
 *
 * [Date Created]: 21 / 12 / 2021
 *
 * [Description]: Header File for System to measure 1) Volume of Water
 * 													2) Cost of the Water
 * 													3) Flow Rate
 * 				  Using Flow Sensor ( YF-S201 ).
 *
 *********************************************************************************/

#ifndef SHOWER_WATER_MONITOR_H_
#define SHOWER_WATER_MONITOR_H_

#include "micro_config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lcd.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include "buzzer.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Button HW Port and Pin Ids */
#define Button_PORT_ID                 PORTD_ID
#define Button_PIN_ID                  PIN3_ID

/* Sensor HW Port and Pin Ids */
#define Sensor_PORT_ID                 PORTD_ID
#define Sensor_PIN_ID                  PIN2_ID


/* Predefined values to track the water status */
#define RUNNING		1
#define STOPPED		0

/* Predefined values to track the current active mode */
#define Rate_Mode	    1
#define Cost_Mode		0

/* Predefined constant values to be further used */
#define REFRESH_RATE		200.0
#define COST_PER_LITER		0.066

/*******************************************************************************
 *                              Global Variable                                *
 *******************************************************************************/

volatile uint32 g_pulses = 0; 		/* Global Variable to store the number of pulses generated from the flow sensor */
volatile uint32 g_last_pulses = 0; 	/* Global Variable to store the last number of pulses generated from the flow sensor */

volatile uint8 g_mode = 0; 			/* Global Variable to store the mode of the screen */
volatile uint8 g_mode_changed = 0; 	/* Global Variable to store if the mode of the screen has changed */

uint8 g_water_status; 		/* Global Variable to store the status of the water */


#endif /* SHOWER_WATER_MONITOR_H_ */
