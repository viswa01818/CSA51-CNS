#include <stdio.h>
#include <math.h>

int is_prime(long long n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int main() {
    printf("RSA Key Generation Safety Analysis\n\n");
    
    printf("Scenario: Bob leaks his private key d\n");
    printf("Instead of generating new modulus n, he generates new e and d\n\n");
    
    printf("This is NOT safe for the following reasons:\n\n");
    
    printf("1. Same modulus n = pq:\n");
    printf("   - If attacker knows old (e1, d1) and new (e2, d2)\n");
    printf("   - They can compute: e1 * d1 - 1 = k1 * φ(n)\n");
    printf("   - And: e2 * d2 - 1 = k2 * φ(n)\n");
    printf("   - gcd(e1*d1-1, e2*d2-1) likely reveals φ(n)\n");
    printf("   - From φ(n), they can factor n\n\n");
    
    printf("2. Attack method:\n");
    printf("   - Compute gcd(e1*d1-1, e2*d2-1)\n");
    printf("   - This gives multiple of φ(n)\n");
    printf("   - Use this to find p and q\n");
    printf("   - Generate new private key\n\n");
    
    printf("3. Example:\n");
    long long n = 3599, e1 = 31, d1 = 3031, e2 = 7, d2 = 2743;
    long long phi_approx = gcd(e1 * d1 - 1, e2 * d2 - 1);
    
    printf("   n = %lld\n", n);
    printf("   Old keys: e1=%lld, d1=%lld\n", e1, d1);
    printf("   New keys: e2=%lld, d2=%lld\n", e2, d2);
    printf("   gcd(e1*d1-1, e2*d2-1) = %lld\n", phi_approx);
    printf("   This reveals information about φ(n)\n\n");
    
    printf("Conclusion: Always generate new modulus n when private key is compromised!\n");
    
    return 0;
}
