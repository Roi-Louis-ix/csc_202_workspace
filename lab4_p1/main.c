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
#define In_Between       (500)    //Time between parts

#define Int_LEDs_On      (60)     //Corresponds to bits 2-5 being active
#define P1_Delay         (2000)   //Length of Part 1 in ms

#define P2_Delay         (200)    //Time of each LED in Part 2 in ms

#define P3_Delay         (250)    //Time of each LED in Part 3 in ms

#define Seg7_L           (56)     //Corresponds to the 7-segment code for L
#define P4_Delay         (2000)   //Length of Part 4 in ms

#define P5_On            (3000)   //7seg display on time in ms
#define P5_Off           (2000)   //7seg display off time in ms
#define Seg7_4           (102)    //Corresponds to the 7-segment code for 4

#define P6_Delay         (1)      //Time of each 7seg display in Part 6
#define Seg7_C           (57)     //Corresponds to the 7-segment code for C,
#define Seg7_A           (119)    //A,
#define Seg7_F           (113)    //F,
#define Seg7_E           (121)    //E




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


//-----------------------------------------------------------------------------
// DESCRIPTION:
//  This function activates bits 2-5 based on Int_LEDs_On for a length of 
//  P1_Delay milliseconds.
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
void run_lab4_part1()
{
    leds_on(Int_LEDs_On);
    msec_delay(P1_Delay);
    leds_off();

    msec_delay(In_Between);
}


//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function activates LEDs 0 through 7 10 times. 
//  
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
void run_lab4_part2()
{
    uint8_t loop_count = 0;
    uint8_t p2iterations = 10;
    while(loop_count < p2iterations)
    {
        uint8_t countup_index = 0;
        uint8_t start_countup_loop = 0;
        uint8_t end_countup_loop = 8;
        for(
            countup_index = start_countup_loop;
            countup_index < end_countup_loop; 
            countup_index++
            )
        {
            led_on(countup_index);
            msec_delay(P2_Delay);
            led_off(countup_index);
        }

        uint8_t countdown_index = 0;
        uint8_t start_countdown_loop = 6;
        uint8_t end_countdown_loop = 0;
        for(
            countdown_index = start_countdown_loop; 
            countdown_index > end_countdown_loop; 
            countdown_index--
            )
        {
            led_on(countdown_index);
            msec_delay(P2_Delay);
            led_off(countdown_index);
        }
        
        loop_count ++;
        
    }

    msec_delay(In_Between);
}


//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function displays a binary counter from 0-255 on LEDs 0 through 7. 
//  
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
            msec_delay(P3_Delayelay);
            leds_off();
        }
        loop_count++;
        
    }
    msec_delay(In_Between);

}


//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function displays the letter L on 7seg display 0 for a period of 
// P4_Delay ms.
//  
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
void run_lab4_part4()
{
    led_disable();

    seg7_on(Seg7_L, SEG7_DIG0_ENABLE_IDX);
    msec_delay(P4_Delay);
    seg7_off();

    msec_delay(In_Between);
}


//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function flashes the number 4 on 7seg display 4 times; on for a period
// of P5_On ms and off for a period of P5_Off ms.  
//  
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
void run_lab4_part5()
{
    uint8_t loop_count = 0;
    uint8_t p5iterations = 4;
    
    while(loop_count < p5iterations)
    {
        seg7_on(Seg7_4, SEG7_DIG2_ENABLE_IDX);
        msec_delay(P5_On);
        seg7_off();
        msec_delay(P5_Off);

        loop_count++;
    }
    msec_delay(In_Between);
    
}


//-----------------------------------------------------------------------------
// DESCRIPTION:
// This function multiplexes between 7seg displays 0 and 3 to display the word
// "CAFE". It cycles between the displays 200 times with each letter being
// displayed for 1 ms. 
//  
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
void run_lab4_part6()
{
    uint8_t loop_count = 0;
    uint8_t p6iterations = 200;
    while(loop_count < p6iterations)
    {
        seg7_on(Seg7_C, SEG7_DIG0_ENABLE_IDX);
        msec_delay(P6_Delay);
        seg7_off();

        seg7_on(Seg7_A, SEG7_DIG1_ENABLE_IDX);
        msec_delay(P6_Delay);
        seg7_off();

        seg7_on(Seg7_F, SEG7_DIG2_ENABLE_IDX);
        msec_delay(P6_Delay);
        seg7_off();

        seg7_on(Seg7_E, SEG7_DIG3_ENABLE_IDX);
        msec_delay(P6_Delay);
        seg7_off();

        loop_count += 1;
        
    }
    msec_delay(In_Between);
}