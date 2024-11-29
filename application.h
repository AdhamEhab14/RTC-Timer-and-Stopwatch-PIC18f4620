/* 
 * File:   application.h
 * Author: Adham
 *
 * Created on July 6, 2024, 6:36 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/***************************************Includes***************************************/

#include "ECU_Layer/ecu_layer_initialize.h"
#include "MCAL_Layer/mcal_layer_initialize.h"
#include <builtins.h> 

/***********************************Macro Declarations**********************************/

#define INPUT_TIMER_MODE     0
#define START_TIMER_MODE     4
#define STOPWATCH_MODE       1
#define CLOCK_MODE           2
#define OFF_STATE            3

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

/*********************************** ECU Externs *******************************/

extern segment_t seven_segment;

extern pin_config_t seg_enable_1;
extern pin_config_t seg_enable_2;
extern pin_config_t seg_enable_3;
extern pin_config_t seg_enable_4;
extern pin_config_t seg_enable_5;
extern pin_config_t seg_enable_6;

extern led_t stopwatch_led;
extern led_t timer_led;
extern led_t clock_led;
extern led_t buzzer_led;

extern button_t reset_btn;
extern button_t pause_resume_btn;

extern keypad_t keypad;

/*********************************** MCAL Externs *******************************/

extern timer0_t timer0_timer;

extern pin_config_t buzzer;

/***********************************Function Declarations*******************************/

void application_initialize(void);

#endif	/* APPLICATION_H */

