/* 
 * File:   hal_eeprom.c
 * Author: Adham
 *
 * Created on August 11, 2024, 11:09 PM
 */


#include "hal_eeprom.h"


/**
 * @brief Write data in a specific address in the EEPROM
 * @param bADD the address that the data will be written in
 * @param bData the data to be written in the required address
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Data_EEPROM_Write_Byte(uint16 bADD , uint8 bData){
    Std_ReturnType retVal = E_NOT_OK;
    /* Read the interrupt status */
    uint8 General_Interrupt_Status = INTCONbits.GIE;
    /* Update the address register */
    EEADRH = (uint8)(bADD >> 8) & 0x03;
    EEADR = (uint8)(bADD & 0xFF);
    /* Update the data register */
    EEDATA = bData;
    /* Select Access to EEPROM memory */
    EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allow write cycles to flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable all interrupts "General interrupt" */
    INTERRUPT_GlobalInterruptDisable();
    /* Write the required sequence "0x55 -> 0xAA" */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiate a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibit write cycles to flash program/data EEPROM */
     EECON1bits.WREN = INHIBIT_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the interrupt status */
     INTCONbits.GIE = General_Interrupt_Status;
     retVal = E_OK;
    return retVal;
}
/**
 * @brief Read data from a specific address in the EEPROM
 * @param bADD the address that the data will be read from
 * @param bData the read data from the given address
 * @return status of the function
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : the function has issue to perform this action
 */
Std_ReturnType Data_EEPROM_Read_Byte(uint16 bADD , uint8 *bData){
    Std_ReturnType retVal = E_NOT_OK;
    if(NULL == bData){
       retVal = E_NOT_OK;
    }
    else{
        /* Update the address register */
        EEADRH = (uint8)(bADD >> 8) & 0x03;
        EEADR = (uint8)(bADD & 0xFF);
        /* Select access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_DATA_EEPROM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        /* NOPs may be required for latency and high frequencies */
        NOP();
        NOP();
        /* Return Data */
        *bData = EEDATA;
        retVal = E_OK;
    }
    return retVal;
}