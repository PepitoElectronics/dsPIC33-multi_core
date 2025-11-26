/**
 * MAIN_CORE Generated Driver Source File
 * 
 * @file     main_core.c
 * 
 * @ingroup  main_coredriver
 * 
 * @brief    This is the generated driver source file for MAIN_CORE driver
 *
 * @skipline @version Firmware Driver Version 1.0.0
 *
 * @skipline @version   PLIB Version 1.2.1
 *            
 * @skipline Device : dsPIC33CH128MP508S1
*/

/*disclaimer*/

// Section: Included Files

#include <stddef.h>
#include "../main_core_types.h"
#include "../main_core_interface.h"
#include "../main_core.h"

// Section: File specific functions

extern void (*MAIN_CORE_MSI1_ProtocolAHandler)(void) = NULL;
extern void (*MAIN_CORE_MSI1_ProtocolBHandler)(void) = NULL;


// Section: Driver Interface

const struct MAIN_CORE_INTERFACE MSIInterface = {
    .Initialize                         = &MAIN_CORE_Initialize,
    .Deinitialize                       = &MAIN_CORE_Deinitialize,
    .InterruptRequestGenerate           = &MAIN_CORE_InterruptRequestGenerate,
    .IsInterruptRequestAcknowledged     = &MAIN_CORE_IsInterruptRequestAcknowledged,
    .InterruptRequestComplete           = &MAIN_CORE_InterruptRequestComplete,
    .IsInterruptRequested               = &MAIN_CORE_IsInterruptRequested,
    .InterruptRequestAcknowledge        = &MAIN_CORE_InterruptRequestAcknowledge,
    .InterruptRequestAcknowledgeComplete= &MAIN_CORE_InterruptRequestAcknowledgeComplete,
    .SystemStatusGet                    = &MAIN_CORE_SystemStatusGet,
    .FIFORead                           = &MAIN_CORE_FIFORead,
    .FIFOWrite                          = &MAIN_CORE_FIFOWrite,
    .FIFOReadIsFull                     = &MAIN_CORE_FIFOReadIsFull,
    .FIFOReadIsEmpty                    = &MAIN_CORE_FIFOReadIsEmpty,
    .FIFOWriteIsFull                    = &MAIN_CORE_FIFOWriteIsFull,
    .FIFOWriteIsEmpty                   = &MAIN_CORE_FIFOWriteIsEmpty,
    .ProtocolRead                       = &MAIN_CORE_ProtocolRead,
    .ProtocolWrite                      = &MAIN_CORE_ProtocolWrite, 
    .ProtocolIsFull                     = &MAIN_CORE_ProtocolIsFull,
    .ProtocolIsEmpty                    = &MAIN_CORE_ProtocolIsEmpty,
    .ProtocolCallbackRegister           = &MAIN_CORE_ProtocolCallbackRegister,
    .ReadFIFODataReadyCallbackRegister        = NULL,
    .WriteFIFOEmptyCallbackRegister        = NULL,
    .FIFOOverFLowUnderFlowCallbackRegister        = NULL,
    .MainInitiatedCallbackRegister        = NULL,
    .MainBreakCallbackRegister        = NULL,
    .MainResetCallbackRegister        = NULL,
};

// Section: MAIN_CORE Module APIs

void MAIN_CORE_Initialize(void)
{
    //MRSTIE disabled; MTSIACK disabled; STMIRQ disabled; RFITSEL Trigger data valid interrupt when 1st FIFO entry is written by Slave; 
    SI1CON = 0x0U;    

    MAIN_CORE_ProtocolCallbackRegister(MSI1_ProtocolA, &MAIN_CORE_MSI1_ProtocolACallback);
    MAIN_CORE_ProtocolCallbackRegister(MSI1_ProtocolB, &MAIN_CORE_MSI1_ProtocolBCallback);

    //Protocol A Interrupt Flag Clear
    IFS8bits.MSIAIF = 0U;    
    //Protocol A Interrupt Enable
    IEC8bits.MSIAIE = 1U;
    //Protocol B Interrupt Flag Clear
    IFS8bits.MSIBIF = 0U;    
    //Protocol B Interrupt Enable
    IEC8bits.MSIBIE = 1U;
}

void MAIN_CORE_Deinitialize(void)
{
    SI1CON = 0x0U;    

    //Protocol A Interrupt Disable
    IEC8bits.MSIAIE = 0U;
    //Protocol A Interrupt Flag Clear
    IFS8bits.MSIAIF = 0U;    
    //Protocol B Interrupt Disable
    IEC8bits.MSIBIE = 0U;
    //Protocol B Interrupt Flag Clear
    IFS8bits.MSIBIF = 0U;    

}

void MAIN_CORE_InterruptRequestGenerate(void)
{
    SI1CONbits.STMIRQ = 1U;
}

bool MAIN_CORE_IsInterruptRequestAcknowledged(void)
{
    return(SI1STATbits.STMIACK);
    
}

void MAIN_CORE_InterruptRequestComplete(void)
{
    SI1CONbits.STMIRQ = 0U; 
}
 
bool MAIN_CORE_IsInterruptRequested(void)
{
    return(SI1STATbits.MTSIRQ);
}
void MAIN_CORE_InterruptRequestAcknowledge(void)
{
    SI1CONbits.MTSIACK = 1U;
}

void MAIN_CORE_InterruptRequestAcknowledgeComplete(void)
{
    SI1CONbits.MTSIACK = 0U;
}
 
enum MAIN_CORE_SYSTEM_STATUS MAIN_CORE_SystemStatusGet(void)
{
    enum MAIN_CORE_SYSTEM_STATUS systemStatus = MAIN_CORE_SYSTEM_STATUS_RUNNING_STATE;
    
    if (SI1STATbits.MSTRST != 0)
    {
        systemStatus = MAIN_CORE_SYSTEM_STATUS_IN_RESET_STATE;
    }
    else
    {
        switch(SI1STATbits.MSTPWR)
        {
            case 0: systemStatus = MAIN_CORE_SYSTEM_STATUS_NOT_IN_LOW_POWER_MODE;
                    break;
            case 1: systemStatus = MAIN_CORE_SYSTEM_STATUS_IDLE_MODE;
                    break;
            case 2: systemStatus = MAIN_CORE_SYSTEM_STATUS_SLEEP_MODE;
                    break;
            default:systemStatus = MAIN_CORE_SYSTEM_STATUS_RUNNING_STATE;
                    break;             
        }
    }
    return systemStatus;
}

uint16_t MAIN_CORE_FIFORead(uint16_t *pData, uint16_t wordCount)
{
    uint16_t readCountStatus = 0U;
    
    while (wordCount != 0u)
    {
        if(!MAIN_CORE_FIFOReadIsEmpty())
        {
            *pData++ = SRMWFDATA;
            wordCount--;
            readCountStatus++;
        }
        else
        {
            break;
        }
    }
    return readCountStatus;  
}

uint16_t MAIN_CORE_FIFOWrite(uint16_t *pData, uint16_t wordCount)
{
    uint16_t writeCountStatus = 0U;
    
    while (wordCount != 0u)
    {
        if(!MAIN_CORE_FIFOWriteIsFull())
        {
            SWMRFDATA = *pData++;
            wordCount--;
            writeCountStatus++;
        }
        else
        {
            break;
        }
    }
    return writeCountStatus;
}
 
bool MAIN_CORE_ProtocolWrite(enum MAIN_CORE_PROTOCOLS protocolName, uint16_t *pData)
{
    bool status = false;
    switch(protocolName)
    {
        case MSI1_ProtocolB:
            if(MAIN_CORE_ProtocolIsEmpty(MSI1_ProtocolB))
            {
                SI1MBX1D = pData[0];
                status = true;
            }    
            else
            {
                status = false;
            }
            break;
        default:
            break; 
    }
    return status;    
}

bool MAIN_CORE_ProtocolRead(enum MAIN_CORE_PROTOCOLS protocolName, uint16_t *pData)
{
    bool status = false;   
    switch(protocolName)
    {
        case MSI1_ProtocolA:
            if(MAIN_CORE_ProtocolIsFull(MSI1_ProtocolA))
            {
                pData[0] = SI1MBX0D;

                status = true;
            }
            else
            {
                status = false;
            }
            break;
        default:
            break; 
	}
    return status;
}

void MAIN_CORE_ProtocolCallbackRegister(enum MAIN_CORE_PROTOCOLS protocolName, void (*handler)(void))
{
    switch(protocolName)
    {
        case MSI1_ProtocolA:
            if(NULL != handler)
            {
                MAIN_CORE_MSI1_ProtocolAHandler = handler;
            }
            break;
        case MSI1_ProtocolB:
            if(NULL != handler)
            {
                MAIN_CORE_MSI1_ProtocolBHandler = handler;
            }
            break;
        default:
            break;
    }
}

void __attribute__ ((weak)) MAIN_CORE_MSI1_ProtocolACallback(void)
{
    
}

/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ((interrupt, no_auto_psv)) _MSIAInterrupt(void)
{
    (*MAIN_CORE_MSI1_ProtocolAHandler)();
    IFS8bits.MSIAIF=0U;
}

void __attribute__ ((weak)) MAIN_CORE_MSI1_ProtocolBCallback(void)
{
    
}

/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ((interrupt, no_auto_psv)) _MSIBInterrupt(void)
{
    (*MAIN_CORE_MSI1_ProtocolBHandler)();
    IFS8bits.MSIBIF=0U;
}









