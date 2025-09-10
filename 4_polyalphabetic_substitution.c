#include <stdio.h>
#include <string.h>
#include <ctype.h>

void polyalphabetic_encrypt(char *plaintext, char *key) {
    int i, key_len = strlen(key);
    int key_index = 0;
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int shift = toupper(key[key_index % key_len]) - 'A';
            
            plaintext[i] = ((plaintext[i] - base + shift) % 26) + base;
            key_index++;
        }
    }
}

void polyalphabetic_decrypt(char *ciphertext, char *key) {
    int i, key_len = strlen(key);
    int key_index = 0;
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int shift = toupper(key[key_index % key_len]) - 'A';
            
            ciphertext[i] = ((ciphertext[i] - base - shift + 26) % 26) + base;
            key_index++;
        }
    }
}

int main() {
    char message[1000];
    char key[100];
    
    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;
    
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;
    
    printf("\nOriginal message: %s\n", message);
    printf("Key: %s\n", key);
    
    // Encrypt
    char encrypted[1000];
    strcpy(encrypted, message);
    polyalphabetic_encrypt(encrypted, key);
    printf("Encrypted message: %s\n", encrypted);
    
    // Decrypt
    char decrypted[1000];
    strcpy(decrypted, encrypted);
    polyalphabetic_decrypt(decrypted, key);
    printf("Decrypted message: %s\n", decrypted);
    
    return 0;
}
