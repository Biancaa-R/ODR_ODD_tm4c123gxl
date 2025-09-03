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

#define UART_MODULE UART0_BASE
#define UART_GPIO_PORT GPIO_PORTA_BASE
#define UART_GPIO_TX GPIO_PIN_1
#define UART_GPIO_RX GPIO_PIN_0
#define BAUD_RATE 115200

// ---------- Neural Network Parameters ----------
// Example NN: 4 inputs → 5 hidden → 3 outputs

// Hidden layer (5 neurons, 4 inputs)
float W1[5][4] = {
    {0.2, -0.1, 0.4, 0.1},
    {0.3,  0.5, -0.2, 0.0},
    {-0.3, 0.8, 0.1, -0.1},
    {0.6, -0.4, 0.2, 0.3},
    {0.1,  0.2, 0.3, 0.4}
};
float B1[5] = {0.0, 0.1, -0.1, 0.0, 0.05};

// Output layer (3 neurons, 5 inputs)
float W2[3][5] = {
    {0.5, -0.2, 0.1, 0.4, -0.3},
    {-0.1, 0.6, 0.3, -0.2, 0.2},
    {0.2, 0.1, -0.5, 0.3, 0.4}
};
float B2[3] = {0.0, 0.0, 0.1};

void UARTInit(void);
void UARTPrint(const char *message);
void UARTPrintFloat(const char *label, float value);
char UARTCharRead(void);
void UARTReadLine(char *buffer, int maxlen);


float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

void run_inference(float input[4]) {
    char buffer[100];

    // Hidden layer
    float hidden[5];
    for (int i = 0; i < 5; i++) {
        hidden[i] = B1[i];
        for (int j = 0; j < 4; j++) {
            hidden[i] += W1[i][j] * input[j];
        }
        hidden[i] = sigmoid(hidden[i]);
    }

    // Output layer
    float output[3];
    int predicted_class = 0;
    float max_val = -1000.0f;

    for (int i = 0; i < 3; i++) {
        output[i] = B2[i];
        for (int j = 0; j < 5; j++) {
            output[i] += W2[i][j] * hidden[j];
        }
        output[i] = sigmoid(output[i]);

        if (output[i] > max_val) {
            max_val = output[i];
            predicted_class = i;
        }
    }

    // Print results
    UARTPrint("\r\nInput received: ");
    sprintf(buffer, "[%.3f, %.3f, %.3f, %.3f]\r\n", input[0], input[1], input[2], input[3]);
    UARTPrint(buffer);

    for (int i = 0; i < 3; i++) {
        sprintf(buffer, "Class %d score: %.4f\r\n", i, output[i]);
        UARTPrint(buffer);
    }

    sprintf(buffer, "Predicted class: %d\r\n", predicted_class);
    UARTPrint(buffer);
}

int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_OSC |
                   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    UARTInit();

    UARTPrint("Neural Net Inference Ready!\r\n");
    UARTPrint("Enter 4 float inputs separated by spaces, then press Enter.\r\n");

    char line[100];
    float input[4];

    while (1) {
        UARTPrint("\r\n>> ");
        UARTReadLine(line, sizeof(line));

        if (sscanf(line, "%f %f %f %f", &input[0], &input[1], &input[2], &input[3]) == 4) {
            run_inference(input);
        } else {
            UARTPrint("Invalid input. Example: 0.5 1.2 -0.3 0.7\r\n");
        }
    }
    return 0;
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
