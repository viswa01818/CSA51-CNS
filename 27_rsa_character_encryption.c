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
    printf("RSA Character-by-Character Encryption Analysis\n\n");
    
    printf("Method: Encrypt each letter A=0, B=1, ..., Z=25 separately\n");
    printf("Using RSA with large e and large n\n\n");
    
    printf("This method is NOT secure because:\n\n");
    
    printf("1. Small message space:\n");
    printf("   - Only 26 possible plaintexts (0-25)\n");
    printf("   - Attacker can precompute all possible ciphertexts\n");
    printf("   - Create lookup table: plaintext -> ciphertext\n\n");
    
    printf("2. Most efficient attack:\n");
    printf("   - Precompute: c_i = i^e mod n for i = 0,1,2,...,25\n");
    printf("   - For each received ciphertext, lookup in table\n");
    printf("   - Time complexity: O(1) per character\n");
    printf("   - Space complexity: O(1) - only 26 entries\n\n");
    
    printf("3. Example attack:\n");
    long long e = 65537, n = 3599;
    printf("   Using e = %lld, n = %lld\n", e, n);
    printf("   Precomputed table:\n");
    
    for (int i = 0; i < 26; i++) {
        long long cipher = mod_exp(i, e, n);
        printf("   %c -> %lld\n", 'A' + i, cipher);
    }
    
    printf("\n4. Why this breaks RSA security:\n");
    printf("   - RSA security relies on large message space\n");
    printf("   - Small message space allows exhaustive search\n");
    printf("   - No need to factor n or find private key\n\n");
    
    printf("Solution: Use proper padding (PKCS#1) or encrypt larger blocks\n");
    
    return 0;
}
