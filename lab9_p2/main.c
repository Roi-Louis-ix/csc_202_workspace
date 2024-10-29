//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Matthew Barry
//
//       LAB NAME:  9 Part 2: The Lab Heats Up
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
#include "adc.h"
#include "lcd1602.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/devices/msp/peripherals/hw_gpio.h"
#include "ti/devices/msp/peripherals/m0p/hw_cpuss.h"

//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void run_lab9_p2();
void GROUP1_IRQHandler();
void config_pb1_interrupt();
void config_pb2_interrupt();
void OPA0_init();
uint8_t celsius_to_fahrenheit(uint8_t celsius);


//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define NUM_STATES              (9)
#define ADC_RANGE            (4096)
#define STATE_RANGE           (455)
#define CHANNEL                 (7)
#define PTC_CHANNEL             (5)
#define DEG_SYMBOL_ASCII     (0xDF)
#define C_F_CONV_FACTOR       (9/5)
#define C_0DEG_IN_F            (32)
#define LOAD_VALUE           (4000)
#define THRESHOLD_TEMP         (70) //At this temp, switch from 25% to 80%
#define LOOP_TIME             (250) //.25 seconds between each iteration
#define HIGH_DUTY_CYCLE        (80)
#define LOW_DUTY_CYCLE         (25)

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
    launchpad_gpio_init();
    dipsw_init();

    I2C_init();
    lcd1602_init();

    config_pb1_interrupt();
    config_pb2_interrupt();

    ADC0_init(ADC12_MEMCTL_VRSEL_VDDA_VSSA);
    lcd_clear();
    motor0_init();
    motor0_pwm_init(LOAD_VALUE, 0);

    run_lab9_p2();

    char msg[] = "Program Stopped";
    lcd_clear();
    lcd_set_ddram_addr(LCD_LINE1_ADDR);
    lcd_write_string(msg);
} /* main */

void run_lab9_p2(void)
{
    while(!g_PB1_pressed)
    {
        uint16_t raw_temp = ADC0_in(PTC_CHANNEL);
        uint8_t temp = thermistor_calc_temperature(raw_temp);
        uint8_t temp_f = celsius_to_fahrenheit(temp);

        if(temp_f > THRESHOLD_TEMP)
        {
            motor0_set_pwm_dc(HIGH_DUTY_CYCLE);
            lcd_set_ddram_addr(LCD_LINE2_ADDR);
            lcd_write_string("SPEED = ");
            lcd_write_byte(HIGH_DUTY_CYCLE);
            lcd_write_string("%");
        }
        else 
        {
            motor0_set_pwm_dc(LOW_DUTY_CYCLE);
            lcd_set_ddram_addr(LCD_LINE2_ADDR);
            lcd_write_string("SPEED = ");
            lcd_write_byte(LOW_DUTY_CYCLE);
            lcd_write_string("%");
        }

        lcd_set_ddram_addr(LCD_LINE1_ADDR + LCD_CHAR_POSITION_1);
        lcd_write_string("Temp  =");
        lcd_write_doublebyte(temp_f);
        lcd_write_char(DEG_SYMBOL_ASCII);
        lcd_write_string("F");
        
        msec_delay(LOOP_TIME);
    }
    
}

uint8_t celsius_to_fahrenheit(uint8_t celsius)
{
    uint8_t temp_f = 0;
    temp_f = celsius * 9 / 5 + C_0DEG_IN_F;
    return(temp_f);
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