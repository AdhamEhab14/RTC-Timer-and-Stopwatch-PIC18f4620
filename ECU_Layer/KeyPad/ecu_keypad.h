/* 
 * File:   ecu_keypad.h
 * Author: Adham
 *
 * Created on July 23, 2024, 4:41 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/***************************************Includes***************************************/

#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/***********************************Macro Declarations**********************************/

#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 4

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[KEYPAD_COLUMNS];
}keypad_t;

/***********************************Function Declarations*******************************/

/**
 * @brief initialize the keypad assigned pins
 * @param pad pointer to the keypad module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t * pad);
/**
 * @brief get the value of the button pressed by the user and performing the scanning algorithm
 * @param pad pointer to the keypad module configurations
 * @param value value of the button pressed by the user
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t * pad , uint8 * value);

#endif	/* ECU_KEYPAD_H */

