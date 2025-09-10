#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void affine_encrypt(char *plaintext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int p = tolower(plaintext[i]) - 'a';
            int c = (a * p + b) % 26;
            plaintext[i] = isupper(plaintext[i]) ? (c + 'A') : (c + 'a');
        }
    }
}

int main() {
    char message[] = "affine cipher test";
    int a = 5, b = 8;
    
    printf("Affine Caesar Cipher (Second Implementation)\n\n");
    printf("Message: %s\n", message);
    printf("Parameters: a=%d, b=%d\n", a, b);
    
    if (gcd(a, 26) != 1) {
        printf("Error: a must be coprime with 26\n");
        return 1;
    }
    
    char encrypted[1000];
    strcpy(encrypted, message);
    affine_encrypt(encrypted, a, b);
    printf("Encrypted: %s\n", encrypted);
    
    return 0;
}
