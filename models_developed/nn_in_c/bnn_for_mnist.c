#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_NODES 784   // MNIST images are 28x28
#define HIDDEN_NODES 128
#define OUTPUT_NODES 10    // Digits 0-9
#define LEARNING_RATE 0.01
#define EPOCHS 10

// Activation Functions
double relu(double x) { return x > 0 ? x : 0; }
double softmax(double x) { return exp(x); } // Applied in a layer-wise manner

// Initialize Weights and Biases
double input_weights[INPUT_NODES][HIDDEN_NODES];
double hidden_weights[HIDDEN_NODES][OUTPUT_NODES];
double hidden_bias[HIDDEN_NODES];
double output_bias[OUTPUT_NODES];

// Random Weight Initialization
void initialize_weights() {
    for (int i = 0; i < INPUT_NODES; i++)
        for (int j = 0; j < HIDDEN_NODES; j++)
            input_weights[i][j] = ((double) rand() / RAND_MAX) * 0.01;  // Small random values

    for (int i = 0; i < HIDDEN_NODES; i++)
        for (int j = 0; j < OUTPUT_NODES; j++)
            hidden_weights[i][j] = ((double) rand() / RAND_MAX) * 0.01;

    for (int i = 0; i < HIDDEN_NODES; i++)
        hidden_bias[i] = 0;

    for (int i = 0; i < OUTPUT_NODES; i++)
        output_bias[i] = 0;
}

// Forward Pass
void forward_pass(double input[], double hidden[], double output[]) {
    // Hidden Layer
    for (int i = 0; i < HIDDEN_NODES; i++) {
        hidden[i] = hidden_bias[i];
        for (int j = 0; j < INPUT_NODES; j++)
            hidden[i] += input[j] * input_weights[j][i];
        hidden[i] = relu(hidden[i]);
    }

    // Output Layer (Softmax)
    double sum_exp = 0.0;
    for (int i = 0; i < OUTPUT_NODES; i++) {
        output[i] = output_bias[i];
        for (int j = 0; j < HIDDEN_NODES; j++)
            output[i] += hidden[j] * hidden_weights[j][i];
        output[i] = softmax(output[i]);
        sum_exp += output[i];
    }

    for (int i = 0; i < OUTPUT_NODES; i++)
        output[i] /= sum_exp;  // Normalize softmax
}

// Training (Simple Backpropagation)
void train(double input[], int label) {
    double hidden[HIDDEN_NODES], output[OUTPUT_NODES];
    forward_pass(input, hidden, output);

    // Compute Error (Cross-Entropy)
    double target[OUTPUT_NODES] = {0};
    target[label] = 1.0;

    double output_error[OUTPUT_NODES];
    for (int i = 0; i < OUTPUT_NODES; i++)
        output_error[i] = output[i] - target[i];

    // Backpropagate to Hidden Layer
    double hidden_error[HIDDEN_NODES] = {0};
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++)
            hidden_error[i] += output_error[j] * hidden_weights[i][j];
    }

    // Update Weights & Biases
    for (int i = 0; i < OUTPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++)
            hidden_weights[j][i] -= LEARNING_RATE * output_error[i] * hidden[j];
        output_bias[i] -= LEARNING_RATE * output_error[i];
    }

    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < INPUT_NODES; j++)
            input_weights[j][i] -= LEARNING_RATE * hidden_error[i] * input[j];
        hidden_bias[i] -= LEARNING_RATE * hidden_error[i];
    }
}

// Load MNIST Dataset (Requires Preprocessing)
void load_mnist_dataset() {
    // Implement a function to load and preprocess the MNIST dataset
}

// Main Function
int main() {
    initialize_weights();
    load_mnist_dataset();

    // Training Loop
    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        printf("Epoch %d/%d\n", epoch + 1, EPOCHS);
        // Loop through MNIST training data
        // for each training example -> train(input, label)
    }

    printf("Training Complete!\n");
    return 0;
}
