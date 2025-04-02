#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mnist_loader.h"  // Ensure you have a loader to parse MNIST data

#define INPUT_NODES 784  // 28x28 pixels
#define HIDDEN_NODES 128
#define OUTPUT_NODES 10  // Digits 0-9
#define LEARNING_RATE 0.1

// Activation function (Sigmoid)
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_derivative(double x) {
    return x * (1.0 - x);
}

// Neural Network Weights
double input_hidden[INPUT_NODES][HIDDEN_NODES];
double hidden_output[HIDDEN_NODES][OUTPUT_NODES];
double bias_hidden[HIDDEN_NODES];
double bias_output[OUTPUT_NODES];

double hidden_layer[HIDDEN_NODES];
double output_layer[OUTPUT_NODES];

// Initialize Weights and Biases
void initialize_network() {
    for (int i = 0; i < INPUT_NODES; i++)
        for (int j = 0; j < HIDDEN_NODES; j++)
            input_hidden[i][j] = ((double)rand() / RAND_MAX) * 2 - 1;
    
    for (int i = 0; i < HIDDEN_NODES; i++) {
        bias_hidden[i] = ((double)rand() / RAND_MAX) * 2 - 1;
        for (int j = 0; j < OUTPUT_NODES; j++)
            hidden_output[i][j] = ((double)rand() / RAND_MAX) * 2 - 1;
    }
    
    for (int i = 0; i < OUTPUT_NODES; i++)
        bias_output[i] = ((double)rand() / RAND_MAX) * 2 - 1;
}

// Forward Propagation
// void forward_propagation(double input[INPUT_NODES]) {
//     // Input to Hidden Layer
//     for (int i = 0; i < HIDDEN_NODES; i++) {
//         hidden_layer[i] = bias_hidden[i];
//         for (int j = 0; j < INPUT_NODES; j++)
//             hidden_layer[i] += input[j] * input_hidden[j][i];
//         hidden_layer[i] = sigmoid(hidden_layer[i]);
//     }
    
//     // Hidden to Output Layer
//     for (int i = 0; i < OUTPUT_NODES; i++) {
//         output_layer[i] = bias_output[i];
//         for (int j = 0; j < HIDDEN_NODES; j++)
//             output_layer[i] += hidden_layer[j] * hidden_output[j][i];
//         output_layer[i] = sigmoid(output_layer[i]);
//     }
// }
void forward_propagation(double input[INPUT_NODES]) {
    printf("Starting forward propagation...\n");

    // Input to Hidden Layer
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden_layer[i] = bias_hidden[i];
        for (int j = 0; j < INPUT_NODES; j++) {
            if (j >= INPUT_NODES || i >= HIDDEN_NODES) {  // Safety check
                printf("ERROR: Array index out of bounds in input-hidden layer!\n");
                exit(1);
            }
            hidden_layer[i] += input[j] * input_hidden[j][i];
        }
        hidden_layer[i] = sigmoid(hidden_layer[i]);
    }
    
    // Hidden to Output Layer
    for (int i = 0; i < OUTPUT_NODES; i++) {
        output_layer[i] = bias_output[i];
        for (int j = 0; j < HIDDEN_NODES; j++) {
            if (j >= HIDDEN_NODES || i >= OUTPUT_NODES) {  // Safety check
                printf("ERROR: Array index out of bounds in hidden-output layer!\n");
                exit(1);
            }
            output_layer[i] += hidden_layer[j] * hidden_output[j][i];
        }
        output_layer[i] = sigmoid(output_layer[i]);
    }
    
    printf("Forward propagation completed successfully.\n");
}


// Backpropagation
void backpropagation(double input[INPUT_NODES], int label) {
    double output_errors[OUTPUT_NODES];
    double hidden_errors[HIDDEN_NODES];
    
    // Output Layer Error
    for (int i = 0; i < OUTPUT_NODES; i++) {
        double target = (i == label) ? 1.0 : 0.0;
        output_errors[i] = (target - output_layer[i]) * sigmoid_derivative(output_layer[i]);
    }
    
    // Hidden Layer Error
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden_errors[i] = 0;
        for (int j = 0; j < OUTPUT_NODES; j++)
            hidden_errors[i] += output_errors[j] * hidden_output[i][j];
        hidden_errors[i] *= sigmoid_derivative(hidden_layer[i]);
    }
    
    // Update Weights and Biases
    for (int i = 0; i < OUTPUT_NODES; i++) {
        bias_output[i] += LEARNING_RATE * output_errors[i];
        for (int j = 0; j < HIDDEN_NODES; j++)
            hidden_output[j][i] += LEARNING_RATE * output_errors[i] * hidden_layer[j];
    }
    
    for (int i = 0; i < HIDDEN_NODES; i++) {
        bias_hidden[i] += LEARNING_RATE * hidden_errors[i];
        for (int j = 0; j < INPUT_NODES; j++)
            input_hidden[j][i] += LEARNING_RATE * hidden_errors[i] * input[j];
    }
}

// Train the Network
void train_mnist(int epochs, int train_size) {
    for (int e = 0; e < epochs; e++) {
        for (int i = 0; i < train_size; i++) {
            double input[INPUT_NODES];
            int label;
            load_mnist_image(i, input, &label);  // Load image as input
            forward_propagation(input);
            backpropagation(input, label);
        }
        printf("Epoch %d completed\n", e + 1);
    }
}

// Predict a Digit
int predict(double input[INPUT_NODES]) {
    forward_propagation(input);
    int max_idx = 0;
    for (int i = 1; i < OUTPUT_NODES; i++) {
        if (output_layer[i] > output_layer[max_idx])
            max_idx = i;
    }
    return max_idx;
}

// int main() {
//     srand(42);
//     initialize_network();
//     load_mnist_dataset();  // Ensure this function loads images
    
//     train_mnist(10, 60000);
    
//     // Test on one image
//     double test_image[INPUT_NODES];
//     int test_label;
//     load_mnist_image(0, test_image, &test_label);
//     int prediction = predict(test_image);
//     printf("Predicted: %d, Actual: %d\n", prediction, test_label);
    
//     return 0;
// }

int main() {
    srand(42);
    printf("Initializing Neural Network...\n");
    initialize_network();
    
    printf("Loading MNIST dataset...\n");
    load_mnist_dataset();
    
    printf("Loading first image for testing...\n");
    double test_image[INPUT_NODES];
    int test_label;
    load_mnist_image(0, test_image, &test_label);
    printf("First image loaded successfully. Label: %d\n", test_label);

    printf("Running a forward pass...\n");
    forward_propagation(test_image);
    printf("Forward pass completed.\n");

    printf("Training network...\n");
    train_mnist(10, 600);  // Train for 10 epochs
    printf("Training completed.\n");

    printf("Testing first image...\n");
    int prediction = predict(test_image);
    printf("Predicted: %d, Actual: %d\n", prediction, test_label);

    return 0;
}