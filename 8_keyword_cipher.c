#include <stdio.h>
#include <string.h>
#include <ctype.h>

void create_keyword_cipher(char *keyword, char *cipher_alphabet) {
    int i, j, k = 0;
    int used[26] = {0};
    
    // Add keyword letters (removing duplicates)
    for (i = 0; keyword[i] != '\0' && k < 26; i++) {
        char c = toupper(keyword[i]);
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            cipher_alphabet[k++] = c;
            used[c - 'A'] = 1;
        }
    }
    
    // Add remaining letters in alphabetical order
    for (i = 0; i < 26 && k < 26; i++) {
        if (!used[i]) {
            cipher_alphabet[k++] = 'A' + i;
        }
    }
    cipher_alphabet[26] = '\0';
}

void keyword_encrypt(char *plaintext, char *cipher_alphabet) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int index = tolower(plaintext[i]) - 'a';
            plaintext[i] = isupper(plaintext[i]) ? 
                          cipher_alphabet[index] : tolower(cipher_alphabet[index]);
        }
    }
}

void keyword_decrypt(char *ciphertext, char *cipher_alphabet) {
    int i, j;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char target = toupper(ciphertext[i]);
            
            // Find position in cipher alphabet
            for (j = 0; j < 26; j++) {
                if (cipher_alphabet[j] == target) {
                    ciphertext[i] = isupper(ciphertext[i]) ? 
                                   (j + 'A') : (j + 'a');
                    break;
                }
            }
        }
    }
}

int main() {
    char keyword[100];
    char message[1000];
    char cipher_alphabet[27];
    
    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;
    
    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;
    
    create_keyword_cipher(keyword, cipher_alphabet);
    
    printf("\nKeyword: %s\n", keyword);
    printf("Cipher alphabet: %s\n", cipher_alphabet);
    
    printf("\nPlaintext alphabet:  ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher alphabet:     %s\n", cipher_alphabet);
    
    printf("\nOriginal message: %s\n", message);
    
    // Encrypt
    char encrypted[1000];
    strcpy(encrypted, message);
    keyword_encrypt(encrypted, cipher_alphabet);
    printf("Encrypted message: %s\n", encrypted);
    
    // Decrypt
    char decrypted[1000];
    strcpy(decrypted, encrypted);
    keyword_decrypt(decrypted, cipher_alphabet);
    printf("Decrypted message: %s\n", decrypted);
    
    return 0;
}
