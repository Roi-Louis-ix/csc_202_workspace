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
void run_lab4_part1();
void run_lab4_part2();
void run_lab4_part3();
void run_lab4_part4();
void run_lab4_part5();
void run_lab4_part6();

//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
#define In_Between      (500)

#define Int_LEDs_On     (60)
#define P1_Delay        (2000)
#define numofLEDs       (8)

#define p2delay         (50)

#define p3delay         (50)

#define seg7L           (56)
#define p4seg7          (0)
#define p4delay         (2000)

#define p5on            (3000)
#define p5off           (2000)
#define p5seg7          (2)
#define seg74           (102)

#define p6delay         (1)
#define seg7c           (57)
#define seg7a           (119)
#define seg7f           (113)
#define seg7e           (121)




int main(void)
{
    clock_init_40mhz();
    launchpad_gpio_init();
    led_init();
    led_enable();
    seg7_init();

    run_lab4_part1();

    run_lab4_part2();    

    run_lab4_part3();

    run_lab4_part4();

    run_lab4_part5();    

    run_lab4_part6();    

} /* main */

void run_lab4_part1()
{
    leds_on(Int_LEDs_On);
    msec_delay(P1_Delay);
    leds_off();

    msec_delay(In_Between);
}
void run_lab4_part2()
{
    uint8_t loop_count = 0;
    uint8_t p2iterations = 10;
    while(loop_count < p2iterations)
    {
        uint8_t countup_index = 0;
        uint8_t start_countup_loop = 0;
        uint8_t end_countup_loop = 8;
        for(countup_index = start_countup_loop; countup_index < end_countup_loop; countup_index++)
        {
            led_on(countup_index);
            msec_delay(p2delay);
            led_off(countup_index);
        }

        uint8_t countdown_index = 0;
        uint8_t start_countdown_loop = 6;
        uint8_t end_countdown_loop = 0;
        for(countdown_index = start_countdown_loop; countdown_index > end_countdown_loop; countdown_index--)
        {
            led_on(countdown_index);
            msec_delay(p2delay);
            led_off(countdown_index);
        }
        
        loop_count ++;
        
    }

    msec_delay(In_Between);
}

void run_lab4_part3()
{
    uint8_t loop_count = 0;
    uint16_t p3iterations = 2;

    while(loop_count < p3iterations)
    {
        uint16_t countup_index = 0;
        uint16_t start_countup_loop = 0;
        uint16_t end_countup_loop = 256;

        for(countup_index = start_countup_loop; countup_index < end_countup_loop; countup_index++)
        {
            leds_on(countup_index);
            msec_delay(p3delay);
            leds_off();
        }
        loop_count++;
        
    }
    msec_delay(In_Between);

}

void run_lab4_part4()
{
    led_disable();

    seg7_on(seg7L, SEG7_DIG0_ENABLE_IDX);
    msec_delay(p4delay);
    seg7_off();

    msec_delay(In_Between);
}

void run_lab4_part5()
{
    uint8_t loop_count = 0;
    uint8_t p5iterations = 4;
    
    while(loop_count < p5iterations)
    {
        seg7_on(seg74, SEG7_DIG2_ENABLE_IDX);
        msec_delay(p5on);
        seg7_off();
        msec_delay(p5off);

        loop_count++;
    }
    msec_delay(In_Between);
    
}


void run_lab4_part6()
{
    uint8_t loop_count = 0;
    uint8_t p6iterations = 200;
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
    msec_delay(In_Between);
}