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


//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------


// Define a structure to hold different data types

int main(void)
{
    const int count_start = 0;
    const int count_finish = 100;
    uint8_t loop_count;
    for(loop_count = 0; loop_count <= count_finish; loop_count++)
    {
        lcd_write_byte(loop_count);
        loop_count++;
        if(loop_count > count_finish)
        {
            loop_count = count_start;
        }
    }
} /* main */

void SysTick_Handler(void)
{
    uint8_t switches_on = dipsw_read();
    seg7_hex(SEG7_DIG0_ENABLE_IDX, switches_on);
}
