#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_NODES 784
#define MAX_LINE_LENGTH 3200  // To accommodate a full row in the CSV file

// Function to load MNIST dataset from a CSV file
// void load_mnist_dataset() {
//     printf("Loading MNIST dataset...\n");
//     FILE *file = fopen("mnist_train.csv", "r");
//     if (!file) {
//         printf("Error: Could not open mnist_train.csv\n");
//         exit(1);
//     }
//     fclose(file);
// }
void load_mnist_dataset() {
    printf("Loading MNIST dataset from CSV...\n");
    
    FILE *file = fopen("mnist_train.csv", "r");
    if (!file) {
        printf("Error: Could not open mnist_train.csv\n");
        exit(1);
    }

    // Read the first line (header)
    char buffer[3200];  // Ensure the buffer is large enough
    if (!fgets(buffer, sizeof(buffer), file)) {
        printf("Error: Failed to read the CSV header\n");
        fclose(file);
        exit(1);
    }

    printf("Dataset header read successfully.\n");

    fclose(file);
}


// Function to load a specific image and label
// void load_mnist_image(int index, double input[INPUT_NODES], int *label) {
//     FILE *file = fopen("mnist_train.csv", "r");
//     if (!file) {
//         printf("Error: Could not open mnist_train.csv\n");
//         exit(1);
//     }

//     char line[MAX_LINE_LENGTH];
//     int i = 0;
//     while (fgets(line, MAX_LINE_LENGTH, file)) {
//         if (i == index) {  // Read the required index
//             char *token = strtok(line, ",");
//             *label = atoi(token);  // First value is the label
//             for (int j = 0; j < INPUT_NODES; j++) {
//                 token = strtok(NULL, ",");
//                 input[j] = atoi(token) / 255.0;  // Normalize pixel values
//             }
//             break;
//         }
//         i++;
//     }
//     fclose(file);
// }


#define INPUT_NODES 784
#define MAX_LINE_LENGTH 3200  // To accommodate a full row in the CSV file

void load_mnist_image(int index, int input[INPUT_NODES], int *label) {
    FILE *file = fopen("mnist_train_bnn.csv", "r");
    if (!file) {
        printf("Error: Could not open mnist_train_bnn.csv\n");
        exit(1);
    }

    char line[3200];  // Large enough buffer
    int i = 0;

    while (fgets(line, sizeof(line), file)) {
        if (i == index) {
            char *token = strtok(line, ",");
            if (token == NULL) {
                printf("Error: Could not read label for index %d\n", index);
                fclose(file);
                exit(1);
            }

            *label = atoi(token);  // Read label
            printf("Label: %d\n", *label);

            // Read binarized pixel values (already 0 or 1)
            for (int j = 0; j < INPUT_NODES; j++) {
                token = strtok(NULL, ",");
                if (token == NULL) {
                    printf("Error: Missing pixel values at index %d\n", index);
                    fclose(file);
                    exit(1);
                }
                input[j] = atoi(token);  // Store as integer (0 or 1)
            }

            printf("Successfully loaded image %d with label %d\n", index, *label);
            break;
        }
        i++;
    }

    fclose(file);
}
