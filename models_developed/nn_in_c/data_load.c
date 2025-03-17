#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define TRAIN_CSV "mnist_train.csv"
#define TRAIN_CSV "D:\\c_25\\ml_in_c\\nn_in_c\\mnist_test.csv"

#define NUM_TRAIN 60000
#define IMAGE_SIZE 784  // 28x28 pixels

// Structure to hold image data
typedef struct {
    int label;
    float pixels[IMAGE_SIZE];
} MNIST_Image;

// Function to load MNIST CSV file
int load_mnist_csv(const char* filename, MNIST_Image* dataset, int num_samples) {
    char line[16000];  // Buffer for each line
    int index = 0;

    FILE *csv_fp = fopen(filename, "r");
    if (!csv_fp) {
        printf("Error opening file: %s\n", filename);
        return -1;
    }
    
    // Skip the header line
    if (!fgets(line, sizeof(line), csv_fp)) {
        printf("Error: Unable to read header.\n");
        fclose(csv_fp);
        return -1;
    }
    printf("Header: %s\n", line);  // Debug print
    
    // Read each image
    while (fgets(line, sizeof(line), csv_fp) && index < num_samples) {
        printf("Reading line %d: %s\n", index + 1, line);  // Debug print
        char *token = strtok(line, ",");
        if (!token) {
            printf("Error: Missing label at line %d\n", index + 1);
            continue;
        }
    
        dataset[index].label = atoi(token);
        for (int i = 0; i < IMAGE_SIZE; i++) {
            token = strtok(NULL, ",");
            if (!token) {
                printf("Error: Missing pixel data at line %d, pixel %d\n", index + 1, i);
                break;
            }
            dataset[index].pixels[i] = atof(token);
        }
        index++;
    }
    
}

int main() {
    MNIST_Image train_data[NUM_TRAIN];

    // Load training dataset
    if (load_mnist_csv(TRAIN_CSV, train_data, NUM_TRAIN) == 0) {
        printf("Successfully loaded %d MNIST images.\n", NUM_TRAIN);
    } else {
        printf("Failed to load MNIST images.\n");
    }

    // Example: Print first image's label and first few pixel values
    printf("First image label: %d\n", train_data[0].label);
    printf("First 10 pixel values: ");
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", train_data[0].pixels[i]);
    }
    printf("\n");

    return 0;
}
