/* 
 * File:   hal_timer0.c
 * Author: Adham
 *
 * Created on August 23, 2024, 8:22 PM
 */

#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* TMR0_InterruptHandler)(void) = NULL;
#endif

static volatile uint16 timer0_preload = 0;

static inline void Timer0_Prescaler_Config(const timer0_t *timer0);
static inline void Timer0_Mode_Select(const timer0_t *timer0);
static inline void Timer0_Register_Size_Config(const timer0_t *timer0);


/**
 * @brief Initialize Timer0
 * @param timer0 pointer to the timer0 module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Timer0_Init(const timer0_t *timer0){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == timer0){
        retVal = E_NOT_OK;
    }
    else{
        /* Disable Timer0 */
        TIMER0_MODULE_DISABLE();
        /* Configure Pre-scaler */
        Timer0_Prescaler_Config(timer0);
        /* Configure the timer Mode */
        Timer0_Mode_Select(timer0);
        /* Configure the timer register size */
        Timer0_Register_Size_Config(timer0);
        /* Configure Pre-Loaded Value */
        TMR0H = (timer0->timer0_preload_value) >> 8;
        TMR0L = (uint8)(timer0->timer0_preload_value);
        timer0_preload = timer0->timer0_preload_value;
        /* Configure the interrupts */
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptEnable();    /* Enable Timer0 module interrupt */
        TIMER0_InterruptFlagClear(); /* Clear flag */
        TMR0_InterruptHandler = timer0->TMR0_InterruptHandler;
        /* Check priority & Enable Timer0 module interrupt */
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer0->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == timer0->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet();
        }
        #else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        #endif
#endif
        /* Enable Timer0*/
        TIMER0_MODULE_ENABLE();
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief DeInitialize Timer0
 * @param timer0 pointer to the timer0 module configurations
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Timer0_DeInit(const timer0_t *timer0){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == timer0){
        retVal = E_NOT_OK;
    }
    else{
        /* Disable Timer0 */
        TIMER0_MODULE_DISABLE();
        /* Configure the interrupt */
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
#endif
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief Write value in Timer0
 * @param timer0 pointer to the timer0 module configurations
 * @param value
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Timer0_Write_value(const timer0_t *timer0 , uint16 value){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == timer0){
        retVal = E_NOT_OK;
    }
    else{
        TMR0H = (value) >> 8;
        TMR0L = (uint8)(value);
        retVal = E_OK;
    }
    return retVal;
}

/**
 * @brief Read value from Timer0
 * @param timer0 pointer to the timer0 module configurations
 * @param value
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Timer0_Read_value(const timer0_t *timer0 , uint16 *value){
    Std_ReturnType retVal = E_NOT_OK;
    uint8 l_tmr0l = 0 , l_tmr0h = 0;
    if((NULL == timer0) || (NULL == value)){
        retVal = E_NOT_OK;
    }
    else{
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *value = (uint16)((l_tmr0h << 8) + l_tmr0l);
        retVal = E_OK;
    }
    return retVal;
}



/*--------------------------------------Helper Functions-------------------------------------*/

static inline void Timer0_Prescaler_Config(const timer0_t *timer0){
    if(NULL != timer0){
        if(TIMER0_PRESCALER_ENABLE_CFG == timer0->prescaler_enable){
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS = timer0->prescaler_value;
        }
        else if(TIMER0_PRESCALER_DISABLE_CFG == timer0->prescaler_enable){
            TIMER0_PRESCALER_DISABLE();
        }
    }
}

static inline void Timer0_Mode_Select(const timer0_t *timer0){
    if(NULL != timer0){
        if(TIMER0_TIMER_MODE == timer0->timer0_mode){
            TIMER0_TIMER_MODE_ENABLE();
        }
        else if(TIMER0_COUNTER_MODE == timer0->timer0_mode){
            TIMER0_COUNTER_MODE_ENABLE();
            if(TIMER0_RISING_EDGE_CFG == timer0->timer0_counter_edge){
                TIMER0_RISING_EDGE_ENABLE();
            }
            else if(TIMER0_FALLING_EDGE_CFG == timer0->timer0_counter_edge){
                TIMER0_FALLING_EDGE_ENABLE();
            }
        }
    }
}

static inline void Timer0_Register_Size_Config(const timer0_t *timer0){
    if(NULL != timer0){
        if(TIMER0_8_BIT_REGISTER_MODE == timer0->timer0_register_size){
            TIMER0_8_BIT_REGISTER_MODE_ENABLE();
        }
        else if(TIMER0_16_BIT_REGISTER_MODE == timer0->timer0_register_size){
            TIMER0_16_BIT_REGISTER_MODE_ENABLE();
        }
    }
}
    
/*---------------------------------------------- ISR --------------------------------------------------*/

void TMR0_ISR(void){
    TIMER0_InterruptFlagClear();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}