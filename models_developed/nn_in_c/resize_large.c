#include <stdio.h>
#include <stdlib.h>

// Bilinear interpolation function
void resize_bilinear(unsigned char *input, int in_width, int in_height, 
                     unsigned char *output, int out_width, int out_height) {
    float x_ratio = ((float)(in_width - 1)) / out_width;
    float y_ratio = ((float)(in_height - 1)) / out_height;
    
    for (int y = 0; y < out_height; y++) {
        for (int x = 0; x < out_width; x++) {
            int x_low = (int)(x * x_ratio);
            int y_low = (int)(y * y_ratio);
            int x_high = x_low + 1 < in_width ? x_low + 1 : x_low;
            int y_high = y_low + 1 < in_height ? y_low + 1 : y_low;

            float x_diff = (x * x_ratio) - x_low;
            float y_diff = (y * y_ratio) - y_low;

            // Get the four pixel values
            unsigned char A = input[y_low * in_width + x_low];
            unsigned char B = input[y_low * in_width + x_high];
            unsigned char C = input[y_high * in_width + x_low];
            unsigned char D = input[y_high * in_width + x_high];

            // Bilinear interpolation formula
            float pixel = (A * (1 - x_diff) * (1 - y_diff)) +
                          (B * (x_diff) * (1 - y_diff)) +
                          (C * (y_diff) * (1 - x_diff)) +
                          (D * (x_diff) * (y_diff));

            output[y * out_width + x] = (unsigned char)pixel;
        }
    }
}

// Helper function to print image (for debugging)
void print_image(unsigned char *image, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%3d ", image[y * width + x]);
        }
        printf("\n");
    }
}

int main() {
    // Example large image (10x10 grayscale)
    int in_width = 10, in_height = 10;
    unsigned char input_image[100] = {
        10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
        15, 25, 35, 45, 55, 65, 75, 85, 95, 105,
        20, 30, 40, 50, 60, 70, 80, 90, 100, 110,
        25, 35, 45, 55, 65, 75, 85, 95, 105, 115,
        30, 40, 50, 60, 70, 80, 90, 100, 110, 120,
        35, 45, 55, 65, 75, 85, 95, 105, 115, 125,
        40, 50, 60, 70, 80, 90, 100, 110, 120, 130,
        45, 55, 65, 75, 85, 95, 105, 115, 125, 135,
        50, 60, 70, 80, 90, 100, 110, 120, 130, 140,
        55, 65, 75, 85, 95, 105, 115, 125, 135, 145
    };

    // Output image (28x28)
    int out_width = 28, out_height = 28;
    unsigned char output_image[28 * 28];

    // Resize the image
    resize_bilinear(input_image, in_width, in_height, output_image, out_width, out_height);

    // Print output (for debugging)
    print_image(output_image, out_width, out_height);

    return 0;
}
