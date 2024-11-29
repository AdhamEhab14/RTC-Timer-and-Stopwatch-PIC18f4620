/* 
 * File:   hal_eeprom.h
 * Author: Adham
 *
 * Created on August 11, 2024, 11:09 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/***************************************Includes***************************************/

#include "pic18f4620.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/***********************************Macro Declarations**********************************/

#define ACCESS_FLASH_PROGRAM_MEMORY         1
#define ACCESS_DATA_EEPROM_MEMORY           0

#define ACCESS_CONFIG_REGISTERS             1
#define ACCESS_FLASH_EEPROM_MEMORY          0

#define ALLOW_WRITE_CYCLES_FLASH_EEPROM     1
#define INHIBIT_WRITE_CYCLES_FLASH_EEPROM   0

#define INITIATE_DATA_EEPROM_WRITE_ERASE    1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED   0

#define INITIATE_DATA_EEPROM_READ           1

/******************************Macro Function Declarations******************************/

/***********************************Datatype Declarations*******************************/

/***********************************Function Declarations*******************************/

/**
 * @brief Write data in a specific address in the EEPROM
 * @param bADD the address that the data will be written in
 * @param bData the data to be written in the required address
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Data_EEPROM_Write_Byte(uint16 bADD , uint8 bData);
/**
 * @brief Read data from a specific address in the EEPROM
 * @param bADD the address that the data will be read from
 * @param bData the read data from the given address
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Data_EEPROM_Read_Byte(uint16 bADD , uint8 *bData);

#endif	/* HAL_EEPROM_H */

