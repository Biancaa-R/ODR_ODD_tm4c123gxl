

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

char data_block[100][100] = {
    "Layer0: nodes=2",
    "  outputs = [ 0.0000 0.0000]",
    "Layer1 (<- Layer0): nodes=3",
    "  outputs = [ 0.0000 0.0000 0.0000]",
    "  biases = [ 0.0000 0.0000 0.0000]",
    "  weights = [ -0.1712 -0.0779 0.0290 0.0599 0.1556 -0.0012]",
    "Layer2 (<- Layer1): nodes=1",
    "  outputs = [ 0.0000]",
    "  biases = [ 0.0000]",
    "  weights = [ -0.0466 0.0492 0.0764]",
    "i=0, x=[0.5369, 0.9635], y=[0.5110], t=[0.4266], etotal=0.0071",
    "i=1, x=[0.7813, 0.1796], y=[0.5110], t=[0.6017], etotal=0.0082",
    "i=2, x=[0.0295, 0.7577], y=[0.5102], t=[0.7281], etotal=0.0475",
    "i=3, x=[0.6625, 0.6416], y=[0.5110], t=[0.0209], etotal=0.2402",
    "i=4, x=[0.6403, 0.4392], y=[0.5109], t=[0.2011], etotal=0.0960",
    "i=5, x=[0.7178, 0.4760], y=[0.5110], t=[0.2418], etotal=0.0725",
    "i=6, x=[0.3360, 0.6991], y=[0.5106], t=[0.3631], etotal=0.0218",
    "i=7, x=[0.6646, 0.7998], y=[0.5111], t=[0.1352], etotal=0.1413",
    "i=8, x=[0.5412, 0.0142], y=[0.5106], t=[0.5269], etotal=0.0003",
    "i=9, x=[0.1372, 0.9043], y=[0.5104], t=[0.7671], etotal=0.0659",
    "i=10, x=[0.8701, 0.4851], y=[0.5112], t=[0.3850], etotal=0.0159",
    "i=11, x=[0.0669, 0.1597], y=[0.5100], t=[0.0928], etotal=0.1741",
    "i=12, x=[0.3612, 0.6278], y=[0.5106], t=[0.2665], etotal=0.0596",
    "i=13, x=[0.7182, 0.8186], y=[0.5112], t=[0.1004], etotal=0.1687",
    "i=14, x=[0.9438, 0.3939], y=[0.5112], t=[0.4179], etotal=0.0087",
    "i=15, x=[0.2439, 0.1118], y=[0.5102], t=[0.1042], etotal=0.1642",
    "i=16, x=[0.1451, 0.8437], y=[0.5104], t=[0.7465], etotal=0.0609",
    "i=17, x=[0.6789, 0.5271], y=[0.5110], t=[0.2127], etotal=0.0862",
    "i=18, x=[0.4184, 0.3495], y=[0.5104], t=[0.1843], etotal=0.1063",
    "i=19, x=[0.8503, 0.6274], y=[0.5112], t=[0.2483], etotal=0.0690",
    "i=20, x=[0.9614, 0.2548], y=[0.5111], t=[0.5036], etotal=0.0003",
    "i=21, x=[0.1348, 0.4957], y=[0.5103], t=[0.4298], etotal=0.0072",
    "i=22, x=[0.0742, 0.7908], y=[0.5103], t=[0.7024], etotal=0.0457",
    "i=23, x=[0.2926, 0.9105], y=[0.5105], t=[0.7629], etotal=0.0642",
    "i=24, x=[0.8995, 0.3746], y=[0.5112], t=[0.4457], etotal=0.0042",
    "i=25, x=[0.2058, 0.6239], y=[0.5104], t=[0.3152], etotal=0.0410",
    "i=26, x=[0.7014, 0.2125], y=[0.5109], t=[0.5924], etotal=0.0067",
    "i=27, x=[0.6597, 0.9375], y=[0.5111], t=[0.1657], etotal=0.1277",
    "i=28, x=[0.1001, 0.2874], y=[0.5102], t=[0.2389], etotal=0.0737",
    "i=29, x=[0.8136, 0.5732], y=[0.5111], t=[0.2847], etotal=0.0513",
    "i=30, x=[0.5123, 0.9201], y=[0.5109], t=[0.1784], etotal=0.1098",
    "i=31 x=[0.6293 0.2613], y=[0.5108] t=[0.3680] etotal=[0.0204]",
    "i=32 x=[0.8728 0.6244], y=[0.5113], t=[0.2484], etotal=[0.0691]",
    "i=33 x=[0.5980 0.9401], y=[0.5110] t=[0.3421], etotal=[0.0285]",
    "i=34 x=[0.2820 0.5763 ],y=[0.5105], t=[0.2943 ],etotal=[0.0467]",
    "i=35 x=[0.6477 0.3787], y=[0.5109 ],t=[0.2690 ],etotal=[0.0585]",
    "Layer0: nodes=2",
    "outputs = [ 0.7707 0.5149]",
    "Layer1 (<- Layer0): nodes=3",
    "outputs = [ 0.4571 0.5133 0.5298]",
    "biases = [ 0.0000 0.0000 0.0000]",
    "weights = [ -0.1712 -0.0779 0.0290 0.0599 0.1556 -0.0012]",
    "Layer2 (<- Layer1): nodes=1",
    "outputs = [ 0.5111]",
    "biases = [ 0.0000]",
    "weights = [ -0.0466 0.0492 0.0764]",
    "Predicted digit: 0"
};
void UARTInit(void);
void UARTPrint(const char*message);
int main(void)
{
    //set up the clock of microcontroller
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_OSC |SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
    //initialize the uart functionality
    UARTInit();
    //own function
    /*while(1){
        //superloop
        UARTPrint("Hello Darling\r\n");
        //user defined function
        SysCtlDelay(1600000);

    }*/
    unsigned int i;
    for ( i = 0; i < 70; i++) {
        UARTPrint(data_block[i]);
        UARTPrint("\r\n");
        SysCtlDelay(1600000);
    }

	return 0;
}

void UARTInit(void){
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

void UARTPrint(const char* message){
    while(*message !='\0'){
        //till the end of the message
        UARTCharPut(UART_MODULE,*message);
        message++;
    }
}


