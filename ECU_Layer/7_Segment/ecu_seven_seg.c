/* 
 * File:   ecu_seven_seg.c
 * Author: Adham
 *
 * Created on July 21, 2024, 11:22 PM
 */

#include "ecu_seven_seg.h"


/**
 * @brief initialize the assigned pins to be OUTPUT
 * @param segment pointer to the seven segment module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType seven_segment_initialize(const segment_t *segment){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == segment){
        retVal = E_NOT_OK;
    }
    else{
        retVal = gpio_pin_initialize(&(segment->segment_pin[SEGMENT_PIN0]));
        retVal = gpio_pin_initialize(&(segment->segment_pin[SEGMENT_PIN1]));
        retVal = gpio_pin_initialize(&(segment->segment_pin[SEGMENT_PIN2]));
        retVal = gpio_pin_initialize(&(segment->segment_pin[SEGMENT_PIN3]));
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief write a number between 0 ~ 9 to the segment
 * @param segment pointer to the seven segment module configurations
 * @param number
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *segment , uint8 number){
    Std_ReturnType retVal = E_NOT_OK;
    if((NULL == segment) || (number > 9)){
        retVal = E_NOT_OK;
    }
    else{
        retVal = gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_PIN0]) , number & 0x01);
        retVal = gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_PIN1]) , (number>>1) & 0x01);
        retVal = gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_PIN2]) , (number>>2) & 0x01);
        retVal = gpio_pin_write_logic(&(segment->segment_pin[SEGMENT_PIN3]) , (number>>3) & 0x01);
        retVal = E_OK;
    }
    return retVal;
}