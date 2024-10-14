//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Matthew Barry
//
//       LAB NAME:  7 Part 4: the Hummdinger
//
//      FILE NAME:  main.c
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//    This program configures and runs interrupts for both pushbuttons. It 
//    runs a counter on the LCD and LEDs whilst indicating if a PB is pressed.
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
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/devices/msp/peripherals/hw_gpio.h"
#include "ti/devices/msp/peripherals/m0p/hw_cpuss.h"

//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void run_lab7_part4();
void GROUP1_IRQHandler();
void config_pb1_interrupt();
void config_pb2_interrupt();

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define COUNTER_TIME            (200)
#define DEBOUNCE                 (80)

//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------
bool g_PB1_pressed;
bool g_PB2_pressed;

// Define a structure to hold different data types

int main(void)
{
    I2C_init();
    lcd1602_init();
    launchpad_gpio_init();
    dipsw_init();
    led_init();
    led_enable();

    config_pb1_interrupt();
    config_pb2_interrupt();
    
    run_lab7_part4();
    
    while(true);
} /* main */

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function counts from 0 to 99 and displays the count on the LCD and the
// binary value on the LEDs.
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
void run_lab7_part4(void)
{
    bool display = false;
    while(!g_PB1_pressed)
    {
        uint8_t loop_stop = 100;
        uint8_t loop_start  = 0;
        for(uint8_t loop_count = loop_start; loop_count < loop_stop && !g_PB1_pressed; loop_count++)
        {
            lcd_set_ddram_addr(LCD_CHAR_POSITION_7);
            lcd_write_byte(loop_count);
            leds_on(loop_count);
            msec_delay(COUNTER_TIME);
            if(g_PB2_pressed)
            {
                msec_delay(DEBOUNCE);
                if(display)
                {
                    lcd_clear();
                    g_PB2_pressed = false;
                    display = false;
                }

                else 
                {
                    lcd_set_ddram_addr(LCD_LINE2_ADDR);
                    lcd_write_string("PB2 pressed");
                    g_PB2_pressed = false;
                    display = true;
                }
            }
        }
        
    
    }
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR);
    lcd_write_string("Program Stopped");
    leds_off();
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function programs an ISR for pushbuttons 1 and 2, on bits 15 and 18.
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
void GROUP1_IRQHandler(void)
{

    bool display;

    uint32_t group_iidx_status;
    uint32_t gpio_mis;
    do 
    {
        group_iidx_status = CPUSS->INT_GROUP[1].IIDX;

        switch (group_iidx_status)
        {
            case (CPUSS_INT_GROUP_IIDX_STAT_INT0):
                gpio_mis = GPIOA->CPU_INT.MIS;
                if ((gpio_mis & GPIO_CPU_INT_MIS_DIO15_MASK) == GPIO_CPU_INT_MIS_DIO15_SET)
                {
                    g_PB2_pressed = true;
                    GPIOA->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO15_CLR;
                }
                break;

            case (CPUSS_INT_GROUP_IIDX_STAT_INT1):
                gpio_mis = GPIOB->CPU_INT.MIS;
                if ((gpio_mis & GPIO_CPU_INT_MIS_DIO18_MASK) == GPIO_CPU_INT_MIS_DIO18_SET)
                {
                    g_PB1_pressed = true;
                    GPIOB->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO18_CLR;
                }
                break;

            default:
                break;
        }
    } while (group_iidx_status != 0);
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function:
// 1) sets the polarity to the rising edge
// 2) clears the flag
// 3) enables masks interrupts
// for GPIOA Port 15, or PB1.
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
void config_pb1_interrupt(void)
{
    GPIOA->POLARITY15_0 = GPIO_POLARITY15_0_DIO15_RISE;
    GPIOA->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO15_CLR;
    GPIOA->CPU_INT.IMASK = GPIO_CPU_INT_IMASK_DIO15_SET;

    NVIC_SetPriority(GPIOA_INT_IRQn, 2);
    NVIC_EnableIRQ(GPIOA_INT_IRQn);
}

//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function:
// 1) sets the polarity to the rising edge
// 2) clears the flag
// 3) enables masks interrupts
// for GPIOB Port 18, or PB2.
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
void config_pb2_interrupt(void)
{
    GPIOB->POLARITY31_16 = GPIO_POLARITY31_16_DIO18_RISE;
    GPIOB->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO18_CLR;
    GPIOB->CPU_INT.IMASK = GPIO_CPU_INT_IMASK_DIO18_SET;

    NVIC_SetPriority(GPIOB_INT_IRQn, 2);
    NVIC_EnableIRQ(GPIOB_INT_IRQn);
}