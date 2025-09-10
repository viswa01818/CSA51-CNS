#include <stdio.h>
#include <math.h>

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    printf("RSA Common Factor Analysis\n\n");
    
    printf("Given: n = pq, e is public key\n");
    printf("Someone knows a plaintext block has a common factor with n\n\n");
    
    printf("This DOES help us in the following ways:\n\n");
    
    printf("1. If gcd(plaintext, n) > 1, then:\n");
    printf("   - gcd(plaintext, n) = p or q\n");
    printf("   - We can factor n immediately\n");
    printf("   - We can compute φ(n) = (p-1)(q-1)\n");
    printf("   - We can find the private key d\n\n");
    
    printf("2. Attack method:\n");
    printf("   - Compute gcd(plaintext, n)\n");
    printf("   - If result > 1, we found a factor of n\n");
    printf("   - Use this to break the entire RSA system\n\n");
    
    printf("3. Example:\n");
    long long n = 3599, plaintext = 13;
    long long factor = gcd(plaintext, n);
    
    printf("   n = %lld, plaintext = %lld\n", n, plaintext);
    printf("   gcd(%lld, %lld) = %lld\n", plaintext, n, factor);
    
    if (factor > 1) {
        printf("   Found factor: %lld\n", factor);
        printf("   Other factor: %lld\n", n / factor);
        printf("   Attack successful!\n");
    } else {
        printf("   No common factor found\n");
    }
    
    return 0;
}
