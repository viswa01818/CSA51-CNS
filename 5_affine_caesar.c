#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void affine_encrypt(char *plaintext, int a, int b) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int p = tolower(plaintext[i]) - 'a';
            int c = (a * p + b) % 26;
            plaintext[i] = isupper(plaintext[i]) ? 
                          (c + 'A') : (c + 'a');
        }
    }
}

void affine_decrypt(char *ciphertext, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    int i;
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int c = tolower(ciphertext[i]) - 'a';
            int p = (a_inv * (c - b + 26)) % 26;
            ciphertext[i] = isupper(ciphertext[i]) ? 
                           (p + 'A') : (p + 'a');
        }
    }
}

int main() {
    char message[1000];
    int a, b;
    
    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;
    
    printf("Enter value of 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    
    printf("Enter value of 'b': ");
    scanf("%d", &b);
    
    // Check if 'a' is valid
    if (gcd(a, 26) != 1) {
        printf("Error: 'a' must be coprime with 26\n");
        printf("Valid values of 'a': 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25\n");
        return 1;
    }
    
    printf("\nOriginal message: %s\n", message);
    printf("Affine parameters: a=%d, b=%d\n", a, b);
    
    // Encrypt
    char encrypted[1000];
    strcpy(encrypted, message);
    affine_encrypt(encrypted, a, b);
    printf("Encrypted message: %s\n", encrypted);
    
    // Decrypt
    char decrypted[1000];
    strcpy(decrypted, encrypted);
    affine_decrypt(decrypted, a, b);
    printf("Decrypted message: %s\n", decrypted);
    
    // Analysis
    printf("\nAnalysis:\n");
    printf("a. Limitations on 'b': b can be any integer (0-25)\n");
    printf("b. Invalid values of 'a': ");
    for (int i = 1; i < 26; i++) {
        if (gcd(i, 26) != 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    return 0;
}
