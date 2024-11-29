/* 
 * File:   ecu_keypad.c
 * Author: Adham
 *
 * Created on July 23, 2024, 4:41 PM
 */

#include "ecu_keypad.h"

static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
                                                                {'7' , '8' , '9' , '/'} ,
                                                                {'4' , '5' , '6' , '*'} ,
                                                                {'1' , '2' , '3' , '-'} ,
                                                                {'#' , '0' , '=' , '+'} ,
                                                            };

/**
 * @brief initialize the keypad assigned pins
 * @param pad pointer to the keypad module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t * pad){
    Std_ReturnType retVal = E_NOT_OK;
    uint8 rows_counter=0 , columns_counter=0;
    if(NULL == pad){
        retVal = E_NOT_OK;
    }
    else{
        for(rows_counter=0 ; rows_counter<KEYPAD_ROWS ; rows_counter++){
            retVal = gpio_pin_initialize(&(pad->keypad_rows_pins[rows_counter]));
        }
        for(columns_counter=0 ; columns_counter<KEYPAD_COLUMNS ; columns_counter++){
            retVal = gpio_pin_direction_initialize(&(pad->keypad_columns_pins[columns_counter]));
        }
        retVal = E_OK;
    }
    return retVal;
}
/**
 * @brief get the value of the button pressed by the user and performing the scanning algorithm
 * @param pad pointer to the keypad module configurations
 * @param value value of the button pressed by the user
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t * pad , uint8 * value){
    Std_ReturnType retVal = E_NOT_OK;
    uint8 rows_counter=0, columns_counter=0;
    uint8 counter=0;
    uint8 column_logic=0;
    if((NULL == pad) || (NULL == value)){
        retVal = E_NOT_OK;
    }
    else{
        for(rows_counter=0 ; rows_counter < KEYPAD_ROWS ; rows_counter++){
            for(counter=0 ; counter < KEYPAD_ROWS ; counter++){
                retVal = gpio_pin_write_logic(&(pad->keypad_rows_pins[counter]) , GPIO_LOW);
            }
            gpio_pin_write_logic(&(pad->keypad_rows_pins[rows_counter]) , GPIO_HIGH);
            __delay_ms(70);
            for(columns_counter=0; columns_counter < KEYPAD_COLUMNS ; columns_counter++){
                retVal = gpio_pin_read_logic(&(pad->keypad_columns_pins[columns_counter]) , &column_logic);
                if(GPIO_HIGH == column_logic){
                    *value = btn_values[rows_counter][columns_counter];
                }
            }
        }
        retVal = E_OK;
    }
    return retVal;
}
