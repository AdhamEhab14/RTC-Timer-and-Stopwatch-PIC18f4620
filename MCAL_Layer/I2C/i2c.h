/* 
 * File:   i2c.h
 * Author: Adham
 *
 * Created on October 17, 2024, 11:12 PM
 */

#ifndef I2C_H
#define	I2C_H

/****************************************Includes***************************************/

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/***********************************Macro Declarations**********************************/

// Define i2c pins
#define SDA			RC4				// Data pin for i2c
#define SCK			RC3				// Clock pin for i2c
#define SDA_DIR		TRISC4			// Data pin direction
#define SCK_DIR		TRISC3			// Clock pin direction

// Define i2c speed
#define I2C_SPEED	100				// kbps

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

/***********************************Function Declarations*******************************/

void InitI2C(void);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
void I2C_Send_ACK(void);
void I2C_Send_NACK(void);
uint8  I2C_Write_Byte(unsigned char);
unsigned char I2C_Read_Byte(void);


#endif	/* I2C_H */

