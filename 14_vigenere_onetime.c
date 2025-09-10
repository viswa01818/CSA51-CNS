#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenere_onetime_encrypt(char *plaintext, int *key_stream, int key_len) {
    int i, key_index = 0;
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int shift = key_stream[key_index % key_len];
            
            plaintext[i] = ((plaintext[i] - base + shift) % 26) + base;
            key_index++;
        }
    }
}

void vigenere_onetime_decrypt(char *ciphertext, int *key_stream, int key_len) {
    int i, key_index = 0;
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int shift = key_stream[key_index % key_len];
            
            ciphertext[i] = ((ciphertext[i] - base - shift + 26) % 26) + base;
            key_index++;
        }
    }
}

int main() {
    char message[] = "send more money";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_len = sizeof(key_stream) / sizeof(key_stream[0]);
    
    printf("Vigenère One-Time Pad Encryption\n\n");
    printf("Message: %s\n", message);
    printf("Key stream: ");
    for (int i = 0; i < key_len; i++) {
        printf("%d ", key_stream[i]);
    }
    printf("\n\n");
    
    // Encrypt
    char encrypted[1000];
    strcpy(encrypted, message);
    vigenere_onetime_encrypt(encrypted, key_stream, key_len);
    printf("Encrypted: %s\n", encrypted);
    
    // Decrypt
    char decrypted[1000];
    strcpy(decrypted, encrypted);
    vigenere_onetime_decrypt(decrypted, key_stream, key_len);
    printf("Decrypted: %s\n", decrypted);
    
    // Part b: Find key for "cash not needed"
    printf("\nPart b: Finding key for 'cash not needed'\n");
    char target[] = "cash not needed";
    char cipher[] = "send more money";
    
    printf("Target plaintext: %s\n", target);
    printf("Ciphertext: %s\n", cipher);
    printf("Required key stream: ");
    
    for (int i = 0; i < strlen(target); i++) {
        if (isalpha(target[i]) && isalpha(cipher[i])) {
            int target_val = tolower(target[i]) - 'a';
            int cipher_val = tolower(cipher[i]) - 'a';
            int key_val = (target_val - cipher_val + 26) % 26;
            printf("%d ", key_val);
        }
    }
    printf("\n");
    
    return 0;
}
