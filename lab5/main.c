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
void run_lab5_part1();
void run_lab5_part2();
void run_lab5_part3();
void run_lab5_part4();

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define DEBOUNCE            (600)       //time for which PBs need to be depressed
                                        // in order to activate 7seg, in ms
#define SEG7_3              (0x4F)      //Displays the number 3 on 7seg display
#define In_Between          (600)
#define P4_LEDs_On          (0xFFFF)    //Turns on all LEDs
#define P4_On_Off           (500)       //On and off time for LEDs in Part 4

//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------


// Define a structure to hold different data types

int main(void)
{
    clock_init_40mhz();
    launchpad_gpio_init();
    seg7_init();
    dipsw_init();
    lpsw_init();
    keypad_init();

    //run_lab5_part1();
    //run_lab5_part2();
    run_lab5_part3();
    //run_lab5_part4();

} /* main */

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function allows the number 3 to be displayed on the 7seg display by PB1
// or turned off by PB1 if it is already being displayed.
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
void run_lab5_part1()
{   
    uint8_t loop_count = 0;
    uint8_t p1_iterations = 3;
    bool display_on = false;
    while(loop_count < p1_iterations)
    {   
        if(is_pb_down(PB1_IDX))
        {
            if(display_on)
            {
                seg7_off();
                display_on = false;
                loop_count++;                
            }
            else
            {
                seg7_on(SEG7_3, SEG7_DIG0_ENABLE_IDX);
                display_on = true;
            }
            
        }
        msec_delay(DEBOUNCE);
    }
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function acts as a state machine that reads the DIP switch values and
// writes them to the 7seg display when SW2 is pressed on the LaunchPad. 
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
void run_lab5_part2()
{
    msec_delay(In_Between);
    typedef enum
    {
        get_low,        //Gets the first 4 digits for the 7seg display
        get_high,       //Gets the last 3 digits for the 7seg display
        display,        //Displays the results from get_low and get_high on
                        //the 7seg display
    } fsm_states;

    fsm_states state = get_low;
    uint8_t display_num = 0;
    switch(state)
    {
        case(get_low):
        {
            while(is_lpsw_up(LP_SW2_IDX)) {}
            if(is_lpsw_down(LP_SW2_IDX))
            {
                uint8_t dipsw_value = dipsw_read();
                display_num |= dipsw_value;
                msec_delay(DEBOUNCE);
                while(is_lpsw_down(LP_SW2_IDX)) {}

                state = get_high;
                msec_delay(DEBOUNCE);
            }
        }

        case(get_high):
        {
            while(is_lpsw_up(LP_SW2_IDX)) {}
            if(is_lpsw_down(LP_SW2_IDX))
            {
                uint8_t dipsw_value = dipsw_read();
                display_num |= (dipsw_value << 4);
                msec_delay(DEBOUNCE);
                while(is_lpsw_down(LP_SW2_IDX)) {}

                state = display;
                msec_delay(DEBOUNCE);
                
            }
        }

        case(display):
        {
            while(is_lpsw_up(LP_SW2_IDX)) {}
            if(is_lpsw_down(LP_SW2_IDX)) 
            {
                seg7_on(SEG7_DIG2_ENABLE_IDX, display_num);
            }
            
        }
    }
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function displays the binary value of the keypad pressed on the
// LaunchPad LEDs.
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
 void run_lab5_part3()
 {
    msec_delay(In_Between);
    lp_leds_init();

    uint8_t loop_count = 0;
    uint8_t p3_iterations = 8;
    while(loop_count < p3_iterations)
    {
        uint8_t key = getkey_pressed();
        lp_leds_on(key);
        loop_count++;
        msec_delay(DEBOUNCE);
        wait_no_key_pressed();
        lp_leds_off(key);
    }
 }

 void run_lab5_part4()
 {
    msec_delay(In_Between);

    uint8_t loop_count = 0;
    uint8_t p4_iterations = 4;
    while(loop_count < p4_iterations)
    {
        uint8_t num_of_flashes = keypad_scan();
        uint8_t flash_count = 0;
        for(flash_count; flash_count < num_of_flashes; flash_count++)
        {
            leds_on(P4_LEDs_On);
            msec_delay(P4_On_Off);
            leds_off();
            msec_delay(P4_On_Off);
        }
    }
 }