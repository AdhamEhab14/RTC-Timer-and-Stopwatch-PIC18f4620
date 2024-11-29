/* 
 * File:   ecu_ button.h
 * Author: Adham
 *
 * Created on July 15, 2024, 6:28 PM
 */

#ifndef ECU__BUTTON_H
#define	ECU__BUTTON_H

/****************************************Includes***************************************/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/***********************************Macro Declarations**********************************/

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

/***********************************Function Declarations*******************************/

/**
 * @brief Initialize the assigned pin to be output
 * @param btn pointer to the button configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType button_initialize(const button_t * btn);
/**
 * @brief Read the state of the button
 * @param btn pointer to the button configurations
 * @param btn_state
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType button_read_state(const button_t * btn , button_state_t *btn_state);

#endif	/* ECU__BUTTON_H */

