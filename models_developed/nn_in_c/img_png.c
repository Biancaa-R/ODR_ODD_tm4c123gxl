#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // Include the STB image write library
#include <stdio.h>
#include <stdlib.h>

// Function to generate a simple grayscale gradient
void generate_image(unsigned char *image, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image[y * width + x] = (x + y) % 256;  // Pixel intensity (0-255)
        }
    }
}

int main() {
    int width = 100, height = 100; // Image dimensions
    unsigned char *image = (unsigned char *)malloc(width * height); // Allocate memory

    if (!image) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    generate_image(image, width, height); // Fill pixel data

    // Save as PNG (grayscale, single channel)
    stbi_write_png("output.png", width, height, 1, image, width);

    printf("Image saved as output.png\n");

    free(image); // Free allocated memory
    return 0;
}
