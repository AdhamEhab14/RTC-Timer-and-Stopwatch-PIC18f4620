/* 
 * File:   application.c
 * Author: Adham
 *
 * Created on July 6, 2024, 6:01 PM
 */

#include "application.h"



volatile uint8 seconds, minutes, hours;
volatile uint8 paused_hours, paused_minutes, paused_seconds;
volatile uint8 pause_flag = 0;
volatile uint8 resume_flag = 1;
volatile uint8 pause_resume_btn_state;
volatile uint8 mode_status = 3;
volatile uint8 alarm_hours, alarm_minutes, alarm_seconds;
volatile uint8 clock_hours, clock_minutes, clock_seconds;
uint8 time[4];
uint8* ptr;
volatile uint8 keypad_value ;
uint8 hours_input[2];
uint8 minutes_input[2];
uint8 seconds_input[2];
uint8 counter1 = 0 , counter2 = 0, counter3 = 0;


void seven_seg_display(uint8 __hours , uint8 __minutes , uint8 __seconds);
void set_alarm(void);
void get_rtc_time(void);
void hours_display(void);
void minutes_display(void);
void seconds_display(void);

int main() {
    Std_ReturnType retVal = E_NOT_OK; //fixed
    application_initialize(); //fixed
    
    get_rtc_time();
    
    while(1){
        /*------------------------------ Stopwatch Mode ----------------------------------*/
        if(INPUT_TIMER_MODE == mode_status ){
            set_alarm();
        }
        else if(START_TIMER_MODE == mode_status){
            seven_seg_display(alarm_hours, alarm_minutes, alarm_seconds);
        }
        /*------------------------------ Timer Mode ----------------------------------*/
        else if(STOPWATCH_MODE == mode_status){
            if(1 == resume_flag){
                seven_seg_display(hours, minutes, seconds);
            }
            else if(1 == pause_flag){
                seven_seg_display(paused_hours, paused_minutes, paused_seconds);
            }
            else { /* Nothing */ }
        }
        /*------------------------------ Clock Mode ----------------------------------*/
        else if(CLOCK_MODE == mode_status){
            seven_seg_display(clock_hours, clock_minutes, clock_seconds);
        }
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    ecu_layer_initialize(); //fixed 
    mcal_layer_initialize(); //fixed
}


void seven_seg_display(uint8 __hours , uint8 __minutes , uint8 __seconds){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(__hours/10))); 
    retVal = gpio_pin_write_logic(&seg_enable_1 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_1 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(__hours%10))); 
    retVal = gpio_pin_write_logic(&seg_enable_2 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_2 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(__minutes/10))); 
    retVal = gpio_pin_write_logic(&seg_enable_3 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_3 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(__minutes%10))); 
    retVal = gpio_pin_write_logic(&seg_enable_4 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_4 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(__seconds/10))); 
    retVal = gpio_pin_write_logic(&seg_enable_5 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_5 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(__seconds%10))); 
    retVal = gpio_pin_write_logic(&seg_enable_6 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_6 , GPIO_LOW);
}

void set_alarm(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
        while(1){
                /* Loop to catch pressed button */
                do{
                    retVal = keypad_get_value(&keypad, &keypad_value);
                }while(keypad_value == '\0');
                hours_input[counter1] = keypad_value;
                counter1++;
                /* Checking for maximum digits */
                if(counter1 == 2){
                    keypad_value = '\0';
                    break;
                }
                keypad_value = '\0';
            }
        hours_display();
            /* Getting the minutes */
            while(1){
                /* Loop to catch pressed button */
                do{
                    retVal = keypad_get_value(&keypad, &keypad_value);
                }while(keypad_value == '\0');
                minutes_input[counter2] = keypad_value;
                counter2++;
                /* Checking for maximum digits */
                if(counter2 == 2){
                    keypad_value = '\0';
                    break;
                }
                keypad_value = '\0';
            }
        minutes_display();
            /* Getting the seconds */
            while(1){
                /* Loop to catch pressed button */
                do{
                    retVal = keypad_get_value(&keypad, &keypad_value);
                }while(keypad_value == '\0');
                seconds_input[counter3] = keypad_value;
                counter3++;
                /* Checking for maximum digits */
                if(counter3 == 2){
                    keypad_value = '\0';
                    break;
                }
                keypad_value = '\0';
            }             
        seconds_display();
        alarm_hours  = (hours_input[0] - 48) * 10 + (hours_input[1] - 48);
        alarm_minutes  = (minutes_input[0] - 48) * 10 + (minutes_input[1] - 48);
        alarm_seconds  = (seconds_input[0] - 48) * 10 + (seconds_input[1] - 48);
        mode_status = START_TIMER_MODE;
}


void TIMER0_IneterruptHandler(void){
    if(STOPWATCH_MODE == mode_status){
        seconds++;
        if(60 == seconds){
            seconds = 0;
            minutes++;
        }
        if(60 == minutes){
            minutes = 0;
            hours++;
        }
        if(99 == hours){
            hours = 0;
        }
    }
    else if(START_TIMER_MODE == mode_status){
            if(0 == alarm_seconds){
                if(0 == alarm_minutes){
                    if(0 == alarm_hours){
                        gpio_pin_toggle_logic(&buzzer);
                        led_toggle(&buzzer_led);
                    }
                    else if(0 != alarm_hours){
                        alarm_hours--;
                        alarm_minutes = 60;
                    }
                }
                else if(0 != alarm_minutes){
                    alarm_minutes--;
                    alarm_seconds = 59;
                }
            }
            else if(0 != alarm_seconds){
                alarm_seconds--;
            }   
    }
    else if(CLOCK_MODE == mode_status){
        clock_seconds++;
        if(60 == clock_seconds){
            clock_seconds = 0;
            clock_minutes++;
        }
        if(60 == clock_minutes){
            clock_minutes = 0;
            clock_hours++;
        }
        if(24 == clock_hours){
            clock_hours = 0;
        }
    }
}

void INT0_ResetIneterruptHandler(void){
    hours = 0;
    minutes = 0;
    seconds = 0;
}

void RB0_PauseIneterruptHandler(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    if(1 == resume_flag){
        resume_flag = 0;
        retVal = Data_EEPROM_Write_Byte(0x00 , hours);
        retVal = Data_EEPROM_Write_Byte(0x01 , minutes);
        retVal = Data_EEPROM_Write_Byte(0x02 , seconds);
        retVal = Data_EEPROM_Read_Byte(0x00 ,&paused_hours);
        retVal = Data_EEPROM_Read_Byte(0x01 ,&paused_minutes);
        retVal = Data_EEPROM_Read_Byte(0x02 ,&paused_seconds);
        pause_flag = 1;
    }
    else if(1 == pause_flag){
        pause_flag = 0;
        resume_flag = 1;
        retVal = Data_EEPROM_Read_Byte(0x00 ,&hours);
        retVal = Data_EEPROM_Read_Byte(0x01 ,&minutes);
        retVal = Data_EEPROM_Read_Byte(0x02 ,&seconds);
    }
}

void INT1_CountUpIneterruptHandler(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    mode_status = STOPWATCH_MODE;
    retVal = led_turn_on(&stopwatch_led);
    retVal = led_turn_off(&timer_led);
    retVal = led_turn_off(&clock_led);
}

void INT2_CountDownIneterruptHandler(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    mode_status = INPUT_TIMER_MODE;
    retVal = led_turn_on(&timer_led);
    retVal = led_turn_off(&stopwatch_led);
    retVal = led_turn_off(&clock_led);
}


void RB1_ClockIneterruptHandler(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    mode_status = CLOCK_MODE;
    retVal = led_turn_on(&clock_led);
    retVal = led_turn_off(&timer_led);
    retVal = led_turn_off(&stopwatch_led);
}


void hours_display(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(hours_input[0] - 48))); 
    retVal = gpio_pin_write_logic(&seg_enable_1 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_1 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(hours_input[1] - 48))); 
    retVal = gpio_pin_write_logic(&seg_enable_2 , GPIO_HIGH);
    __delay_us(50);
}
void minutes_display(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    retVal = gpio_pin_write_logic(&seg_enable_2 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(minutes_input[0] - 48))); 
    retVal = gpio_pin_write_logic(&seg_enable_3 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_3 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(minutes_input[1] - 48))); 
    retVal = gpio_pin_write_logic(&seg_enable_4 , GPIO_HIGH);
    __delay_us(50);
}
void seconds_display(void){
    Std_ReturnType retVal = E_NOT_OK; //fixed
    retVal = gpio_pin_write_logic(&seg_enable_4 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(seconds_input[0] - 48))); 
    retVal = gpio_pin_write_logic(&seg_enable_5 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_5 , GPIO_LOW);
    retVal = seven_segment_write_number(&seven_segment , ((uint8)(seconds_input[1] - 48))); 
    retVal = gpio_pin_write_logic(&seg_enable_6 , GPIO_HIGH);
    __delay_us(50);
    retVal = gpio_pin_write_logic(&seg_enable_6 , GPIO_LOW);
}



void get_rtc_time(void){
    InitI2C();
    ptr = time;
	ptr = Get_DS1307_RTC_Time();

    clock_hours = ptr[2];
    clock_minutes = ptr[1];
    clock_seconds = ptr[0];
    
}

