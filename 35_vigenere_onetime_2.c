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

int main() {
    char message[] = "hello world";
    int key_stream[] = {3, 19, 5, 7, 11, 13, 17, 23, 1, 2, 3};
    int key_len = sizeof(key_stream) / sizeof(key_stream[0]);
    
    printf("Vigenère One-Time Pad (Second Implementation)\n\n");
    printf("Message: %s\n", message);
    printf("Key stream: ");
    for (int i = 0; i < key_len; i++) printf("%d ", key_stream[i]);
    printf("\n\n");
    
    char encrypted[1000];
    strcpy(encrypted, message);
    vigenere_onetime_encrypt(encrypted, key_stream, key_len);
    printf("Encrypted: %s\n", encrypted);
    
    return 0;
}
