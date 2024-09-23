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

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define P1_Push_Time            (10)   //time for which PBs need to be depressed
                                       // in order to activate 7seg, in ms
#define Seg7_3                  (0x4F) //Displays the number 3 on 7seg display

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

    run_lab5_part1();

} /* main */

void run_lab5_part1()
{
    uint8_t loop_count = 0;
    uint8_t p1_iterations = 3;
    while(loop_count < p1_iterations)
    {
        if(is_pb_down(PB1_IDX))
        {
            msec_delay(P1_Push_Time);
            if(is_pb_down(PB1_IDX))
            {
                seg7_on(Seg7_3, SEG7_DIG0_ENABLE_IDX);
            }
        }

        if(is_pb_down(PB1_IDX))
        {
            msec_delay(P1_Push_Time);
            if(is_pb_down(PB1_IDX))
            {
                seg7_off();
            }
        }
        loop_count++;
    }
}