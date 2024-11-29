/* 
 * File:   hal_timer0.h
 * Author: Adham
 *
 * Created on August 23, 2024, 8:22 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/***************************************Includes***************************************/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"

/***********************************Macro Declarations**********************************/

#define TIMER0_PRESCALER_ENABLE_CFG     1
#define TIMER0_PRESCALER_DISABLE_CFG    0

#define TIMER0_RISING_EDGE_CFG          0
#define TIMER0_FALLING_EDGE_CFG         1

#define TIMER0_TIMER_MODE               1
#define TIMER0_COUNTER_MODE             0

#define TIMER0_8_BIT_REGISTER_MODE      1
#define TIMER0_16_BIT_REGISTER_MODE     0

/******************************Macro Function Declarations******************************/

/* Enable Timer0 Pre-scaler */
#define TIMER0_PRESCALER_ENABLE() (T0CONbits.PSA = 0)
/* Disable Timer0 Pre-scaler */
#define TIMER0_PRESCALER_DISABLE() (T0CONbits.PSA = 1)

/* Timer0 Rising Edge Enable */
#define TIMER0_RISING_EDGE_ENABLE() (T0CONbits.T0SE = 0)
/* Timer0 Falling Edge Enable */
#define TIMER0_FALLING_EDGE_ENABLE() (T0CONbits.T0SE = 1)

/* Initialize Timer0 in timer mode */
#define TIMER0_TIMER_MODE_ENABLE() (T0CONbits.T0CS = 0)
/* Initialize Timer0 in counter mode */
#define TIMER0_COUNTER_MODE_ENABLE() (T0CONbits.T0CS = 1)

/* Initialize Timer0 as 8-bit timer */
#define TIMER0_8_BIT_REGISTER_MODE_ENABLE() (T0CONbits.T08BIT = 1)
/* Initialize Timer0 as 16-bit timer */
#define TIMER0_16_BIT_REGISTER_MODE_ENABLE() (T0CONbits.T08BIT = 0)

/* Enable Timer0 module */
#define TIMER0_MODULE_ENABLE() (T0CONbits.TMR0ON = 1)
/* Disable Timer0 module */
#define TIMER0_MODULE_DISABLE() (T0CONbits.TMR0ON = 0)

/***********************************Datatype Declarations*******************************/

typedef enum{
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,        
    TIMER0_PRESCALER_DIV_BY_8,        
    TIMER0_PRESCALER_DIV_BY_16,        
    TIMER0_PRESCALER_DIV_BY_32,       
    TIMER0_PRESCALER_DIV_BY_64,       
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256       
}timer0_prescaler_select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TMR0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    timer0_prescaler_select_t prescaler_value;
    uint16 timer0_preload_value;
    uint8 prescaler_enable : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_register_size : 1;
    uint8 : 4;
    
}timer0_t;

/***********************************Function Declarations*******************************/

/**
 * @brief Initialize Timer0
 * @param timer0 pointer to the timer0 module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Timer0_Init(const timer0_t *timer0);
/**
 * @brief DeInitialize Timer0
 * @param timer0 pointer to the timer0 module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Timer0_DeInit(const timer0_t *timer0);
/**
 * @brief Write value in Timer0
 * @param timer0 pointer to the timer0 module configurations
 * @param value
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Timer0_Write_value(const timer0_t *timer0 , uint16 value);
/**
 * @brief Read value from Timer0
 * @param timer0 pointer to the timer0 module configurations
 * @param value
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Timer0_Read_value(const timer0_t *timer0 , uint16 *value);


#endif	/* HAL_TIMER0_H */

