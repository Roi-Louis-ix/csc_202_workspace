//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Matthew Barry
//
//       LAB NAME:  Lab 7 Part 1: Working with Interrupts
//
//      FILE NAME:  main.c
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//    This program uses SysTick to flash "S O S" on the 7seg display while the
//    LCD scrolls through "Microcontrollers are fun!"
//
//*****************************************************************************
//*****************************************************************************

//-----------------------------------------------------------------------------
// Loads standard C include files
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>

//-----------------------------------------------------------------------------
// Loads MSP launchpad board support macros and definitions
//-----------------------------------------------------------------------------
#include <ti/devices/msp/msp.h>
#include "clock.h"
#include "lcd1602.h"
#include "LaunchPad.h"


//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void run_lab7_part1();
void run_lab7_part2();
void lcd_string_parser(char string[], uint8_t start_lcd_addr, uint8_t max_lcd_addr);

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define NUM_STATES                                                          18
#define MSPM0_CLOCK_FREQUENCY                                           (40E6)
#define SYST_TICK_PERIOD                                            (10.25E-3)
#define SYST_TICK_PERIOD_COUNT      (SYST_TICK_PERIOD * MSPM0_CLOCK_FREQUENCY)
#define RUNNING_PART                                                    (1000)
#define DEBOUNCE                                                          (80)
#define LCD_DELAY                                                        (100)

//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------
const uint8_t seg7_letter_code[] =
{
    0x6D, 0x00, 0x6D, 0x00, 0x6D, 0x00, // S
    0x3F, 0x00, 0x3F, 0x00, 0x3F, 0x00, // O
    0x6D, 0x00, 0x6D, 0x00, 0x6D, 0x00, // S
};

const uint8_t delay_count[] = 
{
    0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18,
    0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
    0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x30
};


int main(void)
{
    clock_init_40mhz();
    launchpad_gpio_init();

    I2C_init();
    lcd1602_init();
    lcd_clear();
    led_init();
    led_disable();
    seg7_init();
    dipsw_init();


    run_lab7_part1();
    run_lab7_part2();
    for (; ;);
} 

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function is an interrupt service routine for the SysTick timer. It
// flashes "S O S" on the 7seg display for the number of SysTick pulses 
// specified in delay_count[].
// 
// 
//  
//  
// INPUT PARAMETERS:
// none
//
// OUTPUT PARAMETERS:
//  none
//
// RETURN:
// none
// -----------------------------------------------------------------------------
void SysTick_Handler(void)
{
    static uint16_t delay_time = 1;
    static uint16_t code_index = 0;

    delay_time--;
    if (delay_time == 0)
    {
        seg7_on(seg7_letter_code[code_index], SEG7_DIG0_ENABLE_IDX);

        delay_time = delay_count[code_index];
        code_index++;

        if (code_index == NUM_STATES)
        {
            code_index = 0;
        }
    }
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function scrolls through the message "Microcontrollers are fun" on Line
// 2 of the LCD while SOS continues to flash.
//  
// INPUT PARAMETERS:
// none
//
// OUTPUT PARAMETERS:
//  none
//
// RETURN:
// none
// -----------------------------------------------------------------------------
void run_lab7_part1()
{
    bool Done = 0;
    char msg[] = "Microcontrollers are fun.";
    int addr;
    sys_tick_init(SYST_TICK_PERIOD_COUNT);
    
    while(!Done)
    {
        for(addr = LCD_LINE2_ADDR + LCD_CHAR_POSITION_16; addr >= LCD_LINE2_ADDR && !Done; addr--)
        {
            lcd_set_ddram_addr(addr);
            lcd_write_string(msg);
            msec_delay(LCD_DELAY);
            if(is_pb_down(PB2_IDX))
            {
                msec_delay(DEBOUNCE);
                addr = LCD_LINE2_ADDR;
                Done = true;
            }
        }
        if(is_pb_down(PB2_IDX))
        {
            msec_delay(DEBOUNCE);
            Done = true;
        }
        uint8_t msg_idx = 0;
        while(msg[msg_idx] != '\0' && !Done)
        {
            
            lcd_set_ddram_addr(LCD_LINE2_ADDR);
            lcd_write_string(msg + msg_idx);
            msg_idx++;
            msec_delay(LCD_DELAY);
            if(is_pb_down(PB2_IDX))
            {
                msec_delay(DEBOUNCE);
                lcd_clear();
                Done = 1;
            }
        }
        
    }
    sys_tick_disable();
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR);
    lcd_write_string("Part 1 done");
    msec_delay(RUNNING_PART);
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function scrolls through the message "Microcontrollers are fun. I love
// programming in MSPM0+ assembly code!!!" on the second line of the LCD while
// SOS continues to flash.
//  
// INPUT PARAMETERS:
// none
//
// OUTPUT PARAMETERS:
//  none
//
// RETURN:
// none
// -----------------------------------------------------------------------------
void run_lab7_part2()
{
    lcd_clear();
    lcd_write_string("Press PB2");
    while(is_pb_up(PB2_IDX)) {}
    sys_tick_init(SYST_TICK_PERIOD_COUNT);
    lcd_clear();
    lcd_write_string("Running Part 2");
    msec_delay(RUNNING_PART);
    lcd_clear();
    bool Done = 0;
    char msg[] = "Microcontrollers are fun. I love programming in MSPM0+ assembly code!!!";
    int addr;
    while(!Done)
    {
        for(addr = LCD_LINE2_ADDR + LCD_CHAR_POSITION_16; addr >= LCD_LINE2_ADDR && !Done; addr--)
        {
            lcd_set_ddram_addr(addr);
            char msg[] = "Microcontrollers are fun. I love programming in MSPM0+ assembly code!!!";
            lcd_string_parser(msg, addr, LCD_LINE2_ADDR + LCD_CHAR_POSITION_16);
            msec_delay(LCD_DELAY);
            if(is_pb_down(PB2_IDX))
            {
                msec_delay(DEBOUNCE);
                lcd_clear();
                Done = 1;
            }
        }
        uint16_t msg_idx = 0;
        while(msg[msg_idx] != '\0' && !Done)
        {
            
            lcd_set_ddram_addr(LCD_LINE2_ADDR);
            char msg[] = "Microcontrollers are fun. I love programming in MSPM0+ assembly code!!!";
            lcd_string_parser(msg + msg_idx, LCD_LINE2_ADDR, LCD_LINE2_ADDR + LCD_CHAR_POSITION_16);
            msec_delay(LCD_DELAY);
            if(is_pb_down(PB2_IDX))
            {
                msec_delay(DEBOUNCE);
                lcd_clear();
                Done = 1;
            }
            msg_idx++;
        }
        addr = LCD_LINE2_ADDR + LCD_CHAR_POSITION_16;
    }
    sys_tick_disable();
    lcd_clear();
    lcd_write_string("Part 2 done");
    msec_delay(RUNNING_PART);
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function terminates the string at 1 character past the edge of the LCD,
// Preventing it from wrapping around.
//  
// INPUT PARAMETERS:
// none
//
// OUTPUT PARAMETERS:
//  none
//
// RETURN:
// none
// -----------------------------------------------------------------------------
void lcd_string_parser(char string[],
                       uint8_t start_lcd_addr,
                       uint8_t max_lcd_addr)
{
    lcd_set_ddram_addr(start_lcd_addr);
    if(string[max_lcd_addr - start_lcd_addr] != '\0')
    {
        string[max_lcd_addr - start_lcd_addr + LCD_CHAR_POSITION_1] = '\0';
    }

    lcd_write_string(string);
}