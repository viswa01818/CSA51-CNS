#include <stdio.h>
#include <string.h>
#include <ctype.h>

void monoalphabetic_encrypt(char *plaintext, char *key) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int index = tolower(plaintext[i]) - 'a';
            plaintext[i] = isupper(plaintext[i]) ? 
                          toupper(key[index]) : tolower(key[index]);
        }
    }
}

void monoalphabetic_decrypt(char *ciphertext, char *key) {
    int i, j;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char target = tolower(ciphertext[i]);
            
            // Find the position of the ciphertext character in the key
            for (j = 0; j < 26; j++) {
                if (tolower(key[j]) == target) {
                    ciphertext[i] = isupper(ciphertext[i]) ? 
                                   (j + 'A') : (j + 'a');
                    break;
                }
            }
        }
    }
}

int main() {
    char message[1000];
    char key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM"; // Example key
    
    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;
    
    printf("Using key: %s\n", key);
    printf("Original message: %s\n", message);
    
    // Encrypt
    char encrypted[1000];
    strcpy(encrypted, message);
    monoalphabetic_encrypt(encrypted, key);
    printf("Encrypted message: %s\n", encrypted);
    
    // Decrypt
    char decrypted[1000];
    strcpy(decrypted, encrypted);
    monoalphabetic_decrypt(decrypted, key);
    printf("Decrypted message: %s\n", decrypted);
    
    return 0;
}
