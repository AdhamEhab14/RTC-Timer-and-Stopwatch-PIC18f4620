/* 
 * File:   ecu_layer_initialize.c
 * Author: Adham
 *
 * Created on July 23, 2024, 5:28 PM
 */

#include "ecu_layer_initialize.h"

/*---------------------------- Seven Segment -----------------------------*/
segment_t seven_segment = {
    .segment_pin[0].port = PORTA_INDEX,
    .segment_pin[0].pin = GPIO_PIN0,
    .segment_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[0].logic = GPIO_LOW,
    .segment_pin[1].port = PORTA_INDEX,
    .segment_pin[1].pin = GPIO_PIN1,
    .segment_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[1].logic = GPIO_LOW,
    .segment_pin[2].port = PORTA_INDEX,
    .segment_pin[2].pin = GPIO_PIN2,
    .segment_pin[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[2].logic = GPIO_LOW,
    .segment_pin[3].port = PORTA_INDEX,
    .segment_pin[3].pin = GPIO_PIN3,
    .segment_pin[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pin[3].logic = GPIO_LOW,
    .segment_type = SEGMENT_COMMON_ANODE
};
/*---------------------------- Seven Segment Enables -----------------------------*/
pin_config_t seg_enable_1 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};
pin_config_t seg_enable_2 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};
pin_config_t seg_enable_3 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};
pin_config_t seg_enable_4 = {
    .port = PORTB_INDEX,
    .pin = GPIO_PIN6,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};
pin_config_t seg_enable_5 = {
    .port = PORTB_INDEX,
    .pin = GPIO_PIN7,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};
pin_config_t seg_enable_6 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN5,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};
/*---------------------------- Modes LEDs -----------------------------*/
led_t stopwatch_led = {
  .port = PORTA_INDEX,
  .pin = GPIO_PIN4,
  .led_status = LED_OFF,
};
led_t timer_led = {
  .port = PORTA_INDEX,
  .pin = GPIO_PIN5,
  .led_status = LED_OFF,
};
led_t clock_led = {
  .port = PORTB_INDEX,
  .pin = GPIO_PIN3,
  .led_status = LED_OFF,
};
/*-------------------------------- Key Pad -------------------------------------*/
keypad_t keypad = {
    .keypad_rows_pins[0].port = PORTD_INDEX,
    .keypad_rows_pins[0].pin = GPIO_PIN0,
    .keypad_rows_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[0].logic = GPIO_LOW,
    .keypad_rows_pins[1].port = PORTD_INDEX,
    .keypad_rows_pins[1].pin = GPIO_PIN1,
    .keypad_rows_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[1].logic = GPIO_LOW,
    .keypad_rows_pins[2].port = PORTD_INDEX,
    .keypad_rows_pins[2].pin = GPIO_PIN2,
    .keypad_rows_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[2].logic = GPIO_LOW,
    .keypad_rows_pins[3].port = PORTD_INDEX,
    .keypad_rows_pins[3].pin = GPIO_PIN3,
    .keypad_rows_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[3].logic = GPIO_LOW,
    
    .keypad_columns_pins[0].port = PORTD_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[1].port = PORTD_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[2].port = PORTD_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[3].port = PORTD_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,
};
/*---------------------------- Buzzer LED -----------------------------*/
led_t buzzer_led = {
  .port = PORTC_INDEX,
  .pin = GPIO_PIN7,
  .led_status = LED_OFF,
};


void ecu_layer_initialize(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    
    retVal = seven_segment_initialize(&seven_segment);
    retVal = gpio_pin_initialize(&seg_enable_1);
    retVal = gpio_pin_initialize(&seg_enable_2);
    retVal = gpio_pin_initialize(&seg_enable_3);
    retVal = gpio_pin_initialize(&seg_enable_4);
    retVal = gpio_pin_initialize(&seg_enable_5);
    retVal = gpio_pin_initialize(&seg_enable_6);
    
    retVal = led_initialize(&stopwatch_led);
    retVal = led_initialize(&timer_led);
    retVal = led_initialize(&clock_led);
    retVal = led_initialize(&buzzer_led);
    
    retVal = keypad_initialize(&keypad);
    
}

