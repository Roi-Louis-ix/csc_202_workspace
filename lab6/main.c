//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Matthew Barry
//
//       LAB NAME:  Lab 6: Interfacing with the LCD
//
//      FILE NAME:  main.c
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//    This program serves as an interface between the LaunchPad, push buttons,
//    keypad, and LCD.
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
void run_lab6_part1();
void run_lab6_part2();
void run_lab6_part3();
void run_lab6_part4();
<<<<<<< HEAD

=======
>>>>>>> e807cecaad076096c9740e6d7f689c10ff99f295
//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define A_Byte              (0x41)  //Corresponding ASCII code for the letter A
#define P1_Letter_Length    (500)   //Length to display each letter in ms
#define Running_Part        (1000)  //Time to display "RUNNING PART 2" in ms
#define Debounce            (20)
#define Count_Down          (200)   //Countdown time in ms 




int main(void)
{
    clock_init_40mhz();
    launchpad_gpio_init();

    I2C_init();
    lcd1602_init();
    lcd_set_display_on();
    lcd_clear();
    keypad_init();

    dipsw_init();

    //run_lab6_part1();
    //run_lab6_part2();
    //run_lab6_part3();
    //run_lab6_part4();
    char*  message = "WINNER";
    lcd_set_ddram_addr(LCD_CHAR_POSITION_6);
    lcd_write_string(message);
} /* main */

//-----------------------------------------------------------------------------
// DESCRIPTION:
<<<<<<< HEAD
// This function displays the entire alphabet on the LCD.
// 
=======
// This function displays the alphabet on the LCD display.
>>>>>>> ff9750081f9fcd494199c57e309d31511660b122
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
void run_lab6_part1()
{
    uint8_t loop_count = 0;
    uint8_t alphabet = 26;
    uint8_t addr = 0;
    char letter = 'A';
    for(loop_count = 0; loop_count < alphabet; loop_count++)
    {
        lcd_set_ddram_addr(addr);
        lcd_write_char(letter + loop_count);
        addr++;
        if(addr == LCD_CHAR_POSITION_16 + 1)
        {
            addr = LCD_LINE2_ADDR;
        }
    }
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
<<<<<<< HEAD
// This function displays 3 numbers on the LCD. The first number comes on
// automatically, then when PB1 is pressed, the second comes on under it, then
// when PB1 is pressed again, both are cleared and the third number is 
// displayed.
// 
=======
// This function displays numbers on the LCD and uses PB1 to switch between
// numbers. The first number is displayed on row 1, the second on row 2,
// and the third on row 1 after the first and second are cleared.
>>>>>>> ff9750081f9fcd494199c57e309d31511660b122
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
void run_lab6_part2()
{
    uint32_t top_num = 1234567890;
    uint16_t bot_num = 1234;
    uint8_t top_num2 = 123;

    //Begin P2
    while(is_pb_up(PB2_IDX)) {msec_delay(Debounce);}
    lcd_clear();
    lcd_write_string("Running Part 2");
    msec_delay(Running_Part);

    //First two numbers displayed
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_4);
    lcd_write_quadbyte(top_num);

    while(is_pb_up(PB1_IDX)) {msec_delay(Debounce);}
    lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_6);
    lcd_write_doublebyte(bot_num);
    while(is_pb_down(PB1_IDX)) {}

    //Display the third number
    while(is_pb_up(PB1_IDX)) {msec_delay(Debounce);}
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_6);
    lcd_write_doublebyte(top_num2);
    while(is_pb_down(PB1_IDX)) {}

    while(is_pb_up(PB1_IDX)) {msec_delay(Debounce);}
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_3);
    lcd_write_string("Part 2 Done.");
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function counts down from 100 every 200 ms. When the count reaches 0 or
// PB1 is pressed, the counter resets to 100; pressing PB2 terminates the
// program.
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
    bool counting = 1;
    lcd_clear();
    
    while(counting)
    {
       lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_7);
        if(is_pb_down(PB2_IDX))
        {
            msec_delay(Debounce);
            counting = 0;
        }
        
        lcd_write_byte(timer_count);
        if(timer_count == timer_stop)
        {
            timer_count = 101;
        }
        if(is_pb_down(PB1_IDX))
        {
            msec_delay(Debounce);
            timer_count = 101;
        }
        timer_count--;
        msec_delay(Count_Down);
    }

    lcd_set_ddram_addr(LCD_LINE1_ADDR);
    lcd_write_string("Part 3 Done.");
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function displays the keypad pressed on the LCD. When the entire
// display is filled, it clears the display and restarts at line 1 column 1.
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
void run_lab6_part4()
{
    lcd_set_ddram_addr(LCD_LINE2_ADDR);
    lcd_write_string("Press PB2");

    while(is_pb_up(PB2_IDX)) {}
    lcd_clear();
    lcd_write_string("Running Part 4");
    msec_delay(Running_Part);
    lcd_clear();

    uint8_t pressed_key = 0;
    bool running = 1;
    uint8_t key_count = 0;
    while(running)
    {
        pressed_key = keypad_scan();
        if(pressed_key != NO_KEY_PRESSED)
        {
            if(key_count == CHARACTERS_PER_LCD_LINE)
            {
                lcd_set_ddram_addr(LCD_LINE2_ADDR);
            }
            else if(key_count == TOTAL_CHARACTERS_PER_LCD)
            {
                lcd_clear();
                lcd_set_ddram_addr(LCD_LINE1_ADDR);
                key_count = 0;
            }
            hex_to_lcd(pressed_key);
            wait_no_key_pressed();
            key_count++;
        }
        
        while(is_pb_down(PB1_IDX))
        {
            msec_delay(Debounce);
            lcd_clear();
            lcd_set_ddram_addr(LCD_LINE1_ADDR);
            key_count = 0;
        }
        while(is_pb_down(PB2_IDX))
        {
            msec_delay(Debounce);
            lcd_clear();
            running = 0;
        }
    }
    lcd_set_ddram_addr(LCD_LINE1_ADDR);
    lcd_write_string("Program Completed.");
}
