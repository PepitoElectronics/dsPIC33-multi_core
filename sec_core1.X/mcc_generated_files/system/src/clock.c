/**
 * CLOCK Generated Driver Source File 
 * 
 * @file      clock.c
 *            
 * @ingroup   clockdriver
 *            
 * @brief     This is the generated source file for CLOCK driver
 *
 * @skipline @version   PLIB Version 1.4.4
 *
 * @skipline  Device : dsPIC33CH64MP502S1
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

// Section: Includes
#include <xc.h>
#include <stdint.h>
#include "../clock.h"

#define OSC_SOURCE_FRC 0U
#define OSC_SOURCE_FRC_PLL 0x1U
#define OSC_SOURCE_POSC_PLL 0x3U
#define OSCCONH_NOSC_MASK 0x07U

void CLOCK_Initialize(void)
{
    //If PLL derived clock sources are used, then switch to FRC clock before changing PLL related settings
    if(OSCCONbits.COSC == OSC_SOURCE_FRC_PLL || OSCCONbits.COSC == OSC_SOURCE_POSC_PLL)
    {
        //Set to FRC clock if current clock is not FRC
        __builtin_write_OSCCONH((OSCCONH & ~ OSCCONH_NOSC_MASK) | OSC_SOURCE_FRC);
        __builtin_write_OSCCONL((uint8_t) (0x01));
        // Wait for Clock switch to occur
        while (OSCCONbits.OSWEN != 0){}
        while (OSCCONbits.LOCK != 1){}
    }
    // RCDIV FRC/1; PLLPRE 1:1; DOZE 1:8; DOZEN disabled; ROI disabled; 
   CLKDIV = 0x3001U;
    // PLLDIV 150; 
   PLLFBD = 0x96U;
    // PLLPOST 1:4; VCODIV FVCO/4; POST2DIV 1:1; 
   PLLDIV = 0x41U;
    // ENAPLL disabled; FRCSEL FRC Oscillator; APLLPRE 1:1; 
   ACLKCON1 = 0x101U;
    // APLLFBDIV 150; 
   APLLFBD1 = 0x96U;
    // APSTSCLR 1:4; APOST2DIV 1:1; AVCODIV FVCO/4; 
   APLLDIV1 = 0x41U;
    // ROEN disabled; DIVSWEN disabled; ROSLP disabled; ROSEL ; OE disabled; ROSIDL disabled; 
   REFOCONL = 0x0U;
    // RODIV 0; 
   REFOCONH = 0x0U;
    // ROTRIM 0; 
   REFOTRIMH = 0x0U;
    // IOLOCK disabled; 
   RPCON = 0x0U;
    // ADC1MD enabled; T1MD enabled; U1MD enabled; SPI1MD enabled; QEIMD enabled; PWMMD enabled; I2C1MD enabled; 
   PMD1 = 0x0U;
    // CCP2MD enabled; CCP1MD enabled; CCP4MD enabled; CCP3MD enabled; 
   PMD2 = 0x0U;
    // REFOMD enabled; 
   PMD4 = 0x0U;
    // DMA1MD enabled; DMA0MD enabled; 
   PMD6 = 0x0U;
    // CMP1MD enabled; CMP3MD enabled; PGA1MD enabled; CMP2MD enabled; 
   PMD7 = 0x0U;
    // CLC3MD enabled; CLC4MD enabled; CLC1MD enabled; CLC2MD enabled; PGA2MD enabled; PGA3MD enabled; 
   PMD8 = 0x0U;
    /*  
       Input frequency                               :  8.00 MHz
       Clock source                                  :  FRC Oscillator with Postscaler
       System frequency (Fosc)                       :  8.00 MHz [8.00 MHz / 1 =  8.00 MHz]
       Clock switching enabled                       :  false
       Auxiliary clock source                        :  FRC Oscillator
       Auxiliary clock input frequency               :  8.00 MHz
       Auxiliary clock PLL output frequency (AFpllo) :  8.00 MHz
    */
    // CF no clock failure; NOSC FRCDIV; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x07));
    __builtin_write_OSCCONL((uint8_t) (0x00));
}

bool CLOCK_AuxPllLockStatusGet(void)
{
    return ACLKCON1bits.APLLCK;
}

