//*****************************************************************************
//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//
//  DESIGNER NAME:  Matthew Barry
//
//       LAB NAME:  Lab 3, part 1
//
//      FILE NAME:  Lab3p1_main.c
//
//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//    This program serves as a practice exercise for students to implement 
//    bitwise operations in C. It includes a series of problems, each 
//    requiring the manipulation of bits in a test register using bitwise 
//    operations. The program initializes the UART communication, sets up 
//    the system clock, and provides a function 'msp_printf' to print 
//    messages over UART. 
//
//    Each problem is outlined with a description, and students are instructed 
//    to write code to solve the problem within the designated sections. 
//    Upon execution, the program demonstrates the effect of various 
//    bitwise operations on the test register, along with the corresponding 
//    output messages indicating the results of each operation. After 
//    completing all the problems, the program terminates.
//
//*****************************************************************************
//*****************************************************************************

//-----------------------------------------------------------------------------
// Loads standard C include files
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------
// Loads MSP launchpad board support macros and definitions
//-----------------------------------------------------------------------------
#include <ti/devices/msp/msp.h>
#include "clock.h"
#include "uart.h"

//-----------------------------------------------------------
// Define function prototypes used by the program
//-----------------------------------------------------------
void msp_printf(char* buffer, unsigned int value);
int uint16_t_set_bit(uint16_t reg_value, uint16_t bit_mask);
int uint16_t_clear_bit(uint16_t reg_value, uint16_t bit_mask);
bool check_bit(uint16_t reg_value, uint16_t bit_mask);
//-----------------------------------------------------------------------------
// Define symbolic constants used by program
//-----------------------------------------------------------------------------
#define PIE_MASK       (1 << 0) 
#define EME_MASK       (1 << 1) 
#define RD_MASK        (1 << 2) 
#define MD_MASK        (1 << 3) 
#define CRS_MASK       (7 << 4) 
#define CRS_MASK       (7 << 4) 
#define MODE_MASK      (3 << 7) 
#define MODE_10_MASK   (1 << 8)
#define MODE_01_MASK   (1 << 7)
#define PRS_MASK       (7 << 9) 
#define A0_MASK        (1 << 12) 
#define A1_MASK        (1 << 13)
#define A2_MASK        (1 << 14)
#define A3_MASK        (1 << 15)

//-----------------------------------------------------------------------------
// Define global variable and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------

uint16_t test_reg16 = 0x0000;


int main(void)
{
  // create local variable to hold register value
  uint16_t reg_value;
  
  clock_init_40mhz();
  UART_init(115200);

  msp_printf(" *** PROGRAM RUNNING ***\r\n\r\n",0);
  msp_printf("CSC-202 ARM M0+ C Bitwise Test Program\r\n",0);
  msp_printf("--------------------------------------------------------\r\n",0);

  // Display the size of the test register
  msp_printf(" The size of the test reg is 0x%X bytes\r\n", sizeof(test_reg16));

  // Display the value of the test register
  msp_printf("The starting value of test reg is 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 1: Set the PIE bit in test register (test_reg16)
  // ***************************************************************************
  msp_printf("PROBLEM 1: Setting PIE bit\r\n", 0);

  reg_value = test_reg16;
  reg_value = uint16_t_set_bit(reg_value, PIE_MASK);
  test_reg16 = reg_value;

  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 2: Set the RD bit in test register
  // ***************************************************************************
  msp_printf("PROBLEM 2: Setting RD bit\r\n", 0);

  // enter your code here for problem 2

  reg_value = test_reg16;
  reg_value = uint16_t_set_bit(reg_value, RD_MASK);
  test_reg16 = reg_value;

  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 3: Set the CRS bits in test register
  // ***************************************************************************
  msp_printf("PROBLEM 3: Setting CRS bits\r\n", 0);

  // enter your code here for problem 3
  
  reg_value = test_reg16;
  reg_value = uint16_t_set_bit(reg_value, CRS_MASK);
  test_reg16 = reg_value;

  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 4: Set the A[3:0] bits in test register
  // ***************************************************************************
  msp_printf("PROBLEM 4: Setting A[3:0] bits\r\n", 0);

  // enter your code here for problem 4

  reg_value = test_reg16;
  reg_value = uint16_t_set_bit(reg_value, A3_MASK);
  reg_value = uint16_t_set_bit(reg_value, A2_MASK);
  reg_value = uint16_t_set_bit(reg_value, A1_MASK);
  reg_value = uint16_t_set_bit(reg_value, A0_MASK);
  test_reg16 = reg_value;

  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 5: Use an IF statement to test it A2 bit is set
  //            if A2 = 1 then print "Bit A2 is 1"
  //            else print "The bit A2 is 0"
  // ***************************************************************************
  msp_printf("PROBLEM 5: Testing bit A2\r\n", 0);

  // enter your code here for problem 5

  reg_value = test_reg16;
  if(check_bit(reg_value, A2_MASK))
  {
    msp_printf("Bit A2 is 1\r\n", 0);
  }
  else
  {
    msp_printf("Bit A2 is 0\r\n", 0);
  }
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 6: Clear A2 bit in test register
  // ***************************************************************************
  msp_printf("PROBLEM 6: Clearing A[2] bit\r\n", 0);

  // enter your code here for problem 6
  
  reg_value = test_reg16;
  reg_value = uint16_t_clear_bit(reg_value, A2_MASK);
  test_reg16 = reg_value;

  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 7: Clear CRS bits and set PRS bits in test register
  // ***************************************************************************
  msp_printf("PROBLEM 7: Clear CRS bits and set PRS bits\r\n", 0);

  // enter your code here for problem 7

  reg_value = test_reg16;
  reg_value = uint16_t_clear_bit(reg_value, CRS_MASK);
  reg_value = uint16_t_set_bit(reg_value, PRS_MASK);
  test_reg16 = reg_value;

  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 8: Use an IF statement to test if A2 is set
  //            if A2 = 1 then
  //                print "Bit A2=1 so clearing it"
  //                modify the reg to clear the bit
  //            else
  //                print "Bit A2=0 so setting it"
  //                modify the reg to set the bit
  // ***************************************************************************
  msp_printf("PROBLEM 8: Testing bit A2\r\n", 0);

  // enter your code here for problem 8

  reg_value = test_reg16;
  if(check_bit(reg_value, A2_MASK))
  {
    msp_printf("Bit A2=1 so clearing it\r\n", 0);
    reg_value = uint16_t_clear_bit(reg_value, A2_MASK);
    test_reg16 = reg_value;
  }
  else {
    msp_printf("Bit A2=0 so setting it\r\n", 0);
    reg_value = uint16_t_set_bit(reg_value, A2_MASK);
    test_reg16 = reg_value;
  }
  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 9: Use an IF statement to test it MD is 0
  //            if MD = 0 then
  //                print "Bit MD=0, setting mode=10"
  //                set MODE to 10
  //            else
  //                print "Bit MD=1, setting mode=11"
  //                set MODE to 11
  // ***************************************************************************
  msp_printf("PROBLEM 9: Testing bit MD & setting mode bits\r\n", 0);

  // enter your code here for problem 8

  reg_value = test_reg16;
  if(~check_bit(reg_value,MD_MASK))
  {
    msp_printf("Bit MD=0, setting mode=10\r\n", 0);
    reg_value = uint16_t_set_bit(reg_value, MODE_10_MASK);
    reg_value = uint16_t_clear_bit(reg_value, MODE_01_MASK);
    test_reg16 = reg_value;
  }
  else {
    msp_printf("Bit MD=1, setting mode=11", 0);
    reg_value = uint16_t_set_bit(reg_value, MODE_MASK);
    test_reg16 = reg_value;
  }

  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  // ***************************************************************************
  // PROBLEM 10: Clear all bits in test register
  // ***************************************************************************
  msp_printf("PROBLEM 10: Clearing all bits\r\n", 0);

  // enter your code here for problem 1

  reg_value = test_reg16;
  reg_value = uint16_t_clear_bit(reg_value,0xFFFF);
  test_reg16 = reg_value;

  msp_printf("    --> Test reg = 0x%04X\r\n", test_reg16);
  msp_printf("\r\n",0);;


  msp_printf(" *** PROGRAM TERMINATED ***\r\n",0);
  
  for(;;);

} /* main */


//-----------------------------------------------------------------------------
// DESCRIPTION:
//  This function sets the specified bit(s) in a 16-bit register value using
//  the provided bit mask. It performs a bitwise OR operation to set the bit(s).
//
// INPUT PARAMETERS:
//  reg_value - The original 16-bit register value.
//  bit_mask  - The bit mask indicating which bit(s) to clear.
//
// OUTPUT PARAMETERS:
//  none
//
// RETURN:
//  uint16_t - The modified register value with the specified bit(s) set.
// -----------------------------------------------------------------------------
int uint16_t_set_bit(uint16_t reg_value, uint16_t bit_mask)
{
    reg_value |= bit_mask;
    return (reg_value);

}



//-----------------------------------------------------------------------------
// DESCRIPTION:
//  This function clears the specified bit(s) in a 16-bit register value using
//  the provided bit mask. It performs a bitwise AND operation with the
//  complement of the bit mask to clear the bit(s).
//
// INPUT PARAMETERS:
//  reg_value - The original 16-bit register value.
//  bit_mask  - The bit mask indicating which bit(s) to clear.
//
// OUTPUT PARAMETERS:
//  none
//
// RETURN:
//  uint16_t - The modified register value with the specified bit(s) cleared.
// -----------------------------------------------------------------------------
int uint16_t_clear_bit(uint16_t reg_value, uint16_t bit_mask)
{
    reg_value &= ~bit_mask;
    return (reg_value);

}


//-----------------------------------------------------------------------------
// DESCRIPTION:
//  This function checks if the specified bit(s) in a 16-bit register value are
//  set using the provided bit mask. It performs a bitwise AND operation to 
//  verify if the bit(s) are set.
//
// INPUT PARAMETERS:
//  reg_value - a 16-bit register value to check.
//  bit_mask  - a 16-bit mask indicating which bit(s) to check.
//
// OUTPUT PARAMETERS:
//  none
//
// RETURN:
//  bool - true if the specified bit(s) are set, false otherwise.
// -----------------------------------------------------------------------------

bool check_bit(uint16_t reg_value,uint16_t bit_mask)
{
    if((reg_value & bit_mask) == bit_mask)
    {
        return true;
    }
    else 
    {
        return false;
    }
}


//-------------------------------------------------------------
// buffer: A format string used to format the integer value. It follows the format specifiers used by 'sprintf'.
// value: The integer value to be formatted and included in the formatted string.
//
// OUTPUT PARAMETERS:
// none
//
//RETURN:
// none
//------------------------------------------------------------

void msp_printf(char* buffer, unsigned int value)
{
    unsigned int i = 0;
    unsigned int len = 0;
    char    string[80];

    len = sprintf(string, buffer, value);

    //Walk through array to send each character to serial port
    for (i = 0; i< len; i++)
    {
        UART_out_char(string[i]);
    } /* for */

} /* msp printf */
