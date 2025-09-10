#include <stdio.h>
#include <math.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    printf("Diffie-Hellman Protocol Analysis\n\n");
    
    printf("Original protocol:\n");
    printf("Alice: sends a^x mod q\n");
    printf("Bob: sends a^y mod q\n");
    printf("Shared key: a^(xy) mod q\n\n");
    
    printf("Modified protocol (sending x^a and y^a):\n");
    printf("Alice: sends x^a mod q\n");
    printf("Bob: sends y^a mod q\n\n");
    
    printf("Problems with modified protocol:\n");
    printf("1. No shared key can be derived\n");
    printf("2. Alice and Bob can't agree on same key\n");
    printf("3. Protocol is fundamentally broken\n\n");
    
    printf("Alternative method for key agreement:\n");
    printf("1. Use original DH: a^x mod q and a^y mod q\n");
    printf("2. Or use RSA-based key exchange\n");
    printf("3. Or use elliptic curve cryptography\n\n");
    
    printf("Can Eve break the system?\n");
    printf("- Yes, if she can solve discrete logarithm problem\n");
    printf("- If she finds x from x^a mod q, she can compute shared key\n");
    printf("- Security depends on difficulty of discrete log\n\n");
    
    printf("Example with small numbers:\n");
    long long q = 23, a = 5, x = 6, y = 15;
    long long alice_sends = mod_exp(a, x, q);
    long long bob_sends = mod_exp(a, y, q);
    long long shared_key = mod_exp(a, x * y, q);
    
    printf("q = %lld, a = %lld\n", q, a);
    printf("Alice's secret: x = %lld, sends: %lld\n", x, alice_sends);
    printf("Bob's secret: y = %lld, sends: %lld\n", y, bob_sends);
    printf("Shared key: %lld\n", shared_key);
    
    return 0;
}
