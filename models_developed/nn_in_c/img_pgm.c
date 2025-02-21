#include <stdio.h>
#include <stdlib.h>

// Function to save grayscale image as a PGM file
void save_pgm(const char *filename, unsigned char *image, int width, int height) {
    FILE *file = fopen(filename, "wb"); // Open file in binary mode
    if (!file) {
        printf("Error: Could not open file %s for writing\n", filename);
        return;
    }

    // Write the PGM file header
    fprintf(file, "P5\n%d %d\n255\n", width, height); 

    // Write the pixel data
    fwrite(image, sizeof(unsigned char), width * height, file);

    fclose(file);
    printf("Saved image as %s\n", filename);
}

int main() {
    // Example: Create a small grayscale gradient image (10x10)
    int width = 10, height = 10;
    unsigned char image[100];

    // Generate pixel values (simple gradient)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image[y * width + x] = (x + y) * 10;  // Example pixel intensity
        }
    }

    // Save the image as "output.pgm"
    save_pgm("output.pgm", image, width, height);

    return 0;
}
