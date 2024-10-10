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
#include <stdint.h>

//-----------------------------------------------------------------------------
// Loads MSP launchpad board support macros and definitions
//-----------------------------------------------------------------------------
#include <ti/devices/msp/msp.h>
#include "clock.h"
#include "LaunchPad.h"
#include "lcd1602.h"

//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void run_lab7_part3();

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define MSPM0_CLOCK_FREQUENCY                                           (40E6)
#define SYST_TICK_PERIOD                                            (10.25E-3)
#define SYST_TICK_PERIOD_COUNT      (SYST_TICK_PERIOD * MSPM0_CLOCK_FREQUENCY)
#define CNTR_TIME                                                        (200)


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------

// Define a structure to hold different data types

int main(void)
{
    I2C_init();
    clock_init_40mhz();
    launchpad_gpio_init();
    lcd1602_init();
    seg7_init();
    lcd_clear();
    led_disable();
    dipsw_init();
    sys_tick_init(SYST_TICK_PERIOD_COUNT);
    
    run_lab7_part3();
} /* main */

void run_lab7_part3()
{
    const int count_start = 0;
    const int count_finish = 100;
    uint8_t loop_count;
    
    while(true)
    {
        
        for(loop_count = count_start; loop_count < count_finish; loop_count++)
        {
            lcd_set_ddram_addr(LCD_CHAR_POSITION_7);
            lcd_write_byte(loop_count);
            if(loop_count == count_finish)
            {
                loop_count = count_start;
            }
            msec_delay(CNTR_TIME);
        }
    }
}
void SysTick_Handler(void)
{
    uint8_t switch_value = 0;
    uint8_t dip_value = 0;

    uint8_t switches_on = dipsw_read();
    uint8_t display_value = 0;
    for(uint8_t loop_count = 0; loop_count < 4; loop_count++)
    {
        if((switches_on & (1 << loop_count)) == (1 << loop_count))
        {
            display_value++;
        }
    }

    seg7_hex(display_value, SEG7_DIG0_ENABLE_IDX);
}