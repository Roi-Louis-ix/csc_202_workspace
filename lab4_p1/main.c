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
#include "LaunchPad.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/devices/msp/peripherals/hw_gpio.h"
#include "ti/devices/msp/peripherals/hw_iomux.h"



//-----------------------------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------------------------
void run_lab4_part4(uint8_t loop_count);
void run_lab4_part5(uint8_t loop_count);
void run_lab4_part6(uint8_t loop_count);

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define inbetween       (500)

#define int_leds_on     (60)
#define p1delay         (2000)
#define numofLEDs       (8)

#define p2delay         (200)

#define p3delay         (250)

#define seg7L           (56)
#define p4seg7          (0)
#define p4delay         (2000)

#define p5on            (2000)
#define p5off           (3000)
#define p5seg7          (2)
#define seg74           (102)
#define p5iterations    (4)

#define p6delay         (1)
#define p6iterations    (200)
#define seg7c           (57)
#define seg7a           (119)
#define seg7f           (113)
#define seg7e           (121)




int main(void)
{
    clock_init_40mhz();
    led_init();
    led_enable();
    seg7_init();

    leds_on(int_leds_on);
    msec_delay(p1delay);
    leds_off();

    msec_delay(inbetween);

    uint8_t loop_count = 0;
    uint8_t p2iterations = 10;
    while(loop_count < p2iterations)
    {
        for(loop_count = 0; loop_count < numofLEDs; loop_count++)
        {
            led_on(loop_count);
            msec_delay(p2delay);
            led_off(loop_count);
        }

        for(loop_count = 0; loop_count < numofLEDs; loop_count--)
        {
            led_on(loop_count);
            msec_delay(p2delay);
            led_off(loop_count);
        }
        
        loop_count += 1;
        
    }

    loop_count = 0;

    msec_delay(inbetween);

    uint8_t p3iterations = 0;

    while(loop_count < p3iterations)
    {
        leds_on(loop_count);
        msec_delay(p3delay);
        leds_off();
        loop_count += 1;
    }

    loop_count = 0;

    msec_delay(inbetween);

    run_lab4_part4(loop_count);
    loop_count = 0;

    msec_delay(inbetween);

    run_lab4_part5(loop_count);
    loop_count = 0;

    msec_delay(inbetween);

    run_lab4_part6(loop_count);
    loop_count = 0;


} /* main */

void run_lab4_part4(uint8_t loop_count)
{
    seg7_on(seg7L, SEG7_DIG0_ENABLE_IDX);
    msec_delay(p4delay);
    seg7_off();
}

void run_lab4_part5(uint8_t loop_count)
{
    while(loop_count < p5iterations)
    {
        seg7_on(seg74, SEG7_DIG2_ENABLE_IDX);
        msec_delay(p5on);
        seg7_off();

        loop_count += 1;
    }
    
}

void run_lab4_part6(uint8_t loop_count)
{
    while(loop_count < p6iterations)
    {
        seg7_on(seg7c, SEG7_DIG0_ENABLE_IDX);
        msec_delay(p6delay);
        seg7_off();

        seg7_on(seg7a, SEG7_DIG1_ENABLE_IDX);
        msec_delay(p6delay);
        seg7_off();

        seg7_on(seg7f, SEG7_DIG2_ENABLE_IDX);
        msec_delay(p6delay);
        seg7_off();

        seg7_on(seg7e, SEG7_DIG3_ENABLE_IDX);
        msec_delay(p6delay);
        seg7_off();

        loop_count += 1;
        
    }
}