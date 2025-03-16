

/**
 * main.c
 */
#include<stdint.h>
#include<stdbool.h>
#include <inc/hw_types.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
//idhu iruka en kitta
#include "driverlib/debug.h"


#define UART_MODULE UART0_BASE
#define UART_GPIO_PORT GPIO_PORTA_BASE
#define UART_GPIO_TX GPIO_PIN_1 //uart o tx pin
//port A pin 0,1 as tx ,rx
#define UART_GPIO_RX GPIO_PIN_0 //uart o rx pin
#define BAUD_RATE 115200

void UARTInit1(void);
void UARTPrint1(const char*message);
int main1(void)
{
    //set up the clock of microcontroller
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_OSC |SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
    //initialize the uart functionality
    UARTInit();
    //own function
    while(1){
        //superloop
        UARTPrint("Hello Darling\r\n");
        //user defined function
        SysCtlDelay(1600000);

    }
    return 0;
}

void UARTInit1(void){
    //provide clock to uart module ,gpio portA
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    //enabled both the modules
    //gpio pin configure function -->configures alternate functions
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);//PA1 as transmitter pin
    GPIOPinTypeUART(UART_GPIO_PORT,UART_GPIO_RX | UART_GPIO_TX);
    //provide port and pin details

    //Configure the uart
    //inbuilt function to provide the clock
    //sysctl_clk_set and sysctl_clk_get --> gets the clock rate of processor
    UARTConfigSetExpClk(UART_MODULE,SysCtlClockGet(),BAUD_RATE,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
}

void UARTPrint1(const char* message){
    while(*message !='\0'){
        //till the end of the message
        UARTCharPut(UART_MODULE,*message);
        message++;
    }
}
