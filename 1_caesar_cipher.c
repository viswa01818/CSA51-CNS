#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar_encrypt(char *plaintext, int key) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = ((plaintext[i] - base + key) % 26) + base;
        }
    }
}

void caesar_decrypt(char *ciphertext, int key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            ciphertext[i] = ((ciphertext[i] - base - key + 26) % 26) + base;
        }
    }
}

int main() {
    char message[1000];
    int key;
    
    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline
    
    printf("Enter key (1-25): ");
    scanf("%d", &key);
    
    if (key < 1 || key > 25) {
        printf("Key must be between 1 and 25\n");
        return 1;
    }
    
    printf("\nOriginal message: %s\n", message);
    
    // Encrypt
    char encrypted[1000];
    strcpy(encrypted, message);
    caesar_encrypt(encrypted, key);
    printf("Encrypted message: %s\n", encrypted);
    
    // Decrypt
    char decrypted[1000];
    strcpy(decrypted, encrypted);
    caesar_decrypt(decrypted, key);
    printf("Decrypted message: %s\n", decrypted);
    
    return 0;
}
