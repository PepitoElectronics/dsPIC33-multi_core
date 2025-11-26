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
#define FCY 4000000UL  // 4 MHz instruction cycle
#include <libpic30.h>  // Provides __delay_ms() and __delay_us()
#include <xc.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/uart/uart1.h"
#include "mcc_generated_files/secondary_core/sec_core_interface.h"
#include "mcc_generated_files/secondary_core/sec_core1.h"
#include <stdio.h>
#include <stdint.h>

void UART1_Write_Text(const char* str);

extern const struct SEC_CORE_INTERFACE MSIInterface; // generated instance
void get_status(void);
void get_status_with_msi(void);
static void UART_PrintHex16(uint16_t v);

int main(void) {
    
    SYSTEM_Initialize();

    MSIInterface.Program(); 
    MSIInterface.Start();
    
   __delay_ms(1000);

    get_status();
    get_status_with_msi();
    UART1_Write_Text("Hello PEPITO \r\n");
    uint16_t received = 0;
    uint8_t UARTbuffer = 0;
    
    // print MSI1STAT register fields
    uint16_t msistat = MSI1STAT; // read whole register
    UART1_Write_Text("MSI1STAT = 0x");
    UART_PrintHex16(msistat);

    // print specific flags
    UART1_Write_Text(" SLVRST=");
    UART1_Write(MSI1STATbits.SLVRST ? '1' : '0');
    UART1_Write_Text(" SLVPWR=");
    // print numeric value
    {
        char t[4]; t[0] = '0' + (MSI1STATbits.SLVPWR); t[1] = '\r'; t[2] = '\n'; t[3] = '\0';
        UART1_Write_Text(t);
    }

    while(1) {
        //MSIInterface.ReadFIFOEnable();
        if(!MSIInterface.FIFOReadIsEmpty()){
            MSIInterface.FIFORead(&received, 1); 
            UARTbuffer = (received >> 8) & 0xFF;   // upper 8 bits
            UART1_Write(UARTbuffer);
            UARTbuffer  = received & 0xFF;          // lower 8 bits
            UART1_Write(UARTbuffer);
            //LATAbits.LATA0 = !LATAbits.LATA0;        // LED ON (active-low)
        }
        //MSIInterface.ReadFIFODisable();
        get_status();
        get_status_with_msi();
        __delay_ms(1000);    
    }
}



void UART1_Write_Text(const char* str) {
    while(*str) {
        UART1_Write(*str++);
    }
}

void get_status(void){
    enum SEC_CORE_SYSTEM_STATUS status;
    status = SEC_CORE1_SystemStatusGet();  // get status

    if(status == SEC_CORE_SYSTEM_STATUS_RUNNING_STATE)
    {
        UART1_Write_Text("Core1 Status: RUNNING\r\n");
    }
    else if(status == SEC_CORE_SYSTEM_STATUS_IN_RESET_STATE)
    {
        UART1_Write_Text("Core1 Status: IN RESET\r\n");
    }
    else if(status == SEC_CORE_SYSTEM_STATUS_NOT_IN_LOW_POWER_MODE)
    {
        UART1_Write_Text("Core1 Status: NORMAL MODE\r\n");
    }
    else if(status == SEC_CORE_SYSTEM_STATUS_IDLE_MODE)
    {
        UART1_Write_Text("Core1 Status: IDLE MODE\r\n");
    }
    else if(status == SEC_CORE_SYSTEM_STATUS_SLEEP_MODE)
    {
        UART1_Write_Text("Core1 Status: SLEEP MODE\r\n");
    }
    else
    {
        UART1_Write_Text("Core1 Status: UNKNOWN\r\n");
    }
}

void get_status_with_msi(void){
    enum SEC_CORE_SYSTEM_STATUS status;
    status = MSIInterface.SystemStatusGet();  // get status

    if(status == SEC_CORE_SYSTEM_STATUS_RUNNING_STATE)
    {
        UART1_Write_Text("Core1 MSI Status: RUNNING\r\n");
    }
    else if(status == SEC_CORE_SYSTEM_STATUS_IN_RESET_STATE)
    {
        UART1_Write_Text("Core1 MSI Status: IN RESET\r\n");
    }
    else if(status == SEC_CORE_SYSTEM_STATUS_NOT_IN_LOW_POWER_MODE)
    {
        UART1_Write_Text("Core1 MSI Status: NORMAL MODE\r\n");
    }
    else if(status == SEC_CORE_SYSTEM_STATUS_IDLE_MODE)
    {
        UART1_Write_Text("Core1 MSI Status: IDLE MODE\r\n");
    }
    else if(status == SEC_CORE_SYSTEM_STATUS_SLEEP_MODE)
    {
        UART1_Write_Text("Core1 MSI Status: SLEEP MODE\r\n");
    }
    else
    {
        UART1_Write_Text("Core1 MSI Status: UNKNOWN\r\n");
    }
}

static void UART_PrintHex16(uint16_t v)
{
    char buf[6+1];
    const char hex[] = "0123456789ABCDEF";
    for(int i=0;i<4;i++){
        buf[3-i] = hex[v & 0xF];
        v >>= 4;
    }
    buf[4] = '\r'; buf[5] = '\n'; buf[6] = '\0';
    UART1_Write_Text(buf);
}