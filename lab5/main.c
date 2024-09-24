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

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define DEBOUNCE            (600)   //time for which PBs need to be depressed
                                       // in order to activate 7seg, in ms
#define SEG7_3                  (0x4F) //Displays the number 3 on 7seg display
#define In_Between          (500)

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

    run_lab5_part1();
    run_lab5_part2();

} /* main */

void run_lab5_part1()
{
    uint8_t loop_count = 0;
    uint8_t p1_iterations = 3;
    bool display_on = false;
    while(loop_count < p1_iterations)
    {
        if(is_lpsw_down(LP_SW2_IDX))
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

void run_lab5_part2()
{
    msec_delay(In_Between);
    typedef enum
    {
        get_low,
        get_high,
        display,
    } fsm_states;

    fsm_states state = get_low;
    uint8_t display_num = 0;
    switch(state)
    {
        case(get_low):
        {
            uint8_t dipsw_value = dipsw_read();
            display_num |= dipsw_value;
            if(is_lpsw_down(LP_SW2_IDX))
            {
                state = get_high;
                msec_delay(DEBOUNCE);
            }
        }

        case(get_high):
        {
            uint8_t dipsw_value = dipsw_read();
            display_num |= (dipsw_value << 4);
            if(is_lpsw_down(LP_SW2_IDX))
            {
                state = display;
                msec_delay(DEBOUNCE);
            }
        }

        case(display):
        {
            if(is_lpsw_down(LP_SW2_IDX))
            {
                seg7_on(SEG7_DIG2_ENABLE_IDX, display_num);
                state = get_low;
                msec_delay(DEBOUNCE);
            }
            else
            {
                seg7_on(SEG7_DIG0_ENABLE_IDX, display_num);
            }
        }
    }
}