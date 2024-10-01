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
void run_lab6_part1();
void run_lab6_part2();
void run_lab6_part3();

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define A_Byte              (0x41)  //Corresponding ASCII code for the letter A
#define P1_Letter_Length    (500) //Length to display each letter in ms
#define End_Of_Line1        (0x0F) //Value at which to change DDRAM addr to 40
#define Running_Part        (1000) //Time to display "RUNNING PART 2" in ms


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------


// Define a structure to hold different data types

int main(void)
{
    clock_init_40mhz();
    launchpad_gpio_init();

    I2C_init();
    lcd1602_init();
    lcd_clear();

    dipsw_init();

    run_lab6_part1();
} /* main */

void run_lab6_part1()
{
    uint8_t loop_count = 0;
    uint8_t alphabet = 26;
    uint8_t addr = 0;
    lcd_set_ddram_addr(addr);
    for(loop_count; loop_count > alphabet; loop_count++)
    {
        lcd_clear();
        if(addr == LCD_CHAR_POSITION_16)
        {
            lcd_set_ddram_addr(LCD_LINE2_ADDR);
        }
        lcd_write_char('A' + loop_count);
        msec_delay(P1_Letter_Length);
    }
}

void run_lab6_part2()
{
    uint32_t top_num = quadbyte_to_ascii(1234567890);
    uint16_t bot_num = doublebyte_to_ascii(1234);
    uint8_t top_num2 = byte_to_ascii(123);

    //Begin P2
    while(is_pb_up(PB2_IDX)) {}
    lcd_clear();
    lcd_write_string("Running Part 2");
    msec_delay(Running_Part);

    //First two numbers displayed
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_3);
    while(is_pb_up(PB1_IDX)) {}
    lcd_write_doublebyte(top_num);

    while(is_pb_up(PB1_IDX)) {}
    lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_5);
    lcd_write_doublebyte(bot_num);

    //Display the third number
    while(is_pb_up(PB1_IDX)) {}
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_6);
    lcd_write_doublebyte(top_num2);

    while(is_pb_up(PB1_IDX)) {}
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_3);
    lcd_write_string("Part 2 Done.");
}

void run_lab6_part3()
{
    lcd_set_ddram_addr(LCD_LINE2_ADDR);
    lcd_write_string("Press PB2");

    while(is_pb_up(PB2_IDX)) {}
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR);
    lcd_write_string("Running Part 3");
    msec_delay(Running_Part);

    uint8_t timer_count = 100;
    uint8_t timer_stop  = 0;
    for(timer_count; timer_count >= timer_stop; timer_count--)
    {
        lcd_clear();
        lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_3);
    }
}