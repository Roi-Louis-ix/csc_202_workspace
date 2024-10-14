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
#include "lcd1602.h"
#include "LaunchPad.h"
#include "adc.h"
#include "ti/devices/msp/peripherals/hw_oa.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/devices/msp/peripherals/hw_gpio.h"
#include "ti/devices/msp/peripherals/m0p/hw_cpuss.h"
//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void run_lab8_p1(void);
void config_pb1_interrupt(void);
void OPA0_init(void);
void GROUP1_IRQHandler(void);

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define     VREF_VOLTS              (5)
#define     CHANNEL                 (6)
#define     LIGHT_DARK_THRESHOLD    (100)
#define     DELAY_TIME              (80)
#define     ADC_BITS                (4096)

//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------
bool g_PB1_pressed;
bool g_PB2_pressed;

// Define a structure to hold different data types

int main(void)
{
    clock_init_40mhz();
    config_pb1_interrupt();
    launchpad_gpio_init();
    dipsw_init();

    I2C_init();
    lcd1602_init();
    
    ADC0_init(VREF_VOLTS);
    OPA0_init();

    run_lab8_p1();

} /* main */

void run_lab8_p1(void)
{
    while(!g_PB1_pressed)
    {
        uint32_t ADC_val = ADC0_in(CHANNEL);
        lcd_clear();
        if(ADC_val >= LIGHT_DARK_THRESHOLD)
        {
            lcd_set_ddram_addr(LCD_LINE1_ADDR);
            lcd_write_string("Status: Light");
        }    
        else 
        {
            lcd_set_ddram_addr(LCD_LINE1_ADDR);
            lcd_write_string("Status: Dark ");
        }

        lcd_set_ddram_addr(LCD_LINE2_ADDR);
        lcd_write_string("ADC = ");
        lcd_set_ddram_addr(LCD_LINE2_ADDR + LCD_CHAR_POSITION_7);
        lcd_write_quadbyte(ADC_val);
        
        msec_delay(DELAY_TIME);
    }
}

void config_pb1_interrupt(void)
{
    GPIOB->POLARITY31_16 = GPIO_POLARITY31_16_DIO18_RISE;
    GPIOB->CPU_INT.ICLR = GPIO_CPU_INT_ICLR_DIO18_CLR;
    GPIOB->CPU_INT.IMASK = GPIO_CPU_INT_IMASK_DIO18_SET;

    NVIC_SetPriority(GPIOB_INT_IRQn, 2);
    NVIC_EnableIRQ(GPIOB_INT_IRQn);
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

void OPA0_init(void)
{
    OPA0->GPRCM.RSTCTL = (OA_RSTCTL_KEY_UNLOCK_W | OA_RSTCTL_RESETSTKYCLR_CLR |
                          OA_RSTCTL_RESETASSERT_ASSERT);

    OPA0->GPRCM.PWREN = (OA_PWREN_KEY_UNLOCK_W | OA_PWREN_ENABLE_ENABLE);

    // time for OPA to power up
    clock_delay(24);

    OPA0->CFGBASE &= ~(OA_CFGBASE_RRI_MASK);

    OPA0->CFGBASE |= ((uint32_t) OA_CFGBASE_GBW_HIGHGAIN);

    OPA0->CFG |= (OA_CFG_GAIN_MINIMUM | OA_CFG_MSEL_NC | OA_CFG_NSEL_EXTPIN0 |
                  OA_CFG_PSEL_EXTPIN0 | OA_CFG_OUTPIN_ENABLED |
                  OA_CFG_CHOP_OFF);

    OPA0->CTL |= OA_CTL_ENABLE_ON;

}