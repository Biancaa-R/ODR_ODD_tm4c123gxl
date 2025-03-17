#include <stdio.h>
#include <stdlib.h>

#define TRAIN_IMAGES "D:\\c_25\\ml_in_c\\t10k-images-idx3-ubyte\\t10k-images-idx3-ubyte" //"train-images-idx3-ubyte"
#define TRAIN_LABELS "D:\\c_25\\ml_in_c\\train-labels-idx1-ubyte\\train-labels-idx1-ubyte"
#define TEST_IMAGES "D:\\c_25\\ml_in_c\\t10k-images-idx3-ubyte\\t10k-images-idx3-ubyte"
#define TEST_LABELS "D:\\c_25\\ml_in_c\\t10k-labels-idx1-ubyte\\t10k-labels-idx1-ubyte"

#define TRAIN_CSV "mnist_train.csv"
#define TEST_CSV "mnist_test.csv"

#define NUM_TRAIN 60000
#define NUM_TEST 10000
#define IMAGE_SIZE 784  // 28x28 pixels

// Function to convert MNIST data to CSV
void convert_mnist_to_csv(const char* image_file, const char* label_file, const char* output_csv, int num_samples) {
    FILE *img_fp = fopen(image_file, "rb");
    FILE *lbl_fp = fopen(label_file, "rb");
    FILE *csv_fp = fopen(output_csv, "w");

    if (!img_fp || !lbl_fp || !csv_fp) {
        printf("Error opening files.\n");
        exit(1);
    }

    // Skip headers
    fseek(img_fp, 16, SEEK_SET);
    fseek(lbl_fp, 8, SEEK_SET);

    // Write CSV header
    fprintf(csv_fp, "label");
    for (int i = 0; i < IMAGE_SIZE; i++) {
        fprintf(csv_fp, ",pixel%d", i);
    }
    fprintf(csv_fp, "\n");

    // Process each image
    for (int i = 0; i < num_samples; i++) {
        unsigned char label;
        unsigned char pixels[IMAGE_SIZE];

        // Read label
        fread(&label, sizeof(unsigned char), 1, lbl_fp);

        // Read image pixels
        fread(pixels, sizeof(unsigned char), IMAGE_SIZE, img_fp);

        // Write label
        fprintf(csv_fp, "%d", label);

        // Write pixel values (normalized to 0-1)
        for (int j = 0; j < IMAGE_SIZE; j++) {
            fprintf(csv_fp, ",%.4f", pixels[j] / 255.0);
        }

        fprintf(csv_fp, "\n");
    }

    // Close files
    fclose(img_fp);
    fclose(lbl_fp);
    fclose(csv_fp);
    
    printf("Successfully created: %s\n", output_csv);
}

int main() {
    printf("Converting MNIST dataset to CSV...\n");

    // Convert training set
    convert_mnist_to_csv(TRAIN_IMAGES, TRAIN_LABELS, TRAIN_CSV, NUM_TRAIN);

    // Convert test set
    convert_mnist_to_csv(TEST_IMAGES, TEST_LABELS, TEST_CSV, NUM_TEST);

    printf("Conversion completed!\n");
    return 0;
}