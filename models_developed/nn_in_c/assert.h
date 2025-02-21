#include <stdint.h>

#define ASSERT(expr)  if (!(expr)) while(1);  // Infinite loop on failure

void someFunction() {
    int x = 5;
    ASSERT(x > 10); // This will cause an infinite loop
}
