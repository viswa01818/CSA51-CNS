#include <stdio.h>
#include <math.h>

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long extended_gcd(long long a, long long b, long long *x, long long *y) {
    if (a == 0) { *x = 0; *y = 1; return b; }
    long long x1, y1;
    long long gcd_val = extended_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd_val;
}

long long mod_inverse(long long e, long long phi) {
    long long x, y;
    long long g = extended_gcd(e, phi, &x, &y);
    if (g != 1) return -1;
    return (x % phi + phi) % phi;
}

int main() {
    long long e = 31, n = 3599;
    long long p, q, phi, d;
    
    printf("RSA Private Key Calculation\n\n");
    printf("Given: e = %lld, n = %lld\n\n", e, n);
    
    // Find p and q by trial and error
    printf("Finding p and q by trial and error:\n");
    for (p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            printf("Found: p = %lld, q = %lld\n", p, q);
            printf("Verification: p * q = %lld * %lld = %lld\n", p, q, p * q);
            break;
        }
    }
    
    // Calculate phi(n)
    phi = (p - 1) * (q - 1);
    printf("\nφ(n) = (p-1)(q-1) = (%lld-1)(%lld-1) = %lld\n", p, q, phi);
    
    // Find private key d
    d = mod_inverse(e, phi);
    printf("\nFinding d such that e*d ≡ 1 (mod φ(n))\n");
    printf("d = %lld\n", d);
    
    printf("\nVerification: e * d mod φ(n) = %lld * %lld mod %lld = %lld\n", 
           e, d, phi, (e * d) % phi);
    
    printf("\nPrivate key: d = %lld\n", d);
    
    return 0;
}
