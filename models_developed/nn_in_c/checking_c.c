#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PIXELS 784  // 28x28 image
#define MAX_LINE 10000   // Large enough buffer for a CSV row

int main() {
    FILE *file = fopen("D:\\c_25\\ml_in_c\\nn_in_c\\mnist_test.csv", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    char line[MAX_LINE];
    int row = 0;

    // Skip header
    fgets(line, sizeof(line), file);

    // Read first row
    if (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        int label = atoi(token);  // Read label

        float pixels[NUM_PIXELS];
        int count = 0;

        // Read pixel values
        while ((token = strtok(NULL, ",")) && count < NUM_PIXELS) {
            pixels[count++] = atof(token);
        }

        if (count != NUM_PIXELS) {
            printf("Error: Missing pixel values at index %d (read %d, expected %d)\n", row, count, NUM_PIXELS);
        } else {
            printf("Row %d loaded correctly. Label: %d, First Pixel: %.1f\n", row, label, pixels[0]);
        }
    }

    fclose(file);
    return 0;
}
