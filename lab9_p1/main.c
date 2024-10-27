//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Matthew Barry
//
//       LAB NAME:  9 Part 1: Controlling a DC Motor
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
#include "LaunchPad.h"
#include "clock.h"


//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define CONV_FACTOR (100 / 16)
#define LOAD_VALUE          (4000)
#define DUTY_CYCLE          (2000)
#define UPDATE_DELAY        (100) 


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
    keypad_init();
    dipsw_init();
    
    motor0_init();
    motor0_pwm_init(LOAD_VALUE, 0);

} /* main */

void run_lab9_p1(void)
{
    enum motor_state 
    {
        int MOTOR_OFF1 = 0,
        int MOTOR_CW = 1,
        int MOTOR_OFF2 = 2,
        int MOTOR_CCW = 3
    }

    uint8_t duty_cycle = 0;

    motor_state = MOTOR_CCW;

    
    
    key_val = keypad_scan();
    while(!g_PB1_pressed)
    {
        switch(motor_state)
        {
            case(MOTOR_OFF1):
                motor0_pwm_disable();
                while(!g_PB2_pressed) {}
                motor_state = MOTOR_CW;
                g_PB2_pressed = false;
                break;
            
            case(MOTOR_CW):
                while(!g_PB2_pressed) 
                {
                    duty_cycle = key_val * CONV_FACTOR;
                    motor0_set_pwm_dc(duty_cycle);
                    motor0_set_pwm_count(0);
                    motor0_pwm_enable();
                }
                motor_state = MOTOR_OFF2;
                g_PB2_pressed = false;
                break;

            case(MOTOR_OFF2):
                motor0_pwm_disable();
                while(!g_PB2_pressed) {}
                motor_state = MOTOR_CCW;
                g_PB2_pressed = false;
                break;

            case(MOTOR_CCW):
                while(!g_PB2_pressed) 
                {
                    duty_cycle = key_val * CONV_FACTOR;
                    motor0_set_pwm_dc(duty_cycle);
                    motor0_set_pwm_count(0);
                    motor0_pwm_enable();
                }
                motor_state = MOTOR_OFF2;
                g_PB2_pressed = false;
                break;

            msec_delay(UPDATE_DELAY);
        }
    }
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