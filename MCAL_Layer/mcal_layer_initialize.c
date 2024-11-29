/* 
 * File:   mcal_layer_initialize.c
 * Author: Adham
 *
 * Created on August 18, 2024, 3:19 PM
 */

#include "mcal_layer_initialize.h"


extern void TIMER0_IneterruptHandler(void);
extern void INT0_ResetIneterruptHandler(void);
extern void INT1_CountUpIneterruptHandler(void);
extern void INT2_CountDownIneterruptHandler(void);
extern void RB0_PauseIneterruptHandler(void);
extern void RB0_ResumeIneterruptHandler(void);
extern void RB1_ClockIneterruptHandler(void);

/*---------------------------- Timer -----------------------------*/
timer0_t timer = {
    .TMR0_InterruptHandler = TIMER0_IneterruptHandler,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_32,
    .timer0_mode = TIMER0_TIMER_MODE,
    .timer0_preload_value = 3036,
    .timer0_register_size = TIMER0_16_BIT_REGISTER_MODE
};
/*---------------------------- Reset -----------------------------*/
interrupt_INTx_t reset_int = {
    .EXT_InterruptHandler = INT0_ResetIneterruptHandler,
    .source = INTERRUPT_EXTERNAL_INT0,
    .edge = INTERRUPT_RISING_EDGE,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.logic = GPIO_LOW
};
/*---------------------------- Stopwatch & timer modes -----------------------------*/
interrupt_INTx_t count_up_int = {
    .EXT_InterruptHandler = INT1_CountUpIneterruptHandler,
    .source = INTERRUPT_EXTERNAL_INT1,
    .edge = INTERRUPT_RISING_EDGE,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN1,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.logic = GPIO_LOW
};
interrupt_INTx_t count_down_int = {
    .EXT_InterruptHandler = INT2_CountDownIneterruptHandler,
    .source = INTERRUPT_EXTERNAL_INT2,
    .edge = INTERRUPT_RISING_EDGE,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN2,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.logic = GPIO_LOW
};
/*---------------------------- Pause & Resume -----------------------------*/
interrupt_RBx_t pause_resume_int = {
    .EXT_InterruptHandler_LOW = RB0_PauseIneterruptHandler,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN4,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.logic = GPIO_LOW
};
/*---------------------------- Clock mode -----------------------------*/
interrupt_RBx_t clock_mode_int = {
    .EXT_InterruptHandler_LOW = RB1_ClockIneterruptHandler,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN5,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
    .mcu_pin.logic = GPIO_LOW
};
/*---------------------------- Buzzer -----------------------------*/
pin_config_t buzzer = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN6,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};


void mcal_layer_initialize(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    
    retVal = Timer0_Init(&timer);
    retVal = Interrupt_INTx_Init(&reset_int);
    retVal = Interrupt_INTx_Init(&count_up_int);
    retVal = Interrupt_INTx_Init(&count_down_int);
    retVal = Interrupt_RBx_Init(&pause_resume_int);
    retVal = Interrupt_RBx_Init(&clock_mode_int);
    retVal = gpio_pin_initialize(&buzzer);

}