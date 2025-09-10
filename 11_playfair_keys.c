#include <stdio.h>
#include <math.h>

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    printf("Playfair Cipher Key Space Analysis\n\n");
    
    // Total possible arrangements of 25 letters (I and J are combined)
    long long total_keys = factorial(25);
    
    printf("a. Total possible keys (ignoring identical results):\n");
    printf("   Total arrangements of 25 letters = 25! = %lld\n", total_keys);
    printf("   As power of 2: 2^%.0f (approximately)\n", log2(total_keys));
    
    // Effectively unique keys considering symmetries
    // Many arrangements produce identical encryption results due to:
    // 1. Row/column order doesn't matter for encryption rules
    // 2. Some arrangements are equivalent under rotation/reflection
    
    printf("\nb. Effectively unique keys (considering identical results):\n");
    printf("   The actual number is much smaller due to:\n");
    printf("   - Row/column permutations that don't affect encryption\n");
    printf("   - Equivalent arrangements under rotation/reflection\n");
    printf("   - Approximately 2^25 to 2^30 effectively unique keys\n");
    
    return 0;
}
