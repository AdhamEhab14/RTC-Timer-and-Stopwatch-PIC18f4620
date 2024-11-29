/* 
 * File:   ecu_ button.c
 * Author: Adham
 *
 * Created on July 15, 2024, 6:28 PM
 */

#include "ecu_ button.h"


/**
 * @brief Initialize the assigned pin to be output
 * @param btn pointer to the button configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType button_initialize(const button_t * btn){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == btn){
        retVal = E_NOT_OK;
    }else{
        retVal = gpio_pin_direction_initialize(&(btn->button_pin));
        retVal = E_OK;
    }
}
/**
 * @brief Read the state of the button
 * @param btn pointer to the button configurations
 * @param btn_state
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType button_read_state(const button_t * btn , button_state_t *btn_state){
    Std_ReturnType retVal = E_NOT_OK;
    logic_t logic_status = GPIO_LOW;
    if((NULL == btn) || (NULL == btn_state)){
        retVal = E_NOT_OK;
    }else{
        gpio_pin_read_logic(&(btn->button_pin) , &logic_status);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection){
            if(GPIO_HIGH == logic_status){
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection){
            if(GPIO_LOW == logic_status){
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else{
            retVal = E_NOT_OK;
        }
        retVal = E_OK;
    }
    return retVal;
}