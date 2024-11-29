/* 
 * File:   mcal_internal_interrupt.h
 * Author: Adham
 *
 * Created on August 7, 2024, 9:53 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/***************************************Includes***************************************/

#include "mcal_interrupt_config.h"

/***********************************Macro Declarations**********************************/

/******************************Macro Function Declarations******************************/

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the Timer0 module */
#define TIMER0_InterruptDisable() (INTCONbits.TMR0IE = 0)
/* This routine sets the interrupt enable for the Timer0 module */
#define TIMER0_InterruptEnable() (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the Timer0 module */
#define TIMER0_InterruptFlagClear() (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine sets high priority of the Timer0 module */
#define TIMER0_HighPrioritySet() (INTCON2bits.TMR0IP = 1)
/* This routine sets low priority of the Timer0 module */
#define TIMER0_LowPrioritySet() (INTCON2bits.TMR0IP = 0)
#endif
#endif







/***********************************Datatype Declarations*******************************/

/***********************************Function Declarations*******************************/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

