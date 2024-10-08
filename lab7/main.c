//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  TBD
//
//       LAB NAME:  TBD
//
//      FILE NAME:  main.c
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//    This program serves as a ... 
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
#define MSPM0_CLOCK_FREQUENCY                                           (40E6)
#define SYST_TICK_PERIOD                                            (10.25E-3)
#define SYST_TICK_PERIOD_COUNT      (SYST_TICK_PERIOD * MSPM0_CLOCK_FREQUENCY)
#define RUNNING_PART                                                    (1000)

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define NUM_STATES                18

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

// Define a structure to hold different data types

void run_lab7_part1();
void run_lab7_part2();

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
    sys_tick_init(SYST_TICK_PERIOD_COUNT);

    run_lab7_part1();
    for (; ;);
} 

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

void run_lab7_part1()
{
    bool Done = 0;
    char msg[] = "Microcontrollers are fun.";
    int addr;
    while(!Done)
    {
        for(addr = 0x4F; addr >= 0x40; addr--)
        {
            lcd_set_ddram_addr(addr);
            lcd_write_string(msg);
        }
        uint8_t msg_idx = 0;
        while(msg[msg_idx] != '\0')
        {
            
            lcd_set_ddram_addr(LCD_LINE2_ADDR);
            lcd_write_string(msg + msg_idx);
            msg_idx++;
            lcd_clear();
        }
        
    }
}

void run_lab7_part2()
{
    lcd_write_string("Press PB2");
    while(is_pb_up(PB2_IDX)) {}
    lcd_clear();
    lcd_write_string("Running Part 2");
    msec_delay(RUNNING_PART);

}

void lcd_string_parser(string, start_lcd_addr, max_lcd_addr)
{
    uint8_t addr;
    for(addr = start_lcd_addr; addr >= max_lcd_addr; addr--)
    {
        lcd_set_ddram_addr(addr);
        lcd_write_string(string);
    }
}