// mnist_loader.h
#ifndef MNIST_LOADER_H
#define MNIST_LOADER_H

#define INPUT_NODES 784
#define TRAIN_SIZE 60000

void load_mnist_dataset();
void load_mnist_image(int index, double input[INPUT_NODES], int *label);

#endif