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

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/main_core/main_core.h"
#include "mcc_generated_files/main_core/main_core_types.h"
#include "mcc_generated_files/main_core/main_core_interface.h"
#include <stdlib.h>
#include <stdint.h>


/*
    Main application
*/
void UART1_Write_Text(const char* str);

extern const struct MAIN_CORE_INTERFACE MSIInterface; // generated instance
uint16_t sendNumb;
int flag;

int main(void) {
    SYSTEM_Initialize();
    //LATAbits.LATA0 = 0;  // start low
        /////////////////////// MSI (SLAVE) ///////////////////////
    //MSIInterface.Initialize();
    flag = 0;
    uint8_t UARTslavebuffer = 0;
    //UART1_Write_Text("Slave init done \r\n");
    /*LATAbits.LATA0 = !LATAbits.LATA0;
    __delay_ms(1000);
    LATAbits.LATA0 = !LATAbits.LATA0;
    __delay_ms(1000);
    LATAbits.LATA0 = !LATAbits.LATA0;
    __delay_ms(1000);*/
    while (1) {
       // UART1_Write_Text("Slave enter main \r\n");
        //send_random_to_core1();
        if(flag == 0){
            sendNumb = 0xfffe;
            if (!MSIInterface.FIFOWriteIsFull()) {
                MSIInterface.FIFOWrite(&sendNumb, 1);  // 1 word = 2 bytes
                /*UARTslavebuffer = (sendNumb >> 8) & 0xFF;   // upper 8 bits
                UART1_Write(UARTslavebuffer);
                UART1_Write('\r');
                UART1_Write('\n');
                UART1_Write(UARTslavebuffer);
                UARTslavebuffer  = sendNumb & 0xFF;          // lower 8 bits
                UART1_Write(UARTslavebuffer);
                UART1_Write('\r');
                UART1_Write('\n');*/
            }
            flag = 1;
        }
        else if(flag == 1){
            sendNumb = 0;
            if (!MSIInterface.FIFOWriteIsFull()) {
                MSIInterface.FIFOWrite(&sendNumb, 1);  // 1 word = 2 bytes
                /*UARTslavebuffer = (sendNumb >> 8) & 0xFF;   // upper 8 bits
                UART1_Write(UARTslavebuffer);
                UART1_Write('\r');
                UART1_Write('\n');
                UARTslavebuffer  = sendNumb & 0xFF;          // lower 8 bits
                UART1_Write(UARTslavebuffer);
                UART1_Write('\r');
                UART1_Write('\n');*/
            }
            flag = 0;
        }
        //UART1_Write_Text("Slave main done \r\n");
        LATAbits.LATA0 = !LATAbits.LATA0; 
        LATBbits.LATB11 = !LATBbits.LATB11; 
        __delay_ms(1000);
    }
}