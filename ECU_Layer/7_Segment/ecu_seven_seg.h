/* 
 * File:   ecu_seven_seg.h
 * Author: Adham
 *
 * Created on July 21, 2024, 11:22 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/***************************************Includes***************************************/

#include "ecu_seven_seg_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/***********************************Macro Declarations**********************************/

#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE        
}segment_types_t;

typedef struct{
    pin_config_t segment_pin[4];
    segment_types_t segment_type;
}segment_t;

/***********************************Function Declarations*******************************/

/**
 * @brief initialize the assigned pins to be OUTPUT
 * @param segment pointer to the seven segment module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType seven_segment_initialize(const segment_t *segment);
/**
 * @brief write a number between 0 ~ 9 to the segment
 * @param segment pointer to the seven segment module configurations
 * @param number
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *segment , uint8 number);

#endif	/* ECU_SEVEN_SEG_H */

