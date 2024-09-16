//*****************************************************************************
//*****************************    C Source Code    ***************************
//*****************************************************************************
//  DESIGNER NAME:  Matthew Barry
//
//       LAB NAME:  Lab 4 Part 1: Interfacing with LEDs
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


//-----------------------------------------------------------------------------
// Define symbolic constants used by the program
//-----------------------------------------------------------------------------
//Define the configuration data for the LEDs on the CSC202 Board
const gpio_struct led_config_data[] = {
    {LED0_PORT, LED0_MASK, LED0_IOMUX, LED0_LOW},
    {LED1_PORT, LED1_MASK, LED1_IOMUX, LED1_LOW},
    {LED2_PORT, LED2_MASK, LED2_IOMUX, LED2_LOW},
    {LED3_PORT, LED3_MASK, LED3_IOMUX, LED3_LOW},
    {LED4_PORT, LED4_MASK, LED4_IOMUX, LED4_LOW},
    {LED5_PORT, LED5_MASK, LED5_IOMUX, LED5_LOW},
    {LED6_PORT, LED6_MASK, LED6_IOMUX, LED6_LOW},
    {LED7_PORT, LED7_MASK, LED7_IOMUX, LED7_LOW},
};

GPIOA->GPRCM.RSTCTL = (GPIO_RSTCLT_KEY_UNLOCK_W |
                       GPIO_RSTCTL_RESETSTKYCLR_CLR |
                       GPIO_RSTCTL_RESETASSERT_ASSERT);

GPIOB->GPRCM.RSTCTL = (GPIO_RSTCLT_KEY_UNLOCK_W |
                       GPIO_RSTCTL_RESETSTKYCLR_CLR |
                       GPIO_RSTCTL_RESETASSERT_ASSERT);

GPIOA->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);
GPIOB->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);

IOMUX->SECCFG.PINCM[IOMUX_PINCM3]  = IOMUX_PINCM_PC_CONNECTED |
                                     IOMUX_PINCM1_PF_GPIOA_DIO28;

IOMUX->SECCFG.PINCM[IOMUX_PINCM6]  = IOMUX_PINCM_PC_CONNECTED |
                                     IOMUX_PINCM57_PF_GPIOA_DIO31;

IOMUX->SECCFG.PINCM[IOMUX_PINCM42] = IOMUX_PINCM_PC_CONNECTED |
                                     IOMUX_PINCM58_PF_GPIOA_DIO20;

IOMUX->SECCFG.PINCM[IOMUX_PINCM30] = IOMUX_PINCM_PC_CONNECTED |
                                     IOMUX_PINCM50_PF_GPIOB_DIO13;

IOMUX->SECCFG.PINCM[IOMUX_PINCM34] = IOMUX_PINCM_PC_CONNECTED |
                                     IOMUX_PINCM1_PF_GPIOA_DIO12;

IOMUX->SECCFG.PINCM[IOMUX_PINCM35] = IOMUX_PINCM_PC_CONNECTED |
                                     IOMUX_PINCM1_PF_GPIOA_DIO13;

IOMUX->SECCFG.PINCM[IOMUX_PINCM38] = IOMUX_PINCM_PC_CONNECTED |
                                     IOMUX_PINCM1_PF_GPIOA_DIO16;

IOMUX->SECCFG.PINCM[IOMUX_PINCM39] = IOMUX_PINCM_PC_CONNECTED |
                                     IOMUX_PINCM1_PF_GPIOA_DIO17;


//-----------------------------------------------------------------------------
// Define global variables and structures here.
// NOTE: when possible avoid using global variables
//-----------------------------------------------------------------------------


// Define a structure to hold different data types

typedef struct {
    uint8_t     port_id;
    uint32_t    bit_mask;
    uint16_t    pin_cm;
    uint8_t     polarity;
}

int main(void)
{
  GPIOA->DOUT31_0 |= GPIO_DOUT31_0_DIO20_MASK | GPIO_DOUT31_0_DIO13_MASK | GPIO_DOUT31_0_DIO12_MASK;
  GPIOB->DOUT31_0 |= GPIO_DOUT31_0_DIO13_MASK;
  for(uint8_1 loop_cntr = 0; loop_cntr < 10; loop_cntr++)
  {
    GPIOA->DOUT31_0 |= GPIO_DOUT31_0_DIO0_MASK;
    msec_delay(500);

  }


  
  
} /* main */

