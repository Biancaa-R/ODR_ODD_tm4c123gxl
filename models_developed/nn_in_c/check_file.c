#include<stdio.h>
int main()
{
FILE *test = fopen("D:\\c_25\\ml_in_c\\t10k-images-idx3-ubyte\\t10k-images-idx3-ubyte", "rb");
if (test) {
    printf("File opened successfully!\n");
    fclose(test);
} else {
    printf("File does not exist or cannot be accessed.\n");
}
}