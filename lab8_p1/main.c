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
#include "adc.h"

//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void run_lab8_p1(void);
void config_pb1_interrupt(void);

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------
bool g_PB1_pressed;

// Define a structure to hold different data types

int main(void)
{
    clock_init_40mhz();
    config_pb1_interrupt();
    launchpad_gpio_init();
    dipsw_init();

    I2C_init();
    lcd1602_init();
    
    uint8_t vref_volts = 1;
    ADC0_init(vref_volts);

    run_lab8_p1();

} /* main */

void run_lab8_p1(void)
{
    uint8_t light_dark_threshold = 20;
    while(!g_PB1_pressed)
    {
        uint8_t channel = 7;
        uint8_t ADC_val = ADC0_in(channel);

        if(ADC_val >= light_dark_threshold)
        {
            lcd_set_ddram_addr(LCD_LINE1_ADDR);
            lcd_write_string("Status: Light");
        }    
        else 
        {
            lcd_set_ddram_addr(LCD_LINE1_ADDR);
            lcd_write_string("Status: Dark");
        }

        lcd_set_ddram_addr(LCD_LINE2_ADDR);
        lcd_write_string("ADC = ");
        lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_7);
        lcd_write_byte(ADC_val);
    }
}

void config_pb1_interrupt(void)
{
    GPIOA->POLARITY15_0 = GPIO_POLARITY15_0_DIO15_RISE;
    GPIOA->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO15_CLR;
    GPIOA->CPU_INT.IMASK = GPIO_CPU_INT_IMASK_DIO15_SET;

    NVIC_SetPriority(GPIOA_INT_IRQn, 2);
    NVIC_EnableIRQ(GPIOA_INT_IRQn);
}

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