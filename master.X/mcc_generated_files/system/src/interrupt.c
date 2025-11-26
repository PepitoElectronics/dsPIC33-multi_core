/**
 * INTERRUPT Generated Driver Source File 
 * 
 * @file      interrupt.c
 *            
 * @ingroup   interruptdriver
 *            
 * @brief     This is the generated driver source file for INTERRUPT driver
 *            
 * @skipline @version   Firmware Driver Version 1.1.2
 *
 * @skipline @version   PLIB Version 1.4.2
 *            
 * @skipline  Device : dsPIC33CH64MP502
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
#include "../interrupt.h"

// Section: Driver Interface Function Definitions

void INTERRUPT_Initialize(void)
{
    // DMT: Dead Man Timer
    // Priority: 1
    IPC11bits.DMTIP = 1;
    
    // MSIA: MSI Protocol A
    // Priority: 1
    IPC32bits.MSIAIP = 1;
    
    // MSIB: MSI Protocol B
    // Priority: 1
    IPC32bits.MSIBIP = 1;
    
    // MSIDT: MSI Master Read FIFO Data Ready
    // Priority: 1
    IPC34bits.MSIDTIP = 1;
    
    // MSIFLT: MSI Master R/W FIFO Over/Underflow
    // Priority: 1
    IPC35bits.MSIFLTIP = 1;
    
    // MSIS1: MSI Slave Initiated
    // Priority: 1
    IPC32bits.MSIS1IP = 1;
    
    // MSIWFE: MSI Master Write FIFO Empty
    // Priority: 1
    IPC34bits.MSIWFEIP = 1;
    
    // S1BRK: Slave Break
    // Priority: 1
    IPC36bits.S1BRKIP = 1;
    
    // S1RST: MSI Slave Reset
    // Priority: 1
    IPC35bits.S1RSTIP = 1;
    
}

void INTERRUPT_Deinitialize(void)
{
    //POR default value of priority
    IPC11bits.DMTIP = 4;
    IPC32bits.MSIAIP = 4;
    IPC32bits.MSIBIP = 4;
    IPC34bits.MSIDTIP = 4;
    IPC35bits.MSIFLTIP = 4;
    IPC32bits.MSIS1IP = 4;
    IPC34bits.MSIWFEIP = 4;
    IPC36bits.S1BRKIP = 4;
    IPC35bits.S1RSTIP = 4;
}
