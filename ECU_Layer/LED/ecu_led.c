/* 
 * File:   ecu_led.c
 * Author: Adham
 *
 * Created on July 6, 2024, 6:01 PM
 */

#include "ecu_led.h"

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the led off
 * @param led pointer to the led module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t * led){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == led){
        retVal = E_NOT_OK;
    }else{
        pin_config_t pin_obj = {.port = led->port,
                                .pin = led->pin,
                                .direction = GPIO_DIRECTION_OUTPUT,
                                .logic = led->led_status
                                };
        gpio_pin_initialize(&pin_obj);
        retVal = E_OK;
    }
    return retVal;
}
/**
 * @brief turn the led on
 * @param led pointer to the led module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t * led){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == led){
        retVal = E_NOT_OK;
    }else{
        pin_config_t pin_obj = {.port = led->port,
                                .pin = led->pin,
                                .direction = GPIO_DIRECTION_OUTPUT,
                                .logic = led->led_status
                                };
        gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
        retVal = E_OK;
    }
    return retVal;
}
/**
 * @brief turn the led off
 * @param led pointer to the led module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t * led){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == led){
        retVal = E_NOT_OK;
    }else{
        pin_config_t pin_obj = {.port = led->port,
                                .pin = led->pin,
                                .direction = GPIO_DIRECTION_OUTPUT,
                                .logic = led->led_status
                                };
        gpio_pin_write_logic(&pin_obj , GPIO_LOW);
        retVal = E_OK;
    }
    return retVal;
}
/**
 * @brief toggle the led
 * @param led pointer to the led module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType led_toggle(const led_t * led){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == led){
        retVal = E_NOT_OK;
    }else{
        pin_config_t pin_obj = {.port = led->port,
                                .pin = led->pin,
                                .direction = GPIO_DIRECTION_OUTPUT,
                                .logic = led->led_status
                                };
        gpio_pin_toggle_logic(&pin_obj);
        retVal = E_OK;
    }
    return retVal;
}   