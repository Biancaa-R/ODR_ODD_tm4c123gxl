/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/debug.h"
#include "bnn.c"

#define UART_MODULE UART0_BASE
#define UART_GPIO_PORT GPIO_PORTA_BASE
#define UART_GPIO_TX GPIO_PIN_1
#define UART_GPIO_RX GPIO_PIN_0
#define BAUD_RATE 115200
#define IMG_SIZE 784
float input[IMG_SIZE];
char line[4000];  // enough for a line with all pixel values as text

// UART receive buffer
#define UART_RX_BUFFER_SIZE 256

volatile uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];
volatile uint32_t uart_rx_index = 0;
volatile uint8_t uart_rx_byte = 0;

// Flags
volatile bool uart_data_ready = false;

// Stub function for UART receive
uint8_t UARTReceiveByte(void) {
    // placeholder: just return last received byte
    return uart_rx_byte;
}


void UARTInit(void);
void UARTPrint(const char *message);
void UARTPrintFloat(const char *label, float value);
char UARTCharRead(void);
void UARTReadLine(char *buffer, int maxlen);
void UARTReadImage(float *img, int size);

int main(){
while (1) {
    UARTPrint("\r\n>> Send image (784 floats separated by spaces):\r\n");
    Layer* linput = Layer_create(NULL, IMG_SIZE); // 784 inputs 
    Layer* lhidden = Layer_create(linput, 128); // hidden layer 
    Layer* loutput = Layer_create(lhidden, 10); // 10 output classes 
    double rate = 0.1; 
    int nepochs = 1000; // smaller for demo
    UARTReadImage(input, IMG_SIZE);

for (int i = 0; i < nepochs; i++) {
    double x[IMG_SIZE] = {0};
    double t[10] = {0};
    int label = 0;

    // --- Receive input over UART ---
    for (int j = 0; j < IMG_SIZE; j++) {
        uint8_t buf[4];  // assuming float sent as 4 bytes
        UART_ReceiveBytes(buf, 4);    // blocking read
        float val;
        memcpy(&val, buf, sizeof(float));
        x[j] = (double)val;
    }

    // --- Receive label ---
    uint8_t label_buf[1];
    UART_ReceiveBytes(label_buf, 1);
    label = label_buf[0];  // assuming 0-9
    t[label] = 1.0;        // one-hot encoding

    // Forward pass
    Layer_setInputs(linput, input);
    double output[10];
    Layer_getOutputs(loutput, output);

    // Send outputs back via UART
    UARTPrint("Output scores:\r\n");
    char buf[64];
    for (int i = 0; i < 10; i++) {
        sprintf(buf, "Class %d: %.4f\r\n", i, output[i]);
        UARTPrint(buf);
    }

    // Predicted class
    int pred = 0;
    for (int i = 1; i < 10; i++)
        if (output[i] > output[pred])
            pred = i;

    sprintf(buf, "Predicted: %d\r\n", pred);
    UARTPrint(buf);

    // Training
    Layer_learnOutputs(loutput, target);
    Layer_update(loutput, 0.1); // learning rate
}
}

void UARTReadImage(float *img, int size) {
    char line[4000];  // big enough buffer
    UARTReadLine(line, sizeof(line));

    char *token = strtok(line, " ");
    int idx = 0;
    while (token != NULL && idx < size) {
        img[idx++] = atof(token);
        token = strtok(NULL, " ");
    }

    if (idx != size) {
        UARTPrint("Error: Expected ");
        char buf[10];
        sprintf(buf, "%d", size);
        UARTPrint(buf);
        UARTPrint(" values.\r\n");
    }
}
void UARTInit(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(UART_GPIO_PORT, UART_GPIO_RX | UART_GPIO_TX);

    UARTConfigSetExpClk(UART_MODULE, SysCtlClockGet(), BAUD_RATE,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

void UARTPrint(const char *message) {
    while (*message != '\0') {
        UARTCharPut(UART_MODULE, *message);
        message++;
    }
}

void UARTPrintFloat(const char *label, float value) {
    char buffer[50];
    sprintf(buffer, "%s %.4f\r\n", label, value);
    UARTPrint(buffer);
}

char UARTCharRead(void) {
    return UARTCharGet(UART_MODULE);
}

void UARTReadLine(char *buffer, int maxlen) {
    int i = 0;
    char c;
    while (1) {
        c = UARTCharRead();
        if (c == '\r' || c == '\n') {
            buffer[i] = '\0';
            UARTPrint("\r\n");
            return;
        } else if (i < maxlen - 1) {
            buffer[i++] = c;
            UARTCharPut(UART_MODULE, c); // echo back
        }
    }
}
