//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Matthew Barry
//
//       LAB NAME:  Lab 4: Interfacing with LEDs
//
//      FILE NAME:  main.c
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//    This program is to help control pins on the LaunchPad board and the
//    expansion board. It controls the expansion board LED bar, the LaunchPad
//    LED bar, and the Launchpad 7-segment display.
//
//*****************************************************************************
//*****************************************************************************

//-----------------------------------------------------------------------------
// Loads standard C include files
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>

//-----------------------------------------------------------------------------
// Loads MSP launchpad board support macros and definitions
//-----------------------------------------------------------------------------
#include <ti/devices/msp/msp.h>
#include "clock.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/devices/msp/peripheral/hw_gpio.h"
#include "ti/devices/msp/peripheral/hw_iomux.h"


//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void run_lab4_part4(void);
void run_lab4_part5(void);
void run_lab4_part6(void);

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define inbetween       (500)

#define int_leds_on     (60)
#define p1delay         (2000)

#define p2delay         (200)

#define p3delay         (250)

#define seg7L           (56)
#define p4seg7          (0)
#define p4delay         (2000)

#define p5on            (2000)
#define p5off           (3000)
#define p5seg7          (2)
#define seg74           (102)

#define p6delay         (1)
#define seg7c           (57)
#define seg7a           (119)
#define seg7f           (113)
#define seg7e           (121)



int main(void)
{
    clock_init();
    led_init();
    led_enable();
    seg7_init();

    leds_on(int_leds_on);
    msec_delay(p1length);
    leds_off(int_leds_on);

    msec_delay(inbetween);

    while(i < 5, i = 0, i++)
    {
        for(j = 0, j < 8, j++)
        {
            led_on(led_config_data[j]);
            msec_delay(p2delay);
            led_off(led_config_data[j]);
        }

        for(k = 0, k < 6, k--)
        {
            led_on(led_config_data[k]);
            msec_delay(p2delay);
            led_off(led_config_data[k]);
        }
        
    }

    msec_delay(inbetween);

    while(i < 2, i=0, i++)
    {
        for(j = 0, j < 256, j++)
        {
            leds_on(led_config_data[j]);
            msec_delay(p3delay);
            leds_off(led_config_data[j]);
        }
    }

    msec_delay(inbetween);

    run_lab4_part4();

    msec_delay(inbetween);

    run_lab4_part5();

    msec_delay(inbetween);



} /* main */

void run_lab4_part4()
{
    seg7_on(seg7L, p4seg7);
    msec_delay(delay);
    seg7_off(seg7L, p4seg7);
}

void run_lab4_part5()
{
    while(i < 4, i = 0, i++)
    {
        seg7_on(seg74, p5seg7);
        msec_delay(p5on);
        seg7_off(seg74, p5off);
    }
    
}

void run_lab4_part6()
{
    while(i < 200, i = 0, i++)
    {
        seg7_on(seg7c, 0);
        msec_delay(p6delay);
        seg7_off(seg7c, 0);

        seg7_on(seg7a, 1);
        msec_delay(p6delay);
        seg7_off(seg7_a, 1);

        seg7_on(seg7f, 2);
        msec_delay(p6delay);
        seg7_off(seg7f);

        seg7_on(seg7e, 3);
        msec_delay(p6delay);
        seg7_off(seg7e, e);
    }
}